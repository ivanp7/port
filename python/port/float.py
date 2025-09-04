 ############################################################################
 # Copyright (C) 2020-2025 by Ivan Podmazov                                 #
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
# @brief Operations on floating-point numbers.
#

import port.types as p


def to_float16(value):
    """Convert Python float to IEEE754 float16.
    """
    import numpy as np

    float32_val = np.float32(value)
    float16_val = float32_val.astype(np.float16)

    return int(float16_val.view(np.uint16))


def from_float16(value):
    """Convert IEEE754 float16 to Python float.
    """
    import numpy as np

    float16_val = np.uint16(value).view(np.float16)
    float32_val = float16_val.astype(np.float32)

    return float(float32_val)


def convert_float32_to_float16(vector_or_scalar, /):
    """Convert Port float32 vector/scalar to float16.
    """
    if isinstance(vector_or_scalar, p.port_float32_t):
        return p.port_uint16_t(to_float16(vector_or_scalar.value))
    elif isinstance(vector_or_scalar, p.port_float32_v2_t):
        return p.port_uint16_v2_t([to_float16(cmp) for cmp in vector_or_scalar.s])
    elif isinstance(vector_or_scalar, p.port_float32_v3_t):
        return p.port_uint16_v3_t([to_float16(cmp) for cmp in vector_or_scalar.s])
    elif isinstance(vector_or_scalar, p.port_float32_v4_t):
        return p.port_uint16_v4_t([to_float16(cmp) for cmp in vector_or_scalar.s])
    elif isinstance(vector_or_scalar, p.port_float32_v8_t):
        return p.port_uint16_v8_t([to_float16(cmp) for cmp in vector_or_scalar.s])
    elif isinstance(vector_or_scalar, p.port_float32_v16_t):
        return p.port_uint16_v16_t([to_float16(cmp) for cmp in vector_or_scalar.s])
    else:
        raise TypeError


def convert_float16_to_float32(vector_or_scalar, /):
    """Convert Port float16 vector/scalar to float32.
    """
    if isinstance(vector_or_scalar, p.port_uint16_t):
        return p.port_float32_t(from_float16(vector_or_scalar.value))
    elif isinstance(vector_or_scalar, p.port_uint16_v2_t):
        return p.port_float32_v2_t([from_float16(cmp) for cmp in vector_or_scalar.s])
    elif isinstance(vector_or_scalar, p.port_uint16_v3_t):
        return p.port_float32_v3_t([from_float16(cmp) for cmp in vector_or_scalar.s])
    elif isinstance(vector_or_scalar, p.port_uint16_v4_t):
        return p.port_float32_v4_t([from_float16(cmp) for cmp in vector_or_scalar.s])
    elif isinstance(vector_or_scalar, p.port_uint16_v8_t):
        return p.port_float32_v8_t([from_float16(cmp) for cmp in vector_or_scalar.s])
    elif isinstance(vector_or_scalar, p.port_uint16_v16_t):
        return p.port_float32_v16_t([from_float16(cmp) for cmp in vector_or_scalar.s])

