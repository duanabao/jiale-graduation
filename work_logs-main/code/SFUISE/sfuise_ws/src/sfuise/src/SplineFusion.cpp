#include <rclcpp/rclcpp.hpp> // 引入ROS 2核心库
#include "../include/Linearizer.h" // 引入自定义的Linearizer类
#include "../include/Accumulator.h" // 引入自定义的Accumulator类
#include "../include/utils/tic_toc.h" // 引入自定义的tic_toc工具类

// 标准消息类型
#include "std_msgs/msg/int64.hpp"

// 传感器消息类型
#include "sensor_msgs/msg/imu.hpp"
#include "sensor_msgs/msg/point_cloud.hpp"

// 自定义消息类型
#include "cf_msgs/msg/tdoa.hpp"
#include "isas_msgs/msg/anchorlist.hpp"
#include "isas_msgs/msg/rtls_stick.hpp"
#include "sfuise_msgs/msg/calib.hpp"
#include "sfuise_msgs/msg/spline.hpp"
#include "sfuise_msgs/msg/estimate.hpp"


class SplineFusion : public rclcpp::Node {
public:
    SplineFusion(): Node("SplineFusion")  // 构造函数，接收ROS 2节点句柄
    {
        if_anchor_ini = false;  // 初始化锚点标志
        average_runtime = 0;  // 初始化平均运行时间
        window_count = 0;  // 初始化窗口计数
        // imu_count = 0;
        // uwb_count = 0;
        solver_flag = INITIAL;  // 初始化求解器标志
        readParameters();  // 读取参数

        // 订阅IMU和锚点数据
        sub_imu = this->create_subscription<sensor_msgs::msg::Imu>(
            "/imu_ds", 1000, std::bind(&SplineFusion::getImuCallback, this, std::placeholders::_1));
        
        sub_anchor = this->create_subscription<isas_msgs::msg::Anchorlist>(
            "/anchor_list", 1000, std::bind(&SplineFusion::getAnchorCallback, this, std::placeholders::_1));
        
        // 根据是否使用TDOA选择订阅的主题
        if (if_tdoa) {
            sub_uwb = this->create_subscription<cf_msgs::msg::Tdoa>(
                "/tdoa_ds", 1000, std::bind(&SplineFusion::getTdoaCallback, this, std::placeholders::_1));
        } else { //进入
            sub_uwb = this->create_subscription<isas_msgs::msg::RTLSStick>(
                "/toa_ds", 1000, std::bind(&SplineFusion::getToaCallback, this, std::placeholders::_1));
        }

        // 创建发布者
        pub_knots_active = this->create_publisher<sensor_msgs::msg::PointCloud>(
            "/active_control_points", 1000);
        
        pub_knots_inactive = this->create_publisher<sensor_msgs::msg::PointCloud>(
            "/inactive_control_points", 1000);
        
        pub_calib = this->create_publisher<sfuise_msgs::msg::Calib>(
            "/sys_calib", 100);

        pub_est = this->create_publisher<sfuise_msgs::msg::Estimate>(
            "/est_window", 1000);

        pub_start_time = this->create_publisher<std_msgs::msg::Int64>(
            "/start_time", 1000);
        // timer_ = this->create_wall_timer(
            // std::chrono::milliseconds(1000), std::bind(&SplineFusion::run, this));
        RCLCPP_INFO(this->get_logger(), "SplineFusion Initialized.");
    }

    void run()
    {
        // RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: 111111111111111 ");
        static int num_window = 0;  // 窗口计数
        rclcpp::Time t_window_start = this->get_clock()->now();  // 获取当前时间
        if((int)window_count > n_window_calib) {
            return;
        }
        if (initialization()) {  // 如果初始化成功
            displayControlPoints();  // 显示控制点
            optimization();  // 执行优化
            // RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: 111111111111111 ");
            double t_consum = (this->get_clock()->now() - t_window_start).seconds();  // 计算消耗时间
            average_runtime = (t_consum + double(num_window) * average_runtime) / double(num_window + 1);  // 更新平均运行时间
            num_window++;  // 增加窗口计数

            if ((int)window_count <= n_window_calib) {  // 如果窗口计数小于等于校准窗口数
                // RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: ssssssssssssssss ");
                sfuise_msgs::msg::Calib calib_msg;  // 创建校准消息
                // 设置校准参数
                calib_msg.q_nav_uwb.w = calib_param.q_nav_uwb.w();
                calib_msg.q_nav_uwb.x = calib_param.q_nav_uwb.x();
                calib_msg.q_nav_uwb.y = calib_param.q_nav_uwb.y();
                calib_msg.q_nav_uwb.z = calib_param.q_nav_uwb.z();
                calib_msg.t_nav_uwb.x = calib_param.t_nav_uwb[0];
                calib_msg.t_nav_uwb.y = calib_param.t_nav_uwb[1];
                calib_msg.t_nav_uwb.z = calib_param.t_nav_uwb[2];

                geometry_msgs::msg::Point offset_msg;  // 创建偏移消息
                offset_msg.x = calib_param.offset.x();
                offset_msg.y = calib_param.offset.y();
                offset_msg.z = calib_param.offset.z();
                calib_msg.t_tag_body_set = offset_msg;  // 设置标签体偏移

                pub_calib->publish(calib_msg);  // 发布校准消息
            }

            if (spline_local.numKnots() >= (size_t)window_size) {  // 如果样条节点数达到窗口大小
                window_count++;  // 增加窗口计数
                if (solver_flag == INITIAL) {  // 如果求解器标志为初始状态
                    solver_flag = FULLSIZE;  // 设置为全尺寸状态
                }
            }

            sfuise_msgs::msg::Spline spline_msg;  // 创建样条消息
            spline_local.getSplineMsg(spline_msg);  // 获取样条消息

            sfuise_msgs::msg::Estimate est_msg;  // 创建估计消息
            est_msg.spline = spline_msg;  // 设置样条
            est_msg.if_full_window.data = (solver_flag != INITIAL);  // 设置是否为全窗口
            est_msg.runtime.data = average_runtime;  // 设置运行时间

            pub_est->publish(est_msg);  // 发布估计消息
            displayControlPoints();  // 显示控制点

            if (solver_flag == FULLSIZE) {
                spline_local.removeOneOldState();  // 如果为全尺寸状态，移除一个旧状态
            }
            // 输出窗口大小、样条节点数、窗口计数和求解器标志的值
            RCLCPP_INFO_STREAM(this->get_logger(), "\n=== 窗口情况 ===");
            RCLCPP_INFO(this->get_logger(), "窗口大小(window_size): %d", window_size);
            RCLCPP_INFO(this->get_logger(), "样条节点数(spline_local.numKnots()): %zu", spline_local.numKnots());
            RCLCPP_INFO(this->get_logger(), "窗口计数(window_count): %zu", window_count);
            RCLCPP_INFO(this->get_logger(), "求解器标志(solver_flag): %s", 
                        solver_flag == INITIAL ? "INITIAL" : "FULLSIZE");

            RCLCPP_INFO_STREAM(this->get_logger(), "\n======================");
        }
    }

