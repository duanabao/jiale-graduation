import rclpy
from rclpy.node import Node
from sensor_msgs.msg import LaserScan
from geometry_msgs.msg import Twist

class EpuckController(Node):

    def __init__(self):
        super().__init__('epuck_controller')
        self.publisher_ = self.create_publisher(Twist, 'cmd_vel', 10)
        self.subscription = self.create_subscription(
            LaserScan,
            'laser/scan',
            self.listener_callback,
            10
        )
        self.get_logger().info("E-puck Controller Started")

    def listener_callback(self, msg):
        twist = Twist()
        # 例如：基于激光扫描数据进行简单的障碍物避让
        if min(msg.ranges) < 1.0:
            twist.linear.x = 0.0
            twist.angular.z = 0.5
        else:
            twist.linear.x = 0.1
            twist.angular.z = 0.0
        self.publisher_.publish(twist)

def main(args=None):
    rclpy.init(args=args)
    epuck_controller = EpuckController()
    rclpy.spin(epuck_controller)
    epuck_controller.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
