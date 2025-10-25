// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from sfuise_msgs:msg/Knot.idl
// generated code does not contain a copyright notice
#include "sfuise_msgs/msg/detail/knot__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `position`
// Member `bias_acc`
// Member `bias_gyro`
#include "geometry_msgs/msg/detail/point__functions.h"
// Member `orientation`
#include "geometry_msgs/msg/detail/quaternion__functions.h"

bool
sfuise_msgs__msg__Knot__init(sfuise_msgs__msg__Knot * msg)
{
  if (!msg) {
    return false;
  }
  // position
  if (!geometry_msgs__msg__Point__init(&msg->position)) {
    sfuise_msgs__msg__Knot__fini(msg);
    return false;
  }
  // orientation
  if (!geometry_msgs__msg__Quaternion__init(&msg->orientation)) {
    sfuise_msgs__msg__Knot__fini(msg);
    return false;
  }
  // bias_acc
  if (!geometry_msgs__msg__Point__init(&msg->bias_acc)) {
    sfuise_msgs__msg__Knot__fini(msg);
    return false;
  }
  // bias_gyro
  if (!geometry_msgs__msg__Point__init(&msg->bias_gyro)) {
    sfuise_msgs__msg__Knot__fini(msg);
    return false;
  }
  return true;
}

void
sfuise_msgs__msg__Knot__fini(sfuise_msgs__msg__Knot * msg)
{
  if (!msg) {
    return;
  }
  // position
  geometry_msgs__msg__Point__fini(&msg->position);
  // orientation
  geometry_msgs__msg__Quaternion__fini(&msg->orientation);
  // bias_acc
  geometry_msgs__msg__Point__fini(&msg->bias_acc);
  // bias_gyro
  geometry_msgs__msg__Point__fini(&msg->bias_gyro);
}

bool
sfuise_msgs__msg__Knot__are_equal(const sfuise_msgs__msg__Knot * lhs, const sfuise_msgs__msg__Knot * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // position
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->position), &(rhs->position)))
  {
    return false;
  }
  // orientation
  if (!geometry_msgs__msg__Quaternion__are_equal(
      &(lhs->orientation), &(rhs->orientation)))
  {
    return false;
  }
  // bias_acc
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->bias_acc), &(rhs->bias_acc)))
  {
    return false;
  }
  // bias_gyro
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->bias_gyro), &(rhs->bias_gyro)))
  {
    return false;
  }
  return true;
}

bool
sfuise_msgs__msg__Knot__copy(
  const sfuise_msgs__msg__Knot * input,
  sfuise_msgs__msg__Knot * output)
{
  if (!input || !output) {
    return false;
  }
  // position
  if (!geometry_msgs__msg__Point__copy(
      &(input->position), &(output->position)))
  {
    return false;
  }
  // orientation
  if (!geometry_msgs__msg__Quaternion__copy(
      &(input->orientation), &(output->orientation)))
  {
    return false;
  }
  // bias_acc
  if (!geometry_msgs__msg__Point__copy(
      &(input->bias_acc), &(output->bias_acc)))
  {
    return false;
  }
  // bias_gyro
  if (!geometry_msgs__msg__Point__copy(
      &(input->bias_gyro), &(output->bias_gyro)))
  {
    return false;
  }
  return true;
}

sfuise_msgs__msg__Knot *
sfuise_msgs__msg__Knot__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sfuise_msgs__msg__Knot * msg = (sfuise_msgs__msg__Knot *)allocator.allocate(sizeof(sfuise_msgs__msg__Knot), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sfuise_msgs__msg__Knot));
  bool success = sfuise_msgs__msg__Knot__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sfuise_msgs__msg__Knot__destroy(sfuise_msgs__msg__Knot * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sfuise_msgs__msg__Knot__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sfuise_msgs__msg__Knot__Sequence__init(sfuise_msgs__msg__Knot__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sfuise_msgs__msg__Knot * data = NULL;

  if (size) {
    data = (sfuise_msgs__msg__Knot *)allocator.zero_allocate(size, sizeof(sfuise_msgs__msg__Knot), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sfuise_msgs__msg__Knot__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sfuise_msgs__msg__Knot__fini(&data[i - 1]);
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
sfuise_msgs__msg__Knot__Sequence__fini(sfuise_msgs__msg__Knot__Sequence * array)
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
      sfuise_msgs__msg__Knot__fini(&array->data[i]);
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

sfuise_msgs__msg__Knot__Sequence *
sfuise_msgs__msg__Knot__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sfuise_msgs__msg__Knot__Sequence * array = (sfuise_msgs__msg__Knot__Sequence *)allocator.allocate(sizeof(sfuise_msgs__msg__Knot__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sfuise_msgs__msg__Knot__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sfuise_msgs__msg__Knot__Sequence__destroy(sfuise_msgs__msg__Knot__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sfuise_msgs__msg__Knot__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sfuise_msgs__msg__Knot__Sequence__are_equal(const sfuise_msgs__msg__Knot__Sequence * lhs, const sfuise_msgs__msg__Knot__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sfuise_msgs__msg__Knot__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sfuise_msgs__msg__Knot__Sequence__copy(
  const sfuise_msgs__msg__Knot__Sequence * input,
  sfuise_msgs__msg__Knot__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sfuise_msgs__msg__Knot);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sfuise_msgs__msg__Knot * data =
      (sfuise_msgs__msg__Knot *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sfuise_msgs__msg__Knot__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sfuise_msgs__msg__Knot__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sfuise_msgs__msg__Knot__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
