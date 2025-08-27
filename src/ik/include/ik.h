#ifndef IK_H
#define IK_H

#include <rclcpp/rclcpp.hpp>
#include <memory>
#include <string>
#include <sensor_msgs/msg/joint_state.hpp>
#include <std_srvs/srv/trigger.hpp> 
#include <std_msgs/msg/float64_multi_array.hpp>
#include <geometry_msgs/msg/point.hpp> 
#include <rclcpp/timer.hpp>  
#include <pinocchio/algorithm/frames.hpp>
#include "pinocchio/algorithm/kinematics.hpp"
#include <pinocchio/algorithm/jacobian.hpp>
#include <pinocchio/parsers/urdf.hpp>
#include <Eigen/Dense>
#include <vector>
#include <string>
#include <map>
#include <set>

// 类的声明
class IKNode : public rclcpp::Node
{
public:
    // 构造函数和析构函数
    IKNode();
    ~IKNode();
private:
    // 定义成员变量
    std::string robot_description_param;
    // 定义Pinocchio模型和数据
    pinocchio::Model model;
    pinocchio::Data data;
    // 定义末端执行器的帧ID
    pinocchio::FrameIndex end_effector_frame_id;
    // 定义末端执行器的名称
    std::string end_effector_frame_name;
    // 存储当前关节角度
    Eigen::VectorXd current_joint_positions_;
    // 关节名称到索引的映射
    std::map<std::string, int> joint_name_to_index_;
    // 存储当前的雅可比矩阵
    Eigen::MatrixXd current_jacobian_;
    // 存储当前的末端执行器位置
    Eigen::Vector3d current_end_effector_position_;
    // UR10关节名称列表
    std::vector<std::string> ur10_joint_names = {"shoulder_pan_joint","shoulder_lift_joint", "elbow_joint","wrist_1_joint","wrist_2_joint","wrist_3_joint"};
    // 定义订阅器和发布器
    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_state_subscriber_;
    // 定义话题发布器
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr jacobian_publisher_;
    rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr ee_position_publisher_;
    rclcpp::TimerBase::SharedPtr timer_;  
    double publish_rate_;
        // 定义回调函数
    void jointStateCallback(const sensor_msgs::msg::JointState::SharedPtr msg);
    //  定义成员函数
    void computeEndEffectorJacobian(const Eigen::VectorXd& q);
    void publishJacobianAndPosition();
};


#endif