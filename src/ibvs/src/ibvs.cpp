#include "rclcpp/rclcpp.hpp"
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
    //构造函数
    VisualServoInit() : Node("ibvs"), 
                        tf_buffer_(this->get_clock()), 
                        tf_listener_(tf_buffer_)
    {
     // 订阅相机内参话题
    rgb_cam_info_sub_ = this->create_subscription<sensor_msgs::msg::CameraInfo>("/rgb/camera_info", 10,
            std::bind(&VisualServoInit::rgb_camera_info_callback, this, std::placeholders::_1));   
    // 订阅彩色图像话题
    rgb_subscriber = this->create_subscription<sensor_msgs::msg::Image>("/rgb/image_raw",10,
            std::bind(&VisualServoInit::rgb_callback, this, std::placeholders::_1));
    // 订阅深度图像话题
    depth_subscriber = this->create_subscription<sensor_msgs::msg::Image>("/depth/image_raw",10,
            std::bind(&VisualServoInit::depth_callback, this, std::placeholders::_1));
     // 订阅机械臂当前的关节角度
    joint_state_subscriber_ = this->create_subscription<sensor_msgs::msg::JointState>("/joint_states", 10, 
            std::bind(&VisualServoInit::jointStateCallback, this, std::placeholders::_1));
    // // 订阅机械臂的雅可比矩阵
    // jacobian_client_ = this->create_client<service_interfaces::srv::GetJacobian>("get_jacobian");
    // // 创建一个定时器，用于周期性地发布关节速度指令
    // velocity_publisher_timer_ = this->create_wall_timer(std::chrono::milliseconds(10),std::bind(&VisualServoInit::velocity_publisher_callback, this));
    // 发布关节速度指令
    velocity_publisher_ = this->create_publisher<std_msgs::msg::Float64MultiArray>("/ur5_arm_vel_controller/commands", 10);
    // 创建显示窗口
    cv::namedWindow("Detected Corners", cv::WINDOW_NORMAL);
    // 调整窗口大小
    cv::resizeWindow("Detected Corners", 640, 480);

    //RCLCPP_INFO(this->get_logger(), "节点初始化完成");   
    }
    
    ~VisualServoInit()
    {    
            // 取消订阅话题
            rgb_subscriber.reset();
            depth_subscriber.reset();
            rgb_cam_info_sub_.reset();
            joint_state_subscriber_.reset();
            velocity_publisher_.reset();
            // 销毁OpenCV窗口
            cv::destroyWindow("Detected Corners");
            // 释放OpenCV资源
            cv::waitKey(1); 
            //RCLCPP_INFO(this->get_logger(), "节点已关闭");
    }
    
