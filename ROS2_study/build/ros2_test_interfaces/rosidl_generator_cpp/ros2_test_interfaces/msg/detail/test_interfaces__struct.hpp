// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from ros2_test_interfaces:msg/TestInterfaces.idl
// generated code does not contain a copyright notice

#ifndef ROS2_TEST_INTERFACES__MSG__DETAIL__TEST_INTERFACES__STRUCT_HPP_
#define ROS2_TEST_INTERFACES__MSG__DETAIL__TEST_INTERFACES__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'image'
#include "sensor_msgs/msg/detail/image__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__ros2_test_interfaces__msg__TestInterfaces __attribute__((deprecated))
#else
# define DEPRECATED__ros2_test_interfaces__msg__TestInterfaces __declspec(deprecated)
#endif

namespace ros2_test_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct TestInterfaces_
{
  using Type = TestInterfaces_<ContainerAllocator>;

  explicit TestInterfaces_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : image(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->content = "";
    }
  }

  explicit TestInterfaces_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : content(_alloc),
    image(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->content = "";
    }
  }

  // field types and members
  using _content_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _content_type content;
  using _image_type =
    sensor_msgs::msg::Image_<ContainerAllocator>;
  _image_type image;

  // setters for named parameter idiom
  Type & set__content(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->content = _arg;
    return *this;
  }
  Type & set__image(
    const sensor_msgs::msg::Image_<ContainerAllocator> & _arg)
  {
    this->image = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    ros2_test_interfaces::msg::TestInterfaces_<ContainerAllocator> *;
  using ConstRawPtr =
    const ros2_test_interfaces::msg::TestInterfaces_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<ros2_test_interfaces::msg::TestInterfaces_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<ros2_test_interfaces::msg::TestInterfaces_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      ros2_test_interfaces::msg::TestInterfaces_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<ros2_test_interfaces::msg::TestInterfaces_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      ros2_test_interfaces::msg::TestInterfaces_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<ros2_test_interfaces::msg::TestInterfaces_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<ros2_test_interfaces::msg::TestInterfaces_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<ros2_test_interfaces::msg::TestInterfaces_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__ros2_test_interfaces__msg__TestInterfaces
    std::shared_ptr<ros2_test_interfaces::msg::TestInterfaces_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__ros2_test_interfaces__msg__TestInterfaces
    std::shared_ptr<ros2_test_interfaces::msg::TestInterfaces_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TestInterfaces_ & other) const
  {
    if (this->content != other.content) {
      return false;
    }
    if (this->image != other.image) {
      return false;
    }
    return true;
  }
  bool operator!=(const TestInterfaces_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TestInterfaces_

// alias to use template instance with default allocator
using TestInterfaces =
  ros2_test_interfaces::msg::TestInterfaces_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace ros2_test_interfaces

#endif  // ROS2_TEST_INTERFACES__MSG__DETAIL__TEST_INTERFACES__STRUCT_HPP_
