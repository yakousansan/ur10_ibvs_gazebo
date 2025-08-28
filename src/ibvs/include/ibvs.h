#ifndef IK_H
#define IK_H

#include <chrono>
#include <iomanip>
#include <sstream>
#include "sensor_msgs/msg/image.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "sensor_msgs/msg/camera_info.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include <visp3/core/vpCameraParameters.h>
#include <visp3/core/vpPoint.h>
#include <visp3/visual_features/vpFeaturePoint.h>
#include <visp3/vs/vpServo.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <vector>
#include "tf2/transform_datatypes.h"
#include "tf2/exceptions.h"
#include "tf2_ros/buffer.h"
#include "tf2_ros/transform_listener.h"
#include <Eigen/Dense>

class VisualServoInit : public rclcpp::Node
{
public:
    // 构造函数析沟函数
    VisualServoInit();
    ~VisualServoInit();
private:
    //定义成员变量
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr rgb_subscriber;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr depth_subscriber;
    rclcpp::Subscription<sensor_msgs::msg::CameraInfo>::SharedPtr rgb_cam_info_sub_;
    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_state_subscriber_;
    rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr jacobian_subscriber_;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr joint_velocity_publisher_;
    //声明一个类型为 vpCameraParameters 的成员变量 cam_params_，用于存储相机内参数据。
    vpCameraParameters cam_params_;
    // 存储检测到的角点
        // vpImagePoint 是 ViSP 库中表示图像点的类，包含像素坐标（y, x）信息。这个变量的完整含义：存储 vpImagePoint 类型的动态数组
        // std::vector：动态数组容器，可以理解为 “能够自动扩容的数组”
    std::vector<vpImagePoint> detected_corners_;  
    // 存储目标特征点（期望的角点位置,用于存储目标特征点)
        // vpFeaturePoint 是 ViSP 库中表示特征点的类，包含特征点的像素坐标、深度等信息。
        // std::vector<vpFeaturePoint> 是 ViSP 库中表示特征点的动态数组容器，存储多个 vpFeaturePoint 对象。
    std::vector<vpFeaturePoint> target_features_;
    // 目标特征点的中心坐标和偏移量
    double center_u_ = 320.0; // 图像中心u坐标
    double center_v_ = 240.0; // 图像中心v坐标
    double offset_u_ = 100.0;  // 水平偏移量
    double offset_v_ = 100.0;  // 垂直偏移量
    // 目标特征点的像素坐标（用于存储目标特征点的像素坐标）
    std::vector<vpImagePoint> target_pixels_; 
    // 定义当前特征点（用于存储当前检测到的特征点）
    std::vector<vpFeaturePoint> current_features_;
    // 定义特征误差（用于存储特征点的误差）
    vpColVector feature_error_;
    // 特征误差阈值
    double error_threshold_ = 0.01;
    // 定义伺服控制器
    vpServo task;
    // 定义伺服控制器的增益
    double lambda_ = 0.3;
    // 相机速度指令
    vpColVector cam_velocity_cmd;
    geometry_msgs::msg::Twist camera_vel_cmd;
    geometry_msgs::msg::Twist camera_vel_cmd_in_base;
    // 定义TF2相关变量
    tf2_ros::Buffer tf_buffer_;
    tf2_ros::TransformListener tf_listener_;
    // 存储当前雅可比矩阵
    Eigen::MatrixXd current_jacobian_;
    // 定义绘图变量
    std::ofstream joint_vel_data_file;
    std::ofstream error_data_file;
    // 定义回调函数
    void rgb_callback(const sensor_msgs::msg::Image::SharedPtr msg);
    void depth_callback(const sensor_msgs::msg::Image::SharedPtr msg);
    void rgb_camera_info_callback(const sensor_msgs::msg::CameraInfo::SharedPtr msg);
    void jointStateCallback(const sensor_msgs::msg::JointState::SharedPtr msg);
    void joint_velocity_publisher_callback();
    void jacobianCallback(const std_msgs::msg::Float64MultiArray::SharedPtr msg);

    // 定义成员函数
    bool detect_rectangle_corners(const cv::Mat& img, std::vector<vpImagePoint>& corners);
    void init_target_features();
    bool compute_feature_error();
    void init_visual_servo();
    void ConvertCameraVelToBaseVel(const std::string &camera_frame, const std::string &base_frame);
    void convertBaseVelToJointVel();


};

#endif