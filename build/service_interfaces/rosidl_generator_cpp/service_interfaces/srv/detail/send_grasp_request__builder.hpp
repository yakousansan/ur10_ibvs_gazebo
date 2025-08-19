// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from service_interfaces:srv/SendGraspRequest.idl
// generated code does not contain a copyright notice

#ifndef SERVICE_INTERFACES__SRV__DETAIL__SEND_GRASP_REQUEST__BUILDER_HPP_
#define SERVICE_INTERFACES__SRV__DETAIL__SEND_GRASP_REQUEST__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "service_interfaces/srv/detail/send_grasp_request__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace service_interfaces
{

namespace srv
{

namespace builder
{

class Init_SendGraspRequest_Request_qz
{
public:
  explicit Init_SendGraspRequest_Request_qz(::service_interfaces::srv::SendGraspRequest_Request & msg)
  : msg_(msg)
  {}
  ::service_interfaces::srv::SendGraspRequest_Request qz(::service_interfaces::srv::SendGraspRequest_Request::_qz_type arg)
  {
    msg_.qz = std::move(arg);
    return std::move(msg_);
  }

private:
  ::service_interfaces::srv::SendGraspRequest_Request msg_;
};

class Init_SendGraspRequest_Request_qy
{
public:
  explicit Init_SendGraspRequest_Request_qy(::service_interfaces::srv::SendGraspRequest_Request & msg)
  : msg_(msg)
  {}
  Init_SendGraspRequest_Request_qz qy(::service_interfaces::srv::SendGraspRequest_Request::_qy_type arg)
  {
    msg_.qy = std::move(arg);
    return Init_SendGraspRequest_Request_qz(msg_);
  }

private:
  ::service_interfaces::srv::SendGraspRequest_Request msg_;
};

class Init_SendGraspRequest_Request_qx
{
public:
  explicit Init_SendGraspRequest_Request_qx(::service_interfaces::srv::SendGraspRequest_Request & msg)
  : msg_(msg)
  {}
  Init_SendGraspRequest_Request_qy qx(::service_interfaces::srv::SendGraspRequest_Request::_qx_type arg)
  {
    msg_.qx = std::move(arg);
    return Init_SendGraspRequest_Request_qy(msg_);
  }

private:
  ::service_interfaces::srv::SendGraspRequest_Request msg_;
};

class Init_SendGraspRequest_Request_qw
{
public:
  explicit Init_SendGraspRequest_Request_qw(::service_interfaces::srv::SendGraspRequest_Request & msg)
  : msg_(msg)
  {}
  Init_SendGraspRequest_Request_qx qw(::service_interfaces::srv::SendGraspRequest_Request::_qw_type arg)
  {
    msg_.qw = std::move(arg);
    return Init_SendGraspRequest_Request_qx(msg_);
  }

private:
  ::service_interfaces::srv::SendGraspRequest_Request msg_;
};

class Init_SendGraspRequest_Request_z
{
public:
  explicit Init_SendGraspRequest_Request_z(::service_interfaces::srv::SendGraspRequest_Request & msg)
  : msg_(msg)
  {}
  Init_SendGraspRequest_Request_qw z(::service_interfaces::srv::SendGraspRequest_Request::_z_type arg)
  {
    msg_.z = std::move(arg);
    return Init_SendGraspRequest_Request_qw(msg_);
  }

private:
  ::service_interfaces::srv::SendGraspRequest_Request msg_;
};

class Init_SendGraspRequest_Request_y
{
public:
  explicit Init_SendGraspRequest_Request_y(::service_interfaces::srv::SendGraspRequest_Request & msg)
  : msg_(msg)
  {}
  Init_SendGraspRequest_Request_z y(::service_interfaces::srv::SendGraspRequest_Request::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_SendGraspRequest_Request_z(msg_);
  }

private:
  ::service_interfaces::srv::SendGraspRequest_Request msg_;
};

class Init_SendGraspRequest_Request_x
{
public:
  Init_SendGraspRequest_Request_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SendGraspRequest_Request_y x(::service_interfaces::srv::SendGraspRequest_Request::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_SendGraspRequest_Request_y(msg_);
  }

private:
  ::service_interfaces::srv::SendGraspRequest_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::service_interfaces::srv::SendGraspRequest_Request>()
{
  return service_interfaces::srv::builder::Init_SendGraspRequest_Request_x();
}

}  // namespace service_interfaces


namespace service_interfaces
{

namespace srv
{

namespace builder
{

class Init_SendGraspRequest_Response_message
{
public:
  explicit Init_SendGraspRequest_Response_message(::service_interfaces::srv::SendGraspRequest_Response & msg)
  : msg_(msg)
  {}
  ::service_interfaces::srv::SendGraspRequest_Response message(::service_interfaces::srv::SendGraspRequest_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::service_interfaces::srv::SendGraspRequest_Response msg_;
};

class Init_SendGraspRequest_Response_success
{
public:
  Init_SendGraspRequest_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SendGraspRequest_Response_message success(::service_interfaces::srv::SendGraspRequest_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_SendGraspRequest_Response_message(msg_);
  }

private:
  ::service_interfaces::srv::SendGraspRequest_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::service_interfaces::srv::SendGraspRequest_Response>()
{
  return service_interfaces::srv::builder::Init_SendGraspRequest_Response_success();
}

}  // namespace service_interfaces

#endif  // SERVICE_INTERFACES__SRV__DETAIL__SEND_GRASP_REQUEST__BUILDER_HPP_
