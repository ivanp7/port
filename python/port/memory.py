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
# @brief Memory model types.
#

import ctypes as c

import port.types as p

########################
### Memory reference ###
########################

port_memory_refq_t = p.port_sintq_t
port_memory_refh_t = p.port_sinth_t
port_memory_ref_t = p.port_sints_t

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
    _fields_ = [('as_uints', p.port_uints_t),
                ('as_uinth', p.port_uinth_t * 2),
                ('as_uinth_v2', p.port_uinth_v2_t),
                ('as_uintq', p.port_uintq_t * 4),
                ('as_uintq_v2', p.port_uintq_v2_t * 2),
                ('as_uintq_v4', p.port_uintq_v4_t),
                ('as_sints', p.port_sints_t),
                ('as_sinth', p.port_sinth_t * 2),
                ('as_sinth_v2', p.port_sinth_v2_t),
                ('as_sintq', p.port_sintq_t * 4),
                ('as_sintq_v2', p.port_sintq_v2_t * 2),
                ('as_sintq_v4', p.port_sintq_v4_t),
                ('as_floats', p.port_floats_t)]

class port_memory_unitd_t(c.Union):
    """Type punning union for double size types.
    """
    _fields_ = [('as_unit', port_memory_unit_t * 2),
                ('as_uintd', p.port_uintd_t),
                ('as_sintd', p.port_sintd_t),
                ('as_floatd', p.port_floatd_t)]

