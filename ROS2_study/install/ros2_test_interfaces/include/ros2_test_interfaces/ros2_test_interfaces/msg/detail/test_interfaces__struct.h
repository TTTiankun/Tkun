// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ros2_test_interfaces:msg/TestInterfaces.idl
// generated code does not contain a copyright notice

#ifndef ROS2_TEST_INTERFACES__MSG__DETAIL__TEST_INTERFACES__STRUCT_H_
#define ROS2_TEST_INTERFACES__MSG__DETAIL__TEST_INTERFACES__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'content'
#include "rosidl_runtime_c/string.h"
// Member 'image'
#include "sensor_msgs/msg/detail/image__struct.h"

/// Struct defined in msg/TestInterfaces in the package ros2_test_interfaces.
/**
  * 标准消息接口std_msgs下的string类型
  * std_msgs/String content 其中一种写法
 */
typedef struct ros2_test_interfaces__msg__TestInterfaces
{
  /// 调用原始的数据类型
  rosidl_runtime_c__String content;
  /// 调用已有的数据类型
  /// 图像消息，调用sensor_msgs下的Image类型
  sensor_msgs__msg__Image image;
} ros2_test_interfaces__msg__TestInterfaces;

// Struct for a sequence of ros2_test_interfaces__msg__TestInterfaces.
typedef struct ros2_test_interfaces__msg__TestInterfaces__Sequence
{
  ros2_test_interfaces__msg__TestInterfaces * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ros2_test_interfaces__msg__TestInterfaces__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROS2_TEST_INTERFACES__MSG__DETAIL__TEST_INTERFACES__STRUCT_H_
