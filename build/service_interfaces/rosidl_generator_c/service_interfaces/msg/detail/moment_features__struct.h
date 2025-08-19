// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from service_interfaces:msg/MomentFeatures.idl
// generated code does not contain a copyright notice

#ifndef SERVICE_INTERFACES__MSG__DETAIL__MOMENT_FEATURES__STRUCT_H_
#define SERVICE_INTERFACES__MSG__DETAIL__MOMENT_FEATURES__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"

/// Struct defined in msg/MomentFeatures in the package service_interfaces.
typedef struct service_interfaces__msg__MomentFeatures
{
  std_msgs__msg__Header header;
  /// 重心X坐标
  double x_gravity;
  /// 重心Y坐标
  double y_gravity;
  /// 区域面积（零阶矩）
  double area;
  /// sx
  double sx;
  /// sy
  double sy;
  /// 方向角
  double alpha;
} service_interfaces__msg__MomentFeatures;

// Struct for a sequence of service_interfaces__msg__MomentFeatures.
typedef struct service_interfaces__msg__MomentFeatures__Sequence
{
  service_interfaces__msg__MomentFeatures * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} service_interfaces__msg__MomentFeatures__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SERVICE_INTERFACES__MSG__DETAIL__MOMENT_FEATURES__STRUCT_H_
