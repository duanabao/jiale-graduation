#include <rclcpp/rclcpp.hpp> // 引入ROS 2核心库
#include <fstream> // 引入文件流库
#include "../include/SplineState.h" // 引入自定义的SplineState类
#include "../include/utils/PoseVisualization.h" // 引入自定义的PoseVisualization类

// 传感器消息
#include "sensor_msgs/msg/imu.hpp"
#include "sensor_msgs/msg/point_cloud.hpp"

// 变换和位姿消息
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "geometry_msgs/msg/pose_with_covariance_stamped.hpp"

// 路径消息
#include "nav_msgs/msg/path.hpp"

// 自定义消息类型
#include "cf_msgs/msg/tdoa.hpp"
#include "isas_msgs/msg/rtls_range.hpp"
#include "isas_msgs/msg/rtls_stick.hpp"
#include "isas_msgs/msg/anchor_position.hpp"
#include "isas_msgs/msg/anchorlist.hpp"

// 其他消息
#include "sfuise_msgs/msg/spline.hpp"
#include "sfuise_msgs/msg/estimate.hpp"
#include "sfuise_msgs/msg/calib.hpp"
#include "std_msgs/msg/int64.hpp"
#include "std_msgs/msg/string.hpp"

class EstimationInterface : public rclcpp::Node {
public:
    EstimationInterface() : Node("EstimationInterface") {
        std::string imu_type = this->declare_parameter<std::string>("topic_imu", "/waveshare_sense_hat_b"); // 读取IMU话题类型
        sub_imu = this->create_subscription<sensor_msgs::msg::Imu>(
            imu_type, 400, std::bind(&EstimationInterface::getImuCallback, this, std::placeholders::_1));

        pub_imu = this->create_publisher<sensor_msgs::msg::Imu>("imu_ds", 400);


        RCLCPP_INFO(this->get_logger(), "EstimationInterface Initialized.");
    }

private:
    // ROS 2 成员变量定义
    int64_t dt_ns; 
    bool initialized_anchor; 
    bool if_tdoa; 
    bool if_nav_uwb; 
    CalibParam calib_param; 
    Eigen::aligned_vector<PoseData> gt; 
    Eigen::aligned_map<uint16_t, Eigen::Vector3d> anchor_list; 
    double imu_sample_coeff; 
    double uwb_sample_coeff; 
    double imu_frequency; 
    double uwb_frequency; 
    double average_runtime; 
    bool gyro_unit; 
    bool acc_ratio; 
    SplineState spline_global; 
    Eigen::aligned_vector<PoseData> opt_old; 
    Eigen::aligned_vector<PoseData> opt_window; 

    // // ROS 2 定时器
    rclcpp::TimerBase::SharedPtr timer_anchor; 

    // // ROS 2 订阅者
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr sub_imu; 
    rclcpp::SubscriptionBase::SharedPtr sub_uwb;
    rclcpp::Subscription<isas_msgs::msg::Anchorlist>::SharedPtr sub_anchor; 
    rclcpp::SubscriptionBase::SharedPtr sub_gt; 
    rclcpp::Subscription<sfuise_msgs::msg::Calib>::SharedPtr sub_calib; 
    rclcpp::Subscription<sfuise_msgs::msg::Estimate>::SharedPtr sub_est; 
    rclcpp::Subscription<std_msgs::msg::Int64>::SharedPtr sub_start; 

    // // ROS 2 发布者
    rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr pub_imu; 
    rclcpp::PublisherBase::SharedPtr pub_uwb;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud>::SharedPtr anchor_pos_pub; 
    rclcpp::Publisher<isas_msgs::msg::Anchorlist>::SharedPtr anchor_pub; 
    rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr pub_opt_old; 
    rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr pub_opt_window; 
    rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr pub_opt_pose;

    // 其他数据
    nav_msgs::msg::Path opt_old_path; 
    PoseVisualization opt_pose_vis; 

    void getImuCallback(const sensor_msgs::msg::Imu::SharedPtr imu_msg) 
    {
        RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: 111111111111111 ");
        auto imu_ds_msg = std::make_shared<sensor_msgs::msg::Imu>(); 
        imu_ds_msg->header = imu_msg->header; // 复制消息头
        imu_ds_msg->linear_acceleration.x = imu_msg->linear_acceleration.x;
        imu_ds_msg->linear_acceleration.y = imu_msg->linear_acceleration.y;
        imu_ds_msg->linear_acceleration.z = imu_msg->linear_acceleration.z;
        imu_ds_msg->angular_velocity.x = imu_msg->angular_velocity.x;
        imu_ds_msg->angular_velocity.y = imu_msg->angular_velocity.y;
        imu_ds_msg->angular_velocity.z = imu_msg->angular_velocity.z;
        pub_imu->publish(*imu_ds_msg);
    }


};



int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<EstimationInterface>();
    RCLCPP_INFO(node->get_logger(), "\033[1;32m---->\033[0m Starting EstimationInterface.");

    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}
