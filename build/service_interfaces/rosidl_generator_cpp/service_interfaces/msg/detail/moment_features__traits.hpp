// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from service_interfaces:msg/MomentFeatures.idl
// generated code does not contain a copyright notice

#ifndef SERVICE_INTERFACES__MSG__DETAIL__MOMENT_FEATURES__TRAITS_HPP_
#define SERVICE_INTERFACES__MSG__DETAIL__MOMENT_FEATURES__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "service_interfaces/msg/detail/moment_features__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace service_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const MomentFeatures & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: x_gravity
  {
    out << "x_gravity: ";
    rosidl_generator_traits::value_to_yaml(msg.x_gravity, out);
    out << ", ";
  }

  // member: y_gravity
  {
    out << "y_gravity: ";
    rosidl_generator_traits::value_to_yaml(msg.y_gravity, out);
    out << ", ";
  }

  // member: area
  {
    out << "area: ";
    rosidl_generator_traits::value_to_yaml(msg.area, out);
    out << ", ";
  }

  // member: sx
  {
    out << "sx: ";
    rosidl_generator_traits::value_to_yaml(msg.sx, out);
    out << ", ";
  }

  // member: sy
  {
    out << "sy: ";
    rosidl_generator_traits::value_to_yaml(msg.sy, out);
    out << ", ";
  }

  // member: alpha
  {
    out << "alpha: ";
    rosidl_generator_traits::value_to_yaml(msg.alpha, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MomentFeatures & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: x_gravity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x_gravity: ";
    rosidl_generator_traits::value_to_yaml(msg.x_gravity, out);
    out << "\n";
  }

  // member: y_gravity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y_gravity: ";
    rosidl_generator_traits::value_to_yaml(msg.y_gravity, out);
    out << "\n";
  }

  // member: area
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "area: ";
    rosidl_generator_traits::value_to_yaml(msg.area, out);
    out << "\n";
  }

  // member: sx
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sx: ";
    rosidl_generator_traits::value_to_yaml(msg.sx, out);
    out << "\n";
  }

  // member: sy
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sy: ";
    rosidl_generator_traits::value_to_yaml(msg.sy, out);
    out << "\n";
  }

  // member: alpha
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "alpha: ";
    rosidl_generator_traits::value_to_yaml(msg.alpha, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MomentFeatures & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace service_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use service_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const service_interfaces::msg::MomentFeatures & msg,
  std::ostream & out, size_t indentation = 0)
{
  service_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use service_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const service_interfaces::msg::MomentFeatures & msg)
{
  return service_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<service_interfaces::msg::MomentFeatures>()
{
  return "service_interfaces::msg::MomentFeatures";
}

template<>
inline const char * name<service_interfaces::msg::MomentFeatures>()
{
  return "service_interfaces/msg/MomentFeatures";
}

template<>
struct has_fixed_size<service_interfaces::msg::MomentFeatures>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<service_interfaces::msg::MomentFeatures>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<service_interfaces::msg::MomentFeatures>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SERVICE_INTERFACES__MSG__DETAIL__MOMENT_FEATURES__TRAITS_HPP_
