 ros2 launch sfuise sfuise_test_isas-walk1.launch 
[INFO] [launch]: All log files can be found below /home/dsh/.ros/log/2025-04-08-02-35-47-916588-dsh-Precision-5680-287805
[INFO] [launch]: Default logging verbosity is set to INFO
[INFO] [rviz2-1]: process started with pid [287806]
[INFO] [static_transform_publisher-2]: process started with pid [287808]
[INFO] [EstimationInterface-3]: process started with pid [287810]
[INFO] [SplineFusion-4]: process started with pid [287812]
[static_transform_publisher-2] [INFO] [1744050948.058640508] [static_transform_publisher]: Spinning until stopped - publishing transform
[static_transform_publisher-2] translation: ('0.000000', '0.000000', '0.000000')
[static_transform_publisher-2] rotation: ('0.000000', '0.000000', '0.000000', '1.000000')
[static_transform_publisher-2] from 'map' to 'my_frame'
[SplineFusion-4] [INFO] [1744050948.063737215] [SplineFusion]: ----> Starting SplineFusion.
[EstimationInterface-3] [INFO] [1744050948.067357775] [EstimationInterface]: EstimationInterface Initialized.
[EstimationInterface-3] [INFO] [1744050948.067477239] [EstimationInterface]: ----> Starting EstimationInterface.
[rviz2-1] [INFO] [1744050948.413738515] [rviz2]: Stereo is NOT SUPPORTED
[rviz2-1] [INFO] [1744050948.413856691] [rviz2]: OpenGl version: 4.6 (GLSL 4.6)
[rviz2-1] [INFO] [1744050948.439371596] [rviz2]: Stereo is NOT SUPPORTED




dsh@dsh-Precision-5680:~/Documents/work_logs/code/SFUISE/sfuise_ws/src/dataset$ ros2 bag info ros2-walk1

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

dsh@dsh-Precision-5680:~/Documents/work_logs/code/SFUISE/sfuise_ws$ ros2 bag play src/dataset/ros2-walk1
[INFO] [1744104312.370102031] [rosbag2_storage]: Opened database 'src/dataset/ros2-walk1/ros2-walk1.db3' for READ_ONLY.
[INFO] [1744104312.370172445] [rosbag2_player]: Set rate to 1
[INFO] [1744104312.376061030] [rosbag2_player]: Adding keyboard callbacks.
[INFO] [1744104312.376102351] [rosbag2_player]: Press SPACE for Pause/Resume
[INFO] [1744104312.376112795] [rosbag2_player]: Press CURSOR_RIGHT for Play Next Message
[INFO] [1744104312.376121344] [rosbag2_player]: Press CURSOR_UP for Increase Rate 10%
[INFO] [1744104312.376128868] [rosbag2_player]: Press CURSOR_DOWN for Decrease Rate 10%
[INFO] [1744104312.376579619] [rosbag2_storage]: Opened database 'src/dataset/ros2-walk1/ros2-walk1.db3' for READ_ONLY.


dsh@dsh-Precision-5680:~/Documents/work_logs/code/SFUISE/sfuise_ws$ ros2 topic list
/EstimationInterface/anchor_list
/EstimationInterface/imu_ds
/EstimationInterface/toa_ds
/SplineFusion/est_window
/SplineFusion/start_time
/SplineFusion/sys_calib
/active_control_points
/anchor_list
/bspline_optimization_old
/bspline_optimization_window
/clicked_point
/default_imu_topic
/est_window
/events/read_split
/goal_pose
/imu_ds
/inactive_control_points
/initialpose
/map
/map_updates
/opt_pose
/parameter_events
/rosout
/rtls_flares
/rtls_pose
/start_time
/sys_calib
/tdoa_data
/tdoa_ds
/tf
/tf_static
/visualization_anchor
/vive/transform/tracker_1_ref
/waveshare_sense_hat_b


dsh@dsh-Precision-5680:~/Documents/work_logs/code/SFUISE/sfuise_ws$ ros2 bag info src/dataset/ros2-walk1

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

bag发布的话题：
/vive/transform/tracker_1_ref 
/waveshare_sense_hat_b
/rtls_flares
/rtls_pose
/anchor_list

Estimationface发布的话题：
与bag相关
/imu_ds
/toa_ds
/visualization_anchor
/anchor_list

与SplineFusion相关
/bspline_optimization_old
/bspline_optimization_window
/opt_pose

SplineFusion发布的话题：
/start_time
/sys_calib

[SplineFusion-4] min_time 1 2272 9701  
[SplineFusion-4] spline_local 10 0787 3034
min_time
1 1416 3992
1 0195 3786
  7175 1144
  6527 8780
  5304 4093

[SplineFusion-4] 2222222222222dt_ns:100000000 bag_start_time:0
[SplineFusion-4] 2222222222222dt_ns:100000000 bag_start_time:974539702
[SplineFusion-4] 11111111111111dt_ns:100000000 bag_start_time:974539702
[SplineFusion-4] 111111111111111111###974539701
[SplineFusion-4] 22222222222222222###1007873034


[SplineFusion-4] 111111111111###imu_buff974539702
[SplineFusion-4] 2222222222222###imu_buff974539702
[SplineFusion-4] 11111111111111dt_ns:1 0000 0000 
bag_start_time:9 7453 9702
[SplineFusion-4] 111111111111111111###974539701
[SplineFusion-4] 22222222222222222###1074539701

[SplineFusion-4] 111111111111###imu_buff998896409
[SplineFusion-4] 11111111111111dt_ns:100000000 bag_start_time:998896409
[SplineFusion-4] 111111111111111111###998896408
[SplineFusion-4] 22222222222222222###1098896408



974539702
[SplineFusion-4] imu_buff back:974539702
[SplineFusion-4] 111111111111###imu_buff974539702
[SplineFusion-4] 11111111111111dt_ns:1 0000 0000 bag_start_time:974539702
[SplineFusion-4] 111111111111111111###974539701
[SplineFusion-4] 22222222222222222###1074539701
9 7453 9702
[SplineFusion-4] imu_buff back:9 8672 7491
974539702
[SplineFusion-4] imu_buff back:9 9889 6409
974539702
[SplineFusion-4] imu_buff back:  1100 4940
974539702
[SplineFusion-4] imu_buff back:  2311 2526
974539702
[SplineFusion-4] imu_buff back:  3521 6205
974539702
[SplineFusion-4] imu_buff back:  4737 0679
974539702
[SplineFusion-4] imu_buff back:  5949 4302
974539702
[SplineFusion-4] imu_buff back:  7159 9684
974539702
[SplineFusion-4] imu_buff back:  8369 9011
974539702
[SplineFusion-4] imu_buff back:  9596 8243
974539702
[SplineFusion-4] imu_buff back:1 0809 6014
974539702
[SplineFusion-4] imu_buff back:1 2019 6452
974539702
[SplineFusion-4] imu_buff back:1 3230 7760
974539702
[SplineFusion-4] imu_buff back:1 4441 5883
974539702
[SplineFusion-4] imu_buff back:1 5654 1988
974539702
[SplineFusion-4] imu_buff back:1 6867 3388
974539702
[SplineFusion-4] imu_buff back:1 8083 6695
974539702
[SplineFusion-4] imu_buff back:1 9295 1985
974539702
[SplineFusion-4] imu_buff back:2 0505 2016
974539702
[SplineFusion-4] imu_buff back:2 1716 2824
974539702
[SplineFusion-4] imu_buff back:2 2930 3058
974539702
[SplineFusion-4] imu_buff back:2 4141 2311
974539702
[SplineFusion-4] imu_buff back:2 5352 4545
974539702
[SplineFusion-4] imu_buff back:2 6562 6261
974539702
[SplineFusion-4] imu_buff back:2 7772 8828
974539702
[SplineFusion-4] imu_buff back:2 8989 4562
974539702
[SplineFusion-4] imu_buff back:3 0205 7888
974539702


