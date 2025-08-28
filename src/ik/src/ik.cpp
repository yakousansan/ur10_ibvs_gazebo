#include"ik.h"
#include <rclcpp/rclcpp.hpp> 

// 构造函数实现
IKNode::IKNode() : Node("ik_node")
{
    // 声明需要使用的参数
    this->declare_parameter<std::string>("robot_description", "");
    this->declare_parameter<std::string>("end_effector_frame", "tool0"); 
    // 从参数服务器加载URDF模型
    this->get_parameter("robot_description", robot_description_param);
    // 获取末端执行器的名称
    this->get_parameter("end_effector_frame", end_effector_frame_name);

    if (robot_description_param.empty()) {
        RCLCPP_ERROR(this->get_logger(), "'robot_description' 参数是空的");
        return;
    }

    // 初始化发布频率
    publish_rate_ = 30.0;
    // 使用Pinocchio加载URDF模型
    try
    {
        pinocchio::urdf::buildModelFromXML(robot_description_param, model);
        RCLCPP_INFO(this->get_logger(), "模型加载成功.");
        // 模型加载成功后再初始化data
        data = pinocchio::Data(model);

        // 初始化末端执行器的帧ID
        end_effector_frame_id = model.getFrameId(end_effector_frame_name);
        // 检查末端执行器的帧ID是否有效
        if (end_effector_frame_id >=model.frames.size()) {
            RCLCPP_ERROR(this->get_logger(), "未找到末端执行器 '%s' 的帧ID", end_effector_frame_name.c_str());
            return;
        }
        // RCLCPP_INFO(this->get_logger(), "末端执行器 '%s' 的帧ID: %zu", end_effector_frame_name.c_str(), end_effector_frame_id);
        // 获取所有帧ID
        // RCLCPP_INFO(this->get_logger(), "\n===== 所有帧列表 =====");
        // for (size_t i = 0; i < model.frames.size(); ++i) {
        //     const auto& frame = model.frames[i];
        //     RCLCPP_INFO(this->get_logger(), "帧ID: %zu, 名称: %s, 父关节: %s", 
        //             i, frame.name.c_str(), model.names[frame.parent].c_str());
        //     // 特别标记tool0帧
        //     if (frame.name == "tool0") {
        //         RCLCPP_INFO(this->get_logger(), "  ^--- 这是你要找的tool0帧!");
        //     }
        // }
        // 初始化当前关节角度
        current_joint_positions_ = Eigen::VectorXd::Zero(model.nq);
        // 初始化雅可比矩阵
        current_jacobian_ = Eigen::MatrixXd::Zero(6, 6);
        // 初始化末端执行器位置
        current_end_effector_position_ = Eigen::Vector3d::Zero();
        
        // 创建关节映射
        for (size_t i = 0; i < ur10_joint_names.size(); ++i) { 
        const std::string& joint_name = ur10_joint_names[i];
        // 查找关节对应的帧ID
        pinocchio::FrameIndex frame_id = model.getFrameId(joint_name);
        if (frame_id < model.frames.size()) {
            joint_name_to_index_[joint_name] = static_cast<int>(i);
            RCLCPP_INFO(this->get_logger(), "映射: '%s' (帧ID %zu) -> 索引 %zu", 
                    joint_name.c_str(), frame_id, i);
        } else {
            RCLCPP_WARN(this->get_logger(), "未找到关节 '%s'", joint_name.c_str());
        }
    }
        // 验证映射完整性
        // if (joint_name_to_index_.size() == 6) {
        //     RCLCPP_INFO(this->get_logger(), "✅ 成功映射所有6个关节");
        // } else {
        //     RCLCPP_ERROR(this->get_logger(), "❌ 只映射了 %zu 个关节，期望6个", 
        //                 joint_name_to_index_.size());
        // }

    }
    catch (const std::exception& e)
    {
        RCLCPP_ERROR(this->get_logger(), "模型加载失败: %s", e.what());
        return;
    }

    // 订阅机械臂关节状态话题
    joint_state_subscriber_ = this->create_subscription<sensor_msgs::msg::JointState>(
        "/joint_states", 10, std::bind(&IKNode::jointStateCallback, this, std::placeholders::_1));

    // 创建雅可比矩阵话题发布器
    jacobian_publisher_ = this->create_publisher<std_msgs::msg::Float64MultiArray>("jacobian_matrix", 10);
    
    // 创建末端执行器位置话题发布器
    ee_position_publisher_ = this->create_publisher<geometry_msgs::msg::Point>("end_effector_position", 10);
    
    RCLCPP_INFO(this->get_logger(), "雅可比矩阵话题已创建: /jacobian_matrix");
    RCLCPP_INFO(this->get_logger(), "末端执行器位置话题已创建: /end_effector_position");
    
    // 创建定时器以固定频率发布数据
    auto timer_callback = [this]() {this->publishJacobianAndPosition();};
    auto period = std::chrono::duration<double>(1.0 / publish_rate_);
    timer_ = this->create_wall_timer(period, timer_callback);
    RCLCPP_INFO(this->get_logger(), "以 %.1f Hz 的频率发布雅可比矩阵和末端执行器位置", publish_rate_);
}

//  析沟函数
IKNode::~IKNode()
{
    joint_state_subscriber_.reset();
    RCLCPP_INFO(this->get_logger(), "IK Node已关闭.");
}

