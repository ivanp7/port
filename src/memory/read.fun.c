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
 * @brief Functions for reading built-in types from memory.
 */

#include "port/memory/read.fun.h"

#ifndef __OPENCL_C_VERSION__
#  include "port/float.fun.h" // for port_convert_float*()
#  include <stdint.h> // for uintptr_t
#  include <assert.h>
#endif

#ifdef __OPENCL_C_VERSION__
#  define ASSERT_MEMORY(type)
#else
#  define ASSERT_MEMORY(type) \
    assert(memory != NULL);   \
    assert((uintptr_t)memory % sizeof(type) == 0)
#endif

///////////////////////////////////////////////////////////////////////////////
// Scalars (generic address space)
///////////////////////////////////////////////////////////////////////////////

#define DEFINE_READ_FUNCTION(type) \
port_##type##_t port_memory_read_##type(port_const_void_ptr_t memory, size_t offset) \
{                                                       \
    ASSERT_MEMORY(port_##type##_t);                     \
    return *((const port_##type##_t*)memory + offset);  \
}

DEFINE_READ_FUNCTION(uint8)
DEFINE_READ_FUNCTION(uint16)
DEFINE_READ_FUNCTION(uint32)
DEFINE_READ_FUNCTION(uint64)

DEFINE_READ_FUNCTION(sint8)
DEFINE_READ_FUNCTION(sint16)
DEFINE_READ_FUNCTION(sint32)
DEFINE_READ_FUNCTION(sint64)

DEFINE_READ_FUNCTION(float32)
DEFINE_READ_FUNCTION(float64)

#undef DEFINE_READ_FUNCTION


port_float32_t port_memory_read_float16(port_const_void_ptr_t memory, size_t offset)
{
#ifdef __OPENCL_C_VERSION__
    return vload_half(offset, (const half*)memory);
#else
    ASSERT_MEMORY(port_uint16_t);
    return port_convert_float16_to_float32(*((const port_uint16_t*)memory + offset));
#endif
}

///////////////////////////////////////////////////////////////////////////////
// Vectors (generic address space)
///////////////////////////////////////////////////////////////////////////////

#ifdef __OPENCL_C_VERSION__

#define DEFINE_READ_FUNCTION(type, vlen) \
port_##type##_v##vlen##_t port_memory_read_##type##_v##vlen(port_const_void_ptr_t memory, size_t offset) \
{                                                               \
    return vload##vlen(offset, (const port_##type##_t*)memory); \
}

#else // __OPENCL_C_VERSION__

#define DEFINE_READ_FUNCTION(type, vlen) \
port_##type##_v##vlen##_t port_memory_read_##type##_v##vlen(port_const_void_ptr_t memory, size_t offset) \
{                                                                   \
    ASSERT_MEMORY(port_##type##_t);                                 \
    port_##type##_v##vlen##_t value;                                \
    for (size_t i = 0; i < vlen; i++)                               \
        value.s[i] = ((const port_##type##_t*)memory + offset)[i];  \
    return value;                                                   \
}

#endif // __OPENCL_C_VERSION__

#define DEFINE_READ_FUNCTIONS(type) \
    DEFINE_READ_FUNCTION(type, 2) \
    DEFINE_READ_FUNCTION(type, 3) \
    DEFINE_READ_FUNCTION(type, 4) \
    DEFINE_READ_FUNCTION(type, 8) \
    DEFINE_READ_FUNCTION(type, 16)

DEFINE_READ_FUNCTIONS(uint8)
DEFINE_READ_FUNCTIONS(uint16)
DEFINE_READ_FUNCTIONS(uint32)
DEFINE_READ_FUNCTIONS(uint64)

DEFINE_READ_FUNCTIONS(sint8)
DEFINE_READ_FUNCTIONS(sint16)
DEFINE_READ_FUNCTIONS(sint32)
DEFINE_READ_FUNCTIONS(sint64)

DEFINE_READ_FUNCTIONS(float32)
DEFINE_READ_FUNCTIONS(float64)

#undef DEFINE_READ_FUNCTIONS
#undef DEFINE_READ_FUNCTION


#ifdef __OPENCL_C_VERSION__

#define DEFINE_READ_FUNCTION(vlen) \
port_float32_v##vlen##_t port_memory_read_float16_v##vlen(port_const_void_ptr_t memory, size_t offset) \
{                                                           \
    return vload_half##vlen(offset, (const half*)memory);   \
}

#else // __OPENCL_C_VERSION__

#define DEFINE_READ_FUNCTION(vlen) \
port_float32_v##vlen##_t port_memory_read_float16_v##vlen(port_const_void_ptr_t memory, size_t offset) \
{                                                                                                   \
    ASSERT_MEMORY(port_uint16_t);                                                                   \
    port_float32_v##vlen##_t value;                                                                 \
    for (size_t i = 0; i < vlen; i++)                                                               \
        value.s[i] = port_convert_float16_to_float32(((const port_uint16_t*)memory + offset)[i]);   \
    return value;                                                                                   \
}

#endif // __OPENCL_C_VERSION__

DEFINE_READ_FUNCTION(2)
DEFINE_READ_FUNCTION(3)
DEFINE_READ_FUNCTION(4)
DEFINE_READ_FUNCTION(8)
DEFINE_READ_FUNCTION(16)

#undef DEFINE_READ_FUNCTION

///////////////////////////////////////////////////////////////////////////////
// Scalars (named address spaces)
///////////////////////////////////////////////////////////////////////////////

#ifdef __OPENCL_C_VERSION__

typedef port_constant_void_ptr_t port_const_constant_void_ptr_t; // workaround needed for the 'constant' address space

#define DEFINE_READ_FUNCTION(type, address_space) \
port_##type##_t port_memory_read_##address_space##_##type( \
        port_const_##address_space##_void_ptr_t memory, size_t offset) \
{                                                                           \
    return *((const __##address_space port_##type##_t*)memory + offset);    \
}

#define DEFINE_READ_FUNCTIONS(type) \
    DEFINE_READ_FUNCTION(type, local) \
    DEFINE_READ_FUNCTION(type, global) \
    DEFINE_READ_FUNCTION(type, constant)

DEFINE_READ_FUNCTIONS(uint8)
DEFINE_READ_FUNCTIONS(uint16)
DEFINE_READ_FUNCTIONS(uint32)
DEFINE_READ_FUNCTIONS(uint64)

DEFINE_READ_FUNCTIONS(sint8)
DEFINE_READ_FUNCTIONS(sint16)
DEFINE_READ_FUNCTIONS(sint32)
DEFINE_READ_FUNCTIONS(sint64)

DEFINE_READ_FUNCTIONS(float32)
DEFINE_READ_FUNCTIONS(float64)

#undef DEFINE_READ_FUNCTIONS
#undef DEFINE_READ_FUNCTION


#define DEFINE_READ_FUNCTION(address_space) \
port_float32_t port_memory_read_##address_space##_float16( \
        port_const_##address_space##_void_ptr_t memory, size_t offset) \
{                                                                       \
    return vload_half(offset, (const __##address_space half*)memory);   \
}

DEFINE_READ_FUNCTION(local)
DEFINE_READ_FUNCTION(global)
DEFINE_READ_FUNCTION(constant)

#undef DEFINE_READ_FUNCTION

#endif // __OPENCL_C_VERSION__

///////////////////////////////////////////////////////////////////////////////
// Vectors (named address spaces)
///////////////////////////////////////////////////////////////////////////////

#ifdef __OPENCL_C_VERSION__

#define DEFINE_READ_FUNCTION(type, vlen, address_space) \
port_##type##_v##vlen##_t port_memory_read_##address_space##_##type##_v##vlen( \
        port_const_##address_space##_void_ptr_t memory, size_t offset) \
{                                                                                   \
    return vload##vlen(offset, (const __##address_space port_##type##_t*)memory);   \
}

#define DEFINE_READ_FUNCTIONS(type) \
    DEFINE_READ_FUNCTION(type, 2, local) \
    DEFINE_READ_FUNCTION(type, 2, global) \
    DEFINE_READ_FUNCTION(type, 2, constant) \
    DEFINE_READ_FUNCTION(type, 3, local) \
    DEFINE_READ_FUNCTION(type, 3, global) \
    DEFINE_READ_FUNCTION(type, 3, constant) \
    DEFINE_READ_FUNCTION(type, 4, local) \
    DEFINE_READ_FUNCTION(type, 4, global) \
    DEFINE_READ_FUNCTION(type, 4, constant) \
    DEFINE_READ_FUNCTION(type, 8, local) \
    DEFINE_READ_FUNCTION(type, 8, global) \
    DEFINE_READ_FUNCTION(type, 8, constant) \
    DEFINE_READ_FUNCTION(type, 16, local) \
    DEFINE_READ_FUNCTION(type, 16, global) \
    DEFINE_READ_FUNCTION(type, 16, constant)

DEFINE_READ_FUNCTIONS(uint8)
DEFINE_READ_FUNCTIONS(uint16)
DEFINE_READ_FUNCTIONS(uint32)
DEFINE_READ_FUNCTIONS(uint64)

DEFINE_READ_FUNCTIONS(sint8)
DEFINE_READ_FUNCTIONS(sint16)
DEFINE_READ_FUNCTIONS(sint32)
DEFINE_READ_FUNCTIONS(sint64)

DEFINE_READ_FUNCTIONS(float32)
DEFINE_READ_FUNCTIONS(float64)

#undef DEFINE_READ_FUNCTIONS
#undef DEFINE_READ_FUNCTION


#define DEFINE_READ_FUNCTION(vlen, address_space) \
port_float32_v##vlen##_t port_memory_read_##address_space##_float16_v##vlen( \
        port_const_##address_space##_void_ptr_t memory, size_t offset) \
{                                                                           \
    return vload_half##vlen(offset, (const __##address_space half*)memory); \
}

#define DEFINE_READ_FUNCTIONS(vlen) \
    DEFINE_READ_FUNCTION(vlen, local) \
    DEFINE_READ_FUNCTION(vlen, global) \
    DEFINE_READ_FUNCTION(vlen, constant)

DEFINE_READ_FUNCTIONS(2)
DEFINE_READ_FUNCTIONS(3)
DEFINE_READ_FUNCTIONS(4)
DEFINE_READ_FUNCTIONS(8)
DEFINE_READ_FUNCTIONS(16)

#undef DEFINE_READ_FUNCTIONS
#undef DEFINE_READ_FUNCTION

#endif // __OPENCL_C_VERSION__

