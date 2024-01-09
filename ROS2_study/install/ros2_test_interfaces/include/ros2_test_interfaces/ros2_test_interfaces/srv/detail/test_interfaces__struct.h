// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ros2_test_interfaces:srv/TestInterfaces.idl
// generated code does not contain a copyright notice

#ifndef ROS2_TEST_INTERFACES__SRV__DETAIL__TEST_INTERFACES__STRUCT_H_
#define ROS2_TEST_INTERFACES__SRV__DETAIL__TEST_INTERFACES__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'name'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/TestInterfaces in the package ros2_test_interfaces.
typedef struct ros2_test_interfaces__srv__TestInterfaces_Request
{
  rosidl_runtime_c__String name;
  uint32_t money;
} ros2_test_interfaces__srv__TestInterfaces_Request;

// Struct for a sequence of ros2_test_interfaces__srv__TestInterfaces_Request.
typedef struct ros2_test_interfaces__srv__TestInterfaces_Request__Sequence
{
  ros2_test_interfaces__srv__TestInterfaces_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ros2_test_interfaces__srv__TestInterfaces_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/TestInterfaces in the package ros2_test_interfaces.
typedef struct ros2_test_interfaces__srv__TestInterfaces_Response
{
  bool success;
  uint32_t money;
} ros2_test_interfaces__srv__TestInterfaces_Response;

// Struct for a sequence of ros2_test_interfaces__srv__TestInterfaces_Response.
typedef struct ros2_test_interfaces__srv__TestInterfaces_Response__Sequence
{
  ros2_test_interfaces__srv__TestInterfaces_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ros2_test_interfaces__srv__TestInterfaces_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROS2_TEST_INTERFACES__SRV__DETAIL__TEST_INTERFACES__STRUCT_H_