989318950
[SplineFusion-4] toa_buff back:989318950
989318950
[SplineFusion-4] toa_buff back:989318950
989318950
[SplineFusion-4] toa_buff back:989318950
989318950
[SplineFusion-4] toa_buff back:989318950
989318950
[SplineFusion-4] toa_buff back:  4332 8058
989318950
[SplineFusion-4] toa_buff back:  4332 8058
989318950
[SplineFusion-4] toa_buff back:43328058
989318950
[SplineFusion-4] toa_buff back:43328058
989318950
[SplineFusion-4] toa_buff back:43328058
989318950
[SplineFusion-4] toa_buff back:94287788
989318950
[SplineFusion-4] toa_buff back:94287788
989318950
[SplineFusion-4] toa_buff back:94287788
989318950
[SplineFusion-4] toa_buff back:94287788
989318950
[SplineFusion-4] toa_buff back:94287788
989318950
[SplineFusion-4] toa_buff back:169999571
989318950
[SplineFusion-4] toa_buff back:169999571
989318950
[SplineFusion-4] toa_buff back:169999571
989318950
[SplineFusion-4] toa_buff back:169999571
[SplineFusion-4] spline_local_numknots2
989318950
[SplineFusion-4] toa_buff back:220419976
989318950
[SplineFusion-4] toa_buff back:220419976
989318950
[SplineFusion-4] toa_buff back:220419976
989318950
[SplineFusion-4] toa_buff back:220419976
[SplineFusion-4] spline_local_numknots3
989318950
[SplineFusion-4] toa_buff back:345279092
989318950
[SplineFusion-4] toa_buff back:345279092
989318950
[SplineFusion-4] toa_buff back:345279092
989318950
[SplineFusion-4] toa_buff back:345279092
[SplineFusion-4] spline_local_numknots4
989318950
[SplineFusion-4] toa_buff back:396286507
989318950
[SplineFusion-4] toa_buff back:396286507
989318950
[SplineFusion-4] toa_buff back:396286507
989318950
[SplineFusion-4] toa_buff back:396286507
989318950
[SplineFusion-4] toa_buff back:451065640
989318950
[SplineFusion-4] toa_buff back:451065640
989318950
[SplineFusion-4] toa_buff back:451065640
989318950
[SplineFusion-4] toa_buff back:451065640
989318950
[SplineFusion-4] toa_buff back:451065640
[SplineFusion-4] spline_local_numknots5
989318950
[SplineFusion-4] toa_buff back:501272326
989318950
[SplineFusion-4] toa_buff back:501272326
989318950
[SplineFusion-4] toa_buff back:501272326
989318950
[SplineFusion-4] toa_buff back:501272326
989318950
[SplineFusion-4] toa_buff back:501272326
989318950
[SplineFusion-4] toa_buff back:576078716
989318950
[SplineFusion-4] toa_buff back:576078716
989318950
[SplineFusion-4] toa_buff back:576078716
989318950
[SplineFusion-4] toa_buff back:576078716
989318950
[SplineFusion-4] toa_buff back:576078716
[SplineFusion-4] spline_local_numknots6
989318950





[SplineFusion-4] spline_local_numknots:2
[SplineFusion-4] Point0: [0, 0, 0]
[SplineFusion-4] Point1: [0, 0, 0]
[SplineFusion-4] Point0: [2.22542, -1.02967, 2.15179]
[SplineFusion-4] Point1: [2.22542, -1.02967, 2.15179]

[SplineFusion-4] spline_local_numknots:3
[SplineFusion-4] Point0: [2.22542, -1.02967, 2.15179]
[SplineFusion-4] Point1: [2.22542, -1.02967, 2.15179]
[SplineFusion-4] Point2: [2.22542, -1.02967, 2.15179]
[SplineFusion-4] Point0: [2.19993, -1.29699, 1.77976]
[SplineFusion-4] Point1: [2.19993, -1.29699, 1.77976]
[SplineFusion-4] Point2: [2.19993, -1.29699, 1.77976]

[SplineFusion-4] spline_local_numknots:4
[SplineFusion-4] Point0: [2.19993, -1.29699, 1.77976]
[SplineFusion-4] Point1: [2.19993, -1.29699, 1.77976]
[SplineFusion-4] Point2: [2.19993, -1.29699, 1.77976]
[SplineFusion-4] Point3: [2.1998, -1.29682, 1.77977]
[SplineFusion-4] Point0: [2.25118, -1.24371, 1.85588]
[SplineFusion-4] Point1: [2.25118, -1.24371, 1.85588]
[SplineFusion-4] Point2: [2.25118, -1.24371, 1.85588]
[SplineFusion-4] Point3: [2.2514, -1.2436, 1.85602]

[SplineFusion-4] spline_local_numknots:5
[SplineFusion-4] Point0: [2.25118, -1.24371, 1.85588]
[SplineFusion-4] Point1: [2.25118, -1.24371, 1.85588]
[SplineFusion-4] Point2: [2.25118, -1.24371, 1.85588]
[SplineFusion-4] Point3: [2.2514, -1.2436, 1.85602]
[SplineFusion-4] Point4: [2.24788, -1.23586, 1.85541]
[SplineFusion-4] Point0: [2.19312, -1.21846, 1.95927]
[SplineFusion-4] Point1: [2.19312, -1.21846, 1.95927]
[SplineFusion-4] Point2: [2.19312, -1.21846, 1.95927]
[SplineFusion-4] Point3: [2.19332, -1.21822, 1.95933]
[SplineFusion-4] Point4: [2.18947, -1.21282, 1.9515]

[SplineFusion-4] spline_local_numknots:6
[SplineFusion-4] Point0: [2.19312, -1.21846, 1.95927]
[SplineFusion-4] Point1: [2.19312, -1.21846, 1.95927]
[SplineFusion-4] Point2: [2.19312, -1.21846, 1.95927]
[SplineFusion-4] Point3: [2.19332, -1.21822, 1.95933]
[SplineFusion-4] Point4: [2.18947, -1.21282, 1.9515]
[SplineFusion-4] Point5: [2.19306, -1.21786, 1.95873]
[SplineFusion-4] Point0: [2.36264, -1.1321, 1.86881]
[SplineFusion-4] Point1: [2.36264, -1.1321, 1.86881]
[SplineFusion-4] Point2: [2.36264, -1.1321, 1.86881]
[SplineFusion-4] Point3: [2.36255, -1.13234, 1.86872]
[SplineFusion-4] Point4: [2.35123, -1.12881, 1.86969]
[SplineFusion-4] Point5: [2.36159, -1.13204, 1.86888]

[SplineFusion-4] spline_local_numknots:7
[SplineFusion-4] Point0: [2.36264, -1.1321, 1.86881]
[SplineFusion-4] Point1: [2.36264, -1.1321, 1.86881]
[SplineFusion-4] Point2: [2.36264, -1.1321, 1.86881]
[SplineFusion-4] Point3: [2.36255, -1.13234, 1.86872]
[SplineFusion-4] Point4: [2.35123, -1.12881, 1.86969]
[SplineFusion-4] Point5: [2.36159, -1.13204, 1.86888]
[SplineFusion-4] Point6: [2.35123, -1.12881, 1.86969]
[SplineFusion-4] Point0: [2.33711, -1.06661, 1.90552]
[SplineFusion-4] Point1: [2.33711, -1.06661, 1.90552]
[SplineFusion-4] Point2: [2.33711, -1.06661, 1.90552]
[SplineFusion-4] Point3: [2.33712, -1.06677, 1.90556]
[SplineFusion-4] Point4: [2.32688, -1.0702, 1.89748]
[SplineFusion-4] Point5: [2.33607, -1.06704, 1.90485]
[SplineFusion-4] Point6: [2.32688, -1.0702, 1.89748]

[SplineFusion-4] spline_local_numknots:8
[SplineFusion-4] Point0: [2.33711, -1.06661, 1.90552]
[SplineFusion-4] Point1: [2.33711, -1.06661, 1.90552]
[SplineFusion-4] Point2: [2.33711, -1.06661, 1.90552]
[SplineFusion-4] Point3: [2.33712, -1.06677, 1.90556]
[SplineFusion-4] Point4: [2.32688, -1.0702, 1.89748]
[SplineFusion-4] Point5: [2.33607, -1.06704, 1.90485]
[SplineFusion-4] Point6: [2.32688, -1.0702, 1.89748]
[SplineFusion-4] Point7: [2.33607, -1.06704, 1.90485]
[SplineFusion-4] Point0: [2.27858, -1.04558, 1.73209]
[SplineFusion-4] Point1: [2.27858, -1.04558, 1.73209]
[SplineFusion-4] Point2: [2.27858, -1.04558, 1.73209]
[SplineFusion-4] Point3: [2.27856, -1.04553, 1.73213]
[SplineFusion-4] Point4: [2.27683, -1.05486, 1.74386]
[SplineFusion-4] Point5: [2.27826, -1.04655, 1.73329]
[SplineFusion-4] Point6: [2.27683, -1.05486, 1.74386]
[SplineFusion-4] Point7: [2.27826, -1.04655, 1.73329]

