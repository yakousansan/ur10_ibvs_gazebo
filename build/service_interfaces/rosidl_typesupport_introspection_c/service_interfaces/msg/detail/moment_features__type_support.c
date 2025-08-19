// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from service_interfaces:msg/MomentFeatures.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "service_interfaces/msg/detail/moment_features__rosidl_typesupport_introspection_c.h"
#include "service_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "service_interfaces/msg/detail/moment_features__functions.h"
#include "service_interfaces/msg/detail/moment_features__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void service_interfaces__msg__MomentFeatures__rosidl_typesupport_introspection_c__MomentFeatures_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  service_interfaces__msg__MomentFeatures__init(message_memory);
}

void service_interfaces__msg__MomentFeatures__rosidl_typesupport_introspection_c__MomentFeatures_fini_function(void * message_memory)
{
  service_interfaces__msg__MomentFeatures__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember service_interfaces__msg__MomentFeatures__rosidl_typesupport_introspection_c__MomentFeatures_message_member_array[7] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(service_interfaces__msg__MomentFeatures, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "x_gravity",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(service_interfaces__msg__MomentFeatures, x_gravity),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "y_gravity",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(service_interfaces__msg__MomentFeatures, y_gravity),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "area",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(service_interfaces__msg__MomentFeatures, area),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "sx",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(service_interfaces__msg__MomentFeatures, sx),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "sy",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(service_interfaces__msg__MomentFeatures, sy),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "alpha",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(service_interfaces__msg__MomentFeatures, alpha),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers service_interfaces__msg__MomentFeatures__rosidl_typesupport_introspection_c__MomentFeatures_message_members = {
  "service_interfaces__msg",  // message namespace
  "MomentFeatures",  // message name
  7,  // number of fields
  sizeof(service_interfaces__msg__MomentFeatures),
  service_interfaces__msg__MomentFeatures__rosidl_typesupport_introspection_c__MomentFeatures_message_member_array,  // message members
  service_interfaces__msg__MomentFeatures__rosidl_typesupport_introspection_c__MomentFeatures_init_function,  // function to initialize message memory (memory has to be allocated)
  service_interfaces__msg__MomentFeatures__rosidl_typesupport_introspection_c__MomentFeatures_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t service_interfaces__msg__MomentFeatures__rosidl_typesupport_introspection_c__MomentFeatures_message_type_support_handle = {
  0,
  &service_interfaces__msg__MomentFeatures__rosidl_typesupport_introspection_c__MomentFeatures_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_service_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_interfaces, msg, MomentFeatures)() {
  service_interfaces__msg__MomentFeatures__rosidl_typesupport_introspection_c__MomentFeatures_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  if (!service_interfaces__msg__MomentFeatures__rosidl_typesupport_introspection_c__MomentFeatures_message_type_support_handle.typesupport_identifier) {
    service_interfaces__msg__MomentFeatures__rosidl_typesupport_introspection_c__MomentFeatures_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &service_interfaces__msg__MomentFeatures__rosidl_typesupport_introspection_c__MomentFeatures_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