// 回调函数
void IKNode::jointStateCallback(const sensor_msgs::msg::JointState::SharedPtr msg)
{
    
    try
    {   
        // 打印接收到的关节名称
        // RCLCPP_INFO(this->get_logger(), "\n===== 接收到的关节状态 =====");
        std::set<std::string> received_joints;
        for (size_t i = 0; i < msg->name.size(); ++i) {
            // RCLCPP_INFO(this->get_logger(), "关节 '%s': %.3f rad", msg->name[i].c_str(), msg->position[i]);
            received_joints.insert(msg->name[i]);
        }
        
        // 检查是否所有需要的关节都收到了
        std::vector<std::string> missing_joints;
        for (const auto& pair : joint_name_to_index_) {
            if (received_joints.find(pair.first) == received_joints.end()) {
                missing_joints.push_back(pair.first);
            }
        }
        
        if (!missing_joints.empty()) {
            RCLCPP_WARN(this->get_logger(), "缺少以下关节的状态:");
            for (const auto& joint : missing_joints) {
                RCLCPP_WARN(this->get_logger(), "  - %s", joint.c_str());
            }
        }
        
        // 将关节状态消息转换为Eigen向量
        for (size_t i = 0; i < msg->name.size(); ++i) {
            const std::string& joint_name = msg->name[i];
            if (joint_name_to_index_.find(joint_name) != joint_name_to_index_.end()) {
                int index = joint_name_to_index_[joint_name];
                if (index < current_joint_positions_.size()) {
                    current_joint_positions_[index] = msg->position[i];
                }
            }
        }
        // 打印转换后的状态
        // RCLCPP_INFO(this->get_logger(), "\n===== 转换后的关节状态 =====");
        // for (const auto& pair : joint_name_to_index_) {
        //     int index = pair.second;
        //     RCLCPP_INFO(this->get_logger(), "索引 %d ('%s'): %.3f rad", 
        //                index, pair.first.c_str(), current_joint_positions_[index]);
        // }
        
        // 计算雅可比矩阵
        computeEndEffectorJacobian(current_joint_positions_);
    }
    catch (const std::exception& e)
    {
        RCLCPP_ERROR(this->get_logger(), "Error in jointStateCallback: %s", e.what());
    }
}
// 自定义函数
// 计算末端执行器的雅可比矩阵
void IKNode::computeEndEffectorJacobian(const Eigen::VectorXd& q)
{
    // 正运动学计算
    pinocchio::forwardKinematics(model, data, q);
    pinocchio::updateFramePlacements(model, data);
    // 计算雅可比矩阵
    Eigen::MatrixXd jacobian(6, model.nv);
    jacobian.setZero();
    // 计算相对于世界坐标系的雅可比矩阵
    pinocchio::computeFrameJacobian(model, data, q, end_effector_frame_id, pinocchio::LOCAL_WORLD_ALIGNED,jacobian);
     // 打印雅可比矩阵信息
    // RCLCPP_INFO(this->get_logger(), "末端执行器位置: [%.3f, %.3f, %.3f]", 
    //            data.oMf[end_effector_frame_id].translation().x(),
    //            data.oMf[end_effector_frame_id].translation().y(),
    //            data.oMf[end_effector_frame_id].translation().z());
    // 打印

    // 保存雅可比矩阵和末端执行器位置
    current_jacobian_ = jacobian;
    current_end_effector_position_ = data.oMf[end_effector_frame_id].translation();


}
// 发布雅可比矩阵和末端执行器位置
void IKNode::publishJacobianAndPosition()
{
    // 发布雅可比矩阵
    auto jacobian_msg = std_msgs::msg::Float64MultiArray();
    
    // 设置布局信息
    jacobian_msg.layout.dim.push_back(std_msgs::msg::MultiArrayDimension());
    jacobian_msg.layout.dim[0].label = "rows";
    jacobian_msg.layout.dim[0].size = 6;
    jacobian_msg.layout.dim[0].stride = 6 * 6;
    
    jacobian_msg.layout.dim.push_back(std_msgs::msg::MultiArrayDimension());
    jacobian_msg.layout.dim[1].label = "columns";
    jacobian_msg.layout.dim[1].size = 6;
    jacobian_msg.layout.dim[1].stride = 6;
    
    // 将雅可比矩阵数据填充到消息中（按行优先顺序）
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            jacobian_msg.data.push_back(current_jacobian_(i, j));
        }
    }
    
    jacobian_publisher_->publish(jacobian_msg);
    
    // 发布末端执行器位置
    auto position_msg = geometry_msgs::msg::Point();
    position_msg.x = current_end_effector_position_.x();
    position_msg.y = current_end_effector_position_.y();
    position_msg.z = current_end_effector_position_.z();
    
    ee_position_publisher_->publish(position_msg);
    
    // 打印发布信息
    static int count = 0;
    if (++count % 30 == 0) { // 每30次发布打印一次
        RCLCPP_DEBUG(this->get_logger(), "已发布雅可比矩阵和末端执行器位置");
    }
}
// main函数：程序入口
int main(int argc, char * argv[])
{
    // 初始化ROS 2
    rclcpp::init(argc, argv);
    
    // 创建节点实例
    auto node = std::make_shared<IKNode>();
    
    // 运行节点（进入事件循环）
    rclcpp::spin(node);
    
    // 退出时清理
    rclcpp::shutdown();
    return 0;
}