#include <webots/Robot.hpp>
#include <webots/Node.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <rclcpp/rclcpp.hpp>

using namespace webots;
using namespace std;

class EpuckController : public rclcpp::Node {
public:
    EpuckController() : Node("epuck_controller") {
        // 初始化 Webots 机器人
        robot = new Robot();
        epuck_node = robot->getSelf();

        // 设置 ROS 2 订阅器，订阅机器人的位置
        subscription_ = this->create_subscription<geometry_msgs::msg::Pose>(
            "/epuck/pose", 10, std::bind(&EpuckController::pose_callback, this, std::placeholders::_1));
    }

    void pose_callback(const geometry_msgs::msg::Pose::SharedPtr msg) {
        // 从 ROS 2 消息中获取目标位置并设置 Webots 中机器人的位置
        double x = msg->position.x;
        double y = msg->position.y;
        double z = msg->position.z;
        epuck_node->getField("translation")->setSFVec3f({x, y, z});
        RCLCPP_INFO(this->get_logger(), "Setting position to: x=%f, y=%f, z=%f", x, y, z);
    }

    void run() {
        while (rclcpp::ok()) {
            rclcpp::spin_some(this->shared_from_this());
            robot->step(32);
        }
    }

private:
    rclcpp::Subscription<geometry_msgs::msg::Pose>::SharedPtr subscription_;
    Robot *robot;
    Node *epuck_node;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<EpuckController>());
    rclcpp::shutdown();
    return 0;
}