    EIGEN_MAKE_ALIGNED_OPERATOR_NEW // 使Eigen对齐

private:
    static constexpr double NS_TO_S = 1e-9;  // 纳秒转秒的常量

    // ROS 2订阅者和发布者
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr sub_imu;  // IMU订阅者
    rclcpp::Subscription<isas_msgs::msg::Anchorlist>::SharedPtr sub_anchor;  // 锚点订阅者
    rclcpp::SubscriptionBase::SharedPtr sub_uwb;  // UWB订阅者
    rclcpp::Publisher<sensor_msgs::msg::PointCloud>::SharedPtr pub_knots_active;  // 活动控制点发布者
    rclcpp::Publisher<sensor_msgs::msg::PointCloud>::SharedPtr pub_knots_inactive;  // 非活动控制点发布者
    rclcpp::Publisher<sfuise_msgs::msg::Calib>::SharedPtr pub_calib;  // 校准发布者
    rclcpp::Publisher<sfuise_msgs::msg::Estimate>::SharedPtr pub_est;  // 估计发布者
    rclcpp::Publisher<std_msgs::msg::Int64>::SharedPtr pub_start_time;  // 启动时间发布者

    // 参数和校准结构体
    Parameters param;  // 参数结构体
    CalibParam calib_param;  // 校准参数结构体

    // 数据缓冲区
    Eigen::aligned_deque<TOAData> toa_buff;  // TOA数据缓冲区
    Eigen::aligned_deque<TDOAData> tdoa_buff;  // TDOA数据缓冲区
    Eigen::aligned_deque<ImuData> imu_buff;  // IMU数据缓冲区
    Eigen::aligned_deque<ImuData> imu_window;  // IMU窗口
    Eigen::aligned_deque<TOAData> toa_window;  // TOA窗口
    Eigen::aligned_deque<TDOAData> tdoa_window;  // TDOA窗口

    // 状态变量
    bool if_anchor_ini;  // 锚点初始化标志
    bool if_tdoa;  // 是否使用TDOA标志
    bool if_uwb_only;  // 是否仅使用UWB标志

    size_t window_count;  // 窗口计数
    int window_size;  // 窗口大小
    int n_window_calib;  // 校准窗口数

    int64_t dt_ns;  // 时间间隔（纳秒）
    int64_t bag_start_time;  // 行李开始时间
    int64_t last_imu_t_ns;  // 上一个IMU时间（纳秒）
    int64_t next_knot_time_ns;  // 下一个节点时间（纳秒）

    // int64_t imu_count;
    // int64_t uwb_count;

    // 求解器状态枚举
    enum SolverFlag { INITIAL, FULLSIZE };
    SolverFlag solver_flag;  // 求解器状态
    SplineState spline_local;  // 本地样条状态

    // 线性化器相关变量
    size_t bias_block_offset;  // 偏差块偏移
    size_t gravity_block_offset;  // 重力块偏移
    size_t hess_size;  // Hessian矩阵大小
    bool pose_fixed;  // 位姿固定标志
    int max_iter;  // 最大迭代次数
    double lambda;  // 步长
    double lambda_vee;  // 步长倍增因子
    double average_runtime;  // 平均运行时间
    std::vector<double> v_toa_offset;  // TOA偏移量

