ROS QR 跟踪器
==============

一个用于 [ROS](http://www.ros.org/) 的 [QR 码](https://en.wikipedia.org/wiki/QR_code) 跟踪包。

安装
------------

安装依赖项：

    sudo apt-get install libffi-dev libffi6 libzbar-dev python-catkin-pkg
    pip install libzbar-cffi

使用 git 检出到您的 Catkin 工作区或覆盖中，然后构建：

    mkdir -p overlay/src
    cd overlay/src
    catkin_init_workspace
    git clone https://github.com/chrisspen/ros_qr_tracker.git
    cd ..
    catkin_make --pkg ros_qr_tracker

使用
-----

运行：

    rosrun ros_qr_tracker qr_tracker.py _topic:=/mycamera/image/compressed

启动时，节点处于空闲状态。要开始跟踪 QR 码，请运行：

    rosservice call /qr_tracker/start

如果找到任何 QR 码，它们将通过主题 `/qr_tracker/matches` 广播，您可以使用以下命令监控：

    rostopic echo /qr_tracker/matches

如果您想跟踪包含特定文本的 QR 码，请设置目标：

    rosservice call /qr_tracker/set_target "一些文本"

要清除目标并跟踪所有 QR 码，请运行：

    rosservice call /qr_tracker/clear_target

要使用网络摄像头进行测试，请运行：

    rosrun ros_qr_tracker webcam.py _start:=1

要创建 QR 码：

    create_qr_code.py "一些文本" myqrcode.jpg

并使用以下命令查看：

    sudo apt-get install ros-kinetic-rqt-image-view
    rosrun rqt_image_view rqt_image_view image:=/webcam/image _image_transport:=compressed

然后打印出一个 QR 码，慢慢放在摄像头前面，并确认从 `/qr_tracker/matches` 广播的消息。

测试
-------

在本地运行测试：

    ./test.sh
