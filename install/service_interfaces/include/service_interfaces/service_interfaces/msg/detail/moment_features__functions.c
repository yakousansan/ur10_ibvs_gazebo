// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from service_interfaces:msg/MomentFeatures.idl
// generated code does not contain a copyright notice
#include "service_interfaces/msg/detail/moment_features__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
service_interfaces__msg__MomentFeatures__init(service_interfaces__msg__MomentFeatures * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    service_interfaces__msg__MomentFeatures__fini(msg);
    return false;
  }
  // x_gravity
  // y_gravity
  // area
  // sx
  // sy
  // alpha
  return true;
}

void
service_interfaces__msg__MomentFeatures__fini(service_interfaces__msg__MomentFeatures * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // x_gravity
  // y_gravity
  // area
  // sx
  // sy
  // alpha
}

bool
service_interfaces__msg__MomentFeatures__are_equal(const service_interfaces__msg__MomentFeatures * lhs, const service_interfaces__msg__MomentFeatures * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // x_gravity
  if (lhs->x_gravity != rhs->x_gravity) {
    return false;
  }
  // y_gravity
  if (lhs->y_gravity != rhs->y_gravity) {
    return false;
  }
  // area
  if (lhs->area != rhs->area) {
    return false;
  }
  // sx
  if (lhs->sx != rhs->sx) {
    return false;
  }
  // sy
  if (lhs->sy != rhs->sy) {
    return false;
  }
  // alpha
  if (lhs->alpha != rhs->alpha) {
    return false;
  }
  return true;
}

bool
service_interfaces__msg__MomentFeatures__copy(
  const service_interfaces__msg__MomentFeatures * input,
  service_interfaces__msg__MomentFeatures * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // x_gravity
  output->x_gravity = input->x_gravity;
  // y_gravity
  output->y_gravity = input->y_gravity;
  // area
  output->area = input->area;
  // sx
  output->sx = input->sx;
  // sy
  output->sy = input->sy;
  // alpha
  output->alpha = input->alpha;
  return true;
}

service_interfaces__msg__MomentFeatures *
service_interfaces__msg__MomentFeatures__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  service_interfaces__msg__MomentFeatures * msg = (service_interfaces__msg__MomentFeatures *)allocator.allocate(sizeof(service_interfaces__msg__MomentFeatures), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(service_interfaces__msg__MomentFeatures));
  bool success = service_interfaces__msg__MomentFeatures__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
service_interfaces__msg__MomentFeatures__destroy(service_interfaces__msg__MomentFeatures * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    service_interfaces__msg__MomentFeatures__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
service_interfaces__msg__MomentFeatures__Sequence__init(service_interfaces__msg__MomentFeatures__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  service_interfaces__msg__MomentFeatures * data = NULL;

  if (size) {
    data = (service_interfaces__msg__MomentFeatures *)allocator.zero_allocate(size, sizeof(service_interfaces__msg__MomentFeatures), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = service_interfaces__msg__MomentFeatures__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        service_interfaces__msg__MomentFeatures__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
service_interfaces__msg__MomentFeatures__Sequence__fini(service_interfaces__msg__MomentFeatures__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      service_interfaces__msg__MomentFeatures__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

service_interfaces__msg__MomentFeatures__Sequence *
service_interfaces__msg__MomentFeatures__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  service_interfaces__msg__MomentFeatures__Sequence * array = (service_interfaces__msg__MomentFeatures__Sequence *)allocator.allocate(sizeof(service_interfaces__msg__MomentFeatures__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = service_interfaces__msg__MomentFeatures__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
service_interfaces__msg__MomentFeatures__Sequence__destroy(service_interfaces__msg__MomentFeatures__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    service_interfaces__msg__MomentFeatures__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
service_interfaces__msg__MomentFeatures__Sequence__are_equal(const service_interfaces__msg__MomentFeatures__Sequence * lhs, const service_interfaces__msg__MomentFeatures__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!service_interfaces__msg__MomentFeatures__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
service_interfaces__msg__MomentFeatures__Sequence__copy(
  const service_interfaces__msg__MomentFeatures__Sequence * input,
  service_interfaces__msg__MomentFeatures__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(service_interfaces__msg__MomentFeatures);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    service_interfaces__msg__MomentFeatures * data =
      (service_interfaces__msg__MomentFeatures *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!service_interfaces__msg__MomentFeatures__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          service_interfaces__msg__MomentFeatures__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!service_interfaces__msg__MomentFeatures__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
