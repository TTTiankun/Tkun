// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from ros2_test_interfaces:srv/TestInterfaces.idl
// generated code does not contain a copyright notice

#ifndef ROS2_TEST_INTERFACES__SRV__DETAIL__TEST_INTERFACES__TRAITS_HPP_
#define ROS2_TEST_INTERFACES__SRV__DETAIL__TEST_INTERFACES__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "ros2_test_interfaces/srv/detail/test_interfaces__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace ros2_test_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const TestInterfaces_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: name
  {
    out << "name: ";
    rosidl_generator_traits::value_to_yaml(msg.name, out);
    out << ", ";
  }

  // member: money
  {
    out << "money: ";
    rosidl_generator_traits::value_to_yaml(msg.money, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const TestInterfaces_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "name: ";
    rosidl_generator_traits::value_to_yaml(msg.name, out);
    out << "\n";
  }

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

inline std::string to_yaml(const TestInterfaces_Request & msg, bool use_flow_style = false)
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
  const ros2_test_interfaces::srv::TestInterfaces_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  ros2_test_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use ros2_test_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const ros2_test_interfaces::srv::TestInterfaces_Request & msg)
{
  return ros2_test_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<ros2_test_interfaces::srv::TestInterfaces_Request>()
{
  return "ros2_test_interfaces::srv::TestInterfaces_Request";
}

template<>
inline const char * name<ros2_test_interfaces::srv::TestInterfaces_Request>()
{
  return "ros2_test_interfaces/srv/TestInterfaces_Request";
}

template<>
struct has_fixed_size<ros2_test_interfaces::srv::TestInterfaces_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<ros2_test_interfaces::srv::TestInterfaces_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<ros2_test_interfaces::srv::TestInterfaces_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace ros2_test_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const TestInterfaces_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: money
  {
    out << "money: ";
    rosidl_generator_traits::value_to_yaml(msg.money, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const TestInterfaces_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }

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

inline std::string to_yaml(const TestInterfaces_Response & msg, bool use_flow_style = false)
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
  const ros2_test_interfaces::srv::TestInterfaces_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  ros2_test_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use ros2_test_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const ros2_test_interfaces::srv::TestInterfaces_Response & msg)
{
  return ros2_test_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<ros2_test_interfaces::srv::TestInterfaces_Response>()
{
  return "ros2_test_interfaces::srv::TestInterfaces_Response";
}

template<>
inline const char * name<ros2_test_interfaces::srv::TestInterfaces_Response>()
{
  return "ros2_test_interfaces/srv/TestInterfaces_Response";
}

template<>
struct has_fixed_size<ros2_test_interfaces::srv::TestInterfaces_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<ros2_test_interfaces::srv::TestInterfaces_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<ros2_test_interfaces::srv::TestInterfaces_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<ros2_test_interfaces::srv::TestInterfaces>()
{
  return "ros2_test_interfaces::srv::TestInterfaces";
}

template<>
inline const char * name<ros2_test_interfaces::srv::TestInterfaces>()
{
  return "ros2_test_interfaces/srv/TestInterfaces";
}

template<>
struct has_fixed_size<ros2_test_interfaces::srv::TestInterfaces>
  : std::integral_constant<
    bool,
    has_fixed_size<ros2_test_interfaces::srv::TestInterfaces_Request>::value &&
    has_fixed_size<ros2_test_interfaces::srv::TestInterfaces_Response>::value
  >
{
};

template<>
struct has_bounded_size<ros2_test_interfaces::srv::TestInterfaces>
  : std::integral_constant<
    bool,
    has_bounded_size<ros2_test_interfaces::srv::TestInterfaces_Request>::value &&
    has_bounded_size<ros2_test_interfaces::srv::TestInterfaces_Response>::value
  >
{
};

template<>
struct is_service<ros2_test_interfaces::srv::TestInterfaces>
  : std::true_type
{
};

template<>
struct is_service_request<ros2_test_interfaces::srv::TestInterfaces_Request>
  : std::true_type
{
};

template<>
struct is_service_response<ros2_test_interfaces::srv::TestInterfaces_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // ROS2_TEST_INTERFACES__SRV__DETAIL__TEST_INTERFACES__TRAITS_HPP_
