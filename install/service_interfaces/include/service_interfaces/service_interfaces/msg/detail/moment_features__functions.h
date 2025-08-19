// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from service_interfaces:msg/MomentFeatures.idl
// generated code does not contain a copyright notice

#ifndef SERVICE_INTERFACES__MSG__DETAIL__MOMENT_FEATURES__FUNCTIONS_H_
#define SERVICE_INTERFACES__MSG__DETAIL__MOMENT_FEATURES__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "service_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "service_interfaces/msg/detail/moment_features__struct.h"

/// Initialize msg/MomentFeatures message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * service_interfaces__msg__MomentFeatures
 * )) before or use
 * service_interfaces__msg__MomentFeatures__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_service_interfaces
bool
service_interfaces__msg__MomentFeatures__init(service_interfaces__msg__MomentFeatures * msg);

/// Finalize msg/MomentFeatures message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_service_interfaces
void
service_interfaces__msg__MomentFeatures__fini(service_interfaces__msg__MomentFeatures * msg);

/// Create msg/MomentFeatures message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * service_interfaces__msg__MomentFeatures__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_service_interfaces
service_interfaces__msg__MomentFeatures *
service_interfaces__msg__MomentFeatures__create();

/// Destroy msg/MomentFeatures message.
/**
 * It calls
 * service_interfaces__msg__MomentFeatures__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_service_interfaces
void
service_interfaces__msg__MomentFeatures__destroy(service_interfaces__msg__MomentFeatures * msg);

/// Check for msg/MomentFeatures message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_service_interfaces
bool
service_interfaces__msg__MomentFeatures__are_equal(const service_interfaces__msg__MomentFeatures * lhs, const service_interfaces__msg__MomentFeatures * rhs);

/// Copy a msg/MomentFeatures message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_service_interfaces
bool
service_interfaces__msg__MomentFeatures__copy(
  const service_interfaces__msg__MomentFeatures * input,
  service_interfaces__msg__MomentFeatures * output);

/// Initialize array of msg/MomentFeatures messages.
/**
 * It allocates the memory for the number of elements and calls
 * service_interfaces__msg__MomentFeatures__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_service_interfaces
bool
service_interfaces__msg__MomentFeatures__Sequence__init(service_interfaces__msg__MomentFeatures__Sequence * array, size_t size);

/// Finalize array of msg/MomentFeatures messages.
/**
 * It calls
 * service_interfaces__msg__MomentFeatures__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_service_interfaces
void
service_interfaces__msg__MomentFeatures__Sequence__fini(service_interfaces__msg__MomentFeatures__Sequence * array);

/// Create array of msg/MomentFeatures messages.
/**
 * It allocates the memory for the array and calls
 * service_interfaces__msg__MomentFeatures__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_service_interfaces
service_interfaces__msg__MomentFeatures__Sequence *
service_interfaces__msg__MomentFeatures__Sequence__create(size_t size);

/// Destroy array of msg/MomentFeatures messages.
/**
 * It calls
 * service_interfaces__msg__MomentFeatures__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_service_interfaces
void
service_interfaces__msg__MomentFeatures__Sequence__destroy(service_interfaces__msg__MomentFeatures__Sequence * array);

/// Check for msg/MomentFeatures message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_service_interfaces
bool
service_interfaces__msg__MomentFeatures__Sequence__are_equal(const service_interfaces__msg__MomentFeatures__Sequence * lhs, const service_interfaces__msg__MomentFeatures__Sequence * rhs);

/// Copy an array of msg/MomentFeatures messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_service_interfaces
bool
service_interfaces__msg__MomentFeatures__Sequence__copy(
  const service_interfaces__msg__MomentFeatures__Sequence * input,
  service_interfaces__msg__MomentFeatures__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // SERVICE_INTERFACES__MSG__DETAIL__MOMENT_FEATURES__FUNCTIONS_H_
