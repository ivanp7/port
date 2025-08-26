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
# @brief Memory model types.
#

import ctypes as c

import port.types as p

########################
### Memory reference ###
########################

port_memory_ref_t = p.port_sint_single_t
port_memory_ref_half_t = p.port_sint_half_t
port_memory_ref_quarter_t = p.port_sint_quarter_t

def reference(offset, table_index=None, num_tidx_bits=None, /):
    """Construct a memory reference value.
    """
    if offset < 0:
        raise ValueError

    if table_index is None: # near reference
        if offset == 0:
            raise ValueError("Near memory references cannot have zero offset")

        return -offset

    else: # far reference
        if num_tidx_bits is None:
            raise ValueError
        elif table_index < 0:
            raise ValueError
        elif table_index >= (1 << num_tidx_bits):
            raise ValueError

        return (offset << num_tidx_bits) | table_index

###################
### Memory unit ###
###################

class port_memory_unit_t(c.Union):
    """Standard memory unit.
    """
    _fields_ = [('as_uint_single', p.port_uint_single_t),
                ('as_uint_half', p.port_uint_half_t * 2),
                ('as_uint_half_v2', p.port_uint_half_v2_t),
                ('as_uint_quarter', p.port_uint_quarter_t * 4),
                ('as_uint_quarter_v2', p.port_uint_quarter_v2_t * 2),
                ('as_uint_quarter_v4', p.port_uint_quarter_v4_t),
                ('as_sint_single', p.port_sint_single_t),
                ('as_sint_half', p.port_sint_half_t * 2),
                ('as_sint_half_v2', p.port_sint_half_v2_t),
                ('as_sint_quarter', p.port_sint_quarter_t * 4),
                ('as_sint_quarter_v2', p.port_sint_quarter_v2_t * 2),
                ('as_sint_quarter_v4', p.port_sint_quarter_v4_t),
                ('as_float_single', p.port_float_single_t)]

class port_memory_unit_double_t(c.Union):
    """Type punning union for double size types.
    """
    _fields_ = [('as_unit', port_memory_unit_t * 2),
                ('as_uint_double', p.port_uint_double_t),
                ('as_sint_double', p.port_sint_double_t),
                ('as_float_double', p.port_float_double_t)]

