// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from cf_msgs:msg/Flow.idl
// generated code does not contain a copyright notice
#include "cf_msgs/msg/detail/flow__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
cf_msgs__msg__Flow__init(cf_msgs__msg__Flow * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    cf_msgs__msg__Flow__fini(msg);
    return false;
  }
  // delta_x
  // delta_y
  return true;
}

void
cf_msgs__msg__Flow__fini(cf_msgs__msg__Flow * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // delta_x
  // delta_y
}

bool
cf_msgs__msg__Flow__are_equal(const cf_msgs__msg__Flow * lhs, const cf_msgs__msg__Flow * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // delta_x
  if (lhs->delta_x != rhs->delta_x) {
    return false;
  }
  // delta_y
  if (lhs->delta_y != rhs->delta_y) {
    return false;
  }
  return true;
}

bool
cf_msgs__msg__Flow__copy(
  const cf_msgs__msg__Flow * input,
  cf_msgs__msg__Flow * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // delta_x
  output->delta_x = input->delta_x;
  // delta_y
  output->delta_y = input->delta_y;
  return true;
}

cf_msgs__msg__Flow *
cf_msgs__msg__Flow__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cf_msgs__msg__Flow * msg = (cf_msgs__msg__Flow *)allocator.allocate(sizeof(cf_msgs__msg__Flow), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cf_msgs__msg__Flow));
  bool success = cf_msgs__msg__Flow__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cf_msgs__msg__Flow__destroy(cf_msgs__msg__Flow * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cf_msgs__msg__Flow__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cf_msgs__msg__Flow__Sequence__init(cf_msgs__msg__Flow__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cf_msgs__msg__Flow * data = NULL;

  if (size) {
    data = (cf_msgs__msg__Flow *)allocator.zero_allocate(size, sizeof(cf_msgs__msg__Flow), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cf_msgs__msg__Flow__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cf_msgs__msg__Flow__fini(&data[i - 1]);
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
cf_msgs__msg__Flow__Sequence__fini(cf_msgs__msg__Flow__Sequence * array)
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
      cf_msgs__msg__Flow__fini(&array->data[i]);
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

cf_msgs__msg__Flow__Sequence *
cf_msgs__msg__Flow__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cf_msgs__msg__Flow__Sequence * array = (cf_msgs__msg__Flow__Sequence *)allocator.allocate(sizeof(cf_msgs__msg__Flow__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cf_msgs__msg__Flow__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cf_msgs__msg__Flow__Sequence__destroy(cf_msgs__msg__Flow__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cf_msgs__msg__Flow__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cf_msgs__msg__Flow__Sequence__are_equal(const cf_msgs__msg__Flow__Sequence * lhs, const cf_msgs__msg__Flow__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cf_msgs__msg__Flow__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cf_msgs__msg__Flow__Sequence__copy(
  const cf_msgs__msg__Flow__Sequence * input,
  cf_msgs__msg__Flow__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(cf_msgs__msg__Flow);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cf_msgs__msg__Flow * data =
      (cf_msgs__msg__Flow *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cf_msgs__msg__Flow__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cf_msgs__msg__Flow__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cf_msgs__msg__Flow__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
