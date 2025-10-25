import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/ljl/Documents/工作目录/2_1虚拟环境拍照/code/webots_epuck_ws/install/webots_epuck'
