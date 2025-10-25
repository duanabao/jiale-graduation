#!/usr/bin/env python

# 版权所有 1996-2023 Cyberbotics Ltd.
#
# 根据 Apache 许可证第 2.0 版（“许可证”）进行许可；
# 除非遵守许可证，否则您不得使用此文件。
# 您可以在以下网址获取许可证的副本：
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# 除非适用法律或书面同意，否则根据许可证分发的软件是按“原样”基础提供的，
# 不提供任何形式的保证或条件。
# 请参阅许可证以获取特定语言下的权限和限制。

"""启动 Rat's Life 世界，并使机器人自主移动以绘制环境地图。"""

import os
import json
from math import pi, sin, cos
from launch.substitutions import LaunchConfiguration
from launch.actions import DeclareLaunchArgument
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch import LaunchDescription
from ament_index_python.packages import get_package_share_directory
from launch_ros.actions import Node
from launch.actions import ExecuteProcess
from geometry_msgs.msg import Quaternion


class WaypointCollection:
    """根据每个点定义的 [x, y, theta] 参数创建与 Navigation2 兼容的航点列表。"""

    def __init__(self, frame_id='odom'):
        self.__waypoints = {'poses': []}  # 初始化航点列表
        self.__frame_id = frame_id  # 设置坐标框架 ID

    def add(self, position=None, orientation=None):
        if orientation is not None:
            q = Quaternion()  # 创建四元数对象
            q.z = sin(orientation / 2)  # 计算四元数的 z 分量
            q.w = cos(orientation / 2)  # 计算四元数的 w 分量
            orientation = {'x': q.x, 'y': q.y, 'z': q.z, 'w': q.w}  # 设置方向
        if position is not None:
            position = {'x': position[0], 'y': position[1], 'z': 0}  # 设置位置
        if position is None:
            position = self.__waypoints['poses'][-1]['pose']['position']  # 获取上一个位置
        if orientation is None:
            orientation = self.__waypoints['poses'][-1]['pose']['orientation']  # 获取上一个方向

        self.__waypoints['poses'].append({
            'header': {'frame_id': self.__frame_id},  # 添加头部信息
            'pose': {
                'orientation': orientation,  # 添加方向
                'position': position  # 添加位置
            }
        })

    def export(self):
        return json.dumps(self.__waypoints)  # 导出为 JSON 字符串


def get_waypoints():
    """向 `WaypointCollection` 添加航点列表并返回与 Navigation2 兼容的 JSON 字符串。"""
    collection = WaypointCollection()  # 创建航点集合

    collection.add(position=[0, 0], orientation=0)      # 初始姿态
    collection.add(orientation=-pi/2)                   # 探索大厅，旋转
    collection.add(orientation=0)                       # 探索大厅，旋转
    collection.add(position=[0.28, 0], orientation=0)   # 移动到红色入口附近
    collection.add(orientation=pi/2)                    # 旋转朝向红色
    collection.add(position=[0.28, 0.2])                # 移动到红色内部
    collection.add(orientation=0)                       # 探索红色，旋转
    collection.add(orientation=-pi)                     # 探索红色，旋转
    collection.add(orientation=-pi/2)                   # 旋转朝向蓝色
    collection.add(position=[0.23, -0.2])               # 移动到蓝色内部
    collection.add(orientation=0)                       # 探索蓝色，旋转
    collection.add(orientation=pi/3)                    # 探索蓝色，旋转
    collection.add(orientation=-pi/2)                   # 探索蓝色，旋转
    collection.add(orientation=-2.7*pi)                 # 探索蓝色，旋转
    collection.add(orientation=pi/2)                    # 旋转朝向大厅
    collection.add(position=[0.23, 0])                  # 前往大厅
    collection.add(orientation=1/3*pi)                  # 探索大厅，旋转
    collection.add(orientation=pi)                      # 旋转朝向后方
    collection.add(position=[-0.1, 0])                  # 前往绿色入口
    collection.add(orientation=pi/2)                    # 探索大厅，旋转
    collection.add(orientation=pi/4)                    # 探索大厅，旋转
    collection.add(orientation=2/3*pi)                  # 探索大厅，旋转
    collection.add(orientation=-pi/2)                   # 旋转朝向绿色
    collection.add(position=[-0.1, -0.2])               # 移动到绿色内部
    collection.add(orientation=0)                       # 探索绿色，旋转
    collection.add(orientation=pi/3)                    # 探索绿色，旋转
    collection.add(orientation=-pi/2)                   # 探索绿色，旋转
    collection.add(orientation=3/4*pi)                  # 探索绿色，旋转

    return collection.export()  # 返回航点的 JSON 字符串


def generate_launch_description():
    package_dir = get_package_share_directory('webots_epuck')  # 获取包的共享目录
    use_sim_time = LaunchConfiguration('use_sim_time', default=True)  # 使用仿真时间
    world = LaunchConfiguration('world', default='epuck_world.wbt')  # 设置世界文件

    # Webots
    webots_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(package_dir, 'launch', 'my_launch.py')  # 包含 Webots 启动文件
        ),
        launch_arguments={
            'use_sim_time': 'true',
            'world': world  # 启动参数
        }.items()
    )

    # 启动 Navigation2，不进行定位和不使用代价地图。
    # 由于该启动文件仅用于映射比较（真实与物理），我们希望严格遵循航点
    # （不进行障碍物规避）。
    # 这样，映射质量不会因不同路径而受到影响。
    nav2 = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(get_package_share_directory('nav2_bringup'), 'launch', 'navigation_launch.py')  # 包含导航启动文件
        ),
        launch_arguments=[
            ('use_sim_time', use_sim_time),  # 启用仿真时间
            ('params_file', os.path.join(package_dir, 'resource', 'nav2_rats_life_waypoints.yaml'))  # 参数文件
        ]
    )

    rviz = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        arguments=['-d', os.path.join(package_dir, 'resource', 'all.rviz')],  # 启动 RViz
        parameters=[{'use_sim_time': use_sim_time}],  # 设置参数
        output='screen'  # 输出到屏幕
    )

    mapper = Node(
        package='webots_epuck',
        executable='simple_mapper',  # 启动简单映射器
        output='screen',
        parameters=[{'use_sim_time': use_sim_time, 'fill_map': True}],  # 设置参数
    )

    # 一旦相应的节点准备就绪，将航点发送到 Navigation2 包。
    send_waypoints = ExecuteProcess(
        # 目标必须在仿真启动并运行后发送。
        # 因此，我们不断发送目标，直到它被接受。
        cmd=[
            'sleep 5;'
            'while [ -z '
            f'`ros2 action send_goal /follow_waypoints nav2_msgs/action/FollowWaypoints \'{get_waypoints()}\' | grep accepted`'
            ']; do'
            '  sleep 3;'
            'done'
        ],
        shell=True
    )

    return LaunchDescription([
        webots_launch,
        nav2,
        rviz,
        mapper,
        send_waypoints,
        DeclareLaunchArgument(
            'use_sim_time',
            default_value='true',
            description='如果为真，则使用仿真（Webots）时钟'
        )
    ])
