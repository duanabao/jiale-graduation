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
        initialized_anchor = false;
        if_nav_uwb = false;
        // 声明参数文件路径
        std::string config_file;
        this->declare_parameter("rosparam_yaml", "");
        this->get_parameter("rosparam_yaml", config_file);
        RCLCPP_INFO(this->get_logger(), "Loading parameters from: %s", config_file.c_str());

        // 读取参数
        readParamsInterface();

        //订阅启动时间话题
        sub_start = this->create_subscription<std_msgs::msg::Int64>(
        "/start_time", 1000, std::bind(&EstimationInterface::startCallBack, this, std::placeholders::_1));

        // 订阅 IMU 数据,发布
        std::string imu_type = this->declare_parameter<std::string>("topic_imu", "/waveshare_sense_hat_b"); // 读取IMU话题类型
        sub_imu = this->create_subscription<sensor_msgs::msg::Imu>(
            imu_type, 400, std::bind(&EstimationInterface::getImuCallback, this, std::placeholders::_1));

        pub_imu = this->create_publisher<sensor_msgs::msg::Imu>("/imu_ds", 400);

        // 订阅 UWB 数据
        std::string uwb_type = this->declare_parameter<std::string>("topic_uwb", "/rtls_flares");// 读取UWB话题类型
        if (uwb_type == "/tdoa_data") {
            sub_uwb = this->create_subscription<cf_msgs::msg::Tdoa>(
                uwb_type, 400, std::bind(&EstimationInterface::getTdoaUTILCallback, this, std::placeholders::_1));
            pub_uwb = this->create_publisher<cf_msgs::msg::Tdoa>("/tdoa_ds", 400);
        } else if (uwb_type == "/rtls_flares") {
            sub_uwb = this->create_subscription<isas_msgs::msg::RTLSStick>(
                uwb_type, 400, std::bind(&EstimationInterface::getToaISASCallback, this, std::placeholders::_1));
            pub_uwb = this->create_publisher<isas_msgs::msg::RTLSStick>("/toa_ds", 400);
        } else {
            RCLCPP_ERROR(this->get_logger(), "Wrong UWB format!");
        }

        // 订阅 Anchor 数据 
        std::string anchor_type = this->declare_parameter<std::string>("topic_anchor_list", "/anchor_list");
        if (!if_tdoa && anchor_type == "/anchor_list") {
            sub_anchor = this->create_subscription<isas_msgs::msg::Anchorlist>(
                anchor_type, 400, std::bind(&EstimationInterface::getAnchorListFromISASCallback, this, std::placeholders::_1));
        } else {
            RCLCPP_ERROR(this->get_logger(), "Anchor list not available!");
        }

        // 发布 Anchor 可视化数据
        anchor_pos_pub = this->create_publisher<sensor_msgs::msg::PointCloud>("/visualization_anchor", 1000);
        anchor_pub = this->create_publisher<isas_msgs::msg::Anchorlist>("/anchor_list", 1000);

        // 定时器
        timer_anchor = this->create_wall_timer(
            std::chrono::milliseconds(10), std::bind(&EstimationInterface::publishAnchor, this));

        // 订阅 Ground Truth 数据
        std::string gt_type = this->declare_parameter<std::string>("topic_ground_truth", "/vive/transform/tracker_1_ref");
        if (gt_type == "/vive/transform/tracker_1_ref") {
            sub_gt = this->create_subscription<geometry_msgs::msg::TransformStamped>(
                gt_type, 1000, std::bind(&EstimationInterface::getGtFromISASCallback, this, std::placeholders::_1));
        } else if (gt_type == "/pose_data") {
            sub_gt = this->create_subscription<geometry_msgs::msg::PoseWithCovarianceStamped>(
                gt_type, 1000, std::bind(&EstimationInterface::getGtFromUTILCallback, this, std::placeholders::_1));
        }

        // 其他订阅和发布
        int control_point_fps = this->declare_parameter<int>("control_point_fps", 10);// 10 读取控制点帧率
        dt_ns = 1e9 / control_point_fps; // 计算时间间隔（纳秒）
        sub_calib = this->create_subscription<sfuise_msgs::msg::Calib>(
            "/sys_calib", 100, std::bind(&EstimationInterface::getCalibCallback, this, std::placeholders::_1));// 订阅系统标定数据
        sub_est = this->create_subscription<sfuise_msgs::msg::Estimate>(
            "/est_window", 100, std::bind(&EstimationInterface::getEstCallback, this, std::placeholders::_1));// 订阅估计窗口数据

        pub_opt_old = this->create_publisher<nav_msgs::msg::Path>("/bspline_optimization_old", 1000);// 发布旧的B样条优化路径
        pub_opt_window = this->create_publisher<nav_msgs::msg::Path>("/bspline_optimization_window", 1000);// 发布当前B样条优化窗口
        opt_old_path.header.frame_id = "map";// 设置旧路径的坐标系为地图

        pub_opt_pose = this->create_publisher<visualization_msgs::msg::Marker>("/opt_pose", 1000);// 发布优化位姿的可视化标记
        opt_pose_vis.setColor(85.0 / 255.0, 164.0 / 255.0, 104.0 / 255.0); // 设置优化位姿可视化的颜色

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

    // ROS 2 定时器
    rclcpp::TimerBase::SharedPtr timer_anchor; 

    // ROS 2 订阅者
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr sub_imu; 
    rclcpp::SubscriptionBase::SharedPtr sub_uwb;
    rclcpp::Subscription<isas_msgs::msg::Anchorlist>::SharedPtr sub_anchor; 
    rclcpp::SubscriptionBase::SharedPtr sub_gt; 
    rclcpp::Subscription<sfuise_msgs::msg::Calib>::SharedPtr sub_calib; 
    rclcpp::Subscription<sfuise_msgs::msg::Estimate>::SharedPtr sub_est; 
    rclcpp::Subscription<std_msgs::msg::Int64>::SharedPtr sub_start; 

    // ROS 2 发布者
    rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr pub_imu; 
    rclcpp::PublisherBase::SharedPtr pub_uwb;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud>::SharedPtr anchor_pos_pub; 
    rclcpp::Publisher<isas_msgs::msg::Anchorlist>::SharedPtr anchor_pub; 
    rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr pub_opt_old; 
    rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr pub_opt_window; 
    rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr pub_opt_pose; 

    // 初始化路径消息
    nav_msgs::msg::Path opt_old_path; 
    PoseVisualization opt_pose_vis; 


   
    void readParamsInterface() { 
        // 读取参数
        if_tdoa = this->declare_parameter<bool>("if_tdoa", false); // false
        imu_sample_coeff = this->declare_parameter<double>("imu_sample_coeff", 1.0); // 1
        uwb_sample_coeff = this->declare_parameter<double>("uwb_sample_coeff", 1.0); // 1
        imu_frequency = this->declare_parameter<double>("imu_frequency", 84.0); // 84
        uwb_frequency = this->declare_parameter<double>("uwb_frequency", 16.0); // 16
        gyro_unit = this->declare_parameter<bool>("gyro_unit", false); // false
        acc_ratio = this->declare_parameter<bool>("acc_ratio", false); // false

        // 错误检查
        if (uwb_sample_coeff == 0) {
            RCLCPP_ERROR(this->get_logger(), "Parameter 'uwb_sample_coeff' cannot be 0!");
            rclcpp::shutdown();
            return;
        }

        // 如果启用TDOA，则读取锚点路径并加载锚点列表
        if (if_tdoa) {
            std::string anchor_path = this->declare_parameter<std::string>("anchor_path", "");
            getAnchorListFromUTIL(anchor_path);
        }
    }

    void getEstCallback(const sfuise_msgs::msg::Estimate::SharedPtr est_msg) 
    {
        sfuise_msgs::msg::Spline spline_msg = est_msg->spline; // 获取样条消息
        SplineState spline_w; // 创建样条状态对象
        spline_w.init(spline_msg.dt, 0, spline_msg.start_t, spline_msg.start_idx); // 初始化样条状态

        // 遍历样条节点
        for (const auto knot : spline_msg.knots) {
            Eigen::Vector3d pos(knot.position.x, knot.position.y, knot.position.z); // 获取位置
            Eigen::Quaterniond quat(knot.orientation.w, knot.orientation.x, knot.orientation.y, knot.orientation.z); // 获取方向
            Eigen::Matrix<double, 6, 1> bias; // 创建偏置矩阵
            bias << knot.bias_acc.x, knot.bias_acc.y, knot.bias_acc.z, // 设置加速度偏置
                    knot.bias_gyro.x, knot.bias_gyro.y, knot.bias_gyro.z; // 设置陀螺仪偏置
            spline_w.addOneStateKnot(quat, pos, bias); // 添加样条节点
        }

        // 遍历空闲节点
        for (int i = 0; i < 3; i++) {
            sfuise_msgs::msg::Knot idle = spline_msg.idles[i]; // 获取空闲节点
            Eigen::Vector3d t_idle(idle.position.x, idle.position.y, idle.position.z); // 获取空闲节点位置
            Eigen::Quaterniond q_idle(idle.orientation.w, idle.orientation.x, idle.orientation.y, idle.orientation.z); // 获取空闲节点方向
            Eigen::Matrix<double, 6, 1> b_idle; // 创建空闲节点偏置矩阵
            b_idle << idle.bias_acc.x, idle.bias_acc.y, idle.bias_acc.z, idle.bias_gyro.x, idle.bias_gyro.y, idle.bias_gyro.z; // 设置偏置
            spline_w.setIdles(i, t_idle, q_idle, b_idle); // 设置空闲节点
        }

        spline_global.updateKnots(&spline_w); // 更新全局样条节点
        // std::cout << "spline_global_numknots:" << spline_global.numKnots() << std::endl;

        // 如果启用导航UWB，则发布优化
        if (if_nav_uwb) {
            // std::cout << "true_uwb" << std::endl;
            pubOpt(spline_w, !est_msg->if_full_window.data);
        }

        average_runtime = est_msg->runtime.data; // 更新平均运行时间
    }

    void pubOpt(SplineState& spline_local, const bool if_window_full) 
    {
        int64_t min_t = spline_local.minTimeNs(); // 获取样条最小时间
        int64_t max_t = spline_local.maxTimeNs(); // 获取样条最大时间
        static int cnt = 0; // 计数器

        if (!if_window_full) { // 如果滑动窗口满了
            // 将时间戳小于当前窗口最小时间的数据点移动到历史数据中
            for (const auto& pose_data : opt_window) {
                if (pose_data.time_ns < min_t) {
                    opt_old.push_back(pose_data); // 将数据点添加到历史数据队列
                    opt_old_path.poses.push_back(CommonUtils::pose2msg(pose_data.time_ns, pose_data.pos, pose_data.orient)); // 将位姿转换为消息并添加到历史路径
                }
            }
        } else {
            cnt = 0; // 当窗口满时重置计数器
        }

        opt_window.clear(); // 清空优化窗口
        nav_msgs::msg::Path opt_window_path; // 创建优化窗口路径
        opt_window_path.header.frame_id = "map"; // 设置坐标系
        opt_window_path.header.stamp = rclcpp::Clock().now(); // 设置时间戳

        // RCLCPP_INFO_STREAM(this->get_logger(), "\n=== 优化窗口路径消息内容 ===");
        for (size_t i = cnt; i < gt.size(); i++) { // 遍历地面真实数据
            int64_t t_ns = gt.at(i).time_ns; // 获取时间戳
            // 只处理时间窗口内的数据点
            if (t_ns < min_t) { // 如果时间小于最小时间
                cnt = i; // 更新计数器
                continue;
            } else if (t_ns > max_t) { // 如果时间大于最大时间
                break;
            }

            PoseData pose_tf = getPoseInUWB(spline_local, t_ns); // 获取UWB中的位姿
            // RCLCPP_INFO_STREAM(this->get_logger(), "pose_tf position: "
            //     << "time_ns=" << t_ns 
            //     << ", x=" << pose_tf.pos.x()
            //     << ", y=" << pose_tf.pos.y()
            //     << ", z=" << pose_tf.pos.z());
            opt_window.push_back(pose_tf); // 添加到优化窗口
            opt_window_path.poses.push_back(CommonUtils::pose2msg(t_ns, pose_tf.pos, pose_tf.orient)); // 添加到优化窗口路径
            
        }

        pub_opt_old->publish(opt_old_path); // 发布旧优化路径
        pub_opt_window->publish(opt_window_path); // 发布当前优化窗口路径
        // 输出发布的pub_opt_window的消息内容
        // RCLCPP_INFO_STREAM(this->get_logger(), "帧ID: " << opt_window_path.header.frame_id);
        // RCLCPP_INFO_STREAM(this->get_logger(), "时间戳: " << opt_window_path.header.stamp.nanosec);//当前时间的时间戳
        // RCLCPP_INFO_STREAM(this->get_logger(), "路径点数量: " << opt_window_path.poses.size());
        // RCLCPP_INFO_STREAM(this->get_logger(), "\n==========================");
        

        if (!opt_window.empty()) { 
            opt_pose_vis.pubPose(opt_window.back().pos, opt_window.back().orient, pub_opt_pose, opt_window_path.header); // 发布优化位姿可视化
        }
    }

    void getImuCallback(const sensor_msgs::msg::Imu::SharedPtr imu_msg) 
    {
        static int64_t last_imu = 0; // 上一个IMU时间戳
        int64_t t_ns = rclcpp::Time(imu_msg->header.stamp).nanoseconds(); // 获取当前时间戳
        // std::cout << "--------------->imu_time:" << t_ns << std::endl;

        if (sampleData(t_ns, last_imu, imu_sample_coeff, imu_frequency)) { // 检查是否需要采样（由原始IMU-->IMU_DS）
            Eigen::Vector3d acc(imu_msg->linear_acceleration.x, imu_msg->linear_acceleration.y, imu_msg->linear_acceleration.z); // 获取加速度
            if (acc_ratio) acc *= 9.81; // 如果启用加速度比，转换为米每二次方秒

            Eigen::Vector3d gyro(imu_msg->angular_velocity.x, imu_msg->angular_velocity.y, imu_msg->angular_velocity.z); // 获取陀螺仪数据
            if (gyro_unit) gyro *= M_PI / 180.0; // 如果启用陀螺仪单位，转换为弧度

            last_imu = t_ns; // 更新上一个IMU时间戳

            // 创建 IMU 数据消息
            auto imu_ds_msg = std::make_shared<sensor_msgs::msg::Imu>(); 
            imu_ds_msg->header = imu_msg->header; // 复制消息头
            imu_ds_msg->linear_acceleration.x = acc[0]; // 设置线性加速度
            imu_ds_msg->linear_acceleration.y = acc[1];
            imu_ds_msg->linear_acceleration.z = acc[2];
            imu_ds_msg->angular_velocity.x = gyro[0]; // 设置角速度
            imu_ds_msg->angular_velocity.y = gyro[1];
            imu_ds_msg->angular_velocity.z = gyro[2];

            // 发布 IMU 数据
            pub_imu->publish(*imu_ds_msg);
        }
    }

    void getCalibCallback(const sfuise_msgs::msg::Calib::SharedPtr calib_msg) // 标定回调函数
    {
        RCLCPP_INFO_STREAM(this->get_logger(), "sys_calib: @@@@@@@@ ");
        if_nav_uwb = true; // 启用导航UWB
        calib_param.q_nav_uwb = Eigen::Quaterniond(calib_msg->q_nav_uwb.w, calib_msg->q_nav_uwb.x, calib_msg->q_nav_uwb.y, calib_msg->q_nav_uwb.z); // 设置四元数
        calib_param.t_nav_uwb = Eigen::Vector3d(calib_msg->t_nav_uwb.x, calib_msg->t_nav_uwb.y, calib_msg->t_nav_uwb.z); // 设置平移向量
        calib_param.gravity = Eigen::Vector3d(calib_msg->gravity.x, calib_msg->gravity.y, calib_msg->gravity.z); // 设置重力向量
        calib_param.offset = Eigen::Vector3d(calib_msg->t_tag_body_set.x, calib_msg->t_tag_body_set.y, calib_msg->t_tag_body_set.z); // 设置标签身体的偏移
    }

    void getToaISASCallback(const isas_msgs::msg::RTLSStick::SharedPtr uwb_msg) // RTLS Stick回调
    {
        // RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: 11111111111111 ");
        static int64_t last_uwb = 0; // 上一个UWB时间戳
        int64_t t_ns = rclcpp::Time(uwb_msg->header.stamp).nanoseconds(); // 获取当前时间戳

        if (sampleData(t_ns, last_uwb, uwb_sample_coeff, uwb_frequency)) { // 检查是否需要采样
            for (const auto& rg : uwb_msg->ranges) { 
                if (rg.ra == 0) continue; // 过滤无效数据
            }
            // 动态转换为具体类型指针
            auto pub_rtls = dynamic_cast<rclcpp::Publisher<isas_msgs::msg::RTLSStick>*>(pub_uwb.get());
            if (pub_rtls) {
                // RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: 333333333333333 ");
                pub_rtls->publish(*uwb_msg);
            } else {
                RCLCPP_ERROR(get_logger(), "pub_uwb is not RTLSStick publisher!");
            }
            last_uwb = t_ns; // 更新时间戳
        }
    }

    void getTdoaUTILCallback(const cf_msgs::msg::Tdoa::SharedPtr msg) // TDOA回调
    {
        static int64_t last_uwb = 0; // 上一个UWB时间戳
        int64_t t_ns = rclcpp::Time(msg->header.stamp).nanoseconds(); // 获取当前时间戳

        if (sampleData(t_ns, last_uwb, uwb_sample_coeff, uwb_frequency)) { // 采样检查
            int idA = msg->id_a; // 获取ID A
            int idB = msg->id_b; // 获取ID B
            auto pub_tdoa = dynamic_cast<rclcpp::Publisher<cf_msgs::msg::Tdoa>*>(pub_uwb.get());
            if (pub_tdoa) {
                pub_tdoa->publish(*msg);
            } else {
                RCLCPP_ERROR(get_logger(), "pub_uwb is not TDOA publisher!");
            }
            last_uwb = t_ns; // 更新时间戳
        }
    }

    void getGtFromISASCallback(const geometry_msgs::msg::TransformStamped::SharedPtr gt_msg) // 从ISAS获取地面真实数据
    {
        // RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: 222222222222222 ");
        Eigen::Quaterniond q(gt_msg->transform.rotation.w, gt_msg->transform.rotation.x,
                             gt_msg->transform.rotation.y, gt_msg->transform.rotation.z); // 获取四元数
        Eigen::Vector3d pos(gt_msg->transform.translation.x, gt_msg->transform.translation.y, gt_msg->transform.translation.z); // 获取位置

        PoseData pose(rclcpp::Time(gt_msg->header.stamp).nanoseconds(), q, pos); // 创建位姿数据
        gt.push_back(pose); // 添加到地面真实数据
        // std::cout << "gt:" <<gt.back().time_ns << std::endl;
    }

    void getGtFromUTILCallback(const geometry_msgs::msg::PoseWithCovarianceStamped::SharedPtr gt_msg) // 从UTIL获取地面真实数据
    {
        Eigen::Quaterniond q(gt_msg->pose.pose.orientation.w, gt_msg->pose.pose.orientation.x,
                             gt_msg->pose.pose.orientation.y, gt_msg->pose.pose.orientation.z); // 获取四元数
        Eigen::Vector3d pos(gt_msg->pose.pose.position.x, gt_msg->pose.pose.position.y, gt_msg->pose.pose.position.z); // 获取位置

        PoseData pose(rclcpp::Time(gt_msg->header.stamp).nanoseconds(), q, pos); // 创建位姿数据
        gt.push_back(pose); // 添加到地面真实数据
    }

    void getAnchorListFromISASCallback(const isas_msgs::msg::Anchorlist::SharedPtr anchor_msg) // 从ISAS获取锚点列表
    {
        // RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: 44444444444444 ");
        if (initialized_anchor) return; // 如果已初始化，直接返回

        int num_sum = 20; // 设定锚点累积次数
        static int cnt = 0; // 计数器

        for (const auto& anchor : anchor_msg->anchor) { // 遍历锚点
            // RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: 44444444444444 ");
            Eigen::Vector3d anchor_pos(anchor.position.x, anchor.position.y, anchor.position.z); // 获取锚点位置
            uint16_t anchor_id = anchor.id; // 获取锚点ID

            if (cnt == 0) { 
                anchor_list[anchor_id] = anchor_pos; // 第一次直接赋值
            } else { 
                Eigen::Vector3d ave_pos = anchor_list[anchor_id]; // 计算平均位置
                anchor_list[anchor_id] = (ave_pos * cnt + anchor_pos) / (cnt + 1); 
                anchor_pos = anchor_list[anchor_id]; // 更新锚点位置
            }
        }

        cnt++; // 计数器增加
        if (cnt >= num_sum) { // 当达到设定次数
            initialized_anchor = true; // 标记初始化完成
            publishAnchor(); // 发布锚点数据
        }
    }

    void getAnchorListFromUTIL(const std::string& anchor_path) // 从文件获取锚点列表的函数
    {
        std::ifstream infile(anchor_path); // 打开文件
        if (!infile) {
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Unable to open file: %s", anchor_path.c_str());
            return;
        }

        std::string line;
        while (std::getline(infile, line)) {
            std::istringstream iss(line);
            char comma, tmp, tmp2;
            int anchor_id;
            double x, y, z;
            iss >> tmp >> tmp >> anchor_id >> tmp >> tmp2 >> comma >> x >> comma >> y >> comma >> z;
            if (tmp2 == 'p') {
                anchor_list[anchor_id] = Eigen::Vector3d(x, y, z);
            }
        }
        infile.close();
        initialized_anchor = true;
    }

    bool sampleData(const int64_t t_ns, const int64_t last_t_ns, const double coeff, const double frequency) const // 数据采样函数
    {
        if (coeff == 0)  return false; // 如果系数为0，返回false
        int64_t dt = 1e9 / (coeff * frequency); // 计算采样间隔
        if (coeff == 1) { // 如果系数为1
            return true; // 直接返回true
        } else if (t_ns - last_t_ns > dt - 1e5) { // 如果时间差大于采样间隔
            return true; // 返回true
        } else {
            return false; // 否则返回false
        }
    }

    void publishAnchor() // 发布锚点的函数
    {
        if (!initialized_anchor) return; // 初始化没成功，则直接返回
        
        // RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: aaaaaaaaaaaaaaaaa ");
        auto anchor_list_msg = isas_msgs::msg::Anchorlist();
        for (auto it = anchor_list.begin(); it != anchor_list.end(); it++) { // 遍历锚点列表
            isas_msgs::msg::AnchorPosition anchor;
            Eigen::Vector3d pos = it->second; // 获取锚点位置
            anchor.position.x = pos[0];
            anchor.position.y = pos[1];
            anchor.position.z = pos[2];
            anchor.id = it->first; // 设置锚点ID
            anchor_list_msg.anchor.push_back(anchor);
        }
        anchor_pub->publish(anchor_list_msg);

        auto anchors = sensor_msgs::msg::PointCloud();
        anchors.header.frame_id = "map";
        anchors.header.stamp = rclcpp::Clock().now();

        for (auto it = anchor_list.begin(); it != anchor_list.end(); it++) { // 遍历锚点列表
            Eigen::Matrix<double, 3, 1> pos = it->second; // 获取锚点位置
            geometry_msgs::msg::Point32 p;
            p.x = pos[0];
            p.y = pos[1];
            p.z = pos[2];
            anchors.points.push_back(p);
        }
        anchor_pos_pub->publish(anchors);
    }

    void startCallBack(const std_msgs::msg::Int64::SharedPtr start_time_msg) // 启动回调函数
    {
        int64_t bag_start_time = start_time_msg->data;
        spline_global.init(dt_ns, 0, bag_start_time);
    }

    PoseData getPoseInUWB(SplineState& spline, int64_t t_ns) 
    {
        // // 1. 输出标定参数
        // RCLCPP_INFO_STREAM(this->get_logger(), "\n=== 标定参数调试信息 ===");
        
        // // 输出q_nav_uwb四元数
        // RCLCPP_INFO_STREAM(this->get_logger(), "q_nav_uwb: w=" << calib_param.q_nav_uwb.w() 
        //     << ", x=" << calib_param.q_nav_uwb.x()
        //     << ", y=" << calib_param.q_nav_uwb.y()
        //     << ", z=" << calib_param.q_nav_uwb.z());
        
        // // 输出t_nav_uwb平移向量
        // RCLCPP_INFO_STREAM(this->get_logger(), "t_nav_uwb: x=" << calib_param.t_nav_uwb.x()
        //     << ", y=" << calib_param.t_nav_uwb.y()
        //     << ", z=" << calib_param.t_nav_uwb.z());
        
        // // 输出offset偏移量
        // RCLCPP_INFO_STREAM(this->get_logger(), "offset: x=" << calib_param.offset.x()
        //     << ", y=" << calib_param.offset.y()
        //     << ", z=" << calib_param.offset.z());

        // 2. 获取并输出插值数据
        Eigen::Quaterniond orient_interp;
        Eigen::Vector3d t_interp = spline.itpPosition(t_ns);
        spline.itpQuaternion(t_ns, &orient_interp);
        
        // RCLCPP_INFO_STREAM(this->get_logger(), "\n=== 插值数据 ===");
        // RCLCPP_INFO_STREAM(this->get_logger(), "t_interp: x=" << t_interp.x()
        //     << ", y=" << t_interp.y()
        //     << ", z=" << t_interp.z());
        // RCLCPP_INFO_STREAM(this->get_logger(), "orient_interp: w=" << orient_interp.w()
        //     << ", x=" << orient_interp.x()
        //     << ", y=" << orient_interp.y()
        //     << ", z=" << orient_interp.z());

        // 3. 计算中间结果并输出
        Eigen::Vector3d rotated_offset = orient_interp * calib_param.offset;
        // RCLCPP_INFO_STREAM(this->get_logger(), "\n=== 中间计算结果 ===");
        // RCLCPP_INFO_STREAM(this->get_logger(), "rotated_offset: x=" << rotated_offset.x()
        //     << ", y=" << rotated_offset.y()
        //     << ", z=" << rotated_offset.z());

        Eigen::Vector3d pos_with_offset = rotated_offset + t_interp;
        // RCLCPP_INFO_STREAM(this->get_logger(), "pos_with_offset: x=" << pos_with_offset.x()
        //     << ", y=" << pos_with_offset.y()
        //     << ", z=" << pos_with_offset.z());

        // 4. 计算最终结果
        Eigen::Quaterniond q = calib_param.q_nav_uwb * orient_interp;
        Eigen::Vector3d t = calib_param.q_nav_uwb * pos_with_offset + calib_param.t_nav_uwb;

        // // 输出最终结果
        // RCLCPP_INFO_STREAM(this->get_logger(), "\n=== 最终结果 ===");
        // RCLCPP_INFO_STREAM(this->get_logger(), "final_position: x=" << t.x()
        //     << ", y=" << t.y()
        //     << ", z=" << t.z());
        // RCLCPP_INFO_STREAM(this->get_logger(), "final_orientation: w=" << q.w()
        //     << ", x=" << q.x()
        //     << ", y=" << q.y()
        //     << ", z=" << q.z());

        // // 5. 添加简单的数值范围检查
        // const double MAX_POSITION = 1000.0; // 根据实际情况调整阈值
        // if (t.norm() > MAX_POSITION) {
        //     RCLCPP_WARN_STREAM(this->get_logger(), "警告：位置值超出预期范围！ norm=" << t.norm());
        // }

        return PoseData(t_ns, q, t);
    }


};


int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<EstimationInterface>();
    RCLCPP_INFO(node->get_logger(), "\033[1;32m---->\033[0m Starting EstimationInterface.");

    // rclcpp::spin(node);
    rclcpp::Rate rate(1000); 
    rclcpp::executors::SingleThreadedExecutor executor;
    executor.add_node(node);

    while (rclcpp::ok()) {
        executor.spin_some(); // 处理回调
        // 其他任务（如发布消息、控制逻辑）
        // RCLCPP_INFO(node->get_logger(), "Running EstimationInterface loop...");
        rate.sleep();
    }

    rclcpp::shutdown();
    return 0;
}
