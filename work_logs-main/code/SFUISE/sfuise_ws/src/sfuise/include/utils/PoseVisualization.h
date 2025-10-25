#pragma once

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/color_rgba.hpp>
#include <visualization_msgs/msg/marker.hpp>
#include <Eigen/Dense>
#include <Eigen/Geometry>

class PoseVisualization
{
public:
    PoseVisualization() : scale(0.3), line_width(0.023) {};

    void setColor(float r, float g, float b, float a = 1.0) {
        line_color.r = r;
        line_color.g = g;
        line_color.b = b;
        line_color.a = a;
    }

    void pubPose(const Eigen::Vector3d& p, const Eigen::Quaterniond& q, rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr pub, const std_msgs::msg::Header& header)
    {
        visualization_msgs::msg::Marker marker;
        marker.header = header;
        marker.id = 0;
        marker.type = visualization_msgs::msg::Marker::LINE_STRIP;
        marker.action = visualization_msgs::msg::Marker::ADD;
        marker.scale.x = line_width;
        marker.pose.position.x = 0.0;
        marker.pose.position.y = 0.0;
        marker.pose.position.z = 0.0;
        marker.pose.orientation.w = 1.0;
        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = 0.0;
        
        // Define the points
        geometry_msgs::msg::Point pt_lt, pt_lb, pt_rt, pt_rb, pt_oc, pt_lt0, pt_lt1, pt_lt2;
        eigen2Point(q * (scale * imlt) + p, pt_lt);
        eigen2Point(q * (scale * imlb) + p, pt_lb);
        eigen2Point(q * (scale * imrt) + p, pt_rt);
        eigen2Point(q * (scale * imrb) + p, pt_rb);
        eigen2Point(q * (scale * lt0 ) + p, pt_lt0);
        eigen2Point(q * (scale * lt1 ) + p, pt_lt1);
        eigen2Point(q * (scale * lt2 ) + p, pt_lt2);
        eigen2Point(q * (scale * oc  ) + p, pt_oc);

        // Add points and colors to the marker
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
        
        // Publish the marker
        pub->publish(marker);
    }

private:
    std_msgs::msg::ColorRGBA line_color;
    double scale;
    double line_width;
    
    // Define static points
    static const Eigen::Vector3d imlt;
    static const Eigen::Vector3d imlb;
    static const Eigen::Vector3d imrt;
    static const Eigen::Vector3d imrb;
    static const Eigen::Vector3d oc;
    static const Eigen::Vector3d lt0;
    static const Eigen::Vector3d lt1;
    static const Eigen::Vector3d lt2;

    void eigen2Point(const Eigen::Vector3d& v, geometry_msgs::msg::Point& p)
    {
        p.x = v.x();
        p.y = v.y();
        p.z = v.z();
    }
};

// Define the static points
const Eigen::Vector3d PoseVisualization::imlt = Eigen::Vector3d(-0.7, -0.7, -0.5);
const Eigen::Vector3d PoseVisualization::imlb = Eigen::Vector3d(-0.7, 0.7, -0.5);
const Eigen::Vector3d PoseVisualization::imrt = Eigen::Vector3d(-0.7, -0.7, 0.5);
const Eigen::Vector3d PoseVisualization::imrb = Eigen::Vector3d(-0.7, 0.7, 0.5);
const Eigen::Vector3d PoseVisualization::oc = Eigen::Vector3d(0.0, 0.0, 0.0);
const Eigen::Vector3d PoseVisualization::lt0 = Eigen::Vector3d(-0.7, -0.35, -0.5);
const Eigen::Vector3d PoseVisualization::lt1 = Eigen::Vector3d(-0.7, -0.35, -0.25);
const Eigen::Vector3d PoseVisualization::lt2 = Eigen::Vector3d(-0.7, -0.7, -0.25);
