// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from service_interfaces:srv/GetJacobian.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "service_interfaces/srv/detail/get_jacobian__rosidl_typesupport_introspection_c.h"
#include "service_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "service_interfaces/srv/detail/get_jacobian__functions.h"
#include "service_interfaces/srv/detail/get_jacobian__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void service_interfaces__srv__GetJacobian_Request__rosidl_typesupport_introspection_c__GetJacobian_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  service_interfaces__srv__GetJacobian_Request__init(message_memory);
}

void service_interfaces__srv__GetJacobian_Request__rosidl_typesupport_introspection_c__GetJacobian_Request_fini_function(void * message_memory)
{
  service_interfaces__srv__GetJacobian_Request__fini(message_memory);
}

size_t service_interfaces__srv__GetJacobian_Request__rosidl_typesupport_introspection_c__size_function__GetJacobian_Request__joint_angles(
  const void * untyped_member)
{
  (void)untyped_member;
  return 6;
}

const void * service_interfaces__srv__GetJacobian_Request__rosidl_typesupport_introspection_c__get_const_function__GetJacobian_Request__joint_angles(
  const void * untyped_member, size_t index)
{
  const double * member =
    (const double *)(untyped_member);
  return &member[index];
}

void * service_interfaces__srv__GetJacobian_Request__rosidl_typesupport_introspection_c__get_function__GetJacobian_Request__joint_angles(
  void * untyped_member, size_t index)
{
  double * member =
    (double *)(untyped_member);
  return &member[index];
}

