#include <ros/ros.h> // 引入ROS库
#include "../include/Linearizer.h" // 引入线性化器头文件
#include "../include/Accumulator.h" // 引入累加器头文件
#include "../include/utils/tic_toc.h" // 引入计时工具头文件
#include "std_msgs/Int64.h" // 引入Int64消息类型
#include "sensor_msgs/Imu.h" // 引入IMU传感器消息类型
#include "cf_msgs/Tdoa.h" // 引入TDOA消息类型
#include "sensor_msgs/PointCloud.h" // 引入点云消息类型
#include "isas_msgs/Anchorlist.h" // 引入锚点列表消息类型
#include "isas_msgs/RTLSStick.h" // 引入RTLSStick消息类型
#include "sfuise_msgs/Calib.h" // 引入校准消息类型
#include "sfuise_msgs/Spline.h" // 引入样条消息类型
#include "sfuise_msgs/Estimate.h" // 引入估计消息类型

class SplineFusion // 定义样条融合类
{
  public:
    SplineFusion(ros::NodeHandle& nh) // 构造函数，接收ROS节点句柄
    {
        if_anchor_ini = false; // 初始化锚点标志
        average_runtime = 0; // 初始化平均运行时间
        window_count = 0; // 初始化窗口计数
        solver_flag = INITIAL; // 初始化求解器标志
        readParameters(nh); // 读取参数
        // 订阅IMU和锚点数据
        sub_imu = nh.subscribe("/EstimationInterface/imu_ds", 1000, &SplineFusion::getImuCallback, this);
        sub_anchor = nh.subscribe("/EstimationInterface/anchor_list", 1000, &SplineFusion::getAnchorCallback, this);
        // 根据是否使用TDOA选择订阅的主题
        if (if_tdoa) {
            sub_uwb = nh.subscribe("/EstimationInterface/tdoa_ds", 1000, &SplineFusion::getTdoaCallback, this);
        } else {
            sub_uwb = nh.subscribe("/EstimationInterface/toa_ds", 1000, &SplineFusion::getToaCallback, this);
        }
        // 发布控制点和校准消息
        // 发布活动控制点的点云消息，队列大小为1000
        pub_knots_active = nh.advertise<sensor_msgs::PointCloud>("active_control_points", 1000);
        // 发布非活动控制点的点云消息，队列大小为1000
        pub_knots_inactive = nh.advertise<sensor_msgs::PointCloud>("inactive_control_points", 1000);
        // 发布系统校准消息，队列大小为100
        pub_calib = nh.advertise<sfuise_msgs::Calib>("sys_calib", 100);
        // 发布估计窗口消息，队列大小为1000
        pub_est = nh.advertise<sfuise_msgs::Estimate>("est_window", 1000);
        // 发布启动时间消息，队列大小为1000
        pub_start_time = nh.advertise<std_msgs::Int64>("start_time", 1000);
    }