[SplineFusion-4] spline_local_numknots:9
[SplineFusion-4] Point0: [2.27858, -1.04558, 1.73209]
[SplineFusion-4] Point1: [2.27858, -1.04558, 1.73209]
[SplineFusion-4] Point2: [2.27858, -1.04558, 1.73209]
[SplineFusion-4] Point3: [2.27856, -1.04553, 1.73213]
[SplineFusion-4] Point4: [2.27683, -1.05486, 1.74386]
[SplineFusion-4] Point5: [2.27826, -1.04655, 1.73329]
[SplineFusion-4] Point6: [2.27683, -1.05486, 1.74386]
[SplineFusion-4] Point7: [2.27826, -1.04655, 1.73329]
[SplineFusion-4] Point8: [2.27683, -1.05486, 1.74386]
[SplineFusion-4] Point0: [2.29693, -1.01744, 1.78436]
[SplineFusion-4] Point1: [2.29693, -1.01744, 1.78436]
[SplineFusion-4] Point2: [2.29693, -1.01744, 1.78436]
[SplineFusion-4] Point3: [2.2969, -1.01744, 1.78432]
[SplineFusion-4] Point4: [2.29316, -1.033, 1.78915]
[SplineFusion-4] Point5: [2.29631, -1.01912, 1.78481]
[SplineFusion-4] Point6: [2.29316, -1.033, 1.78915]
[SplineFusion-4] Point7: [2.29631, -1.01912, 1.78481]
[SplineFusion-4] Point8: [2.29316, -1.033, 1.78915]

[SplineFusion-4] spline_local_numknots:10
[SplineFusion-4] Point0: [2.29693, -1.01744, 1.78436]
[SplineFusion-4] Point1: [2.29693, -1.01744, 1.78436]
[SplineFusion-4] Point2: [2.29693, -1.01744, 1.78436]
[SplineFusion-4] Point3: [2.2969, -1.01744, 1.78432]
[SplineFusion-4] Point4: [2.29316, -1.033, 1.78915]
[SplineFusion-4] Point5: [2.29631, -1.01912, 1.78481]
[SplineFusion-4] Point6: [2.29316, -1.033, 1.78915]
[SplineFusion-4] Point7: [2.29631, -1.01912, 1.78481]
[SplineFusion-4] Point8: [2.29316, -1.033, 1.78915]
[SplineFusion-4] Point9: [2.29634, -1.01912, 1.78485]
[SplineFusion-4] Point0: [2.19886, -1.11267, 1.7052]
[SplineFusion-4] Point1: [2.19886, -1.11267, 1.7052]
[SplineFusion-4] Point2: [2.19886, -1.11267, 1.7052]
[SplineFusion-4] Point3: [2.19887, -1.11277, 1.70512]
[SplineFusion-4] Point4: [2.20449, -1.12237, 1.71973]
[SplineFusion-4] Point5: [2.19935, -1.11402, 1.70677]
[SplineFusion-4] Point6: [2.20449, -1.12237, 1.71973]
[SplineFusion-4] Point7: [2.19935, -1.11402, 1.70677]
[SplineFusion-4] Point8: [2.20449, -1.12237, 1.71973]
[SplineFusion-4] Point9: [2.19934, -1.11391, 1.70685]


dsh@dsh-Precision-5680:~/Documents/work_logs/code/SFUISE/sfuise_ws$ ros2 topic echo /sys_calib 偏移情况
gravity:
  x: 0.0
  y: 0.0
  z: 0.0
t_nav_uwb:
  x: 2.2254151323045925
  y: -1.0296735934942516
  z: 2.151787679468557
q_nav_uwb:
  x: 0.9184569484399521
  y: 0.29878946238519977
  z: -0.10474232301648664
  w: 0.23704585379003007
t_tag_body_set:
  x: 0.1
  y: -0.025
  z: 0.0
---
gravity:
  x: 0.0
  y: 0.0
  z: 0.0
t_nav_uwb:
  x: 2.199926971425238
  y: -1.296990186270124
  z: 1.7797613885495196
q_nav_uwb:
  x: -0.9426008098867519
  y: -0.32289447335684995
  z: 0.05426615349809839
  w: -0.06555956727253948
t_tag_body_set:
  x: 0.1
  y: -0.025
  z: 0.0
---
gravity:
  x: 0.0
  y: 0.0
  z: 0.0
t_nav_uwb:
  x: 2.251183645936754
  y: -1.2437148488198966
  z: 1.8558813364772366
q_nav_uwb:
  x: 0.28885251366618436
  y: 0.3423390551322106
  z: -0.7671407692465522
  w: -0.45919847216614385
t_tag_body_set:
  x: 0.1
  y: -0.025
  z: 0.0
---
gravity:
  x: 0.0
  y: 0.0
  z: 0.0
t_nav_uwb:
  x: 2.193120191456887
  y: -1.2184568302995813
  z: 1.9592701746710797
q_nav_uwb:
  x: -0.528035603945008
  y: -0.11645260007375452
  z: 0.8117631354159874
  w: 0.220585142024795
t_tag_body_set:
  x: 0.1
  y: -0.025
  z: 0.0
---
gravity:
  x: 0.0
  y: 0.0
  z: 0.0
t_nav_uwb:
  x: 2.3626386253675427
  y: -1.132104187967525
  z: 1.8688077087611414
q_nav_uwb:
  x: 0.1695458255207822
  y: 0.8975624119421857
  z: 0.40680435109301133
  w: -0.01208923689884571
t_tag_body_set:
  x: 0.1
  y: -0.025
  z: 0.0
---
gravity:
  x: 0.0
  y: 0.0
  z: 0.0
t_nav_uwb:
  x: 2.3371054056020655
  y: -1.066607992950884
  z: 1.9055183760484031
q_nav_uwb:
  x: 0.1429043049030251
  y: -0.9448071007272698
  z: -0.11342221540582181
  w: -0.27212736559917833
t_tag_body_set:
  x: 0.1
  y: -0.025
  z: 0.0
---
gravity:
  x: 0.0
  y: 0.0
  z: 0.0
t_nav_uwb:
  x: 2.2785792201792505
  y: -1.045578894406602
  z: 1.7320891949426098
q_nav_uwb:
  x: 0.6236788263137163
  y: -0.39389588662565744
  z: 0.6646780703819124
  w: -0.11863311030529869
t_tag_body_set:
  x: 0.1
  y: -0.025
  z: 0.0
---
gravity:
  x: 0.0
  y: 0.0
  z: 0.0
t_nav_uwb:
  x: 2.2969320601921153
  y: -1.0174364497385013
  z: 1.7843582507269782
q_nav_uwb:
  x: -0.5640425190378695
  y: 0.6963355572520684
  z: -0.4184657004352208
  w: 0.14784886196087327
t_tag_body_set:
  x: 0.1
  y: -0.025
  z: 0.0
---
gravity:
  x: 0.0
  y: 0.0
  z: 0.0
t_nav_uwb:
  x: 2.1988626229028734
  y: -1.1126651352515255
  z: 1.7051995010928724
q_nav_uwb:
  x: 0.7717978075210316
  y: -0.28717092573951086
  z: 0.5523038061535107
  w: -0.12969776183105583
t_tag_body_set:
  x: 0.1
  y: -0.025
  z: 0.0
---


