// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from ros2_test_interfaces:msg/TestInterfaces.idl
// generated code does not contain a copyright notice

#ifndef ROS2_TEST_INTERFACES__MSG__DETAIL__TEST_INTERFACES__FUNCTIONS_H_
#define ROS2_TEST_INTERFACES__MSG__DETAIL__TEST_INTERFACES__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "ros2_test_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "ros2_test_interfaces/msg/detail/test_interfaces__struct.h"

/// Initialize msg/TestInterfaces message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * ros2_test_interfaces__msg__TestInterfaces
 * )) before or use
 * ros2_test_interfaces__msg__TestInterfaces__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_ros2_test_interfaces
bool
ros2_test_interfaces__msg__TestInterfaces__init(ros2_test_interfaces__msg__TestInterfaces * msg);

/// Finalize msg/TestInterfaces message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ros2_test_interfaces
void
ros2_test_interfaces__msg__TestInterfaces__fini(ros2_test_interfaces__msg__TestInterfaces * msg);

/// Create msg/TestInterfaces message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * ros2_test_interfaces__msg__TestInterfaces__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ros2_test_interfaces
ros2_test_interfaces__msg__TestInterfaces *
ros2_test_interfaces__msg__TestInterfaces__create();

/// Destroy msg/TestInterfaces message.
/**
 * It calls
 * ros2_test_interfaces__msg__TestInterfaces__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ros2_test_interfaces
void
ros2_test_interfaces__msg__TestInterfaces__destroy(ros2_test_interfaces__msg__TestInterfaces * msg);

/// Check for msg/TestInterfaces message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_ros2_test_interfaces
bool
ros2_test_interfaces__msg__TestInterfaces__are_equal(const ros2_test_interfaces__msg__TestInterfaces * lhs, const ros2_test_interfaces__msg__TestInterfaces * rhs);

/// Copy a msg/TestInterfaces message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_ros2_test_interfaces
bool
ros2_test_interfaces__msg__TestInterfaces__copy(
  const ros2_test_interfaces__msg__TestInterfaces * input,
  ros2_test_interfaces__msg__TestInterfaces * output);

/// Initialize array of msg/TestInterfaces messages.
/**
 * It allocates the memory for the number of elements and calls
 * ros2_test_interfaces__msg__TestInterfaces__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_ros2_test_interfaces
bool
ros2_test_interfaces__msg__TestInterfaces__Sequence__init(ros2_test_interfaces__msg__TestInterfaces__Sequence * array, size_t size);

/// Finalize array of msg/TestInterfaces messages.
/**
 * It calls
 * ros2_test_interfaces__msg__TestInterfaces__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ros2_test_interfaces
void
ros2_test_interfaces__msg__TestInterfaces__Sequence__fini(ros2_test_interfaces__msg__TestInterfaces__Sequence * array);

/// Create array of msg/TestInterfaces messages.
/**
 * It allocates the memory for the array and calls
 * ros2_test_interfaces__msg__TestInterfaces__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ros2_test_interfaces
ros2_test_interfaces__msg__TestInterfaces__Sequence *
ros2_test_interfaces__msg__TestInterfaces__Sequence__create(size_t size);

/// Destroy array of msg/TestInterfaces messages.
/**
 * It calls
 * ros2_test_interfaces__msg__TestInterfaces__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ros2_test_interfaces
void
ros2_test_interfaces__msg__TestInterfaces__Sequence__destroy(ros2_test_interfaces__msg__TestInterfaces__Sequence * array);

/// Check for msg/TestInterfaces message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_ros2_test_interfaces
bool
ros2_test_interfaces__msg__TestInterfaces__Sequence__are_equal(const ros2_test_interfaces__msg__TestInterfaces__Sequence * lhs, const ros2_test_interfaces__msg__TestInterfaces__Sequence * rhs);

/// Copy an array of msg/TestInterfaces messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_ros2_test_interfaces
bool
ros2_test_interfaces__msg__TestInterfaces__Sequence__copy(
  const ros2_test_interfaces__msg__TestInterfaces__Sequence * input,
  ros2_test_interfaces__msg__TestInterfaces__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // ROS2_TEST_INTERFACES__MSG__DETAIL__TEST_INTERFACES__FUNCTIONS_H_
