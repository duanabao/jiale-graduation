// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from sfuise_msgs:msg/Offset.idl
// generated code does not contain a copyright notice
#include "sfuise_msgs/msg/detail/offset__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `t_tag_body`
#include "geometry_msgs/msg/detail/point__functions.h"

bool
sfuise_msgs__msg__Offset__init(sfuise_msgs__msg__Offset * msg)
{
  if (!msg) {
    return false;
  }
  // id_tag
  // id_antenna
  // t_tag_body
  if (!geometry_msgs__msg__Point__init(&msg->t_tag_body)) {
    sfuise_msgs__msg__Offset__fini(msg);
    return false;
  }
  return true;
}

void
sfuise_msgs__msg__Offset__fini(sfuise_msgs__msg__Offset * msg)
{
  if (!msg) {
    return;
  }
  // id_tag
  // id_antenna
  // t_tag_body
  geometry_msgs__msg__Point__fini(&msg->t_tag_body);
}

bool
sfuise_msgs__msg__Offset__are_equal(const sfuise_msgs__msg__Offset * lhs, const sfuise_msgs__msg__Offset * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // id_tag
  if (lhs->id_tag != rhs->id_tag) {
    return false;
  }
  // id_antenna
  if (lhs->id_antenna != rhs->id_antenna) {
    return false;
  }
  // t_tag_body
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->t_tag_body), &(rhs->t_tag_body)))
  {
    return false;
  }
  return true;
}

bool
sfuise_msgs__msg__Offset__copy(
  const sfuise_msgs__msg__Offset * input,
  sfuise_msgs__msg__Offset * output)
{
  if (!input || !output) {
    return false;
  }
  // id_tag
  output->id_tag = input->id_tag;
  // id_antenna
  output->id_antenna = input->id_antenna;
  // t_tag_body
  if (!geometry_msgs__msg__Point__copy(
      &(input->t_tag_body), &(output->t_tag_body)))
  {
    return false;
  }
  return true;
}

sfuise_msgs__msg__Offset *
sfuise_msgs__msg__Offset__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sfuise_msgs__msg__Offset * msg = (sfuise_msgs__msg__Offset *)allocator.allocate(sizeof(sfuise_msgs__msg__Offset), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sfuise_msgs__msg__Offset));
  bool success = sfuise_msgs__msg__Offset__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sfuise_msgs__msg__Offset__destroy(sfuise_msgs__msg__Offset * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sfuise_msgs__msg__Offset__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sfuise_msgs__msg__Offset__Sequence__init(sfuise_msgs__msg__Offset__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sfuise_msgs__msg__Offset * data = NULL;

  if (size) {
    data = (sfuise_msgs__msg__Offset *)allocator.zero_allocate(size, sizeof(sfuise_msgs__msg__Offset), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sfuise_msgs__msg__Offset__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sfuise_msgs__msg__Offset__fini(&data[i - 1]);
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
sfuise_msgs__msg__Offset__Sequence__fini(sfuise_msgs__msg__Offset__Sequence * array)
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
      sfuise_msgs__msg__Offset__fini(&array->data[i]);
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

sfuise_msgs__msg__Offset__Sequence *
sfuise_msgs__msg__Offset__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sfuise_msgs__msg__Offset__Sequence * array = (sfuise_msgs__msg__Offset__Sequence *)allocator.allocate(sizeof(sfuise_msgs__msg__Offset__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sfuise_msgs__msg__Offset__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sfuise_msgs__msg__Offset__Sequence__destroy(sfuise_msgs__msg__Offset__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sfuise_msgs__msg__Offset__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sfuise_msgs__msg__Offset__Sequence__are_equal(const sfuise_msgs__msg__Offset__Sequence * lhs, const sfuise_msgs__msg__Offset__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sfuise_msgs__msg__Offset__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sfuise_msgs__msg__Offset__Sequence__copy(
  const sfuise_msgs__msg__Offset__Sequence * input,
  sfuise_msgs__msg__Offset__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sfuise_msgs__msg__Offset);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sfuise_msgs__msg__Offset * data =
      (sfuise_msgs__msg__Offset *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sfuise_msgs__msg__Offset__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sfuise_msgs__msg__Offset__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sfuise_msgs__msg__Offset__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