dsh@dsh-Precision-5680:~/Documents/work_logs/code/SFUISE/sfuise_ws$ ros2 topic echo /est_window
2025-04-22 16:43:47.771 [RTPS_TRANSPORT_SHM Error] Failed init_port fastrtps_port7419: open_and_lock_file failed -> Function open_port_internal
spline:
  start_idx: 0
  dt: 100000000
  start_t: 11004940
  knots:
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: -8.526227973865753e-05
      y: -2.7943692679716726e-05
      z: 0.0042768703939963576
    bias_gyro:
      x: -0.00027649034167867234
      y: -1.5594573118588137e-05
      z: 0.00017488729213776838
  - position:
      x: -0.0015222996463144412
      y: -2.4754482657506844e-05
      z: 0.0025762095153491027
    orientation:
      x: -0.0011207231391893542
      y: 0.00013942500876992263
      z: -0.0008312588789412956
      w: 0.9999990167740108
    bias_acc:
      x: -4.4613291057698005e-05
      y: -4.868648663026663e-05
      z: 0.0017449012631313818
    bias_gyro:
      x: -0.00013577568121730555
      y: -6.353891553033538e-06
      z: 8.874090124105345e-05
  idles:
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: -8.526227973865753e-05
      y: -2.7943692679716726e-05
      z: 0.0042768703939963576
    bias_gyro:
      x: -0.00027649034167867234
      y: -1.5594573118588137e-05
      z: 0.00017488729213776838
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: -8.526227973865753e-05
      y: -2.7943692679716726e-05
      z: 0.0042768703939963576
    bias_gyro:
      x: -0.00027649034167867234
      y: -1.5594573118588137e-05
      z: 0.00017488729213776838
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: -8.526227973865753e-05
      y: -2.7943692679716726e-05
      z: 0.0042768703939963576
    bias_gyro:
      x: -0.00027649034167867234
      y: -1.5594573118588137e-05
      z: 0.00017488729213776838
if_full_window:
  data: false
runtime:
  data: 0.001200011
---
spline:
  start_idx: 0
  dt: 100000000
  start_t: 11004940
  knots:
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: -0.00020977809377928716
      y: -2.442116516808011e-05
      z: 0.006741664797790753
    bias_gyro:
      x: -0.0005066254215985672
      y: 4.815091099158566e-05
      z: 0.0003011248097972959
  - position:
      x: -0.0015399897782407523
      y: -0.00011715364519673078
      z: 0.002182825192941234
    orientation:
      x: -0.00030587977997902527
      y: -0.0005968282035842472
      z: -0.0008428936565273325
      w: 0.9999994198818015
    bias_acc:
      x: -0.00015185218031885973
      y: -7.651004594905033e-05
      z: 0.006119264219243845
    bias_gyro:
      x: -0.00046416880086215415
      y: 3.388756626838456e-05
      z: 0.0002772015047401204
  - position:
      x: -0.004108609203644585
      y: 8.727418708378113e-05
      z: 0.005942127127893976
    orientation:
      x: -0.001301214164611651
      y: -0.003915300343861352
      z: -0.0024499947200580397
      w: 0.9999884873291596
    bias_acc:
      x: -0.00037784741735451407
      y: 0.00016261506139626027
      z: 0.00784861512996364
    bias_gyro:
      x: -0.0005657037643162782
      y: 7.005077650059723e-05
      z: 0.00033594063119359355
  idles:
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: -0.00020977809377928716
      y: -2.442116516808011e-05
      z: 0.006741664797790753
    bias_gyro:
      x: -0.0005066254215985672
      y: 4.815091099158566e-05
      z: 0.0003011248097972959
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: -0.00020977809377928716
      y: -2.442116516808011e-05
      z: 0.006741664797790753
    bias_gyro:
      x: -0.0005066254215985672
      y: 4.815091099158566e-05
      z: 0.0003011248097972959
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: -0.00020977809377928716
      y: -2.442116516808011e-05
      z: 0.006741664797790753
    bias_gyro:
      x: -0.0005066254215985672
      y: 4.815091099158566e-05
      z: 0.0003011248097972959
if_full_window:
  data: false
runtime:
  data: 0.0014439639999999998
---
spline:
  start_idx: 0
  dt: 100000000
  start_t: 11004940
  knots:
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: -0.0002585347489465559
      y: -0.00010974216994215295
      z: 0.008505479374561309
    bias_gyro:
      x: -0.0006565397784378822
      y: 0.0001811550274343114
      z: 0.0004917519459845743
  - position:
      x: -0.001470636244710264
      y: -9.37374632435579e-05
      z: 0.0021400558711877353
    orientation:
      x: -0.000465273463680104
      y: -0.001053293278328326
      z: -0.0013066523481704139
      w: 0.9999984833756074
    bias_acc:
      x: -0.000224635080685018
      y: -0.00010139343306588172
      z: 0.00817113993733746
    bias_gyro:
      x: -0.000637318500311291
      y: 0.00015329956770373035
      z: 0.0004556679259753125
  - position:
      x: -0.004221853222368391
      y: 0.00012453460843493957
      z: 0.0059367745562150034
    orientation:
      x: -0.000567284934518968
      y: -0.0021632732111831936
      z: -0.0009085316571295155
      w: 0.9999970864993152
    bias_acc:
      x: -0.0003203908740323853
      y: -0.0001311250467247952
      z: 0.008472230116097627
    bias_gyro:
      x: -0.0006477970390707315
      y: 0.00017940499287532824
      z: 0.0004890296379213312
  - position:
      x: -0.008159541094253884
      y: 0.0006669122513566969
      z: 0.011440952813872389
    orientation:
      x: -0.0017219743620287748
      y: -0.0002556738066022604
      z: 0.002582480870259446
      w: 0.99999515010212
    bias_acc:
      x: 4.316594143466638e-05
      y: 5.92209239030074e-05
      z: 0.007581814573322301
    bias_gyro:
      x: -0.0006209247151031377
      y: 0.00010492568585362613
      z: 0.00039101469013502386
  idles:
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: -0.0002585347489465559
      y: -0.00010974216994215295
      z: 0.008505479374561309
    bias_gyro:
      x: -0.0006565397784378822
      y: 0.0001811550274343114
      z: 0.0004917519459845743
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: -0.0002585347489465559
      y: -0.00010974216994215295
      z: 0.008505479374561309
    bias_gyro:
      x: -0.0006565397784378822
      y: 0.0001811550274343114
      z: 0.0004917519459845743
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: -0.0002585347489465559
      y: -0.00010974216994215295
      z: 0.008505479374561309
    bias_gyro:
      x: -0.0006565397784378822
      y: 0.0001811550274343114
      z: 0.0004917519459845743
if_full_window:
  data: false
runtime:
  data: 0.0019062446666666666
---
spline:
  start_idx: 0
  dt: 100000000
  start_t: 11004940
  knots:
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: -0.00027855035160613057
      y: -0.00014570314867187254
      z: 0.010231399675884257
    bias_gyro:
      x: -0.000799234417165127
      y: 0.0003405926293876492
      z: 0.0007433146753180204
  - position:
      x: -0.0014347840149717837
      y: -6.78322870765769e-05
      z: 0.0021168778748444045
    orientation:
      x: -0.0004887355219360772
      y: -0.0011991804378517772
      z: -0.0015822725461637757
      w: 0.9999979097565438
    bias_acc:
      x: -0.00027694150765442956
      y: -0.00014183781567584465
      z: 0.009958682206408616
    bias_gyro:
      x: -0.0007848572854332488
      y: 0.00030973334092642037
      z: 0.0006965710495199992
  - position:
      x: -0.004221130899328442
      y: 9.948281189304438e-05
      z: 0.005884104686465367
    orientation:
      x: -0.0004923158036249079
      y: -0.0018857098747007528
      z: -0.00042282257864855366
      w: 0.9999980114703022
    bias_acc:
      x: -0.0003264831213632296
      y: -0.0001920768777871861
      z: 0.010121515251660695
    bias_gyro:
      x: -0.0007892323849426137
      y: 0.0003326818232663615
      z: 0.0007346595617470826
  - position:
      x: -0.007883795067991693
      y: 0.0008934622650929932
      z: 0.011309446056808779
    orientation:
      x: -0.0018907749444603099
      y: -0.0020222437913720334
      z: -5.822627309400119e-05
      w: 0.9999961660475827
    bias_acc:
      x: -0.00021059391574264544
      y: 2.8943791328481905e-05
      z: 0.009934723356763845
    bias_gyro:
      x: -0.0007864456072917276
      y: 0.0003088658187107045
      z: 0.0006892485643217724
  - position:
      x: -0.012381210690914447
      y: 0.0029597739168886004
      z: 0.0185023210856553
    orientation:
      x: -0.0027464861811865187
      y: -0.0023191149611125556
      z: -0.003546284852865232
      w: 0.9999872511103337
    bias_acc:
      x: -0.0006584254503665788
      y: -0.001007011857442654
      z: 0.01051940475282605
    bias_gyro:
      x: -0.000787350495965592
      y: 0.00037422415706637335
      z: 0.0008258014052575908
  idles:
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: -0.00027855035160613057
      y: -0.00014570314867187254
      z: 0.010231399675884257
    bias_gyro:
      x: -0.000799234417165127
      y: 0.0003405926293876492
      z: 0.0007433146753180204
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: -0.00027855035160613057
      y: -0.00014570314867187254
      z: 0.010231399675884257
    bias_gyro:
      x: -0.000799234417165127
      y: 0.0003405926293876492
      z: 0.0007433146753180204
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: -0.00027855035160613057
      y: -0.00014570314867187254
      z: 0.010231399675884257
    bias_gyro:
      x: -0.000799234417165127
      y: 0.0003405926293876492
      z: 0.0007433146753180204
