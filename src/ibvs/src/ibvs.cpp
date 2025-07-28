#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "sensor_msgs/msg/camera_info.hpp"
#include <visp3/core/vpCameraParameters.h>
#include <visp3/core/vpPoint.h>
#include <visp3/visual_features/vpFeaturePoint.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <vector>

class VisualServoInit : public rclcpp::Node
{
public:
    //构造函数
    VisualServoInit() : Node("ibvs")
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
    // 创建显示窗口
    cv::namedWindow("Detected Corners", cv::WINDOW_NORMAL);
    // 调整窗口大小
    cv::resizeWindow("Detected Corners", 640, 480);
    //
    init_target_features();
    //RCLCPP_INFO(this->get_logger(), "节点初始化完成");   
    }
    
    ~VisualServoInit()
    {
            //RCLCPP_INFO(this->get_logger(), "节点已关闭");
    }
    
private:
    //定义成员变量
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr rgb_subscriber;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr depth_subscriber;
    rclcpp::Subscription<sensor_msgs::msg::CameraInfo>::SharedPtr rgb_cam_info_sub_;
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

    //定义回调函数（当收到话题的消息，会自动调用回调函数） 
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
                // 获取容器中第 i 个目标特征点，用 feature 作为临时别名方便后续操作
                const auto& feature = target_features_[i];
                // 获取目标特征点的像素坐标
                double u = feature.get_x(); 
                double v = feature.get_y(); 
                // 将目标特征点的像素坐标转换为 OpenCV 格式
                cv::Point pt(static_cast<int>(u), static_cast<int>(v));
                
                // 绘制特征点（蓝色实心圆）
                cv::circle(img_copy, pt, 5, cv::Scalar(255, 0, 0), -1);
                
                // 绘制编号（蓝色文字）
                cv::putText(img_copy, std::to_string(i + 1), 
                            cv::Point(pt.x + 10, pt.y - 10),
                            cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 0, 0), 1);
            }

            // 显示处理后的图像
            cv::imshow("Detected Corners", img_copy);
            cv::waitKey(1);
        }
        catch (const std::exception& e)
        {
            RCLCPP_ERROR(this->get_logger(), "未检测到角点catch: %s", e.what());
        }
    }
    //深度图回调函数
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
            //RCLCPP_INFO(this->get_logger(), "相机内参初始化完成");
            //RCLCPP_INFO(this->get_logger(), "fx=%.2f, fy=%.2f, cx=%.2f, cy=%.2f",fx, fy, cx, cy);
        }
        catch (const std::exception& e)
        {
            RCLCPP_ERROR(this->get_logger(), "相机内参回调函数出错: %s", e.what());      
        }

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
            // 设定目标特征点（矩形四个角点）
            // 1. 左上角
            // 计算目标特征点的偏移量
            // 这里假设图像中心为 (320, 240)，偏移量为 (50, 50)，通过设置偏移量来确定目标特征点的位置
            vpFeaturePoint fp0;
                fp0.set_x(center_u_ - offset_u_);  
                fp0.set_y(center_v_ - offset_v_);  
                target_features_.push_back(fp0);

                // 2. 左下角（编号2，逆时针下一个点）
                vpFeaturePoint fp1;
                fp1.set_x(center_u_ - offset_u_);
                fp1.set_y(center_v_ + offset_v_);
                target_features_.push_back(fp1);

                // 3. 右下角（编号3，逆时针下一个点）
                vpFeaturePoint fp2;
                fp2.set_x(center_u_ + offset_u_);  
                fp2.set_y(center_v_ + offset_v_); 
                target_features_.push_back(fp2);

                // 4. 右上角（编号4，逆时针最后一个点）
                vpFeaturePoint fp3;
                fp3.set_x(center_u_ + offset_u_); 
                fp3.set_y(center_v_ - offset_v_);
                target_features_.push_back(fp3);
    }
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
