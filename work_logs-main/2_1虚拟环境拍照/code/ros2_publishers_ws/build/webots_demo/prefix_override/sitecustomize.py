import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/ljl/Documents/工作目录/2_1虚拟环境拍照/code/ros2_publishers_ws/install/webots_demo'