if_full_window:
  data: false
runtime:
  data: 0.00230101675
---
spline:
  start_idx: 0
  dt: 100000000
  start_t: 11004940
  knots:
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: -0.00023372722246331042
      y: -0.00012002002239242572
      z: 0.011862217212093474
    bias_gyro:
      x: -0.0009286590643896322
      y: 0.0005005368653104183
      z: 0.0010186910283480858
  - position:
      x: -0.0014429624724105919
      y: -3.927445321826986e-05
      z: 0.0020981385460720793
    orientation:
      x: -0.0005151310424634125
      y: -0.0012240513074619457
      z: -0.0017047701264390949
      w: 0.9999976650458845
    bias_acc:
      x: -0.00024409849419199868
      y: -0.0001581479885182917
      z: 0.011601569469266056
    bias_gyro:
      x: -0.0009173799896167622
      y: 0.00047083463517647245
      z: 0.0009664363262037126
  - position:
      x: -0.004254165757987852
      y: 0.00012662510614850985
      z: 0.005840220892221253
    orientation:
      x: -0.00041875722154802007
      y: -0.0018851396638011628
      z: -0.00026606947606666305
      w: 0.9999981000471677
    bias_acc:
      x: -0.000257899432874665
      y: -0.00013035366015005812
      z: 0.01171207991614
    bias_gyro:
      x: -0.0009170492383879918
      y: 0.0004893063552536955
      z: 0.0010062439157665702
  - position:
      x: -0.007933399643732682
      y: 0.001083637032252644
      z: 0.011202174138749826
    orientation:
      x: -0.0020316953480171572
      y: -0.002126060828004438
      z: -0.0006753075356212028
      w: 0.9999954480091928
    bias_acc:
      x: -0.00022346903121561742
      y: -5.0700178371290556e-05
      z: 0.011615446158594505
    bias_gyro:
      x: -0.0009186558210943497
      y: 0.00047643564626440775
      z: 0.000968859139693739
  - position:
      x: -0.012540394989252662
      y: 0.002742981205631308
      z: 0.018407056876041654
    orientation:
      x: -0.0021376138667356793
      y: -0.0018089900484066126
      z: -0.0008938332304444694
      w: 0.9999956796027285
    bias_acc:
      x: -0.00026946337614413435
      y: -0.0002893371725244728
      z: 0.011714716831429686
    bias_gyro:
      x: -0.0009131738104039678
      y: 0.0004844175230605702
      z: 0.00100449147011759
  - position:
      x: -0.018225351498531068
      y: 0.004434112741636536
      z: 0.027114229907832767
    orientation:
      x: -0.002638427999907694
      y: -0.001398463877876028
      z: -0.001692463534936811
      w: 0.9999941092644774
    bias_acc:
      x: -0.0001548930205015588
      y: 0.00047436570796772365
      z: 0.011435824881676042
    bias_gyro:
      x: -0.0009298470681959242
      y: 0.0004685823681897963
      z: 0.0009191661306341844
  idles:
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: -0.00023372722246331042
      y: -0.00012002002239242572
      z: 0.011862217212093474
    bias_gyro:
      x: -0.0009286590643896322
      y: 0.0005005368653104183
      z: 0.0010186910283480858
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: -0.00023372722246331042
      y: -0.00012002002239242572
      z: 0.011862217212093474
    bias_gyro:
      x: -0.0009286590643896322
      y: 0.0005005368653104183
      z: 0.0010186910283480858
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: -0.00023372722246331042
      y: -0.00012002002239242572
      z: 0.011862217212093474
    bias_gyro:
      x: -0.0009286590643896322
      y: 0.0005005368653104183
      z: 0.0010186910283480858
if_full_window:
  data: false
runtime:
  data: 0.0027594588
---
spline:
  start_idx: 0
  dt: 100000000
  start_t: 11004940
  knots:
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: -0.0001492878450450224
      y: -7.779958294590523e-05
      z: 0.013437020594045236
    bias_gyro:
      x: -0.0010560837630553856
      y: 0.0006659922506058992
      z: 0.001295530708422024
  - position:
      x: -0.0014552913263418791
      y: -3.470114501166201e-05
      z: 0.0020774165776460286
    orientation:
      x: -0.0005161426186118836
      y: -0.0012452634613687873
      z: -0.0017323224436294673
      w: 0.999997590984428
    bias_acc:
      x: -0.0001606677889335789
      y: -0.0001308536095677108
      z: 0.013179106865347038
    bias_gyro:
      x: -0.0010462015625866234
      y: 0.0006361156935813667
      z: 0.0012446709481700301
  - position:
      x: -0.0042896265536314215
      y: 0.00013824284151251162
      z: 0.005786267349797866
    orientation:
      x: -0.0003871011194592461
      y: -0.0018890874497115356
      z: -0.0002880104201499167
      w: 0.999998099273895
    bias_acc:
      x: -0.00016860616274900174
      y: -7.519077136393925e-05
      z: 0.013277758864813617
    bias_gyro:
      x: -0.001044704392301603
      y: 0.0006557018134836643
      z: 0.0012829318241306354
  - position:
      x: -0.008003946497205377
      y: 0.0011078297099922508
      z: 0.011096096427093456
    orientation:
      x: -0.0020592805248801746
      y: -0.002196557220964407
      z: -0.0007517289820686157
      w: 0.9999951846902253
    bias_acc:
      x: -0.0001466146287065189
      y: -5.9302325211282785e-05
      z: 0.013197506811441672
    bias_gyro:
      x: -0.0010480380635911229
      y: 0.0006421239310533802
      z: 0.0012508273481967181
  - position:
      x: -0.012663157690828599
      y: 0.0027677557122534665
      z: 0.01824978894906802
    orientation:
      x: -0.0019970315805774006
      y: -0.0017408691064582284
      z: -0.0008784359900600911
      w: 0.9999961047873321
    bias_acc:
      x: -0.00016170989397089073
      y: -0.00014166385454650486
      z: 0.013251884716901512
    bias_gyro:
      x: -0.0010416572154918963
      y: 0.000649114096873124
      z: 0.001270923405038247
  - position:
      x: -0.01840486283754039
      y: 0.0045047693956866775
      z: 0.026832546405109587
    orientation:
      x: -0.0030632581098452775
      y: -0.0019679930093182783
      z: -0.0022238825607450935
      w: 0.9999908988583969
    bias_acc:
      x: -0.00017406899889015092
      y: -4.457794107914913e-05
      z: 0.013159184018674417
    bias_gyro:
      x: -0.00104944945893478
      y: 0.0006431818194970742
      z: 0.0012537751988274805
  - position:
      x: -0.025751588905718232
      y: 0.007311982924895023
      z: 0.037032436820042286
    orientation:
      x: -0.0023919520164798823
      y: -0.004101136631205998
      z: -0.0024167032747244017
      w: 0.9999858092938969
    bias_acc:
      x: -7.828769180022811e-05
      y: -0.00025564553361495163
      z: 0.01345581668797705
    bias_gyro:
      x: -0.0010283763070015588
      y: 0.0006569244967513699
      z: 0.0012916375709142276
  idles:
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: -0.0001492878450450224
      y: -7.779958294590523e-05
      z: 0.013437020594045236
    bias_gyro:
      x: -0.0010560837630553856
      y: 0.0006659922506058992
      z: 0.001295530708422024
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: -0.0001492878450450224
      y: -7.779958294590523e-05
      z: 0.013437020594045236
    bias_gyro:
      x: -0.0010560837630553856
      y: 0.0006659922506058992
      z: 0.001295530708422024
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: -0.0001492878450450224
      y: -7.779958294590523e-05
      z: 0.013437020594045236
    bias_gyro:
      x: -0.0010560837630553856
      y: 0.0006659922506058992
      z: 0.001295530708422024
