#include <ros/ros.h> // 引入ROS库
#include <fstream> // 引入文件流库
#include "../include/SplineState.h" // 引入自定义的SplineState类
#include "../include/utils/PoseVisualization.h" // 引入自定义的PoseVisualization类
#include "sensor_msgs/Imu.h" // 引入IMU传感器消息类型
#include "geometry_msgs/TransformStamped.h" // 引入变换消息类型
#include "geometry_msgs/PoseWithCovarianceStamped.h" // 引入带协方差的位姿消息类型
#include "nav_msgs/Path.h" // 引入路径消息类型
#include "cf_msgs/Tdoa.h" // 引入TDOA消息类型
#include "isas_msgs/RTLSRange.h" // 引入RTLS范围消息类型
#include "isas_msgs/RTLSStick.h" // 引入RTLS Stick消息类型
#include "isas_msgs/AnchorPosition.h" // 引入锚点位置消息类型
#include "isas_msgs/Anchorlist.h" // 引入锚点列表消息类型
#include "sensor_msgs/PointCloud.h" // 引入点云消息类型
#include "sfuise_msgs/Spline.h" // 引入样条消息类型
#include "sfuise_msgs/Estimate.h" // 引入估计消息类型
#include "sfuise_msgs/Calib.h" // 引入标定消息类型
#include "std_msgs/Int64.h" // 引入64位整数消息类型

