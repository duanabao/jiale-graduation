import cv2
import numpy as np

# 读取图像
image = cv2.imread('image.jpg', cv2.IMREAD_GRAYSCALE)

# 如果图像读取失败，退出
if image is None:
    print("图像加载失败!")
    exit()

# 使用高斯模糊去噪
blurred = cv2.GaussianBlur(image, (5, 5), 0)

# 使用Canny边缘检测
edges = cv2.Canny(blurred, 50, 150)


# 霍夫圆变换检测圆形（这里假设孔的半径为2.5mm）
# 根据图像的分辨率调整半径的值，这里假设每个像素为0.4mm
radius_in_pixels = 5 / 0.4  # 5mm / 0.4mm/pixel ≈ 12.5像素

# 执行霍夫变换
circles = cv2.HoughCircles(
    edges,                          # 输入图像（通常是边缘图）
    cv2.HOUGH_GRADIENT,            # 检测方法
    dp=1,                          # 累加器分辨率比率（通常设为1）
    minDist=10,                    # 将-10改为10，圆之间的最小距离必须为正数
    param1=40,                     # Canny边缘检测的高阈值
    param2=20,                     # 累加器阈值
    minRadius=int(radius_in_pixels - 20),  
    maxRadius=int(radius_in_pixels + 20)   
)

# 检测到的圆
if circles is not None:
    circles = np.round(circles[0, :]).astype("int")
    for (x, y, r) in circles:
        # 绘制圆形
        cv2.circle(image, (x, y), r, (0, 255, 0), 4)
        print(f"孔的中心坐标：({x}, {y}), 半径：{r}")

    # 假设图像的像素单位与实际物理单位的比例是0.4mm/像素
    pixel_to_mm = 0.4  # 每个像素代表0.4mm

    # 将孔的坐标从像素单位转换为毫米
    for (x, y, r) in circles:
        x_mm = x * pixel_to_mm  # X坐标转换为毫米
        y_mm = y * pixel_to_mm  # Y坐标转换为毫米
        r_mm = r * pixel_to_mm  # 半径转换为毫米
        print(f"孔的物理坐标：({x_mm:.2f}mm, {y_mm:.2f}mm), 半径：{r_mm:.2f}mm")
        
    # 显示检测结果
    cv2.imshow("Detected Circles", image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

else:
    print("未检测到孔")