    void readParameters() // 读取参数函数
    {
        // 声明参数文件路径
        std::string config_file;
        this->declare_parameter("rosparam_yaml", "");
        this->get_parameter("rosparam_yaml", config_file);
        RCLCPP_INFO(this->get_logger(), "Loading parameters from: %s", config_file.c_str());

        double imu_sample_coeff = this->declare_parameter("imu_sample_coeff", 1.0);
        RCLCPP_INFO_STREAM(this->get_logger(), "imu_sample_coeff: " << imu_sample_coeff);
        if_uwb_only = (imu_sample_coeff == 0);

        param.if_opt_g = true;
        param.if_opt_transform = true;

        if (this->get_parameter("w_uwb", param.w_uwb)) {
            RCLCPP_INFO(this->get_logger(), "Loaded w_uwb: %.2f", param.w_uwb);
        } else {
            param.w_uwb = 5.0;  // 默认值
            RCLCPP_WARN(this->get_logger(), "Using default w_uwb: %.2f", param.w_uwb);
        }
        
        max_iter = this->declare_parameter("max_iter", 5);
        RCLCPP_INFO_STREAM(this->get_logger(), "max_iter: " << max_iter);
        
        int control_point_fps = this->declare_parameter("control_point_fps", 10);
        RCLCPP_INFO_STREAM(this->get_logger(), "control_point_fps: " << control_point_fps);
        
        dt_ns = 1e9 / control_point_fps;

        if_tdoa = this->declare_parameter("if_tdoa", false);
        RCLCPP_INFO_STREAM(this->get_logger(), "if_tdoa: " << if_tdoa);
        
        bag_start_time = 0;
        n_window_calib = this->declare_parameter("n_window_calib", 50);
        RCLCPP_INFO_STREAM(this->get_logger(), "n_window_calib: " << n_window_calib);
        
        window_size = this->declare_parameter("window_size", 100);
        RCLCPP_INFO_STREAM(this->get_logger(), "window_size: " << window_size);

        if (n_window_calib == 0) {
            RCLCPP_ERROR(this->get_logger(), "n_window_calib cannot be set 0.");
            rclcpp::shutdown();
        } else {
            param.q_nav_uwb_init.setIdentity();
            param.t_nav_uwb_init.setZero();
        }

        std::vector<double> accel_var_inv = this->declare_parameter("accel_var_inv", std::vector<double>{7.8483,7.8483,7.8483});
        RCLCPP_INFO_STREAM(this->get_logger(), "accel_var_inv: [" << accel_var_inv[0] << ", " << accel_var_inv[1] << ", " << accel_var_inv[2] << "]");
        param.accel_var_inv << accel_var_inv[0], accel_var_inv[1], accel_var_inv[2];

        std::vector<double> bias_accel_var_inv = this->declare_parameter("bias_accel_var_inv", std::vector<double>{514.9887, 514.9887, 514.9887});
        RCLCPP_INFO_STREAM(this->get_logger(), "bias_accel_var_inv: [" << bias_accel_var_inv[0] << ", " << bias_accel_var_inv[1] << ", " << bias_accel_var_inv[2] << "]");
        param.bias_accel_var_inv << bias_accel_var_inv[0], bias_accel_var_inv[1], bias_accel_var_inv[2];

        param.w_acc = this->declare_parameter("w_accel", 1.0);
        RCLCPP_INFO_STREAM(this->get_logger(), "w_accel: " << param.w_acc);
        
        param.w_bias_acc = this->declare_parameter("w_bias_accel", 1.0);
        RCLCPP_INFO_STREAM(this->get_logger(), "w_bias_accel: " << param.w_bias_acc);

        std::vector<double> gyro_var_inv = this->declare_parameter("gyro_var_inv", std::vector<double>{27.5646, 27.5646, 27.5646});
        RCLCPP_INFO_STREAM(this->get_logger(), "gyro_var_inv: [" << gyro_var_inv[0] << ", " << gyro_var_inv[1] << ", " << gyro_var_inv[2] << "]");
        param.gyro_var_inv << gyro_var_inv[0], gyro_var_inv[1], gyro_var_inv[2];

        std::vector<double> bias_gyro_var_inv = this->declare_parameter("bias_gyro_var_inv", std::vector<double>{2950.6680, 2950.6680, 2950.6680});
        RCLCPP_INFO_STREAM(this->get_logger(), "bias_gyro_var_inv: [" << bias_gyro_var_inv[0] << ", " << bias_gyro_var_inv[1] << ", " << bias_gyro_var_inv[2] << "]");
        param.bias_gyro_var_inv << bias_gyro_var_inv[0], bias_gyro_var_inv[1], bias_gyro_var_inv[2];

        param.w_gyro = this->declare_parameter("w_gyro", 1.0);
        RCLCPP_INFO_STREAM(this->get_logger(), "w_gyro: " << param.w_gyro);
        
        param.w_bias_gyro = this->declare_parameter("w_bias_gyro", 1.0);
        RCLCPP_INFO_STREAM(this->get_logger(), "w_bias_gyro: " << param.w_bias_gyro);

        param.if_reject_uwb = this->declare_parameter("if_reject_uwb", true);
        RCLCPP_INFO_STREAM(this->get_logger(), "if_reject_uwb: " << param.if_reject_uwb);
        
        if (param.if_reject_uwb) {
            param.reject_uwb_thresh = this->declare_parameter("reject_uwb_thresh", 0.5);
            RCLCPP_INFO_STREAM(this->get_logger(), "reject_uwb_thresh: " << param.reject_uwb_thresh);
            
            param.reject_uwb_window_width = this->declare_parameter("reject_uwb_window_width", 0.8);
            RCLCPP_INFO_STREAM(this->get_logger(), "reject_uwb_window_width: " << param.reject_uwb_window_width);
        }

        std::vector<double> v_offset = this->declare_parameter("offset", std::vector<double>{0.1, -0.025, 0.0});
        RCLCPP_INFO_STREAM(this->get_logger(), "offset: [" << v_offset[0] << ", " << v_offset[1] << ", " << v_offset[2] << "]");
        calib_param.offset = Eigen::Vector3d(v_offset[0], v_offset[1], v_offset[2]);

        if (!if_tdoa) {
            v_toa_offset = this->declare_parameter("toa_offset", std::vector<double>{-0.0700, 0.1539, -0.0751, 0.1409, -0.0247});
            RCLCPP_INFO_STREAM(this->get_logger(), "toa_offset: [" << v_toa_offset[0] << ", " << v_toa_offset[1] << ", " << v_toa_offset[2] << ", " << v_toa_offset[3] << ", " << v_toa_offset[4] << "]");
        }
        RCLCPP_INFO_STREAM(this->get_logger(), "ReadParameters finished");
    }

   // IMU回调函数
    void getImuCallback(const sensor_msgs::msg::Imu::SharedPtr imu_msg)
    {
        // RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: 111111111111111 ");
        int64_t t_ns = rclcpp::Time(imu_msg->header.stamp).nanoseconds(); // 获取当前时间戳
        Eigen::Vector3d acc(imu_msg->linear_acceleration.x, imu_msg->linear_acceleration.y, imu_msg->linear_acceleration.z); // 获取加速度
        Eigen::Vector3d gyro(imu_msg->angular_velocity.x, imu_msg->angular_velocity.y, imu_msg->angular_velocity.z); // 获取角速度

        ImuData imu(t_ns, gyro, acc); // 创建IMU数据对象
        imu_buff.push_back(imu); // 将IMU数据添加到缓冲区
        // std::cout << "imu_buff front:" << imu_buff.front().time_ns << std::endl;
        // std::cout << "imu_buff back:" << imu_buff.back().time_ns << std::endl;
    }

