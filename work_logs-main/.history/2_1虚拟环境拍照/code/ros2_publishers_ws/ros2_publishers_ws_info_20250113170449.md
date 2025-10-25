### 工作空间功能
- 该工作空间主要用于话题的发布与分装

### 功能包：webots_demo
#### 节点：
- camera_xyz.py
    - 运行该节点时，周期性发布图像和位置信息
    - 图像话题：`/camera_image`
    - 位置话题：`/camera_pose`
- camera_xyz2.py
    - 运行该节点时，周期性发布图像和位置信息，以及深度图像信息和点云信息
    - 图像话题：`/camera_image`
    - 位置话题：`/camera_pose`
    - 深度图像话题：`/range_image`
    - 点云话题：`/range_pointcloud`
- random_walk.py
    - 运行该节点时，epuck机器人随机行走，简单避障
- photo.py
    - 运行节点时，epuck机器人避障行走，并拍摄400张均匀覆盖地图的照片

### 使用方式
- ros2 run webots_demo camera_xyz
- ros2 run webots_demo camera_xyz2
- ros2 run webots_demo random_walk