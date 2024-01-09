// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from ros2_test_interfaces:srv/SellBook.idl
// generated code does not contain a copyright notice

#ifndef ROS2_TEST_INTERFACES__SRV__DETAIL__SELL_BOOK__TRAITS_HPP_
#define ROS2_TEST_INTERFACES__SRV__DETAIL__SELL_BOOK__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "ros2_test_interfaces/srv/detail/sell_book__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace ros2_test_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const SellBook_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: money
  {
    out << "money: ";
    rosidl_generator_traits::value_to_yaml(msg.money, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SellBook_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: money
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "money: ";
    rosidl_generator_traits::value_to_yaml(msg.money, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SellBook_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace ros2_test_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use ros2_test_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const ros2_test_interfaces::srv::SellBook_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  ros2_test_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use ros2_test_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const ros2_test_interfaces::srv::SellBook_Request & msg)
{
  return ros2_test_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<ros2_test_interfaces::srv::SellBook_Request>()
{
  return "ros2_test_interfaces::srv::SellBook_Request";
}

template<>
inline const char * name<ros2_test_interfaces::srv::SellBook_Request>()
{
  return "ros2_test_interfaces/srv/SellBook_Request";
}

template<>
struct has_fixed_size<ros2_test_interfaces::srv::SellBook_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<ros2_test_interfaces::srv::SellBook_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<ros2_test_interfaces::srv::SellBook_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace ros2_test_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const SellBook_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: novels
  {
    if (msg.novels.size() == 0) {
      out << "novels: []";
    } else {
      out << "novels: [";
      size_t pending_items = msg.novels.size();
      for (auto item : msg.novels) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SellBook_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: novels
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.novels.size() == 0) {
      out << "novels: []\n";
    } else {
      out << "novels:\n";
      for (auto item : msg.novels) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SellBook_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace ros2_test_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use ros2_test_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const ros2_test_interfaces::srv::SellBook_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  ros2_test_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use ros2_test_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const ros2_test_interfaces::srv::SellBook_Response & msg)
{
  return ros2_test_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<ros2_test_interfaces::srv::SellBook_Response>()
{
  return "ros2_test_interfaces::srv::SellBook_Response";
}

template<>
inline const char * name<ros2_test_interfaces::srv::SellBook_Response>()
{
  return "ros2_test_interfaces/srv/SellBook_Response";
}

template<>
struct has_fixed_size<ros2_test_interfaces::srv::SellBook_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<ros2_test_interfaces::srv::SellBook_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<ros2_test_interfaces::srv::SellBook_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<ros2_test_interfaces::srv::SellBook>()
{
  return "ros2_test_interfaces::srv::SellBook";
}

template<>
inline const char * name<ros2_test_interfaces::srv::SellBook>()
{
  return "ros2_test_interfaces/srv/SellBook";
}

template<>
struct has_fixed_size<ros2_test_interfaces::srv::SellBook>
  : std::integral_constant<
    bool,
    has_fixed_size<ros2_test_interfaces::srv::SellBook_Request>::value &&
    has_fixed_size<ros2_test_interfaces::srv::SellBook_Response>::value
  >
{
};

template<>
struct has_bounded_size<ros2_test_interfaces::srv::SellBook>
  : std::integral_constant<
    bool,
    has_bounded_size<ros2_test_interfaces::srv::SellBook_Request>::value &&
    has_bounded_size<ros2_test_interfaces::srv::SellBook_Response>::value
  >
{
};

template<>
struct is_service<ros2_test_interfaces::srv::SellBook>
  : std::true_type
{
};

template<>
struct is_service_request<ros2_test_interfaces::srv::SellBook_Request>
  : std::true_type
{
};

template<>
struct is_service_response<ros2_test_interfaces::srv::SellBook_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // ROS2_TEST_INTERFACES__SRV__DETAIL__SELL_BOOK__TRAITS_HPP_
