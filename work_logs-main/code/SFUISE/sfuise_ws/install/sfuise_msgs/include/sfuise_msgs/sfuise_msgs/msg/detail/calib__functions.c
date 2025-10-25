// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from sfuise_msgs:msg/Calib.idl
// generated code does not contain a copyright notice
#include "sfuise_msgs/msg/detail/calib__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `gravity`
// Member `t_nav_uwb`
// Member `t_tag_body_set`
#include "geometry_msgs/msg/detail/point__functions.h"
// Member `q_nav_uwb`
#include "geometry_msgs/msg/detail/quaternion__functions.h"

bool
sfuise_msgs__msg__Calib__init(sfuise_msgs__msg__Calib * msg)
{
  if (!msg) {
    return false;
  }
  // gravity
  if (!geometry_msgs__msg__Point__init(&msg->gravity)) {
    sfuise_msgs__msg__Calib__fini(msg);
    return false;
  }
  // t_nav_uwb
  if (!geometry_msgs__msg__Point__init(&msg->t_nav_uwb)) {
    sfuise_msgs__msg__Calib__fini(msg);
    return false;
  }
  // q_nav_uwb
  if (!geometry_msgs__msg__Quaternion__init(&msg->q_nav_uwb)) {
    sfuise_msgs__msg__Calib__fini(msg);
    return false;
  }
  // t_tag_body_set
  if (!geometry_msgs__msg__Point__init(&msg->t_tag_body_set)) {
    sfuise_msgs__msg__Calib__fini(msg);
    return false;
  }
  return true;
}

void
sfuise_msgs__msg__Calib__fini(sfuise_msgs__msg__Calib * msg)
{
  if (!msg) {
    return;
  }
  // gravity
  geometry_msgs__msg__Point__fini(&msg->gravity);
  // t_nav_uwb
  geometry_msgs__msg__Point__fini(&msg->t_nav_uwb);
  // q_nav_uwb
  geometry_msgs__msg__Quaternion__fini(&msg->q_nav_uwb);
  // t_tag_body_set
  geometry_msgs__msg__Point__fini(&msg->t_tag_body_set);
}

bool
sfuise_msgs__msg__Calib__are_equal(const sfuise_msgs__msg__Calib * lhs, const sfuise_msgs__msg__Calib * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // gravity
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->gravity), &(rhs->gravity)))
  {
    return false;
  }
  // t_nav_uwb
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->t_nav_uwb), &(rhs->t_nav_uwb)))
  {
    return false;
  }
  // q_nav_uwb
  if (!geometry_msgs__msg__Quaternion__are_equal(
      &(lhs->q_nav_uwb), &(rhs->q_nav_uwb)))
  {
    return false;
  }
  // t_tag_body_set
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->t_tag_body_set), &(rhs->t_tag_body_set)))
  {
    return false;
  }
  return true;
}

bool
sfuise_msgs__msg__Calib__copy(
  const sfuise_msgs__msg__Calib * input,
  sfuise_msgs__msg__Calib * output)
{
  if (!input || !output) {
    return false;
  }
  // gravity
  if (!geometry_msgs__msg__Point__copy(
      &(input->gravity), &(output->gravity)))
  {
    return false;
  }
  // t_nav_uwb
  if (!geometry_msgs__msg__Point__copy(
      &(input->t_nav_uwb), &(output->t_nav_uwb)))
  {
    return false;
  }
  // q_nav_uwb
  if (!geometry_msgs__msg__Quaternion__copy(
      &(input->q_nav_uwb), &(output->q_nav_uwb)))
  {
    return false;
  }
  // t_tag_body_set
  if (!geometry_msgs__msg__Point__copy(
      &(input->t_tag_body_set), &(output->t_tag_body_set)))
  {
    return false;
  }
  return true;
}

sfuise_msgs__msg__Calib *
sfuise_msgs__msg__Calib__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sfuise_msgs__msg__Calib * msg = (sfuise_msgs__msg__Calib *)allocator.allocate(sizeof(sfuise_msgs__msg__Calib), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sfuise_msgs__msg__Calib));
  bool success = sfuise_msgs__msg__Calib__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sfuise_msgs__msg__Calib__destroy(sfuise_msgs__msg__Calib * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sfuise_msgs__msg__Calib__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sfuise_msgs__msg__Calib__Sequence__init(sfuise_msgs__msg__Calib__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sfuise_msgs__msg__Calib * data = NULL;

  if (size) {
    data = (sfuise_msgs__msg__Calib *)allocator.zero_allocate(size, sizeof(sfuise_msgs__msg__Calib), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sfuise_msgs__msg__Calib__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sfuise_msgs__msg__Calib__fini(&data[i - 1]);
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
sfuise_msgs__msg__Calib__Sequence__fini(sfuise_msgs__msg__Calib__Sequence * array)
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
      sfuise_msgs__msg__Calib__fini(&array->data[i]);
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

sfuise_msgs__msg__Calib__Sequence *
sfuise_msgs__msg__Calib__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sfuise_msgs__msg__Calib__Sequence * array = (sfuise_msgs__msg__Calib__Sequence *)allocator.allocate(sizeof(sfuise_msgs__msg__Calib__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sfuise_msgs__msg__Calib__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sfuise_msgs__msg__Calib__Sequence__destroy(sfuise_msgs__msg__Calib__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sfuise_msgs__msg__Calib__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sfuise_msgs__msg__Calib__Sequence__are_equal(const sfuise_msgs__msg__Calib__Sequence * lhs, const sfuise_msgs__msg__Calib__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sfuise_msgs__msg__Calib__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sfuise_msgs__msg__Calib__Sequence__copy(
  const sfuise_msgs__msg__Calib__Sequence * input,
  sfuise_msgs__msg__Calib__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sfuise_msgs__msg__Calib);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sfuise_msgs__msg__Calib * data =
      (sfuise_msgs__msg__Calib *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sfuise_msgs__msg__Calib__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sfuise_msgs__msg__Calib__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sfuise_msgs__msg__Calib__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
