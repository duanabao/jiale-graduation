// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from isas_msgs:msg/RTLSStick.idl
// generated code does not contain a copyright notice
#include "isas_msgs/msg/detail/rtls_stick__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `pos`
// Member `mean`
#include "geometry_msgs/msg/detail/point__functions.h"
// Member `hrp`
#include "geometry_msgs/msg/detail/vector3__functions.h"
// Member `ranges`
#include "isas_msgs/msg/detail/rtls_range__functions.h"

bool
isas_msgs__msg__RTLSStick__init(isas_msgs__msg__RTLSStick * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    isas_msgs__msg__RTLSStick__fini(msg);
    return false;
  }
  // id
  // t
  // pos
  if (!geometry_msgs__msg__Point__init(&msg->pos)) {
    isas_msgs__msg__RTLSStick__fini(msg);
    return false;
  }
  // mean
  if (!geometry_msgs__msg__Point__init(&msg->mean)) {
    isas_msgs__msg__RTLSStick__fini(msg);
    return false;
  }
  // hrp
  if (!geometry_msgs__msg__Vector3__init(&msg->hrp)) {
    isas_msgs__msg__RTLSStick__fini(msg);
    return false;
  }
  // noga
  // nora
  // ranges
  if (!isas_msgs__msg__RTLSRange__Sequence__init(&msg->ranges, 0)) {
    isas_msgs__msg__RTLSStick__fini(msg);
    return false;
  }
  return true;
}

void
isas_msgs__msg__RTLSStick__fini(isas_msgs__msg__RTLSStick * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // id
  // t
  // pos
  geometry_msgs__msg__Point__fini(&msg->pos);
  // mean
  geometry_msgs__msg__Point__fini(&msg->mean);
  // hrp
  geometry_msgs__msg__Vector3__fini(&msg->hrp);
  // noga
  // nora
  // ranges
  isas_msgs__msg__RTLSRange__Sequence__fini(&msg->ranges);
}

bool
isas_msgs__msg__RTLSStick__are_equal(const isas_msgs__msg__RTLSStick * lhs, const isas_msgs__msg__RTLSStick * rhs)
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
  // t
  if (lhs->t != rhs->t) {
    return false;
  }
  // pos
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->pos), &(rhs->pos)))
  {
    return false;
  }
  // mean
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->mean), &(rhs->mean)))
  {
    return false;
  }
  // hrp
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->hrp), &(rhs->hrp)))
  {
    return false;
  }
  // noga
  if (lhs->noga != rhs->noga) {
    return false;
  }
  // nora
  if (lhs->nora != rhs->nora) {
    return false;
  }
  // ranges
  if (!isas_msgs__msg__RTLSRange__Sequence__are_equal(
      &(lhs->ranges), &(rhs->ranges)))
  {
    return false;
  }
  return true;
}

bool
isas_msgs__msg__RTLSStick__copy(
  const isas_msgs__msg__RTLSStick * input,
  isas_msgs__msg__RTLSStick * output)
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
  // t
  output->t = input->t;
  // pos
  if (!geometry_msgs__msg__Point__copy(
      &(input->pos), &(output->pos)))
  {
    return false;
  }
  // mean
  if (!geometry_msgs__msg__Point__copy(
      &(input->mean), &(output->mean)))
  {
    return false;
  }
  // hrp
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->hrp), &(output->hrp)))
  {
    return false;
  }
  // noga
  output->noga = input->noga;
  // nora
  output->nora = input->nora;
  // ranges
  if (!isas_msgs__msg__RTLSRange__Sequence__copy(
      &(input->ranges), &(output->ranges)))
  {
    return false;
  }
  return true;
}

isas_msgs__msg__RTLSStick *
isas_msgs__msg__RTLSStick__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  isas_msgs__msg__RTLSStick * msg = (isas_msgs__msg__RTLSStick *)allocator.allocate(sizeof(isas_msgs__msg__RTLSStick), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(isas_msgs__msg__RTLSStick));
  bool success = isas_msgs__msg__RTLSStick__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
isas_msgs__msg__RTLSStick__destroy(isas_msgs__msg__RTLSStick * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    isas_msgs__msg__RTLSStick__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
isas_msgs__msg__RTLSStick__Sequence__init(isas_msgs__msg__RTLSStick__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  isas_msgs__msg__RTLSStick * data = NULL;

  if (size) {
    data = (isas_msgs__msg__RTLSStick *)allocator.zero_allocate(size, sizeof(isas_msgs__msg__RTLSStick), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = isas_msgs__msg__RTLSStick__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        isas_msgs__msg__RTLSStick__fini(&data[i - 1]);
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
isas_msgs__msg__RTLSStick__Sequence__fini(isas_msgs__msg__RTLSStick__Sequence * array)
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
      isas_msgs__msg__RTLSStick__fini(&array->data[i]);
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

isas_msgs__msg__RTLSStick__Sequence *
isas_msgs__msg__RTLSStick__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  isas_msgs__msg__RTLSStick__Sequence * array = (isas_msgs__msg__RTLSStick__Sequence *)allocator.allocate(sizeof(isas_msgs__msg__RTLSStick__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = isas_msgs__msg__RTLSStick__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
isas_msgs__msg__RTLSStick__Sequence__destroy(isas_msgs__msg__RTLSStick__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    isas_msgs__msg__RTLSStick__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
isas_msgs__msg__RTLSStick__Sequence__are_equal(const isas_msgs__msg__RTLSStick__Sequence * lhs, const isas_msgs__msg__RTLSStick__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!isas_msgs__msg__RTLSStick__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
isas_msgs__msg__RTLSStick__Sequence__copy(
  const isas_msgs__msg__RTLSStick__Sequence * input,
  isas_msgs__msg__RTLSStick__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(isas_msgs__msg__RTLSStick);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    isas_msgs__msg__RTLSStick * data =
      (isas_msgs__msg__RTLSStick *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!isas_msgs__msg__RTLSStick__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          isas_msgs__msg__RTLSStick__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!isas_msgs__msg__RTLSStick__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