class EstimationInterface // 定义估计接口类
{
  public:
    EstimationInterface(ros::NodeHandle& nh) // 构造函数，接收ROS节点句柄
    {
        initialized_anchor = false; // 初始化锚点状态为未初始化
        if_nav_uwb = false; // 初始化导航UWB状态为未启用
        readParamsInterface(nh); // 读取参数配置
        sub_start = nh.subscribe("/SplineFusion/start_time", 1000, &EstimationInterface::startCallBack, this); // 订阅启动时间话题
        std::string imu_type = CommonUtils::readParam<std::string>(nh, "topic_imu"); // 读取IMU话题类型
        sub_imu = nh.subscribe(imu_type, 400, &EstimationInterface::getImuCallback, this); // 订阅IMU数据
        pub_imu = nh.advertise<sensor_msgs::Imu>("imu_ds", 400); // 发布IMU数据
        std::string uwb_type = CommonUtils::readParam<std::string>(nh, "topic_uwb"); // 读取UWB话题类型
        if (!uwb_type.compare("/tdoa_data")) { // 如果是TDOA数据
            sub_uwb = nh.subscribe(uwb_type, 400, &EstimationInterface::getTdoaUTILCallback, this); // 订阅TDOA数据
            pub_uwb = nh.advertise<cf_msgs::Tdoa>("tdoa_ds", 400); // 发布TDOA数据
        } else if (!uwb_type.compare("/rtls_flares")) { // 如果是RTLS Flares数据
            sub_uwb = nh.subscribe(uwb_type, 400, &EstimationInterface::getToaISASCallback, this); // 订阅RTLS数据
            pub_uwb = nh.advertise<isas_msgs::RTLSStick>("toa_ds", 400); // 发布RTLS数据
        } else {
            ROS_ERROR_STREAM("Wrong UWB format!"); // 错误处理：UWB格式错误
        }
        std::string anchor_type = CommonUtils::readParam<std::string>(nh, "topic_anchor_list"); // 读取锚点列表话题类型
        if (!if_tdoa) { // 如果不是TDOA模式
            if (!anchor_type.compare("/anchor_list")) { // 如果锚点列表话题正确
                sub_anchor = nh.subscribe(anchor_type, 400, &EstimationInterface::getAnchorListFromISASCallback, this); // 订阅锚点列表
            } else {
                ROS_ERROR_STREAM("Anchor list not available!"); // 错误处理：锚点列表不可用
            }
        }
        anchor_pos_pub = nh.advertise<sensor_msgs::PointCloud>("visualization_anchor", 1000); // 发布锚点可视化点云
        anchor_pub = nh.advertise<isas_msgs::Anchorlist>("anchor_list", 1000); // 发布锚点列表
        timer_anchor = nh.createTimer(ros::Duration(1/100), std::bind(&EstimationInterface::publishAnchor, this)); // 创建定时器以定期发布锚点
        std::string gt_type = CommonUtils::readParam<std::string>(nh, "topic_ground_truth"); // 读取地面真实话题类型
        if (!gt_type.compare("/vive/transform/tracker_1_ref")) { // 如果是VIVE跟踪器数据
            sub_gt = nh.subscribe(gt_type, 1000, &EstimationInterface::getGtFromISASCallback, this); // 订阅VIVE数据
        } else if (!gt_type.compare("/pose_data")) { // 如果是位姿数据
            sub_gt = nh.subscribe(gt_type, 1000, &EstimationInterface::getGtFromUTILCallback, this); // 订阅位姿数据
        }
        int control_point_fps = CommonUtils::readParam<int>(nh, "control_point_fps"); // 读取控制点帧率
        dt_ns = 1e9 / control_point_fps; // 计算时间间隔（纳秒）
        sub_calib = nh.subscribe("/SplineFusion/sys_calib", 100, &EstimationInterface::getCalibCallback, this); // 订阅系统标定数据
        sub_est = nh.subscribe("/SplineFusion/est_window", 100, &EstimationInterface::getEstCallback, this); // 订阅估计窗口数据
        pub_opt_old = nh.advertise<nav_msgs::Path>("bspline_optimization_old", 1000); // 发布旧的B样条优化路径
        pub_opt_window = nh.advertise<nav_msgs::Path>("bspline_optimization_window", 1000); // 发布当前B样条优化窗口
        opt_old_path.header.frame_id = "map"; // 设置旧路径的坐标系为地图
        pub_opt_pose = nh.advertise<visualization_msgs::Marker>("opt_pose", 1000); // 发布优化位姿的可视化标记
        opt_pose_vis.setColor(85.0/255.0, 164.0/255.0, 104.0/255.0); // 设置优化位姿可视化的颜色
    }

private:
    // 成员变量定义
    int64_t dt_ns; // 时间间隔（纳秒）
    bool initialized_anchor; // 锚点初始化状态
    bool if_tdoa; // 是否启用TDOA
    bool if_nav_uwb; // 是否启用导航UWB
    CalibParam calib_param; // 标定参数
    Eigen::aligned_vector<PoseData> gt; // 地面真实数据
    Eigen::aligned_map<uint16_t, Eigen::Vector3d> anchor_list; // 锚点列表
    double imu_sample_coeff; // IMU采样系数
    double uwb_sample_coeff; // UWB采样系数
    double imu_frequency; // IMU频率
    double uwb_frequency; // UWB频率
    double average_runtime; // 平均运行时间
    bool gyro_unit; // 陀螺仪单位
    bool acc_ratio; // 加速度比
    SplineState spline_global; // 全局样条状态
    Eigen::aligned_vector<PoseData> opt_old; // 旧的优化数据
    Eigen::aligned_vector<PoseData> opt_window; // 当前优化窗口数据
    ros::Timer timer_anchor; // 定时器
    ros::Subscriber sub_imu; // IMU订阅者
    ros::Subscriber sub_uwb; // UWB订阅者
    ros::Subscriber sub_anchor; // 锚点订阅者
    ros::Subscriber sub_gt; // 地面真实订阅者
    ros::Subscriber sub_calib; // 标定订阅者
    ros::Subscriber sub_est; // 估计订阅者
    ros::Subscriber sub_start; // 启动订阅者
    ros::Publisher pub_imu; // IMU发布者
    ros::Publisher pub_uwb; // UWB发布者
    ros::Publisher anchor_pos_pub; // 锚点位置发布者
    ros::Publisher anchor_pub; // 锚点列表发布者
    ros::Publisher pub_opt_old; // 旧优化路径发布者
    ros::Publisher pub_opt_window; // 当前优化窗口发布者
    ros::Publisher pub_opt_pose; // 优化位姿发布者
    nav_msgs::Path opt_old_path; // 旧路径
    PoseVisualization opt_pose_vis; // 优化位姿可视化对象

