// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from ros2_test_interfaces:srv/TestInterfaces.idl
// generated code does not contain a copyright notice

#ifndef ROS2_TEST_INTERFACES__SRV__DETAIL__TEST_INTERFACES__STRUCT_HPP_
#define ROS2_TEST_INTERFACES__SRV__DETAIL__TEST_INTERFACES__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__ros2_test_interfaces__srv__TestInterfaces_Request __attribute__((deprecated))
#else
# define DEPRECATED__ros2_test_interfaces__srv__TestInterfaces_Request __declspec(deprecated)
#endif

namespace ros2_test_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct TestInterfaces_Request_
{
  using Type = TestInterfaces_Request_<ContainerAllocator>;

  explicit TestInterfaces_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
      this->money = 0ul;
    }
  }

  explicit TestInterfaces_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : name(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
      this->money = 0ul;
    }
  }

  // field types and members
  using _name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _name_type name;
  using _money_type =
    uint32_t;
  _money_type money;

  // setters for named parameter idiom
  Type & set__name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->name = _arg;
    return *this;
  }
  Type & set__money(
    const uint32_t & _arg)
  {
    this->money = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    ros2_test_interfaces::srv::TestInterfaces_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const ros2_test_interfaces::srv::TestInterfaces_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<ros2_test_interfaces::srv::TestInterfaces_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<ros2_test_interfaces::srv::TestInterfaces_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      ros2_test_interfaces::srv::TestInterfaces_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<ros2_test_interfaces::srv::TestInterfaces_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      ros2_test_interfaces::srv::TestInterfaces_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<ros2_test_interfaces::srv::TestInterfaces_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<ros2_test_interfaces::srv::TestInterfaces_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<ros2_test_interfaces::srv::TestInterfaces_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__ros2_test_interfaces__srv__TestInterfaces_Request
    std::shared_ptr<ros2_test_interfaces::srv::TestInterfaces_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__ros2_test_interfaces__srv__TestInterfaces_Request
    std::shared_ptr<ros2_test_interfaces::srv::TestInterfaces_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TestInterfaces_Request_ & other) const
  {
    if (this->name != other.name) {
      return false;
    }
    if (this->money != other.money) {
      return false;
    }
    return true;
  }
  bool operator!=(const TestInterfaces_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TestInterfaces_Request_

// alias to use template instance with default allocator
using TestInterfaces_Request =
  ros2_test_interfaces::srv::TestInterfaces_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace ros2_test_interfaces


#ifndef _WIN32
# define DEPRECATED__ros2_test_interfaces__srv__TestInterfaces_Response __attribute__((deprecated))
#else
# define DEPRECATED__ros2_test_interfaces__srv__TestInterfaces_Response __declspec(deprecated)
#endif

namespace ros2_test_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct TestInterfaces_Response_
{
  using Type = TestInterfaces_Response_<ContainerAllocator>;

  explicit TestInterfaces_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->money = 0ul;
    }
  }

  explicit TestInterfaces_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->money = 0ul;
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _money_type =
    uint32_t;
  _money_type money;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__money(
    const uint32_t & _arg)
  {
    this->money = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    ros2_test_interfaces::srv::TestInterfaces_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const ros2_test_interfaces::srv::TestInterfaces_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<ros2_test_interfaces::srv::TestInterfaces_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<ros2_test_interfaces::srv::TestInterfaces_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      ros2_test_interfaces::srv::TestInterfaces_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<ros2_test_interfaces::srv::TestInterfaces_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      ros2_test_interfaces::srv::TestInterfaces_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<ros2_test_interfaces::srv::TestInterfaces_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<ros2_test_interfaces::srv::TestInterfaces_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<ros2_test_interfaces::srv::TestInterfaces_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__ros2_test_interfaces__srv__TestInterfaces_Response
    std::shared_ptr<ros2_test_interfaces::srv::TestInterfaces_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__ros2_test_interfaces__srv__TestInterfaces_Response
    std::shared_ptr<ros2_test_interfaces::srv::TestInterfaces_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TestInterfaces_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->money != other.money) {
      return false;
    }
    return true;
  }
  bool operator!=(const TestInterfaces_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TestInterfaces_Response_

// alias to use template instance with default allocator
using TestInterfaces_Response =
  ros2_test_interfaces::srv::TestInterfaces_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace ros2_test_interfaces

namespace ros2_test_interfaces
{

namespace srv
{

struct TestInterfaces
{
  using Request = ros2_test_interfaces::srv::TestInterfaces_Request;
  using Response = ros2_test_interfaces::srv::TestInterfaces_Response;
};

}  // namespace srv

}  // namespace ros2_test_interfaces

#endif  // ROS2_TEST_INTERFACES__SRV__DETAIL__TEST_INTERFACES__STRUCT_HPP_
