// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from ros2_test_interfaces:srv/TestInterfaces.idl
// generated code does not contain a copyright notice

#ifndef ROS2_TEST_INTERFACES__SRV__DETAIL__TEST_INTERFACES__BUILDER_HPP_
#define ROS2_TEST_INTERFACES__SRV__DETAIL__TEST_INTERFACES__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "ros2_test_interfaces/srv/detail/test_interfaces__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace ros2_test_interfaces
{

namespace srv
{

namespace builder
{

class Init_TestInterfaces_Request_money
{
public:
  explicit Init_TestInterfaces_Request_money(::ros2_test_interfaces::srv::TestInterfaces_Request & msg)
  : msg_(msg)
  {}
  ::ros2_test_interfaces::srv::TestInterfaces_Request money(::ros2_test_interfaces::srv::TestInterfaces_Request::_money_type arg)
  {
    msg_.money = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ros2_test_interfaces::srv::TestInterfaces_Request msg_;
};

class Init_TestInterfaces_Request_name
{
public:
  Init_TestInterfaces_Request_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TestInterfaces_Request_money name(::ros2_test_interfaces::srv::TestInterfaces_Request::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_TestInterfaces_Request_money(msg_);
  }

private:
  ::ros2_test_interfaces::srv::TestInterfaces_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::ros2_test_interfaces::srv::TestInterfaces_Request>()
{
  return ros2_test_interfaces::srv::builder::Init_TestInterfaces_Request_name();
}

}  // namespace ros2_test_interfaces


namespace ros2_test_interfaces
{

namespace srv
{

namespace builder
{

class Init_TestInterfaces_Response_money
{
public:
  explicit Init_TestInterfaces_Response_money(::ros2_test_interfaces::srv::TestInterfaces_Response & msg)
  : msg_(msg)
  {}
  ::ros2_test_interfaces::srv::TestInterfaces_Response money(::ros2_test_interfaces::srv::TestInterfaces_Response::_money_type arg)
  {
    msg_.money = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ros2_test_interfaces::srv::TestInterfaces_Response msg_;
};

class Init_TestInterfaces_Response_success
{
public:
  Init_TestInterfaces_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TestInterfaces_Response_money success(::ros2_test_interfaces::srv::TestInterfaces_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_TestInterfaces_Response_money(msg_);
  }

private:
  ::ros2_test_interfaces::srv::TestInterfaces_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::ros2_test_interfaces::srv::TestInterfaces_Response>()
{
  return ros2_test_interfaces::srv::builder::Init_TestInterfaces_Response_success();
}

}  // namespace ros2_test_interfaces

#endif  // ROS2_TEST_INTERFACES__SRV__DETAIL__TEST_INTERFACES__BUILDER_HPP_