    void readParamsInterface(ros::NodeHandle& nh) // 读取参数配置的函数
    {
        if_tdoa = CommonUtils::readParam<bool>(nh, "if_tdoa"); // 读取是否启用TDOA参数
        imu_sample_coeff = CommonUtils::readParam<double>(nh, "imu_sample_coeff"); // 读取IMU采样系数
        uwb_sample_coeff = CommonUtils::readParam<double>(nh, "uwb_sample_coeff"); // 读取UWB采样系数
        imu_frequency = CommonUtils::readParam<double>(nh, "imu_frequency"); // 读取IMU频率
        uwb_frequency = CommonUtils::readParam<double>(nh, "uwb_frequency"); // 读取UWB频率
        gyro_unit = CommonUtils::readParam<bool>(nh, "gyro_unit"); // 读取陀螺仪单位参数
        acc_ratio = CommonUtils::readParam<bool>(nh, "acc_ratio"); // 读取加速度比参数
        if (uwb_sample_coeff == 0) { // 检查UWB采样系数是否为0
            ROS_ERROR_STREAM("Parameter 'uwb_sample_coeff' cannot be 0!"); // 错误处理：UWB采样系数不能为0
            nh.shutdown(); // 关闭节点
        }
        if (if_tdoa) { // 如果启用TDOA
            std::string anchor_path = CommonUtils::readParam<std::string>(nh, "anchor_path"); // 读取锚点路径
            getAnchorListFromUTIL(anchor_path); // 从文件获取锚点列表
        }
    }

    void getEstCallback(const sfuise_msgs::Estimate::ConstPtr& est_msg) // 估计回调函数
    {
        sfuise_msgs::Spline spline_msg = est_msg->spline; // 获取样条消息
        SplineState spline_w; // 创建样条状态对象
        spline_w.init(spline_msg.dt, 0, spline_msg.start_t, spline_msg.start_idx); // 初始化样条状态
        for(const auto knot : spline_msg.knots) { // 遍历样条节点
            Eigen::Vector3d pos(knot.position.x, knot.position.y, knot.position.z); // 获取位置
            Eigen::Quaterniond quat(knot.orientation.w, knot.orientation.x, knot.orientation.y, knot.orientation.z); // 获取方向
            Eigen::Matrix<double, 6, 1> bias; // 创建偏置矩阵
            bias << knot.bias_acc.x, knot.bias_acc.y, knot.bias_acc.z, // 设置加速度偏置
                    knot.bias_gyro.x, knot.bias_gyro.y, knot.bias_gyro.z; // 设置陀螺仪偏置
            spline_w.addOneStateKnot(quat, pos, bias); // 添加样条节点
        }
        for (int i = 0; i < 3; i++) { // 遍历空闲节点
            sfuise_msgs::Knot idle = spline_msg.idles[i]; // 获取空闲节点
            Eigen::Vector3d t_idle(idle.position.x, idle.position.y, idle.position.z); // 获取空闲节点位置
            Eigen::Quaterniond q_idle(idle.orientation.w, idle.orientation.x, idle.orientation.y, idle.orientation.z); // 获取空闲节点方向
            Eigen::Matrix<double, 6, 1> b_idle; // 创建空闲节点偏置矩阵
            b_idle << idle.bias_acc.x, idle.bias_acc.y, idle.bias_acc.z, idle.bias_gyro.x, idle.bias_gyro.y, idle.bias_gyro.z; // 设置偏置
            spline_w.setIdles(i, t_idle, q_idle, b_idle); // 设置空闲节点
        }
        spline_global.updateKnots(&spline_w); // 更新全局样条节点
        if (if_nav_uwb) pubOpt(spline_w, !est_msg->if_full_window.data); // 如果启用导航UWB，发布优化
        average_runtime = est_msg->runtime.data; // 更新平均运行时间
    }

