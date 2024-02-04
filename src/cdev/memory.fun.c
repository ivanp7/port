/****************************************************************************
 * Copyright (C) 2020-2024 by Ivan Podmazov                                 *
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

#include <port/cdev/memory.fun.h>
#include <port/cdev/bit.def.h>

#ifndef __OPENCL_C_VERSION__
#  include <assert.h>
#  include <string.h>
#endif

///////////////////////////////////////////////////////////////////////////////
// Memory reference
///////////////////////////////////////////////////////////////////////////////

port_const_global_memory_ptr_t
port_memory_reference(
        port_memory_ref_t ref,

        port_uint8_t num_idx_bits,
        port_uint8_t offset_shift,

        port_const_global_memory_ptr_t base_ptr,
        port_memory_table_t memory_table)
{
#ifndef __OPENCL_C_VERSION__
    if (ref >= 0)
        assert(((port_size_t)(ref >> num_idx_bits) << offset_shift) >> offset_shift ==
                (port_size_t)(ref >> num_idx_bits));
    assert(memory_table != NULL);
#endif

    if (ref < 0) // near reference
        return (base_ptr ? base_ptr : memory_table[0]) - ref;
    else // far reference
        return memory_table[ref & PORT_SINGLE_MASK(num_idx_bits)] +
            ((port_size_t)(ref >> num_idx_bits) << offset_shift);
}

///////////////////////////////////////////////////////////////////////////////
// Memory copying
///////////////////////////////////////////////////////////////////////////////

#ifdef __OPENCL_C_VERSION__

#  define MEMCPY_IMPL \
    for (port_size_t i = 0; i < num_units; i++) dest[i] = src[i];

#else

#  define MEMCPY_IMPL     \
    assert(dest != NULL); \
    assert(src != NULL);  \
    memcpy(dest, src, sizeof(port_memory_unit_t) * num_units);

#endif

void
port_memcpy_global_to_private(
        port_private_memory_ptr_t restrict dest,
        port_const_global_memory_ptr_t restrict src,
        port_size_t num_units)
{
    MEMCPY_IMPL
}

void
port_memcpy_constant_to_private(
        port_private_memory_ptr_t restrict dest,
        port_constant_memory_ptr_t restrict src,
        port_size_t num_units)
{
    MEMCPY_IMPL
}

void
port_memcpy_local_to_private(
        port_private_memory_ptr_t restrict dest,
        port_const_local_memory_ptr_t restrict src,
        port_size_t num_units)
{
    MEMCPY_IMPL
}

void
port_memcpy_private_to_private(
        port_private_memory_ptr_t restrict dest,
        port_const_private_memory_ptr_t restrict src,
        port_size_t num_units)
{
    MEMCPY_IMPL
}

void
port_memcpy_global_to_local(
        port_local_memory_ptr_t restrict dest,
        port_const_global_memory_ptr_t restrict src,
        port_size_t num_units)
{
    MEMCPY_IMPL
}

void
port_memcpy_constant_to_local(
        port_local_memory_ptr_t restrict dest,
        port_constant_memory_ptr_t restrict src,
        port_size_t num_units)
{
    MEMCPY_IMPL
}

void
port_memcpy_local_to_local(
        port_local_memory_ptr_t restrict dest,
        port_const_local_memory_ptr_t restrict src,
        port_size_t num_units)
{
    MEMCPY_IMPL
}

void
port_memcpy_private_to_local(
        port_local_memory_ptr_t restrict dest,
        port_const_private_memory_ptr_t restrict src,
        port_size_t num_units)
{
    MEMCPY_IMPL
}

void
port_memcpy_global_to_global(
        port_global_memory_ptr_t restrict dest,
        port_const_global_memory_ptr_t restrict src,
        port_size_t num_units)
{
    MEMCPY_IMPL
}

void
port_memcpy_local_to_global(
        port_global_memory_ptr_t restrict dest,
        port_const_local_memory_ptr_t restrict src,
        port_size_t num_units)
{
    MEMCPY_IMPL
}

void
port_memcpy_constant_to_global(
        port_global_memory_ptr_t restrict dest,
        port_constant_memory_ptr_t restrict src,
        port_size_t num_units)
{
    MEMCPY_IMPL
}

void
port_memcpy_private_to_global(
        port_global_memory_ptr_t restrict dest,
        port_const_private_memory_ptr_t restrict src,
        port_size_t num_units)
{
    MEMCPY_IMPL
}

#undef MEMCPY_IMPL

///////////////////////////////////////////////////////////////////////////////
// Reading/writing of integers
///////////////////////////////////////////////////////////////////////////////

port_uint64_t
port_memread_uint64(
        port_const_memory_ptr_t memory)
{
#ifndef __OPENCL_C_VERSION__
    assert(memory != NULL);
#endif

    port_memory_unit_double_t u = {.as_units = {memory[0], memory[1]}};
    return u.as_uint_double;
}

port_sint64_t
port_memread_sint64(
        port_const_memory_ptr_t memory)
{
#ifndef __OPENCL_C_VERSION__
    assert(memory != NULL);
#endif

    port_memory_unit_double_t u = {.as_units = {memory[0], memory[1]}};
    return u.as_sint_double;
}

void
port_memwrite_uint64(
        port_memory_ptr_t memory,
        port_uint64_t value)
{
#ifndef __OPENCL_C_VERSION__
    assert(memory != NULL);
#endif

    port_memory_unit_double_t u = {.as_uint_double = value};
    memory[0] = u.as_units[0];
    memory[1] = u.as_units[1];
}

void
port_memwrite_sint64(
        port_memory_ptr_t memory,
        port_sint64_t value)
{
#ifndef __OPENCL_C_VERSION__
    assert(memory != NULL);
#endif

    port_memory_unit_double_t u = {.as_sint_double = value};
    memory[0] = u.as_units[0];
    memory[1] = u.as_units[1];
}

port_uint_t
port_memread_uint(
        port_const_memory_ptr_t memory)
{
#ifndef __OPENCL_C_VERSION__
    assert(memory != NULL);
#endif

#ifndef PORT_FEATURE_DEFAULT_INTEGER_64
    return memory->as_uint_single;
#else
    return port_memread_uint64(memory);
#endif
}

port_sint_t
port_memread_sint(
        port_const_memory_ptr_t memory)
{
#ifndef __OPENCL_C_VERSION__
    assert(memory != NULL);
#endif

#ifndef PORT_FEATURE_DEFAULT_INTEGER_64
    return memory->as_sint_single;
#else
    return port_memread_sint64(memory);
#endif
}

void
port_memwrite_uint(
        port_memory_ptr_t memory,
        port_uint_t value)
{
#ifndef __OPENCL_C_VERSION__
    assert(memory != NULL);
#endif

#ifndef PORT_FEATURE_DEFAULT_INTEGER_64
    memory->as_uint_single = value;
#else
    port_memwrite_uint64(memory, value);
#endif
}

void
port_memwrite_sint(
        port_memory_ptr_t memory,
        port_sint_t value)
{
#ifndef __OPENCL_C_VERSION__
    assert(memory != NULL);
#endif

#ifndef PORT_FEATURE_DEFAULT_INTEGER_64
    memory->as_sint_single = value;
#else
    port_memwrite_sint64(memory, value);
#endif
}

///////////////////////////////////////////////////////////////////////////////
// Reading/writing of floating-point numbers
///////////////////////////////////////////////////////////////////////////////

port_float64_t
port_memread_float64(
        port_const_memory_ptr_t memory)
{
#ifndef __OPENCL_C_VERSION__
    assert(memory != NULL);
#endif

    port_memory_unit_double_t u = {.as_units = {memory[0], memory[1]}};
    return u.as_float_double;
}

void
port_memwrite_float64(
        port_memory_ptr_t memory,
        port_float64_t value)
{
#ifndef __OPENCL_C_VERSION__
    assert(memory != NULL);
#endif

    port_memory_unit_double_t u = {.as_float_double = value};
    memory[0] = u.as_units[0];
    memory[1] = u.as_units[1];
}

port_float_t
port_memread_float(
        port_const_memory_ptr_t memory)
{
#ifndef __OPENCL_C_VERSION__
    assert(memory != NULL);
#endif

#ifndef PORT_FEATURE_DEFAULT_FLOAT_64
    return memory->as_float_single;
#else
    return port_memread_float64(memory);
#endif
}

void
port_memwrite_float(
        port_memory_ptr_t memory,
        port_float_t value)
{
#ifndef __OPENCL_C_VERSION__
    assert(memory != NULL);
#endif

#ifndef PORT_FEATURE_DEFAULT_FLOAT_64
    memory->as_float_single = value;
#else
    port_memwrite_float64(memory, value);
#endif
}