    // TDOA回调函数
    void getTdoaCallback(const cf_msgs::msg::Tdoa::SharedPtr msg)
    {
        TDOAData uwb(rclcpp::Time(msg->header.stamp).nanoseconds(), msg->id_a, msg->id_b, msg->data); // 创建TDOA数据对象
        tdoa_buff.push_back(uwb); // 将TDOA数据添加到缓冲区
    }

    // TOA回调函数
    void getToaCallback(const isas_msgs::msg::RTLSStick::SharedPtr uwb_msg)
    {
        // RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: 3333333333333333 ");
        int64_t t_ns = rclcpp::Time(uwb_msg->header.stamp).nanoseconds(); // 获取时间戳
        for (const auto& rg : uwb_msg->ranges) { // 遍历范围数据
            if (rg.ra == 0) continue; // 如果范围为0，跳过
            
            TOAData uwb(t_ns, rg.id, rg.range); // 创建TOA数据对象,锚点id,锚点到标签的距离
            toa_buff.push_back(uwb); // 将TOA数据添加到缓冲区
            // std::cout << "toa_buff front:" << toa_buff.front().time_ns << std::endl;
            // std::cout << "toa_buff back:" << toa_buff.back().time_ns << std::endl;
        }
    }

    // 锚点回调函数
    void getAnchorCallback(const isas_msgs::msg::Anchorlist::SharedPtr anchor_msg)
    {
        // RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: 22222222222222 ");
        if (if_anchor_ini) return; // 如果锚点已初始化，返回
        for (const auto& anchor : anchor_msg->anchor) { // 遍历锚点
            param.anchor_list[anchor.id] = Eigen::Vector3d(anchor.position.x, anchor.position.y, anchor.position.z); // 添加锚点到列表
        }
        if_anchor_ini = true; // 设置锚点初始化标志
        if (!if_tdoa) { // 进入
            int i = 0; // 初始化索引
            for (auto it = param.anchor_list.begin(); it != param.anchor_list.end(); it++) { // 遍历锚点列表
                param.toa_offset[it->first] = v_toa_offset[i]; // 设置TOA偏移
                i++; // 增加索引
            }
        }
    }

    // 更新测量数据
    template <typename type_data>
    void updateMeasurements(Eigen::aligned_deque<type_data>& data_window, Eigen::aligned_deque<type_data>& data_buff)
    {
        int64_t t_window_l = spline_local.minTimeNs(); // 获取窗口左边界
        if (!data_window.empty()) { // 如果数据窗口不为空
            while (data_window.front().time_ns < t_window_l) { // 移除过期数据
                data_window.pop_front();
            }
        }
        int64_t t_window_r = spline_local.maxTimeNs(); // 获取窗口右边界
        for (size_t i = 0; i < data_buff.size(); i++) { // 遍历数据缓冲区
            auto v = data_buff.at(i); // 获取数据
            if (v.time_ns >= t_window_l && v.time_ns <= t_window_r) { // 如果数据在窗口内
                data_window.push_back(v); // 添加到数据窗口
            } else if (v.time_ns > t_window_r) { // 如果数据超出窗口
                break; // 退出循环
            }
        }
        while (data_buff.front().time_ns <= t_window_r) { // 移除过期数据
            data_buff.pop_front();
            if (data_buff.empty()) break; // 如果缓冲区为空，退出
        }
    }

