// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from sfuise_msgs:msg/Spline.idl
// generated code does not contain a copyright notice

#ifndef SFUISE_MSGS__MSG__DETAIL__SPLINE__FUNCTIONS_H_
#define SFUISE_MSGS__MSG__DETAIL__SPLINE__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "sfuise_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "sfuise_msgs/msg/detail/spline__struct.h"

/// Initialize msg/Spline message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * sfuise_msgs__msg__Spline
 * )) before or use
 * sfuise_msgs__msg__Spline__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_sfuise_msgs
bool
sfuise_msgs__msg__Spline__init(sfuise_msgs__msg__Spline * msg);

/// Finalize msg/Spline message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_sfuise_msgs
void
sfuise_msgs__msg__Spline__fini(sfuise_msgs__msg__Spline * msg);

/// Create msg/Spline message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * sfuise_msgs__msg__Spline__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_sfuise_msgs
sfuise_msgs__msg__Spline *
sfuise_msgs__msg__Spline__create();

/// Destroy msg/Spline message.
/**
 * It calls
 * sfuise_msgs__msg__Spline__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_sfuise_msgs
void
sfuise_msgs__msg__Spline__destroy(sfuise_msgs__msg__Spline * msg);

/// Check for msg/Spline message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_sfuise_msgs
bool
sfuise_msgs__msg__Spline__are_equal(const sfuise_msgs__msg__Spline * lhs, const sfuise_msgs__msg__Spline * rhs);

/// Copy a msg/Spline message.
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
ROSIDL_GENERATOR_C_PUBLIC_sfuise_msgs
bool
sfuise_msgs__msg__Spline__copy(
  const sfuise_msgs__msg__Spline * input,
  sfuise_msgs__msg__Spline * output);

/// Initialize array of msg/Spline messages.
/**
 * It allocates the memory for the number of elements and calls
 * sfuise_msgs__msg__Spline__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_sfuise_msgs
bool
sfuise_msgs__msg__Spline__Sequence__init(sfuise_msgs__msg__Spline__Sequence * array, size_t size);

/// Finalize array of msg/Spline messages.
/**
 * It calls
 * sfuise_msgs__msg__Spline__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_sfuise_msgs
void
sfuise_msgs__msg__Spline__Sequence__fini(sfuise_msgs__msg__Spline__Sequence * array);

/// Create array of msg/Spline messages.
/**
 * It allocates the memory for the array and calls
 * sfuise_msgs__msg__Spline__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_sfuise_msgs
sfuise_msgs__msg__Spline__Sequence *
sfuise_msgs__msg__Spline__Sequence__create(size_t size);

/// Destroy array of msg/Spline messages.
/**
 * It calls
 * sfuise_msgs__msg__Spline__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_sfuise_msgs
void
sfuise_msgs__msg__Spline__Sequence__destroy(sfuise_msgs__msg__Spline__Sequence * array);

/// Check for msg/Spline message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_sfuise_msgs
bool
sfuise_msgs__msg__Spline__Sequence__are_equal(const sfuise_msgs__msg__Spline__Sequence * lhs, const sfuise_msgs__msg__Spline__Sequence * rhs);

/// Copy an array of msg/Spline messages.
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
ROSIDL_GENERATOR_C_PUBLIC_sfuise_msgs
bool
sfuise_msgs__msg__Spline__Sequence__copy(
  const sfuise_msgs__msg__Spline__Sequence * input,
  sfuise_msgs__msg__Spline__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // SFUISE_MSGS__MSG__DETAIL__SPLINE__FUNCTIONS_H_
