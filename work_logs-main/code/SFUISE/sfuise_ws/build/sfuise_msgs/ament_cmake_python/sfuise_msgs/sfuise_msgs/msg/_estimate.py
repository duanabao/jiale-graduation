# generated from rosidl_generator_py/resource/_idl.py.em
# with input from sfuise_msgs:msg/Estimate.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Estimate(type):
    """Metaclass of message 'Estimate'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('sfuise_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'sfuise_msgs.msg.Estimate')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__estimate
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__estimate
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__estimate
            cls._TYPE_SUPPORT = module.type_support_msg__msg__estimate
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__estimate

            from sfuise_msgs.msg import Spline
            if Spline.__class__._TYPE_SUPPORT is None:
                Spline.__class__.__import_type_support__()

            from std_msgs.msg import Bool
            if Bool.__class__._TYPE_SUPPORT is None:
                Bool.__class__.__import_type_support__()

            from std_msgs.msg import Float64
            if Float64.__class__._TYPE_SUPPORT is None:
                Float64.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Estimate(metaclass=Metaclass_Estimate):
    """Message class 'Estimate'."""

    __slots__ = [
        '_spline',
        '_if_full_window',
        '_runtime',
    ]

    _fields_and_field_types = {
        'spline': 'sfuise_msgs/Spline',
        'if_full_window': 'std_msgs/Bool',
        'runtime': 'std_msgs/Float64',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['sfuise_msgs', 'msg'], 'Spline'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Bool'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Float64'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from sfuise_msgs.msg import Spline
        self.spline = kwargs.get('spline', Spline())
        from std_msgs.msg import Bool
        self.if_full_window = kwargs.get('if_full_window', Bool())
        from std_msgs.msg import Float64
        self.runtime = kwargs.get('runtime', Float64())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.spline != other.spline:
            return False
        if self.if_full_window != other.if_full_window:
            return False
        if self.runtime != other.runtime:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def spline(self):
        """Message field 'spline'."""
        return self._spline

    @spline.setter
    def spline(self, value):
        if __debug__:
            from sfuise_msgs.msg import Spline
            assert \
                isinstance(value, Spline), \
                "The 'spline' field must be a sub message of type 'Spline'"
        self._spline = value

    @builtins.property
    def if_full_window(self):
        """Message field 'if_full_window'."""
        return self._if_full_window

    @if_full_window.setter
    def if_full_window(self, value):
        if __debug__:
            from std_msgs.msg import Bool
            assert \
                isinstance(value, Bool), \
                "The 'if_full_window' field must be a sub message of type 'Bool'"
        self._if_full_window = value

    @builtins.property
    def runtime(self):
        """Message field 'runtime'."""
        return self._runtime

    @runtime.setter
    def runtime(self, value):
        if __debug__:
            from std_msgs.msg import Float64
            assert \
                isinstance(value, Float64), \
                "The 'runtime' field must be a sub message of type 'Float64'"
        self._runtime = value