    void pubOpt(SplineState& spline_local, const bool if_window_full) // 发布优化函数
    {
        int64_t min_t = spline_local.minTimeNs(); // 获取样条最小时间
        int64_t max_t = spline_local.maxTimeNs(); // 获取样条最大时间
        static int cnt = 0; // 计数器
        if (!if_window_full) { // 如果窗口未满
            for (auto v: opt_window) { // 遍历优化窗口
                if (v.time_ns < min_t) { // 如果时间小于最小时间
                    opt_old.push_back(v); // 将数据添加到旧优化数据
                    opt_old_path.poses.push_back(CommonUtils::pose2msg(v.time_ns, v.pos, v.orient)); // 添加到旧路径
                }
            }
        } else {
            cnt = 0; // 重置计数器
        }
        opt_window.clear(); // 清空优化窗口
        nav_msgs::Path opt_window_path; // 创建优化窗口路径
        opt_window_path.header.frame_id = "map"; // 设置坐标系为地图
        for (size_t i = cnt; i < gt.size(); i++) { // 遍历地面真实数据
            int64_t t_ns = gt.at(i).time_ns; // 获取时间戳
            if (t_ns < min_t) { // 如果时间小于最小时间
                cnt = i; // 更新计数器
                continue; // 继续下一个循环
            } else if (t_ns > max_t) { // 如果时间大于最大时间
                break; // 退出循环
            }
            PoseData pose_tf = getPoseInUWB(spline_local, t_ns); // 获取UWB中的位姿
            opt_window.push_back(pose_tf); // 添加到优化窗口
            opt_window_path.poses.push_back(CommonUtils::pose2msg(t_ns, pose_tf.pos, pose_tf.orient)); // 添加到优化窗口路径
        }
        pub_opt_old.publish(opt_old_path); // 发布旧优化路径
        pub_opt_window.publish(opt_window_path); // 发布当前优化窗口路径
        opt_pose_vis.pubPose(opt_window.back().pos, opt_window.back().orient, pub_opt_pose, opt_window_path.header); // 发布优化位姿可视化
     }

    void getImuCallback(const sensor_msgs::Imu::ConstPtr& imu_msg) // IMU回调函数
    {
        static int64_t last_imu = 0; // 上一个IMU时间戳
        int64_t t_ns = imu_msg->header.stamp.toNSec(); // 获取当前时间戳
        if (sampleData(t_ns, last_imu, imu_sample_coeff, imu_frequency)) { // 检查是否需要采样
            Eigen::Vector3d acc(imu_msg->linear_acceleration.x, imu_msg->linear_acceleration.y, imu_msg->linear_acceleration.z); // 获取加速度
            if (acc_ratio) acc *= 9.81; // 如果启用加速度比，转换为米每二次方秒
            Eigen::Vector3d gyro(imu_msg->angular_velocity.x, imu_msg->angular_velocity.y, imu_msg->angular_velocity.z); // 获取陀螺仪数据
            if (gyro_unit) gyro *= M_PI / 180.0; // 如果启用陀螺仪单位，转换为弧度
            last_imu = t_ns; // 更新上一个IMU时间戳
            sensor_msgs::Imu imu_ds_msg; // 创建IMU数据消息
            imu_ds_msg.header = imu_msg->header; // 设置消息头
            imu_ds_msg.linear_acceleration.x = acc[0]; // 设置线性加速度
            imu_ds_msg.linear_acceleration.y = acc[1];
            imu_ds_msg.linear_acceleration.z = acc[2];
            imu_ds_msg.angular_velocity.x = gyro[0]; // 设置角速度
            imu_ds_msg.angular_velocity.y = gyro[1];
            imu_ds_msg.angular_velocity.z = gyro[2];
            pub_imu.publish(imu_ds_msg); // 发布IMU数据
        }
    }

    void getCalibCallback(const sfuise_msgs::Calib::ConstPtr& calib_msg) // 标定回调函数
    {
        if_nav_uwb = true; // 启用导航UWB
        calib_param.q_nav_uwb = Eigen::Quaterniond(calib_msg->q_nav_uwb.w, calib_msg->q_nav_uwb.x, calib_msg->q_nav_uwb.y, calib_msg->q_nav_uwb.z); // 设置导航UWB的四元数
        calib_param.t_nav_uwb = Eigen::Vector3d(calib_msg->t_nav_uwb.x, calib_msg->t_nav_uwb.y, calib_msg->t_nav_uwb.z); // 设置导航UWB的平移向量
        calib_param.gravity = Eigen::Vector3d(calib_msg->gravity.x, calib_msg->gravity.y, calib_msg->gravity.z); // 设置重力向量
        calib_param.offset = Eigen::Vector3d(calib_msg->t_tag_body_set.x, calib_msg->t_tag_body_set.y, calib_msg->t_tag_body_set.z); // 设置标签身体的偏移
    }