    void run() // 运行函数
    {
        static int num_window = 0; // 窗口计数
        TicToc t_window; // 创建计时器
        if (initialization()) { // 如果初始化成功
            displayControlPoints(); // 显示控制点
            optimization(); // 执行优化
            double t_consum = t_window.toc(); // 计算消耗时间
            average_runtime = (t_consum + double(num_window) * average_runtime) / double (num_window + 1); // 更新平均运行时间
            num_window++; // 增加窗口计数
            if ((int) window_count <= n_window_calib) { // 如果窗口计数小于等于校准窗口数
                sfuise_msgs::Calib calib_msg; // 创建校准消息
                // 设置校准参数
                calib_msg.q_nav_uwb.w = calib_param.q_nav_uwb.w();
                calib_msg.q_nav_uwb.x = calib_param.q_nav_uwb.x();
                calib_msg.q_nav_uwb.y = calib_param.q_nav_uwb.y();
                calib_msg.q_nav_uwb.z = calib_param.q_nav_uwb.z();
                calib_msg.t_nav_uwb.x = calib_param.t_nav_uwb[0];
                calib_msg.t_nav_uwb.y = calib_param.t_nav_uwb[1];
                calib_msg.t_nav_uwb.z = calib_param.t_nav_uwb[2];
                geometry_msgs::Point offset_msg; // 创建偏移消息
                offset_msg.x = calib_param.offset.x();
                offset_msg.y = calib_param.offset.y();
                offset_msg.z = calib_param.offset.z();
                calib_msg.t_tag_body_set = offset_msg; // 设置标签体偏移
                pub_calib.publish(calib_msg); // 发布校准消息
            }
            if (spline_local.numKnots() >= (size_t) window_size) { // 如果样条节点数达到窗口大小
                window_count++; // 增加窗口计数
                if (solver_flag == INITIAL) { // 如果求解器标志为初始状态
                    solver_flag = FULLSIZE; // 设置为全尺寸状态
                }
            }
            sfuise_msgs::Spline spline_msg; // 创建样条消息
            spline_local.getSplineMsg(spline_msg); // 获取样条消息
            sfuise_msgs::Estimate est_msg; // 创建估计消息
            est_msg.spline = spline_msg; // 设置样条
            est_msg.if_full_window.data = (solver_flag != INITIAL); // 设置是否为全窗口
            est_msg.runtime.data = average_runtime; // 设置运行时间
            pub_est.publish(est_msg); // 发布估计消息
            displayControlPoints(); // 显示控制点
            if (solver_flag == FULLSIZE) spline_local.removeOneOldState(); // 如果为全尺寸状态，移除一个旧状态
        }
    }

    EIGEN_MAKE_ALIGNED_OPERATOR_NEW // 使Eigen对齐

  private:
    static constexpr double NS_TO_S = 1e-9; // 纳秒转秒的常量

    // ROS订阅者和发布者
    ros::Subscriber sub_imu; // IMU订阅者
    ros::Subscriber sub_anchor; // 锚点订阅者
    ros::Subscriber sub_uwb; // UWB订阅者
    ros::Publisher pub_knots_active; // 活动控制点发布者
    ros::Publisher pub_knots_inactive; // 非活动控制点发布者
    ros::Publisher pub_calib; // 校准发布者
    ros::Publisher pub_est; // 估计发布者
    ros::Publisher pub_start_time; // 启动时间发布者

    Parameters param; // 参数结构体
    CalibParam calib_param; // 校准参数结构体

    // 数据缓冲区
    Eigen::aligned_deque<TOAData> toa_buff; // TOA数据缓冲区
    Eigen::aligned_deque<TDOAData> tdoa_buff; // TDOA数据缓冲区
    Eigen::aligned_deque<ImuData> imu_buff; // IMU数据缓冲区
    Eigen::aligned_deque<ImuData> imu_window; // IMU窗口
    Eigen::aligned_deque<TOAData> toa_window; // TOA窗口
    Eigen::aligned_deque<TDOAData> tdoa_window; // TDOA窗口

    // 状态变量
    bool if_anchor_ini; // 锚点初始化标志
    bool if_tdoa; // 是否使用TDOA标志
    bool if_uwb_only; // 是否仅使用UWB标志

    size_t window_count; // 窗口计数
    int window_size; // 窗口大小
    int n_window_calib; // 校准窗口数

    int64_t dt_ns; // 时间间隔（纳秒）
    int64_t bag_start_time; // 行李开始时间
    int64_t last_imu_t_ns; // 上一个IMU时间（纳秒）
    int64_t next_knot_TimeNs; // 下一个节点时间（纳秒）

    // 求解器状态枚举
    enum SolverFlag {
        INITIAL, // 初始状态
        FULLSIZE // 全尺寸状态
    };
    SolverFlag solver_flag; // 求解器状态
    SplineState spline_local; // 本地样条状态

    // 线性化器相关变量
    size_t bias_block_offset; // 偏差块偏移
    size_t gravity_block_offset; // 重力块偏移
    size_t hess_size; // Hessian矩阵大小
    bool pose_fixed; // 位姿固定标志
    int max_iter; // 最大迭代次数
    double lambda; // 步长
    double lambda_vee; // 步长倍增因子
    double average_runtime; // 平均运行时间
    std::vector<double> v_toa_offset; // TOA偏移量

