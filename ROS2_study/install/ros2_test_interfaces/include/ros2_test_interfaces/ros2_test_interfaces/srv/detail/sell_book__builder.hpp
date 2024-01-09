// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from ros2_test_interfaces:srv/SellBook.idl
// generated code does not contain a copyright notice

#ifndef ROS2_TEST_INTERFACES__SRV__DETAIL__SELL_BOOK__BUILDER_HPP_
#define ROS2_TEST_INTERFACES__SRV__DETAIL__SELL_BOOK__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "ros2_test_interfaces/srv/detail/sell_book__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace ros2_test_interfaces
{

namespace srv
{

namespace builder
{

class Init_SellBook_Request_money
{
public:
  Init_SellBook_Request_money()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::ros2_test_interfaces::srv::SellBook_Request money(::ros2_test_interfaces::srv::SellBook_Request::_money_type arg)
  {
    msg_.money = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ros2_test_interfaces::srv::SellBook_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::ros2_test_interfaces::srv::SellBook_Request>()
{
  return ros2_test_interfaces::srv::builder::Init_SellBook_Request_money();
}

}  // namespace ros2_test_interfaces


namespace ros2_test_interfaces
{

namespace srv
{

namespace builder
{

class Init_SellBook_Response_novels
{
public:
  Init_SellBook_Response_novels()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::ros2_test_interfaces::srv::SellBook_Response novels(::ros2_test_interfaces::srv::SellBook_Response::_novels_type arg)
  {
    msg_.novels = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ros2_test_interfaces::srv::SellBook_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::ros2_test_interfaces::srv::SellBook_Response>()
{
  return ros2_test_interfaces::srv::builder::Init_SellBook_Response_novels();
}

}  // namespace ros2_test_interfaces

#endif  // ROS2_TEST_INTERFACES__SRV__DETAIL__SELL_BOOK__BUILDER_HPP_
