import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
from sensor_msgs.msg import Range, Image
import random
import cv2
import numpy as np
from cv_bridge import CvBridge

class PhotoSheetNode(Node):
    def __init__(self):
        super().__init__('photo_sheet_node')

        # 订阅 TOF 传感器数据
        self.tof_subscriber = self.create_subscription(Range, '/tof', self.tof_callback, 10)
        self.ps0_subscriber = self.create_subscription(Range, '/ps0', self.ps0_message, 10)
        self.ps7_subscriber = self.create_subscription(Range, '/ps7', self.ps7_message, 10)
        self.ps1_subscriber = self.create_subscription(Range, '/ps1', self.ps1_message, 10)
        self.ps6_subscriber = self.create_subscription(Range, '/ps6', self.ps6_message, 10)

        # 初始化传感器值和状态
        self.ps0_value = self.ps7_value = self.ps1_value = self.ps6_value = 0
        self.obstacle_detected = False
        self.__now = self.get_clock().now().to_msg()

        # 创建发布器，用于发布速度控制命令
        self.velocity_publisher = self.create_publisher(Twist, '/cmd_vel', 10)

        # 初始化随机数生成器
        random.seed()

        # 初始化一个标志位，表示机器人是否遇到了障碍物
        self.walk_or_rotate = False

        # 定时器用于持续调用 move_robot 函数
        self.timer = self.create_timer(2, self.check_obstacle)

        # 订阅相机图像
        self.image_subscriber = self.create_subscription(Image, '/camera/image_color', self.image_callback, 10)
        self.image_count = 0  # 初始化计数器
        self.image_timer = self.create_timer(10, self.save_image)  # 每两秒调用一次保存图像的函数
        self.image_total = 400 # 总的拍照数

        self.walk_count = 0 # 增加随机性

        self.bridge = CvBridge()

    def ps0_message(self, msg):
        self.ps0_value = msg.range
        self.__now = msg.header.stamp

    def ps7_message(self, msg):
        self.ps7_value = msg.range

    def ps1_message(self, msg):
        self.ps1_value = msg.range

    def ps6_message(self, msg):
        self.ps6_value = msg.range

    def tof_callback(self, msg):
        """TOF 传感器的回调函数，用于检测障碍物"""
        # 如果检测到障碍物 (距离小于0.5米)
        if msg.range < 0.1 or self.ps0_value < 0.04 or self.ps7_value <0.04 or self.ps1_value <0.04 or self.ps6_value <0.04:
            # self.get_logger().info(f'Obstacle detected at {msg.range} meters')
            self.obstacle_detected = True
            
        else:
            self.obstacle_detected = False
                
        self.move_robot()
        

    def check_obstacle(self):
        if self.obstacle_detected: 
            self.walk_or_rotate = False
        else:
            self.walk_or_rotate = True

    def move_robot(self):
        """根据障碍物检测结果移动机器人"""
        twist_msg = Twist()

        if self.walk_or_rotate:
            if not self.obstacle_detected:
                twist_msg.linear.x = 0.08  # 设置直线前进速度
                self.walk_count +=1
                if self.walk_count > 10

                # self.get_logger().info('Moving forward')
        else:
            twist_msg.angular.z = 0.4  # 设置旋转速度
            self.walk_count = 0
            
            # self.get_logger().info(f'Turning')

        self.velocity_publisher.publish(twist_msg)

    def image_callback(self, msg):
        """相机图像的回调函数"""
        self.current_image = msg  # 保存当前图像

    def save_image(self):
        """保存图像的函数"""
        if self.image_count < self.image_total:
            cv_image = self.bridge.imgmsg_to_cv2(self.current_image, desired_encoding='bgr8')
            cv_image = cv2.resize(cv_image, (256, 256))  # 调整图像大小为256x256
            image_path = f'/home/ljl/Documents/工作目录/2_1虚拟环境拍照/img/image_{self.image_count + 1}.png'
            cv2.imwrite(image_path, cv_image)
            self.get_logger().info(f'Saving image {self.image_count + 1}')
            self.image_count += 1
        else:
            self.image_timer.cancel()  # 停止定时器
            self.get_logger().info(f'Stopped saving images after {self.image_total} images.')

def main(args=None):
    rclpy.init(args=args)

    # 创建并运行节点
    node = PhotoSheetNode()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        # 关闭节点
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
