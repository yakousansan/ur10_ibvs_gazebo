#include <iostream>
#include <mymovegroup.h>

MyMoveGroup::MyMoveGroup(const rclcpp::NodeOptions &options)
    : Node("MoveGroupNode", options),
      node_(std::make_shared<rclcpp::Node>("move_group_interface")),
      executor_(std::make_shared<rclcpp::executors::SingleThreadedExecutor>())
{
    RCLCPP_INFO(this->get_logger(), "MoveGroupNode has been started.");

    // 初始化movegroup
    move_group_ = std::make_shared<moveit::planning_interface::MoveGroupInterface>(node_, "ur5_arm");
    move_group_->setEndEffectorLink("tool0");
    
    // 初始化robot_state和joint_model_group
    robot_model_loader_ = std::make_shared<robot_model_loader::RobotModelLoader>(node_);
    robot_model_ = robot_model_loader_->getModel();
    robot_state_ = std::make_shared<moveit::core::RobotState>(robot_model_);
    joint_model_group_ = robot_model_->getJointModelGroup("ur5_arm");

    // 发布打印位姿的服务
    print_pose_service_ = this->create_service<Trigger>(
      "print_current_pose",
      std::bind(&MyMoveGroup::handlePrintPoseRequest, this, std::placeholders::_1, std::placeholders::_2)
    );

    // 订阅机械臂当前的关节角度
    joint_state_subscriber_ = this->create_subscription<sensor_msgs::msg::JointState>(
              "/joint_states", 10, std::bind(&MyMoveGroup::jointStateCallback, this, std::placeholders::_1));

    // 发布机械臂雅可比矩阵的服务
    jacobian_service_ = this->create_service<service_interfaces::srv::GetJacobian>(
          "get_jacobian", std::bind(&MyMoveGroup::getJacobianCallback, this, std::placeholders::_1, std::placeholders::_2));

    // 用来旋转节点的
    executor_->add_node(node_);
    executor_thread_ = std::thread([this]() {
        RCLCPP_INFO(node_->get_logger(), "Starting executor thread");
        executor_->spin();
    });
}

void MyMoveGroup::handlePrintPoseRequest(const std::shared_ptr<Trigger::Request> /*request*/,
                                               std::shared_ptr<Trigger::Response> response) {
    RCLCPP_INFO(this->get_logger(), "Received request to print current pose.");
    
    auto current_pose = move_group_->getCurrentPose().pose; // Get the current pose
    std::cout << "Current Pose:" << std::endl;
    std::cout << "Position: (" 
              << current_pose.position.x << ", "
              << current_pose.position.y << ", "
              << current_pose.position.z << ") " << std::endl;
    std::cout << "Orientation: (" 
              << current_pose.orientation.x << ", "
              << current_pose.orientation.y << ", "
              << current_pose.orientation.z << ", "
              << current_pose.orientation.w << ") " << std::endl;

    response->success = true;
    response->message = "Current pose printed successfully.";
}
// 机械臂关节状态回调函数
void MyMoveGroup::jointStateCallback(const sensor_msgs::msg::JointState::SharedPtr msg) {
    for (size_t i = 0; i < msg->name.size(); ++i) {
        robot_state_->setJointPositions(msg->name[i], &msg->position[i]);
    }
    robot_state_->update();
}
// 获取雅可比矩阵的回调函数
void MyMoveGroup::getJacobianCallback(const std::shared_ptr<service_interfaces::srv::GetJacobian::Request> /*request*/,
                                            std::shared_ptr<service_interfaces::srv::GetJacobian::Response> response) 
{
    Eigen::MatrixXd jacobian;
    bool success = robot_state_->getJacobian(joint_model_group_, robot_state_->getLinkModel(joint_model_group_->getLinkModelNames().back()), 
                              Eigen::Vector3d::Zero(), jacobian);

    // 创建并填充雅可比矩阵
    std_msgs::msg::Float64MultiArray jacobian_msg;
    jacobian_msg.layout.dim.push_back(std_msgs::msg::MultiArrayDimension());
    jacobian_msg.layout.dim[0].size = jacobian.rows();  // 矩阵行数
    jacobian_msg.layout.dim[0].stride = 6;
    jacobian_msg.layout.dim[0].label = "rows";

    jacobian_msg.layout.dim.push_back(std_msgs::msg::MultiArrayDimension());
    jacobian_msg.layout.dim[1].size = jacobian.cols();  // 矩阵列数
    jacobian_msg.layout.dim[1].stride = 1;
    jacobian_msg.layout.dim[1].label = "cols";

    if (success) {
        for (int i = 0; i < jacobian.rows(); ++i)
        {
            for (int j = 0; j < jacobian.cols(); ++j)
            {
                jacobian_msg.data.push_back(jacobian(i, j));
            }
        }
        response->jacobian_matrix = jacobian_msg;

        // RCLCPP_INFO(this->get_logger(), "successfully compute jacobian...");

        response->success = true;
    } else {
        response->success = false;
    }
}

int main(int argc, char** argv) {
  rclcpp::init(argc, argv); 
  rclcpp::NodeOptions node_options;
  // 设置参数自动声明
  node_options.automatically_declare_parameters_from_overrides(true);
  // 创建节点并传入参数选项 
  auto node = std::make_shared<MyMoveGroup>(node_options); 
  rclcpp::spin(node); 
  rclcpp::shutdown();
  return 0; 
}