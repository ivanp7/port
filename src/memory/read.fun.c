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
 * @brief Memory read operations.
 */

#include "port/memory/read.fun.h"
#include "port/memory.def.h"
#include "port/types.def.h"
#include "port/vector.def.h"

#ifndef __OPENCL_C_VERSION__
#  include "port/float.fun.h" // for port_convert_*()
#  include <assert.h>
#endif

#ifdef __OPENCL_C_VERSION__
#  define ASSERT_MEMORY
#else
#  define ASSERT_MEMORY assert(memory != NULL)
#endif

///////////////////////////////////////////////////////////////////////////////
// Reading from memory (scalars)
///////////////////////////////////////////////////////////////////////////////

typedef port_constant_memory_ptr_t port_const_constant_memory_ptr_t; // workaround needed for macros regularity

#define PORT_DEFINE_MEMORY_READ_FUNCTION_SCALAR_SUB(name, value_type, addrspace, subunit_size, unit_field) \
value_type name(port_const_##addrspace##_memory_ptr_t memory, port_uint8_t offset) {    \
    ASSERT_MEMORY;                                                                      \
    memory += offset >> (PORT_TYPE_LOGSIZE_SINGLE - subunit_size);                      \
    offset &= (1 << (PORT_TYPE_LOGSIZE_SINGLE - subunit_size)) - 1;                     \
    return memory->unit_field[offset]; }

#define PORT_DEFINE_MEMORY_READ_FUNCTION_SCALAR_SINGLE(name, value_type, addrspace, unit_field) \
value_type name(port_const_##addrspace##_memory_ptr_t memory, port_uint8_t offset) {    \
    ASSERT_MEMORY;                                                                      \
    memory += offset;                                                                   \
    return memory->unit_field; }

#define PORT_DEFINE_MEMORY_READ_FUNCTION_SCALAR_DOUBLE(name, value_type, addrspace, unit_field) \
value_type name(port_const_##addrspace##_memory_ptr_t memory, port_uint8_t offset) {    \
    ASSERT_MEMORY;                                                                      \
    memory += offset;                                                                   \
    memory += offset;                                                                   \
    port_memory_unit_double_t u = {.as_unit = {memory[0], memory[1]}};                 \
    return u.unit_field; }

#ifdef __OPENCL_C_VERSION__

