// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from ros2_test_interfaces:msg/TestInterfaces.idl
// generated code does not contain a copyright notice
#include "ros2_test_interfaces/msg/detail/test_interfaces__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `content`
#include "rosidl_runtime_c/string_functions.h"
// Member `image`
#include "sensor_msgs/msg/detail/image__functions.h"

bool
ros2_test_interfaces__msg__TestInterfaces__init(ros2_test_interfaces__msg__TestInterfaces * msg)
{
  if (!msg) {
    return false;
  }
  // content
  if (!rosidl_runtime_c__String__init(&msg->content)) {
    ros2_test_interfaces__msg__TestInterfaces__fini(msg);
    return false;
  }
  // image
  if (!sensor_msgs__msg__Image__init(&msg->image)) {
    ros2_test_interfaces__msg__TestInterfaces__fini(msg);
    return false;
  }
  return true;
}

void
ros2_test_interfaces__msg__TestInterfaces__fini(ros2_test_interfaces__msg__TestInterfaces * msg)
{
  if (!msg) {
    return;
  }
  // content
  rosidl_runtime_c__String__fini(&msg->content);
  // image
  sensor_msgs__msg__Image__fini(&msg->image);
}

bool
ros2_test_interfaces__msg__TestInterfaces__are_equal(const ros2_test_interfaces__msg__TestInterfaces * lhs, const ros2_test_interfaces__msg__TestInterfaces * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // content
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->content), &(rhs->content)))
  {
    return false;
  }
  // image
  if (!sensor_msgs__msg__Image__are_equal(
      &(lhs->image), &(rhs->image)))
  {
    return false;
  }
  return true;
}

bool
ros2_test_interfaces__msg__TestInterfaces__copy(
  const ros2_test_interfaces__msg__TestInterfaces * input,
  ros2_test_interfaces__msg__TestInterfaces * output)
{
  if (!input || !output) {
    return false;
  }
  // content
  if (!rosidl_runtime_c__String__copy(
      &(input->content), &(output->content)))
  {
    return false;
  }
  // image
  if (!sensor_msgs__msg__Image__copy(
      &(input->image), &(output->image)))
  {
    return false;
  }
  return true;
}

ros2_test_interfaces__msg__TestInterfaces *
ros2_test_interfaces__msg__TestInterfaces__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ros2_test_interfaces__msg__TestInterfaces * msg = (ros2_test_interfaces__msg__TestInterfaces *)allocator.allocate(sizeof(ros2_test_interfaces__msg__TestInterfaces), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(ros2_test_interfaces__msg__TestInterfaces));
  bool success = ros2_test_interfaces__msg__TestInterfaces__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
ros2_test_interfaces__msg__TestInterfaces__destroy(ros2_test_interfaces__msg__TestInterfaces * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    ros2_test_interfaces__msg__TestInterfaces__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
ros2_test_interfaces__msg__TestInterfaces__Sequence__init(ros2_test_interfaces__msg__TestInterfaces__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ros2_test_interfaces__msg__TestInterfaces * data = NULL;

  if (size) {
    data = (ros2_test_interfaces__msg__TestInterfaces *)allocator.zero_allocate(size, sizeof(ros2_test_interfaces__msg__TestInterfaces), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = ros2_test_interfaces__msg__TestInterfaces__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        ros2_test_interfaces__msg__TestInterfaces__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
ros2_test_interfaces__msg__TestInterfaces__Sequence__fini(ros2_test_interfaces__msg__TestInterfaces__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      ros2_test_interfaces__msg__TestInterfaces__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

ros2_test_interfaces__msg__TestInterfaces__Sequence *
ros2_test_interfaces__msg__TestInterfaces__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ros2_test_interfaces__msg__TestInterfaces__Sequence * array = (ros2_test_interfaces__msg__TestInterfaces__Sequence *)allocator.allocate(sizeof(ros2_test_interfaces__msg__TestInterfaces__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = ros2_test_interfaces__msg__TestInterfaces__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
ros2_test_interfaces__msg__TestInterfaces__Sequence__destroy(ros2_test_interfaces__msg__TestInterfaces__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    ros2_test_interfaces__msg__TestInterfaces__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
ros2_test_interfaces__msg__TestInterfaces__Sequence__are_equal(const ros2_test_interfaces__msg__TestInterfaces__Sequence * lhs, const ros2_test_interfaces__msg__TestInterfaces__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!ros2_test_interfaces__msg__TestInterfaces__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
ros2_test_interfaces__msg__TestInterfaces__Sequence__copy(
  const ros2_test_interfaces__msg__TestInterfaces__Sequence * input,
  ros2_test_interfaces__msg__TestInterfaces__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(ros2_test_interfaces__msg__TestInterfaces);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    ros2_test_interfaces__msg__TestInterfaces * data =
      (ros2_test_interfaces__msg__TestInterfaces *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!ros2_test_interfaces__msg__TestInterfaces__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          ros2_test_interfaces__msg__TestInterfaces__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!ros2_test_interfaces__msg__TestInterfaces__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
