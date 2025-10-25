import cv2
import numpy as np
from PIL import Image
from pyzbar.pyzbar import decode
import os

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

def identify_qr_code(image_path):
    try:
        # 从输入图片路径获取文件名
        base_name = os.path.basename(image_path)
        name_without_ext = os.path.splitext(base_name)[0]
        output_path = f'output_{name_without_ext}.png'
        
        # 添加调试信息确认图片加载
        print(f"正在尝试打开图片: {image_path}")
        pil_img = Image.open(image_path)
        print(f"图片尺寸: {pil_img.size}, 格式: {pil_img.format}, 模式: {pil_img.mode}")
        
        # 尝试直接用OpenCV读取图片作为备选方案
        cv_img_direct = cv2.imread(image_path)
        if cv_img_direct is None:
            print("OpenCV无法直接读取图片")
        
        cv_img = cv2.cvtColor(np.array(pil_img), cv2.COLOR_RGB2BGR)  # 转换为OpenCV格式

        width, height = pil_img.size  # 获取图像尺寸
        centerpoint = width / 2, height / 2  # 计算中心点
        cp_size = 10  # 中心点大小
        
        # 添加图像预处理步骤
        # 1. 调整图像大小
        height, width = cv_img.shape[:2]
        scale_factor = 2.0  # 放大2倍
        cv_img_resized = cv2.resize(cv_img, (int(width * scale_factor), int(height * scale_factor)))
        
        # 2. 增强图像处理
        gray = cv2.cvtColor(cv_img_resized, cv2.COLOR_BGR2GRAY)
        # 自适应直方图均衡化
        clahe = cv2.createCLAHE(clipLimit=3.0, tileGridSize=(8,8))
        gray = clahe.apply(gray)
        # 高斯模糊减少噪声
        blurred = cv2.GaussianBlur(gray, (5, 5), 0)
        # 自适应阈值处理
        binary = cv2.adaptiveThreshold(blurred, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY, 11, 2)
        
        # 3. 尝试不同的解码方式
        matches = decode(binary)  # 首先尝试处理后的二值图像
        if not matches:
            print("尝试使用放大后的灰度图像进行解码")
            matches = decode(gray)
        if not matches:
            print("尝试使用放大后的原始图像进行解码")
            matches = decode(cv_img_resized)
            
        print(f"识别到的二维码数量: {len(matches)}")
        
        # 如果在放大图像中找到了二维码，需要将坐标映射回原始尺寸
        if matches:
            mapped_matches = []
            for match in matches:
                # 创建新的点来存储映射后的坐标
                mapped_points = []
                for point in match.polygon:
                    mapped_points.append(Point(
                        x=int(point.x / scale_factor),
                        y=int(point.y / scale_factor)
                    ))
                # 创建一个新的匹配对象，包含映射后的坐标
                mapped_match = type('MappedMatch', (), {
                    'polygon': mapped_points,
                    'data': match.data,
                    'type': match.type,
                    'rect': match.rect
                })
                mapped_matches.append(mapped_match)
            
            # 使用映射后的匹配结果
            matches = mapped_matches
            
        count=0
        if matches:
            for match in matches:
                count=count+1
                tl, bl, br, tr = match.polygon  # 获取QR码的四个角点
                match_cp = ((tl.x + bl.x + br.x + tr.x) / 4, (tl.y + bl.y + br.y + tr.y) / 4)  # 计算中心点

                centerpoint_dist = np.linalg.norm(np.array(match_cp) - np.array(centerpoint))  # 计算中心点距离
                outline_color = (0, 0, 255)  # 默认轮廓颜色
                if centerpoint_dist < 10:
                    outline_color = (0, 255, 0)  # 如果距离小于10，改变颜色

                # 绘制轮廓
                cv2.line(cv_img, (tl.x, tl.y), (bl.x, bl.y), outline_color, 3)
                cv2.line(cv_img, (bl.x, bl.y), (br.x, br.y), outline_color, 3)
                cv2.line(cv_img, (br.x, br.y), (tr.x, tr.y), outline_color, 3)
                cv2.line(cv_img, (tr.x, tr.y), (tl.x, tl.y), outline_color, 3)

                # 绘制中心点
                cv2.line(cv_img, (int(match_cp[0] - cp_size), int(match_cp[1] - cp_size)), (int(match_cp[0] + cp_size), int(match_cp[1] + cp_size)), (0, 0, 255), 2)
                cv2.line(cv_img, (int(match_cp[0] - cp_size), int(match_cp[1] + cp_size)), (int(match_cp[0] + cp_size), int(match_cp[1] - cp_size)), (0, 0, 255), 2)

                # 绘制图像中心
                cv2.line(cv_img, (int(centerpoint[0] - cp_size), int(centerpoint[1] - cp_size)), (int(centerpoint[0] + cp_size), int(centerpoint[1] + cp_size)), (255, 0, 0), 2)
                cv2.line(cv_img, (int(centerpoint[0] - cp_size), int(centerpoint[1] + cp_size)), (int(centerpoint[0] + cp_size), int(centerpoint[1] - cp_size)), (255, 0, 0), 2)

                # 绘制文本
                cv2.putText(cv_img, f'ID:{match.data.decode("utf-8")}', (tl.x-10, tl.y - 12), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)
                
                # 显示二维码中心点坐标
                cv2.putText(cv_img, f'{count}{match_cp}', (int(match_cp[0]), int(match_cp[1] - 20)), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)
                # 在中心点旁边标注坐标（0,0）
                print(f'{count}二维码位置: ({match_cp[0]/1000:.2f}, {match_cp[1]/1000:.2f}), 编码: {match.data.decode("utf-8")}')

        # 保存处理后的图片
        cv2.imwrite(output_path, cv_img)
        print(f"已保存处理后的图片到: {output_path}")

        cv2.imshow('QR Code Detection', cv_img)  # 显示图像
        cv2.waitKey(0)
        cv2.destroyAllWindows()

    except Exception as exc:
        print('Error: %s' % exc)  # 错误日志

if __name__ == '__main__':
    identify_qr_code('/home/dsh/Documents/work_logs/1_3二维码定位/test_img/1.jpeg')  # 替换为你的图像路径