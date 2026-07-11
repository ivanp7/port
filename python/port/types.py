 ############################################################################
 # Copyright (C) 2020-2026 by Ivan Podmazov                                 #
 #                                                                          #
 # This file is part of Port.                                               #
 #                                                                          #
 #   Port is free software: you can redistribute it and/or modify it        #
 #   under the terms of the GNU Lesser General Public License as published  #
 #   by the Free Software Foundation, either version 3 of the License, or   #
 #   (at your option) any later version.                                    #
 #                                                                          #
 #   Port is distributed in the hope that it will be useful,                #
 #   but WITHOUT ANY WARRANTY; without even the implied warranty of         #
 #   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          #
 #   GNU Lesser General Public License for more details.                    #
 #                                                                          #
 #   You should have received a copy of the GNU Lesser General Public       #
 #   License along with Port. If not, see <http://www.gnu.org/licenses/>.   #
 ############################################################################

##
# @file
# @brief Definitions of built-in scalar and vector types in Port.
#

import ctypes as c
import os


def _define_vector_type(basetype, length, actual_length=None):
    if hasattr(_define_vector_type, 'vector_fields'):
        vector_fields = _define_vector_type.vector_fields
    else:
        vector_fields = {}
        vector_fields[2] = [['s0', 's1'], ['x', 'y']]
        vector_fields[3] = [vector_fields[2][0] + ['s2'], vector_fields[2][1] + ['z']]
        vector_fields[4] = [vector_fields[3][0] + ['s3'], vector_fields[3][1] + ['w']]
        vector_fields[8] = [vector_fields[4][0] + ['s4', 's5', 's6', 's7'], vector_fields[4][1]]
        vector_fields[16] = [vector_fields[8][0] + ['s8', 's9', 'sA', 'sB', 'sC', 'sD', 'sE', 'sF'], vector_fields[8][1]]

        _define_vector_type.vector_fields = vector_fields

    field_groups = vector_fields[length]

    if actual_length is None:
        actual_length = length

    def define_struct(fields):
        class struct(c.Structure):
            _fields_ = [(field, basetype) for field in fields]

        return struct

    class vector(c.Union):
        _anonymous_ = [''.join(fields) for fields in field_groups]
        _fields_ = [('s', basetype * length)] + \
                [(''.join(fields), define_struct(fields)) for fields in field_groups]
        _align_ = c.sizeof(basetype * actual_length)

        def __init__(self, *components):
            if components is not None:
                self.s = (basetype * length)(*components)

    return vector


def _define_vector_types(basetype):
    return (_define_vector_type(basetype, 2),
            _define_vector_type(basetype, 3, 4),
            _define_vector_type(basetype, 4),
            _define_vector_type(basetype, 8),
            _define_vector_type(basetype, 16))

######################
### Absolute types ###
######################

# Scalars
port_uint8_t = c.c_uint8
port_uint16_t = c.c_uint16
port_uint32_t = c.c_uint32
port_uint64_t = c.c_uint64

port_sint8_t = c.c_int8
port_sint16_t = c.c_int16
port_sint32_t = c.c_int32
port_sint64_t = c.c_int64

port_float32_t = c.c_float
port_float64_t = c.c_double

# Vectors of unsigned integers
port_uint8_v2_t, port_uint8_v3_t, port_uint8_v4_t, port_uint8_v8_t, port_uint8_v16_t = \
        _define_vector_types(port_uint8_t)

port_uint16_v2_t, port_uint16_v3_t, port_uint16_v4_t, port_uint16_v8_t, port_uint16_v16_t = \
        _define_vector_types(port_uint16_t)

port_uint32_v2_t, port_uint32_v3_t, port_uint32_v4_t, port_uint32_v8_t, port_uint32_v16_t = \
        _define_vector_types(port_uint32_t)

port_uint64_v2_t, port_uint64_v3_t, port_uint64_v4_t, port_uint64_v8_t, port_uint64_v16_t = \
        _define_vector_types(port_uint64_t)

# Vectors of signed integers
port_sint8_v2_t, port_sint8_v3_t, port_sint8_v4_t, port_sint8_v8_t, port_sint8_v16_t = \
        _define_vector_types(port_sint8_t)

