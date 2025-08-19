// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from service_interfaces:srv/SendGraspRequest.idl
// generated code does not contain a copyright notice

#ifndef SERVICE_INTERFACES__SRV__DETAIL__SEND_GRASP_REQUEST__STRUCT_H_
#define SERVICE_INTERFACES__SRV__DETAIL__SEND_GRASP_REQUEST__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/SendGraspRequest in the package service_interfaces.
typedef struct service_interfaces__srv__SendGraspRequest_Request
{
  /// 机器人操作器端点的x坐标
  double x;
  /// 机器人操作器端点的y坐标
  double y;
  /// 机器人操作器端点的z坐标
  double z;
  /// 四元数w分量
  double qw;
  /// 四元数x分量
  double qx;
  /// 四元数y分量
  double qy;
  /// 四元数z分量
  double qz;
} service_interfaces__srv__SendGraspRequest_Request;

// Struct for a sequence of service_interfaces__srv__SendGraspRequest_Request.
typedef struct service_interfaces__srv__SendGraspRequest_Request__Sequence
{
  service_interfaces__srv__SendGraspRequest_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} service_interfaces__srv__SendGraspRequest_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/SendGraspRequest in the package service_interfaces.
typedef struct service_interfaces__srv__SendGraspRequest_Response
{
  /// Response part
  /// 规划是否成功
  bool success;
  /// 返回的结果信息
  rosidl_runtime_c__String message;
} service_interfaces__srv__SendGraspRequest_Response;

// Struct for a sequence of service_interfaces__srv__SendGraspRequest_Response.
typedef struct service_interfaces__srv__SendGraspRequest_Response__Sequence
{
  service_interfaces__srv__SendGraspRequest_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} service_interfaces__srv__SendGraspRequest_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SERVICE_INTERFACES__SRV__DETAIL__SEND_GRASP_REQUEST__STRUCT_H_
