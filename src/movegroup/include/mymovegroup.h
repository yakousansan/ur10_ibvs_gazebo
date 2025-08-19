#ifndef MYMOVEGROUP_H
#define MYMOVEGROUP_H

#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/robot_model_loader/robot_model_loader.h>
#include <moveit/robot_state/robot_state.h>
#include <rclcpp/rclcpp.hpp>
#include <thread>
#include <sensor_msgs/msg/joint_state.hpp>
#include <std_srvs/srv/trigger.hpp> 
#include <std_msgs/msg/float64_multi_array.hpp>
#include "service_interfaces/srv/get_jacobian.hpp" 
#include "service_interfaces/srv/send_grasp_request.hpp"

using std_srvs::srv::Trigger;

class MyMoveGroup : public rclcpp::Node
{
public:
    explicit MyMoveGroup(const rclcpp::NodeOptions &options);

private:
    rclcpp::Node::SharedPtr node_;
    moveit::planning_interface::MoveGroupInterfacePtr move_group_;
    rclcpp::Service<service_interfaces::srv::SendGraspRequest>::SharedPtr movegroup_service_;

    rclcpp::Service<Trigger>::SharedPtr print_pose_service_; 
    std::shared_ptr<rclcpp::executors::SingleThreadedExecutor> executor_;
    std::thread executor_thread_;
    
    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_state_subscriber_;
    rclcpp::Service<service_interfaces::srv::GetJacobian>::SharedPtr jacobian_service_;
    std::shared_ptr<robot_model_loader::RobotModelLoader> robot_model_loader_;
    moveit::core::RobotModelPtr robot_model_;
    moveit::core::RobotStatePtr robot_state_;
    const moveit::core::JointModelGroup* joint_model_group_;
    
    

    void handlePrintPoseRequest(const std::shared_ptr<Trigger::Request> /*request*/,
                                      std::shared_ptr<Trigger::Response> response);

    void jointStateCallback(const sensor_msgs::msg::JointState::SharedPtr msg);

    void getJacobianCallback(const std::shared_ptr<service_interfaces::srv::GetJacobian::Request> /*request*/,
                                   std::shared_ptr<service_interfaces::srv::GetJacobian::Response> response);

};

#endif //MYMOVEGROUP_H