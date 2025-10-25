// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from cf_msgs:msg/Twr.idl
// generated code does not contain a copyright notice
#include "cf_msgs/msg/detail/twr__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
cf_msgs__msg__Twr__init(cf_msgs__msg__Twr * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    cf_msgs__msg__Twr__fini(msg);
    return false;
  }
  // id
  // data
  return true;
}

void
cf_msgs__msg__Twr__fini(cf_msgs__msg__Twr * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // id
  // data
}

bool
cf_msgs__msg__Twr__are_equal(const cf_msgs__msg__Twr * lhs, const cf_msgs__msg__Twr * rhs)
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
  // id
  if (lhs->id != rhs->id) {
    return false;
  }
  // data
  if (lhs->data != rhs->data) {
    return false;
  }
  return true;
}

bool
cf_msgs__msg__Twr__copy(
  const cf_msgs__msg__Twr * input,
  cf_msgs__msg__Twr * output)
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
  // id
  output->id = input->id;
  // data
  output->data = input->data;
  return true;
}

cf_msgs__msg__Twr *
cf_msgs__msg__Twr__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cf_msgs__msg__Twr * msg = (cf_msgs__msg__Twr *)allocator.allocate(sizeof(cf_msgs__msg__Twr), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cf_msgs__msg__Twr));
  bool success = cf_msgs__msg__Twr__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cf_msgs__msg__Twr__destroy(cf_msgs__msg__Twr * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cf_msgs__msg__Twr__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cf_msgs__msg__Twr__Sequence__init(cf_msgs__msg__Twr__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cf_msgs__msg__Twr * data = NULL;

  if (size) {
    data = (cf_msgs__msg__Twr *)allocator.zero_allocate(size, sizeof(cf_msgs__msg__Twr), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cf_msgs__msg__Twr__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cf_msgs__msg__Twr__fini(&data[i - 1]);
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
cf_msgs__msg__Twr__Sequence__fini(cf_msgs__msg__Twr__Sequence * array)
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
      cf_msgs__msg__Twr__fini(&array->data[i]);
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

cf_msgs__msg__Twr__Sequence *
cf_msgs__msg__Twr__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cf_msgs__msg__Twr__Sequence * array = (cf_msgs__msg__Twr__Sequence *)allocator.allocate(sizeof(cf_msgs__msg__Twr__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cf_msgs__msg__Twr__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cf_msgs__msg__Twr__Sequence__destroy(cf_msgs__msg__Twr__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cf_msgs__msg__Twr__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cf_msgs__msg__Twr__Sequence__are_equal(const cf_msgs__msg__Twr__Sequence * lhs, const cf_msgs__msg__Twr__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cf_msgs__msg__Twr__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cf_msgs__msg__Twr__Sequence__copy(
  const cf_msgs__msg__Twr__Sequence * input,
  cf_msgs__msg__Twr__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(cf_msgs__msg__Twr);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cf_msgs__msg__Twr * data =
      (cf_msgs__msg__Twr *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cf_msgs__msg__Twr__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cf_msgs__msg__Twr__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cf_msgs__msg__Twr__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
