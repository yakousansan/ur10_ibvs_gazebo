# generated from rosidl_generator_py/resource/_idl.py.em
# with input from service_interfaces:msg/MomentFeatures.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_MomentFeatures(type):
    """Metaclass of message 'MomentFeatures'."""

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
            module = import_type_support('service_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'service_interfaces.msg.MomentFeatures')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__moment_features
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__moment_features
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__moment_features
            cls._TYPE_SUPPORT = module.type_support_msg__msg__moment_features
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__moment_features

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


class MomentFeatures(metaclass=Metaclass_MomentFeatures):
    """Message class 'MomentFeatures'."""

    __slots__ = [
        '_header',
        '_x_gravity',
        '_y_gravity',
        '_area',
        '_sx',
        '_sy',
        '_alpha',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'x_gravity': 'double',
        'y_gravity': 'double',
        'area': 'double',
        'sx': 'double',
        'sy': 'double',
        'alpha': 'double',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.x_gravity = kwargs.get('x_gravity', float())
        self.y_gravity = kwargs.get('y_gravity', float())
        self.area = kwargs.get('area', float())
        self.sx = kwargs.get('sx', float())
        self.sy = kwargs.get('sy', float())
        self.alpha = kwargs.get('alpha', float())

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
        if self.x_gravity != other.x_gravity:
            return False
        if self.y_gravity != other.y_gravity:
            return False
        if self.area != other.area:
            return False
        if self.sx != other.sx:
            return False
        if self.sy != other.sy:
            return False
        if self.alpha != other.alpha:
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

    @builtins.property
    def x_gravity(self):
        """Message field 'x_gravity'."""
        return self._x_gravity

    @x_gravity.setter
    def x_gravity(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'x_gravity' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'x_gravity' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._x_gravity = value

    @builtins.property
    def y_gravity(self):
        """Message field 'y_gravity'."""
        return self._y_gravity

    @y_gravity.setter
    def y_gravity(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'y_gravity' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'y_gravity' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._y_gravity = value

    @builtins.property
    def area(self):
        """Message field 'area'."""
        return self._area

    @area.setter
    def area(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'area' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'area' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._area = value

    @builtins.property
    def sx(self):
        """Message field 'sx'."""
        return self._sx

    @sx.setter
    def sx(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'sx' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'sx' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._sx = value

    @builtins.property
    def sy(self):
        """Message field 'sy'."""
        return self._sy

    @sy.setter
    def sy(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'sy' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'sy' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._sy = value

    @builtins.property
    def alpha(self):
        """Message field 'alpha'."""
        return self._alpha

    @alpha.setter
    def alpha(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'alpha' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'alpha' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._alpha = value