void service_interfaces__srv__GetJacobian_Request__rosidl_typesupport_introspection_c__fetch_function__GetJacobian_Request__joint_angles(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    service_interfaces__srv__GetJacobian_Request__rosidl_typesupport_introspection_c__get_const_function__GetJacobian_Request__joint_angles(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void service_interfaces__srv__GetJacobian_Request__rosidl_typesupport_introspection_c__assign_function__GetJacobian_Request__joint_angles(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    service_interfaces__srv__GetJacobian_Request__rosidl_typesupport_introspection_c__get_function__GetJacobian_Request__joint_angles(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember service_interfaces__srv__GetJacobian_Request__rosidl_typesupport_introspection_c__GetJacobian_Request_message_member_array[1] = {
  {
    "joint_angles",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    6,  // array size
    false,  // is upper bound
    offsetof(service_interfaces__srv__GetJacobian_Request, joint_angles),  // bytes offset in struct
    NULL,  // default value
    service_interfaces__srv__GetJacobian_Request__rosidl_typesupport_introspection_c__size_function__GetJacobian_Request__joint_angles,  // size() function pointer
    service_interfaces__srv__GetJacobian_Request__rosidl_typesupport_introspection_c__get_const_function__GetJacobian_Request__joint_angles,  // get_const(index) function pointer
    service_interfaces__srv__GetJacobian_Request__rosidl_typesupport_introspection_c__get_function__GetJacobian_Request__joint_angles,  // get(index) function pointer
    service_interfaces__srv__GetJacobian_Request__rosidl_typesupport_introspection_c__fetch_function__GetJacobian_Request__joint_angles,  // fetch(index, &value) function pointer
    service_interfaces__srv__GetJacobian_Request__rosidl_typesupport_introspection_c__assign_function__GetJacobian_Request__joint_angles,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers service_interfaces__srv__GetJacobian_Request__rosidl_typesupport_introspection_c__GetJacobian_Request_message_members = {
  "service_interfaces__srv",  // message namespace
  "GetJacobian_Request",  // message name
  1,  // number of fields
  sizeof(service_interfaces__srv__GetJacobian_Request),
  service_interfaces__srv__GetJacobian_Request__rosidl_typesupport_introspection_c__GetJacobian_Request_message_member_array,  // message members
  service_interfaces__srv__GetJacobian_Request__rosidl_typesupport_introspection_c__GetJacobian_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  service_interfaces__srv__GetJacobian_Request__rosidl_typesupport_introspection_c__GetJacobian_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t service_interfaces__srv__GetJacobian_Request__rosidl_typesupport_introspection_c__GetJacobian_Request_message_type_support_handle = {
  0,
  &service_interfaces__srv__GetJacobian_Request__rosidl_typesupport_introspection_c__GetJacobian_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_service_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_interfaces, srv, GetJacobian_Request)() {
  if (!service_interfaces__srv__GetJacobian_Request__rosidl_typesupport_introspection_c__GetJacobian_Request_message_type_support_handle.typesupport_identifier) {
    service_interfaces__srv__GetJacobian_Request__rosidl_typesupport_introspection_c__GetJacobian_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &service_interfaces__srv__GetJacobian_Request__rosidl_typesupport_introspection_c__GetJacobian_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "service_interfaces/srv/detail/get_jacobian__rosidl_typesupport_introspection_c.h"
// already included above
// #include "service_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "service_interfaces/srv/detail/get_jacobian__functions.h"
// already included above
// #include "service_interfaces/srv/detail/get_jacobian__struct.h"


// Include directives for member types
// Member `jacobian_matrix`
#include "std_msgs/msg/float64_multi_array.h"
// Member `jacobian_matrix`
#include "std_msgs/msg/detail/float64_multi_array__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void service_interfaces__srv__GetJacobian_Response__rosidl_typesupport_introspection_c__GetJacobian_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  service_interfaces__srv__GetJacobian_Response__init(message_memory);
}

void service_interfaces__srv__GetJacobian_Response__rosidl_typesupport_introspection_c__GetJacobian_Response_fini_function(void * message_memory)
{
  service_interfaces__srv__GetJacobian_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember service_interfaces__srv__GetJacobian_Response__rosidl_typesupport_introspection_c__GetJacobian_Response_message_member_array[2] = {
  {
    "jacobian_matrix",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(service_interfaces__srv__GetJacobian_Response, jacobian_matrix),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(service_interfaces__srv__GetJacobian_Response, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers service_interfaces__srv__GetJacobian_Response__rosidl_typesupport_introspection_c__GetJacobian_Response_message_members = {
  "service_interfaces__srv",  // message namespace
  "GetJacobian_Response",  // message name
  2,  // number of fields
  sizeof(service_interfaces__srv__GetJacobian_Response),
  service_interfaces__srv__GetJacobian_Response__rosidl_typesupport_introspection_c__GetJacobian_Response_message_member_array,  // message members
  service_interfaces__srv__GetJacobian_Response__rosidl_typesupport_introspection_c__GetJacobian_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  service_interfaces__srv__GetJacobian_Response__rosidl_typesupport_introspection_c__GetJacobian_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t service_interfaces__srv__GetJacobian_Response__rosidl_typesupport_introspection_c__GetJacobian_Response_message_type_support_handle = {
  0,
  &service_interfaces__srv__GetJacobian_Response__rosidl_typesupport_introspection_c__GetJacobian_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_service_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_interfaces, srv, GetJacobian_Response)() {
  service_interfaces__srv__GetJacobian_Response__rosidl_typesupport_introspection_c__GetJacobian_Response_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Float64MultiArray)();
  if (!service_interfaces__srv__GetJacobian_Response__rosidl_typesupport_introspection_c__GetJacobian_Response_message_type_support_handle.typesupport_identifier) {
    service_interfaces__srv__GetJacobian_Response__rosidl_typesupport_introspection_c__GetJacobian_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &service_interfaces__srv__GetJacobian_Response__rosidl_typesupport_introspection_c__GetJacobian_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "service_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "service_interfaces/srv/detail/get_jacobian__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers service_interfaces__srv__detail__get_jacobian__rosidl_typesupport_introspection_c__GetJacobian_service_members = {
  "service_interfaces__srv",  // service namespace
  "GetJacobian",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // service_interfaces__srv__detail__get_jacobian__rosidl_typesupport_introspection_c__GetJacobian_Request_message_type_support_handle,
  NULL  // response message
  // service_interfaces__srv__detail__get_jacobian__rosidl_typesupport_introspection_c__GetJacobian_Response_message_type_support_handle
};

static rosidl_service_type_support_t service_interfaces__srv__detail__get_jacobian__rosidl_typesupport_introspection_c__GetJacobian_service_type_support_handle = {
  0,
  &service_interfaces__srv__detail__get_jacobian__rosidl_typesupport_introspection_c__GetJacobian_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_interfaces, srv, GetJacobian_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_interfaces, srv, GetJacobian_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_service_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_interfaces, srv, GetJacobian)() {
  if (!service_interfaces__srv__detail__get_jacobian__rosidl_typesupport_introspection_c__GetJacobian_service_type_support_handle.typesupport_identifier) {
    service_interfaces__srv__detail__get_jacobian__rosidl_typesupport_introspection_c__GetJacobian_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)service_interfaces__srv__detail__get_jacobian__rosidl_typesupport_introspection_c__GetJacobian_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_interfaces, srv, GetJacobian_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_interfaces, srv, GetJacobian_Response)()->data;
  }

  return &service_interfaces__srv__detail__get_jacobian__rosidl_typesupport_introspection_c__GetJacobian_service_type_support_handle;
}
