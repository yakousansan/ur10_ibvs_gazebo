#include"ibvs.h"
#include "rclcpp/rclcpp.hpp"


    //构造函数
VisualServoInit::VisualServoInit() : Node("ibvs"), 
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
    // 订阅机械臂的雅可比矩阵
    jacobian_subscriber_ = this->create_subscription<std_msgs::msg::Float64MultiArray>("/jacobian_matrix",10,
            std::bind(&VisualServoInit::jacobianCallback, this, std::placeholders::_1));
    // // 创建一个定时器，用于周期性地发布关节速度指令
    // velocity_publisher_timer_ = this->create_wall_timer(std::chrono::milliseconds(10),std::bind(&VisualServoInit::velocity_publisher_callback, this));
    // 发布关节速度指令
    joint_velocity_publisher_ = this->create_publisher<std_msgs::msg::Float64MultiArray>("/ur_joint_velocity_controller/commands", 10);
    // 创建显示窗口
    cv::namedWindow("Detected Corners", cv::WINDOW_NORMAL);
    // 调整窗口大小
    cv::resizeWindow("Detected Corners", 640, 480);
    // 初始化雅可比
    current_jacobian_.setZero(6, 6);
    // 伺服控制器初始化
    task.setServo(vpServo::EYEINHAND_CAMERA); // 设置伺服模式为相机在手眼坐标系下
    // 交互矩阵
    task.setInteractionMatrixType(vpServo::CURRENT); 
    // 增益
    task.setLambda(lambda_);
    // 初始化数据记录
    // 时间戳
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%m%d_%H%M%S");
    std::string timestamp = ss.str();
    joint_vel_data_file.open("/home/p/ws_demo2/src/ibvs/data/joint_vel_data/joint_vel_data_" + timestamp + ".csv");
    joint_vel_data_file << "Timestamp,joint_vel_0,joint_vel_1,joint_vel_2,joint_vel_3,joint_vel_4,joint_vel_5\n";
    // 误差
    error_data_file.open("/home/p/ws_demo2/src/ibvs/data/error_data/error_data_" + timestamp + ".csv");
    error_data_file << "Timestamp,error_x0,error_y0,error_x1,error_y1,error_x2,error_y2,error_x3,error_y3,RMSE\n";

    RCLCPP_INFO(this->get_logger(), "ibvs节点初始化完成");   
}
    
VisualServoInit::~VisualServoInit()
{    
            // 取消订阅话题
            rgb_subscriber.reset();
            depth_subscriber.reset();
            rgb_cam_info_sub_.reset();
            joint_state_subscriber_.reset();
            joint_velocity_publisher_.reset();
            jacobian_subscriber_.reset();
            // 销毁OpenCV窗口
            cv::destroyWindow("Detected Corners");
            // 释放OpenCV资源
            cv::waitKey(1);
            // 关闭文件
            if (joint_vel_data_file.is_open()) joint_vel_data_file.close();
            if (error_data_file.is_open()) error_data_file.close();
            RCLCPP_INFO(this->get_logger(), "ibvs节点已关闭");
}
    