    bool initialization()
    {
        static bool param_set = false; // 参数设置标志
        static bool initialize_control_point = false; // 控制点初始化标志
        if (initialize_control_point) { // 如果控制点已初始化
            int64_t min_time = 1e18; // 初始化最小时间SAS
            // 我们只能使用时间小于 min_time 的数据来做插值或同步，因为之后的数据还没有到来。
            // imu_buff:存储了按时间排序的 IMU 消息
            // imu_buff.back():取缓冲区的最后一个元素（即时间上最新的IMU数据）
            // imu_buff.back().time_ns:表示这个 IMU 数据的时间戳，单位是纳秒（ns）。
            if (!imu_buff.empty()) min_time = imu_buff.back().time_ns; // 获取IMU缓冲区的时间
            if (!toa_buff.empty()) min_time = std::min(toa_buff.back().time_ns, min_time); // 获取TOA缓冲区的时间
            if (!tdoa_buff.empty()) min_time = std::min(tdoa_buff.back().time_ns, min_time); // 获取TDOA缓冲区的时间
            // std::cout << "min_time:" << min_time << std::endl;
            // std::cout << "spline_local_nextmaxtime:" << spline_local.nextMaxTimeNs() << std::endl;
            // nextMaxTimeNs()返回下一个样条段的最大时间戳，单位是纳秒（ns = nanoseconds）。它通常用于轨迹插值或预测过程中，确定当前插值是否需要"前进"到下一个样条段。
            if (min_time > spline_local.nextMaxTimeNs()) { // 如果最小时间大于样条的最大时间
                // RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: ttttttttttttttt ");
                Eigen::Quaterniond q_ini = spline_local.getKnotOrt(spline_local.numKnots() - 1); // 获取初始四元数
                Eigen::Quaterniond q_ini_backup = q_ini; // 备份初始四S元数
                Eigen::Vector3d pos_ini = spline_local.getKnotPos(spline_local.numKnots() - 1); // 获取初始位置
                Eigen::Matrix<double, 6, 1> bias_ini = spline_local.getKnotBias(spline_local.numKnots() - 1); // 获取初始偏差
                if (!if_uwb_only) { // 如果不只使用UWB，进入
                    if (spline_local.numKnots() <= 2) { // 如果样条节点数小于等于2
                        last_imu_t_ns = bag_start_time; // 设置最后IMU时间为bag开始时间
                    } else {
                        last_imu_t_ns = imu_window.back().time_ns; // 获取IMU窗口的最后时间
                    }
                    integration(next_knot_time_ns, q_ini, pos_ini); // 执行积分
                } else {
                    if (if_tdoa) { // 如果使用TDOA
                        pos_ini = tdoaMultilateration(next_knot_time_ns * NS_TO_S); // 执行TDOA多边定位
                        q_ini  = Eigen::Quaterniond::Identity(); // 设置初始四元数为单位四元数
                    } else {
                        RCLCPP_ERROR(this->get_logger(), "UWB-only tracking only supported for TDOA data!"); // 输出错误信息
                        rclcpp::shutdown(); // 退出程序
                    }
                }
                if (q_ini_backup.dot(q_ini) < 0) q_ini = Eigen::Quaterniond(-q_ini.w(), -q_ini.x(), -q_ini.y(), -q_ini.z()); // 确保四元数方向一致
                spline_local.addOneStateKnot(q_ini, pos_ini, bias_ini); // 添加状态节点
                next_knot_time_ns += dt_ns; // 更新下一个节点时间
                // std::cout << "spline_local_numknots:" << spline_local.numKnots() << std::endl;
                return true; // 返回成功
            } else {
                return false; // 返回失败
            }
        } else {
            if (!param_set) { // 如果参数未设置，，，，多次运行，为0
                // RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: tttttttttttttttt ");
                param_set = setParameters(); // 设置参数
                std_msgs::msg::Int64 start_time; // 创建启动时间消息
                start_time.data = bag_start_time; // 设置启动时间
                pub_start_time->publish(start_time); // 发布启动时间
                // std::cout << "2222222222222dt_ns:" << dt_ns << " bag_start_time:" << bag_start_time << std::endl;
            }
            if (param_set && if_anchor_ini) { // 如果参数已设置且锚点已初始化，，，，运行1次
                // RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: tttttttttttttttt ");
                // 以时间间隔 dt_ns，从时间 bag_start_time 开始，初始化一个样条轨迹，初始 knot 索引为 0
                spline_local.init(dt_ns, 0, bag_start_time); // 初始化样条
                // std::cout << "11111111111111dt_ns:" << dt_ns << " bag_start_time:" << bag_start_time << std::endl;
                // std::cout << "111111111111111111###" << spline_local.nextMaxTimeNs() << std::endl;
                if (!if_uwb_only) { // 如果不只使用UWB，进入
                    Eigen::Vector3d gravity_sum(0, 0, 0); // 初始化重力和
                    size_t n_imu = imu_buff.size(); // 获取IMU缓冲区大小
                    for (size_t i = 0; i < n_imu; i++) { // 遍历IMU缓冲区
                        gravity_sum += imu_buff.at(i).accel; // 累加加速度
                    }
                    gravity_sum /= n_imu; // 计算平均重力
                    Eigen::Vector3d gravity_ave = gravity_sum.normalized() * 9.81; // 归一化重力
                    calib_param.gravity = gravity_ave; // 设置校准重力
                }
                calib_param.q_nav_uwb = param.q_nav_uwb_init; // 设置导航四元数，从导航坐标系到UWB传感器坐标系的初始旋转关系
                calib_param.t_nav_uwb = param.t_nav_uwb_init; // 设置导航平移，从导航坐标系到UWB传感器坐标系的初始位移向
                initialize_control_point = true; // 设置控制点初始化标志
                int num = 1; // 控制点数量
                for (int i = 0; i < num; i++) { // 添加控制点
                    Eigen::Quaterniond q_ini = Eigen::Quaterniond::Identity(); // 创建单位四元数，代表"无旋转"，相当于朝向不变
                    Eigen::Vector3d pos_ini = Eigen::Vector3d::Zero(); // 创建零位置，初始位置为零向量 [0, 0, 0]
                    Eigen::Matrix<double, 6, 1> bias_ini = Eigen::Matrix<double, 6, 1>::Zero(); // 创建零偏差，创建一个零偏差向量（6维）
                    spline_local.addOneStateKnot(q_ini, pos_ini, bias_ini); // 添加状态节点
                    next_knot_time_ns += dt_ns; // 更新下一个节点时间
                }
                // std::cout << "22222222222222222###" << spline_local.nextMaxTimeNs() << std::endl;
            }
            return false; // 返回失败
        }
    }

    Eigen::Vector3d tdoaMultilateration(double t_s) const // TDOA多边定位函数
    {
        static Eigen::Vector3d last_knot(0, 0, 0); // 上一个节点位置
        static bool set_origin = true; // 原点设置标志
        int num_data = 7; // 数据数量
        size_t idx[num_data]; // 索引数组
        findClosestNWithOrderedID(t_s, num_data, idx); // 查找最近的N个数据
        Eigen::Vector3d pos; // 位置
        Eigen::MatrixXd H(num_data, 4); // Jacobian矩阵
        Eigen::VectorXd b(num_data); // 右侧向量
        Eigen::Vector3d anchor0 = param.anchor_list.at(0); // 获取第一个锚点
        std::vector<double> range; // 范围数据
        range.push_back(tdoa_buff.at(idx[0]).data); // 添加第一个范围
        for (int i = 1; i < num_data; i++) { // 计算范围
            range.push_back(range[i - 1] + tdoa_buff.at(idx[i]).data);
        }
        for (int i = 0; i < num_data; i++) { // 填充Jacobian矩阵和右侧向量
            TDOAData uwb = tdoa_buff.at(idx[i]); // 获取TDOA数据
            double range0 = range[i]; // 获取范围
            Eigen::Vector3d anchori = param.anchor_list.at(uint16_t(uwb.idB)); // 获取锚点位置
            H.row(i) = Eigen::Vector4d(anchori.x() - anchor0.x(), anchori.y() - anchor0.y(), anchori.z() - anchor0.z(), range0); // 填充Jacobian矩阵
            b[i] = range0 * range0 - anchori.dot(anchori) + anchor0.dot(anchor0); // 填充右侧向量
        }
        H *= -2; // Jacobian矩阵乘以-2
        Eigen::VectorXd x = (H.transpose() * H).inverse() * H.transpose() * b; // 计算最小二乘解
        pos =  x.head(3); // 获取位置
        if (!set_origin) { // 如果未设置原点
            pos.setZero(); // 设置位置为零
            set_origin = true; // 设置原点标志
        } else {
            pos = calib_param.q_nav_uwb.inverse() * (pos - calib_param.t_nav_uwb); // 计算最终位置
        }
        return pos; // 返回位置
    }