    void readParameters(ros::NodeHandle& nh) // 读取参数函数
    {
        if (CommonUtils::readParam<double>(nh, "imu_sample_coeff")==0) { // 读取IMU采样系数
            if_uwb_only = true; // 如果系数为0，则仅使用UWB
        } else {
            if_uwb_only = false; // 否则不只使用UWB
        }
        param.if_opt_g = true; // 设置优化重力标志
        param.if_opt_transform = true; // 设置优化变换标志
        param.w_uwb = CommonUtils::readParam<double>(nh, "w_uwb"); // 读取UWB权重
        max_iter = CommonUtils::readParam<int>(nh, "max_iter"); // 读取最大迭代次数
        dt_ns = 1e9 / CommonUtils::readParam<int>(nh, "control_point_fps"); // 计算时间间隔
        if_tdoa = CommonUtils::readParam<bool>(nh, "if_tdoa"); // 读取是否使用TDOA标志
        bag_start_time = 0; // 初始化行李开始时间
        n_window_calib = CommonUtils::readParam<int>(nh, "n_window_calib"); // 读取校准窗口数
        window_size = CommonUtils::readParam<int>(nh, "window_size"); // 读取窗口大小
        if (n_window_calib == 0) { // 如果校准窗口数为0
            ROS_ERROR_STREAM("n_window_calib cannot be set 0."); // 输出错误信息
            exit(1); // 退出程序
        } else {
            param.q_nav_uwb_init.setIdentity(); // 初始化导航四元数
            param.t_nav_uwb_init.setZero(); // 初始化导航平移
        }
        // 读取加速度和陀螺仪的方差倒数
        std::vector<double> accel_var_inv = CommonUtils::readParam<std::vector<double>>(nh, "accel_var_inv");
        param.accel_var_inv << accel_var_inv.at(0), accel_var_inv.at(1), accel_var_inv.at(2);
        std::vector<double> bias_accel_var_inv = CommonUtils::readParam<std::vector<double>>(nh, "bias_accel_var_inv");
        param.bias_accel_var_inv << bias_accel_var_inv.at(0), bias_accel_var_inv.at(1), bias_accel_var_inv.at(2);
        param.w_acc = CommonUtils::readParam<double>(nh, "w_accel"); // 读取加速度权重
        param.w_bias_acc = CommonUtils::readParam<double>(nh, "w_bias_accel"); // 读取加速度偏差权重
        std::vector<double> gyro_var_inv = CommonUtils::readParam<std::vector<double>>(nh, "gyro_var_inv");
        param.gyro_var_inv << gyro_var_inv.at(0), gyro_var_inv.at(1), gyro_var_inv.at(2);
        std::vector<double> bias_gyro_var_inv = CommonUtils::readParam<std::vector<double>>(nh, "bias_gyro_var_inv");
        param.bias_gyro_var_inv << bias_gyro_var_inv.at(0), bias_gyro_var_inv.at(1), bias_gyro_var_inv.at(2);
        param.w_gyro = CommonUtils::readParam<double>(nh, "w_gyro"); // 读取陀螺仪权重
        param.w_bias_gyro = CommonUtils::readParam<double>(nh, "w_bias_gyro"); // 读取陀螺仪偏差权重
        param.if_reject_uwb = CommonUtils::readParam<bool>(nh, "if_reject_uwb"); // 读取是否拒绝UWB标志
        if (param.if_reject_uwb) { // 如果拒绝UWB标志为真
            param.reject_uwb_thresh = CommonUtils::readParam<double>(nh, "reject_uwb_thresh"); // 读取拒绝阈值
            param.reject_uwb_window_width = CommonUtils::readParam<double>(nh, "reject_uwb_window_width"); // 读取拒绝窗口宽度
        }
        std::vector<double> v_offset; // 偏移量向量
        nh.getParam("offset", v_offset); // 获取偏移量参数
        calib_param.offset = Eigen::Vector3d(v_offset.at(0), v_offset.at(1), v_offset.at(2)); // 设置校准偏移
        if (!if_tdoa) { // 如果不使用TDOA
            v_toa_offset = CommonUtils::readParam<std::vector<double>>(nh, "toa_offset"); // 读取TOA偏移量
        }
    }

