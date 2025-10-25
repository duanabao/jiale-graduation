// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from isas_msgs:msg/AnchorPosition.idl
// generated code does not contain a copyright notice
#include "isas_msgs/msg/detail/anchor_position__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `position`
#include "geometry_msgs/msg/detail/point__functions.h"

bool
isas_msgs__msg__AnchorPosition__init(isas_msgs__msg__AnchorPosition * msg)
{
  if (!msg) {
    return false;
  }
  // id
  // position
  if (!geometry_msgs__msg__Point__init(&msg->position)) {
    isas_msgs__msg__AnchorPosition__fini(msg);
    return false;
  }
  return true;
}

void
isas_msgs__msg__AnchorPosition__fini(isas_msgs__msg__AnchorPosition * msg)
{
  if (!msg) {
    return;
  }
  // id
  // position
  geometry_msgs__msg__Point__fini(&msg->position);
}

bool
isas_msgs__msg__AnchorPosition__are_equal(const isas_msgs__msg__AnchorPosition * lhs, const isas_msgs__msg__AnchorPosition * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // id
  if (lhs->id != rhs->id) {
    return false;
  }
  // position
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->position), &(rhs->position)))
  {
    return false;
  }
  return true;
}

bool
isas_msgs__msg__AnchorPosition__copy(
  const isas_msgs__msg__AnchorPosition * input,
  isas_msgs__msg__AnchorPosition * output)
{
  if (!input || !output) {
    return false;
  }
  // id
  output->id = input->id;
  // position
  if (!geometry_msgs__msg__Point__copy(
      &(input->position), &(output->position)))
  {
    return false;
  }
  return true;
}

isas_msgs__msg__AnchorPosition *
isas_msgs__msg__AnchorPosition__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  isas_msgs__msg__AnchorPosition * msg = (isas_msgs__msg__AnchorPosition *)allocator.allocate(sizeof(isas_msgs__msg__AnchorPosition), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(isas_msgs__msg__AnchorPosition));
  bool success = isas_msgs__msg__AnchorPosition__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
isas_msgs__msg__AnchorPosition__destroy(isas_msgs__msg__AnchorPosition * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    isas_msgs__msg__AnchorPosition__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
isas_msgs__msg__AnchorPosition__Sequence__init(isas_msgs__msg__AnchorPosition__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  isas_msgs__msg__AnchorPosition * data = NULL;

  if (size) {
    data = (isas_msgs__msg__AnchorPosition *)allocator.zero_allocate(size, sizeof(isas_msgs__msg__AnchorPosition), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = isas_msgs__msg__AnchorPosition__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        isas_msgs__msg__AnchorPosition__fini(&data[i - 1]);
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
isas_msgs__msg__AnchorPosition__Sequence__fini(isas_msgs__msg__AnchorPosition__Sequence * array)
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
      isas_msgs__msg__AnchorPosition__fini(&array->data[i]);
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

isas_msgs__msg__AnchorPosition__Sequence *
isas_msgs__msg__AnchorPosition__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  isas_msgs__msg__AnchorPosition__Sequence * array = (isas_msgs__msg__AnchorPosition__Sequence *)allocator.allocate(sizeof(isas_msgs__msg__AnchorPosition__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = isas_msgs__msg__AnchorPosition__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
isas_msgs__msg__AnchorPosition__Sequence__destroy(isas_msgs__msg__AnchorPosition__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    isas_msgs__msg__AnchorPosition__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
isas_msgs__msg__AnchorPosition__Sequence__are_equal(const isas_msgs__msg__AnchorPosition__Sequence * lhs, const isas_msgs__msg__AnchorPosition__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!isas_msgs__msg__AnchorPosition__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
isas_msgs__msg__AnchorPosition__Sequence__copy(
  const isas_msgs__msg__AnchorPosition__Sequence * input,
  isas_msgs__msg__AnchorPosition__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(isas_msgs__msg__AnchorPosition);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    isas_msgs__msg__AnchorPosition * data =
      (isas_msgs__msg__AnchorPosition *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!isas_msgs__msg__AnchorPosition__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          isas_msgs__msg__AnchorPosition__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!isas_msgs__msg__AnchorPosition__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
