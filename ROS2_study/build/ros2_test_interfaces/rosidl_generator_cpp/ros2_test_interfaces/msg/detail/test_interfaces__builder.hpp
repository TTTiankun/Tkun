// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from ros2_test_interfaces:msg/TestInterfaces.idl
// generated code does not contain a copyright notice

#ifndef ROS2_TEST_INTERFACES__MSG__DETAIL__TEST_INTERFACES__BUILDER_HPP_
#define ROS2_TEST_INTERFACES__MSG__DETAIL__TEST_INTERFACES__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "ros2_test_interfaces/msg/detail/test_interfaces__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace ros2_test_interfaces
{

namespace msg
{

namespace builder
{

class Init_TestInterfaces_image
{
public:
  explicit Init_TestInterfaces_image(::ros2_test_interfaces::msg::TestInterfaces & msg)
  : msg_(msg)
  {}
  ::ros2_test_interfaces::msg::TestInterfaces image(::ros2_test_interfaces::msg::TestInterfaces::_image_type arg)
  {
    msg_.image = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ros2_test_interfaces::msg::TestInterfaces msg_;
};

class Init_TestInterfaces_content
{
public:
  Init_TestInterfaces_content()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TestInterfaces_image content(::ros2_test_interfaces::msg::TestInterfaces::_content_type arg)
  {
    msg_.content = std::move(arg);
    return Init_TestInterfaces_image(msg_);
  }

private:
  ::ros2_test_interfaces::msg::TestInterfaces msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::ros2_test_interfaces::msg::TestInterfaces>()
{
  return ros2_test_interfaces::msg::builder::Init_TestInterfaces_content();
}

}  // namespace ros2_test_interfaces

#endif  // ROS2_TEST_INTERFACES__MSG__DETAIL__TEST_INTERFACES__BUILDER_HPP_
