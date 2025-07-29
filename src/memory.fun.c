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
#  ifndef NDEBUG
#    include "port/bit.def.h"
#  endif

#  include <assert.h>
#endif

#if !defined(__OPENCL_C_VERSION__) && !defined(NDEBUG)

#  define ASSERTS \
    assert(format.far.num_tidx_bits < PORT_NUM_BITS(port_memory_ref_t)); \
    if (PORT_MEMORY_REF_IS_FAR(ref)) { \
        size_t offset = PORT_MEMORY_REF_FAR__OFFSET(ref, format.far.num_tidx_bits); \
        assert(((offset << format.far.offset_lshift) >> format.far.offset_lshift) == offset); \
    } else { \
        size_t offset = -(size_t)ref; \
        assert(((offset << format.near.offset_lshift) >> format.near.offset_lshift) == offset); \
    } \
    assert(memory_table != NULL);

#else

#  define ASSERTS

#endif

port_const_void_ptr_t
port_memory_at(
        port_memory_ref_t ref,
        port_memory_ref_format_t format,

        port_const_void_ptr_t base_ptr,
        const PORT_KW_CONSTANT port_const_void_ptr_t *memory_table)
{
    ASSERTS;
    return PORT_MEMORY_AT(ref, format.far.num_tidx_bits, format.far.offset_lshift, format.near.offset_lshift,
            (port_const_char_ptr_t)base_ptr, (const PORT_KW_CONSTANT port_const_char_ptr_t*)memory_table);
}

#ifdef __OPENCL_C_VERSION__

port_const_local_void_ptr_t
port_memory_at_local(
        port_memory_ref_t ref,
        port_memory_ref_format_t format,

        port_const_local_void_ptr_t base_ptr,
        const PORT_KW_CONSTANT port_const_local_void_ptr_t *memory_table)
{
    ASSERTS;
    return PORT_MEMORY_AT(ref, format.far.num_tidx_bits, format.far.offset_lshift, format.near.offset_lshift,
            (port_const_local_char_ptr_t)base_ptr, (const PORT_KW_CONSTANT port_const_local_char_ptr_t*)memory_table);
}

port_const_global_void_ptr_t
port_memory_at_global(
        port_memory_ref_t ref,
        port_memory_ref_format_t format,

        port_const_global_void_ptr_t base_ptr,
        const PORT_KW_CONSTANT port_const_global_void_ptr_t *memory_table)
{
    ASSERTS;
    return PORT_MEMORY_AT(ref, format.far.num_tidx_bits, format.far.offset_lshift, format.near.offset_lshift,
            (port_const_global_char_ptr_t)base_ptr, (const PORT_KW_CONSTANT port_const_global_char_ptr_t*)memory_table);
}

port_constant_void_ptr_t
port_memory_at_constant(
        port_memory_ref_t ref,
        port_memory_ref_format_t format,

        port_constant_void_ptr_t base_ptr,
        const PORT_KW_CONSTANT port_constant_void_ptr_t *memory_table)
{
    ASSERTS;
    return PORT_MEMORY_AT(ref, format.far.num_tidx_bits, format.far.offset_lshift, format.near.offset_lshift,
            (port_constant_char_ptr_t)base_ptr, (const PORT_KW_CONSTANT port_constant_char_ptr_t*)memory_table);
}

#endif // __OPENCL_C_VERSION__

