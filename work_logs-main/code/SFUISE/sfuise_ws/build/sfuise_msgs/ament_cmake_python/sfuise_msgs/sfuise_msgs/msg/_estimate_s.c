// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from sfuise_msgs:msg/Estimate.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "sfuise_msgs/msg/detail/estimate__struct.h"
#include "sfuise_msgs/msg/detail/estimate__functions.h"

bool sfuise_msgs__msg__spline__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * sfuise_msgs__msg__spline__convert_to_py(void * raw_ros_message);
ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__bool__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__bool__convert_to_py(void * raw_ros_message);
ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__float64__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__float64__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool sfuise_msgs__msg__estimate__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[35];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("sfuise_msgs.msg._estimate.Estimate", full_classname_dest, 34) == 0);
  }
  sfuise_msgs__msg__Estimate * ros_message = _ros_message;
  {  // spline
    PyObject * field = PyObject_GetAttrString(_pymsg, "spline");
    if (!field) {
      return false;
    }
    if (!sfuise_msgs__msg__spline__convert_from_py(field, &ros_message->spline)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // if_full_window
    PyObject * field = PyObject_GetAttrString(_pymsg, "if_full_window");
    if (!field) {
      return false;
    }
    if (!std_msgs__msg__bool__convert_from_py(field, &ros_message->if_full_window)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // runtime
    PyObject * field = PyObject_GetAttrString(_pymsg, "runtime");
    if (!field) {
      return false;
    }
    if (!std_msgs__msg__float64__convert_from_py(field, &ros_message->runtime)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * sfuise_msgs__msg__estimate__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of Estimate */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("sfuise_msgs.msg._estimate");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "Estimate");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  sfuise_msgs__msg__Estimate * ros_message = (sfuise_msgs__msg__Estimate *)raw_ros_message;
  {  // spline
    PyObject * field = NULL;
    field = sfuise_msgs__msg__spline__convert_to_py(&ros_message->spline);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "spline", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // if_full_window
    PyObject * field = NULL;
    field = std_msgs__msg__bool__convert_to_py(&ros_message->if_full_window);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "if_full_window", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // runtime
    PyObject * field = NULL;
    field = std_msgs__msg__float64__convert_to_py(&ros_message->runtime);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "runtime", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
