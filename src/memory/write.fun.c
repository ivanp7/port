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
 * @brief Functions for writing built-in types to memory.
 */

#include "port/memory/write.fun.h"

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

#define DEFINE_WRITE_FUNCTION(type) \
void port_memory_write_##type(port_void_ptr_t memory, size_t offset, port_##type##_t value) \
{                                                   \
    ASSERT_MEMORY(port_##type##_t);                 \
    *((port_##type##_t*)memory + offset) = value;   \
}

DEFINE_WRITE_FUNCTION(uint8)
DEFINE_WRITE_FUNCTION(uint16)
DEFINE_WRITE_FUNCTION(uint32)
DEFINE_WRITE_FUNCTION(uint64)

DEFINE_WRITE_FUNCTION(sint8)
DEFINE_WRITE_FUNCTION(sint16)
DEFINE_WRITE_FUNCTION(sint32)
DEFINE_WRITE_FUNCTION(sint64)

DEFINE_WRITE_FUNCTION(float32)
DEFINE_WRITE_FUNCTION(float64)

#undef DEFINE_WRITE_FUNCTION


void port_memory_write_float16(port_void_ptr_t memory, size_t offset, port_float32_t value)
{
#ifdef __OPENCL_C_VERSION__
    return vstore_half(value, offset, (half*)memory);
#else
    ASSERT_MEMORY(port_uint16_t);
    *((port_uint16_t*)memory + offset) = port_convert_float32_to_float16(value);
#endif
}

///////////////////////////////////////////////////////////////////////////////
// Vectors (generic address space)
///////////////////////////////////////////////////////////////////////////////

#ifdef __OPENCL_C_VERSION__

#define DEFINE_WRITE_FUNCTION(type, vlen) \
void port_memory_write_##type##_v##vlen(port_void_ptr_t memory, size_t offset, port_##type##_v##vlen##_t value) \
{                                                           \
    vstore##vlen(value, offset, (port_##type##_t*)memory);  \
}

#else // __OPENCL_C_VERSION__

#define DEFINE_WRITE_FUNCTION(type, vlen) \
void port_memory_write_##type##_v##vlen(port_void_ptr_t memory, size_t offset, port_##type##_v##vlen##_t value) \
{                                                               \
    ASSERT_MEMORY(port_##type##_t);                             \
    for (size_t i = 0; i < vlen; i++)                           \
        ((port_##type##_t*)memory + offset)[i] = value.s[i];    \
}

#endif // __OPENCL_C_VERSION__

#define DEFINE_WRITE_FUNCTIONS(type) \
    DEFINE_WRITE_FUNCTION(type, 2) \
    DEFINE_WRITE_FUNCTION(type, 3) \
    DEFINE_WRITE_FUNCTION(type, 4) \
    DEFINE_WRITE_FUNCTION(type, 8) \
    DEFINE_WRITE_FUNCTION(type, 16)

DEFINE_WRITE_FUNCTIONS(uint8)
DEFINE_WRITE_FUNCTIONS(uint16)
DEFINE_WRITE_FUNCTIONS(uint32)
DEFINE_WRITE_FUNCTIONS(uint64)

DEFINE_WRITE_FUNCTIONS(sint8)
DEFINE_WRITE_FUNCTIONS(sint16)
DEFINE_WRITE_FUNCTIONS(sint32)
DEFINE_WRITE_FUNCTIONS(sint64)

DEFINE_WRITE_FUNCTIONS(float32)
DEFINE_WRITE_FUNCTIONS(float64)

#undef DEFINE_WRITE_FUNCTIONS
#undef DEFINE_WRITE_FUNCTION


#ifdef __OPENCL_C_VERSION__

#define DEFINE_WRITE_FUNCTION(vlen) \
void port_memory_write_float16_v##vlen(port_void_ptr_t memory, size_t offset, port_float32_v##vlen##_t value) \
{                                                       \
    vstore_half##vlen(value, offset, (half*)memory);    \
}

#else // __OPENCL_C_VERSION__

#define DEFINE_WRITE_FUNCTION(vlen) \
void port_memory_write_float16_v##vlen(port_void_ptr_t memory, size_t offset, port_float32_v##vlen##_t value) \
{                                                                                           \
    ASSERT_MEMORY(port_uint16_t);                                                           \
    for (size_t i = 0; i < vlen; i++)                                                       \
        ((port_uint16_t*)memory + offset)[i] = port_convert_float32_to_float16(value.s[i]); \
}

#endif // __OPENCL_C_VERSION__

DEFINE_WRITE_FUNCTION(2)
DEFINE_WRITE_FUNCTION(3)
DEFINE_WRITE_FUNCTION(4)
DEFINE_WRITE_FUNCTION(8)
DEFINE_WRITE_FUNCTION(16)

#undef DEFINE_WRITE_FUNCTION

///////////////////////////////////////////////////////////////////////////////
// Scalars (named address space)
///////////////////////////////////////////////////////////////////////////////

#ifdef __OPENCL_C_VERSION__

#define DEFINE_WRITE_FUNCTION(type, address_space) \
void port_memory_write_##address_space##_##type( \
        port_##address_space##_void_ptr_t memory, size_t offset, port_##type##_t value) \
{                                                                   \
    *((__##address_space port_##type##_t*)memory + offset) = value; \
}

#define DEFINE_WRITE_FUNCTIONS(type) \
    DEFINE_WRITE_FUNCTION(type, local) \
    DEFINE_WRITE_FUNCTION(type, global)

DEFINE_WRITE_FUNCTIONS(uint8)
DEFINE_WRITE_FUNCTIONS(uint16)
DEFINE_WRITE_FUNCTIONS(uint32)
DEFINE_WRITE_FUNCTIONS(uint64)

DEFINE_WRITE_FUNCTIONS(sint8)
DEFINE_WRITE_FUNCTIONS(sint16)
DEFINE_WRITE_FUNCTIONS(sint32)
DEFINE_WRITE_FUNCTIONS(sint64)

DEFINE_WRITE_FUNCTIONS(float32)
DEFINE_WRITE_FUNCTIONS(float64)

#undef DEFINE_WRITE_FUNCTIONS
#undef DEFINE_WRITE_FUNCTION


#define DEFINE_WRITE_FUNCTION(address_space) \
void port_memory_write_##address_space##_float16( \
        port_##address_space##_void_ptr_t memory, size_t offset, port_float32_t value) \
{                                                                   \
    vstore_half(value, offset, (__##address_space half*)memory);    \
}

DEFINE_WRITE_FUNCTION(local)
DEFINE_WRITE_FUNCTION(global)

#undef DEFINE_WRITE_FUNCTION

#endif // __OPENCL_C_VERSION__

///////////////////////////////////////////////////////////////////////////////
// Vectors (named address space)
///////////////////////////////////////////////////////////////////////////////

#ifdef __OPENCL_C_VERSION__

#define DEFINE_WRITE_FUNCTION(type, vlen, address_space) \
void port_memory_write_##address_space##_##type##_v##vlen( \
        port_##address_space##_void_ptr_t memory, size_t offset, port_##type##_v##vlen##_t value) \
{                                                                               \
    vstore##vlen(value, offset, (__##address_space port_##type##_t*)memory);    \
}

#define DEFINE_WRITE_FUNCTIONS(type) \
    DEFINE_WRITE_FUNCTION(type, 2, local) \
    DEFINE_WRITE_FUNCTION(type, 2, global) \
    DEFINE_WRITE_FUNCTION(type, 3, local) \
    DEFINE_WRITE_FUNCTION(type, 3, global) \
    DEFINE_WRITE_FUNCTION(type, 4, local) \
    DEFINE_WRITE_FUNCTION(type, 4, global) \
    DEFINE_WRITE_FUNCTION(type, 8, local) \
    DEFINE_WRITE_FUNCTION(type, 8, global) \
    DEFINE_WRITE_FUNCTION(type, 16, local) \
    DEFINE_WRITE_FUNCTION(type, 16, global)

DEFINE_WRITE_FUNCTIONS(uint8)
DEFINE_WRITE_FUNCTIONS(uint16)
DEFINE_WRITE_FUNCTIONS(uint32)
DEFINE_WRITE_FUNCTIONS(uint64)

DEFINE_WRITE_FUNCTIONS(sint8)
DEFINE_WRITE_FUNCTIONS(sint16)
DEFINE_WRITE_FUNCTIONS(sint32)
DEFINE_WRITE_FUNCTIONS(sint64)

DEFINE_WRITE_FUNCTIONS(float32)
DEFINE_WRITE_FUNCTIONS(float64)

#undef DEFINE_WRITE_FUNCTIONS
#undef DEFINE_WRITE_FUNCTION


#define DEFINE_WRITE_FUNCTION(vlen, address_space) \
void port_memory_write_##address_space##_float16_v##vlen( \
        port_##address_space##_void_ptr_t memory, size_t offset, port_float32_v##vlen##_t value) \
{                                                                       \
    vstore_half##vlen(value, offset, (__##address_space half*)memory);  \
}

#define DEFINE_WRITE_FUNCTIONS(vlen) \
    DEFINE_WRITE_FUNCTION(vlen, local) \
    DEFINE_WRITE_FUNCTION(vlen, global)

DEFINE_WRITE_FUNCTIONS(2)
DEFINE_WRITE_FUNCTIONS(3)
DEFINE_WRITE_FUNCTIONS(4)
DEFINE_WRITE_FUNCTIONS(8)
DEFINE_WRITE_FUNCTIONS(16)

#undef DEFINE_WRITE_FUNCTIONS
#undef DEFINE_WRITE_FUNCTION

#endif // __OPENCL_C_VERSION__