// 定义回调函数（当收到话题的消息，会自动调用回调函数） 
void VisualServoInit::rgb_callback(const sensor_msgs::msg::Image::SharedPtr msg)
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

                // 检测不到停止运行
                std_msgs::msg::Float64MultiArray zero_vel;
                zero_vel.data = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
                joint_velocity_publisher_->publish(zero_vel); 
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
            // 伺服控制器初始化 
            init_visual_servo();
            // 显示处理后的图像
            cv::imshow("Detected Corners", img_copy);
            cv::waitKey(1);
        }
        catch (const std::exception& e)
        {
            RCLCPP_INFO(this->get_logger(), "未检测到角点catch: %s", e.what());
            std_msgs::msg::Float64MultiArray zero_vel;
            zero_vel.data = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
            joint_velocity_publisher_->publish(zero_vel);

        }
}
//  深度图回调函数
void VisualServoInit::depth_callback(const sensor_msgs::msg::Image::SharedPtr msg)
{
        try
        {   
            (void)msg;
        }
        catch (const std::exception& e)
        {
            RCLCPP_INFO(this->get_logger(), "深度图回调函数出错: %s", e.what());
        }
}
// 相机内参回调函数
void VisualServoInit::rgb_camera_info_callback(const sensor_msgs::msg::CameraInfo::SharedPtr msg)
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
            RCLCPP_INFO(this->get_logger(), "相机内参回调函数出错: %s", e.what());      
        }

}
// 机械臂关节状态回调函数
void VisualServoInit::jointStateCallback(const sensor_msgs::msg::JointState::SharedPtr msg)
{
        try
        {   
            (void)msg;
            // 打印关节速度
            // for (int i = 0; i < 6; ++i)
            // {
            //     RCLCPP_INFO(this->get_logger(), "关节 %d 速度: %.4f rad/s", i+1, msg->velocity[i]);
            // }
        }
        catch (const std::exception& e)
        {
            RCLCPP_INFO(this->get_logger(), "关节状态回调异常: %s", e.what());
        }
}
// 速度发布器回调函数
void VisualServoInit::joint_velocity_publisher_callback()
{
        try
        {

        }
        catch(const std::exception& e)
        {

        }

}
// 解析雅可比矩阵回调函数
void VisualServoInit::jacobianCallback(const std_msgs::msg::Float64MultiArray::SharedPtr msg)
{
        try
        {
          // 检查数据大小是否正确
        if (msg->data.size() != 36) {
            RCLCPP_INFO(this->get_logger(), "雅可比矩阵数据大小不正确: 期望36，实际%zu", msg->data.size());
            return;
        }
        // 将一维数组转换为6x6矩阵
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 6; ++j) {
                current_jacobian_(i, j) = msg->data[i * 6 + j];
            }
        }
        // RCLCPP_INFO(this->get_logger(), "收到雅可比矩阵");
        }
        catch(const std::exception& e)
        {
           RCLCPP_INFO(this->get_logger(), "解析雅可比矩阵失败: %s", e.what());
        }
        

}
// 矩形四个角点检测函数
bool VisualServoInit::detect_rectangle_corners(const cv::Mat& img, std::vector<vpImagePoint>& corners)
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
                        // 计算轮廓中心点
                        cv::Moments mom = cv::moments(approx);
                        cv::Point2f center(mom.m10/mom.m00, mom.m01/mom.m00);
                        // 角度排序
                        // 按照角度排序（顺时针方向）
                        std::vector<std::pair<double, cv::Point>> points_with_angles;
                        for (const auto& pt : approx)
                        {
                            double angle = atan2(pt.y - center.y, pt.x - center.x);
                            // 调整角度范围到0-2π
                            if (angle < 0) angle += 2 * CV_PI;
                            points_with_angles.push_back({angle, pt});
                        }
            
                        // 按角度从大到小排序（顺时针方向）
                        std::sort(points_with_angles.begin(), points_with_angles.end(),
                            [](const std::pair<double, cv::Point>& a, const std::pair<double, cv::Point>& b) {
                                return a.first > b.first;
                            });
                        
                        // 确保第一个点是左上角（角度在315-45度范围内的点）
                        // 找到角度最接近315度（或-45度）的点作为起始点
                        int start_index = 0;
                        double min_diff = fabs(points_with_angles[0].first - 7*CV_PI/4); // 315度 = 7π/4
                        for (int i = 1; i < 4; ++i) {
                            double diff = fabs(points_with_angles[i].first - 7*CV_PI/4);
                            if (diff < min_diff) {
                                min_diff = diff;
                                start_index = i;
                            }
                        }
            
                        // 重新排列点，使左上角点在前（顺时针顺序：左上、左下、右下、右上）
                        std::vector<cv::Point> sorted_points;
                        for (int i = 0; i < 4; ++i) {
                            int idx = (start_index + i) % 4;
                            sorted_points.push_back(points_with_angles[idx].second);
                        }
                        corners.clear();
                        // 7. 坐标转换为ViSP格式（y, x）
                        for (const auto& p : sorted_points){
                            corners.push_back(vpImagePoint(p.y, p.x));
                        }
                            
                        return true;
                    }
                }
            return false;
     
}
// 目标特征点设定
void VisualServoInit::init_target_features() {
            // 清空之前的目标特征点和像素坐标
            target_features_.clear();
            target_pixels_.clear(); 

            // 1.设定目标特征点像素坐标
            vpImagePoint ip0(center_v_ - offset_v_, center_u_ + offset_u_);  // 右上
            vpImagePoint ip1(center_v_ - offset_v_, center_u_ - offset_u_);  // 左上
            vpImagePoint ip2(center_v_ + offset_v_, center_u_ - offset_u_);  // 左下
            vpImagePoint ip3(center_v_ + offset_v_, center_u_ + offset_u_);  // 右下 
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
bool VisualServoInit::compute_feature_error(){   
        // 检查target_features_ 和 current_features_ 特征点数量是否匹配
        if (target_features_.size() != current_features_.size() || target_features_.empty()) {
            RCLCPP_INFO(this->get_logger(), "特征点数量不匹配或为空，无法计算误差");
            return false;
        }
        // 清空特征误差 
        feature_error_.resize(target_features_.size() * 2); // 每个特征点有两个误差分量（x和y）
        for (size_t i = 0; i < feature_error_.size(); ++i) {feature_error_[i] = 0.0;}
        double total_error = 0.0;
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

            total_error += error_x * error_x + error_y * error_y;
        }
        // 打印特征误差
        // for (size_t i = 0; i < target_features_.size(); ++i) {
        //     RCLCPP_INFO(this->get_logger(), "特征点 %zu: 误差 (x, y) = (%.6f, %.6f)", 
        //                 i + 1, feature_error_[i * 2], feature_error_[i * 2 + 1]);
        // }

        // 计算均方根误差
        double rmse = std::sqrt(total_error / target_features_.size());
        // RCLCPP_INFO(this->get_logger(), "特征点RMSE: %.3f 像素（阈值: %.3f 像素）", 
        //         rmse, error_threshold_);

        // 误差数据记录
        if (error_data_file.is_open()) {
            auto now = this->now();
            error_data_file << now.seconds() << ","
                       << feature_error_[0] << "," << feature_error_[1] << ","
                       << feature_error_[2] << "," << feature_error_[3] << ","
                       << feature_error_[4] << "," << feature_error_[5] << ","
                       << feature_error_[6] << "," << feature_error_[7] << ","
                       << rmse << "\n";
        }
        // 仅单次RMSE小于阈值即判定收敛
        if (rmse < error_threshold_) {
            RCLCPP_INFO(this->get_logger(), "特征误差已收敛，停止视觉伺服");
            return true; 
    }

    return false; 

}
// 配置伺服参数
void VisualServoInit::init_visual_servo()
{
        // 计算是否收敛
        if (compute_feature_error()) {
            // 特征误差收敛，停止伺服
            // 发布零速度指令
            std_msgs::msg::Float64MultiArray joint_velocity_msg;
            joint_velocity_msg.data = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
            joint_velocity_publisher_->publish(joint_velocity_msg);
            // RCLCPP_INFO(this->get_logger(), "发布零速度指令，视觉伺服停止");
            return;
        }
        // 4.特征计算
        task.kill();
        for (size_t i = 0; i < current_features_.size(); ++i) {
            task.addFeature(current_features_[i], target_features_[i]);
         }
        // 5.计算相机速度
        cam_velocity_cmd = task.computeControlLaw();
    
        camera_vel_cmd.linear.x = cam_velocity_cmd[0];
        camera_vel_cmd.linear.y = cam_velocity_cmd[1];
        camera_vel_cmd.linear.z = cam_velocity_cmd[2];
        camera_vel_cmd.angular.x = cam_velocity_cmd[3];
        camera_vel_cmd.angular.y = cam_velocity_cmd[4];
        camera_vel_cmd.angular.z = cam_velocity_cmd[5];
        // 打印相机速度指令
        // RCLCPP_INFO(this->get_logger(), "相机速度: 线速度=[%.3f, %.3f, %.3f], 角速度=[%.3f, %.3f, %.3f]",
        //         camera_vel_cmd.linear.x, camera_vel_cmd.linear.y, camera_vel_cmd.linear.z,
        //         camera_vel_cmd.angular.x, camera_vel_cmd.angular.y, camera_vel_cmd.angular.z);

        // 将相机速度转换为机器人末端速度
        ConvertCameraVelToBaseVel("kinect_link", "base_link");
        // 将机器人末端速度转换为关节速度
        convertBaseVelToJointVel();
}
// 相机速度转换为机器人末端速度
void VisualServoInit::ConvertCameraVelToBaseVel(const std::string &camera_frame, const std::string &base_frame)
{
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
            Eigen::Quaterniond q_base_cam(tfCamWorld.transform.rotation.w, tfCamWorld.transform.rotation.x,tfCamWorld.transform.rotation.y, tfCamWorld.transform.rotation.z);
            Eigen::Matrix3d R_base_cam = q_base_cam.toRotationMatrix();
            
            // 将平移向量转换为Eigen的向量  
            Eigen::Vector3d p_base_cam(tfCamWorld.transform.translation.x,tfCamWorld.transform.translation.y,tfCamWorld.transform.translation.z);
            // 打印旋转矩阵和平移向量
            // RCLCPP_INFO(this->get_logger(), "Eigen方法：旋转矩阵:\n%.3f %.3f %.3f\n%.3f %.3f %.3f\n%.3f %.3f %.3f",
            //             rotationMatWorldCam(0, 0), rotationMatWorldCam(0, 1), rotationMatWorldCam(0, 2),
            //             rotationMatWorldCam(1, 0), rotationMatWorldCam(1, 1), rotationMatWorldCam(1, 2),
            //             rotationMatWorldCam(2, 0), rotationMatWorldCam(2, 1), rotationMatWorldCam(2, 2));
            // RCLCPP_INFO(this->get_logger(), "Eigen方法：平移向量: x=%.3f, y=%.3f, z=%.3f",arrWorldCamTrans(0), arrWorldCamTrans(1), arrWorldCamTrans(2));
            // 创建一个4x4的变换矩阵，将旋转矩阵和平移向量组合起来
            // Eigen::Matrix4d transform_matrix = Eigen::Matrix4d::Identity();
            // 将旋转矩阵和平移向量填入变换矩阵
            // transform_matrix.block<3, 3>(0, 0) = rotationMatWorldCam;
            // transform_matrix(0, 3) = arrWorldCamTrans(0);
            // transform_matrix(1, 3) = arrWorldCamTrans(1);
            // transform_matrix(2, 3) = arrWorldCamTrans(2);
            // 转换相机速度到基坐标系速度
            // 打印转换后的速度指令
            // RCLCPP_INFO(this->get_logger(), "转换后的机器人末端速度指令: linear=(%.2f, %.2f, %.2f), angular=(%.2f, %.2f, %.2f)", 
            //             linear_velocity(0), linear_velocity(1), linear_velocity(2),
            //             angular_velocity(0), angular_velocity(1), angular_velocity(2));

            // 将转换后的速度指令赋值给 camera_vel_cmd_in_base（将结果填充到Twist消息中）
            // 创建速度向量
            Eigen::Vector3d v_camera(camera_vel_cmd.linear.x,camera_vel_cmd.linear.y,camera_vel_cmd.linear.z);
            Eigen::Vector3d ω_camera(camera_vel_cmd.angular.x,camera_vel_cmd.angular.y,camera_vel_cmd.angular.z);
            // 转换线速度: v_base = R * v_camera + ω_base × p
            // 转换角速度: ω_base = R * ω_camera
            Eigen::Vector3d angular_velocity = R_base_cam * ω_camera;
            Eigen::Vector3d linear_velocity = R_base_cam * v_camera + angular_velocity.cross(p_base_cam);
            
            
            camera_vel_cmd_in_base.linear.x = linear_velocity(0);
            camera_vel_cmd_in_base.linear.y = linear_velocity(1);
            camera_vel_cmd_in_base.linear.z = linear_velocity(2);
            camera_vel_cmd_in_base.angular.x = angular_velocity(0);
            camera_vel_cmd_in_base.angular.y = angular_velocity(1);
            camera_vel_cmd_in_base.angular.z = angular_velocity(2);
            // 打印转换后的速度指令
            // RCLCPP_INFO(this->get_logger(), "转换后的机器人末端速度指令: 线速度=[%.3f, %.3f, %.3f], 角速度=[%.3f, %.3f, %.3f]",
            //             camera_vel_cmd_in_base.linear.x, camera_vel_cmd_in_base.linear.y, camera_vel_cmd_in_base.linear.z,
            //             camera_vel_cmd_in_base.angular.x, camera_vel_cmd_in_base.angular.y, camera_vel_cmd_in_base.angular.z);
        } 
        catch (tf2::TransformException &ex) 
        {
            RCLCPP_INFO(this->get_logger(), "相机速度转换为机器人末端速度失败: %s", ex.what());
            camera_vel_cmd_in_base = geometry_msgs::msg::Twist();
        }

}
// 将机器人末端速度转换为关节速度
void VisualServoInit::convertBaseVelToJointVel()
{
        try
        {
        // 检查雅可比
        if (!current_jacobian_.allFinite()) {
            RCLCPP_INFO(this->get_logger(), "雅可比矩阵包含非有限值");
        return;
        }
        // 计算雅可比矩阵的逆
        Eigen::MatrixXd jacobian_inv = current_jacobian_.completeOrthogonalDecomposition().pseudoInverse();
        // 将相机速度指令转换为Eigen向量
        Eigen::VectorXd vector_camera_vel_cmd_in_base(6);
        vector_camera_vel_cmd_in_base << camera_vel_cmd_in_base.linear.x,
                                        camera_vel_cmd_in_base.linear.y,
                                        camera_vel_cmd_in_base.linear.z,
                                        camera_vel_cmd_in_base.angular.x,
                                        camera_vel_cmd_in_base.angular.y,
                                        camera_vel_cmd_in_base.angular.z;
        // 计算关节速度q_dot = J⁺ * v_base
        Eigen::VectorXd joint_vel = jacobian_inv * vector_camera_vel_cmd_in_base;
        // 打印关节速度
        // RCLCPP_INFO(this->get_logger(), "发布关节速度: [%.3f, %.3f, %.3f, %.3f, %.3f, %.3f]",
        //             joint_vel(0), joint_vel(1), joint_vel(2),
        //             joint_vel(3), joint_vel(4), joint_vel(5));
        if (joint_vel_data_file.is_open()) {
            auto now = this->now();
            joint_vel_data_file << now.seconds() << ","
                            << joint_vel(0) << ","
                            << joint_vel(1) << ","
                            << joint_vel(2) << ","
                            << joint_vel(3) << ","
                            << joint_vel(4) << ","
                            << joint_vel(5) << "\n";
        }

        // 发布关节速度
        std_msgs::msg::Float64MultiArray joint_vel_msg;
        joint_vel_msg.data.resize(6);
        for (size_t i = 0; i < 6; ++i) {
            joint_vel_msg.data[i] = joint_vel(i); 
        }
        joint_velocity_publisher_->publish(joint_vel_msg);
        // RCLCPP_INFO(this->get_logger(), "关节速度已经发布：");
        }
        catch(const std::exception& e)
        {
            RCLCPP_INFO(this->get_logger(), "末端速度转换为关节速度失败！: %s", e.what());
            std_msgs::msg::Float64MultiArray zero_vel;
            zero_vel.data = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
            joint_velocity_publisher_->publish(zero_vel);
        }
    
}

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