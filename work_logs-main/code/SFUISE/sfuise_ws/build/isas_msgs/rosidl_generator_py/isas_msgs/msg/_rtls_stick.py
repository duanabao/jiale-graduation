# generated from rosidl_generator_py/resource/_idl.py.em
# with input from isas_msgs:msg/RTLSStick.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_RTLSStick(type):
    """Metaclass of message 'RTLSStick'."""

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
            module = import_type_support('isas_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'isas_msgs.msg.RTLSStick')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__rtls_stick
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__rtls_stick
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__rtls_stick
            cls._TYPE_SUPPORT = module.type_support_msg__msg__rtls_stick
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__rtls_stick

            from geometry_msgs.msg import Point
            if Point.__class__._TYPE_SUPPORT is None:
                Point.__class__.__import_type_support__()

            from geometry_msgs.msg import Vector3
            if Vector3.__class__._TYPE_SUPPORT is None:
                Vector3.__class__.__import_type_support__()

            from isas_msgs.msg import RTLSRange
            if RTLSRange.__class__._TYPE_SUPPORT is None:
                RTLSRange.__class__.__import_type_support__()

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class RTLSStick(metaclass=Metaclass_RTLSStick):
    """Message class 'RTLSStick'."""

    __slots__ = [
        '_header',
        '_id',
        '_t',
        '_pos',
        '_mean',
        '_hrp',
        '_noga',
        '_nora',
        '_ranges',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'id': 'uint16',
        't': 'uint32',
        'pos': 'geometry_msgs/Point',
        'mean': 'geometry_msgs/Point',
        'hrp': 'geometry_msgs/Vector3',
        'noga': 'uint8',
        'nora': 'uint8',
        'ranges': 'sequence<isas_msgs/RTLSRange>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['isas_msgs', 'msg'], 'RTLSRange')),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.id = kwargs.get('id', int())
        self.t = kwargs.get('t', int())
        from geometry_msgs.msg import Point
        self.pos = kwargs.get('pos', Point())
        from geometry_msgs.msg import Point
        self.mean = kwargs.get('mean', Point())
        from geometry_msgs.msg import Vector3
        self.hrp = kwargs.get('hrp', Vector3())
        self.noga = kwargs.get('noga', int())
        self.nora = kwargs.get('nora', int())
        self.ranges = kwargs.get('ranges', [])

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
        if self.header != other.header:
            return False
        if self.id != other.id:
            return False
        if self.t != other.t:
            return False
        if self.pos != other.pos:
            return False
        if self.mean != other.mean:
            return False
        if self.hrp != other.hrp:
            return False
        if self.noga != other.noga:
            return False
        if self.nora != other.nora:
            return False
        if self.ranges != other.ranges:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def header(self):
        """Message field 'header'."""
        return self._header

    @header.setter
    def header(self, value):
        if __debug__:
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'header' field must be a sub message of type 'Header'"
        self._header = value

    @builtins.property  # noqa: A003
    def id(self):  # noqa: A003
        """Message field 'id'."""
        return self._id

    @id.setter  # noqa: A003
    def id(self, value):  # noqa: A003
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'id' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'id' field must be an unsigned integer in [0, 65535]"
        self._id = value

    @builtins.property
    def t(self):
        """Message field 't'."""
        return self._t

    @t.setter
    def t(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 't' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 't' field must be an unsigned integer in [0, 4294967295]"
        self._t = value

    @builtins.property
    def pos(self):
        """Message field 'pos'."""
        return self._pos

    @pos.setter
    def pos(self, value):
        if __debug__:
            from geometry_msgs.msg import Point
            assert \
                isinstance(value, Point), \
                "The 'pos' field must be a sub message of type 'Point'"
        self._pos = value

    @builtins.property
    def mean(self):
        """Message field 'mean'."""
        return self._mean

    @mean.setter
    def mean(self, value):
        if __debug__:
            from geometry_msgs.msg import Point
            assert \
                isinstance(value, Point), \
                "The 'mean' field must be a sub message of type 'Point'"
        self._mean = value

    @builtins.property
    def hrp(self):
        """Message field 'hrp'."""
        return self._hrp

    @hrp.setter
    def hrp(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'hrp' field must be a sub message of type 'Vector3'"
        self._hrp = value

    @builtins.property
    def noga(self):
        """Message field 'noga'."""
        return self._noga

    @noga.setter
    def noga(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'noga' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'noga' field must be an unsigned integer in [0, 255]"
        self._noga = value

    @builtins.property
    def nora(self):
        """Message field 'nora'."""
        return self._nora

    @nora.setter
    def nora(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'nora' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'nora' field must be an unsigned integer in [0, 255]"
        self._nora = value

    @builtins.property
    def ranges(self):
        """Message field 'ranges'."""
        return self._ranges

    @ranges.setter
    def ranges(self, value):
        if __debug__:
            from isas_msgs.msg import RTLSRange
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
                 all(isinstance(v, RTLSRange) for v in value) and
                 True), \
                "The 'ranges' field must be a set or sequence and each value of type 'RTLSRange'"
        self._ranges = value