    void findClosestNWithOrderedID(double t_s, int N, size_t* idx) const // 查找最近的N个数据
    {
        std::vector<std::pair<std::pair<int,int>,double>> diff; // 差异向量
        for (auto it = tdoa_buff.begin(); it != tdoa_buff.end(); it++) { // 遍历TDOA缓冲区
            double t = it->time_ns * NS_TO_S; // 获取时间
            diff.push_back(std::make_pair(std::make_pair(it->idA, it->idB), std::abs(t - t_s))); // 添加到差异向量
        }
        int idA = 0; // ID A
        int idB = 1; // ID B
        for (int i = 0; i < N; i++) { // 查找N个最近数据
            size_t idx_min = 0; // 最小索引
            std::pair<std::pair<int,int>,double> it_min = diff[idx_min]; // 最小差异
            for (size_t j = 1; j < diff.size(); j++) { // 遍历差异向量
                std::pair<std::pair<int,int>,double> it = diff[j]; // 获取差异
                if (it.first == std::make_pair(idA, idB)) { // 如果ID匹配
                    idx_min = it.second < it_min.second ? j : idx_min; // 更新最小索引
                    it_min = diff[idx_min]; // 更新最小差异
                }
            }
            idx[i] = idx_min; // 设置索引
            idA++; // 增加ID A
            idB++; // 增加ID B
            diff[idx_min].second = std::numeric_limits<double>::max(); // 设置最小差异为最大值，避免重复
        }
    }

    bool optimization() // 优化函数
    {
        if (spline_local.numKnots() < 2) return false; // 如果样条节点数小于2，返回失败

        if (param.if_reject_uwb) { // 如果需要拒绝UWB，进入
            if (solver_flag == INITIAL && spline_local.numKnots() < int(param.reject_uwb_window_width * window_size)) 
                param.if_reject_uwb_in_optimization = false; // 不在优化中拒绝UWB
            else
                param.if_reject_uwb_in_optimization = true; // 在优化中拒绝UWB
        } else {
            param.if_reject_uwb_in_optimization = false; // 不拒绝UWB
        }

        if ((int)window_count >= n_window_calib) { // 如果窗口计数达到校准窗口数
            param.if_opt_g = false; // 不优化重力
            param.if_opt_transform = false; // 不优化变换
        }

        if (!if_uwb_only) updateMeasurements(imu_window, imu_buff); // 更新IMU测量
        if (if_tdoa) {
            updateMeasurements(tdoa_window, tdoa_buff); // 更新TDOA测量
        } else {
            updateMeasurements(toa_window, toa_buff); // 更新TOA测量
        }

        bool converged = false; // 收敛标志
        int opt_iter = 0; // 优化迭代计数
        pose_fixed = false; // 位姿固定标志

        if (solver_flag == INITIAL) {
            pose_fixed = true; // 如果为初始状态，固定位姿
        }
        lambda = 1e-6; // 初始化步长
        lambda_vee = 2; // 初始化步长倍增因子
        updateLinearizerSize(); // 更新线性化器大小

        while (!converged && opt_iter < max_iter) { // 迭代优化
            converged = optimize(opt_iter); // 执行优化
            opt_iter++; // 增加迭代计数
        }
        
        return converged; // 返回收敛状态
    }

    bool setParameters() // 设置参数函数
    {
        if (imu_buff.empty() && !if_uwb_only) 
            return false; // 如果IMU缓冲区为空且不只使用UWB，返回失败
        if (imu_buff.empty() && toa_buff.empty() && tdoa_buff.empty()) { // 如果所有缓冲区都为空
            return false; // 返回失败
        } else {
            // std::cout << "111111111111###imu_buff" << imu_buff.front().time_ns << std::endl;
            // imu_buff.front().time_ns：imu_buff（IMU数据缓冲区）中第一个元素的 time_ns（时间戳，单位为纳秒）
            if (!imu_buff.empty()) { // 如果IMU缓冲区不为空
                bag_start_time += imu_buff.front().time_ns; // 更新bag开始时间
            } else if (!toa_buff.empty()) { // 如果TOA缓冲区不为空
                bag_start_time += toa_buff.front().time_ns; // 更新bag开始时间
            } else { // 如果TDOA缓冲区不为空
                bag_start_time += tdoa_buff.front().time_ns; // 更新行李开始时间
            }
        }
        next_knot_time_ns = bag_start_time; // 设置下一个节点时间
        return true; // 返回成功
    }

