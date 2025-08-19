// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from service_interfaces:msg/MomentFeatures.idl
// generated code does not contain a copyright notice

#ifndef SERVICE_INTERFACES__MSG__DETAIL__MOMENT_FEATURES__STRUCT_HPP_
#define SERVICE_INTERFACES__MSG__DETAIL__MOMENT_FEATURES__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__service_interfaces__msg__MomentFeatures __attribute__((deprecated))
#else
# define DEPRECATED__service_interfaces__msg__MomentFeatures __declspec(deprecated)
#endif

namespace service_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MomentFeatures_
{
  using Type = MomentFeatures_<ContainerAllocator>;

  explicit MomentFeatures_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->x_gravity = 0.0;
      this->y_gravity = 0.0;
      this->area = 0.0;
      this->sx = 0.0;
      this->sy = 0.0;
      this->alpha = 0.0;
    }
  }

  explicit MomentFeatures_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->x_gravity = 0.0;
      this->y_gravity = 0.0;
      this->area = 0.0;
      this->sx = 0.0;
      this->sy = 0.0;
      this->alpha = 0.0;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _x_gravity_type =
    double;
  _x_gravity_type x_gravity;
  using _y_gravity_type =
    double;
  _y_gravity_type y_gravity;
  using _area_type =
    double;
  _area_type area;
  using _sx_type =
    double;
  _sx_type sx;
  using _sy_type =
    double;
  _sy_type sy;
  using _alpha_type =
    double;
  _alpha_type alpha;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__x_gravity(
    const double & _arg)
  {
    this->x_gravity = _arg;
    return *this;
  }
  Type & set__y_gravity(
    const double & _arg)
  {
    this->y_gravity = _arg;
    return *this;
  }
  Type & set__area(
    const double & _arg)
  {
    this->area = _arg;
    return *this;
  }
  Type & set__sx(
    const double & _arg)
  {
    this->sx = _arg;
    return *this;
  }
  Type & set__sy(
    const double & _arg)
  {
    this->sy = _arg;
    return *this;
  }
  Type & set__alpha(
    const double & _arg)
  {
    this->alpha = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    service_interfaces::msg::MomentFeatures_<ContainerAllocator> *;
  using ConstRawPtr =
    const service_interfaces::msg::MomentFeatures_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<service_interfaces::msg::MomentFeatures_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<service_interfaces::msg::MomentFeatures_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      service_interfaces::msg::MomentFeatures_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<service_interfaces::msg::MomentFeatures_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      service_interfaces::msg::MomentFeatures_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<service_interfaces::msg::MomentFeatures_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<service_interfaces::msg::MomentFeatures_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<service_interfaces::msg::MomentFeatures_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__service_interfaces__msg__MomentFeatures
    std::shared_ptr<service_interfaces::msg::MomentFeatures_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__service_interfaces__msg__MomentFeatures
    std::shared_ptr<service_interfaces::msg::MomentFeatures_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MomentFeatures_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->x_gravity != other.x_gravity) {
      return false;
    }
    if (this->y_gravity != other.y_gravity) {
      return false;
    }
    if (this->area != other.area) {
      return false;
    }
    if (this->sx != other.sx) {
      return false;
    }
    if (this->sy != other.sy) {
      return false;
    }
    if (this->alpha != other.alpha) {
      return false;
    }
    return true;
  }
  bool operator!=(const MomentFeatures_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MomentFeatures_

// alias to use template instance with default allocator
using MomentFeatures =
  service_interfaces::msg::MomentFeatures_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace service_interfaces

#endif  // SERVICE_INTERFACES__MSG__DETAIL__MOMENT_FEATURES__STRUCT_HPP_