private:
    //定义成员变量
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr rgb_subscriber;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr depth_subscriber;
    rclcpp::Subscription<sensor_msgs::msg::CameraInfo>::SharedPtr rgb_cam_info_sub_;
    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_state_subscriber_;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr velocity_publisher_;
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
    double offset_u_ = 50.0;  // 水平偏移量
    double offset_v_ = 50.0;  // 垂直偏移量
    // 目标特征点的像素坐标（用于存储目标特征点的像素坐标）
    std::vector<vpImagePoint> target_pixels_; 
    // 定义当前特征点（用于存储当前检测到的特征点）
    std::vector<vpFeaturePoint> current_features_;
    // 定义特征误差（用于存储特征点的误差）
    vpColVector feature_error_;

    // 定义伺服控制器
    vpServo task;
    // 定义伺服控制器的增益
    double lambda_ = 1.0;
    // 相机速度指令
    vpColVector cam_velocity_cmd;
    geometry_msgs::msg::Twist camera_vel_cmd;
    geometry_msgs::msg::Twist camera_vel_cmd_in_base;
    // 定义TF2相关变量
    tf2_ros::Buffer tf_buffer_;
    tf2_ros::TransformListener tf_listener_;
    // 定义回调函数（当收到话题的消息，会自动调用回调函数） 
    void rgb_callback(const sensor_msgs::msg::Image::SharedPtr msg)
    {
        try
        {   
            // //图像尺寸检查
            // RCLCPP_INFO(this->get_logger(), "ROS图像消息尺寸: 宽=%d, 高=%d, 编码=%s", msg->width, msg->height, msg->encoding.c_str());

            // 将ROS图像消息转换为OpenCV（rgb8格式→cv::Mat格式：RGB）
            cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::RGB8);
            cv::Mat img_rgb = cv_ptr->image;
            // RCLCPP_ERROR(this->get_logger(), "回调函数接收到图像，宽: %d, 高: %d", img.cols, img.rows); 
            
            // 检测图像是否有效
            // if (img.empty()) {
            //     RCLCPP_ERROR(this->get_logger(), "回调函数接收为空图像，跳过检测");
            //     return;
            // }
            // if (img.cols <= 0 || img.rows <= 0) {
            //     RCLCPP_ERROR(this->get_logger(), "图像尺寸无效（宽: %d, 高: %d），跳过检测", img.cols, img.rows);
            //     return;
            // }

            // 图像格式转换：RGB→BGR
            cv::Mat img_bgr;
            cv::cvtColor(img_rgb, img_bgr, cv::COLOR_RGB2BGR);
            cv::Mat img_copy = img_bgr.clone();
            // 检测角点
            detected_corners_.clear();
            bool detection_success = detect_rectangle_corners(img_bgr, detected_corners_);

            if (detection_success) {
                //RCLCPP_INFO(this->get_logger(), "成功检测到%d个角点", (int)detected_corners_.size());

                // 在图像上绘制检测到的角点以及编号
                    for (size_t i = 0; i < detected_corners_.size(); ++i) {
                        // 获取ViSP格式的角点坐标
                        const auto& corner = detected_corners_[i];
                        // 将ViSP格式的角点转换为OpenCV格式
                        cv::Point pt(corner.get_u(), corner.get_v());
                        // 绘制角点
                        cv::circle(img_copy, pt, 5, cv::Scalar(0, 255, 0), -1);
                        // 绘制编号
                        cv::putText(img_copy, std::to_string(i + 1), 
                                    cv::Point(pt.x + 10, pt.y - 10),
                                    cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 0, 0), 1);
                    }
                    // 右上角显示文字
                        std::string status = "Corners detected";
                        // cv::putText函数用于在图像上绘制文本
                        cv::putText(img_copy, status,
                        cv::Point(640 - 180, 30),
                        // cv::FONT_HERSHEY_SIMPLEX表示字体类型
                        cv::FONT_HERSHEY_SIMPLEX, 0.4, 
                        cv::Scalar(0, 255, 0), 2);  

                // 将检测到的角点转换为ViSP格式的特征点
                    // 清空当前特征点容器
                    current_features_.clear();
                    // 遍历检测到的角点，将其转换为ViSP格式的特征点并存储
                    for (size_t i = 0; i < detected_corners_.size(); ++i) {
                        // 获取ViSP格式的角点坐标
                        const auto& corner = detected_corners_[i];
                        // 获取角点的像素坐标（u, v）
                        double u = corner.get_u(); 
                        double v = corner.get_v();
                        // 转换为归一化坐标（x, y）
                        double x = (u - cam_params_.get_u0()) / cam_params_.get_px();  // 归一化x
                        double y = (v - cam_params_.get_v0()) / cam_params_.get_py();  // 归一化y
                        // 创建一个新的vpFeaturePoint对象
                        vpFeaturePoint feature;
                        // 设置特征点的像素坐标和归一化坐标
                        feature.set_x(x);
                        feature.set_y(y);
                        // 存入当前特征点容器
                        current_features_.push_back(feature);
                        // 打印坐标信息u和v以及x和y
                        //RCLCPP_INFO(this->get_logger(), "特征点坐标: u=%.2f, v=%.2f, x=%.2f, y=%.2f",corner.get_u(), corner.get_v(), feature.get_x(), feature.get_y());
                        // 相机内参打印
                        //RCLCPP_INFO(this->get_logger(), "相机内参: cx=%.2f, cy=%.2f, fx=%.2f, fy=%.2f",cam_params_.get_u0(), cam_params_.get_v0(), cam_params_.get_px(), cam_params_.get_py());
                    }  
            } 
            if (!detection_success) {
                // 右上角显示文字
                    std::string status = "No Corners detected";
                    cv::putText(img_copy, status,
                    cv::Point(640 - 200, 30),
                    cv::FONT_HERSHEY_SIMPLEX, 0.4, 
                    cv::Scalar(0, 0, 255), 2); 
            }
            // 绘制目标特征点（期望的角点位置）
            for (size_t i = 0; i < target_features_.size(); ++i) {
                // 获取容器中第 i 个目标特征点，用 target_pixel 作为临时别名方便后续操作
                const auto& target_pixel = target_pixels_[i];
                // 获取目标特征点的像素坐标
                double u = target_pixel.get_u(); 
                double v = target_pixel.get_v(); 
                // 将目标特征点的像素坐标转换为 OpenCV 格式
                cv::Point pt(static_cast<int>(u), static_cast<int>(v));
                
                // 绘制特征点（蓝色实心圆）
                cv::circle(img_copy, pt, 5, cv::Scalar(255, 0, 0), -1);
                
                // 绘制编号（蓝色文字）
                cv::putText(img_copy, std::to_string(i + 1), 
                            cv::Point(pt.x + 10, pt.y - 10),
                            cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 0, 0), 1);
            }
            // 计算并打印特征误差
            if (detection_success) {
                compute_feature_error();
            }
            // 伺服控制器初始化 
            init_visual_servo();


            // 显示处理后的图像
            cv::imshow("Detected Corners", img_copy);
            cv::waitKey(1);
        }
        catch (const std::exception& e)
        {
            RCLCPP_ERROR(this->get_logger(), "未检测到角点catch: %s", e.what());
        }
    }
    //  深度图回调函数
    void depth_callback(const sensor_msgs::msg::Image::SharedPtr msg)
    {
        try
        {   
            (void)msg;
        }
        catch (const std::exception& e)
        {
            RCLCPP_ERROR(this->get_logger(), "深度图回调函数出错: %s", e.what());
        }
    }
    // 相机内参回调函数
    void rgb_camera_info_callback(const sensor_msgs::msg::CameraInfo::SharedPtr msg)
    {
        try
        {   
            // 从CameraInfo消息的K矩阵中提取内参
            double fx = msg->k[0];  // 焦距x
            double fy = msg->k[4];  // 焦距y
            double cx = msg->k[2];  // 主点x
            double cy = msg->k[5];  // 主点y

            //vpCameraParameters类是 ViSP 中专门用于存储和管理相机内参的容器
            cam_params_ = vpCameraParameters(fx, fy, cx, cy);
            // 初始化目标特征点
            init_target_features();
            //RCLCPP_INFO(this->get_logger(), "相机内参初始化完成");
            //RCLCPP_INFO(this->get_logger(), "fx=%.2f, fy=%.2f, cx=%.2f, cy=%.2f",fx, fy, cx, cy);
        }
        catch (const std::exception& e)
        {
            RCLCPP_ERROR(this->get_logger(), "相机内参回调函数出错: %s", e.what());      
        }

    }
    // 机械臂关节状态回调函数
    void jointStateCallback(const sensor_msgs::msg::JointState::SharedPtr msg)
    {
        try
        {
            // current_angles_.clear();
            // for (size_t i = 0; i < msg->position.size(); ++i) {
            //     current_angles_.push_back(msg->position[i]);
            // }
        }
        catch (const std::exception& e)
        {

        }
    }
    // 速度发布器回调函数
    void velocity_publisher_callback()
    {

    }
    // 矩形四个角点检测函数
     bool detect_rectangle_corners(const cv::Mat& img, std::vector<vpImagePoint>& corners)
     {
        //输入参数cv::Mat& img：OpencV格式的彩色图像img
        //输出参数std::vector<vpImagePoint>& corners：用于存储检测到的角点（ViSP 库的像素坐标格式），通过引用传递实现输出。核心作用是让函数能够将检测到的角点数据 “传递出去” 给函数外部使用。
            //std::vector<vpImagePoint>  参数的类型
            //& 引用  意味着corners不是函数内部的局部变量，而是函数外部某个变量的 “别名”（两者指向同一块内存）。
            //corners 参数名
        //通常用const &表示输入参数，不带const &表示输出参数！！！！！
        //&在参数列表中表示引用，本质是 “变量的别名”
        //const是 “常量修饰符”，加在参数前表示：函数内部不能修改该参数的值，明确告诉编译器“这个参数是输入，只能读，不能改“

        //1.转化图像为灰度图
            cv::Mat gray_img;
            cv::cvtColor(img, gray_img, cv::COLOR_BGR2GRAY); // 转换为灰度图
            //输入参数img  输出参数gray_img


        //2.使用Canny边缘检测算法检测图像边缘
            cv::Mat edges;
            cv::Canny(gray_img, edges, 50, 150);

        //3.检测外部轮廓
            std::vector<std::vector<cv::Point>> contours;
            cv::findContours(edges, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        
        //4.过滤小轮廓
            const double MIN_AREA = 500.0;
            for (const auto& contour : contours)
                {
                    if (cv::contourArea(contour) < MIN_AREA)
                        continue;

                    // 5. 多边形逼近
                    std::vector<cv::Point> approx;
                    double epsilon = cv::arcLength(contour, true) * 0.02;
                    cv::approxPolyDP(contour, approx, epsilon, true);

                    // 6. 判断是否为矩形（4个顶点）
                    if (approx.size() == 4)
                    {
                        // 7. 坐标转换为ViSP格式（y, x）
                        for (const auto& p : approx)
                            corners.push_back(vpImagePoint(p.y, p.x));
                        return true;
                    }
                }
            return false;
     
     }
     // 目标特征点设定
     void init_target_features() {
            // 清空之前的目标特征点和像素坐标
            target_features_.clear();
            target_pixels_.clear(); 

            // 1.设定目标特征点像素坐标
            vpImagePoint ip0(center_v_ - offset_v_,center_u_ - offset_u_ );  
            vpImagePoint ip1(center_v_ + offset_v_,center_u_ - offset_u_);  
            vpImagePoint ip2(center_v_ + offset_v_,center_u_ + offset_u_ );  
            vpImagePoint ip3(center_v_ - offset_v_,center_u_ + offset_u_ );  
            // 将目标特征点像素坐标存入容器
            target_pixels_.push_back(ip0);
            target_pixels_.push_back(ip1);
            target_pixels_.push_back(ip2);
            target_pixels_.push_back(ip3);
            
            // 2. 转换为归一化坐标（x, y）
            auto to_normalized = [&](const vpImagePoint& ip) {
                double u = ip.get_u();
                double v = ip.get_v();
                //double x = (u - cam_params_.get_u0()) / cam_params_.get_px();  // 归一化x
                //double y = (v - cam_params_.get_v0()) / cam_params_.get_py();  // 归一化y
                double cx = cam_params_.get_u0();
                double cy = cam_params_.get_v0();
                double fx = cam_params_.get_px();
                double fy = cam_params_.get_py();
                // 打印中间值用于排查
                //RCLCPP_INFO(this->get_logger(), "中间值：u=%.0f, v=%.0f, cx=%.2f, cy=%.2f, fx=%.2f, fy=%.2f",u, v, cx, cy, fx, fy);
                double x = (u - cx) / fx;
                double y = (v - cy) / fy;
                return std::make_pair(x, y);
            };

            // 3. 初始化vpFeaturePoint（Z=1.0，默认深度）
            auto [x0, y0] = to_normalized(ip0);
            auto [x1, y1] = to_normalized(ip1);
            auto [x2, y2] = to_normalized(ip2);
            auto [x3, y3] = to_normalized(ip3);

            vpFeaturePoint fp0, fp1, fp2, fp3;
            // 
            fp0.buildFrom(x0, y0, 1.0);
            fp1.buildFrom(x1, y1, 1.0);
            fp2.buildFrom(x2, y2, 1.0);
            fp3.buildFrom(x3, y3, 1.0);

            // 4. 存入容器
            target_features_.push_back(fp0);
            target_features_.push_back(fp1);
            target_features_.push_back(fp2);
            target_features_.push_back(fp3);

            //RCLCPP_INFO(this->get_logger(), "转换前（像素坐标）：u=%.0f, v=%.0f", ip0.get_u(), ip0.get_v());
            //RCLCPP_INFO(this->get_logger(), "转换后（归一化坐标）：x=%.6f, y=%.6f", fp0.get_x(), fp0.get_y());
    }
    // 计算特征误差
     void compute_feature_error(){   
        // 检查target_features_ 和 current_features_ 特征点数量是否匹配
        if (target_features_.size() != current_features_.size() || target_features_.empty()) {
            RCLCPP_ERROR(this->get_logger(), "特征点数量不匹配或为空，无法计算误差");
            return;
        }
        // 清空特征误差 
        feature_error_.resize(target_features_.size() * 2); // 每个特征点有两个误差分量（x和y）
        for (size_t i = 0; i < feature_error_.size(); ++i) {feature_error_[i] = 0.0;}
        //RCLCPP_INFO(this->get_logger(), "特征点数量：%zu", target_features_.size());
        //RCLCPP_INFO(this->get_logger(), "特征误差向量大小：%zu", feature_error_.size());
        // 打印当前特征点和目标特征点
        //RCLCPP_INFO(this->get_logger(), "当前特征点数量：%zu", current_features_.size());
        //RCLCPP_INFO(this->get_logger(), "目标特征点数量：%zu", target_features_.size());
        // 计算特征误差
        for (size_t i = 0; i < target_features_.size(); ++i) {
            const vpFeaturePoint& target = target_features_[i];
            const vpFeaturePoint& current = current_features_[i];

            // 打印目标点和当前点的x、y坐标
        // RCLCPP_INFO(this->get_logger(), 
        //             "特征点 %zu:\n"
        //             "  目标 (x, y) = (%.6f, %.6f)\n"
        //             "  当前 (x, y) = (%.6f, %.6f)",
        //             i + 1,
        //             target.get_x(), target.get_y(),  // 目标特征点坐标
        //             current.get_x(), current.get_y());  // 当前特征点坐标
                    
            // 计算误差：期望特征点 - 当前特征点
            double error_x = target.get_x() - current.get_x();
            double error_y = target.get_y() - current.get_y();

            // 存储误差
            feature_error_[i * 2] = error_x;
            feature_error_[i * 2 + 1] = error_y;
        }
        // 打印特征误差
        // for (size_t i = 0; i < target_features_.size(); ++i) {
        //     RCLCPP_INFO(this->get_logger(), "特征点 %zu: 误差 (x, y) = (%.6f, %.6f)", 
        //                 i + 1, feature_error_[i * 2], feature_error_[i * 2 + 1]);
        // }
    }
    // 配置伺服参数
     void init_visual_servo(){
        // 1.伺服控制器初始化
        task.setServo(vpServo::EYEINHAND_CAMERA); // 设置伺服模式为相机在手眼坐标系下
        // 2.交互矩阵
        task.setInteractionMatrixType(vpServo::CURRENT); 
        // 3.增益
        task.setLambda(lambda_);
        // 4.
        for (size_t i = 0; i < current_features_.size(); ++i) {
            task.addFeature(current_features_[i], target_features_[i]);
         }
        // 5.计算相机速度
        cam_velocity_cmd = task.computeControlLaw();
        // 6.打印相机速度指令
        // RCLCPP_INFO(this->get_logger(), "转换前相机速度指令: [%.6f, %.6f, %.6f, %.6f, %.6f, %.6f]", 
        //             cam_velocity_cmd[0], cam_velocity_cmd[1], cam_velocity_cmd[2],cam_velocity_cmd[3],cam_velocity_cmd[4],cam_velocity_cmd[5]);
        camera_vel_cmd.linear.x = cam_velocity_cmd[0];
        camera_vel_cmd.linear.y = cam_velocity_cmd[1];
        camera_vel_cmd.linear.z = cam_velocity_cmd[2];
        camera_vel_cmd.angular.x = cam_velocity_cmd[3];
        camera_vel_cmd.angular.y = cam_velocity_cmd[4];
        camera_vel_cmd.angular.z = cam_velocity_cmd[5];
        // 将相机速度转换为机器人末端速度
        ConvertCameraVelToBaseVel("kinect_link", "base_link");
        // 
        send_robot_jacobian_request();
    }
    // 相机速度转换为机器人末端速度
     void ConvertCameraVelToBaseVel(const std::string &camera_frame, const std::string &base_frame){
        // 1.获取相机在机器人末端坐标系下的变换矩阵
        // 通过TF式获取相机在机器人末端坐标系下的变换矩阵
        // 获取相机到基坐标系的变换关系
        geometry_msgs::msg::TransformStamped tfCamWorld;
        try
        {
            tfCamWorld = tf_buffer_.lookupTransform(base_frame, camera_frame, rclcpp::Time(0));
            // 打印变换信息
            // RCLCPP_INFO(this->get_logger(), "相机到基坐标系变换: translation=(%.2f, %.2f, %.2f), rotation=(%.2f, %.2f, %.2f, %.2f)", 
            //             tfCamWorld.transform.translation.x, 
            //             tfCamWorld.transform.translation.y, 
            //             tfCamWorld.transform.translation.z,
            //             tfCamWorld.transform.rotation.x,
            //             tfCamWorld.transform.rotation.y,
            //             tfCamWorld.transform.rotation.z,
            //             tfCamWorld.transform.rotation.w);

                //lookupTransform 只是获取了 “相机与基坐标系的位姿关系”（旋转 + 平移），但要完成速度从相机坐标系到基坐标系的转换，还需要：
                //1.将旋转信息从四元数转换为旋转矩阵（便于向量运算）；
                //2.提取平移信息（位置向量），构造完整的变换矩阵；
                //3.用变换矩阵对相机速度向量进行数学转换，得到基坐标系下的速度。

            // 提取平移向量
            // tf2::Vector3 t(tfCamWorld.transform.translation.x,
            //                tfCamWorld.transform.translation.y,
            //                tfCamWorld.transform.translation.z);
            // 

            // // 提取旋转矩阵
            // tf2::Quaternion q(tfCamWorld.transform.rotation.x,
            //                   tfCamWorld.transform.rotation.y,
            //                   tfCamWorld.transform.rotation.z,
            //                   tfCamWorld.transform.rotation.w);
            // RCLCPP_INFO(this->get_logger(), "tf方法：平移向量 t: x=%.3f, y=%.3f, z=%.3f",t.x(), t.y(), t.z());
            // RCLCPP_INFO(this->get_logger(), "tf方法：旋转四元数 q: x=%.3f, y=%.3f, z=%.3f, w=%.3f",q.x(), q.y(), q.z(), q.w());
            // 构建变换矩阵
            // tf2::Transform transform(q, t);

            // 将四元数转换为Eigen的旋转矩阵 
            Eigen::Quaterniond rotationWorldCam(tfCamWorld.transform.rotation.w, tfCamWorld.transform.rotation.x,tfCamWorld.transform.rotation.y, tfCamWorld.transform.rotation.z);
            Eigen::Matrix3d rotationMatWorldCam = rotationWorldCam.toRotationMatrix();
            
            // 将平移向量转换为Eigen的向量  
            Eigen::Vector3d arrWorldCamTrans(tfCamWorld.transform.translation.x,tfCamWorld.transform.translation.y,tfCamWorld.transform.translation.z);
            // 打印旋转矩阵和平移向量
            // RCLCPP_INFO(this->get_logger(), "Eigen方法：旋转矩阵:\n%.3f %.3f %.3f\n%.3f %.3f %.3f\n%.3f %.3f %.3f",
            //             rotationMatWorldCam(0, 0), rotationMatWorldCam(0, 1), rotationMatWorldCam(0, 2),
            //             rotationMatWorldCam(1, 0), rotationMatWorldCam(1, 1), rotationMatWorldCam(1, 2),
            //             rotationMatWorldCam(2, 0), rotationMatWorldCam(2, 1), rotationMatWorldCam(2, 2));
            // RCLCPP_INFO(this->get_logger(), "Eigen方法：平移向量: x=%.3f, y=%.3f, z=%.3f",arrWorldCamTrans(0), arrWorldCamTrans(1), arrWorldCamTrans(2));
            // 创建一个4x4的变换矩阵，将旋转矩阵和平移向量组合起来
            Eigen::Matrix4d transform_matrix = Eigen::Matrix4d::Identity();
            // 将旋转矩阵和平移向量填入变换矩阵
            transform_matrix.block<3, 3>(0, 0) = rotationMatWorldCam;
            transform_matrix(0, 3) = arrWorldCamTrans(0);
            transform_matrix(1, 3) = arrWorldCamTrans(1);
            transform_matrix(2, 3) = arrWorldCamTrans(2);
            // 转换相机速度到基坐标系速度
            // 计算旋转后的速度（从相机坐标系到基坐标系）
            Eigen::Vector4d linear_velocity = transform_matrix * Eigen::Vector4d(camera_vel_cmd.linear.x, camera_vel_cmd.linear.y , camera_vel_cmd.linear.z , 0); // 线速度
            Eigen::Vector4d angular_velocity = transform_matrix * Eigen::Vector4d(camera_vel_cmd.angular.x, camera_vel_cmd.angular.y , camera_vel_cmd.angular.z , 0); // 角速度
            // 打印转换后的速度指令
            // RCLCPP_INFO(this->get_logger(), "转换后的机器人末端速度指令: linear=(%.2f, %.2f, %.2f), angular=(%.2f, %.2f, %.2f)", 
            //             linear_velocity(0), linear_velocity(1), linear_velocity(2),
            //             angular_velocity(0), angular_velocity(1), angular_velocity(2));

            // 将转换后的速度指令赋值给 camera_vel_cmd_in_base（将结果填充到Twist消息中）
            camera_vel_cmd_in_base.linear.x = linear_velocity(0);
            camera_vel_cmd_in_base.linear.y = linear_velocity(1);
            camera_vel_cmd_in_base.linear.z = linear_velocity(2);
            camera_vel_cmd_in_base.angular.x = angular_velocity(0);
            camera_vel_cmd_in_base.angular.y = angular_velocity(1);
            camera_vel_cmd_in_base.angular.z = angular_velocity(2);
        } 
        catch (tf2::TransformException &ex) 
        {
            RCLCPP_WARN(this->get_logger(), "Transform failed: %s", ex.what());
        }
        // // 2.发布机器人末端速度指令
        // // 发布速度指令到机器人末端
        // rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr base_velocity_publisher = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
        // // 发布速度指令
        // base_velocity_publisher->publish(camera_vel_cmd);
        // // RCLCPP_INFO(this->get_logger(), "已发布机器人末端速度指令");
        // // 3.打印速度指令
        // RCLCPP_INFO(this->get_logger(), "机器人末端速度指令: linear=(%.2f, %.2f, %.2f), angular=(%.2f, %.2f, %.2f)", 
        //             camera_vel_cmd.linear.x, camera_vel_cmd.linear.y, camera_vel_cmd.linear.z,
        //             camera_vel_cmd.angular.x, camera_vel_cmd.angular.y, camera_vel_cmd.angular.z);

    }
    //
     void send_robot_jacobian_request()
    {
        RCLCPP_INFO(this->get_logger(), "发送机器人雅可比矩阵请求");

    }
    // 将机器人末端速度转换为关节速度
    // void convertBaseVelToJointVel(const service_interfaces::srv::GetJacobian::Response::SharedPtr result)
    // {
    //     // // 获取雅可比矩阵的值
    //     // Eigen::MatrixXd robot_jacobian(6, 6);
    //     // int index = 0;
    //     // for (size_t i = 0; i < result->jacobian_matrix.layout.dim[0].size; ++i)
    //     // {
    //     //     for (size_t j = 0; j < result->jacobian_matrix.layout.dim[1].size; ++j)
    //     //     {
    //     //         robot_jacobian(i, j) = result->jacobian_matrix.data[index++];
    //     //     }
    //     // }
    //     // // 计算雅可比矩阵的逆
    //     // Eigen::MatrixXd robot_jacobian_inv = robot_jacobian.completeOrthogonalDecomposition().pseudoInverse();
    //     // // 将相机速度指令转换为Eigen向量
    //     // Eigen::VectorXd vector_camera_vel_cmd_in_base(6);
    //     // vector_camera_vel_cmd_in_base << camera_vel_cmd_in_base.linear.x,
    //     //                                 camera_vel_cmd_in_base.linear.y,
    //     //                                 camera_vel_cmd_in_base.linear.z,
    //     //                                 camera_vel_cmd_in_base.angular.x,
    //     //                                 camera_vel_cmd_in_base.angular.y,
    //     //                                 camera_vel_cmd_in_base.angular.z;
    //     // // 计算关节速度q_dot = J⁺ * v_base
    //     // Eigen::MatrixXd joint_vel_msg = robot_jacobian_inv * vector_camera_vel_cmd_in_base;
    //     // // 打印关节速度
    //     // joint_vel.data.resize(joint_vel_msg.rows());
    //     // for (int i = 0; i < joint_vel_msg.rows(); ++i)
    //     // {
    //     //     joint_vel.data[i] = joint_vel_msg(i, 0);
    //     //     if(std::abs(joint_vel.data[i]) > 1)
    //     //     {
    //     //         joint_vel.data[i] = (joint_vel.data[i] > 0) ? 1 : -1;
    //     //     }
    //     // }
    // }
};

int main(int argc, char **argv)
{
    // 初始化
    rclcpp::init(argc, argv);
    // 创建节点
    //auto node = std::make_shared<rclcpp::Node>("camera_image");
    auto node = std::make_shared<VisualServoInit>(); 
    // 运行节点
    rclcpp::spin(node);
    // 关闭ROS2
    rclcpp::shutdown();
    return 0;
}