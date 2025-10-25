# generated from rosidl_generator_py/resource/_idl.py.em
# with input from sfuise_msgs:msg/Spline.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Spline(type):
    """Metaclass of message 'Spline'."""

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
                'sfuise_msgs.msg.Spline')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__spline
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__spline
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__spline
            cls._TYPE_SUPPORT = module.type_support_msg__msg__spline
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__spline

            from sfuise_msgs.msg import Knot
            if Knot.__class__._TYPE_SUPPORT is None:
                Knot.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Spline(metaclass=Metaclass_Spline):
    """Message class 'Spline'."""

    __slots__ = [
        '_start_idx',
        '_dt',
        '_start_t',
        '_knots',
        '_idles',
    ]

    _fields_and_field_types = {
        'start_idx': 'uint64',
        'dt': 'int64',
        'start_t': 'int64',
        'knots': 'sequence<sfuise_msgs/Knot>',
        'idles': 'sequence<sfuise_msgs/Knot>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('int64'),  # noqa: E501
        rosidl_parser.definition.BasicType('int64'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['sfuise_msgs', 'msg'], 'Knot')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['sfuise_msgs', 'msg'], 'Knot')),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.start_idx = kwargs.get('start_idx', int())
        self.dt = kwargs.get('dt', int())
        self.start_t = kwargs.get('start_t', int())
        self.knots = kwargs.get('knots', [])
        self.idles = kwargs.get('idles', [])

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
        if self.start_idx != other.start_idx:
            return False
        if self.dt != other.dt:
            return False
        if self.start_t != other.start_t:
            return False
        if self.knots != other.knots:
            return False
        if self.idles != other.idles:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def start_idx(self):
        """Message field 'start_idx'."""
        return self._start_idx

    @start_idx.setter
    def start_idx(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'start_idx' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'start_idx' field must be an unsigned integer in [0, 18446744073709551615]"
        self._start_idx = value

    @builtins.property
    def dt(self):
        """Message field 'dt'."""
        return self._dt

    @dt.setter
    def dt(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'dt' field must be of type 'int'"
            assert value >= -9223372036854775808 and value < 9223372036854775808, \
                "The 'dt' field must be an integer in [-9223372036854775808, 9223372036854775807]"
        self._dt = value

    @builtins.property
    def start_t(self):
        """Message field 'start_t'."""
        return self._start_t

    @start_t.setter
    def start_t(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'start_t' field must be of type 'int'"
            assert value >= -9223372036854775808 and value < 9223372036854775808, \
                "The 'start_t' field must be an integer in [-9223372036854775808, 9223372036854775807]"
        self._start_t = value

    @builtins.property
    def knots(self):
        """Message field 'knots'."""
        return self._knots

    @knots.setter
    def knots(self, value):
        if __debug__:
            from sfuise_msgs.msg import Knot
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, Knot) for v in value) and
                 True), \
                "The 'knots' field must be a set or sequence and each value of type 'Knot'"
        self._knots = value

    @builtins.property
    def idles(self):
        """Message field 'idles'."""
        return self._idles

    @idles.setter
    def idles(self, value):
        if __debug__:
            from sfuise_msgs.msg import Knot
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, Knot) for v in value) and
                 True), \
                "The 'idles' field must be a set or sequence and each value of type 'Knot'"
        self._idles = value
