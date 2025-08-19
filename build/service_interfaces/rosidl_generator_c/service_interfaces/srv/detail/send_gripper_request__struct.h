// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from service_interfaces:srv/SendGripperRequest.idl
// generated code does not contain a copyright notice

#ifndef SERVICE_INTERFACES__SRV__DETAIL__SEND_GRIPPER_REQUEST__STRUCT_H_
#define SERVICE_INTERFACES__SRV__DETAIL__SEND_GRIPPER_REQUEST__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/SendGripperRequest in the package service_interfaces.
typedef struct service_interfaces__srv__SendGripperRequest_Request
{
  /// 0表示关闭夹爪, 1表示打开夹爪
  int32_t state;
} service_interfaces__srv__SendGripperRequest_Request;

// Struct for a sequence of service_interfaces__srv__SendGripperRequest_Request.
typedef struct service_interfaces__srv__SendGripperRequest_Request__Sequence
{
  service_interfaces__srv__SendGripperRequest_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} service_interfaces__srv__SendGripperRequest_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/SendGripperRequest in the package service_interfaces.
typedef struct service_interfaces__srv__SendGripperRequest_Response
{
  /// Response part
  /// 当前夹爪的状态，0表示关闭，1表示打开
  int32_t state;
  /// 返回的结果信息
  rosidl_runtime_c__String message;
} service_interfaces__srv__SendGripperRequest_Response;

// Struct for a sequence of service_interfaces__srv__SendGripperRequest_Response.
typedef struct service_interfaces__srv__SendGripperRequest_Response__Sequence
{
  service_interfaces__srv__SendGripperRequest_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} service_interfaces__srv__SendGripperRequest_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SERVICE_INTERFACES__SRV__DETAIL__SEND_GRIPPER_REQUEST__STRUCT_H_
