import csv
import rclpy
from rclpy.node import Node
from nav_msgs.msg import Path
from geometry_msgs.msg import PoseStamped
import numpy as np  

class PathPublisher(Node):

    def __init__(self):
        super().__init__('path_publisher')
        # 发布到 /path 话题
        self.publisher_ = self.create_publisher(Path, '/path_location', 10)
       
        # 订阅话题
        self.create_subscription(
            PoseStamped,
            '/qr_code_pose',
            self.location_callback,
            10
        )

        self.path = Path()
        self.path.header.frame_id = 'odom'
        self.location = None
     
    def location_callback(self,msg):
        self.location = msg
        # 将 PoseStamped 加入 Path 消息中
        self.path.poses.append(self.location)
       
        # 发布路径
        self.publisher_.publish(self.path)
        self.get_logger().info(f'Publishing position {self.location}')

def main(args=None):
    rclpy.init(args=args)
    node = PathPublisher()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