    void getImuCallback(const sensor_msgs::ImuConstPtr& imu_msg) // IMU回调函数
    {
        int64_t t_ns = imu_msg->header.stamp.toNSec(); // 获取时间戳
        Eigen::Vector3d acc(imu_msg->linear_acceleration.x, imu_msg->linear_acceleration.y, imu_msg->linear_acceleration.z); // 获取加速度
        Eigen::Vector3d gyro(imu_msg->angular_velocity.x, imu_msg->angular_velocity.y, imu_msg->angular_velocity.z); // 获取角速度
        ImuData imu(t_ns, gyro, acc); // 创建IMU数据对象
        imu_buff.push_back(imu); // 将IMU数据添加到缓冲区
    }

    void getTdoaCallback(const cf_msgs::Tdoa::ConstPtr& msg) // TDOA回调函数
    {
        TDOAData uwb(msg->header.stamp.toNSec(), msg->idA, msg->idB, msg->data); // 创建TDOA数据对象
        tdoa_buff.push_back(uwb); // 将TDOA数据添加到缓冲区
    }

    void getToaCallback(const isas_msgs::RTLSStick::ConstPtr& uwb_msg) // TOA回调函数
    {
        int64_t t_ns = uwb_msg->header.stamp.toNSec(); // 获取时间戳
        for (const auto& rg : uwb_msg->ranges) { // 遍历范围数据
            if (rg.ra == 0) continue; // 如果范围为0，跳过
            TOAData uwb(t_ns, rg.id, rg.range); // 创建TOA数据对象
            toa_buff.push_back(uwb); // 将TOA数据添加到缓冲区
        }
    }

    void getAnchorCallback(const isas_msgs::Anchorlist::ConstPtr& anchor_msg) // 锚点回调函数
    {
        if (if_anchor_ini) return; // 如果锚点已初始化，返回
        for (const auto& anchor : anchor_msg->anchor) { // 遍历锚点
            param.anchor_list[anchor.id] = Eigen::Vector3d(anchor.position.x, anchor.position.y, anchor.position.z); // 添加锚点到列表
        }
        if_anchor_ini = true; // 设置锚点初始化标志
        if (!if_tdoa) { // 如果不使用TDOA
            int i = 0; // 初始化索引
            for (auto it = param.anchor_list.begin(); it != param.anchor_list.end(); it++) { // 遍历锚点列表
                param.toa_offset[it->first] = v_toa_offset[i]; // 设置TOA偏移
                i++; // 增加索引
            }
        }
    }

    template <typename type_data>
    void updateMeasurements(Eigen::aligned_deque<type_data>& data_window, Eigen::aligned_deque<type_data>& data_buff) // 更新测量数据
    {
        int64_t t_window_l = spline_local.minTimeNs(); // 获取窗口左边界
        if(!data_window.empty()) { // 如果数据窗口不为空
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
            if(data_buff.empty()) break; // 如果缓冲区为空，退出
        }
    }

