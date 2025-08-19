// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from service_interfaces:srv/GetJacobian.idl
// generated code does not contain a copyright notice

#ifndef SERVICE_INTERFACES__SRV__DETAIL__GET_JACOBIAN__BUILDER_HPP_
#define SERVICE_INTERFACES__SRV__DETAIL__GET_JACOBIAN__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "service_interfaces/srv/detail/get_jacobian__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace service_interfaces
{

namespace srv
{

namespace builder
{

class Init_GetJacobian_Request_joint_angles
{
public:
  Init_GetJacobian_Request_joint_angles()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::service_interfaces::srv::GetJacobian_Request joint_angles(::service_interfaces::srv::GetJacobian_Request::_joint_angles_type arg)
  {
    msg_.joint_angles = std::move(arg);
    return std::move(msg_);
  }

private:
  ::service_interfaces::srv::GetJacobian_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::service_interfaces::srv::GetJacobian_Request>()
{
  return service_interfaces::srv::builder::Init_GetJacobian_Request_joint_angles();
}

}  // namespace service_interfaces


namespace service_interfaces
{

namespace srv
{

namespace builder
{

class Init_GetJacobian_Response_success
{
public:
  explicit Init_GetJacobian_Response_success(::service_interfaces::srv::GetJacobian_Response & msg)
  : msg_(msg)
  {}
  ::service_interfaces::srv::GetJacobian_Response success(::service_interfaces::srv::GetJacobian_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return std::move(msg_);
  }

private:
  ::service_interfaces::srv::GetJacobian_Response msg_;
};

class Init_GetJacobian_Response_jacobian_matrix
{
public:
  Init_GetJacobian_Response_jacobian_matrix()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetJacobian_Response_success jacobian_matrix(::service_interfaces::srv::GetJacobian_Response::_jacobian_matrix_type arg)
  {
    msg_.jacobian_matrix = std::move(arg);
    return Init_GetJacobian_Response_success(msg_);
  }

private:
  ::service_interfaces::srv::GetJacobian_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::service_interfaces::srv::GetJacobian_Response>()
{
  return service_interfaces::srv::builder::Init_GetJacobian_Response_jacobian_matrix();
}

}  // namespace service_interfaces

#endif  // SERVICE_INTERFACES__SRV__DETAIL__GET_JACOBIAN__BUILDER_HPP_