if_full_window:
  data: false
runtime:
  data: 0.004221237833333333
---
spline:
  start_idx: 0
  dt: 100000000
  start_t: 11004940
  knots:
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: -5.402373502396168e-05
      y: -3.5111260060861704e-05
      z: 0.015021114952426858
    bias_gyro:
      x: -0.0011825108719593458
      y: 0.000838721679750365
      z: 0.0015742481747646603
  - position:
      x: -0.0014636834848747785
      y: -3.3492283510430516e-05
      z: 0.002054061746455453
    orientation:
      x: -0.0005092989091042287
      y: -0.0012698554475605462
      z: -0.0017506725800314896
      w: 0.9999975316105935
    bias_acc:
      x: -6.410594358189165e-05
      y: -9.053619185871559e-05
      z: 0.01477581883331508
    bias_gyro:
      x: -0.0011737133241309337
      y: 0.0008087281015883828
      z: 0.0015260451578653514
  - position:
      x: -0.004314516810224667
      y: 0.00014118334851594393
      z: 0.0057233870916740676
    orientation:
      x: -0.0003693476809990598
      y: -0.0018910558810298008
      z: -0.00032712817021615247
      w: 0.9999980902367663
    bias_acc:
      x: -7.20254208629629e-05
      y: -3.5019084439343766e-05
      z: 0.014885113717489747
    bias_gyro:
      x: -0.0011725796089190324
      y: 0.0008320918645897468
      z: 0.001565328163090993
  - position:
      x: -0.00805445353269458
      y: 0.0011093783057101853
      z: 0.010975182732238957
    orientation:
      x: -0.002050287770014766
      y: -0.0022797960265050197
      z: -0.0007846995309740475
      w: 0.9999949915358524
    bias_acc:
      x: -4.765732324254523e-05
      y: -2.512096778661585e-05
      z: 0.014821045715279842
    bias_gyro:
      x: -0.0011771156741306854
      y: 0.0008154133831791469
      z: 0.0015366899766917146
  - position:
      x: -0.012753802060699268
      y: 0.002775221252692995
      z: 0.018057346777635975
    orientation:
      x: -0.0019449961464632368
      y: -0.001665219172560025
      z: -0.0009777700875488909
      w: 0.9999962439933255
    bias_acc:
      x: -6.652451372185018e-05
      y: -9.433947412071737e-05
      z: 0.01485903907009492
    bias_gyro:
      x: -0.0011702792499846111
      y: 0.0008287327264176271
      z: 0.001553392269779001
  - position:
      x: -0.01853802177390524
      y: 0.004481349977554312
      z: 0.02653935852426206
    orientation:
      x: -0.0030952281104082266
      y: -0.0023223750607017798
      z: -0.002201615607138539
      w: 0.9999900894637611
    bias_acc:
      x: -6.455569210243222e-05
      y: -4.6931727064748774e-05
      z: 0.0148161558721981
    bias_gyro:
      x: -0.0011780295707629145
      y: 0.0008163512370494609
      z: 0.0015447959265587651
  - position:
      x: -0.025985377237285636
      y: 0.00738039346953847
      z: 0.036668337014195994
    orientation:
      x: -0.002178180812616445
      y: -0.0027869777387875576
      z: -0.003044090951858949
      w: 0.9999891108375695
    bias_acc:
      x: -3.812365170010463e-05
      y: -4.5735623313740115e-05
      z: 0.014877209435710873
    bias_gyro:
      x: -0.0011686476648782131
      y: 0.0008310950717560535
      z: 0.0015511046570626725
  - position:
      x: -0.034905667672313026
      y: 0.01103673359141669
      z: 0.04811162682782141
    orientation:
      x: -0.002198154039187926
      y: -0.001240048046613523
      z: -0.0008481427883548524
      w: 0.9999964555204557
    bias_acc:
      x: -0.00016390985383397757
      y: -0.00013030963378688355
      z: 0.014692384016127203
    bias_gyro:
      x: -0.001195670231123006
      y: 0.0007878205249981671
      z: 0.0015351799752108997
  idles:
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: -5.402373502396168e-05
      y: -3.5111260060861704e-05
      z: 0.015021114952426858
    bias_gyro:
      x: -0.0011825108719593458
      y: 0.000838721679750365
      z: 0.0015742481747646603
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: -5.402373502396168e-05
      y: -3.5111260060861704e-05
      z: 0.015021114952426858
    bias_gyro:
      x: -0.0011825108719593458
      y: 0.000838721679750365
      z: 0.0015742481747646603
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: -5.402373502396168e-05
      y: -3.5111260060861704e-05
      z: 0.015021114952426858
    bias_gyro:
      x: -0.0011825108719593458
      y: 0.000838721679750365
      z: 0.0015742481747646603
if_full_window:
  data: false
runtime:
  data: 0.005142338142857143
---
spline:
  start_idx: 0
  dt: 100000000
  start_t: 11004940
  knots:
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: 5.150689497056721e-05
      y: 1.3495184709207678e-06
      z: 0.016633912854231016
    bias_gyro:
      x: -0.0013061908073036328
      y: 0.001012335198139993
      z: 0.0018504711875640565
  - position:
      x: -0.0014628357930617268
      y: -3.39832323841082e-05
      z: 0.0020328323947071503
    orientation:
      x: -0.0005005578204371211
      y: -0.0012886210076816145
      z: -0.0017733018612373077
      w: 0.9999974721459423
    bias_acc:
      x: 4.1409806349834474e-05
      y: -5.304845670547852e-05
      z: 0.016391721530856343
    bias_gyro:
      x: -0.0012977534108402965
      y: 0.000981720839105259
      z: 0.0018024868624972805
  - position:
      x: -0.004314561860119782
      y: 0.00013877876970421905
      z: 0.005665290701167267
    orientation:
      x: -0.0003537719077556266
      y: -0.0018995469701536076
      z: -0.0003549446263600468
      w: 0.9999980702887042
    bias_acc:
      x: 3.12078641613164e-05
      y: 1.2798903492627097e-06
      z: 0.016500079893832436
    bias_gyro:
      x: -0.0012964020443753037
      y: 0.0010062723047465352
      z: 0.0018420382309848279
  - position:
      x: -0.008058646852342996
      y: 0.0011007731939700087
      z: 0.0108632508358385
    orientation:
      x: -0.0020323376037735537
      y: -0.0023377281617316414
      z: -0.0008409903809550894
      w: 0.9999948486697776
    bias_acc:
      x: 5.751187663264588e-05
      y: 1.549461655789526e-05
      z: 0.016439017650030092
    bias_gyro:
      x: -0.0013011394711913255
      y: 0.0009870249246926748
      z: 0.0018125162269751773
  - position:
      x: -0.012766812800895956
      y: 0.002760467614354206
      z: 0.01787515812641435
    orientation:
      x: -0.0019097360842400947
      y: -0.0016369795641810415
      z: -0.0010158864607626987
      w: 0.9999963205835802
    bias_acc:
      x: 3.187768039276824e-05
      y: -6.032974269478392e-05
      z: 0.016471130587998938
    bias_gyro:
      x: -0.0012941870876430081
      y: 0.0010043013349685659
      z: 0.0018308027065155545
  - position:
      x: -0.01856730703811677
      y: 0.004437231292617835
      z: 0.026270620001262866
    orientation:
      x: -0.0030820780790022616
      y: -0.0025235756393669636
      z: -0.0023273729286277076
      w: 0.9999893577913511
    bias_acc:
      x: 4.4473478331877775e-05
      y: -5.307232750011354e-06
      z: 0.016441934735035274
    bias_gyro:
      x: -0.001301586196292581
      y: 0.0009868006671936492
      z: 0.0018198469520148421
  - position:
      x: -0.02603530226329553
      y: 0.007365710798809156
      z: 0.036295769353684205
    orientation:
      x: -0.0020809675288490266
      y: -0.0024351719329473148
      z: -0.003004324825597895
      w: 0.9999903567255777
    bias_acc:
      x: 4.630053279831652e-05
      y: 2.2166801998379597e-06
      z: 0.016467263876500805
    bias_gyro:
      x: -0.0012946040017441044
      y: 0.0010040774863871017
      z: 0.0018282856772980057
  - position:
      x: -0.03500006548887112
      y: 0.010800649575150043
      z: 0.04762095485690898
    orientation:
      x: -0.002400982048934396
      y: -0.0033528028811892537
      z: -0.0014385973916802505
      w: 0.9999904621723084
    bias_acc:
      x: 3.942478885495336e-05
      y: -8.296629251988848e-05
      z: 0.0164614642671629
    bias_gyro:
      x: -0.0013021075227962996
      y: 0.0009842603923454869
      z: 0.0018180556166873829
  - position:
      x: -0.04515816205716707
      y: 0.013842068573057413
      z: 0.060616111853713385
    orientation:
      x: -0.0027206300300902653
      y: -0.0024831039966907416
      z: -0.00698624417221751
      w: 0.9999688118932251
    bias_acc:
      x: 4.6820188244169915e-05
      y: 0.00030970538252717076
      z: 0.016409924325083876
    bias_gyro:
      x: -0.00128106472276257
      y: 0.0010429394688299162
      z: 0.0018503388331074233
  idles:
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: 5.150689497056721e-05
      y: 1.3495184709207678e-06
      z: 0.016633912854231016
    bias_gyro:
      x: -0.0013061908073036328
      y: 0.001012335198139993
      z: 0.0018504711875640565
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: 5.150689497056721e-05
      y: 1.3495184709207678e-06
      z: 0.016633912854231016
    bias_gyro:
      x: -0.0013061908073036328
      y: 0.001012335198139993
      z: 0.0018504711875640565
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: 5.150689497056721e-05
      y: 1.3495184709207678e-06
      z: 0.016633912854231016
    bias_gyro:
      x: -0.0013061908073036328
      y: 0.001012335198139993
      z: 0.0018504711875640565