    void getToaISASCallback(const isas_msgs::RTLSStick::ConstPtr& uwb_msg) // RTLS Stick回调函数
    {
        static int64_t last_uwb = 0; // 上一个UWB时间戳
        int64_t t_ns = uwb_msg->header.stamp.toNSec(); // 获取当前时间戳
        if (sampleData(t_ns, last_uwb, uwb_sample_coeff, uwb_frequency)) { // 检查是否需要采样
            for (const auto& rg : uwb_msg->ranges) { // 遍历范围数据
                if (rg.ra == 0) continue; // 如果范围为0，跳过
            }
            pub_uwb.publish(uwb_msg); // 发布UWB数据
            last_uwb = t_ns; // 更新上一个UWB时间戳
        }
    }

    void getTdoaUTILCallback(const cf_msgs::Tdoa::ConstPtr& msg) // TDOA回调函数
    {
        static int64_t last_uwb = 0; // 上一个UWB时间戳
        int64_t t_ns = msg->header.stamp.toNSec(); // 获取当前时间戳
        if (sampleData(t_ns, last_uwb, uwb_sample_coeff, uwb_frequency)) { // 检查是否需要采样
            int idA = msg->idA; // 获取ID A
            int idB = msg->idB; // 获取ID B
            pub_uwb.publish(*msg); // 发布TDOA数据
            last_uwb = t_ns; // 更新上一个UWB时间戳
        }
    }

    void getGtFromISASCallback(const geometry_msgs::TransformStampedConstPtr& gt_msg) // 从ISAS获取地面真实数据的回调函数
    {
        Eigen::Quaterniond q(gt_msg->transform.rotation.w, gt_msg->transform.rotation.x,
                             gt_msg->transform.rotation.y, gt_msg->transform.rotation.z); // 获取四元数
        Eigen::Vector3d pos(gt_msg->transform.translation.x, gt_msg->transform.translation.y, gt_msg->transform.translation.z); // 获取位置
        PoseData pose(gt_msg->header.stamp.toNSec(), q, pos); // 创建位姿数据
        gt.push_back(pose); // 添加到地面真实数据
    }

    void getGtFromUTILCallback(const geometry_msgs::PoseWithCovarianceStampedConstPtr& gt_msg) // 从UTIL获取地面真实数据的回调函数
    {
        Eigen::Quaterniond q(gt_msg->pose.pose.orientation.w, gt_msg->pose.pose.orientation.x,
                             gt_msg->pose.pose.orientation.y, gt_msg->pose.pose.orientation.z); // 获取四元数
        Eigen::Vector3d pos(gt_msg->pose.pose.position.x, gt_msg->pose.pose.position.y, gt_msg->pose.pose.position.z); // 获取位置
        PoseData pose(gt_msg->header.stamp.toNSec(), q, pos); // 创建位姿数据
        gt.push_back(pose); // 添加到地面真实数据
    }

    void getAnchorListFromISASCallback(const isas_msgs::Anchorlist::ConstPtr &anchor_msg) // 从ISAS获取锚点列表的回调函数
    {
        if (initialized_anchor) return; // 如果锚点已初始化，返回
        int num_sum = 20; // 定义锚点数量
        static int cnt = 0; // 计数器
        for (const auto& anchor : anchor_msg->anchor) { // 遍历锚点
            Eigen::Vector3d anchor_pos(anchor.position.x, anchor.position.y, anchor.position.z); // 获取锚点位置
            uint16_t anchor_id = anchor.id; // 获取锚点ID
            if (cnt == 0) { // 如果是第一个锚点
                anchor_list[anchor_id] = anchor_pos; // 添加到锚点列表
            } else {
                Eigen::Vector3d ave_pos = anchor_list[anchor_id]; // 获取已有锚点位置
                anchor_list[anchor_id] = (ave_pos * cnt + anchor_pos) / (cnt + 1); // 更新锚点位置为平均值
                anchor_pos = anchor_list[anchor_id]; // 更新锚点位置
            }
        }
        cnt++; // 增加计数器
        if (cnt >= num_sum) { // 如果计数器达到设定数量
            initialized_anchor = true; // 设置锚点为已初始化
            publishAnchor(); // 发布锚点
        }
    }

