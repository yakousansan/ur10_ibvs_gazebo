// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from service_interfaces:srv/GetJacobian.idl
// generated code does not contain a copyright notice

#ifndef SERVICE_INTERFACES__SRV__DETAIL__GET_JACOBIAN__STRUCT_H_
#define SERVICE_INTERFACES__SRV__DETAIL__GET_JACOBIAN__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/GetJacobian in the package service_interfaces.
typedef struct service_interfaces__srv__GetJacobian_Request
{
  /// Request: 关节角度
  /// 关节角度是一个包含所有关节角度的数组
  double joint_angles[6];
} service_interfaces__srv__GetJacobian_Request;

// Struct for a sequence of service_interfaces__srv__GetJacobian_Request.
typedef struct service_interfaces__srv__GetJacobian_Request__Sequence
{
  service_interfaces__srv__GetJacobian_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} service_interfaces__srv__GetJacobian_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'jacobian_matrix'
#include "std_msgs/msg/detail/float64_multi_array__struct.h"

/// Struct defined in srv/GetJacobian in the package service_interfaces.
typedef struct service_interfaces__srv__GetJacobian_Response
{
  std_msgs__msg__Float64MultiArray jacobian_matrix;
  bool success;
} service_interfaces__srv__GetJacobian_Response;

// Struct for a sequence of service_interfaces__srv__GetJacobian_Response.
typedef struct service_interfaces__srv__GetJacobian_Response__Sequence
{
  service_interfaces__srv__GetJacobian_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} service_interfaces__srv__GetJacobian_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SERVICE_INTERFACES__SRV__DETAIL__GET_JACOBIAN__STRUCT_H_
