// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from sfuise_msgs:msg/Spline.idl
// generated code does not contain a copyright notice
#include "sfuise_msgs/msg/detail/spline__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `knots`
// Member `idles`
#include "sfuise_msgs/msg/detail/knot__functions.h"

bool
sfuise_msgs__msg__Spline__init(sfuise_msgs__msg__Spline * msg)
{
  if (!msg) {
    return false;
  }
  // start_idx
  // dt
  // start_t
  // knots
  if (!sfuise_msgs__msg__Knot__Sequence__init(&msg->knots, 0)) {
    sfuise_msgs__msg__Spline__fini(msg);
    return false;
  }
  // idles
  if (!sfuise_msgs__msg__Knot__Sequence__init(&msg->idles, 0)) {
    sfuise_msgs__msg__Spline__fini(msg);
    return false;
  }
  return true;
}

void
sfuise_msgs__msg__Spline__fini(sfuise_msgs__msg__Spline * msg)
{
  if (!msg) {
    return;
  }
  // start_idx
  // dt
  // start_t
  // knots
  sfuise_msgs__msg__Knot__Sequence__fini(&msg->knots);
  // idles
  sfuise_msgs__msg__Knot__Sequence__fini(&msg->idles);
}

bool
sfuise_msgs__msg__Spline__are_equal(const sfuise_msgs__msg__Spline * lhs, const sfuise_msgs__msg__Spline * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // start_idx
  if (lhs->start_idx != rhs->start_idx) {
    return false;
  }
  // dt
  if (lhs->dt != rhs->dt) {
    return false;
  }
  // start_t
  if (lhs->start_t != rhs->start_t) {
    return false;
  }
  // knots
  if (!sfuise_msgs__msg__Knot__Sequence__are_equal(
      &(lhs->knots), &(rhs->knots)))
  {
    return false;
  }
  // idles
  if (!sfuise_msgs__msg__Knot__Sequence__are_equal(
      &(lhs->idles), &(rhs->idles)))
  {
    return false;
  }
  return true;
}

bool
sfuise_msgs__msg__Spline__copy(
  const sfuise_msgs__msg__Spline * input,
  sfuise_msgs__msg__Spline * output)
{
  if (!input || !output) {
    return false;
  }
  // start_idx
  output->start_idx = input->start_idx;
  // dt
  output->dt = input->dt;
  // start_t
  output->start_t = input->start_t;
  // knots
  if (!sfuise_msgs__msg__Knot__Sequence__copy(
      &(input->knots), &(output->knots)))
  {
    return false;
  }
  // idles
  if (!sfuise_msgs__msg__Knot__Sequence__copy(
      &(input->idles), &(output->idles)))
  {
    return false;
  }
  return true;
}

sfuise_msgs__msg__Spline *
sfuise_msgs__msg__Spline__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sfuise_msgs__msg__Spline * msg = (sfuise_msgs__msg__Spline *)allocator.allocate(sizeof(sfuise_msgs__msg__Spline), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sfuise_msgs__msg__Spline));
  bool success = sfuise_msgs__msg__Spline__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sfuise_msgs__msg__Spline__destroy(sfuise_msgs__msg__Spline * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sfuise_msgs__msg__Spline__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sfuise_msgs__msg__Spline__Sequence__init(sfuise_msgs__msg__Spline__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sfuise_msgs__msg__Spline * data = NULL;

  if (size) {
    data = (sfuise_msgs__msg__Spline *)allocator.zero_allocate(size, sizeof(sfuise_msgs__msg__Spline), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sfuise_msgs__msg__Spline__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sfuise_msgs__msg__Spline__fini(&data[i - 1]);
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
sfuise_msgs__msg__Spline__Sequence__fini(sfuise_msgs__msg__Spline__Sequence * array)
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
      sfuise_msgs__msg__Spline__fini(&array->data[i]);
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

sfuise_msgs__msg__Spline__Sequence *
sfuise_msgs__msg__Spline__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sfuise_msgs__msg__Spline__Sequence * array = (sfuise_msgs__msg__Spline__Sequence *)allocator.allocate(sizeof(sfuise_msgs__msg__Spline__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sfuise_msgs__msg__Spline__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sfuise_msgs__msg__Spline__Sequence__destroy(sfuise_msgs__msg__Spline__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sfuise_msgs__msg__Spline__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sfuise_msgs__msg__Spline__Sequence__are_equal(const sfuise_msgs__msg__Spline__Sequence * lhs, const sfuise_msgs__msg__Spline__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sfuise_msgs__msg__Spline__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sfuise_msgs__msg__Spline__Sequence__copy(
  const sfuise_msgs__msg__Spline__Sequence * input,
  sfuise_msgs__msg__Spline__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sfuise_msgs__msg__Spline);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sfuise_msgs__msg__Spline * data =
      (sfuise_msgs__msg__Spline *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sfuise_msgs__msg__Spline__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sfuise_msgs__msg__Spline__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sfuise_msgs__msg__Spline__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