#  define PORT_DEFINE_MEMORY_READ_FUNCTION_SCALAR_FLOAT16(name, addrspace) \
port_float32_t name(port_const_##addrspace##_memory_ptr_t memory, port_uint8_t offset) {    \
    memory += offset >> 1;                                                                  \
    offset &= 1;                                                                            \
    return vload_half(offset, (const __##addrspace half*)memory); }

#else // __OPENCL_C_VERSION__

#  define PORT_DEFINE_MEMORY_READ_FUNCTION_SCALAR_FLOAT16(name, addrspace) \
port_float32_t name(port_const_##addrspace##_memory_ptr_t memory, port_uint8_t offset) {    \
    ASSERT_MEMORY;                                                                          \
    memory += offset >> 1;                                                                  \
    offset &= 1;                                                                            \
    return port_convert_float16_to_float32(memory->PORT_MEMORY_UNIT__AS_FLOAT_HALF[offset]); }

#endif // __OPENCL_C_VERSION__

#define PORT_DEFINE_MEMORY_READ_FUNCTIONS_SCALAR_SUB(value_type, subunit_size, unit_field)  \
    PORT_DEFINE_MEMORY_READ_FUNCTION_SCALAR_SUB(port_memory_read_global_##value_type,       \
            port_##value_type##_t, global, subunit_size, unit_field)                        \
    PORT_DEFINE_MEMORY_READ_FUNCTION_SCALAR_SUB(port_memory_read_constant_##value_type,     \
            port_##value_type##_t, constant, subunit_size, unit_field)                      \
    PORT_DEFINE_MEMORY_READ_FUNCTION_SCALAR_SUB(port_memory_read_local_##value_type,        \
            port_##value_type##_t, local, subunit_size, unit_field)                         \
    PORT_DEFINE_MEMORY_READ_FUNCTION_SCALAR_SUB(port_memory_read_private_##value_type,      \
            port_##value_type##_t, private, subunit_size, unit_field)

#define PORT_DEFINE_MEMORY_READ_FUNCTIONS_SCALAR_SINGLE(value_type, unit_field)             \
    PORT_DEFINE_MEMORY_READ_FUNCTION_SCALAR_SINGLE(port_memory_read_global_##value_type,    \
            port_##value_type##_t, global, unit_field)                                      \
    PORT_DEFINE_MEMORY_READ_FUNCTION_SCALAR_SINGLE(port_memory_read_constant_##value_type,  \
            port_##value_type##_t, constant, unit_field)                                    \
    PORT_DEFINE_MEMORY_READ_FUNCTION_SCALAR_SINGLE(port_memory_read_local_##value_type,     \
            port_##value_type##_t, local, unit_field)                                       \
    PORT_DEFINE_MEMORY_READ_FUNCTION_SCALAR_SINGLE(port_memory_read_private_##value_type,   \
            port_##value_type##_t, private, unit_field)

#define PORT_DEFINE_MEMORY_READ_FUNCTIONS_SCALAR_DOUBLE(value_type, unit_field)             \
    PORT_DEFINE_MEMORY_READ_FUNCTION_SCALAR_DOUBLE(port_memory_read_global_##value_type,    \
            port_##value_type##_t, global, unit_field)                                      \
    PORT_DEFINE_MEMORY_READ_FUNCTION_SCALAR_DOUBLE(port_memory_read_constant_##value_type,  \
            port_##value_type##_t, constant, unit_field)                                    \
    PORT_DEFINE_MEMORY_READ_FUNCTION_SCALAR_DOUBLE(port_memory_read_local_##value_type,     \
            port_##value_type##_t, local, unit_field)                                       \
    PORT_DEFINE_MEMORY_READ_FUNCTION_SCALAR_DOUBLE(port_memory_read_private_##value_type,   \
            port_##value_type##_t, private, unit_field)

#define PORT_DEFINE_MEMORY_READ_FUNCTIONS_SCALAR_FLOAT16()                                          \
    PORT_DEFINE_MEMORY_READ_FUNCTION_SCALAR_FLOAT16(port_memory_read_global_float16, global)        \
    PORT_DEFINE_MEMORY_READ_FUNCTION_SCALAR_FLOAT16(port_memory_read_constant_float16, constant)    \
    PORT_DEFINE_MEMORY_READ_FUNCTION_SCALAR_FLOAT16(port_memory_read_local_float16, local)          \
    PORT_DEFINE_MEMORY_READ_FUNCTION_SCALAR_FLOAT16(port_memory_read_private_float16, private)

PORT_DEFINE_MEMORY_READ_FUNCTIONS_SCALAR_SUB(uint8, PORT_TYPE_LOGSIZE_QUARTER, as_uint_quarter)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_SCALAR_SUB(uint16, PORT_TYPE_LOGSIZE_HALF, as_uint_half)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_SCALAR_SINGLE(uint32, as_uint_single)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_SCALAR_DOUBLE(uint64, as_uint_double)

PORT_DEFINE_MEMORY_READ_FUNCTIONS_SCALAR_SUB(sint8, PORT_TYPE_LOGSIZE_QUARTER, as_sint_quarter)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_SCALAR_SUB(sint16, PORT_TYPE_LOGSIZE_HALF, as_sint_half)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_SCALAR_SINGLE(sint32, as_sint_single)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_SCALAR_DOUBLE(sint64, as_sint_double)

PORT_DEFINE_MEMORY_READ_FUNCTIONS_SCALAR_FLOAT16()
PORT_DEFINE_MEMORY_READ_FUNCTIONS_SCALAR_SINGLE(float32, as_float_single)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_SCALAR_DOUBLE(float64, as_float_double)

PORT_DEFINE_MEMORY_READ_FUNCTIONS_SCALAR_SUB(memory_ref_quarter, PORT_TYPE_LOGSIZE_QUARTER, as_ref_quarter)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_SCALAR_SUB(memory_ref_half, PORT_TYPE_LOGSIZE_HALF, as_ref_half)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_SCALAR_SINGLE(memory_ref, as_ref)

#undef PORT_DEFINE_MEMORY_READ_FUNCTIONS_SCALAR_SUB
#undef PORT_DEFINE_MEMORY_READ_FUNCTIONS_SCALAR_SINGLE
#undef PORT_DEFINE_MEMORY_READ_FUNCTIONS_SCALAR_DOUBLE
#undef PORT_DEFINE_MEMORY_READ_FUNCTIONS_SCALAR_FLOAT16
#undef PORT_DEFINE_MEMORY_READ_FUNCTION_SCALAR_SUB
#undef PORT_DEFINE_MEMORY_READ_FUNCTION_SCALAR_SINGLE
#undef PORT_DEFINE_MEMORY_READ_FUNCTION_SCALAR_DOUBLE
#undef PORT_DEFINE_MEMORY_READ_FUNCTION_SCALAR_FLOAT16

///////////////////////////////////////////////////////////////////////////////
// Reading from memory (vectors)
///////////////////////////////////////////////////////////////////////////////

#ifdef __OPENCL_C_VERSION__

#  define PORT_DEFINE_MEMORY_READ_FUNCTION_VECTOR_SUB(name, vector_type, element_type, vector_length, \
        addrspace, subunit_size, unit_field) \
vector_type name(port_const_##addrspace##_memory_ptr_t memory, port_uint8_t offset) { \
    return vload##vector_length(0, (const __##addrspace element_type*)memory + offset); }

#  define PORT_DEFINE_MEMORY_READ_FUNCTION_VECTOR_SINGLE(name, vector_type, element_type, vector_length, \
        addrspace, unit_field) \
    PORT_DEFINE_MEMORY_READ_FUNCTION_VECTOR_SUB(name, vector_type, element_type, vector_length, addrspace, 0, unit_field)

#  define PORT_DEFINE_MEMORY_READ_FUNCTION_VECTOR_DOUBLE(name, vector_type, element_type, vector_length, \
        addrspace, unit_field) \
vector_type name(port_const_##addrspace##_memory_ptr_t memory, port_uint8_t offset) { \
    memory += offset;                                                               \
    memory += offset;                                                               \
    if (((uintptr_t)memory & (sizeof(element_type) - 1)) == 0)                      \
        return vload##vector_length(0, (const __##addrspace element_type*)memory);  \
    else {                                                                          \
        vector_type vector;                                                         \
        for (port_uint8_t i = 0; i < vector_length; i++) {                          \
            port_memory_unit_double_t u = {.as_unit = {memory[0], memory[1]}};     \
            memory += 2;                                                            \
            PORT_V##vector_length##_SET_ELT(vector, i, u.unit_field); }             \
        return vector; } }

#  define PORT_DEFINE_MEMORY_READ_FUNCTION_VECTOR_FLOAT16(name, vector_length, addrspace) \
port_float32_v##vector_length##_t name(port_const_##addrspace##_memory_ptr_t memory, port_uint8_t offset) { \
    return vload_half##vector_length(0, (const __##addrspace half*)memory + offset); }

#else // __OPENCL_C_VERSION__

#  define PORT_DEFINE_MEMORY_READ_FUNCTION_VECTOR_SUB(name, vector_type, element_type, vector_length, \
        addrspace, subunit_size, unit_field) \
vector_type name(port_const_##addrspace##_memory_ptr_t memory, port_uint8_t offset) { \
    ASSERT_MEMORY;                                                      \
    vector_type vector;                                                 \
    for (port_uint8_t i = 0; i < vector_length; i++) {                  \
        memory += offset >> (PORT_TYPE_LOGSIZE_SINGLE - subunit_size);  \
        offset &= (1 << (PORT_TYPE_LOGSIZE_SINGLE - subunit_size)) - 1; \
        vector.s[i] = memory->unit_field[offset++]; }                   \
    return vector; }

#  define PORT_DEFINE_MEMORY_READ_FUNCTION_VECTOR_SINGLE(name, vector_type, element_type, vector_length, \
        addrspace, unit_field) \
vector_type name(port_const_##addrspace##_memory_ptr_t memory, port_uint8_t offset) { \
    ASSERT_MEMORY;                                          \
    memory += offset;                                       \
    vector_type vector;                                     \
    for (port_uint8_t i = 0; i < vector_length; i++) {      \
        vector.s[i] = (memory++)->unit_field; }             \
    return vector; }

#  define PORT_DEFINE_MEMORY_READ_FUNCTION_VECTOR_DOUBLE(name, vector_type, element_type, vector_length, \
        addrspace, unit_field) \
vector_type name(port_const_##addrspace##_memory_ptr_t memory, port_uint8_t offset) { \
    ASSERT_MEMORY;                                                          \
    memory += offset;                                                       \
    memory += offset;                                                       \
    vector_type vector;                                                     \
    for (port_uint8_t i = 0; i < vector_length; i++) {                      \
        port_memory_unit_double_t u = {.as_unit = {memory[0], memory[1]}}; \
        memory += 2;                                                        \
        vector.s[i] = u.unit_field; }                                       \
    return vector; }

#  define PORT_DEFINE_MEMORY_READ_FUNCTION_VECTOR_FLOAT16(name, vector_length, addrspace) \
port_float32_v##vector_length##_t name(port_const_##addrspace##_memory_ptr_t memory, port_uint8_t offset) { \
    ASSERT_MEMORY;                                                                          \
    port_float32_v##vector_length##_t vector;                                               \
    for (port_uint8_t i = 0; i < vector_length; i++) {                                      \
        memory += offset >> 1;                                                              \
        offset &= 1;                                                                        \
        vector.s[i] = port_convert_float16_to_float32(memory->PORT_MEMORY_UNIT__AS_FLOAT_HALF[offset++]); }   \
    return vector; }

#endif // __OPENCL_C_VERSION__

#define PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SUB(value_type, vector_length, subunit_size, unit_field)   \
    PORT_DEFINE_MEMORY_READ_FUNCTION_VECTOR_SUB(port_memory_read_global_##value_type##_v##vector_length,    \
            port_##value_type##_v##vector_length##_t, port_##value_type##_t, vector_length, global,         \
            subunit_size, unit_field)                                                                       \
    PORT_DEFINE_MEMORY_READ_FUNCTION_VECTOR_SUB(port_memory_read_constant_##value_type##_v##vector_length,  \
            port_##value_type##_v##vector_length##_t, port_##value_type##_t, vector_length, constant,       \
            subunit_size, unit_field)                                                                       \
    PORT_DEFINE_MEMORY_READ_FUNCTION_VECTOR_SUB(port_memory_read_local_##value_type##_v##vector_length,     \
            port_##value_type##_v##vector_length##_t, port_##value_type##_t, vector_length, local,          \
            subunit_size, unit_field)                                                                       \
    PORT_DEFINE_MEMORY_READ_FUNCTION_VECTOR_SUB(port_memory_read_private_##value_type##_v##vector_length,   \
            port_##value_type##_v##vector_length##_t, port_##value_type##_t, vector_length, private,        \
            subunit_size, unit_field)

#define PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SINGLE(value_type, vector_length, unit_field)                      \
    PORT_DEFINE_MEMORY_READ_FUNCTION_VECTOR_SINGLE(port_memory_read_global_##value_type##_v##vector_length,         \
            port_##value_type##_v##vector_length##_t, port_##value_type##_t, vector_length, global, unit_field)     \
    PORT_DEFINE_MEMORY_READ_FUNCTION_VECTOR_SINGLE(port_memory_read_constant_##value_type##_v##vector_length,       \
            port_##value_type##_v##vector_length##_t, port_##value_type##_t, vector_length, constant, unit_field)   \
    PORT_DEFINE_MEMORY_READ_FUNCTION_VECTOR_SINGLE(port_memory_read_local_##value_type##_v##vector_length,          \
            port_##value_type##_v##vector_length##_t, port_##value_type##_t, vector_length, local, unit_field)      \
    PORT_DEFINE_MEMORY_READ_FUNCTION_VECTOR_SINGLE(port_memory_read_private_##value_type##_v##vector_length,        \
            port_##value_type##_v##vector_length##_t, port_##value_type##_t, vector_length, private, unit_field)

#define PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_DOUBLE(value_type, vector_length, unit_field)                      \
    PORT_DEFINE_MEMORY_READ_FUNCTION_VECTOR_DOUBLE(port_memory_read_global_##value_type##_v##vector_length,         \
            port_##value_type##_v##vector_length##_t, port_##value_type##_t, vector_length, global, unit_field)     \
    PORT_DEFINE_MEMORY_READ_FUNCTION_VECTOR_DOUBLE(port_memory_read_constant_##value_type##_v##vector_length,       \
            port_##value_type##_v##vector_length##_t, port_##value_type##_t, vector_length, constant, unit_field)   \
    PORT_DEFINE_MEMORY_READ_FUNCTION_VECTOR_DOUBLE(port_memory_read_local_##value_type##_v##vector_length,          \
            port_##value_type##_v##vector_length##_t, port_##value_type##_t, vector_length, local, unit_field)      \
    PORT_DEFINE_MEMORY_READ_FUNCTION_VECTOR_DOUBLE(port_memory_read_private_##value_type##_v##vector_length,        \
            port_##value_type##_v##vector_length##_t, port_##value_type##_t, vector_length, private, unit_field)

#define PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_FLOAT16(vector_length)                                 \
    PORT_DEFINE_MEMORY_READ_FUNCTION_VECTOR_FLOAT16(port_memory_read_global_float16_v##vector_length,   \
            vector_length, global)                                                                      \
    PORT_DEFINE_MEMORY_READ_FUNCTION_VECTOR_FLOAT16(port_memory_read_constant_float16_v##vector_length, \
            vector_length, constant)                                                                    \
    PORT_DEFINE_MEMORY_READ_FUNCTION_VECTOR_FLOAT16(port_memory_read_local_float16_v##vector_length,    \
            vector_length, local)                                                                       \
    PORT_DEFINE_MEMORY_READ_FUNCTION_VECTOR_FLOAT16(port_memory_read_private_float16_v##vector_length,  \
            vector_length, private)

PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SUB(uint8, 2, PORT_TYPE_LOGSIZE_QUARTER, as_uint_quarter)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SUB(uint8, 3, PORT_TYPE_LOGSIZE_QUARTER, as_uint_quarter)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SUB(uint8, 4, PORT_TYPE_LOGSIZE_QUARTER, as_uint_quarter)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SUB(uint8, 8, PORT_TYPE_LOGSIZE_QUARTER, as_uint_quarter)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SUB(uint8, 16, PORT_TYPE_LOGSIZE_QUARTER, as_uint_quarter)

PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SUB(uint16, 2, PORT_TYPE_LOGSIZE_HALF, as_uint_half)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SUB(uint16, 3, PORT_TYPE_LOGSIZE_HALF, as_uint_half)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SUB(uint16, 4, PORT_TYPE_LOGSIZE_HALF, as_uint_half)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SUB(uint16, 8, PORT_TYPE_LOGSIZE_HALF, as_uint_half)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SUB(uint16, 16, PORT_TYPE_LOGSIZE_HALF, as_uint_half)

PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SINGLE(uint32, 2, as_uint_single)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SINGLE(uint32, 3, as_uint_single)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SINGLE(uint32, 4, as_uint_single)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SINGLE(uint32, 8, as_uint_single)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SINGLE(uint32, 16, as_uint_single)

PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_DOUBLE(uint64, 2, as_uint_double)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_DOUBLE(uint64, 3, as_uint_double)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_DOUBLE(uint64, 4, as_uint_double)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_DOUBLE(uint64, 8, as_uint_double)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_DOUBLE(uint64, 16, as_uint_double)

PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SUB(sint8, 2, PORT_TYPE_LOGSIZE_QUARTER, as_sint_quarter)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SUB(sint8, 3, PORT_TYPE_LOGSIZE_QUARTER, as_sint_quarter)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SUB(sint8, 4, PORT_TYPE_LOGSIZE_QUARTER, as_sint_quarter)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SUB(sint8, 8, PORT_TYPE_LOGSIZE_QUARTER, as_sint_quarter)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SUB(sint8, 16, PORT_TYPE_LOGSIZE_QUARTER, as_sint_quarter)

PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SUB(sint16, 2, PORT_TYPE_LOGSIZE_HALF, as_sint_half)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SUB(sint16, 3, PORT_TYPE_LOGSIZE_HALF, as_sint_half)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SUB(sint16, 4, PORT_TYPE_LOGSIZE_HALF, as_sint_half)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SUB(sint16, 8, PORT_TYPE_LOGSIZE_HALF, as_sint_half)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SUB(sint16, 16, PORT_TYPE_LOGSIZE_HALF, as_sint_half)

PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SINGLE(sint32, 2, as_sint_single)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SINGLE(sint32, 3, as_sint_single)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SINGLE(sint32, 4, as_sint_single)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SINGLE(sint32, 8, as_sint_single)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SINGLE(sint32, 16, as_sint_single)

PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_DOUBLE(sint64, 2, as_sint_double)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_DOUBLE(sint64, 3, as_sint_double)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_DOUBLE(sint64, 4, as_sint_double)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_DOUBLE(sint64, 8, as_sint_double)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_DOUBLE(sint64, 16, as_sint_double)

PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_FLOAT16(2)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_FLOAT16(3)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_FLOAT16(4)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_FLOAT16(8)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_FLOAT16(16)

PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SINGLE(float32, 2, as_float_single)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SINGLE(float32, 3, as_float_single)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SINGLE(float32, 4, as_float_single)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SINGLE(float32, 8, as_float_single)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SINGLE(float32, 16, as_float_single)

PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_DOUBLE(float64, 2, as_float_double)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_DOUBLE(float64, 3, as_float_double)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_DOUBLE(float64, 4, as_float_double)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_DOUBLE(float64, 8, as_float_double)
PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_DOUBLE(float64, 16, as_float_double)

#undef PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SUB
#undef PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_SINGLE
#undef PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_DOUBLE
#undef PORT_DEFINE_MEMORY_READ_FUNCTIONS_VECTOR_FLOAT16
#undef PORT_DEFINE_MEMORY_READ_FUNCTION_VECTOR_SUB
#undef PORT_DEFINE_MEMORY_READ_FUNCTION_VECTOR_SINGLE
#undef PORT_DEFINE_MEMORY_READ_FUNCTION_VECTOR_DOUBLE
#undef PORT_DEFINE_MEMORY_READ_FUNCTION_VECTOR_FLOAT16