    void getAnchorListFromUTIL(const std::string& anchor_path) // 从文件获取锚点列表的函数
    {
        std::string line; // 行缓冲
        std::ifstream infile; // 文件输入流
        infile.open(anchor_path); // 打开文件
        if (!infile) { // 检查文件是否成功打开
            std::cerr << "Unable to open file: " << anchor_path << std::endl; // 错误处理：无法打开文件
            exit(1); // 退出程序
        }
        while (std::getline(infile, line)) { // 逐行读取文件
            std::istringstream iss(line); // 创建字符串流
            char comma, tmp, tmp2; // 定义临时变量
            int anchor_id; // 锚点ID
            double x, y, z; // 锚点坐标
            iss >> tmp >> tmp >> anchor_id >> tmp >> tmp2 >> comma >> x >> comma >> y >> comma >> z; // 解析行数据
            if (tmp2 == 'p') { // 如果是有效的锚点
                anchor_list[anchor_id] = Eigen::Vector3d(x, y, z); // 添加到锚点列表
            }
        }
        infile.close(); // 关闭文件
        initialized_anchor = true; // 设置锚点为已初始化
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
        if (!initialized_anchor) { // 如果锚点未初始化
            return; // 返回
        } else {
            isas_msgs::Anchorlist anchor_list_msg; // 创建锚点列表消息
            for (auto it = anchor_list.begin(); it != anchor_list.end(); it++) { // 遍历锚点列表
                isas_msgs::AnchorPosition anchor; // 创建锚点位置消息
                Eigen::Vector3d pos = it->second; // 获取锚点位置
                anchor.position.x = pos[0]; // 设置锚点位置
                anchor.position.y = pos[1];
                anchor.position.z = pos[2];
                anchor.id = it->first; // 设置锚点ID
                anchor_list_msg.anchor.push_back(anchor); // 添加到锚点列表消息
            }
            anchor_pub.publish(anchor_list_msg); // 发布锚点列表消息
            sensor_msgs::PointCloud anchors; // 创建点云消息
            anchors.header.frame_id = "map"; // 设置坐标系为地图
            anchors.header.stamp = ros::Time::now(); // 设置时间戳
            for (auto it = anchor_list.begin(); it != anchor_list.end(); it++) { // 遍历锚点列表
                Eigen::Matrix<double, 3, 1> pos = it->second; // 获取锚点位置
                geometry_msgs::Point32 p; // 创建点
                p.x = pos[0]; // 设置点坐标
                p.y = pos[1];
                p.z = pos[2];
                anchors.points.push_back(p); // 添加到点云
            }
            anchor_pos_pub.publish(anchors); // 发布点云消息
        }
    }

    void startCallBack(const std_msgs::Int64::ConstPtr& start_time_msg) // 启动回调函数
    {
        int64_t bag_start_time = start_time_msg->data; // 获取启动时间
        spline_global.init(dt_ns, 0, bag_start_time); // 初始化全局样条
    }

    PoseData getPoseInUWB(SplineState& spline, int64_t t_ns) // 获取UWB中的位姿的函数
    {
        Eigen::Quaterniond orient_interp; // 创建四元数
        Eigen::Vector3d t_interp = spline.itpPosition(t_ns); // 获取插值位置
        spline.itpQuaternion(t_ns, &orient_interp); // 获取插值方向
        Eigen::Quaterniond q = calib_param.q_nav_uwb * orient_interp; // 计算最终方向
        Eigen::Vector3d t = calib_param.q_nav_uwb * (orient_interp * calib_param.offset + t_interp) + calib_param.t_nav_uwb; // 计算最终位置
        return PoseData(t_ns, q, t); // 返回位姿数据
    }
};

int main(int argc, char *argv[]) // 主函数
{
    ros::init(argc, argv, "sfuise"); // 初始化ROS节点
    ROS_INFO("\033[1;32m---->\033[0m Starting EstimationInterface."); // 输出启动信息
    ros::NodeHandle nh("~"); // 创建节点句柄
    EstimationInterface interface(nh); // 创建估计接口对象
    ros::Rate rate(1000); // 设置循环频率
    while (ros::ok()) { // 当ROS正常运行时
        ros::spinOnce(); // 处理回调
        rate.sleep(); // 睡眠以保持频率
    }
    return 0; // 返回0，正常退出
}
