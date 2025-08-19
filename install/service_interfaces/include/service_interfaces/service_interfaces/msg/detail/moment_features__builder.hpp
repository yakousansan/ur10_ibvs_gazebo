// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from service_interfaces:msg/MomentFeatures.idl
// generated code does not contain a copyright notice

#ifndef SERVICE_INTERFACES__MSG__DETAIL__MOMENT_FEATURES__BUILDER_HPP_
#define SERVICE_INTERFACES__MSG__DETAIL__MOMENT_FEATURES__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "service_interfaces/msg/detail/moment_features__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace service_interfaces
{

namespace msg
{

namespace builder
{

class Init_MomentFeatures_alpha
{
public:
  explicit Init_MomentFeatures_alpha(::service_interfaces::msg::MomentFeatures & msg)
  : msg_(msg)
  {}
  ::service_interfaces::msg::MomentFeatures alpha(::service_interfaces::msg::MomentFeatures::_alpha_type arg)
  {
    msg_.alpha = std::move(arg);
    return std::move(msg_);
  }

private:
  ::service_interfaces::msg::MomentFeatures msg_;
};

class Init_MomentFeatures_sy
{
public:
  explicit Init_MomentFeatures_sy(::service_interfaces::msg::MomentFeatures & msg)
  : msg_(msg)
  {}
  Init_MomentFeatures_alpha sy(::service_interfaces::msg::MomentFeatures::_sy_type arg)
  {
    msg_.sy = std::move(arg);
    return Init_MomentFeatures_alpha(msg_);
  }

private:
  ::service_interfaces::msg::MomentFeatures msg_;
};

class Init_MomentFeatures_sx
{
public:
  explicit Init_MomentFeatures_sx(::service_interfaces::msg::MomentFeatures & msg)
  : msg_(msg)
  {}
  Init_MomentFeatures_sy sx(::service_interfaces::msg::MomentFeatures::_sx_type arg)
  {
    msg_.sx = std::move(arg);
    return Init_MomentFeatures_sy(msg_);
  }

private:
  ::service_interfaces::msg::MomentFeatures msg_;
};

class Init_MomentFeatures_area
{
public:
  explicit Init_MomentFeatures_area(::service_interfaces::msg::MomentFeatures & msg)
  : msg_(msg)
  {}
  Init_MomentFeatures_sx area(::service_interfaces::msg::MomentFeatures::_area_type arg)
  {
    msg_.area = std::move(arg);
    return Init_MomentFeatures_sx(msg_);
  }

private:
  ::service_interfaces::msg::MomentFeatures msg_;
};

class Init_MomentFeatures_y_gravity
{
public:
  explicit Init_MomentFeatures_y_gravity(::service_interfaces::msg::MomentFeatures & msg)
  : msg_(msg)
  {}
  Init_MomentFeatures_area y_gravity(::service_interfaces::msg::MomentFeatures::_y_gravity_type arg)
  {
    msg_.y_gravity = std::move(arg);
    return Init_MomentFeatures_area(msg_);
  }

private:
  ::service_interfaces::msg::MomentFeatures msg_;
};

class Init_MomentFeatures_x_gravity
{
public:
  explicit Init_MomentFeatures_x_gravity(::service_interfaces::msg::MomentFeatures & msg)
  : msg_(msg)
  {}
  Init_MomentFeatures_y_gravity x_gravity(::service_interfaces::msg::MomentFeatures::_x_gravity_type arg)
  {
    msg_.x_gravity = std::move(arg);
    return Init_MomentFeatures_y_gravity(msg_);
  }

private:
  ::service_interfaces::msg::MomentFeatures msg_;
};

class Init_MomentFeatures_header
{
public:
  Init_MomentFeatures_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MomentFeatures_x_gravity header(::service_interfaces::msg::MomentFeatures::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_MomentFeatures_x_gravity(msg_);
  }

private:
  ::service_interfaces::msg::MomentFeatures msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::service_interfaces::msg::MomentFeatures>()
{
  return service_interfaces::msg::builder::Init_MomentFeatures_header();
}

}  // namespace service_interfaces

#endif  // SERVICE_INTERFACES__MSG__DETAIL__MOMENT_FEATURES__BUILDER_HPP_
