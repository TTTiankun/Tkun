// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ros2_test_interfaces:srv/SellBook.idl
// generated code does not contain a copyright notice

#ifndef ROS2_TEST_INTERFACES__SRV__DETAIL__SELL_BOOK__STRUCT_H_
#define ROS2_TEST_INTERFACES__SRV__DETAIL__SELL_BOOK__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/SellBook in the package ros2_test_interfaces.
typedef struct ros2_test_interfaces__srv__SellBook_Request
{
  uint32_t money;
} ros2_test_interfaces__srv__SellBook_Request;

// Struct for a sequence of ros2_test_interfaces__srv__SellBook_Request.
typedef struct ros2_test_interfaces__srv__SellBook_Request__Sequence
{
  ros2_test_interfaces__srv__SellBook_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ros2_test_interfaces__srv__SellBook_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'novels'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/SellBook in the package ros2_test_interfaces.
typedef struct ros2_test_interfaces__srv__SellBook_Response
{
  rosidl_runtime_c__String__Sequence novels;
} ros2_test_interfaces__srv__SellBook_Response;

// Struct for a sequence of ros2_test_interfaces__srv__SellBook_Response.
typedef struct ros2_test_interfaces__srv__SellBook_Response__Sequence
{
  ros2_test_interfaces__srv__SellBook_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ros2_test_interfaces__srv__SellBook_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROS2_TEST_INTERFACES__SRV__DETAIL__SELL_BOOK__STRUCT_H_