port_sint16_v2_t, port_sint16_v3_t, port_sint16_v4_t, port_sint16_v8_t, port_sint16_v16_t = \
        _define_vector_types(port_sint16_t)

port_sint32_v2_t, port_sint32_v3_t, port_sint32_v4_t, port_sint32_v8_t, port_sint32_v16_t = \
        _define_vector_types(port_sint32_t)

port_sint64_v2_t, port_sint64_v3_t, port_sint64_v4_t, port_sint64_v8_t, port_sint64_v16_t = \
        _define_vector_types(port_sint64_t)

# Vectors of floating-point numbers
port_float32_v2_t, port_float32_v3_t, port_float32_v4_t, port_float32_v8_t, port_float32_v16_t = \
        _define_vector_types(port_float32_t)

port_float64_v2_t, port_float64_v3_t, port_float64_v4_t, port_float64_v8_t, port_float64_v16_t = \
        _define_vector_types(port_float64_t)

######################
### Relative types ###
######################

# Unsigned integers
port_uintq_t = port_uint8_t
port_uintq_v2_t = port_uint8_v2_t
port_uintq_v3_t = port_uint8_v3_t
port_uintq_v4_t = port_uint8_v4_t
port_uintq_v8_t = port_uint8_v8_t
port_uintq_v16_t = port_uint8_v16_t

port_uinth_t = port_uint16_t
port_uinth_v2_t = port_uint16_v2_t
port_uinth_v3_t = port_uint16_v3_t
port_uinth_v4_t = port_uint16_v4_t
port_uinth_v8_t = port_uint16_v8_t
port_uinth_v16_t = port_uint16_v16_t

port_uints_t = port_uint32_t
port_uints_v2_t = port_uint32_v2_t
port_uints_v3_t = port_uint32_v3_t
port_uints_v4_t = port_uint32_v4_t
port_uints_v8_t = port_uint32_v8_t
port_uints_v16_t = port_uint32_v16_t

port_uintd_t = port_uint64_t
port_uintd_v2_t = port_uint64_v2_t
port_uintd_v3_t = port_uint64_v3_t
port_uintd_v4_t = port_uint64_v4_t
port_uintd_v8_t = port_uint64_v8_t
port_uintd_v16_t = port_uint64_v16_t

# Signed integers
port_sintq_t = port_sint8_t
port_sintq_v2_t = port_sint8_v2_t
port_sintq_v3_t = port_sint8_v3_t
port_sintq_v4_t = port_sint8_v4_t
port_sintq_v8_t = port_sint8_v8_t
port_sintq_v16_t = port_sint8_v16_t

port_sinth_t = port_sint16_t
port_sinth_v2_t = port_sint16_v2_t
port_sinth_v3_t = port_sint16_v3_t
port_sinth_v4_t = port_sint16_v4_t
port_sinth_v8_t = port_sint16_v8_t
port_sinth_v16_t = port_sint16_v16_t

port_sints_t = port_sint32_t
port_sints_v2_t = port_sint32_v2_t
port_sints_v3_t = port_sint32_v3_t
port_sints_v4_t = port_sint32_v4_t
port_sints_v8_t = port_sint32_v8_t
port_sints_v16_t = port_sint32_v16_t

port_sintd_t = port_sint64_t
port_sintd_v2_t = port_sint64_v2_t
port_sintd_v3_t = port_sint64_v3_t
port_sintd_v4_t = port_sint64_v4_t
port_sintd_v8_t = port_sint64_v8_t
port_sintd_v16_t = port_sint64_v16_t

# Floating-point numbers
port_floats_t = port_float32_t
port_floats_v2_t = port_float32_v2_t
port_floats_v3_t = port_float32_v3_t
port_floats_v4_t = port_float32_v4_t
port_floats_v8_t = port_float32_v8_t
port_floats_v16_t = port_float32_v16_t

port_floatd_t = port_float64_t
port_floatd_v2_t = port_float64_v2_t
port_floatd_v3_t = port_float64_v3_t
port_floatd_v4_t = port_float64_v4_t
port_floatd_v8_t = port_float64_v8_t
port_floatd_v16_t = port_float64_v16_t

