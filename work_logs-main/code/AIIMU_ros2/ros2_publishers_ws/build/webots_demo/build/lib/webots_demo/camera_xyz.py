import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from nav_msgs.msg import Odometry
from cv_bridge import CvBridge
from geometry_msgs.msg import PoseStamped
from tf2_ros import Buffer, TransformListener #坐标变换

class EPuckCameraAndPosePublisher(Node):
    def __init__(self):
        super().__init__('epuck_camera_and_pose_publisher')

        # 创建发布器
        self.image_publisher = self.create_publisher(Image, '/camera_image', 10)
        self.pose_publisher = self.create_publisher(PoseStamped, '/camera_pose', 10)
        
        # 创建 TF2 缓冲区和监听器
        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)

        # 创建 CvBridge，用于将 OpenCV 图像转换为 ROS 消息格式
        self.bridge = CvBridge()

        # 订阅 e-puck 相机话题
        self.create_subscription(
            Image,
            '/camera/image_color',  # 订阅 e-puck 相机图像数据
            self.camera_callback,
            10
        )


        # 定时器：周期性地发布图像和位置信息
        self.timer = self.create_timer(0.1, self.publish_pose)  # 每 100ms 发布一次

        # 用于存储 e-puck 的相机图像和位姿信息
        self.latest_image = None


        self.get_logger().info("e-puck camera and pose publisher node has been started.")

    def camera_callback(self, msg):
        # 将接收到的图像消息转换为 OpenCV 图像
        self.latest_image = msg



    def publish_pose(self):
        # 发布图像
        if self.latest_image is not None:
            self.image_publisher.publish(self.latest_image)

        # 获取并发布相机在 odom 坐标系下的位姿
        try:
            # 获取 odom -> camera_link 的变换
            transform = self.tf_buffer.lookup_transform(
                'odom',        # 源坐标系
                'camera', # 目标坐标系
                rclpy.time.Time()  # 使用最新变换
            )

            # 创建并发布 PoseStamped 消息
            pose_msg = PoseStamped()
            pose_msg.header.stamp = self.get_clock().now().to_msg()
            pose_msg.header.frame_id = 'odom'
            pose_msg.pose.position.x = transform.transform.translation.x
            pose_msg.pose.position.y = transform.transform.translation.y
            pose_msg.pose.position.z = transform.transform.translation.z
            pose_msg.pose.orientation = transform.transform.rotation

            self.pose_publisher.publish(pose_msg)

            self.get_logger().info(
                f"Published pose: x={pose_msg.pose.position.x}, y={pose_msg.pose.position.y}, z={pose_msg.pose.position.z}"
            )
        except Exception as e:
            self.get_logger().error(f"Failed to get transform: {str(e)}")


def main(args=None):
    rclpy.init(args=args)

    # 创建节点
    node = EPuckCameraAndPosePublisher()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        # 销毁节点并关闭 rclpy
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()

###
# 节点说明
# 订阅话题

# 订阅 /camera/image_color（Webots e-puck 的相机画面）。
# 使用 camera_callback 将图像保存。
# TF 获取变换

# 使用 tf2_ros.Buffer 和 tf2_ros.TransformListener 获取 odom -> camera_link 的变换。
# 发布话题

# 发布图像话题 /camera/image_raw。
# 发布相机位姿话题 /camera/pose。
