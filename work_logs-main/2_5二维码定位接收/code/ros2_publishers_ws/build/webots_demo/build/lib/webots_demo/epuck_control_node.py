import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Pose, PoseStamped

class EpuckControlNode(Node):
    def __init__(self):
        super().__init__('epuck_control_node')

        # 创建发布器来发布目标位置
        self.pose_publisher = self.create_publisher(Pose, '/epuck/pose', 10)

        # 创建二维码位置的订阅者
        self.qr_code_subscriber = self.create_subscription(PoseStamped, '/qr_code_pose', self.move_to_qr_code_pose, 1)

        # 设置定时器定期发布位置
        self.timer = self.create_timer(1.0, self.publish_pose)  # 每秒发布一次

        self.current_pose = Pose()  # 当前机器人的位置
        self.current_pose.position.x = 0.2  # 初始化 x 坐标
        self.current_pose.position.y = 0.0  # 初始化 y 坐标

    def publish_pose(self):
        # 创建 Pose 消息并设置目标位置
        pose_msg = Pose()
        pose_msg.position.x = self.current_pose.position.x  # 使用当前机器人的位置
        pose_msg.position.y = self.current_pose.position.y
        pose_msg.position.z = 0.0  # 设置目标位置的 z 坐标（例如，设置为0.0表示地面）

        pose_msg.orientation.x = 0.0  # 无旋转
        pose_msg.orientation.y = 0.0
        pose_msg.orientation.z = 0.0
        pose_msg.orientation.w = 1.0

        # 发布 Pose 消息
        self.pose_publisher.publish(pose_msg)
        self.get_logger().info(f'Publishing position: ({pose_msg.position.x}, {pose_msg.position.y}, {pose_msg.position.z})')

    def move_to_qr_code_pose(self, msg):
        target_x = msg.pose.position.x  # 获取目标位置的 x 坐标
        target_y = msg.pose.position.y  # 获取目标位置的 y 坐标
        self.get_logger().info(f'Moving to QR code position: x={target_x}, y={target_y}')  # 日志记录目标位置


def main(args=None):
    rclpy.init(args=args)

    # 创建并启动 ROS 2 节点
    epuck_node = EpuckControlNode()
    rclpy.spin(epuck_node)

    # 清理并关闭节点
    epuck_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main() 