// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from sfuise_msgs:msg/Estimate.idl
// generated code does not contain a copyright notice
#include "sfuise_msgs/msg/detail/estimate__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `spline`
#include "sfuise_msgs/msg/detail/spline__functions.h"
// Member `if_full_window`
#include "std_msgs/msg/detail/bool__functions.h"
// Member `runtime`
#include "std_msgs/msg/detail/float64__functions.h"

bool
sfuise_msgs__msg__Estimate__init(sfuise_msgs__msg__Estimate * msg)
{
  if (!msg) {
    return false;
  }
  // spline
  if (!sfuise_msgs__msg__Spline__init(&msg->spline)) {
    sfuise_msgs__msg__Estimate__fini(msg);
    return false;
  }
  // if_full_window
  if (!std_msgs__msg__Bool__init(&msg->if_full_window)) {
    sfuise_msgs__msg__Estimate__fini(msg);
    return false;
  }
  // runtime
  if (!std_msgs__msg__Float64__init(&msg->runtime)) {
    sfuise_msgs__msg__Estimate__fini(msg);
    return false;
  }
  return true;
}

void
sfuise_msgs__msg__Estimate__fini(sfuise_msgs__msg__Estimate * msg)
{
  if (!msg) {
    return;
  }
  // spline
  sfuise_msgs__msg__Spline__fini(&msg->spline);
  // if_full_window
  std_msgs__msg__Bool__fini(&msg->if_full_window);
  // runtime
  std_msgs__msg__Float64__fini(&msg->runtime);
}

bool
sfuise_msgs__msg__Estimate__are_equal(const sfuise_msgs__msg__Estimate * lhs, const sfuise_msgs__msg__Estimate * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // spline
  if (!sfuise_msgs__msg__Spline__are_equal(
      &(lhs->spline), &(rhs->spline)))
  {
    return false;
  }
  // if_full_window
  if (!std_msgs__msg__Bool__are_equal(
      &(lhs->if_full_window), &(rhs->if_full_window)))
  {
    return false;
  }
  // runtime
  if (!std_msgs__msg__Float64__are_equal(
      &(lhs->runtime), &(rhs->runtime)))
  {
    return false;
  }
  return true;
}

bool
sfuise_msgs__msg__Estimate__copy(
  const sfuise_msgs__msg__Estimate * input,
  sfuise_msgs__msg__Estimate * output)
{
  if (!input || !output) {
    return false;
  }
  // spline
  if (!sfuise_msgs__msg__Spline__copy(
      &(input->spline), &(output->spline)))
  {
    return false;
  }
  // if_full_window
  if (!std_msgs__msg__Bool__copy(
      &(input->if_full_window), &(output->if_full_window)))
  {
    return false;
  }
  // runtime
  if (!std_msgs__msg__Float64__copy(
      &(input->runtime), &(output->runtime)))
  {
    return false;
  }
  return true;
}

sfuise_msgs__msg__Estimate *
sfuise_msgs__msg__Estimate__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sfuise_msgs__msg__Estimate * msg = (sfuise_msgs__msg__Estimate *)allocator.allocate(sizeof(sfuise_msgs__msg__Estimate), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sfuise_msgs__msg__Estimate));
  bool success = sfuise_msgs__msg__Estimate__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sfuise_msgs__msg__Estimate__destroy(sfuise_msgs__msg__Estimate * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sfuise_msgs__msg__Estimate__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sfuise_msgs__msg__Estimate__Sequence__init(sfuise_msgs__msg__Estimate__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sfuise_msgs__msg__Estimate * data = NULL;

  if (size) {
    data = (sfuise_msgs__msg__Estimate *)allocator.zero_allocate(size, sizeof(sfuise_msgs__msg__Estimate), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sfuise_msgs__msg__Estimate__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sfuise_msgs__msg__Estimate__fini(&data[i - 1]);
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
sfuise_msgs__msg__Estimate__Sequence__fini(sfuise_msgs__msg__Estimate__Sequence * array)
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
      sfuise_msgs__msg__Estimate__fini(&array->data[i]);
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

sfuise_msgs__msg__Estimate__Sequence *
sfuise_msgs__msg__Estimate__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sfuise_msgs__msg__Estimate__Sequence * array = (sfuise_msgs__msg__Estimate__Sequence *)allocator.allocate(sizeof(sfuise_msgs__msg__Estimate__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sfuise_msgs__msg__Estimate__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sfuise_msgs__msg__Estimate__Sequence__destroy(sfuise_msgs__msg__Estimate__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sfuise_msgs__msg__Estimate__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sfuise_msgs__msg__Estimate__Sequence__are_equal(const sfuise_msgs__msg__Estimate__Sequence * lhs, const sfuise_msgs__msg__Estimate__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sfuise_msgs__msg__Estimate__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sfuise_msgs__msg__Estimate__Sequence__copy(
  const sfuise_msgs__msg__Estimate__Sequence * input,
  sfuise_msgs__msg__Estimate__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sfuise_msgs__msg__Estimate);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sfuise_msgs__msg__Estimate * data =
      (sfuise_msgs__msg__Estimate *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sfuise_msgs__msg__Estimate__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sfuise_msgs__msg__Estimate__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sfuise_msgs__msg__Estimate__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
