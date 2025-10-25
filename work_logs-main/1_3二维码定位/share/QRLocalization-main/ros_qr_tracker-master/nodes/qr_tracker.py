#!/usr/bin/env python
from __future__ import print_function

import os
import time
import threading
import io
import traceback
from math import sqrt, acos, pi

import numpy as np
from PIL import Image as PilImage

import rospy
import std_srvs.srv
from std_srvs.srv import EmptyResponse
from sensor_msgs.msg import CompressedImage, Image

import libzbar as zb
import cv2
from cv_bridge import CvBridge, CvBridgeError

from ros_qr_tracker.msg import Percept
from ros_qr_tracker.srv import AddTarget, AddTargetResponse, SetTarget, SetTargetResponse

# 计算两个点之间的距离
def dist(a, b):
    return sqrt((a[0] - b[0])**2 + (a[1] - b[1])**2)

# 定义处理模式
class Modes:
    PUSH = 1 # 快速模式 (~30 fps)，但需要更多的CPU（默认）
    PULL = 2 # 慢速模式 (~10fps)，但使用更少的CPU

# QRTracker类用于处理QR码的检测和跟踪
class QRTracker():

    def __init__(self):
        # 初始化ROS节点
        rospy.init_node('qr_tracker', log_level=rospy.DEBUG)

        self._lock = threading.RLock()  # 线程锁

        # 获取相机主题参数
        self.camera_topic = rospy.get_param("~topic", '/camera/compressed')

        # 发布QR码匹配结果
        self.qr_pub = rospy.Publisher('~matches', Percept, queue_size=10)

        # 发布压缩图像
        self.images_pub = rospy.Publisher('~images/compressed', CompressedImage, queue_size=1)

        # 获取显示匹配结果的参数
        self.show_matches = int(rospy.get_param("~show_matches", 1))

        # 获取自动启动参数
        self.auto_start = int(rospy.get_param("~start", 0))

        # 获取处理模式参数
        self.processing_mode = int(rospy.get_param('~mode', Modes.PULL))

        # 用于估计QR码距离的焦距
        self.focal_length = float(rospy.get_param('~focal_length', 640))

        # 要搜索的QR码文本
        self._targets = [_ for _ in rospy.get_param("~targets", '').split(',') if _.strip()]

        self.running = False  # 运行状态
        self._frames = 0  # 帧计数
        self.last_msg = None  # 最后接收到的消息
        self._t0 = None  # 计时器
        self.bridge = CvBridge()  # OpenCV与ROS图像转换的桥接

        # 处理线程和图像订阅者的句柄
        self._camera_thread = None
        self._camera_sub = None

        # 节点终止时的清理
        rospy.on_shutdown(self.shutdown)

        # 定义服务
        rospy.Service('~start', std_srvs.srv.Empty, self.start)
        rospy.Service('~stop', std_srvs.srv.Empty, self.stop)
        rospy.Service('~set_target', SetTarget, self.set_target)
        rospy.Service('~add_target', AddTarget, self.add_target)
        rospy.Service('~clear_target', std_srvs.srv.Empty, self.clear_target)

        if self.auto_start:
            self.start()  # 自动启动

        # 开始轮询传感器和基础控制器
        self.rate = int(rospy.get_param("~rate", 60))
        r = rospy.Rate(self.rate)
        while not rospy.is_shutdown():
            r.sleep()  # 休眠以保持循环速率

    @property
    def fps(self):
        return self._frames/float(time.time() - self._t0)  # 计算帧率

    def start(self, msg=None):
        with self._lock:
            self.running = True  # 设置运行状态为True

            if self.processing_mode == Modes.PULL:
                # 启动线程进行轮询
                if not self._camera_thread:
                    self._camera_thread = threading.Thread(target=self._process_video)
                    self._camera_thread.daemon = True
                    self._camera_thread.start()

            elif self.processing_mode == Modes.PUSH:
                # 启动线程进行推送
                if not self._camera_sub:
                    if 'compressed' in self.camera_topic:
                        self._camera_sub = rospy.Subscriber(
                            self.camera_topic, CompressedImage, self._process_video)
                    else:
                        self._camera_sub = rospy.Subscriber(
                            self.camera_topic, Image, self._process_video)

            else:
                raise NotImplementedError  # 未实现的处理模式

            rospy.loginfo('Processing started.')  # 日志信息
        return EmptyResponse()

    def stop(self, msg=None):
        with self._lock:
            if self._camera_thread:
                self.running = False  # 设置运行状态为False
                self._camera_thread.join()  # 等待线程结束
                self._camera_thread = None

            if self._camera_sub:
                self._camera_sub.unregister()  # 取消订阅
                self._camera_sub = None

            rospy.loginfo('Processing stopped.')  # 日志信息
            self._frames = 0  # 重置帧计数
            self._t0 = None  # 重置计时器
        return EmptyResponse()

    def set_target(self, msg):
        with self._lock:
            self._targets = [msg.data]  # 设置目标
            rospy.loginfo('Set target "%s".', msg.data)  # 日志信息
        return SetTargetResponse()

    def add_target(self, msg):
        with self._lock:
            self._targets.append(msg.data)  # 添加目标
            rospy.loginfo('Appended target "%s".', msg.data)  # 日志信息
            rospy.loginfo('There are now %i targets.', len(self._targets))  # 日志信息
        return AddTargetResponse()

    def clear_target(self, msg=None):
        with self._lock:
            self._targets = []  # 清除目标
            rospy.loginfo('Targets cleared.')  # 日志信息
        return EmptyResponse()

    def get_image(self):
        try:
            if 'compressed' in self.camera_topic:
                msg = rospy.wait_for_message(self.camera_topic, CompressedImage, timeout=1)  # 等待接收压缩图像
            else:
                msg = rospy.wait_for_message(self.camera_topic, Image, timeout=1)  # 等待接收图像
            with self._lock:
                self.last_msg = msg  # 更新最后接收到的消息
            return msg
        except rospy.exceptions.ROSException:
            return  # 返回None

    def normalize_compressed_image(self, msg):
        return PilImage.open(io.BytesIO(bytearray(msg.data)))  # 将压缩图像转换为PIL图像

    def normalize_image_cv2(self, msg):
        if isinstance(msg, CompressedImage):
            pil_image = self.normalize_compressed_image(msg)  # 处理压缩图像
            cv_image = np.array(pil_image)  # 转换为NumPy数组
            return cv_image
        cv_image = self.bridge.imgmsg_to_cv2(msg, "bgra8")  # 转换为OpenCV格式
        return cv2.cvtColor(cv_image, cv2.COLOR_BGRA2RGB)  # 转换颜色空间

    def normalize_image_pil(self, msg):
        if isinstance(msg, CompressedImage):
            return self.normalize_compressed_image(msg)  # 处理压缩图像
        cv_image = self.normalize_image_cv2(msg)  # 处理普通图像
        return PilImage.fromarray(cv_image)  # 转换为PIL图像

    def get_image_pil(self, msg=None):
        msg = msg or self.get_image()  # 获取图像
        if msg:
            return self.normalize_image_pil(msg)  # 返回PIL图像

    def get_image_cv2(self, msg=None):
        msg = msg or self.get_image()  # 获取图像
        if msg:
            return self.normalize_image_cv2(msg)  # 返回OpenCV图像

    def _process_video(self, msg=None):
        try:
            if msg:
                with self._lock:
                    self.last_msg = msg  # 更新最后接收到的消息

            while self.running:
                pil_img = self.get_image_pil(msg=msg)  # 获取PIL图像
                if pil_img:
                    if self.show_matches:
                        try:
                            cv_img = cv2.cvtColor(np.array(pil_img), cv2.COLOR_RGB2BGR)  # 转换为OpenCV格式
                        except Exception as exc:
                            rospy.log_error('Unable to read image: %s', exc)  # 错误日志
                            traceback.print_exc()

                    # 计算帧率
                    if not self._frames:
                        self._t0 = time.time()  # 记录开始时间
                    self._frames += 1  # 增加帧计数
                    if not self._frames % 50:
                        rospy.loginfo('fps: %s', self.fps)  # 日志帧率

                    width, height = pil_img.size  # 获取图像尺寸
                    centerpoint = width/2, height/2  # 计算中心点
                    cp_size = 10  # 中心点大小
                    # 使用zb库中的Image类将PIL图像转换为zb图像对象，并调用scan方法扫描QR码
                    matches = zb.Image.from_im(pil_img).scan()  # 扫描QR码并返回识别到的QR码列表

                    if matches:
                        for match in matches:
                            with self._lock:
                                if self._targets and match.data not in self._targets:
                                    continue  # 如果不在目标列表中则跳过

                            tl, bl, br, tr = match.locator  # 获取QR码的四个角点
                            match_cp = ((tl[0]+bl[0]+br[0]+tr[0])/4, (tl[1]+bl[1]+br[1]+tr[1])/4)  # 计算中心点

                            centerpoint_dist = dist((match_cp[0], 0), (centerpoint[0], 0))  # 计算中心点距离
                            outline_color = (0, 0, 255)  # 默认轮廓颜色
                            if centerpoint_dist < 10:
                                outline_color = (0, 255, 0)  # 如果距离小于10，改变颜色

                            distance_mm = '?'  # 距离初始化
                            distance_meters = None  # 米数初始化
                            camera_angle_radians = None  # 相机角度初始化
                            known_width_mm = None  # 已知宽度初始化
                            known_height_mm = None  # 已知高度初始化
                            if '=' in match.data:
                                data_pairs = dict(part.split('=')[:2] for part in match.data.split(','))  # 解析数据
                                if 'w' in data_pairs:
                                    known_width_mm = int(data_pairs['w'])  # 获取已知宽度
                                if 'h' in data_pairs:
                                    known_height_mm = int(data_pairs['h'])  # 获取已知高度

                            if self.show_matches:
                                # 绘制轮廓
                                cv2.line(cv_img, tl, bl, outline_color, 3)
                                cv2.line(cv_img, bl, br, outline_color, 3)
                                cv2.line(cv_img, br, tr, outline_color, 3)
                                cv2.line(cv_img, tr, tl, outline_color, 3)

                                # 绘制中心点
                                cv2.line(cv_img, (match_cp[0]-cp_size, match_cp[1]-cp_size), (match_cp[0]+cp_size, match_cp[1]+cp_size), (0, 0, 255), 2)
                                cv2.line(cv_img, (match_cp[0]-cp_size, match_cp[1]+cp_size), (match_cp[0]+cp_size, match_cp[1]-cp_size), (0, 0, 255), 2)

                                # 绘制图像中心
                                cv2.line(cv_img, (centerpoint[0]-cp_size, centerpoint[1]-cp_size), (centerpoint[0]+cp_size, centerpoint[1]+cp_size), (255, 0, 0), 2)
                                cv2.line(cv_img, (centerpoint[0]-cp_size, centerpoint[1]+cp_size), (centerpoint[0]+cp_size, centerpoint[1]-cp_size), (255, 0, 0), 2)

                                # 计算视角方向
                                true_bl, true_br = sorted([tl, bl, br, tr], key=lambda p: p[1])[:2]
                                bottom_hyp = sqrt((true_bl[0] - true_br[0])**2 + (true_bl[1] - true_br[1])**2)
                                bottom_x = true_bl[0] - true_br[0]
                                camera_angle0 = acos(bottom_x/float(bottom_hyp))
                                angle_direction = 1
                                if camera_angle0 > pi/2:
                                    angle_direction = -1
                                distances = [dist(tl, tr), dist(tr, br), dist(br, bl), dist(bl, tl)]

                                # 计算相机视角
                                max_distance = max(distances)
                                min_distance = min(distances)
                                camera_angle_degrees = (90 - min_distance/float(max_distance)*90) * angle_direction
                                camera_angle_radians = camera_angle_degrees * pi / 180.

                                if known_width_mm:
                                    pixel_width1 = dist(tl, tr)
                                    pixel_width2 = dist(bl, br)
                                    pixel_width = (pixel_width1 + pixel_width2)/2.
                                    distance_mm = int((known_width_mm * self.focal_length) / float(pixel_width))  # 计算距离
                                    distance_meters = distance_mm * 1/1000.  # 转换为米

                                    min_point = min(tl, bl, br, tr, key=lambda p: p[0]**2 + p[1]**2)  # 获取最小点

                                font = cv2.FONT_HERSHEY_SIMPLEX  # 字体设置
                                bottomLeftCornerOfText_distance = (min_point[0], -22/2 + min_point[1])  # 文本位置
                                fontScale = 1  # 字体缩放
                                fontColor = (0, 0, 255)  # 字体颜色
                                white = (255, 255, 255)  # 白色
                                lineType = 2  # 线条类型

                                # 绘制文本
                                for point_label, point_coords in zip(('tl', 'tr', 'bl', 'br'), (tl, tr, bl, br)):
                                    cv2.putText(cv_img, point_label, point_coords, font, fontScale, (255, 0, 0), lineType)

                                cv2.putText(cv_img, 'Distance (mm) = %i' % distance_mm, (min_point[0], -22/2 + min_point[1] + 30*1), font, fontScale*0.5, white, lineType)
                                cv2.putText(cv_img, 'Angle (deg) = %.02f' % camera_angle_degrees, (min_point[0], -22/2 + min_point[1] + 30*2), font, fontScale*0.5, white, lineType)
                                cv2.putText(cv_img, 'X = %i' % match_cp[0], (min_point[0], -22/2 + min_point[1] + 30*3), font, fontScale*0.5, white, lineType)
                                cv2.putText(cv_img, 'Y = %i' % match_cp[1], (min_point[0], -22/2 + min_point[1] + 30*4), font, fontScale*0.5, white, lineType)

                            if self.qr_pub.getNumSubcribers():
                                percept = Percept()  # 创建感知对象
                                percept.frame = self.camera_topic
                                percept.type = match.type
                                percept.quality = match.quality
                                percept.a = list(tl)
                                percept.b = list(bl)
                                percept.c = list(br)
                                percept.d = list(tr)
                                percept.width = width
                                percept.height = height
                                percept.distance = distance_meters
                                percept.deflection_angle = camera_angle_radians
                                percept.data = match.data
                                self.qr_pub.publish(percept)  # 发布感知结果

                    if self.show_matches and self.images_pub.getNumSubcribers():
                        self.images_pub.publish(self.bridge.cv2_to_compressed_imgmsg(cv_img, dst_format='jpg'))  # 发布图像

                # 如果不是线程并且已经处理了单个消息，则立即退出
                if msg:
                    break

        except rospy.exceptions.ROSInterruptException:
            pass
        finally:
            if not msg:
                self.running = False  # 结束运行

    def shutdown(self):
        rospy.loginfo('Shutting down...')  # 日志信息
        self.running = False  # 设置运行状态为False
        rospy.loginfo('Done.')  # 日志信息

if __name__ == '__main__':
    QRTracker()  # 启动QRTracker
