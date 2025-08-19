// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from service_interfaces:srv/GetJacobian.idl
// generated code does not contain a copyright notice

#ifndef SERVICE_INTERFACES__SRV__DETAIL__GET_JACOBIAN__STRUCT_HPP_
#define SERVICE_INTERFACES__SRV__DETAIL__GET_JACOBIAN__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__service_interfaces__srv__GetJacobian_Request __attribute__((deprecated))
#else
# define DEPRECATED__service_interfaces__srv__GetJacobian_Request __declspec(deprecated)
#endif

namespace service_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetJacobian_Request_
{
  using Type = GetJacobian_Request_<ContainerAllocator>;

  explicit GetJacobian_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<double, 6>::iterator, double>(this->joint_angles.begin(), this->joint_angles.end(), 0.0);
    }
  }

  explicit GetJacobian_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : joint_angles(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<double, 6>::iterator, double>(this->joint_angles.begin(), this->joint_angles.end(), 0.0);
    }
  }

  // field types and members
  using _joint_angles_type =
    std::array<double, 6>;
  _joint_angles_type joint_angles;

  // setters for named parameter idiom
  Type & set__joint_angles(
    const std::array<double, 6> & _arg)
  {
    this->joint_angles = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    service_interfaces::srv::GetJacobian_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const service_interfaces::srv::GetJacobian_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<service_interfaces::srv::GetJacobian_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<service_interfaces::srv::GetJacobian_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      service_interfaces::srv::GetJacobian_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<service_interfaces::srv::GetJacobian_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      service_interfaces::srv::GetJacobian_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<service_interfaces::srv::GetJacobian_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<service_interfaces::srv::GetJacobian_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<service_interfaces::srv::GetJacobian_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__service_interfaces__srv__GetJacobian_Request
    std::shared_ptr<service_interfaces::srv::GetJacobian_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__service_interfaces__srv__GetJacobian_Request
    std::shared_ptr<service_interfaces::srv::GetJacobian_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetJacobian_Request_ & other) const
  {
    if (this->joint_angles != other.joint_angles) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetJacobian_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetJacobian_Request_

// alias to use template instance with default allocator
using GetJacobian_Request =
  service_interfaces::srv::GetJacobian_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace service_interfaces


// Include directives for member types
// Member 'jacobian_matrix'
#include "std_msgs/msg/detail/float64_multi_array__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__service_interfaces__srv__GetJacobian_Response __attribute__((deprecated))
#else
# define DEPRECATED__service_interfaces__srv__GetJacobian_Response __declspec(deprecated)
#endif

namespace service_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetJacobian_Response_
{
  using Type = GetJacobian_Response_<ContainerAllocator>;

  explicit GetJacobian_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : jacobian_matrix(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
    }
  }

  explicit GetJacobian_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : jacobian_matrix(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
    }
  }

  // field types and members
  using _jacobian_matrix_type =
    std_msgs::msg::Float64MultiArray_<ContainerAllocator>;
  _jacobian_matrix_type jacobian_matrix;
  using _success_type =
    bool;
  _success_type success;

  // setters for named parameter idiom
  Type & set__jacobian_matrix(
    const std_msgs::msg::Float64MultiArray_<ContainerAllocator> & _arg)
  {
    this->jacobian_matrix = _arg;
    return *this;
  }
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    service_interfaces::srv::GetJacobian_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const service_interfaces::srv::GetJacobian_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<service_interfaces::srv::GetJacobian_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<service_interfaces::srv::GetJacobian_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      service_interfaces::srv::GetJacobian_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<service_interfaces::srv::GetJacobian_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      service_interfaces::srv::GetJacobian_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<service_interfaces::srv::GetJacobian_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<service_interfaces::srv::GetJacobian_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<service_interfaces::srv::GetJacobian_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__service_interfaces__srv__GetJacobian_Response
    std::shared_ptr<service_interfaces::srv::GetJacobian_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__service_interfaces__srv__GetJacobian_Response
    std::shared_ptr<service_interfaces::srv::GetJacobian_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetJacobian_Response_ & other) const
  {
    if (this->jacobian_matrix != other.jacobian_matrix) {
      return false;
    }
    if (this->success != other.success) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetJacobian_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetJacobian_Response_

// alias to use template instance with default allocator
using GetJacobian_Response =
  service_interfaces::srv::GetJacobian_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace service_interfaces

namespace service_interfaces
{

namespace srv
{

struct GetJacobian
{
  using Request = service_interfaces::srv::GetJacobian_Request;
  using Response = service_interfaces::srv::GetJacobian_Response;
};

}  // namespace srv

}  // namespace service_interfaces

#endif  // SERVICE_INTERFACES__SRV__DETAIL__GET_JACOBIAN__STRUCT_HPP_