if_full_window:
  data: false
runtime:
  data: 0.006103600125000001
---
spline:
  start_idx: 0
  dt: 100000000
  start_t: 11004940
  knots:
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: 0.00012455600246689947
      y: 4.7161703455412605e-05
      z: 0.01826908781255448
    bias_gyro:
      x: -0.0014298105914479378
      y: 0.0011781926856690207
      z: 0.00212363905190754
  - position:
      x: -0.0014543564134272859
      y: -3.543290094011518e-05
      z: 0.002013783402979575
    orientation:
      x: -0.000490936035929536
      y: -0.0013017211195739912
      z: -0.0017972278032460307
      w: 0.9999974172347432
    bias_acc:
      x: 0.00011456300095385134
      y: -5.359371792242893e-06
      z: 0.018031970595071042
    bias_gyro:
      x: -0.0014216975319329948
      y: 0.00114792585303477
      z: 0.0020755289180030717
  - position:
      x: -0.0042940874663943305
      y: 0.00013267661135559256
      z: 0.005612636347389133
    orientation:
      x: -0.0003389531186492106
      y: -0.001917108275222212
      z: -0.00037860396018071194
      w: 0.9999980332309463
    bias_acc:
      x: 0.00010576479304849086
      y: 4.8028572636980614e-05
      z: 0.018144723612397592
    bias_gyro:
      x: -0.0014202489508394714
      y: 0.001172746935844907
      z: 0.002116233596580698
  - position:
      x: -0.008024313029271896
      y: 0.0010852906940262204
      z: 0.010760571016435056
    orientation:
      x: -0.002011365956354208
      y: -0.0023720427799003396
      z: -0.0009062735431654771
      w: 0.999994753230391
    bias_acc:
      x: 0.00013404275904845608
      y: 6.629025262937128e-05
      z: 0.018088248275310994
    bias_gyro:
      x: -0.0014250757016353764
      y: 0.00115325304649299
      z: 0.0020843466912126665
  - position:
      x: -0.01271969761432372
      y: 0.002731493613913
      z: 0.017704630543075625
    orientation:
      x: -0.0018809781358140264
      y: -0.0016635407430993007
      z: -0.0010322223250514005
      w: 0.9999963145284713
    bias_acc:
      x: 0.00011003169412497996
      y: -1.7703792151457087e-05
      z: 0.01812661855723121
    bias_gyro:
      x: -0.0014181820735878297
      y: 0.0011710364080829388
      z: 0.0021071916513927544
  - position:
      x: -0.018510088587684083
      y: 0.00438392361108263
      z: 0.026017076010530524
    orientation:
      x: -0.003051304884777547
      y: -0.0025965576433776357
      z: -0.002501980207871655
      w: 0.9999888436987409
    bias_acc:
      x: 0.00012263175817285452
      y: 5.52647999367421e-05
      z: 0.018096618329436924
    bias_gyro:
      x: -0.0014253389038915482
      y: 0.0011529831257166263
      z: 0.0020885185533666634
  - position:
      x: -0.025973851658676373
      y: 0.00729656226544765
      z: 0.03593177438251904
    orientation:
      x: -0.0020314763395990966
      y: -0.0024271183498810987
      z: -0.0028538750807966698
      w: 0.999990918757478
    bias_acc:
      x: 0.00012599765358878979
      y: 2.964325311855969e-05
      z: 0.018127810741382717
    bias_gyro:
      x: -0.001419148020627844
      y: 0.0011696428073155595
      z: 0.002108453750625674
  - position:
      x: -0.03493475512942605
      y: 0.010644674793101673
      z: 0.047164930133160636
    orientation:
      x: -0.0023858648796645666
      y: -0.0035794830904020683
      z: -0.0021487763393605542
      w: 0.9999884387880825
    bias_acc:
      x: 0.00011726476249409101
      y: 5.2596739804743815e-06
      z: 0.01812676217461368
    bias_gyro:
      x: -0.0014239237306377282
      y: 0.001155698375116128
      z: 0.0020857211717907535
  - position:
      x: -0.045118592482738244
      y: 0.013823423073608626
      z: 0.05991450132188216
    orientation:
      x: -0.0024857137278649108
      y: -0.001759998834305091
      z: -0.004368401762307135
      w: 0.9999858202481725
    bias_acc:
      x: 0.00012600949366510148
      y: 5.784275224759842e-05
      z: 0.01805786177219344
    bias_gyro:
      x: -0.0014201330595256278
      y: 0.001168853261857141
      z: 0.0021131621452928026
  - position:
      x: -0.05606112171526622
      y: 0.017840493238809145
      z: 0.07435287921055914
    orientation:
      x: -0.0024519203079374345
      y: -0.003079672476159606
      z: -0.002071109091377986
      w: 0.9999901070567552
    bias_acc:
      x: 0.00010092232257919771
      y: -6.144634914377229e-05
      z: 0.01835605908551555
    bias_gyro:
      x: -0.0014286410237913125
      y: 0.0011382319989418068
      z: 0.0020436532157010025
  idles:
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: 0.00012455600246689947
      y: 4.7161703455412605e-05
      z: 0.01826908781255448
    bias_gyro:
      x: -0.0014298105914479378
      y: 0.0011781926856690207
      z: 0.00212363905190754
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: 0.00012455600246689947
      y: 4.7161703455412605e-05
      z: 0.01826908781255448
    bias_gyro:
      x: -0.0014298105914479378
      y: 0.0011781926856690207
      z: 0.00212363905190754
  - position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
    bias_acc:
      x: 0.00012455600246689947
      y: 4.7161703455412605e-05
      z: 0.01826908781255448
    bias_gyro:
      x: -0.0014298105914479378
      y: 0.0011781926856690207
      z: 0.00212363905190754
if_full_window:
  data: false
runtime:
  data: 0.006738976666666667
---


dsh@dsh-Precision-5680:~/Documents/work_logs/code/SFUISE/sfuise_ws$ ros2 topic echo /bspline_optimization_window
header:
  stamp:
    sec: 1745318211
    nanosec: 273811910
  frame_id: map
poses: []
---
header:
  stamp:
    sec: 1745318211
    nanosec: 330692467
  frame_id: map
poses: []
---


