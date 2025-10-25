// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from isas_msgs:msg/RTLSRange.idl
// generated code does not contain a copyright notice
#include "isas_msgs/msg/detail/rtls_range__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `pos`
#include "geometry_msgs/msg/detail/point__functions.h"

bool
isas_msgs__msg__RTLSRange__init(isas_msgs__msg__RTLSRange * msg)
{
  if (!msg) {
    return false;
  }
  // id
  // pos
  if (!geometry_msgs__msg__Point__init(&msg->pos)) {
    isas_msgs__msg__RTLSRange__fini(msg);
    return false;
  }
  // pr
  // range
  // mean
  // var
  // fpp
  // rxp
  // csn
  // cmn
  // toc
  // ra
  return true;
}

void
isas_msgs__msg__RTLSRange__fini(isas_msgs__msg__RTLSRange * msg)
{
  if (!msg) {
    return;
  }
  // id
  // pos
  geometry_msgs__msg__Point__fini(&msg->pos);
  // pr
  // range
  // mean
  // var
  // fpp
  // rxp
  // csn
  // cmn
  // toc
  // ra
}

bool
isas_msgs__msg__RTLSRange__are_equal(const isas_msgs__msg__RTLSRange * lhs, const isas_msgs__msg__RTLSRange * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // id
  if (lhs->id != rhs->id) {
    return false;
  }
  // pos
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->pos), &(rhs->pos)))
  {
    return false;
  }
  // pr
  if (lhs->pr != rhs->pr) {
    return false;
  }
  // range
  if (lhs->range != rhs->range) {
    return false;
  }
  // mean
  if (lhs->mean != rhs->mean) {
    return false;
  }
  // var
  if (lhs->var != rhs->var) {
    return false;
  }
  // fpp
  if (lhs->fpp != rhs->fpp) {
    return false;
  }
  // rxp
  if (lhs->rxp != rhs->rxp) {
    return false;
  }
  // csn
  if (lhs->csn != rhs->csn) {
    return false;
  }
  // cmn
  if (lhs->cmn != rhs->cmn) {
    return false;
  }
  // toc
  if (lhs->toc != rhs->toc) {
    return false;
  }
  // ra
  if (lhs->ra != rhs->ra) {
    return false;
  }
  return true;
}

bool
isas_msgs__msg__RTLSRange__copy(
  const isas_msgs__msg__RTLSRange * input,
  isas_msgs__msg__RTLSRange * output)
{
  if (!input || !output) {
    return false;
  }
  // id
  output->id = input->id;
  // pos
  if (!geometry_msgs__msg__Point__copy(
      &(input->pos), &(output->pos)))
  {
    return false;
  }
  // pr
  output->pr = input->pr;
  // range
  output->range = input->range;
  // mean
  output->mean = input->mean;
  // var
  output->var = input->var;
  // fpp
  output->fpp = input->fpp;
  // rxp
  output->rxp = input->rxp;
  // csn
  output->csn = input->csn;
  // cmn
  output->cmn = input->cmn;
  // toc
  output->toc = input->toc;
  // ra
  output->ra = input->ra;
  return true;
}

isas_msgs__msg__RTLSRange *
isas_msgs__msg__RTLSRange__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  isas_msgs__msg__RTLSRange * msg = (isas_msgs__msg__RTLSRange *)allocator.allocate(sizeof(isas_msgs__msg__RTLSRange), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(isas_msgs__msg__RTLSRange));
  bool success = isas_msgs__msg__RTLSRange__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
isas_msgs__msg__RTLSRange__destroy(isas_msgs__msg__RTLSRange * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    isas_msgs__msg__RTLSRange__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
isas_msgs__msg__RTLSRange__Sequence__init(isas_msgs__msg__RTLSRange__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  isas_msgs__msg__RTLSRange * data = NULL;

  if (size) {
    data = (isas_msgs__msg__RTLSRange *)allocator.zero_allocate(size, sizeof(isas_msgs__msg__RTLSRange), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = isas_msgs__msg__RTLSRange__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        isas_msgs__msg__RTLSRange__fini(&data[i - 1]);
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
isas_msgs__msg__RTLSRange__Sequence__fini(isas_msgs__msg__RTLSRange__Sequence * array)
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
      isas_msgs__msg__RTLSRange__fini(&array->data[i]);
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

isas_msgs__msg__RTLSRange__Sequence *
isas_msgs__msg__RTLSRange__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  isas_msgs__msg__RTLSRange__Sequence * array = (isas_msgs__msg__RTLSRange__Sequence *)allocator.allocate(sizeof(isas_msgs__msg__RTLSRange__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = isas_msgs__msg__RTLSRange__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
isas_msgs__msg__RTLSRange__Sequence__destroy(isas_msgs__msg__RTLSRange__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    isas_msgs__msg__RTLSRange__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
isas_msgs__msg__RTLSRange__Sequence__are_equal(const isas_msgs__msg__RTLSRange__Sequence * lhs, const isas_msgs__msg__RTLSRange__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!isas_msgs__msg__RTLSRange__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
isas_msgs__msg__RTLSRange__Sequence__copy(
  const isas_msgs__msg__RTLSRange__Sequence * input,
  isas_msgs__msg__RTLSRange__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(isas_msgs__msg__RTLSRange);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    isas_msgs__msg__RTLSRange * data =
      (isas_msgs__msg__RTLSRange *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!isas_msgs__msg__RTLSRange__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          isas_msgs__msg__RTLSRange__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!isas_msgs__msg__RTLSRange__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
