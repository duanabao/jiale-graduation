import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/dsh/Documents/work_logs/2_5二维码定位接收/code/webots_epuck_ws/install/webots_epuck'
