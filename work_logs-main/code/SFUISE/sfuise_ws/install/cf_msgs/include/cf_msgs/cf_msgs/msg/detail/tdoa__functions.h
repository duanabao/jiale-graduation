// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from cf_msgs:msg/Tdoa.idl
// generated code does not contain a copyright notice

#ifndef CF_MSGS__MSG__DETAIL__TDOA__FUNCTIONS_H_
#define CF_MSGS__MSG__DETAIL__TDOA__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "cf_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "cf_msgs/msg/detail/tdoa__struct.h"

/// Initialize msg/Tdoa message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * cf_msgs__msg__Tdoa
 * )) before or use
 * cf_msgs__msg__Tdoa__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_cf_msgs
bool
cf_msgs__msg__Tdoa__init(cf_msgs__msg__Tdoa * msg);

/// Finalize msg/Tdoa message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cf_msgs
void
cf_msgs__msg__Tdoa__fini(cf_msgs__msg__Tdoa * msg);

/// Create msg/Tdoa message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * cf_msgs__msg__Tdoa__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cf_msgs
cf_msgs__msg__Tdoa *
cf_msgs__msg__Tdoa__create();

/// Destroy msg/Tdoa message.
/**
 * It calls
 * cf_msgs__msg__Tdoa__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cf_msgs
void
cf_msgs__msg__Tdoa__destroy(cf_msgs__msg__Tdoa * msg);

/// Check for msg/Tdoa message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cf_msgs
bool
cf_msgs__msg__Tdoa__are_equal(const cf_msgs__msg__Tdoa * lhs, const cf_msgs__msg__Tdoa * rhs);

/// Copy a msg/Tdoa message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_cf_msgs
bool
cf_msgs__msg__Tdoa__copy(
  const cf_msgs__msg__Tdoa * input,
  cf_msgs__msg__Tdoa * output);

/// Initialize array of msg/Tdoa messages.
/**
 * It allocates the memory for the number of elements and calls
 * cf_msgs__msg__Tdoa__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_cf_msgs
bool
cf_msgs__msg__Tdoa__Sequence__init(cf_msgs__msg__Tdoa__Sequence * array, size_t size);

/// Finalize array of msg/Tdoa messages.
/**
 * It calls
 * cf_msgs__msg__Tdoa__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cf_msgs
void
cf_msgs__msg__Tdoa__Sequence__fini(cf_msgs__msg__Tdoa__Sequence * array);

/// Create array of msg/Tdoa messages.
/**
 * It allocates the memory for the array and calls
 * cf_msgs__msg__Tdoa__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cf_msgs
cf_msgs__msg__Tdoa__Sequence *
cf_msgs__msg__Tdoa__Sequence__create(size_t size);

/// Destroy array of msg/Tdoa messages.
/**
 * It calls
 * cf_msgs__msg__Tdoa__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cf_msgs
void
cf_msgs__msg__Tdoa__Sequence__destroy(cf_msgs__msg__Tdoa__Sequence * array);

/// Check for msg/Tdoa message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cf_msgs
bool
cf_msgs__msg__Tdoa__Sequence__are_equal(const cf_msgs__msg__Tdoa__Sequence * lhs, const cf_msgs__msg__Tdoa__Sequence * rhs);

/// Copy an array of msg/Tdoa messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_cf_msgs
bool
cf_msgs__msg__Tdoa__Sequence__copy(
  const cf_msgs__msg__Tdoa__Sequence * input,
  cf_msgs__msg__Tdoa__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // CF_MSGS__MSG__DETAIL__TDOA__FUNCTIONS_H_
