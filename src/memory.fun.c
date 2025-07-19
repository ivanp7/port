/****************************************************************************
 * Copyright (C) 2020-2025 by Ivan Podmazov                                 *
 *                                                                          *
 * This file is part of Port.                                               *
 *                                                                          *
 *   Port is free software: you can redistribute it and/or modify it        *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   Port is distributed in the hope that it will be useful,                *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with Port. If not, see <http://www.gnu.org/licenses/>.   *
 ****************************************************************************/

/**
 * @file
 * @brief Operations on memory.
 */

#include "port/memory.fun.h"
#include "port/memory.def.h"

#ifndef __OPENCL_C_VERSION__
#  include "port/bit.def.h"
#  include <assert.h>
#endif

port_const_global_memory_ptr_t
port_memory_at(
        port_memory_ref_t ref,

        port_memory_ref_format_t format,

        port_const_global_memory_ptr_t base_ptr,
        port_memory_table_t memory_table)
{
#ifndef __OPENCL_C_VERSION__
    if (PORT_MEMORY_REF_IS_FAR(ref))
    {
        assert(format.num_tidx_bits < PORT_NUM_BITS(port_memory_ref_t));
        assert(((PORT_MEMORY_REF_FAR__OFFSET(ref, format.num_tidx_bits) << format.offset_shift)
            >> format.offset_shift) == PORT_MEMORY_REF_FAR__OFFSET(ref, format.num_tidx_bits));
    }
    assert(memory_table != NULL);
#endif

    return PORT_MEMORY_AT(ref, format.num_tidx_bits, format.offset_shift, base_ptr, memory_table);
}

