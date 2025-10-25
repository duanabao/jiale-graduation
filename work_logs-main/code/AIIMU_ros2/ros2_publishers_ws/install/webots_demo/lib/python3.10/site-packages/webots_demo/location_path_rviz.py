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
        self.publisher_ = self.create_publisher(Path, '/path', 10)
        # 创建定时器，周期性地发布路径
        self.timer = self.create_timer(0.00001, self.publish_path)

        self.path = Path()
        self.path.header.frame_id = 'map'  # 你可以选择其他坐标系，如 'odom'

        self.positions = self.load_positions("/home/dsh/Documents/work_logs/code/AIIMU_ros2/ai-imu-dr2/results/imu_data_positions.csv")  # 从文件加载位置或其他方式

        self.index = 0  # 用于遍历真实位置数据



    def load_positions(self,file_path):
        positions = []
        # 打开 CSV 文件并读取数据
        with open(file_path, mode='r', newline='') as file:
            reader = csv.reader(file)
            
            # 跳过标题行（假设第一行是列名）
            next(reader)

            # 读取每一行数据并转换为 float 类型的元组 (x, y, z)
            for row in reader:
                if row:  # 确保行不为空
                    x, y, z = map(float, row)  # 将每一列转换为浮动数
                    positions.append((x, y, z))  # 将位置添加到列表中

        return positions


    def publish_path(self):
        if self.index < len(self.positions):
            position = self.positions[self.index]

            # 创建 PoseStamped 消息
            pose_stamped = PoseStamped()
            pose_stamped.header.stamp = self.get_clock().now().to_msg()
            pose_stamped.pose.position.x = position[0]
            pose_stamped.pose.position.y = position[1]
            pose_stamped.pose.position.z = position[2]
            
            # 将 PoseStamped 加入 Path 消息中
            self.path.poses.append(pose_stamped)

            # 增加索引，继续发布下一个位置
            self.index += 1

            # 发布路径
            self.publisher_.publish(self.path)

            self.get_logger().info(f'{self.index}: Publishing position {position}')

def main(args=None):
    rclpy.init(args=args)
    node = PathPublisher()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
