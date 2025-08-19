// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from service_interfaces:srv/GetJacobian.idl
// generated code does not contain a copyright notice

#ifndef SERVICE_INTERFACES__SRV__DETAIL__GET_JACOBIAN__TRAITS_HPP_
#define SERVICE_INTERFACES__SRV__DETAIL__GET_JACOBIAN__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "service_interfaces/srv/detail/get_jacobian__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace service_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetJacobian_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: joint_angles
  {
    if (msg.joint_angles.size() == 0) {
      out << "joint_angles: []";
    } else {
      out << "joint_angles: [";
      size_t pending_items = msg.joint_angles.size();
      for (auto item : msg.joint_angles) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetJacobian_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: joint_angles
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.joint_angles.size() == 0) {
      out << "joint_angles: []\n";
    } else {
      out << "joint_angles:\n";
      for (auto item : msg.joint_angles) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetJacobian_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace service_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use service_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const service_interfaces::srv::GetJacobian_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  service_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use service_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const service_interfaces::srv::GetJacobian_Request & msg)
{
  return service_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<service_interfaces::srv::GetJacobian_Request>()
{
  return "service_interfaces::srv::GetJacobian_Request";
}

template<>
inline const char * name<service_interfaces::srv::GetJacobian_Request>()
{
  return "service_interfaces/srv/GetJacobian_Request";
}

template<>
struct has_fixed_size<service_interfaces::srv::GetJacobian_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<service_interfaces::srv::GetJacobian_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<service_interfaces::srv::GetJacobian_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'jacobian_matrix'
#include "std_msgs/msg/detail/float64_multi_array__traits.hpp"

namespace service_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetJacobian_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: jacobian_matrix
  {
    out << "jacobian_matrix: ";
    to_flow_style_yaml(msg.jacobian_matrix, out);
    out << ", ";
  }

  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetJacobian_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: jacobian_matrix
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "jacobian_matrix:\n";
    to_block_style_yaml(msg.jacobian_matrix, out, indentation + 2);
  }

  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetJacobian_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace service_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use service_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const service_interfaces::srv::GetJacobian_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  service_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use service_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const service_interfaces::srv::GetJacobian_Response & msg)
{
  return service_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<service_interfaces::srv::GetJacobian_Response>()
{
  return "service_interfaces::srv::GetJacobian_Response";
}

template<>
inline const char * name<service_interfaces::srv::GetJacobian_Response>()
{
  return "service_interfaces/srv/GetJacobian_Response";
}

template<>
struct has_fixed_size<service_interfaces::srv::GetJacobian_Response>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Float64MultiArray>::value> {};

template<>
struct has_bounded_size<service_interfaces::srv::GetJacobian_Response>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Float64MultiArray>::value> {};

template<>
struct is_message<service_interfaces::srv::GetJacobian_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<service_interfaces::srv::GetJacobian>()
{
  return "service_interfaces::srv::GetJacobian";
}

template<>
inline const char * name<service_interfaces::srv::GetJacobian>()
{
  return "service_interfaces/srv/GetJacobian";
}

template<>
struct has_fixed_size<service_interfaces::srv::GetJacobian>
  : std::integral_constant<
    bool,
    has_fixed_size<service_interfaces::srv::GetJacobian_Request>::value &&
    has_fixed_size<service_interfaces::srv::GetJacobian_Response>::value
  >
{
};

template<>
struct has_bounded_size<service_interfaces::srv::GetJacobian>
  : std::integral_constant<
    bool,
    has_bounded_size<service_interfaces::srv::GetJacobian_Request>::value &&
    has_bounded_size<service_interfaces::srv::GetJacobian_Response>::value
  >
{
};

template<>
struct is_service<service_interfaces::srv::GetJacobian>
  : std::true_type
{
};

template<>
struct is_service_request<service_interfaces::srv::GetJacobian_Request>
  : std::true_type
{
};

template<>
struct is_service_response<service_interfaces::srv::GetJacobian_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // SERVICE_INTERFACES__SRV__DETAIL__GET_JACOBIAN__TRAITS_HPP_
