// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from service_interfaces:srv/SendGraspRequest.idl
// generated code does not contain a copyright notice

#ifndef SERVICE_INTERFACES__SRV__DETAIL__SEND_GRASP_REQUEST__TRAITS_HPP_
#define SERVICE_INTERFACES__SRV__DETAIL__SEND_GRASP_REQUEST__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "service_interfaces/srv/detail/send_grasp_request__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace service_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const SendGraspRequest_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: x
  {
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << ", ";
  }

  // member: y
  {
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << ", ";
  }

  // member: z
  {
    out << "z: ";
    rosidl_generator_traits::value_to_yaml(msg.z, out);
    out << ", ";
  }

  // member: qw
  {
    out << "qw: ";
    rosidl_generator_traits::value_to_yaml(msg.qw, out);
    out << ", ";
  }

  // member: qx
  {
    out << "qx: ";
    rosidl_generator_traits::value_to_yaml(msg.qx, out);
    out << ", ";
  }

  // member: qy
  {
    out << "qy: ";
    rosidl_generator_traits::value_to_yaml(msg.qy, out);
    out << ", ";
  }

  // member: qz
  {
    out << "qz: ";
    rosidl_generator_traits::value_to_yaml(msg.qz, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SendGraspRequest_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << "\n";
  }

  // member: y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << "\n";
  }

  // member: z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "z: ";
    rosidl_generator_traits::value_to_yaml(msg.z, out);
    out << "\n";
  }

  // member: qw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "qw: ";
    rosidl_generator_traits::value_to_yaml(msg.qw, out);
    out << "\n";
  }

  // member: qx
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "qx: ";
    rosidl_generator_traits::value_to_yaml(msg.qx, out);
    out << "\n";
  }

  // member: qy
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "qy: ";
    rosidl_generator_traits::value_to_yaml(msg.qy, out);
    out << "\n";
  }

  // member: qz
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "qz: ";
    rosidl_generator_traits::value_to_yaml(msg.qz, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SendGraspRequest_Request & msg, bool use_flow_style = false)
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
  const service_interfaces::srv::SendGraspRequest_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  service_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use service_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const service_interfaces::srv::SendGraspRequest_Request & msg)
{
  return service_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<service_interfaces::srv::SendGraspRequest_Request>()
{
  return "service_interfaces::srv::SendGraspRequest_Request";
}

template<>
inline const char * name<service_interfaces::srv::SendGraspRequest_Request>()
{
  return "service_interfaces/srv/SendGraspRequest_Request";
}

template<>
struct has_fixed_size<service_interfaces::srv::SendGraspRequest_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<service_interfaces::srv::SendGraspRequest_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<service_interfaces::srv::SendGraspRequest_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace service_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const SendGraspRequest_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SendGraspRequest_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SendGraspRequest_Response & msg, bool use_flow_style = false)
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
  const service_interfaces::srv::SendGraspRequest_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  service_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use service_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const service_interfaces::srv::SendGraspRequest_Response & msg)
{
  return service_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<service_interfaces::srv::SendGraspRequest_Response>()
{
  return "service_interfaces::srv::SendGraspRequest_Response";
}

template<>
inline const char * name<service_interfaces::srv::SendGraspRequest_Response>()
{
  return "service_interfaces/srv/SendGraspRequest_Response";
}

template<>
struct has_fixed_size<service_interfaces::srv::SendGraspRequest_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<service_interfaces::srv::SendGraspRequest_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<service_interfaces::srv::SendGraspRequest_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<service_interfaces::srv::SendGraspRequest>()
{
  return "service_interfaces::srv::SendGraspRequest";
}

template<>
inline const char * name<service_interfaces::srv::SendGraspRequest>()
{
  return "service_interfaces/srv/SendGraspRequest";
}

template<>
struct has_fixed_size<service_interfaces::srv::SendGraspRequest>
  : std::integral_constant<
    bool,
    has_fixed_size<service_interfaces::srv::SendGraspRequest_Request>::value &&
    has_fixed_size<service_interfaces::srv::SendGraspRequest_Response>::value
  >
{
};

template<>
struct has_bounded_size<service_interfaces::srv::SendGraspRequest>
  : std::integral_constant<
    bool,
    has_bounded_size<service_interfaces::srv::SendGraspRequest_Request>::value &&
    has_bounded_size<service_interfaces::srv::SendGraspRequest_Response>::value
  >
{
};

template<>
struct is_service<service_interfaces::srv::SendGraspRequest>
  : std::true_type
{
};

template<>
struct is_service_request<service_interfaces::srv::SendGraspRequest_Request>
  : std::true_type
{
};

template<>
struct is_service_response<service_interfaces::srv::SendGraspRequest_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // SERVICE_INTERFACES__SRV__DETAIL__SEND_GRASP_REQUEST__TRAITS_HPP_
