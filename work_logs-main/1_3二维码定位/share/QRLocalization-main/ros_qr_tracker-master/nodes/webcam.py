#!/usr/bin/env python  # 指定使用的Python解释器
from __future__ import print_function  # 允许使用Python 3的print函数

import os  # 导入os模块，用于与操作系统交互
import threading  # 导入threading模块，用于多线程处理

import numpy as np  # 导入numpy库，用于数值计算和数组操作

import rospy  # 导入rospy库，用于ROS节点的创建和管理
import std_srvs.srv  # 导入标准服务库
from sensor_msgs.msg import CompressedImage, Image  # 导入ROS传感器消息类型

import cv2  # 导入OpenCV库，用于计算机视觉处理

class WebCam():  # 定义WebCam类
    """
    一个简单的压缩网络摄像头视频流广播节点。
    """

    def __init__(self):  # 初始化方法
        rospy.init_node('webcam', log_level=rospy.DEBUG)  # 初始化ROS节点，设置日志级别为DEBUG

        self._lock = threading.RLock()  # 创建一个递归锁，用于线程安全

        self.image_pub = rospy.Publisher('~image/compressed', CompressedImage, queue_size=1)  # 创建图像发布者

        self.video_index = int(rospy.get_param("~index", 0))  # 获取视频索引参数，默认为0

        self.auto_start = int(rospy.get_param("~start", 0))  # 获取自动启动参数，默认为0

        self.width = int(rospy.get_param("~width", 800))  # 获取图像宽度参数，默认为800
        self.height = int(rospy.get_param("~height", 600))  # 获取图像高度参数，默认为600

        self.running = False  # 初始化运行状态为False

        # 主处理线程的句柄。
        self._camera_thread = None  # 初始化摄像头线程为None

        # 节点终止时的清理。
        rospy.on_shutdown(self.shutdown)  # 注册节点关闭时的清理函数

        rospy.Service('~start', std_srvs.srv.Empty, self.start)  # 创建启动服务

        rospy.Service('~stop', std_srvs.srv.Empty, self.stop)  # 创建停止服务

        if self.auto_start:  # 如果设置了自动启动
            self.start()  # 启动摄像头

        # 开始轮询传感器和基础控制器。
        self.rate = int(rospy.get_param("~rate", 60))  # 获取发布频率参数，默认为60
        r = rospy.Rate(self.rate)  # 创建一个Rate对象，用于控制循环频率
        while not rospy.is_shutdown():  # 当节点未关闭时
            r.sleep()  # 休眠以保持循环频率

    def start(self, msg=None):  # 启动摄像头的方法
        with self._lock:  # 使用锁确保线程安全
            if not self.running:  # 如果摄像头未运行
                self.running = True  # 设置运行状态为True
                self._camera_thread = threading.Thread(target=self._process_video)  # 创建处理视频的线程
                self._camera_thread.daemon = True  # 设置为守护线程
                self._camera_thread.start()  # 启动线程

    def stop(self, msg=None):  # 停止摄像头的方法
        with self._lock:  # 使用锁确保线程安全
            if self._camera_thread:  # 如果摄像头线程存在
                self.running = False  # 设置运行状态为False
                self._camera_thread.join()  # 等待线程结束
                self._camera_thread = None  # 清空线程句柄

    def _process_video(self):  # 处理视频流的方法
        video_capture = cv2.VideoCapture(self.video_index)  # 打开视频捕捉设备
        video_capture.set(cv2.CAP_PROP_FRAME_WIDTH, self.width)  # 设置视频宽度
        video_capture.set(cv2.CAP_PROP_FRAME_HEIGHT, self.height)  # 设置视频高度
        try:
            while self.running:  # 当摄像头运行时
                ret, frame = video_capture.read()  # 读取视频帧

                msg = CompressedImage()  # 创建压缩图像消息
                msg.header.stamp = rospy.Time.now()  # 设置时间戳
                msg.format = "jpeg"  # 设置图像格式为jpeg
                msg.data = np.array(cv2.imencode('.jpg', frame)[1]).tostring()  # 编码图像并转换为字节
                self.image_pub.publish(msg)  # 发布图像消息
        except rospy.exceptions.ROSInterruptException:  # 捕获ROS中断异常
            self.running = False  # 设置运行状态为False

        if video_capture:  # 如果视频捕捉对象存在
            video_capture.release()  # 释放视频捕捉对象

    def shutdown(self):  # 清理方法
        rospy.loginfo('Shutting down...')  # 打印关闭信息
        self.running = False  # 设置运行状态为False
        rospy.loginfo('Done.')  # 打印完成信息

if __name__ == '__main__':  # 如果是主程序
    WebCam()  # 创建WebCam实例
