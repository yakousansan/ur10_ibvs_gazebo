#include <rclcpp/rclcpp.hpp>
#include <image_transport/image_transport.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/msg/image.hpp>
#include <opencv2/opencv.hpp>

class CameraImageViewer : public rclcpp::Node
{
public:
    CameraImageViewer() : Node("camera_image")
    {
    // 订阅彩色图像话题
    rgb_subscriber = this->create_subscription<sensor_msgs::msg::Image>("/rgb/image_raw",10,
            std::bind(&CameraImageViewer::rgb_callback, this, std::placeholders::_1));
    // //订阅深度图像话题
    depth_subscriber = this->create_subscription<sensor_msgs::msg::Image>("/depth/image_raw",10,
            std::bind(&CameraImageViewer::depth_callback, this, std::placeholders::_1));
    //创建显示窗口
    cv::namedWindow("RGB Image", cv::WINDOW_NORMAL);
    cv::namedWindow("Depth Image", cv::WINDOW_NORMAL);
    //调整窗口大小
    cv::resizeWindow("RGB Image", 640, 480);
    cv::resizeWindow("Depth Image", 640, 480);

    //RCLCPP_INFO(this->get_logger(), "节点初始化完成，开始显示图像...");
        
    }
    
    ~CameraImageViewer()
    {
    
    cv::destroyAllWindows();
    RCLCPP_INFO(this->get_logger(), "节点已关闭");
    }
    
private:
    //定义成员变量
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr rgb_subscriber;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr depth_subscriber;

    //定义回调函数（当收到话题的消息，会自动调用回调函数） 
    void rgb_callback(const sensor_msgs::msg::Image::SharedPtr msg)
    {
        try
        {
            // 将ROS图像消息转换为OpenCV格式
            cv::Mat image = cv_bridge::toCvShare(msg, "rgb8")->image;

            //显示图像
            cv::cvtColor(image, image, cv::COLOR_RGB2BGR);
            cv::imshow("RGB Image", image);
            cv::waitKey(1); 

            // // 保存图片
            // std::string save_path = "/home/p/ws_demo2/src/camera_image/picture/rgb_image.jpg";
            // bool save_success = cv::imwrite(save_path, image);

            // 解绑订阅者，回调函数不再被调用
            //rgb_sub_.reset();  
        }
        catch (cv_bridge::Exception& e)
        {
            RCLCPP_ERROR(this->get_logger(), "RGB图像转换失败: %s", e.what());
        }
    }
    void depth_callback(const sensor_msgs::msg::Image::SharedPtr msg)
    {
        try
        {
            // 将ROS图像消息转换为OpenCV格式
            cv::Mat depth = cv_bridge::toCvShare(msg, "32FC1")->image;
            // 2. 检查原始深度图像是否有效（避免空图像）
        if (depth.empty())
        {
            RCLCPP_WARN(this->get_logger(), "收到空的深度图像，跳过显示");
            return;
        }
            //
            cv::Mat depth_8u;

            double min_depth = 0.0;  
            double max_depth = 5.0;   
            depth.convertTo(depth_8u, CV_8UC1, 255.0 / (max_depth - min_depth), -min_depth * 255.0 / (max_depth - min_depth));
        if (!depth_8u.empty())
        {
            cv::imshow("Depth Image", depth_8u);
            cv::waitKey(1);
        }
        else
        {
            RCLCPP_WARN(this->get_logger(), "转换后的深度图像为空，跳过显示");
        }
        }
        catch (cv_bridge::Exception& e)
        {
            RCLCPP_ERROR(this->get_logger(), "深度图像转换失败: %s", e.what());
        }
    }

};

int main(int argc, char **argv)
{
    // 初始化
    rclcpp::init(argc, argv);
    // 创建节点
    //auto node = std::make_shared<rclcpp::Node>("camera_image");
    auto node = std::make_shared<CameraImageViewer>(); 
    // 运行节点
    rclcpp::spin(node);
    // 关闭ROS2
    rclcpp::shutdown();
    return 0;
}