    void integrateStep(int64_t prevTime, int64_t dt_, const ImuData& imu, Eigen::Matrix3d& Rs, Eigen::Vector3d& Ps, Eigen::Vector3d& Vs) // 积分步骤
    {
        static bool first_imu = false; // 首次IMU标志
        static Eigen::Vector3d acc_0; // 初始加速度
        static Eigen::Vector3d gyr_0; // 初始角速度
        Eigen::Vector3d linear_acceleration = imu.accel; // 获取线性加速度
        Eigen::Vector3d angular_velocity = imu.gyro; // 获取角速度

        if (!first_imu) { // 如果不是首次IMU
            first_imu = true; // 设置首次IMU标志
            acc_0 = linear_acceleration; // 设置初始加速度
            gyr_0 = angular_velocity; // 设置初始角速度
        }

        Eigen::Vector3d g = calib_param.gravity; // 获取重力
        Eigen::Vector3d ba; // 偏差加速度
        Eigen::Vector3d bg; // 偏差角速度
        Eigen::Matrix<double, 6, 1> bias = spline_local.itpBias(prevTime); // 获取偏差
        ba = bias.head<3>(); // 获取加速度偏差
        bg = bias.tail<3>(); // 获取角速度偏差

        double dt = dt_ * NS_TO_S; // 转换时间间隔
        Eigen::Vector3d un_acc_0; // 未偏差加速度
        un_acc_0 = Rs * (acc_0 - ba) - g; // 计算未偏差加速度
        Eigen::Vector3d un_gyr = 0.5 * (gyr_0 + angular_velocity) - bg; // 计算未偏差角速度
        Rs *= Quater::deltaQ(un_gyr * dt).toRotationMatrix(); // 更新旋转矩阵
        Eigen::Vector3d un_acc_1 = Rs * (linear_acceleration - ba) - g; // 计算未偏差加速度
        Eigen::Vector3d un_acc = 0.5 * (un_acc_0 + un_acc_1); // 计算平均未偏差加速度

        Ps += dt * Vs + 0.5 * dt * dt * un_acc; // 更新位置
        Vs += dt * un_acc; // 更新速度

        acc_0 = linear_acceleration; // 更新初始加速度
        gyr_0 = angular_velocity; // 更新初始角速度
    }

      void integration(const int64_t curTime, Eigen::Quaterniond& qs, Eigen::Vector3d& Ps)
    {
        std::vector<ImuData> imu_vec; // IMU数据向量
        getIMUInterval(last_imu_t_ns, curTime, imu_vec); // 获取IMU样条时间间隔间数据
        
        if (!imu_vec.empty()) { // 如果IMU数据不为空
            Eigen::Quaterniond qs0; // 初始四元数
            spline_local.itpQuaternion(last_imu_t_ns, &qs0); // 获取插值四元数
            Eigen::Matrix3d Rs0(qs0); // 创建旋转矩阵
            Eigen::Vector3d Ps0 = spline_local.itpPosition(last_imu_t_ns); // 获取插值位置
            Eigen::Vector3d Vs0 = spline_local.itpPosition<1>(last_imu_t_ns); // 获取插值速度
            
            for (size_t i = 0; i < imu_vec.size(); i++) { // 遍历IMU数据
                int64_t dt; // 时间间隔
                int64_t t_ns = imu_vec[i].time_ns; // 获取时间戳
                if (i == 0) { // 如果是第一个数据
                    dt = t_ns - last_imu_t_ns; // 计算时间间隔
                } else {
                    dt = t_ns - imu_vec[i - 1].time_ns; // 计算时间间隔
                }
                integrateStep(last_imu_t_ns, dt, imu_vec[i], Rs0, Ps0, Vs0); // 执行积分步骤
            }
            qs = Eigen::Quaterniond(Rs0); // 更新四元数
            Ps = Ps0; // 更新位置
        } else {
            qs = spline_local.extrapolateOrtKnot(1); // 外推四元数
            Ps = spline_local.extrapolatePosKnot(1); // 外推位置
        }
    }

    bool getIMUInterval(int64_t t0, int64_t t1, std::vector<ImuData>& imu_vec)
    {
        if (imu_buff.empty()) { // 如果IMU缓冲区为空
            RCLCPP_ERROR(this->get_logger(), "No IMU available."); // 输出错误信息
            return false; // 返回失败
        }
        int idx = 0; // 初始化索引
        while (imu_buff.at(idx).time_ns <= std::min(imu_buff.back().time_ns, t1)) { // 遍历IMU缓冲区
            imu_vec.push_back(imu_buff.at(idx)); // 添加IMU数据到向量
            idx++; // 增加索引
            if (idx >= imu_buff.size()) break; // 如果索引超出范围，退出
        }
        return true; // 返回成功
    }

    void displayControlPoints()
    {
        // RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: 5555555555555 ");
        // 创建非活动控制点消息
        sensor_msgs::msg::PointCloud points_inactive_msg;
        points_inactive_msg.header.frame_id = "map"; // 设置坐标系为地图
        points_inactive_msg.header.stamp = rclcpp::Time(spline_local.minTimeNs());
        points_inactive_msg.points.push_back(getPointMsg(spline_local.getIdlePos(0))); // 添加第一个非活动控制点
        points_inactive_msg.points.push_back(getPointMsg(spline_local.getIdlePos(1))); // 添加第二个非活动控制点
        points_inactive_msg.points.push_back(getPointMsg(spline_local.getIdlePos(2))); // 添加第三个非活动控制点


        // // 打印信息到命令行
        // for (size_t i = 0; i < spline_local.numKnots(); i++) {
        //     geometry_msgs::msg::Point32 point = getPointMsg(spline_local.getIdlePos(i));
        //     std::cout << "Point"
        //             << i << ": ["
        //             << point.x << ", "
        //             << point.y << ", "
        //             << point.z << "]" << std::endl;
        // }

        // 创建活动控制点消息
        sensor_msgs::msg::PointCloud points_active_msg;
        points_active_msg.header.frame_id = "map"; // 设置坐标系为地图
        points_active_msg.header.stamp = rclcpp::Time(spline_local.minTimeNs());
        for (size_t i = 0; i < spline_local.numKnots(); i++) { // 遍历样条节点
            points_active_msg.points.push_back(getPointMsg(spline_local.getKnotPos(i))); // 添加活动控制点
        }

        // 发布非活动和活动控制点消息
        pub_knots_inactive->publish(points_inactive_msg);
        pub_knots_active->publish(points_active_msg);
    }

    geometry_msgs::msg::Point32 getPointMsg(Eigen::Vector3d p)
    {
        geometry_msgs::msg::Point32 p_msg; // 创建点消息
        Eigen::Vector3d p_U = calib_param.q_nav_uwb * p + calib_param.t_nav_uwb; // 计算校准后的点
        p_msg.x = p_U.x(); // 设置x坐标
        p_msg.y = p_U.y(); // 设置y坐标
        p_msg.z = p_U.z(); // 设置z坐标
        return p_msg; // 返回点消息
    }