    bool initialization() // 初始化函数
    {
        static bool param_set = false; // 参数设置标志
        static bool initialize_control_point = false; // 控制点初始化标志
        if (initialize_control_point) { // 如果控制点已初始化
            int64_t min_time = 1e18; // 初始化最小时间
            if (!imu_buff.empty()) min_time = imu_buff.back().time_ns; // 获取IMU缓冲区的时间
            if (!toa_buff.empty()) min_time = std::min(toa_buff.back().time_ns, min_time); // 获取TOA缓冲区的时间
            if (!tdoa_buff.empty()) min_time = std::min(tdoa_buff.back().time_ns, min_time); // 获取TDOA缓冲区的时间
            if (min_time > spline_local.nextMaxTimeNs()) { // 如果最小时间大于样条的最大时间
                Eigen::Quaterniond q_ini = spline_local.getKnotOrt(spline_local.numKnots() - 1); // 获取初始四元数
                Eigen::Quaterniond q_ini_backup = q_ini; // 备份初始四元数
                Eigen::Vector3d pos_ini = spline_local.getKnotPos(spline_local.numKnots() - 1); // 获取初始位置
                Eigen::Matrix<double, 6, 1> bias_ini = spline_local.getKnotBias(spline_local.numKnots() - 1); // 获取初始偏差
                if (!if_uwb_only) { // 如果不只使用UWB
                    if (spline_local.numKnots() <=2) { // 如果样条节点数小于等于2
                        last_imu_t_ns = bag_start_time; // 设置最后IMU时间为行李开始时间
                    } else {
                        last_imu_t_ns = imu_window.back().time_ns; // 获取IMU窗口的最后时间
                    }
                    integration(next_knot_TimeNs, q_ini, pos_ini); // 执行积分
                } else {
                    if (if_tdoa) { // 如果使用TDOA
                        pos_ini = tdoaMultilateration(next_knot_TimeNs * NS_TO_S); // 执行TDOA多边定位
                        q_ini  = Eigen::Quaterniond::Identity(); // 设置初始四元数为单位四元数
                    } else {
                        ROS_ERROR_STREAM("UWB-only tracking only supported for TDOA data!"); // 输出错误信息
                        exit(1); // 退出程序
                    }
                }
                if (q_ini_backup.dot(q_ini) < 0) q_ini = Eigen::Quaterniond(-q_ini.w(), -q_ini.x(), -q_ini.y(), -q_ini.z()); // 确保四元数方向一致
                spline_local.addOneStateKnot(q_ini, pos_ini, bias_ini); // 添加状态节点
                next_knot_TimeNs += dt_ns; // 更新下一个节点时间
                return true; // 返回成功
            } else {
                return false; // 返回失败
            }
        } else {
            if (!param_set) { // 如果参数未设置
                param_set = setParameters(); // 设置参数
                std_msgs::Int64 start_time; // 创建启动时间消息
                start_time.data = bag_start_time; // 设置启动时间
                pub_start_time.publish(start_time); // 发布启动时间
            }
            if (param_set && if_anchor_ini) { // 如果参数已设置且锚点已初始化
                spline_local.init(dt_ns, 0, bag_start_time); // 初始化样条
                if (!if_uwb_only) { // 如果不只使用UWB
                    Eigen::Vector3d gravity_sum(0, 0, 0); // 初始化重力和
                    size_t n_imu = imu_buff.size(); // 获取IMU缓冲区大小
                    for (size_t i = 0; i < n_imu; i++) { // 遍历IMU缓冲区
                        gravity_sum += imu_buff.at(i).accel; // 累加加速度
                    }
                    gravity_sum /= n_imu; // 计算平均重力
                    Eigen::Vector3d gravity_ave = gravity_sum.normalized() * 9.81; // 归一化重力
                    calib_param.gravity = gravity_ave; // 设置校准重力
                }
                calib_param.q_nav_uwb = param.q_nav_uwb_init; // 设置导航四元数
                calib_param.t_nav_uwb = param.t_nav_uwb_init; // 设置导航平移
                initialize_control_point = true; // 设置控制点初始化标志
                int num = 1; // 控制点数量
                for (int i = 0; i < num; i++) { // 添加控制点
                    Eigen::Quaterniond q_ini = Eigen::Quaterniond::Identity(); // 创建单位四元数
                    Eigen::Vector3d pos_ini = Eigen::Vector3d::Zero(); // 创建零位置
                    Eigen::Matrix<double, 6, 1> bias_ini = Eigen::Matrix<double, 6, 1>::Zero(); // 创建零偏差
                    spline_local.addOneStateKnot(q_ini, pos_ini, bias_ini); // 添加状态节点
                    next_knot_TimeNs += dt_ns; // 更新下一个节点时间
                }
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
        if (param.if_reject_uwb) { // 如果需要拒绝UWB
            if (solver_flag == INITIAL && spline_local.numKnots() < int (param.reject_uwb_window_width * window_size)) // 如果为初始状态且节点数小于拒绝窗口
                param.if_reject_uwb_in_optimization = false; // 不在优化中拒绝UWB
            else
                param.if_reject_uwb_in_optimization = true; // 在优化中拒绝UWB
        } else {
            param.if_reject_uwb_in_optimization = false; // 不拒绝UWB
        }
        if ((int) window_count >= n_window_calib) { // 如果窗口计数达到校准窗口数
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
        if (imu_buff.empty() && !if_uwb_only) return false; // 如果IMU缓冲区为空且不只使用UWB，返回失败
        if (imu_buff.empty() && toa_buff.empty() && tdoa_buff.empty()) { // 如果所有缓冲区都为空
            return false; // 返回失败
        } else {
            if (!imu_buff.empty()) { // 如果IMU缓冲区不为空
                bag_start_time += imu_buff.front().time_ns; // 更新行李开始时间
            } else if (!toa_buff.empty()) { // 如果TOA缓冲区不为空
                bag_start_time += toa_buff.front().time_ns; // 更新行李开始时间
            } else { // 如果TDOA缓冲区不为空
                bag_start_time += tdoa_buff.front().time_ns; // 更新行李开始时间
            }
        }
        next_knot_TimeNs = bag_start_time; // 设置下一个节点时间
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

    void integration(const int64_t curTime, Eigen::Quaterniond& qs, Eigen::Vector3d& Ps) // 积分函数
    {
        std::vector<ImuData> imu_vec; // IMU数据向量
        getIMUInterval(last_imu_t_ns, curTime, imu_vec); // 获取IMU时间区间数据
        if (!imu_vec.empty()) { // 如果IMU数据不为空
            Eigen::Quaterniond qs0; // 初始四元数
            spline_local.itpQuaternion(last_imu_t_ns, &qs0); // 获取插值四元数
            Eigen::Matrix3d Rs0(qs0); // 创建旋转矩阵
            Eigen::Vector3d Ps0 = spline_local.itpPosition(last_imu_t_ns); // 获取插值位置
            Eigen::Vector3d Vs0 = spline_local.itpPosition<1>(last_imu_t_ns); // 获取插值速度
            for(size_t i = 0; i < imu_vec.size(); i++) { // 遍历IMU数据
                int64_t dt; // 时间间隔
                int64_t t_ns = imu_vec[i].time_ns; // 获取时间戳
                if(i == 0) { // 如果是第一个数据
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

    bool getIMUInterval(int64_t t0, int64_t t1, std::vector<ImuData>& imu_vec) // 获取IMU时间区间数据
    {
        if(imu_buff.empty()) { // 如果IMU缓冲区为空
            printf("No IMU available. \n"); // 输出错误信息
            return false; // 返回失败
        }
        int idx = 0; // 初始化索引
        while(imu_buff.at(idx).time_ns <= std::min(imu_buff.back().time_ns, t1)) { // 遍历IMU缓冲区
            imu_vec.push_back(imu_buff.at(idx)); // 添加IMU数据到向量
            idx++; // 增加索引
            if(idx >= imu_buff.size()) break; // 如果索引超出范围，退出
        }
        return true; // 返回成功
    }

    void displayControlPoints() // 显示控制点函数
    {
        sensor_msgs::PointCloud points_inactive_msg; // 创建非活动控制点消息
        points_inactive_msg.header.frame_id = "map"; // 设置坐标系为地图
        points_inactive_msg.header.stamp.fromNSec(spline_local.minTimeNs()); // 设置时间戳
        points_inactive_msg.points.push_back(getPointMsg(spline_local.getIdlePos(0))); // 添加第一个非活动控制点
        points_inactive_msg.points.push_back(getPointMsg(spline_local.getIdlePos(1))); // 添加第二个非活动控制点
        points_inactive_msg.points.push_back(getPointMsg(spline_local.getIdlePos(2))); // 添加第三个非活动控制点
        sensor_msgs::PointCloud points_active_msg; // 创建活动控制点消息
        points_active_msg.header.frame_id = "map"; // 设置坐标系为地图
        points_active_msg.header.stamp.fromNSec(spline_local.minTimeNs()); // 设置时间戳
        for (size_t i = 0; i < spline_local.numKnots(); i++) { // 遍历样条节点
            points_active_msg.points.push_back(getPointMsg(spline_local.getKnotPos(i))); // 添加活动控制点
        }
        pub_knots_inactive.publish(points_inactive_msg); // 发布非活动控制点消息
        pub_knots_active.publish(points_active_msg); // 发布活动控制点消息
    }

    geometry_msgs::Point32 getPointMsg(Eigen::Vector3d p) // 获取点消息函数
    {
        geometry_msgs::Point32 p_msg; // 创建点消息
        Eigen::Vector3d p_U = calib_param.q_nav_uwb * p + calib_param.t_nav_uwb; // 计算校准后的点
        p_msg.x = p_U.x(); // 设置x坐标
        p_msg.y = p_U.y(); // 设置y坐标
        p_msg.z = p_U.z(); // 设置z坐标
        return p_msg; // 返回点消息
    }

    bool optimize(const int iter) // 优化函数
    {
        Linearizer lopt(bias_block_offset, gravity_block_offset, hess_size, &spline_local, &calib_param, &param, pose_fixed); // 创建线性化器
        if (!imu_window.empty()) lopt(imu_window); // 如果IMU窗口不为空，执行线性化
        if (!tdoa_window.empty()) lopt(tdoa_window); // 如果TDOA窗口不为空，执行线性化
        if (!toa_window.empty()) lopt(toa_window); // 如果TOA窗口不为空，执行线性化
        if (iter) { // 如果不是第一次迭代
            double gradient_max_norm = lopt.accum.getB().array().abs().maxCoeff(); // 获取梯度最大范数
            if (gradient_max_norm < 1e-8) return true; // 如果梯度足够小，返回收敛
        }
        lopt.accum.setup_solver(); // 设置求解器
        Eigen::VectorXd Hdiag = lopt.accum.Hdiagonal(); // 获取Hessian对角线
        bool stop = false; // 停止标志
        while (!stop) { // 迭代优化
            Eigen::VectorXd Hdiag_lambda = Hdiag * lambda; // 计算Hessian对角线与步长的乘积
            for (int i = 0; i < Hdiag_lambda.size(); i++) { // 遍历Hessian对角线
              Hdiag_lambda[i] = std::max(Hdiag_lambda[i], 1e-18); // 确保不小于阈值
            }
            Eigen::VectorXd inc_full = -lopt.accum.solve(&Hdiag_lambda); // 计算增量
            Eigen::aligned_deque<Eigen::Vector3d> knots_trans_backup; // 备份节点位置
            Eigen::aligned_deque<Eigen::Quaterniond> knots_rot_backup; // 备份节点旋转
            Eigen::aligned_deque<Eigen::Matrix<double, 6, 1>> knots_bias_backup; // 备份节点偏差
            spline_local.getAllStateKnots(knots_trans_backup, knots_rot_backup, knots_bias_backup); // 获取所有状态节点
            CalibParam calib_param_backup = calib_param; // 备份校准参数
            applyIncFull(inc_full); // 应用增量
            ComputeErrorSplineOpt eopt(&spline_local, &calib_param, &param); // 创建误差计算对象
            if (!toa_window.empty()) eopt(toa_window); // 计算TOA误差
            if (!imu_window.empty()) eopt(imu_window); // 计算IMU误差
            if (!tdoa_window.empty()) eopt(tdoa_window); // 计算TDOA误差
            double f_diff = lopt.error - eopt.error; // 计算误差差异
            double l_diff = 0.5 * inc_full.dot(inc_full *lambda - lopt.accum.getB()); // 计算增量差异
            double step_quality = f_diff / l_diff; // 计算步长质量
            if (step_quality < 0) { // 如果步长质量差
                lambda = std::min(100.0, lambda_vee * lambda); // 增加步长
                if (abs(lambda - 100.0) < 1e-3) { // 如果步长接近100
                    stop = true; // 停止优化
                }
                lambda_vee *= 2; // 步长倍增因子翻倍
                spline_local.setAllKnots(knots_trans_backup, knots_rot_backup, knots_bias_backup); // 恢复节点
                calib_param.setCalibParam(calib_param_backup); // 恢复校准参数
            } else {
                if (inc_full.norm()/((double)spline_local.numKnots()) < 1e-10 || abs(f_diff)/lopt.error < 1e-6) { // 如果增量足够小
                    stop = true; // 停止优化
                }
                lambda = std::max(1e-18, lambda * std::max(1.0 / 3, 1 - std::pow(2 * step_quality - 1, 3.0))); // 更新步长
                lambda_vee = 2; // 重置步长倍增因子
                break; // 退出循环
            }
        }
        return stop; // 返回停止状态
    }

    void updateLinearizerSize() // 更新线性化器大小
    {
        int num_knots = spline_local.numKnots(); // 获取样条节点数
        bias_block_offset = Linearizer::POSE_SIZE * num_knots; // 计算偏差块偏移
        hess_size = bias_block_offset; // 设置Hessian大小
        if (!if_uwb_only) { // 如果不只使用UWB
            hess_size += Linearizer::ACCEL_BIAS_SIZE * num_knots; // 添加加速度偏差大小
            hess_size += Linearizer::GYRO_BIAS_SIZE * num_knots; // 添加陀螺仪偏差大小
        }
        gravity_block_offset = hess_size; // 设置重力块偏移
        hess_size += Linearizer::G_SIZE; // 添加重力大小
        if (param.if_opt_transform) { // 如果需要优化变换
          hess_size += Linearizer::OFFSET_SIZE; // 添加偏移大小
          hess_size += Linearizer::ROTATION_SIZE; // 添加旋转大小
        }
    }

    void applyIncFull(Eigen::VectorXd& inc_full) // 应用增量函数
    {
        size_t num_knots = spline_local.numKnots(); // 获取样条节点数
        for (size_t i = 0; i < num_knots; i++) { // 遍历样条节点
          Eigen::Matrix<double, 6, 1> inc = inc_full.segment<Linearizer::POSE_SIZE>(Linearizer::POSE_SIZE * i); // 获取增量
          spline_local.applyPoseInc(i, inc); // 应用位姿增量
        }
        spline_local.checkQuaternionControlPoints(); // 检查四元数控制点
        if (!if_uwb_only) { // 如果不只使用UWB
            for (size_t i = 0; i < num_knots; i++) { // 遍历样条节点
                Eigen::Matrix<double, 6, 1> inc = inc_full.segment<Linearizer::BIAS_SIZE>(bias_block_offset + Linearizer::BIAS_SIZE * i); // 获取偏差增量
                spline_local.applyBiasInc(i, inc); // 应用偏差增量
            }
            spline_local.updateBiasIdleFirstWindow(); // 更新偏差
            if (param.if_opt_g) { // 如果需要优化重力
                Eigen::VectorXd dg = inc_full.segment<Linearizer::G_SIZE>(gravity_block_offset); // 获取重力增量
                Eigen::Vector3d g0 = (calib_param.gravity + Sphere::TangentBasis(calib_param.gravity) * dg).normalized() * 9.81; // 计算新的重力
                calib_param.gravity = g0; // 更新校准重力
            }
        }
        if (param.if_opt_transform) { // 如果需要优化变换
            calib_param.t_nav_uwb += inc_full.segment<Linearizer::OFFSET_SIZE>(gravity_block_offset + Linearizer::TRANS_OFFSET); // 更新导航偏移
            Eigen::Quaterniond q_inc; // 创建增量四元数
            Quater::exp(inc_full.segment<Linearizer::ROTATION_SIZE>(gravity_block_offset + Linearizer::ROTATION_OFFSET), q_inc); // 计算增量四元数
            calib_param.q_nav_uwb *= q_inc; // 更新导航四元数
        }
    }

};

int main(int argc, char *argv[]) // 主函数
{
    ros::init(argc, argv, "sfuise"); // 初始化ROS节点
    ROS_INFO("\033[1;32m---->\033[0m Starting SplineFusion."); // 输出启动信息
    ros::NodeHandle nh("~"); // 创建节点句柄
    SplineFusion estimator(nh); // 创建样条融合对象
    ros::Rate rate(1000); // 设置循环频率
    while (ros::ok()) { // 当ROS正常运行时
        ros::spinOnce(); // 处理回调
        estimator.run(); // 执行样条融合
        rate.sleep(); // 睡眠以保持频率
    }
    return 0; // 返回0，正常退出
}