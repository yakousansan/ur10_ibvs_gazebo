// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from service_interfaces:srv/SendGripperRequest.idl
// generated code does not contain a copyright notice

#ifndef SERVICE_INTERFACES__SRV__DETAIL__SEND_GRIPPER_REQUEST__BUILDER_HPP_
#define SERVICE_INTERFACES__SRV__DETAIL__SEND_GRIPPER_REQUEST__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "service_interfaces/srv/detail/send_gripper_request__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace service_interfaces
{

namespace srv
{

namespace builder
{

class Init_SendGripperRequest_Request_state
{
public:
  Init_SendGripperRequest_Request_state()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::service_interfaces::srv::SendGripperRequest_Request state(::service_interfaces::srv::SendGripperRequest_Request::_state_type arg)
  {
    msg_.state = std::move(arg);
    return std::move(msg_);
  }

private:
  ::service_interfaces::srv::SendGripperRequest_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::service_interfaces::srv::SendGripperRequest_Request>()
{
  return service_interfaces::srv::builder::Init_SendGripperRequest_Request_state();
}

}  // namespace service_interfaces


namespace service_interfaces
{

namespace srv
{

namespace builder
{

class Init_SendGripperRequest_Response_message
{
public:
  explicit Init_SendGripperRequest_Response_message(::service_interfaces::srv::SendGripperRequest_Response & msg)
  : msg_(msg)
  {}
  ::service_interfaces::srv::SendGripperRequest_Response message(::service_interfaces::srv::SendGripperRequest_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::service_interfaces::srv::SendGripperRequest_Response msg_;
};

class Init_SendGripperRequest_Response_state
{
public:
  Init_SendGripperRequest_Response_state()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SendGripperRequest_Response_message state(::service_interfaces::srv::SendGripperRequest_Response::_state_type arg)
  {
    msg_.state = std::move(arg);
    return Init_SendGripperRequest_Response_message(msg_);
  }

private:
  ::service_interfaces::srv::SendGripperRequest_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::service_interfaces::srv::SendGripperRequest_Response>()
{
  return service_interfaces::srv::builder::Init_SendGripperRequest_Response_state();
}

}  // namespace service_interfaces

#endif  // SERVICE_INTERFACES__SRV__DETAIL__SEND_GRIPPER_REQUEST__BUILDER_HPP_