    bool optimize(const int iter)
    {
        Linearizer lopt(bias_block_offset, gravity_block_offset, hess_size, &spline_local, &calib_param, &param, pose_fixed);
        if (!imu_window.empty()) lopt(imu_window);
        if (!tdoa_window.empty()) lopt(tdoa_window);
        if (!toa_window.empty()) lopt(toa_window);

        if (iter) {
            double gradient_max_norm = lopt.accum.getB().array().abs().maxCoeff();
            if (gradient_max_norm < 1e-8) return true;
        }

        lopt.accum.setup_solver();
        Eigen::VectorXd Hdiag = lopt.accum.Hdiagonal();
        bool stop = false;

        while (!stop) {
            Eigen::VectorXd Hdiag_lambda = Hdiag * lambda;
            for (int i = 0; i < Hdiag_lambda.size(); i++) {
                Hdiag_lambda[i] = std::max(Hdiag_lambda[i], 1e-18);
            }

            Eigen::VectorXd inc_full = -lopt.accum.solve(&Hdiag_lambda);
            Eigen::aligned_deque<Eigen::Vector3d> knots_trans_backup;
            Eigen::aligned_deque<Eigen::Quaterniond> knots_rot_backup;
            Eigen::aligned_deque<Eigen::Matrix<double, 6, 1>> knots_bias_backup;
            spline_local.getAllStateKnots(knots_trans_backup, knots_rot_backup, knots_bias_backup);

            CalibParam calib_param_backup = calib_param;
            applyIncFull(inc_full);

            ComputeErrorSplineOpt eopt(&spline_local, &calib_param, &param);
            if (!toa_window.empty()) eopt(toa_window);
            if (!imu_window.empty()) eopt(imu_window);
            if (!tdoa_window.empty()) eopt(tdoa_window);

            double f_diff = lopt.error - eopt.error;
            double l_diff = 0.5 * inc_full.dot(inc_full * lambda - lopt.accum.getB());
            double step_quality = f_diff / l_diff;

            if (step_quality < 0) {
                lambda = std::min(100.0, lambda_vee * lambda);
                if (abs(lambda - 100.0) < 1e-3) {
                    stop = true;
                }
                lambda_vee *= 2;
                spline_local.setAllKnots(knots_trans_backup, knots_rot_backup, knots_bias_backup);
                calib_param.setCalibParam(calib_param_backup);
            } else {
                if (inc_full.norm() / ((double)spline_local.numKnots()) < 1e-10 || abs(f_diff) / lopt.error < 1e-6) {
                    stop = true;
                }
                lambda = std::max(1e-18, lambda * std::max(1.0 / 3, 1 - std::pow(2 * step_quality - 1, 3.0)));
                lambda_vee = 2;
                break;
            }
        }
        return stop;
    }

    void updateLinearizerSize()
    {
        int num_knots = spline_local.numKnots();
        bias_block_offset = Linearizer::POSE_SIZE * num_knots;
        hess_size = bias_block_offset;
        if (!if_uwb_only) {
            hess_size += Linearizer::ACCEL_BIAS_SIZE * num_knots;
            hess_size += Linearizer::GYRO_BIAS_SIZE * num_knots;
        }
        gravity_block_offset = hess_size;
        hess_size += Linearizer::G_SIZE;
        if (param.if_opt_transform) {
            hess_size += Linearizer::OFFSET_SIZE;
            hess_size += Linearizer::ROTATION_SIZE;
        }
    }

    void applyIncFull(Eigen::VectorXd& inc_full)
    {
        size_t num_knots = spline_local.numKnots();
        for (size_t i = 0; i < num_knots; i++) {
            Eigen::Matrix<double, 6, 1> inc = inc_full.segment<Linearizer::POSE_SIZE>(Linearizer::POSE_SIZE * i);
            spline_local.applyPoseInc(i, inc);
        }
        spline_local.checkQuaternionControlPoints();

        if (!if_uwb_only) {
            for (size_t i = 0; i < num_knots; i++) {
                Eigen::Matrix<double, 6, 1> inc = inc_full.segment<Linearizer::BIAS_SIZE>(bias_block_offset + Linearizer::BIAS_SIZE * i);
                spline_local.applyBiasInc(i, inc);
            }
            spline_local.updateBiasIdleFirstWindow();
            if (param.if_opt_g) {
                Eigen::VectorXd dg = inc_full.segment<Linearizer::G_SIZE>(gravity_block_offset);
                Eigen::Vector3d g0 = (calib_param.gravity + Sphere::TangentBasis(calib_param.gravity) * dg).normalized() * 9.81;
                calib_param.gravity = g0;
            }
        }

        if (param.if_opt_transform) {
            calib_param.t_nav_uwb += inc_full.segment<Linearizer::OFFSET_SIZE>(gravity_block_offset + Linearizer::TRANS_OFFSET);
            Eigen::Quaterniond q_inc;
            Quater::exp(inc_full.segment<Linearizer::ROTATION_SIZE>(gravity_block_offset + Linearizer::ROTATION_OFFSET), q_inc);
            calib_param.q_nav_uwb *= q_inc;
        }
    }



};




int main(int argc, char *argv[])  // 主函数
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SplineFusion>();
    RCLCPP_INFO(node->get_logger(), "\033[1;32m---->\033[0m Starting SplineFusion.");

    // rclcpp::spin(node); 
    rclcpp::Rate rate(1000); 
    rclcpp::executors::SingleThreadedExecutor executor;
    executor.add_node(node);

    while (rclcpp::ok()) {
        executor.spin_some(); // 处理回调
        // 其他任务（如发布消息、控制逻辑）
        node->run();
        // RCLCPP_INFO(node->get_logger(), "Running SplineFusion loop...");
        rate.sleep();
    }

    rclcpp::shutdown();
    return 0;
}
