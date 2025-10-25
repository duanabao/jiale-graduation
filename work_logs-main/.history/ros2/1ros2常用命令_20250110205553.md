### ros2常规命令
| 命令 | 说明 |
| --- | --- |
| `source /opt/ros/humble/setup.bash` | 设置ROS2环境变量,使系统能够找到ROS2的可执行文件、库文件和其他资源 |
| `source install/local_setup.sh` | 在项目编译后，设置当前工作空间的环境变量,使系统能够找到该工作空间下的功能包 |
| `colcon build` | 编译项目 |
| `ros2 launch <package_name> <launch_file>` | 启动ROS2的launch文件,用于同时启动多个节点和配置参数 |
| `ros2 launch webots_epuck  my_launch.py rviz:=true` | 启动自己的webots_epuck仿真环境,并同时启动rviz可视化工具 |
| `ros2 run <package_name> <executable_name>` | 运行ROS2节点,用于启动单个节点 |
| `ros2 run webots_demo camera_xyz2` | 运行自己编写的相机节点,用于获取深度相机数据 |
