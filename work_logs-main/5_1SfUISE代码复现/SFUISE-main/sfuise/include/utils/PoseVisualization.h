#pragma once // 防止头文件被多次包含

#include <ros/ros.h> // 引入ROS库
#include <std_msgs/ColorRGBA.h> // 引入颜色消息类型
#include <visualization_msgs/Marker.h> // 引入可视化标记消息类型
#include <Eigen/Dense> // 引入Eigen库的密集矩阵功能
#include <Eigen/Geometry> // 引入Eigen库的几何功能

// PoseVisualization类用于可视化姿态
class PoseVisualization
{

public:
    // 构造函数，初始化缩放比例和线宽
    PoseVisualization() : scale(0.3), line_width(0.023) {};

    // 设置线条颜色
    void setColor(float r, float g, float b, float a = 1.0) {
        line_color.r = r; // 设置红色分量
        line_color.g = g; // 设置绿色分量
        line_color.b = b; // 设置蓝色分量
        line_color.a = a; // 设置透明度
    }

    // 发布姿态信息
    void pubPose(const Eigen::Vector3d& p, const Eigen::Quaterniond& q, ros::Publisher& pub, const std_msgs::Header& header)
    {
        visualization_msgs::Marker marker; // 创建标记对象
        marker.header = header; // 设置标记头部信息
        marker.id = 0; // 设置标记ID
        marker.type = visualization_msgs::Marker::LINE_STRIP; // 设置标记类型为线条
        marker.action = visualization_msgs::Marker::ADD; // 设置标记动作为添加
        marker.scale.x = line_width; // 设置线条宽度
        marker.pose.position.x = 0.0; // 设置位置坐标
        marker.pose.position.y = 0.0;
        marker.pose.position.z = 0.0;
        marker.pose.orientation.w = 1.0; // 设置初始方向
        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = 0.0;

        // 定义多个点
        geometry_msgs::Point pt_lt, pt_lb, pt_rt, pt_rb, pt_oc, pt_lt0, pt_lt1, pt_lt2;
        // 计算每个点的位置并转换为geometry_msgs::Point格式
        eigen2Point(q * (scale * imlt) + p, pt_lt);
        eigen2Point(q * (scale * imlb) + p, pt_lb);
        eigen2Point(q * (scale * imrt) + p, pt_rt);
        eigen2Point(q * (scale * imrb) + p, pt_rb);
        eigen2Point(q * (scale * lt0 ) + p, pt_lt0);
        eigen2Point(q * (scale * lt1 ) + p, pt_lt1);
        eigen2Point(q * (scale * lt2 ) + p, pt_lt2);
        eigen2Point(q * (scale * oc  ) + p, pt_oc);

        // 添加点和颜色到标记中
        marker.points.push_back(pt_lt);
        marker.points.push_back(pt_lb);
        marker.colors.push_back(line_color);
        marker.colors.push_back(line_color);
        marker.points.push_back(pt_lb);
        marker.points.push_back(pt_rb);
        marker.colors.push_back(line_color);
        marker.colors.push_back(line_color);
        marker.points.push_back(pt_rb);
        marker.points.push_back(pt_rt);
        marker.colors.push_back(line_color);
        marker.colors.push_back(line_color);
        marker.points.push_back(pt_rt);
        marker.points.push_back(pt_lt);
        marker.colors.push_back(line_color);
        marker.colors.push_back(line_color);
        marker.points.push_back(pt_lt0);
        marker.points.push_back(pt_lt1);
        marker.colors.push_back(line_color);
        marker.colors.push_back(line_color);
        marker.points.push_back(pt_lt1);
        marker.points.push_back(pt_lt2);
        marker.colors.push_back(line_color);
        marker.colors.push_back(line_color);
        marker.points.push_back(pt_lt);
        marker.points.push_back(pt_oc);
        marker.colors.push_back(line_color);
        marker.colors.push_back(line_color);
        marker.points.push_back(pt_lb);
        marker.points.push_back(pt_oc);
        marker.colors.push_back(line_color);
        marker.colors.push_back(line_color);
        marker.points.push_back(pt_rt);
        marker.points.push_back(pt_oc);
        marker.colors.push_back(line_color);
        marker.colors.push_back(line_color);
        marker.points.push_back(pt_rb);
        marker.points.push_back(pt_oc);
        marker.colors.push_back(line_color);
        marker.colors.push_back(line_color);

        pub.publish(marker); // 发布标记
    }

private:
    std_msgs::ColorRGBA line_color; // 线条颜色
    double scale; // 缩放比例
    double line_width; // 线宽
    static const Eigen::Vector3d imlt; // 左上点
    static const Eigen::Vector3d imlb; // 左下点
    static const Eigen::Vector3d imrt; // 右上点
    static const Eigen::Vector3d imrb; // 右下点
    static const Eigen::Vector3d oc; // 中心点
    static const Eigen::Vector3d lt0; // 左上点0
    static const Eigen::Vector3d lt1; // 左上点1
    static const Eigen::Vector3d lt2; // 左上点2

    // 将Eigen向量转换为geometry_msgs::Point
    void eigen2Point(const Eigen::Vector3d& v, geometry_msgs::Point& p)
    {
        p.x = v.x(); // 设置x坐标
        p.y = v.y(); // 设置y坐标
        p.z = v.z(); // 设置z坐标
    }
};

// 定义静态常量向量
const Eigen::Vector3d PoseVisualization::imlt = Eigen::Vector3d(-0.7, -0.7, -0.5);
const Eigen::Vector3d PoseVisualization::imlb = Eigen::Vector3d(-0.7, 0.7, -0.5);
const Eigen::Vector3d PoseVisualization::imrt = Eigen::Vector3d(-0.7, -0.7, 0.5);
const Eigen::Vector3d PoseVisualization::imrb = Eigen::Vector3d(-0.7, 0.7, 0.5);
const Eigen::Vector3d PoseVisualization::oc = Eigen::Vector3d(0.0, 0.0, 0.0);
const Eigen::Vector3d PoseVisualization::lt0 = Eigen::Vector3d(-0.7, -0.35, -0.5);
const Eigen::Vector3d PoseVisualization::lt1 = Eigen::Vector3d(-0.7, -0.35, -0.25);
const Eigen::Vector3d PoseVisualization::lt2 = Eigen::Vector3d(-0.7, -0.7, -0.25);
