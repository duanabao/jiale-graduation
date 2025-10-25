## 代码基本情况说明
### 复现代码源：https://github.com/KIT-ISAS/SFUISE
### 代码改动：将代码中的ros部分改为ros2
### 运行步骤
1. 运行`ros2 launch sfuise sfuise_test_isas-walk1.launch`
    - sfuise_test_isas-walk1.launch代码功能：
        - 启动rviz2
        - 发布tf静态坐标变换
        - 启动 EstimationInterface
        - 启动 SplineFusion
2. 运行`ros2 bag play src/dataset/ros2-walk1`
    - `ros2 bag info src/dataset/ros2-walk1`运行结果：
    ```
    Files:             ros2-walk1.db3
    Bag size:          3.1 MiB
    Storage id:        sqlite3
    Duration:          63.339656084s
    Start:             Oct  5 2022 16:47:53.401605086 (1664959673.401605086)
    End:               Oct  5 2022 16:48:56.741261170 (1664959736.741261170)
    Messages:          10917
    Topic information: Topic: /vive/transform/tracker_1_ref | Type: geometry_msgs/msg/TransformStamped | Count: 3168 | Serialization Format: cdr
                    Topic: /waveshare_sense_hat_b | Type: sensor_msgs/msg/Imu | Count: 4839 | Serialization Format: cdr
                    Topic: /rtls_flares | Type: isas_msgs/msg/RTLSStick | Count: 970 | Serialization Format: cdr
                    Topic: /rtls_pose | Type: geometry_msgs/msg/PoseStamped | Count: 970 | Serialization Format: cdr
                    Topic: /anchor_list | Type: isas_msgs/msg/Anchorlist | Count: 970 | Serialization Format: cdr
    ```
### 主体代码说明：
- 位置：
    - sfuise_ws/src/sfuise/src/EstimationInterface.cpp 
    - sfuise_ws/src/sfuise/src/SplineFusion.cpp
#### EstimationInterface节点
- main:
    ```
    int main(int argc, char *argv[])
    {
        rclcpp::init(argc, argv);
        auto node = std::make_shared<EstimationInterface>();
        rclcpp::Rate rate(1000); 
        rclcpp::executors::SingleThreadedExecutor executor;
        executor.add_node(node);

        while (rclcpp::ok()) {
            executor.spin_some(); // 处理回调
            rate.sleep();
        }

        rclcpp::shutdown();
        return 0;
    }
    ```
- EstimationInterface类：

    | 节点订阅话题 | 话题名 |话题发布者| 情况说明 |
    | --- | --- | --- | --- |
    | 启动时间 | "/start_time" | 由SplineFusion节点发布 | 能正常接收，接收后初始化样条 |
    | IMU数据 | "/waveshare_sense_hat_b" | 由bag发布 |能正常接收|
    | UWB数据 | "/rtls_flares" | 由bag发布 |能正常接收|
    | 锚点列表 | "/anchor_list" | 由bag发布 |能正常接收|
    |真实位资信息|"/vive/transform/tracker_1_ref"| 由bag发布 |能正常接收|
    |系统标定数据|"/sys_calib"|由SplineFusion节点发布|**不能接收**|
    |估计窗口数据|"/est_window"|由SplineFusion节点发布|**不能接收**|

    | 节点发布话题 | 话题名 |情况说明|
    | --- | --- | --- |
    | IMU数据 | "/imu_ds" |能检测到发出|
    |UWB数据|"/toa_ds"|能检测到发出|
    |锚点可视化点云|"/visualization_anchor"|能检测到发出|
    |锚点列表|"/anchor_list"|能检测到发出|
    |旧的B样条优化路径(坐标系为map)|"/bspline_optimization_old"|**不能检测到**：由于未接收的est_window话题|
    |当前B样条优化窗口|"/bspline_optimization_window"|**不能检测到**：由于未接收的est_window话题|
    |优化位姿的可视化标记|"/opt_pose"|**不能检测到**：由于未接收的est_window话题|

#### SplineFusion节点
- main:
    ```
    int main(int argc, char *argv[]) 
    {
        rclcpp::init(argc, argv);
        auto node = std::make_shared<SplineFusion>();
        rclcpp::Rate rate(1000); 
        rclcpp::executors::SingleThreadedExecutor executor;
        executor.add_node(node);

        while (rclcpp::ok()) {
            executor.spin_some(); // 处理回调
            node->run(); //运行样条更新
            rate.sleep();
        }

        rclcpp::shutdown();
        return 0;
    }
    ```
- SplineFusion类：

    | 节点订阅话题 | 话题名 |话题发布者|情况说明|
    | --- | --- | --- | --- |
    |IMU数据|"/imu_ds"| 由EstimationInterface节点发布|能正常接收，收到后添加到imu_buff缓冲区|
    |锚点列表|"/anchor_list"|由EstimationInterface节点发布|能正常接收，收到后添加节点列表并设置toa偏移量|
    |UWB数据|"/toa_ds"|由EstimationInterface节点发布|能正常接收，收到后添加toa数据对象到toa_buff缓冲区|
    

    | 节点发布话题 | 话题名 |情况说明|
    | --- | --- | --- |
    |活动控制点的点云消息|"/active_control_points"|**不能检测到**|
    |非活动控制点的点云消息|"/inactive_control_points"|**不能检测到**|
    |窗口校准消息|"/sys_calib"|**不能检测到**|
    |估计窗口样条消息|"/est_window"|**不能检测到**|
    |启动时间消息|"/start_time"|**不能检测到**|

- run()：SplineFusion的公共方法
    1. 初始化initialization(),成功后才会做下面的事情，~~**一直没有成功初始化**~~
    2. 发布"active_control_points"和"inactive_control_points"话题
    3. 优化样条函数
    4. 窗口数++
    4. 窗口数<=标准窗口数50
        - 发布"sys_calib"话题
    5. 样条节点数spline_local.numKnots()达到窗口大小100,进行
        - 增加窗口数
        - 求解器标志设为全尺寸状态：solver_flag = FULLSIZE; 
    6. 发布"est_window"话题，发布"active_control_points"和"inactive_control_points"话题
    7. 如果solver_flag为全尺寸状态，移除一个旧状态：spline_local.removeOneOldState();

- initialization()
    1. 未设置参数
        - 如果IMU缓冲区有数据，bag_start_time=imu_buff（IMU数据缓冲区）中第一个元素的 time_ns（时间戳，单位为纳秒），~~**数据过大**~~
    2. 设置参数完成且接收到"/anchor_list"
        - 初始化样条
        - 设置calib_param参数:校准重力，导航四元数，导航平移
        - 添加一个初始控制点
    3. 完成控制点初始化后
        - 插入控制点

- imu_buff缓冲区的时间戳情况
    - **开始三个数据的时间戳异常**
    - 跳过这三个数据
    - uwb同理，跳过5个数据

- displayControlPoints()



## 问题
1. 时间戳问题：已解决
2. 
```
[SplineFusion-4] CHOLMOD warning: matrix not positive definite. file: ../Supernodal/t_cholmod_super_numeric.c line: 911
```