gt.back()
[EstimationInterface-3] 166 4959 7004 0031 6238
[EstimationInterface-3] 1664959700420329094
[EstimationInterface-3] 1664959700440330982
[EstimationInterface-3] 1664959700460322142
[EstimationInterface-3] 1664959700480334997
[EstimationInterface-3] 1664959700500341892
[EstimationInterface-3] 1664959700520318508

[SplineFusion-4] spline_local_numknots:2
[EstimationInterface-3] [INFO] [1745322990.578511244] [EstimationInterface]: sys_calib: @@@@@@@@ 
[EstimationInterface-3] spline_global_numknots:2
[EstimationInterface-3] gt.size:189
[EstimationInterface-3] gt.time:1664959673400324106
[EstimationInterface-3] spline_local.minTimeNs():1100 4940
[EstimationInterface-3] spline_local.maxTimeNs():111004939
[EstimationInterface-3] cnt:0
[SplineFusion-4] spline_local_numknots:3
[EstimationInterface-3] [INFO] [1745322990.637285925] [EstimationInterface]: sys_calib: @@@@@@@@ 
[EstimationInterface-3] spline_global_numknots:3
[EstimationInterface-3] gt.size:192
[EstimationInterface-3] gt.time:1664959673400324106
[EstimationInterface-3] spline_local.minTimeNs():11004940
[EstimationInterface-3] spline_local.maxTimeNs():211004939
[EstimationInterface-3] cnt:0
[SplineFusion-4] spline_local_numknots:4
[EstimationInterface-3] [INFO] [1745322990.760336670] [EstimationInterface]: sys_calib: @@@@@@@@ 
[EstimationInterface-3] spline_global_numknots:4
[EstimationInterface-3] gt.size:198
[EstimationInterface-3] gt.time:1664959673400324106
[EstimationInterface-3] spline_local.minTimeNs():11004940
[EstimationInterface-3] spline_local.maxTimeNs():311004939
[EstimationInterface-3] cnt:0
[SplineFusion-4] spline_local_numknots:5
[EstimationInterface-3] [INFO] [1745322990.863412812] [EstimationInterface]: sys_calib: @@@@@@@@ 
[EstimationInterface-3] spline_global_numknots:5
[EstimationInterface-3] gt.size:203
[EstimationInterface-3] gt.time:1664959673400324106
[EstimationInterface-3] spline_local.minTimeNs():11004940
[EstimationInterface-3] spline_local.maxTimeNs():411004939
[EstimationInterface-3] cnt:0
[SplineFusion-4] spline_local_numknots:6
[EstimationInterface-3] [INFO] [1745322990.992279246] [EstimationInterface]: sys_calib: @@@@@@@@ 
[EstimationInterface-3] spline_global_numknots:6
[EstimationInterface-3] gt.size:210
[EstimationInterface-3] gt.time:1664959673400324106
[EstimationInterface-3] spline_local.minTimeNs():11004940
[EstimationInterface-3] spline_local.maxTimeNs():511004939
[EstimationInterface-3] cnt:0
[SplineFusion-4] spline_local_numknots:7
[EstimationInterface-3] [INFO] [1745322991.061330347] [EstimationInterface]: sys_calib: @@@@@@@@ 
[EstimationInterface-3] spline_global_numknots:7
[EstimationInterface-3] gt.size:213
[EstimationInterface-3] gt.time:1664959673400324106
[EstimationInterface-3] spline_local.minTimeNs():11004940
[EstimationInterface-3] spline_local.maxTimeNs():611004939
[EstimationInterface-3] cnt:0
[SplineFusion-4] spline_local_numknots:8
[EstimationInterface-3] [INFO] [1745322991.177368017] [EstimationInterface]: sys_calib: @@@@@@@@ 
[EstimationInterface-3] spline_global_numknots:8
[EstimationInterface-3] gt.size:219
[EstimationInterface-3] gt.time:1664959673400324106
[EstimationInterface-3] spline_local.minTimeNs():11004940
[EstimationInterface-3] spline_local.maxTimeNs():711004939
[EstimationInterface-3] cnt:0
[SplineFusion-4] spline_local_numknots:9
[EstimationInterface-3] [INFO] [1745322991.261459656] [EstimationInterface]: sys_calib: @@@@@@@@ 
[EstimationInterface-3] spline_global_numknots:9
[EstimationInterface-3] gt.size:223
[EstimationInterface-3] gt.time:1664959673400324106
[EstimationInterface-3] spline_local.minTimeNs():11004940
[EstimationInterface-3] spline_local.maxTimeNs():811004939
[EstimationInterface-3] cnt:0
[SplineFusion-4] spline_local_numknots:10
[EstimationInterface-3] [INFO] [1745322991.380446578] [EstimationInterface]: sys_calib: @@@@@@@@ 
[EstimationInterface-3] spline_global_numknots:10
[EstimationInterface-3] gt.size:229
[EstimationInterface-3] gt.time:1664959673400324106
[EstimationInterface-3] spline_local.minTimeNs():11004940
[EstimationInterface-3] spline_local.maxTimeNs():911004939
[EstimationInterface-3] cnt:0





[EstimationInterface-3] spline_global_numknots:142
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] [INFO] [1745742725.569409167] [EstimationInterface]: sys_calib: @@@@@@@@ 
[EstimationInterface-3] spline_global_numknots:143
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] [INFO] [1745742725.977735181] [EstimationInterface]: sys_calib: @@@@@@@@ 
[EstimationInterface-3] spline_global_numknots:144
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] [INFO] [1745742726.358196810] [EstimationInterface]: sys_calib: @@@@@@@@ 
[EstimationInterface-3] spline_global_numknots:145
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] [INFO] [1745742726.686598102] [EstimationInterface]: sys_calib: @@@@@@@@ 
[EstimationInterface-3] spline_global_numknots:146
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] [INFO] [1745742726.955986009] [EstimationInterface]: sys_calib: @@@@@@@@ 
[EstimationInterface-3] spline_global_numknots:147
[EstimationInterface-3] [INFO] [1745742727.308999877] [EstimationInterface]: sys_calib: @@@@@@@@ 
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:148
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] [INFO] [1745742727.630991616] [EstimationInterface]: sys_calib: @@@@@@@@ 
[EstimationInterface-3] spline_global_numknots:149
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] [INFO] [1745742727.963089951] [EstimationInterface]: sys_calib: @@@@@@@@ 
[EstimationInterface-3] spline_global_numknots:150
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:151
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:152
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:153
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:154
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:155
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:156
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:157
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:158
[EstimationInterface-3] spline_global_numknots:159
[SplineFusion-4] spline_local_numknots:100
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:160
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:161
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:162
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:163
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:164
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:165
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:166
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:167
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:168
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:169
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:170
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:171
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:172
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:173
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:174
[EstimationInterface-3] spline_global_numknots:175
[SplineFusion-4] spline_local_numknots:100
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:176
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:177
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:178
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:179
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:180
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:181
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:182
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:183
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:184
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:185
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:186
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:187
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:188
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:189
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:190
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:191
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:192
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:193
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:194
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:195
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:196
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:197
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:198
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:199
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:200
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:201
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:202
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:203
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:204
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:205
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:206
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:207
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:208
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:209
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:210
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:211
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:212
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:213
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:214
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:215
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:216
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:217
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:218
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:219
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:220
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:221
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:222
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:223
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:224
[SplineFusion-4] spline_local_numknots:100
[EstimationInterface-3] spline_global_numknots:225
[SplineFusion-4] CHOLMOD warning: matrix not positive definite. file: ../Supernodal/t_cholmod_super_numeric.c line: 911



dsh@dsh-Precision-5680:~/Documents/work_logs/code/SFUISE/sfuise_ws2$ ros2 topic list 
/accel_data
/active_control_points
/anchor_list
/baro_data
/bspline_optimization_old
/bspline_optimization_window
/clicked_point
/est_window
/events/read_split
/flow_data
/goal_pose
/gyro_data
/imu_data
/imu_ds
/inactive_control_points
/initialpose
/map
/map_updates
/opt_pose
/opt_pose_array
/parameter_events
/path
/path1
/pose_data
/robot_0/current_pose
/robot_1/current_pose
/robot_2/current_pose
/robot_3/current_pose
/robot_4/current_pose
/robot_5/current_pose
/rosout
/start_time
/sys_calib
/tdoa_data
/tdoa_ds
/tf
/tf_static
/tof_data
/visualization_anchor


