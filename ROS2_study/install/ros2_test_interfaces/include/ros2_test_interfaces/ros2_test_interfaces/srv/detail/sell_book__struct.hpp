// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from ros2_test_interfaces:srv/SellBook.idl
// generated code does not contain a copyright notice

#ifndef ROS2_TEST_INTERFACES__SRV__DETAIL__SELL_BOOK__STRUCT_HPP_
#define ROS2_TEST_INTERFACES__SRV__DETAIL__SELL_BOOK__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__ros2_test_interfaces__srv__SellBook_Request __attribute__((deprecated))
#else
# define DEPRECATED__ros2_test_interfaces__srv__SellBook_Request __declspec(deprecated)
#endif

namespace ros2_test_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SellBook_Request_
{
  using Type = SellBook_Request_<ContainerAllocator>;

  explicit SellBook_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->money = 0ul;
    }
  }

  explicit SellBook_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->money = 0ul;
    }
  }

  // field types and members
  using _money_type =
    uint32_t;
  _money_type money;

  // setters for named parameter idiom
  Type & set__money(
    const uint32_t & _arg)
  {
    this->money = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    ros2_test_interfaces::srv::SellBook_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const ros2_test_interfaces::srv::SellBook_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<ros2_test_interfaces::srv::SellBook_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<ros2_test_interfaces::srv::SellBook_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      ros2_test_interfaces::srv::SellBook_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<ros2_test_interfaces::srv::SellBook_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      ros2_test_interfaces::srv::SellBook_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<ros2_test_interfaces::srv::SellBook_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<ros2_test_interfaces::srv::SellBook_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<ros2_test_interfaces::srv::SellBook_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__ros2_test_interfaces__srv__SellBook_Request
    std::shared_ptr<ros2_test_interfaces::srv::SellBook_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__ros2_test_interfaces__srv__SellBook_Request
    std::shared_ptr<ros2_test_interfaces::srv::SellBook_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SellBook_Request_ & other) const
  {
    if (this->money != other.money) {
      return false;
    }
    return true;
  }
  bool operator!=(const SellBook_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SellBook_Request_

// alias to use template instance with default allocator
using SellBook_Request =
  ros2_test_interfaces::srv::SellBook_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace ros2_test_interfaces


#ifndef _WIN32
# define DEPRECATED__ros2_test_interfaces__srv__SellBook_Response __attribute__((deprecated))
#else
# define DEPRECATED__ros2_test_interfaces__srv__SellBook_Response __declspec(deprecated)
#endif

namespace ros2_test_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SellBook_Response_
{
  using Type = SellBook_Response_<ContainerAllocator>;

  explicit SellBook_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit SellBook_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _novels_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _novels_type novels;

  // setters for named parameter idiom
  Type & set__novels(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->novels = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    ros2_test_interfaces::srv::SellBook_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const ros2_test_interfaces::srv::SellBook_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<ros2_test_interfaces::srv::SellBook_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<ros2_test_interfaces::srv::SellBook_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      ros2_test_interfaces::srv::SellBook_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<ros2_test_interfaces::srv::SellBook_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      ros2_test_interfaces::srv::SellBook_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<ros2_test_interfaces::srv::SellBook_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<ros2_test_interfaces::srv::SellBook_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<ros2_test_interfaces::srv::SellBook_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__ros2_test_interfaces__srv__SellBook_Response
    std::shared_ptr<ros2_test_interfaces::srv::SellBook_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__ros2_test_interfaces__srv__SellBook_Response
    std::shared_ptr<ros2_test_interfaces::srv::SellBook_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SellBook_Response_ & other) const
  {
    if (this->novels != other.novels) {
      return false;
    }
    return true;
  }
  bool operator!=(const SellBook_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SellBook_Response_

// alias to use template instance with default allocator
using SellBook_Response =
  ros2_test_interfaces::srv::SellBook_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace ros2_test_interfaces

namespace ros2_test_interfaces
{

namespace srv
{

struct SellBook
{
  using Request = ros2_test_interfaces::srv::SellBook_Request;
  using Response = ros2_test_interfaces::srv::SellBook_Response;
};

}  // namespace srv

}  // namespace ros2_test_interfaces

#endif  // ROS2_TEST_INTERFACES__SRV__DETAIL__SELL_BOOK__STRUCT_HPP_
