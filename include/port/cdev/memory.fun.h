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

#pragma once
#ifndef _PORT_CDEV_MEMORY_FUN_H_
#define _PORT_CDEV_MEMORY_FUN_H_

#include "port/cdev/memory.typ.h"

///////////////////////////////////////////////////////////////////////////////
// Memory reference
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Follow memory reference.
 *
 * See description of PORT_MEMORY_REFERENCE().
 *
 * @return Pointer to referenced memory.
 */
port_const_global_memory_ptr_t
port_memory_reference(
        port_memory_ref_t ref, ///< [in] Memory reference.

        port_uint8_t num_idx_bits, ///< [in] Number of index bits in far memory reference.
        port_uint8_t offset_shift, ///< [in] Argument for offset left shift in far memory reference.

        port_const_global_memory_ptr_t base_ptr, ///< [in] Base address for near references.
        port_memory_table_t memory_table ///< [in] Table of memory pointers for far references.
);

///////////////////////////////////////////////////////////////////////////////
// Memory copying
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Copy memory units from global memory to private memory.
 */
void
port_memory_copy_global_to_private(
        port_private_memory_ptr_t restrict dest, ///< [out] Destination.
        port_const_global_memory_ptr_t restrict src, ///< [in] Source.
        port_size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from constant memory to private memory.
 */
void
port_memory_copy_constant_to_private(
        port_private_memory_ptr_t restrict dest, ///< [out] Destination.
        port_constant_memory_ptr_t restrict src, ///< [in] Source.
        port_size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from local memory to private memory.
 */
void
port_memory_copy_local_to_private(
        port_private_memory_ptr_t restrict dest, ///< [out] Destination.
        port_const_local_memory_ptr_t restrict src, ///< [in] Source.
        port_size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from private memory to private memory.
 */
void
port_memory_copy_private_to_private(
        port_private_memory_ptr_t restrict dest, ///< [out] Destination.
        port_const_private_memory_ptr_t restrict src, ///< [in] Source.
        port_size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from global memory to local memory.
 */
void
port_memory_copy_global_to_local(
        port_local_memory_ptr_t restrict dest, ///< [out] Destination.
        port_const_global_memory_ptr_t restrict src, ///< [in] Source.
        port_size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from constant memory to local memory.
 */
void
port_memory_copy_constant_to_local(
        port_local_memory_ptr_t restrict dest, ///< [out] Destination.
        port_constant_memory_ptr_t restrict src, ///< [in] Source.
        port_size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from local memory to local memory.
 */
void
port_memory_copy_local_to_local(
        port_local_memory_ptr_t restrict dest, ///< [out] Destination.
        port_const_local_memory_ptr_t restrict src, ///< [in] Source.
        port_size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from private memory to local memory.
 */
void
port_memory_copy_private_to_local(
        port_local_memory_ptr_t restrict dest, ///< [out] Destination.
        port_const_private_memory_ptr_t restrict src, ///< [in] Source.
        port_size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from global memory to global memory.
 */
void
port_memory_copy_global_to_global(
        port_global_memory_ptr_t restrict dest, ///< [out] Destination.
        port_const_global_memory_ptr_t restrict src, ///< [in] Source.
        port_size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from local memory to global memory.
 */
void
port_memory_copy_local_to_global(
        port_global_memory_ptr_t restrict dest, ///< [out] Destination.
        port_const_local_memory_ptr_t restrict src, ///< [in] Source.
        port_size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from constant memory to global memory.
 */
void
port_memory_copy_constant_to_global(
        port_global_memory_ptr_t restrict dest, ///< [out] Destination.
        port_constant_memory_ptr_t restrict src, ///< [in] Source.
        port_size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from private memory to global memory.
 */
void
port_memory_copy_private_to_global(
        port_global_memory_ptr_t restrict dest, ///< [out] Destination.
        port_const_private_memory_ptr_t restrict src, ///< [in] Source.
        port_size_t num_units ///< [in] Number of units to copy.
);

///////////////////////////////////////////////////////////////////////////////
// Reading from memory
///////////////////////////////////////////////////////////////////////////////

#define PORT_DECLARE_MEMORY_READ_FUNCTION(name, value_type, memory_type) \
    value_type name(memory_type memory, port_uint8_t offset)

#define PORT_DECLARE_MEMORY_READ_FUNCTIONS(value_type) \
    PORT_DECLARE_MEMORY_READ_FUNCTION(port_memory_read_global_##value_type,   \
            port_##value_type##_t, port_const_global_memory_ptr_t);           \
    PORT_DECLARE_MEMORY_READ_FUNCTION(port_memory_read_constant_##value_type, \
            port_##value_type##_t, port_constant_memory_ptr_t);               \
    PORT_DECLARE_MEMORY_READ_FUNCTION(port_memory_read_local_##value_type,    \
            port_##value_type##_t, port_const_local_memory_ptr_t);            \
    PORT_DECLARE_MEMORY_READ_FUNCTION(port_memory_read_private_##value_type,  \
            port_##value_type##_t, port_const_private_memory_ptr_t);

#define PORT_DECLARE_MEMORY_READ_FUNCTIONS_FLOAT16(value_type) \
    PORT_DECLARE_MEMORY_READ_FUNCTION(port_memory_read_global_float16##value_type,   \
            port_float32##value_type##_t, port_const_global_memory_ptr_t);           \
    PORT_DECLARE_MEMORY_READ_FUNCTION(port_memory_read_constant_float16##value_type, \
            port_float32##value_type##_t, port_constant_memory_ptr_t);               \
    PORT_DECLARE_MEMORY_READ_FUNCTION(port_memory_read_local_float16##value_type,    \
            port_float32##value_type##_t, port_const_local_memory_ptr_t);            \
    PORT_DECLARE_MEMORY_READ_FUNCTION(port_memory_read_private_float16##value_type,  \
            port_float32##value_type##_t, port_const_private_memory_ptr_t);

// Unsigned integers
PORT_DECLARE_MEMORY_READ_FUNCTIONS(uint8)     // Unsigned 8-bit integer (scalar)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(uint8_v2)  // Unsigned 8-bit integer (2-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(uint8_v3)  // Unsigned 8-bit integer (3-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(uint8_v4)  // Unsigned 8-bit integer (4-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(uint8_v8)  // Unsigned 8-bit integer (8-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(uint8_v16) // Unsigned 8-bit integer (16-vector)

PORT_DECLARE_MEMORY_READ_FUNCTIONS(uint16)     // Unsigned 16-bit integer (scalar)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(uint16_v2)  // Unsigned 16-bit integer (2-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(uint16_v3)  // Unsigned 16-bit integer (3-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(uint16_v4)  // Unsigned 16-bit integer (4-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(uint16_v8)  // Unsigned 16-bit integer (8-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(uint16_v16) // Unsigned 16-bit integer (16-vector)

PORT_DECLARE_MEMORY_READ_FUNCTIONS(uint32)     // Unsigned 32-bit integer (scalar)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(uint32_v2)  // Unsigned 32-bit integer (2-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(uint32_v3)  // Unsigned 32-bit integer (3-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(uint32_v4)  // Unsigned 32-bit integer (4-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(uint32_v8)  // Unsigned 32-bit integer (8-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(uint32_v16) // Unsigned 32-bit integer (16-vector)

PORT_DECLARE_MEMORY_READ_FUNCTIONS(uint64)     // Unsigned 64-bit integer (scalar)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(uint64_v2)  // Unsigned 64-bit integer (2-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(uint64_v3)  // Unsigned 64-bit integer (3-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(uint64_v4)  // Unsigned 64-bit integer (4-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(uint64_v8)  // Unsigned 64-bit integer (8-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(uint64_v16) // Unsigned 64-bit integer (16-vector)

// Signed integers
PORT_DECLARE_MEMORY_READ_FUNCTIONS(sint8)     // Signed 8-bit integer (scalar)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(sint8_v2)  // Signed 8-bit integer (2-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(sint8_v3)  // Signed 8-bit integer (3-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(sint8_v4)  // Signed 8-bit integer (4-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(sint8_v8)  // Signed 8-bit integer (8-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(sint8_v16) // Signed 8-bit integer (16-vector)

PORT_DECLARE_MEMORY_READ_FUNCTIONS(sint16)     // Signed 16-bit integer (scalar)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(sint16_v2)  // Signed 16-bit integer (2-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(sint16_v3)  // Signed 16-bit integer (3-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(sint16_v4)  // Signed 16-bit integer (4-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(sint16_v8)  // Signed 16-bit integer (8-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(sint16_v16) // Signed 16-bit integer (16-vector)

PORT_DECLARE_MEMORY_READ_FUNCTIONS(sint32)     // Signed 32-bit integer (scalar)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(sint32_v2)  // Signed 32-bit integer (2-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(sint32_v3)  // Signed 32-bit integer (3-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(sint32_v4)  // Signed 32-bit integer (4-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(sint32_v8)  // Signed 32-bit integer (8-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(sint32_v16) // Signed 32-bit integer (16-vector)

PORT_DECLARE_MEMORY_READ_FUNCTIONS(sint64)     // Signed 64-bit integer (scalar)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(sint64_v2)  // Signed 64-bit integer (2-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(sint64_v3)  // Signed 64-bit integer (3-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(sint64_v4)  // Signed 64-bit integer (4-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(sint64_v8)  // Signed 64-bit integer (8-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(sint64_v16) // Signed 64-bit integer (16-vector)

// Floating-point numbers
PORT_DECLARE_MEMORY_READ_FUNCTIONS_FLOAT16()     // 16-bit floating-point number (scalar)
PORT_DECLARE_MEMORY_READ_FUNCTIONS_FLOAT16(_v2)  // 16-bit floating-point number (2-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS_FLOAT16(_v3)  // 16-bit floating-point number (3-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS_FLOAT16(_v4)  // 16-bit floating-point number (4-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS_FLOAT16(_v8)  // 16-bit floating-point number (8-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS_FLOAT16(_v16) // 16-bit floating-point number (16-vector)

PORT_DECLARE_MEMORY_READ_FUNCTIONS(float32)     // 32-bit floating-point number (scalar)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(float32_v2)  // 32-bit floating-point number (2-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(float32_v3)  // 32-bit floating-point number (3-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(float32_v4)  // 32-bit floating-point number (4-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(float32_v8)  // 32-bit floating-point number (8-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(float32_v16) // 32-bit floating-point number (16-vector)

PORT_DECLARE_MEMORY_READ_FUNCTIONS(float64)     // 64-bit floating-point number (scalar)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(float64_v2)  // 64-bit floating-point number (2-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(float64_v3)  // 64-bit floating-point number (3-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(float64_v4)  // 64-bit floating-point number (4-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(float64_v8)  // 64-bit floating-point number (8-vector)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(float64_v16) // 64-bit floating-point number (16-vector)

// Memory references
PORT_DECLARE_MEMORY_READ_FUNCTIONS(memory_ref_quarter) // Memory reference (quarter size)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(memory_ref_half)    // Memory reference (half size)
PORT_DECLARE_MEMORY_READ_FUNCTIONS(memory_ref)         // Memory reference (single size)

#undef PORT_DECLARE_MEMORY_READ_FUNCTIONS_FLOAT16
#undef PORT_DECLARE_MEMORY_READ_FUNCTIONS
#undef PORT_DECLARE_MEMORY_READ_FUNCTION

// Unsigned integer (quarter size)
#define port_memory_read_global_uint_quarter port_memory_read_global_uint8
#define port_memory_read_constant_uint_quarter port_memory_read_constant_uint8
#define port_memory_read_local_uint_quarter port_memory_read_local_uint8
#define port_memory_read_private_uint_quarter port_memory_read_private_uint8

// 2-vector of unsigned integers (quarter size)
#define port_memory_read_global_uint_quarter_v2 port_memory_read_global_uint8_v2
#define port_memory_read_constant_uint_quarter_v2 port_memory_read_constant_uint8_v2
#define port_memory_read_local_uint_quarter_v2 port_memory_read_local_uint8_v2
#define port_memory_read_private_uint_quarter_v2 port_memory_read_private_uint8_v2

// 3-vector of unsigned integers (quarter size)
#define port_memory_read_global_uint_quarter_v3 port_memory_read_global_uint8_v3
#define port_memory_read_constant_uint_quarter_v3 port_memory_read_constant_uint8_v3
#define port_memory_read_local_uint_quarter_v3 port_memory_read_local_uint8_v3
#define port_memory_read_private_uint_quarter_v3 port_memory_read_private_uint8_v3

// 4-vector of unsigned integers (quarter size)
#define port_memory_read_global_uint_quarter_v4 port_memory_read_global_uint8_v4
#define port_memory_read_constant_uint_quarter_v4 port_memory_read_constant_uint8_v4
#define port_memory_read_local_uint_quarter_v4 port_memory_read_local_uint8_v4
#define port_memory_read_private_uint_quarter_v4 port_memory_read_private_uint8_v4

// 8-vector of unsigned integers (quarter size)
#define port_memory_read_global_uint_quarter_v8 port_memory_read_global_uint8_v8
#define port_memory_read_constant_uint_quarter_v8 port_memory_read_constant_uint8_v8
#define port_memory_read_local_uint_quarter_v8 port_memory_read_local_uint8_v8
#define port_memory_read_private_uint_quarter_v8 port_memory_read_private_uint8_v8

// 16-vector of unsigned integers (quarter size)
#define port_memory_read_global_uint_quarter_v16 port_memory_read_global_uint8_v16
#define port_memory_read_constant_uint_quarter_v16 port_memory_read_constant_uint8_v16
#define port_memory_read_local_uint_quarter_v16 port_memory_read_local_uint8_v16
#define port_memory_read_private_uint_quarter_v16 port_memory_read_private_uint8_v16

// Unsigned integer (half size)
#define port_memory_read_global_uint_half port_memory_read_global_uint16
#define port_memory_read_constant_uint_half port_memory_read_constant_uint16
#define port_memory_read_local_uint_half port_memory_read_local_uint16
#define port_memory_read_private_uint_half port_memory_read_private_uint16

// 2-vector of unsigned integers (half size)
#define port_memory_read_global_uint_half_v2 port_memory_read_global_uint16_v2
#define port_memory_read_constant_uint_half_v2 port_memory_read_constant_uint16_v2
#define port_memory_read_local_uint_half_v2 port_memory_read_local_uint16_v2
#define port_memory_read_private_uint_half_v2 port_memory_read_private_uint16_v2

// 3-vector of unsigned integers (half size)
#define port_memory_read_global_uint_half_v3 port_memory_read_global_uint16_v3
#define port_memory_read_constant_uint_half_v3 port_memory_read_constant_uint16_v3
#define port_memory_read_local_uint_half_v3 port_memory_read_local_uint16_v3
#define port_memory_read_private_uint_half_v3 port_memory_read_private_uint16_v3

// 4-vector of unsigned integers (half size)
#define port_memory_read_global_uint_half_v4 port_memory_read_global_uint16_v4
#define port_memory_read_constant_uint_half_v4 port_memory_read_constant_uint16_v4
#define port_memory_read_local_uint_half_v4 port_memory_read_local_uint16_v4
#define port_memory_read_private_uint_half_v4 port_memory_read_private_uint16_v4

// 8-vector of unsigned integers (half size)
#define port_memory_read_global_uint_half_v8 port_memory_read_global_uint16_v8
#define port_memory_read_constant_uint_half_v8 port_memory_read_constant_uint16_v8
#define port_memory_read_local_uint_half_v8 port_memory_read_local_uint16_v8
#define port_memory_read_private_uint_half_v8 port_memory_read_private_uint16_v8

// 16-vector of unsigned integers (half size)
#define port_memory_read_global_uint_half_v16 port_memory_read_global_uint16_v16
#define port_memory_read_constant_uint_half_v16 port_memory_read_constant_uint16_v16
#define port_memory_read_local_uint_half_v16 port_memory_read_local_uint16_v16
#define port_memory_read_private_uint_half_v16 port_memory_read_private_uint16_v16

// Unsigned integer (single size)
#define port_memory_read_global_uint_single port_memory_read_global_uint32
#define port_memory_read_constant_uint_single port_memory_read_constant_uint32
#define port_memory_read_local_uint_single port_memory_read_local_uint32
#define port_memory_read_private_uint_single port_memory_read_private_uint32

// 2-vector of unsigned integers (single size)
#define port_memory_read_global_uint_single_v2 port_memory_read_global_uint32_v2
#define port_memory_read_constant_uint_single_v2 port_memory_read_constant_uint32_v2
#define port_memory_read_local_uint_single_v2 port_memory_read_local_uint32_v2
#define port_memory_read_private_uint_single_v2 port_memory_read_private_uint32_v2

// 3-vector of unsigned integers (single size)
#define port_memory_read_global_uint_single_v3 port_memory_read_global_uint32_v3
#define port_memory_read_constant_uint_single_v3 port_memory_read_constant_uint32_v3
#define port_memory_read_local_uint_single_v3 port_memory_read_local_uint32_v3
#define port_memory_read_private_uint_single_v3 port_memory_read_private_uint32_v3

// 4-vector of unsigned integers (single size)
#define port_memory_read_global_uint_single_v4 port_memory_read_global_uint32_v4
#define port_memory_read_constant_uint_single_v4 port_memory_read_constant_uint32_v4
#define port_memory_read_local_uint_single_v4 port_memory_read_local_uint32_v4
#define port_memory_read_private_uint_single_v4 port_memory_read_private_uint32_v4

// 8-vector of unsigned integers (single size)
#define port_memory_read_global_uint_single_v8 port_memory_read_global_uint32_v8
#define port_memory_read_constant_uint_single_v8 port_memory_read_constant_uint32_v8
#define port_memory_read_local_uint_single_v8 port_memory_read_local_uint32_v8
#define port_memory_read_private_uint_single_v8 port_memory_read_private_uint32_v8

// 16-vector of unsigned integers (single size)
#define port_memory_read_global_uint_single_v16 port_memory_read_global_uint32_v16
#define port_memory_read_constant_uint_single_v16 port_memory_read_constant_uint32_v16
#define port_memory_read_local_uint_single_v16 port_memory_read_local_uint32_v16
#define port_memory_read_private_uint_single_v16 port_memory_read_private_uint32_v16

// Unsigned integer (double size)
#define port_memory_read_global_uint_double port_memory_read_global_uint64
#define port_memory_read_constant_uint_double port_memory_read_constant_uint64
#define port_memory_read_local_uint_double port_memory_read_local_uint64
#define port_memory_read_private_uint_double port_memory_read_private_uint64

// 2-vector of unsigned integers (double size)
#define port_memory_read_global_uint_double_v2 port_memory_read_global_uint64_v2
#define port_memory_read_constant_uint_double_v2 port_memory_read_constant_uint64_v2
#define port_memory_read_local_uint_double_v2 port_memory_read_local_uint64_v2
#define port_memory_read_private_uint_double_v2 port_memory_read_private_uint64_v2

// 3-vector of unsigned integers (double size)
#define port_memory_read_global_uint_double_v3 port_memory_read_global_uint64_v3
#define port_memory_read_constant_uint_double_v3 port_memory_read_constant_uint64_v3
#define port_memory_read_local_uint_double_v3 port_memory_read_local_uint64_v3
#define port_memory_read_private_uint_double_v3 port_memory_read_private_uint64_v3

// 4-vector of unsigned integers (double size)
#define port_memory_read_global_uint_double_v4 port_memory_read_global_uint64_v4
#define port_memory_read_constant_uint_double_v4 port_memory_read_constant_uint64_v4
#define port_memory_read_local_uint_double_v4 port_memory_read_local_uint64_v4
#define port_memory_read_private_uint_double_v4 port_memory_read_private_uint64_v4

// 8-vector of unsigned integers (double size)
#define port_memory_read_global_uint_double_v8 port_memory_read_global_uint64_v8
#define port_memory_read_constant_uint_double_v8 port_memory_read_constant_uint64_v8
#define port_memory_read_local_uint_double_v8 port_memory_read_local_uint64_v8
#define port_memory_read_private_uint_double_v8 port_memory_read_private_uint64_v8

// 16-vector of unsigned integers (double size)
#define port_memory_read_global_uint_double_v16 port_memory_read_global_uint64_v16
#define port_memory_read_constant_uint_double_v16 port_memory_read_constant_uint64_v16
#define port_memory_read_local_uint_double_v16 port_memory_read_local_uint64_v16
#define port_memory_read_private_uint_double_v16 port_memory_read_private_uint64_v16

// Signed integer (quarter size)
#define port_memory_read_global_sint_quarter port_memory_read_global_sint8
#define port_memory_read_constant_sint_quarter port_memory_read_constant_sint8
#define port_memory_read_local_sint_quarter port_memory_read_local_sint8
#define port_memory_read_private_sint_quarter port_memory_read_private_sint8

// 2-vector of signed integers (quarter size)
#define port_memory_read_global_sint_quarter_v2 port_memory_read_global_sint8_v2
#define port_memory_read_constant_sint_quarter_v2 port_memory_read_constant_sint8_v2
#define port_memory_read_local_sint_quarter_v2 port_memory_read_local_sint8_v2
#define port_memory_read_private_sint_quarter_v2 port_memory_read_private_sint8_v2

// 3-vector of signed integers (quarter size)
#define port_memory_read_global_sint_quarter_v3 port_memory_read_global_sint8_v3
#define port_memory_read_constant_sint_quarter_v3 port_memory_read_constant_sint8_v3
#define port_memory_read_local_sint_quarter_v3 port_memory_read_local_sint8_v3
#define port_memory_read_private_sint_quarter_v3 port_memory_read_private_sint8_v3

// 4-vector of signed integers (quarter size)
#define port_memory_read_global_sint_quarter_v4 port_memory_read_global_sint8_v4
#define port_memory_read_constant_sint_quarter_v4 port_memory_read_constant_sint8_v4
#define port_memory_read_local_sint_quarter_v4 port_memory_read_local_sint8_v4
#define port_memory_read_private_sint_quarter_v4 port_memory_read_private_sint8_v4

// 8-vector of signed integers (quarter size)
#define port_memory_read_global_sint_quarter_v8 port_memory_read_global_sint8_v8
#define port_memory_read_constant_sint_quarter_v8 port_memory_read_constant_sint8_v8
#define port_memory_read_local_sint_quarter_v8 port_memory_read_local_sint8_v8
#define port_memory_read_private_sint_quarter_v8 port_memory_read_private_sint8_v8

// 16-vector of signed integers (quarter size)
#define port_memory_read_global_sint_quarter_v16 port_memory_read_global_sint8_v16
#define port_memory_read_constant_sint_quarter_v16 port_memory_read_constant_sint8_v16
#define port_memory_read_local_sint_quarter_v16 port_memory_read_local_sint8_v16
#define port_memory_read_private_sint_quarter_v16 port_memory_read_private_sint8_v16

// Signed integer (half size)
#define port_memory_read_global_sint_half port_memory_read_global_sint16
#define port_memory_read_constant_sint_half port_memory_read_constant_sint16
#define port_memory_read_local_sint_half port_memory_read_local_sint16
#define port_memory_read_private_sint_half port_memory_read_private_sint16

// 2-vector of signed integers (half size)
#define port_memory_read_global_sint_half_v2 port_memory_read_global_sint16_v2
#define port_memory_read_constant_sint_half_v2 port_memory_read_constant_sint16_v2
#define port_memory_read_local_sint_half_v2 port_memory_read_local_sint16_v2
#define port_memory_read_private_sint_half_v2 port_memory_read_private_sint16_v2

// 3-vector of signed integers (half size)
#define port_memory_read_global_sint_half_v3 port_memory_read_global_sint16_v3
#define port_memory_read_constant_sint_half_v3 port_memory_read_constant_sint16_v3
#define port_memory_read_local_sint_half_v3 port_memory_read_local_sint16_v3
#define port_memory_read_private_sint_half_v3 port_memory_read_private_sint16_v3

// 4-vector of signed integers (half size)
#define port_memory_read_global_sint_half_v4 port_memory_read_global_sint16_v4
#define port_memory_read_constant_sint_half_v4 port_memory_read_constant_sint16_v4
#define port_memory_read_local_sint_half_v4 port_memory_read_local_sint16_v4
#define port_memory_read_private_sint_half_v4 port_memory_read_private_sint16_v4

// 8-vector of signed integers (half size)
#define port_memory_read_global_sint_half_v8 port_memory_read_global_sint16_v8
#define port_memory_read_constant_sint_half_v8 port_memory_read_constant_sint16_v8
#define port_memory_read_local_sint_half_v8 port_memory_read_local_sint16_v8
#define port_memory_read_private_sint_half_v8 port_memory_read_private_sint16_v8

// 16-vector of signed integers (half size)
#define port_memory_read_global_sint_half_v16 port_memory_read_global_sint16_v16
#define port_memory_read_constant_sint_half_v16 port_memory_read_constant_sint16_v16
#define port_memory_read_local_sint_half_v16 port_memory_read_local_sint16_v16
#define port_memory_read_private_sint_half_v16 port_memory_read_private_sint16_v16

// Signed integer (single size)
#define port_memory_read_global_sint_single port_memory_read_global_sint32
#define port_memory_read_constant_sint_single port_memory_read_constant_sint32
#define port_memory_read_local_sint_single port_memory_read_local_sint32
#define port_memory_read_private_sint_single port_memory_read_private_sint32

// 2-vector of signed integers (single size)
#define port_memory_read_global_sint_single_v2 port_memory_read_global_sint32_v2
#define port_memory_read_constant_sint_single_v2 port_memory_read_constant_sint32_v2
#define port_memory_read_local_sint_single_v2 port_memory_read_local_sint32_v2
#define port_memory_read_private_sint_single_v2 port_memory_read_private_sint32_v2

// 3-vector of signed integers (single size)
#define port_memory_read_global_sint_single_v3 port_memory_read_global_sint32_v3
#define port_memory_read_constant_sint_single_v3 port_memory_read_constant_sint32_v3
#define port_memory_read_local_sint_single_v3 port_memory_read_local_sint32_v3
#define port_memory_read_private_sint_single_v3 port_memory_read_private_sint32_v3

// 4-vector of signed integers (single size)
#define port_memory_read_global_sint_single_v4 port_memory_read_global_sint32_v4
#define port_memory_read_constant_sint_single_v4 port_memory_read_constant_sint32_v4
#define port_memory_read_local_sint_single_v4 port_memory_read_local_sint32_v4
#define port_memory_read_private_sint_single_v4 port_memory_read_private_sint32_v4

// 8-vector of signed integers (single size)
#define port_memory_read_global_sint_single_v8 port_memory_read_global_sint32_v8
#define port_memory_read_constant_sint_single_v8 port_memory_read_constant_sint32_v8
#define port_memory_read_local_sint_single_v8 port_memory_read_local_sint32_v8
#define port_memory_read_private_sint_single_v8 port_memory_read_private_sint32_v8

// 16-vector of signed integers (single size)
#define port_memory_read_global_sint_single_v16 port_memory_read_global_sint32_v16
#define port_memory_read_constant_sint_single_v16 port_memory_read_constant_sint32_v16
#define port_memory_read_local_sint_single_v16 port_memory_read_local_sint32_v16
#define port_memory_read_private_sint_single_v16 port_memory_read_private_sint32_v16

// Signed integer (double size)
#define port_memory_read_global_sint_double port_memory_read_global_sint64
#define port_memory_read_constant_sint_double port_memory_read_constant_sint64
#define port_memory_read_local_sint_double port_memory_read_local_sint64
#define port_memory_read_private_sint_double port_memory_read_private_sint64

// 2-vector of signed integers (double size)
#define port_memory_read_global_sint_double_v2 port_memory_read_global_sint64_v2
#define port_memory_read_constant_sint_double_v2 port_memory_read_constant_sint64_v2
#define port_memory_read_local_sint_double_v2 port_memory_read_local_sint64_v2
#define port_memory_read_private_sint_double_v2 port_memory_read_private_sint64_v2

// 3-vector of signed integers (double size)
#define port_memory_read_global_sint_double_v3 port_memory_read_global_sint64_v3
#define port_memory_read_constant_sint_double_v3 port_memory_read_constant_sint64_v3
#define port_memory_read_local_sint_double_v3 port_memory_read_local_sint64_v3
#define port_memory_read_private_sint_double_v3 port_memory_read_private_sint64_v3

// 4-vector of signed integers (double size)
#define port_memory_read_global_sint_double_v4 port_memory_read_global_sint64_v4
#define port_memory_read_constant_sint_double_v4 port_memory_read_constant_sint64_v4
#define port_memory_read_local_sint_double_v4 port_memory_read_local_sint64_v4
#define port_memory_read_private_sint_double_v4 port_memory_read_private_sint64_v4

// 8-vector of signed integers (double size)
#define port_memory_read_global_sint_double_v8 port_memory_read_global_sint64_v8
#define port_memory_read_constant_sint_double_v8 port_memory_read_constant_sint64_v8
#define port_memory_read_local_sint_double_v8 port_memory_read_local_sint64_v8
#define port_memory_read_private_sint_double_v8 port_memory_read_private_sint64_v8

// 16-vector of signed integers (double size)
#define port_memory_read_global_sint_double_v16 port_memory_read_global_sint64_v16
#define port_memory_read_constant_sint_double_v16 port_memory_read_constant_sint64_v16
#define port_memory_read_local_sint_double_v16 port_memory_read_local_sint64_v16
#define port_memory_read_private_sint_double_v16 port_memory_read_private_sint64_v16

// Floating-point number (half size)
#define port_memory_read_global_float_half port_memory_read_global_float16
#define port_memory_read_constant_float_half port_memory_read_constant_float16
#define port_memory_read_local_float_half port_memory_read_local_float16
#define port_memory_read_private_float_half port_memory_read_private_float16

// 2-vector of floating-point numbers (half size)
#define port_memory_read_global_float_half_v2 port_memory_read_global_float16_v2
#define port_memory_read_constant_float_half_v2 port_memory_read_constant_float16_v2
#define port_memory_read_local_float_half_v2 port_memory_read_local_float16_v2
#define port_memory_read_private_float_half_v2 port_memory_read_private_float16_v2

// 3-vector of floating-point numbers (half size)
#define port_memory_read_global_float_half_v3 port_memory_read_global_float16_v3
#define port_memory_read_constant_float_half_v3 port_memory_read_constant_float16_v3
#define port_memory_read_local_float_half_v3 port_memory_read_local_float16_v3
#define port_memory_read_private_float_half_v3 port_memory_read_private_float16_v3

// 4-vector of floating-point numbers (half size)
#define port_memory_read_global_float_half_v4 port_memory_read_global_float16_v4
#define port_memory_read_constant_float_half_v4 port_memory_read_constant_float16_v4
#define port_memory_read_local_float_half_v4 port_memory_read_local_float16_v4
#define port_memory_read_private_float_half_v4 port_memory_read_private_float16_v4

// 8-vector of floating-point numbers (half size)
#define port_memory_read_global_float_half_v8 port_memory_read_global_float16_v8
#define port_memory_read_constant_float_half_v8 port_memory_read_constant_float16_v8
#define port_memory_read_local_float_half_v8 port_memory_read_local_float16_v8
#define port_memory_read_private_float_half_v8 port_memory_read_private_float16_v8

// 16-vector of floating-point numbers (half size)
#define port_memory_read_global_float_half_v16 port_memory_read_global_float16_v16
#define port_memory_read_constant_float_half_v16 port_memory_read_constant_float16_v16
#define port_memory_read_local_float_half_v16 port_memory_read_local_float16_v16
#define port_memory_read_private_float_half_v16 port_memory_read_private_float16_v16

// Floating-point number (single size)
#define port_memory_read_global_float_single port_memory_read_global_float32
#define port_memory_read_constant_float_single port_memory_read_constant_float32
#define port_memory_read_local_float_single port_memory_read_local_float32
#define port_memory_read_private_float_single port_memory_read_private_float32

// 2-vector of floating-point numbers (single size)
#define port_memory_read_global_float_single_v2 port_memory_read_global_float32_v2
#define port_memory_read_constant_float_single_v2 port_memory_read_constant_float32_v2
#define port_memory_read_local_float_single_v2 port_memory_read_local_float32_v2
#define port_memory_read_private_float_single_v2 port_memory_read_private_float32_v2

// 3-vector of floating-point numbers (single size)
#define port_memory_read_global_float_single_v3 port_memory_read_global_float32_v3
#define port_memory_read_constant_float_single_v3 port_memory_read_constant_float32_v3
#define port_memory_read_local_float_single_v3 port_memory_read_local_float32_v3
#define port_memory_read_private_float_single_v3 port_memory_read_private_float32_v3

// 4-vector of floating-point numbers (single size)
#define port_memory_read_global_float_single_v4 port_memory_read_global_float32_v4
#define port_memory_read_constant_float_single_v4 port_memory_read_constant_float32_v4
#define port_memory_read_local_float_single_v4 port_memory_read_local_float32_v4
#define port_memory_read_private_float_single_v4 port_memory_read_private_float32_v4

// 8-vector of floating-point numbers (single size)
#define port_memory_read_global_float_single_v8 port_memory_read_global_float32_v8
#define port_memory_read_constant_float_single_v8 port_memory_read_constant_float32_v8
#define port_memory_read_local_float_single_v8 port_memory_read_local_float32_v8
#define port_memory_read_private_float_single_v8 port_memory_read_private_float32_v8

// 16-vector of floating-point numbers (single size)
#define port_memory_read_global_float_single_v16 port_memory_read_global_float32_v16
#define port_memory_read_constant_float_single_v16 port_memory_read_constant_float32_v16
#define port_memory_read_local_float_single_v16 port_memory_read_local_float32_v16
#define port_memory_read_private_float_single_v16 port_memory_read_private_float32_v16

// Floating-point number (double size)
#define port_memory_read_global_float_double port_memory_read_global_float64
#define port_memory_read_constant_float_double port_memory_read_constant_float64
#define port_memory_read_local_float_double port_memory_read_local_float64
#define port_memory_read_private_float_double port_memory_read_private_float64

// 2-vector of floating-point numbers (double size)
#define port_memory_read_global_float_double_v2 port_memory_read_global_float64_v2
#define port_memory_read_constant_float_double_v2 port_memory_read_constant_float64_v2
#define port_memory_read_local_float_double_v2 port_memory_read_local_float64_v2
#define port_memory_read_private_float_double_v2 port_memory_read_private_float64_v2

// 3-vector of floating-point numbers (double size)
#define port_memory_read_global_float_double_v3 port_memory_read_global_float64_v3
#define port_memory_read_constant_float_double_v3 port_memory_read_constant_float64_v3
#define port_memory_read_local_float_double_v3 port_memory_read_local_float64_v3
#define port_memory_read_private_float_double_v3 port_memory_read_private_float64_v3

// 4-vector of floating-point numbers (double size)
#define port_memory_read_global_float_double_v4 port_memory_read_global_float64_v4
#define port_memory_read_constant_float_double_v4 port_memory_read_constant_float64_v4
#define port_memory_read_local_float_double_v4 port_memory_read_local_float64_v4
#define port_memory_read_private_float_double_v4 port_memory_read_private_float64_v4

// 8-vector of floating-point numbers (double size)
#define port_memory_read_global_float_double_v8 port_memory_read_global_float64_v8
#define port_memory_read_constant_float_double_v8 port_memory_read_constant_float64_v8
#define port_memory_read_local_float_double_v8 port_memory_read_local_float64_v8
#define port_memory_read_private_float_double_v8 port_memory_read_private_float64_v8

// 16-vector of floating-point numbers (double size)
#define port_memory_read_global_float_double_v16 port_memory_read_global_float64_v16
#define port_memory_read_constant_float_double_v16 port_memory_read_constant_float64_v16
#define port_memory_read_local_float_double_v16 port_memory_read_local_float64_v16
#define port_memory_read_private_float_double_v16 port_memory_read_private_float64_v16

#ifndef PORT_FEATURE_DEFAULT_INTEGER_64

// Default unsigned integer
#define port_memory_read_global_uint port_memory_read_global_uint32
#define port_memory_read_constant_uint port_memory_read_constant_uint32
#define port_memory_read_local_uint port_memory_read_local_uint32
#define port_memory_read_private_uint port_memory_read_private_uint32

// 2-vector of default unsigned integers (single size)
#define port_memory_read_global_uint_v2 port_memory_read_global_uint32_v2
#define port_memory_read_constant_uint_v2 port_memory_read_constant_uint32_v2
#define port_memory_read_local_uint_v2 port_memory_read_local_uint32_v2
#define port_memory_read_private_uint_v2 port_memory_read_private_uint32_v2

// 3-vector of default unsigned integers (single size)
#define port_memory_read_global_uint_v3 port_memory_read_global_uint32_v3
#define port_memory_read_constant_uint_v3 port_memory_read_constant_uint32_v3
#define port_memory_read_local_uint_v3 port_memory_read_local_uint32_v3
#define port_memory_read_private_uint_v3 port_memory_read_private_uint32_v3

// 4-vector of default unsigned integers (single size)
#define port_memory_read_global_uint_v4 port_memory_read_global_uint32_v4
#define port_memory_read_constant_uint_v4 port_memory_read_constant_uint32_v4
#define port_memory_read_local_uint_v4 port_memory_read_local_uint32_v4
#define port_memory_read_private_uint_v4 port_memory_read_private_uint32_v4

// 8-vector of default unsigned integers (single size)
#define port_memory_read_global_uint_v8 port_memory_read_global_uint32_v8
#define port_memory_read_constant_uint_v8 port_memory_read_constant_uint32_v8
#define port_memory_read_local_uint_v8 port_memory_read_local_uint32_v8
#define port_memory_read_private_uint_v8 port_memory_read_private_uint32_v8

// 16-vector of default unsigned integers (single size)
#define port_memory_read_global_uint_v16 port_memory_read_global_uint32_v16
#define port_memory_read_constant_uint_v16 port_memory_read_constant_uint32_v16
#define port_memory_read_local_uint_v16 port_memory_read_local_uint32_v16
#define port_memory_read_private_uint_v16 port_memory_read_private_uint32_v16

// Default signed integer
#define port_memory_read_global_sint port_memory_read_global_sint32
#define port_memory_read_constant_sint port_memory_read_constant_sint32
#define port_memory_read_local_sint port_memory_read_local_sint32
#define port_memory_read_private_sint port_memory_read_private_sint32

// 2-vector of default signed integers (single size)
#define port_memory_read_global_sint_v2 port_memory_read_global_sint32_v2
#define port_memory_read_constant_sint_v2 port_memory_read_constant_sint32_v2
#define port_memory_read_local_sint_v2 port_memory_read_local_sint32_v2
#define port_memory_read_private_sint_v2 port_memory_read_private_sint32_v2

// 3-vector of default signed integers (single size)
#define port_memory_read_global_sint_v3 port_memory_read_global_sint32_v3
#define port_memory_read_constant_sint_v3 port_memory_read_constant_sint32_v3
#define port_memory_read_local_sint_v3 port_memory_read_local_sint32_v3
#define port_memory_read_private_sint_v3 port_memory_read_private_sint32_v3

// 4-vector of default signed integers (single size)
#define port_memory_read_global_sint_v4 port_memory_read_global_sint32_v4
#define port_memory_read_constant_sint_v4 port_memory_read_constant_sint32_v4
#define port_memory_read_local_sint_v4 port_memory_read_local_sint32_v4
#define port_memory_read_private_sint_v4 port_memory_read_private_sint32_v4

// 8-vector of default signed integers (single size)
#define port_memory_read_global_sint_v8 port_memory_read_global_sint32_v8
#define port_memory_read_constant_sint_v8 port_memory_read_constant_sint32_v8
#define port_memory_read_local_sint_v8 port_memory_read_local_sint32_v8
#define port_memory_read_private_sint_v8 port_memory_read_private_sint32_v8

// 16-vector of default signed integers (single size)
#define port_memory_read_global_sint_v16 port_memory_read_global_sint32_v16
#define port_memory_read_constant_sint_v16 port_memory_read_constant_sint32_v16
#define port_memory_read_local_sint_v16 port_memory_read_local_sint32_v16
#define port_memory_read_private_sint_v16 port_memory_read_private_sint32_v16

#else // PORT_FEATURE_DEFAULT_INTEGER_64

// Default unsigned integer
#define port_memory_read_global_uint port_memory_read_global_uint64
#define port_memory_read_constant_uint port_memory_read_constant_uint64
#define port_memory_read_local_uint port_memory_read_local_uint64
#define port_memory_read_private_uint port_memory_read_private_uint64

// 2-vector of default unsigned integers (single size)
#define port_memory_read_global_uint_v2 port_memory_read_global_uint64_v2
#define port_memory_read_constant_uint_v2 port_memory_read_constant_uint64_v2
#define port_memory_read_local_uint_v2 port_memory_read_local_uint64_v2
#define port_memory_read_private_uint_v2 port_memory_read_private_uint64_v2

// 3-vector of default unsigned integers (single size)
#define port_memory_read_global_uint_v3 port_memory_read_global_uint64_v3
#define port_memory_read_constant_uint_v3 port_memory_read_constant_uint64_v3
#define port_memory_read_local_uint_v3 port_memory_read_local_uint64_v3
#define port_memory_read_private_uint_v3 port_memory_read_private_uint64_v3

// 4-vector of default unsigned integers (single size)
#define port_memory_read_global_uint_v4 port_memory_read_global_uint64_v4
#define port_memory_read_constant_uint_v4 port_memory_read_constant_uint64_v4
#define port_memory_read_local_uint_v4 port_memory_read_local_uint64_v4
#define port_memory_read_private_uint_v4 port_memory_read_private_uint64_v4

// 8-vector of default unsigned integers (single size)
#define port_memory_read_global_uint_v8 port_memory_read_global_uint64_v8
#define port_memory_read_constant_uint_v8 port_memory_read_constant_uint64_v8
#define port_memory_read_local_uint_v8 port_memory_read_local_uint64_v8
#define port_memory_read_private_uint_v8 port_memory_read_private_uint64_v8

// 16-vector of default unsigned integers (single size)
#define port_memory_read_global_uint_v16 port_memory_read_global_uint64_v16
#define port_memory_read_constant_uint_v16 port_memory_read_constant_uint64_v16
#define port_memory_read_local_uint_v16 port_memory_read_local_uint64_v16
#define port_memory_read_private_uint_v16 port_memory_read_private_uint64_v16

// Default signed integer
#define port_memory_read_global_sint port_memory_read_global_sint64
#define port_memory_read_constant_sint port_memory_read_constant_sint64
#define port_memory_read_local_sint port_memory_read_local_sint64
#define port_memory_read_private_sint port_memory_read_private_sint64

// 2-vector of default signed integers (single size)
#define port_memory_read_global_sint_v2 port_memory_read_global_sint64_v2
#define port_memory_read_constant_sint_v2 port_memory_read_constant_sint64_v2
#define port_memory_read_local_sint_v2 port_memory_read_local_sint64_v2
#define port_memory_read_private_sint_v2 port_memory_read_private_sint64_v2

// 3-vector of default signed integers (single size)
#define port_memory_read_global_sint_v3 port_memory_read_global_sint64_v3
#define port_memory_read_constant_sint_v3 port_memory_read_constant_sint64_v3
#define port_memory_read_local_sint_v3 port_memory_read_local_sint64_v3
#define port_memory_read_private_sint_v3 port_memory_read_private_sint64_v3

// 4-vector of default signed integers (single size)
#define port_memory_read_global_sint_v4 port_memory_read_global_sint64_v4
#define port_memory_read_constant_sint_v4 port_memory_read_constant_sint64_v4
#define port_memory_read_local_sint_v4 port_memory_read_local_sint64_v4
#define port_memory_read_private_sint_v4 port_memory_read_private_sint64_v4

// 8-vector of default signed integers (single size)
#define port_memory_read_global_sint_v8 port_memory_read_global_sint64_v8
#define port_memory_read_constant_sint_v8 port_memory_read_constant_sint64_v8
#define port_memory_read_local_sint_v8 port_memory_read_local_sint64_v8
#define port_memory_read_private_sint_v8 port_memory_read_private_sint64_v8

// 16-vector of default signed integers (single size)
#define port_memory_read_global_sint_v16 port_memory_read_global_sint64_v16
#define port_memory_read_constant_sint_v16 port_memory_read_constant_sint64_v16
#define port_memory_read_local_sint_v16 port_memory_read_local_sint64_v16
#define port_memory_read_private_sint_v16 port_memory_read_private_sint64_v16

#endif // PORT_FEATURE_DEFAULT_INTEGER_64

#ifndef PORT_FEATURE_DEFAULT_FLOAT_64

// Default floating-point number
#define port_memory_read_global_float port_memory_read_global_float32
#define port_memory_read_constant_float port_memory_read_constant_float32
#define port_memory_read_local_float port_memory_read_local_float32
#define port_memory_read_private_float port_memory_read_private_float32

// 2-vector of default floating-point numbers (single size)
#define port_memory_read_global_float_v2 port_memory_read_global_float32_v2
#define port_memory_read_constant_float_v2 port_memory_read_constant_float32_v2
#define port_memory_read_local_float_v2 port_memory_read_local_float32_v2
#define port_memory_read_private_float_v2 port_memory_read_private_float32_v2

// 3-vector of default floating-point numbers (single size)
#define port_memory_read_global_float_v3 port_memory_read_global_float32_v3
#define port_memory_read_constant_float_v3 port_memory_read_constant_float32_v3
#define port_memory_read_local_float_v3 port_memory_read_local_float32_v3
#define port_memory_read_private_float_v3 port_memory_read_private_float32_v3

// 4-vector of default floating-point numbers (single size)
#define port_memory_read_global_float_v4 port_memory_read_global_float32_v4
#define port_memory_read_constant_float_v4 port_memory_read_constant_float32_v4
#define port_memory_read_local_float_v4 port_memory_read_local_float32_v4
#define port_memory_read_private_float_v4 port_memory_read_private_float32_v4

// 8-vector of default floating-point numbers (single size)
#define port_memory_read_global_float_v8 port_memory_read_global_float32_v8
#define port_memory_read_constant_float_v8 port_memory_read_constant_float32_v8
#define port_memory_read_local_float_v8 port_memory_read_local_float32_v8
#define port_memory_read_private_float_v8 port_memory_read_private_float32_v8

// 16-vector of default floating-point numbers (single size)
#define port_memory_read_global_float_v16 port_memory_read_global_float32_v16
#define port_memory_read_constant_float_v16 port_memory_read_constant_float32_v16
#define port_memory_read_local_float_v16 port_memory_read_local_float32_v16
#define port_memory_read_private_float_v16 port_memory_read_private_float32_v16

#else // PORT_FEATURE_DEFAULT_FLOAT_64

// Default floating-point number
#define port_memory_read_global_float port_memory_read_global_float64
#define port_memory_read_constant_float port_memory_read_constant_float64
#define port_memory_read_local_float port_memory_read_local_float64
#define port_memory_read_private_float port_memory_read_private_float64

// 2-vector of default floating-point numbers (single size)
#define port_memory_read_global_float_v2 port_memory_read_global_float64_v2
#define port_memory_read_constant_float_v2 port_memory_read_constant_float64_v2
#define port_memory_read_local_float_v2 port_memory_read_local_float64_v2
#define port_memory_read_private_float_v2 port_memory_read_private_float64_v2

// 3-vector of default floating-point numbers (single size)
#define port_memory_read_global_float_v3 port_memory_read_global_float64_v3
#define port_memory_read_constant_float_v3 port_memory_read_constant_float64_v3
#define port_memory_read_local_float_v3 port_memory_read_local_float64_v3
#define port_memory_read_private_float_v3 port_memory_read_private_float64_v3

// 4-vector of default floating-point numbers (single size)
#define port_memory_read_global_float_v4 port_memory_read_global_float64_v4
#define port_memory_read_constant_float_v4 port_memory_read_constant_float64_v4
#define port_memory_read_local_float_v4 port_memory_read_local_float64_v4
#define port_memory_read_private_float_v4 port_memory_read_private_float64_v4

// 8-vector of default floating-point numbers (single size)
#define port_memory_read_global_float_v8 port_memory_read_global_float64_v8
#define port_memory_read_constant_float_v8 port_memory_read_constant_float64_v8
#define port_memory_read_local_float_v8 port_memory_read_local_float64_v8
#define port_memory_read_private_float_v8 port_memory_read_private_float64_v8

// 16-vector of default floating-point numbers (single size)
#define port_memory_read_global_float_v16 port_memory_read_global_float64_v16
#define port_memory_read_constant_float_v16 port_memory_read_constant_float64_v16
#define port_memory_read_local_float_v16 port_memory_read_local_float64_v16
#define port_memory_read_private_float_v16 port_memory_read_private_float64_v16

#endif // PORT_FEATURE_DEFAULT_FLOAT_64

///////////////////////////////////////////////////////////////////////////////
// Writing to memory
///////////////////////////////////////////////////////////////////////////////

#define PORT_DECLARE_MEMORY_WRITE_FUNCTION(name, value_type, memory_type) \
    void name(memory_type memory, value_type value, port_uint8_t offset)

#define PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(value_type) \
    PORT_DECLARE_MEMORY_WRITE_FUNCTION(port_memory_write_global_##value_type,   \
            port_##value_type##_t, port_global_memory_ptr_t);                   \
    PORT_DECLARE_MEMORY_WRITE_FUNCTION(port_memory_write_local_##value_type,    \
            port_##value_type##_t, port_local_memory_ptr_t);                    \
    PORT_DECLARE_MEMORY_WRITE_FUNCTION(port_memory_write_private_##value_type,  \
            port_##value_type##_t, port_private_memory_ptr_t);

#define PORT_DECLARE_MEMORY_WRITE_FUNCTIONS_FLOAT16(value_type) \
    PORT_DECLARE_MEMORY_WRITE_FUNCTION(port_memory_write_global_float16##value_type,    \
            port_float32##value_type##_t, port_global_memory_ptr_t);                    \
    PORT_DECLARE_MEMORY_WRITE_FUNCTION(port_memory_write_local_float16##value_type,     \
            port_float32##value_type##_t, port_local_memory_ptr_t);                     \
    PORT_DECLARE_MEMORY_WRITE_FUNCTION(port_memory_write_private_float16##value_type,   \
            port_float32##value_type##_t, port_private_memory_ptr_t);

// Unsigned integers
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(uint8)     // Unsigned 8-bit integer (scalar)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(uint8_v2)  // Unsigned 8-bit integer (2-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(uint8_v3)  // Unsigned 8-bit integer (3-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(uint8_v4)  // Unsigned 8-bit integer (4-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(uint8_v8)  // Unsigned 8-bit integer (8-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(uint8_v16) // Unsigned 8-bit integer (16-vector)

PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(uint16)     // Unsigned 16-bit integer (scalar)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(uint16_v2)  // Unsigned 16-bit integer (2-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(uint16_v3)  // Unsigned 16-bit integer (3-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(uint16_v4)  // Unsigned 16-bit integer (4-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(uint16_v8)  // Unsigned 16-bit integer (8-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(uint16_v16) // Unsigned 16-bit integer (16-vector)

PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(uint32)     // Unsigned 32-bit integer (scalar)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(uint32_v2)  // Unsigned 32-bit integer (2-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(uint32_v3)  // Unsigned 32-bit integer (3-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(uint32_v4)  // Unsigned 32-bit integer (4-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(uint32_v8)  // Unsigned 32-bit integer (8-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(uint32_v16) // Unsigned 32-bit integer (16-vector)

PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(uint64)     // Unsigned 64-bit integer (scalar)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(uint64_v2)  // Unsigned 64-bit integer (2-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(uint64_v3)  // Unsigned 64-bit integer (3-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(uint64_v4)  // Unsigned 64-bit integer (4-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(uint64_v8)  // Unsigned 64-bit integer (8-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(uint64_v16) // Unsigned 64-bit integer (16-vector)

// Signed integers
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(sint8)     // Signed 8-bit integer (scalar)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(sint8_v2)  // Signed 8-bit integer (2-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(sint8_v3)  // Signed 8-bit integer (3-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(sint8_v4)  // Signed 8-bit integer (4-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(sint8_v8)  // Signed 8-bit integer (8-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(sint8_v16) // Signed 8-bit integer (16-vector)

PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(sint16)     // Signed 16-bit integer (scalar)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(sint16_v2)  // Signed 16-bit integer (2-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(sint16_v3)  // Signed 16-bit integer (3-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(sint16_v4)  // Signed 16-bit integer (4-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(sint16_v8)  // Signed 16-bit integer (8-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(sint16_v16) // Signed 16-bit integer (16-vector)

PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(sint32)     // Signed 32-bit integer (scalar)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(sint32_v2)  // Signed 32-bit integer (2-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(sint32_v3)  // Signed 32-bit integer (3-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(sint32_v4)  // Signed 32-bit integer (4-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(sint32_v8)  // Signed 32-bit integer (8-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(sint32_v16) // Signed 32-bit integer (16-vector)

PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(sint64)     // Signed 64-bit integer (scalar)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(sint64_v2)  // Signed 64-bit integer (2-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(sint64_v3)  // Signed 64-bit integer (3-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(sint64_v4)  // Signed 64-bit integer (4-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(sint64_v8)  // Signed 64-bit integer (8-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(sint64_v16) // Signed 64-bit integer (16-vector)

// Floating-point numbers
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS_FLOAT16()     // 16-bit floating-point number (scalar)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS_FLOAT16(_v2)  // 16-bit floating-point number (2-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS_FLOAT16(_v3)  // 16-bit floating-point number (3-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS_FLOAT16(_v4)  // 16-bit floating-point number (4-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS_FLOAT16(_v8)  // 16-bit floating-point number (8-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS_FLOAT16(_v16) // 16-bit floating-point number (16-vector)

PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(float32)     // 32-bit floating-point number (scalar)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(float32_v2)  // 32-bit floating-point number (2-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(float32_v3)  // 32-bit floating-point number (3-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(float32_v4)  // 32-bit floating-point number (4-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(float32_v8)  // 32-bit floating-point number (8-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(float32_v16) // 32-bit floating-point number (16-vector)

PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(float64)     // 64-bit floating-point number (scalar)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(float64_v2)  // 64-bit floating-point number (2-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(float64_v3)  // 64-bit floating-point number (3-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(float64_v4)  // 64-bit floating-point number (4-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(float64_v8)  // 64-bit floating-point number (8-vector)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(float64_v16) // 64-bit floating-point number (16-vector)

// Memory references
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(memory_ref_quarter) // Memory reference (quarter size)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(memory_ref_half)    // Memory reference (half size)
PORT_DECLARE_MEMORY_WRITE_FUNCTIONS(memory_ref)         // Memory reference (single size)

#undef PORT_DECLARE_MEMORY_WRITE_FUNCTIONS_FLOAT16
#undef PORT_DECLARE_MEMORY_WRITE_FUNCTIONS
#undef PORT_DECLARE_MEMORY_WRITE_FUNCTION

// Unsigned integer (quarter size)
#define port_memory_write_global_uint_quarter port_memory_write_global_uint8
#define port_memory_write_constant_uint_quarter port_memory_write_constant_uint8
#define port_memory_write_local_uint_quarter port_memory_write_local_uint8
#define port_memory_write_private_uint_quarter port_memory_write_private_uint8

// 2-vector of unsigned integers (quarter size)
#define port_memory_write_global_uint_quarter_v2 port_memory_write_global_uint8_v2
#define port_memory_write_constant_uint_quarter_v2 port_memory_write_constant_uint8_v2
#define port_memory_write_local_uint_quarter_v2 port_memory_write_local_uint8_v2
#define port_memory_write_private_uint_quarter_v2 port_memory_write_private_uint8_v2

// 3-vector of unsigned integers (quarter size)
#define port_memory_write_global_uint_quarter_v3 port_memory_write_global_uint8_v3
#define port_memory_write_constant_uint_quarter_v3 port_memory_write_constant_uint8_v3
#define port_memory_write_local_uint_quarter_v3 port_memory_write_local_uint8_v3
#define port_memory_write_private_uint_quarter_v3 port_memory_write_private_uint8_v3

// 4-vector of unsigned integers (quarter size)
#define port_memory_write_global_uint_quarter_v4 port_memory_write_global_uint8_v4
#define port_memory_write_constant_uint_quarter_v4 port_memory_write_constant_uint8_v4
#define port_memory_write_local_uint_quarter_v4 port_memory_write_local_uint8_v4
#define port_memory_write_private_uint_quarter_v4 port_memory_write_private_uint8_v4

// 8-vector of unsigned integers (quarter size)
#define port_memory_write_global_uint_quarter_v8 port_memory_write_global_uint8_v8
#define port_memory_write_constant_uint_quarter_v8 port_memory_write_constant_uint8_v8
#define port_memory_write_local_uint_quarter_v8 port_memory_write_local_uint8_v8
#define port_memory_write_private_uint_quarter_v8 port_memory_write_private_uint8_v8

// 16-vector of unsigned integers (quarter size)
#define port_memory_write_global_uint_quarter_v16 port_memory_write_global_uint8_v16
#define port_memory_write_constant_uint_quarter_v16 port_memory_write_constant_uint8_v16
#define port_memory_write_local_uint_quarter_v16 port_memory_write_local_uint8_v16
#define port_memory_write_private_uint_quarter_v16 port_memory_write_private_uint8_v16

// Unsigned integer (half size)
#define port_memory_write_global_uint_half port_memory_write_global_uint16
#define port_memory_write_constant_uint_half port_memory_write_constant_uint16
#define port_memory_write_local_uint_half port_memory_write_local_uint16
#define port_memory_write_private_uint_half port_memory_write_private_uint16

// 2-vector of unsigned integers (half size)
#define port_memory_write_global_uint_half_v2 port_memory_write_global_uint16_v2
#define port_memory_write_constant_uint_half_v2 port_memory_write_constant_uint16_v2
#define port_memory_write_local_uint_half_v2 port_memory_write_local_uint16_v2
#define port_memory_write_private_uint_half_v2 port_memory_write_private_uint16_v2

// 3-vector of unsigned integers (half size)
#define port_memory_write_global_uint_half_v3 port_memory_write_global_uint16_v3
#define port_memory_write_constant_uint_half_v3 port_memory_write_constant_uint16_v3
#define port_memory_write_local_uint_half_v3 port_memory_write_local_uint16_v3
#define port_memory_write_private_uint_half_v3 port_memory_write_private_uint16_v3

// 4-vector of unsigned integers (half size)
#define port_memory_write_global_uint_half_v4 port_memory_write_global_uint16_v4
#define port_memory_write_constant_uint_half_v4 port_memory_write_constant_uint16_v4
#define port_memory_write_local_uint_half_v4 port_memory_write_local_uint16_v4
#define port_memory_write_private_uint_half_v4 port_memory_write_private_uint16_v4

// 8-vector of unsigned integers (half size)
#define port_memory_write_global_uint_half_v8 port_memory_write_global_uint16_v8
#define port_memory_write_constant_uint_half_v8 port_memory_write_constant_uint16_v8
#define port_memory_write_local_uint_half_v8 port_memory_write_local_uint16_v8
#define port_memory_write_private_uint_half_v8 port_memory_write_private_uint16_v8

// 16-vector of unsigned integers (half size)
#define port_memory_write_global_uint_half_v16 port_memory_write_global_uint16_v16
#define port_memory_write_constant_uint_half_v16 port_memory_write_constant_uint16_v16
#define port_memory_write_local_uint_half_v16 port_memory_write_local_uint16_v16
#define port_memory_write_private_uint_half_v16 port_memory_write_private_uint16_v16

// Unsigned integer (single size)
#define port_memory_write_global_uint_single port_memory_write_global_uint32
#define port_memory_write_constant_uint_single port_memory_write_constant_uint32
#define port_memory_write_local_uint_single port_memory_write_local_uint32
#define port_memory_write_private_uint_single port_memory_write_private_uint32

// 2-vector of unsigned integers (single size)
#define port_memory_write_global_uint_single_v2 port_memory_write_global_uint32_v2
#define port_memory_write_constant_uint_single_v2 port_memory_write_constant_uint32_v2
#define port_memory_write_local_uint_single_v2 port_memory_write_local_uint32_v2
#define port_memory_write_private_uint_single_v2 port_memory_write_private_uint32_v2

// 3-vector of unsigned integers (single size)
#define port_memory_write_global_uint_single_v3 port_memory_write_global_uint32_v3
#define port_memory_write_constant_uint_single_v3 port_memory_write_constant_uint32_v3
#define port_memory_write_local_uint_single_v3 port_memory_write_local_uint32_v3
#define port_memory_write_private_uint_single_v3 port_memory_write_private_uint32_v3

// 4-vector of unsigned integers (single size)
#define port_memory_write_global_uint_single_v4 port_memory_write_global_uint32_v4
#define port_memory_write_constant_uint_single_v4 port_memory_write_constant_uint32_v4
#define port_memory_write_local_uint_single_v4 port_memory_write_local_uint32_v4
#define port_memory_write_private_uint_single_v4 port_memory_write_private_uint32_v4

// 8-vector of unsigned integers (single size)
#define port_memory_write_global_uint_single_v8 port_memory_write_global_uint32_v8
#define port_memory_write_constant_uint_single_v8 port_memory_write_constant_uint32_v8
#define port_memory_write_local_uint_single_v8 port_memory_write_local_uint32_v8
#define port_memory_write_private_uint_single_v8 port_memory_write_private_uint32_v8

// 16-vector of unsigned integers (single size)
#define port_memory_write_global_uint_single_v16 port_memory_write_global_uint32_v16
#define port_memory_write_constant_uint_single_v16 port_memory_write_constant_uint32_v16
#define port_memory_write_local_uint_single_v16 port_memory_write_local_uint32_v16
#define port_memory_write_private_uint_single_v16 port_memory_write_private_uint32_v16

// Unsigned integer (double size)
#define port_memory_write_global_uint_double port_memory_write_global_uint64
#define port_memory_write_constant_uint_double port_memory_write_constant_uint64
#define port_memory_write_local_uint_double port_memory_write_local_uint64
#define port_memory_write_private_uint_double port_memory_write_private_uint64

// 2-vector of unsigned integers (double size)
#define port_memory_write_global_uint_double_v2 port_memory_write_global_uint64_v2
#define port_memory_write_constant_uint_double_v2 port_memory_write_constant_uint64_v2
#define port_memory_write_local_uint_double_v2 port_memory_write_local_uint64_v2
#define port_memory_write_private_uint_double_v2 port_memory_write_private_uint64_v2

// 3-vector of unsigned integers (double size)
#define port_memory_write_global_uint_double_v3 port_memory_write_global_uint64_v3
#define port_memory_write_constant_uint_double_v3 port_memory_write_constant_uint64_v3
#define port_memory_write_local_uint_double_v3 port_memory_write_local_uint64_v3
#define port_memory_write_private_uint_double_v3 port_memory_write_private_uint64_v3

// 4-vector of unsigned integers (double size)
#define port_memory_write_global_uint_double_v4 port_memory_write_global_uint64_v4
#define port_memory_write_constant_uint_double_v4 port_memory_write_constant_uint64_v4
#define port_memory_write_local_uint_double_v4 port_memory_write_local_uint64_v4
#define port_memory_write_private_uint_double_v4 port_memory_write_private_uint64_v4

// 8-vector of unsigned integers (double size)
#define port_memory_write_global_uint_double_v8 port_memory_write_global_uint64_v8
#define port_memory_write_constant_uint_double_v8 port_memory_write_constant_uint64_v8
#define port_memory_write_local_uint_double_v8 port_memory_write_local_uint64_v8
#define port_memory_write_private_uint_double_v8 port_memory_write_private_uint64_v8

// 16-vector of unsigned integers (double size)
#define port_memory_write_global_uint_double_v16 port_memory_write_global_uint64_v16
#define port_memory_write_constant_uint_double_v16 port_memory_write_constant_uint64_v16
#define port_memory_write_local_uint_double_v16 port_memory_write_local_uint64_v16
#define port_memory_write_private_uint_double_v16 port_memory_write_private_uint64_v16

// Signed integer (quarter size)
#define port_memory_write_global_sint_quarter port_memory_write_global_sint8
#define port_memory_write_constant_sint_quarter port_memory_write_constant_sint8
#define port_memory_write_local_sint_quarter port_memory_write_local_sint8
#define port_memory_write_private_sint_quarter port_memory_write_private_sint8

// 2-vector of signed integers (quarter size)
#define port_memory_write_global_sint_quarter_v2 port_memory_write_global_sint8_v2
#define port_memory_write_constant_sint_quarter_v2 port_memory_write_constant_sint8_v2
#define port_memory_write_local_sint_quarter_v2 port_memory_write_local_sint8_v2
#define port_memory_write_private_sint_quarter_v2 port_memory_write_private_sint8_v2

// 3-vector of signed integers (quarter size)
#define port_memory_write_global_sint_quarter_v3 port_memory_write_global_sint8_v3
#define port_memory_write_constant_sint_quarter_v3 port_memory_write_constant_sint8_v3
#define port_memory_write_local_sint_quarter_v3 port_memory_write_local_sint8_v3
#define port_memory_write_private_sint_quarter_v3 port_memory_write_private_sint8_v3

// 4-vector of signed integers (quarter size)
#define port_memory_write_global_sint_quarter_v4 port_memory_write_global_sint8_v4
#define port_memory_write_constant_sint_quarter_v4 port_memory_write_constant_sint8_v4
#define port_memory_write_local_sint_quarter_v4 port_memory_write_local_sint8_v4
#define port_memory_write_private_sint_quarter_v4 port_memory_write_private_sint8_v4

// 8-vector of signed integers (quarter size)
#define port_memory_write_global_sint_quarter_v8 port_memory_write_global_sint8_v8
#define port_memory_write_constant_sint_quarter_v8 port_memory_write_constant_sint8_v8
#define port_memory_write_local_sint_quarter_v8 port_memory_write_local_sint8_v8
#define port_memory_write_private_sint_quarter_v8 port_memory_write_private_sint8_v8

// 16-vector of signed integers (quarter size)
#define port_memory_write_global_sint_quarter_v16 port_memory_write_global_sint8_v16
#define port_memory_write_constant_sint_quarter_v16 port_memory_write_constant_sint8_v16
#define port_memory_write_local_sint_quarter_v16 port_memory_write_local_sint8_v16
#define port_memory_write_private_sint_quarter_v16 port_memory_write_private_sint8_v16

// Signed integer (half size)
#define port_memory_write_global_sint_half port_memory_write_global_sint16
#define port_memory_write_constant_sint_half port_memory_write_constant_sint16
#define port_memory_write_local_sint_half port_memory_write_local_sint16
#define port_memory_write_private_sint_half port_memory_write_private_sint16

// 2-vector of signed integers (half size)
#define port_memory_write_global_sint_half_v2 port_memory_write_global_sint16_v2
#define port_memory_write_constant_sint_half_v2 port_memory_write_constant_sint16_v2
#define port_memory_write_local_sint_half_v2 port_memory_write_local_sint16_v2
#define port_memory_write_private_sint_half_v2 port_memory_write_private_sint16_v2

// 3-vector of signed integers (half size)
#define port_memory_write_global_sint_half_v3 port_memory_write_global_sint16_v3
#define port_memory_write_constant_sint_half_v3 port_memory_write_constant_sint16_v3
#define port_memory_write_local_sint_half_v3 port_memory_write_local_sint16_v3
#define port_memory_write_private_sint_half_v3 port_memory_write_private_sint16_v3

// 4-vector of signed integers (half size)
#define port_memory_write_global_sint_half_v4 port_memory_write_global_sint16_v4
#define port_memory_write_constant_sint_half_v4 port_memory_write_constant_sint16_v4
#define port_memory_write_local_sint_half_v4 port_memory_write_local_sint16_v4
#define port_memory_write_private_sint_half_v4 port_memory_write_private_sint16_v4

// 8-vector of signed integers (half size)
#define port_memory_write_global_sint_half_v8 port_memory_write_global_sint16_v8
#define port_memory_write_constant_sint_half_v8 port_memory_write_constant_sint16_v8
#define port_memory_write_local_sint_half_v8 port_memory_write_local_sint16_v8
#define port_memory_write_private_sint_half_v8 port_memory_write_private_sint16_v8

// 16-vector of signed integers (half size)
#define port_memory_write_global_sint_half_v16 port_memory_write_global_sint16_v16
#define port_memory_write_constant_sint_half_v16 port_memory_write_constant_sint16_v16
#define port_memory_write_local_sint_half_v16 port_memory_write_local_sint16_v16
#define port_memory_write_private_sint_half_v16 port_memory_write_private_sint16_v16

// Signed integer (single size)
#define port_memory_write_global_sint_single port_memory_write_global_sint32
#define port_memory_write_constant_sint_single port_memory_write_constant_sint32
#define port_memory_write_local_sint_single port_memory_write_local_sint32
#define port_memory_write_private_sint_single port_memory_write_private_sint32

// 2-vector of signed integers (single size)
#define port_memory_write_global_sint_single_v2 port_memory_write_global_sint32_v2
#define port_memory_write_constant_sint_single_v2 port_memory_write_constant_sint32_v2
#define port_memory_write_local_sint_single_v2 port_memory_write_local_sint32_v2
#define port_memory_write_private_sint_single_v2 port_memory_write_private_sint32_v2

// 3-vector of signed integers (single size)
#define port_memory_write_global_sint_single_v3 port_memory_write_global_sint32_v3
#define port_memory_write_constant_sint_single_v3 port_memory_write_constant_sint32_v3
#define port_memory_write_local_sint_single_v3 port_memory_write_local_sint32_v3
#define port_memory_write_private_sint_single_v3 port_memory_write_private_sint32_v3

// 4-vector of signed integers (single size)
#define port_memory_write_global_sint_single_v4 port_memory_write_global_sint32_v4
#define port_memory_write_constant_sint_single_v4 port_memory_write_constant_sint32_v4
#define port_memory_write_local_sint_single_v4 port_memory_write_local_sint32_v4
#define port_memory_write_private_sint_single_v4 port_memory_write_private_sint32_v4

// 8-vector of signed integers (single size)
#define port_memory_write_global_sint_single_v8 port_memory_write_global_sint32_v8
#define port_memory_write_constant_sint_single_v8 port_memory_write_constant_sint32_v8
#define port_memory_write_local_sint_single_v8 port_memory_write_local_sint32_v8
#define port_memory_write_private_sint_single_v8 port_memory_write_private_sint32_v8

// 16-vector of signed integers (single size)
#define port_memory_write_global_sint_single_v16 port_memory_write_global_sint32_v16
#define port_memory_write_constant_sint_single_v16 port_memory_write_constant_sint32_v16
#define port_memory_write_local_sint_single_v16 port_memory_write_local_sint32_v16
#define port_memory_write_private_sint_single_v16 port_memory_write_private_sint32_v16

// Signed integer (double size)
#define port_memory_write_global_sint_double port_memory_write_global_sint64
#define port_memory_write_constant_sint_double port_memory_write_constant_sint64
#define port_memory_write_local_sint_double port_memory_write_local_sint64
#define port_memory_write_private_sint_double port_memory_write_private_sint64

// 2-vector of signed integers (double size)
#define port_memory_write_global_sint_double_v2 port_memory_write_global_sint64_v2
#define port_memory_write_constant_sint_double_v2 port_memory_write_constant_sint64_v2
#define port_memory_write_local_sint_double_v2 port_memory_write_local_sint64_v2
#define port_memory_write_private_sint_double_v2 port_memory_write_private_sint64_v2

// 3-vector of signed integers (double size)
#define port_memory_write_global_sint_double_v3 port_memory_write_global_sint64_v3
#define port_memory_write_constant_sint_double_v3 port_memory_write_constant_sint64_v3
#define port_memory_write_local_sint_double_v3 port_memory_write_local_sint64_v3
#define port_memory_write_private_sint_double_v3 port_memory_write_private_sint64_v3

// 4-vector of signed integers (double size)
#define port_memory_write_global_sint_double_v4 port_memory_write_global_sint64_v4
#define port_memory_write_constant_sint_double_v4 port_memory_write_constant_sint64_v4
#define port_memory_write_local_sint_double_v4 port_memory_write_local_sint64_v4
#define port_memory_write_private_sint_double_v4 port_memory_write_private_sint64_v4

// 8-vector of signed integers (double size)
#define port_memory_write_global_sint_double_v8 port_memory_write_global_sint64_v8
#define port_memory_write_constant_sint_double_v8 port_memory_write_constant_sint64_v8
#define port_memory_write_local_sint_double_v8 port_memory_write_local_sint64_v8
#define port_memory_write_private_sint_double_v8 port_memory_write_private_sint64_v8

// 16-vector of signed integers (double size)
#define port_memory_write_global_sint_double_v16 port_memory_write_global_sint64_v16
#define port_memory_write_constant_sint_double_v16 port_memory_write_constant_sint64_v16
#define port_memory_write_local_sint_double_v16 port_memory_write_local_sint64_v16
#define port_memory_write_private_sint_double_v16 port_memory_write_private_sint64_v16

// Floating-point number (half size)
#define port_memory_write_global_float_half port_memory_write_global_float16
#define port_memory_write_constant_float_half port_memory_write_constant_float16
#define port_memory_write_local_float_half port_memory_write_local_float16
#define port_memory_write_private_float_half port_memory_write_private_float16

// 2-vector of floating-point numbers (half size)
#define port_memory_write_global_float_half_v2 port_memory_write_global_float16_v2
#define port_memory_write_constant_float_half_v2 port_memory_write_constant_float16_v2
#define port_memory_write_local_float_half_v2 port_memory_write_local_float16_v2
#define port_memory_write_private_float_half_v2 port_memory_write_private_float16_v2

// 3-vector of floating-point numbers (half size)
#define port_memory_write_global_float_half_v3 port_memory_write_global_float16_v3
#define port_memory_write_constant_float_half_v3 port_memory_write_constant_float16_v3
#define port_memory_write_local_float_half_v3 port_memory_write_local_float16_v3
#define port_memory_write_private_float_half_v3 port_memory_write_private_float16_v3

// 4-vector of floating-point numbers (half size)
#define port_memory_write_global_float_half_v4 port_memory_write_global_float16_v4
#define port_memory_write_constant_float_half_v4 port_memory_write_constant_float16_v4
#define port_memory_write_local_float_half_v4 port_memory_write_local_float16_v4
#define port_memory_write_private_float_half_v4 port_memory_write_private_float16_v4

// 8-vector of floating-point numbers (half size)
#define port_memory_write_global_float_half_v8 port_memory_write_global_float16_v8
#define port_memory_write_constant_float_half_v8 port_memory_write_constant_float16_v8
#define port_memory_write_local_float_half_v8 port_memory_write_local_float16_v8
#define port_memory_write_private_float_half_v8 port_memory_write_private_float16_v8

// 16-vector of floating-point numbers (half size)
#define port_memory_write_global_float_half_v16 port_memory_write_global_float16_v16
#define port_memory_write_constant_float_half_v16 port_memory_write_constant_float16_v16
#define port_memory_write_local_float_half_v16 port_memory_write_local_float16_v16
#define port_memory_write_private_float_half_v16 port_memory_write_private_float16_v16

// Floating-point number (single size)
#define port_memory_write_global_float_single port_memory_write_global_float32
#define port_memory_write_constant_float_single port_memory_write_constant_float32
#define port_memory_write_local_float_single port_memory_write_local_float32
#define port_memory_write_private_float_single port_memory_write_private_float32

// 2-vector of floating-point numbers (single size)
#define port_memory_write_global_float_single_v2 port_memory_write_global_float32_v2
#define port_memory_write_constant_float_single_v2 port_memory_write_constant_float32_v2
#define port_memory_write_local_float_single_v2 port_memory_write_local_float32_v2
#define port_memory_write_private_float_single_v2 port_memory_write_private_float32_v2

// 3-vector of floating-point numbers (single size)
#define port_memory_write_global_float_single_v3 port_memory_write_global_float32_v3
#define port_memory_write_constant_float_single_v3 port_memory_write_constant_float32_v3
#define port_memory_write_local_float_single_v3 port_memory_write_local_float32_v3
#define port_memory_write_private_float_single_v3 port_memory_write_private_float32_v3

// 4-vector of floating-point numbers (single size)
#define port_memory_write_global_float_single_v4 port_memory_write_global_float32_v4
#define port_memory_write_constant_float_single_v4 port_memory_write_constant_float32_v4
#define port_memory_write_local_float_single_v4 port_memory_write_local_float32_v4
#define port_memory_write_private_float_single_v4 port_memory_write_private_float32_v4

// 8-vector of floating-point numbers (single size)
#define port_memory_write_global_float_single_v8 port_memory_write_global_float32_v8
#define port_memory_write_constant_float_single_v8 port_memory_write_constant_float32_v8
#define port_memory_write_local_float_single_v8 port_memory_write_local_float32_v8
#define port_memory_write_private_float_single_v8 port_memory_write_private_float32_v8

// 16-vector of floating-point numbers (single size)
#define port_memory_write_global_float_single_v16 port_memory_write_global_float32_v16
#define port_memory_write_constant_float_single_v16 port_memory_write_constant_float32_v16
#define port_memory_write_local_float_single_v16 port_memory_write_local_float32_v16
#define port_memory_write_private_float_single_v16 port_memory_write_private_float32_v16

// Floating-point number (double size)
#define port_memory_write_global_float_double port_memory_write_global_float64
#define port_memory_write_constant_float_double port_memory_write_constant_float64
#define port_memory_write_local_float_double port_memory_write_local_float64
#define port_memory_write_private_float_double port_memory_write_private_float64

// 2-vector of floating-point numbers (double size)
#define port_memory_write_global_float_double_v2 port_memory_write_global_float64_v2
#define port_memory_write_constant_float_double_v2 port_memory_write_constant_float64_v2
#define port_memory_write_local_float_double_v2 port_memory_write_local_float64_v2
#define port_memory_write_private_float_double_v2 port_memory_write_private_float64_v2

// 3-vector of floating-point numbers (double size)
#define port_memory_write_global_float_double_v3 port_memory_write_global_float64_v3
#define port_memory_write_constant_float_double_v3 port_memory_write_constant_float64_v3
#define port_memory_write_local_float_double_v3 port_memory_write_local_float64_v3
#define port_memory_write_private_float_double_v3 port_memory_write_private_float64_v3

// 4-vector of floating-point numbers (double size)
#define port_memory_write_global_float_double_v4 port_memory_write_global_float64_v4
#define port_memory_write_constant_float_double_v4 port_memory_write_constant_float64_v4
#define port_memory_write_local_float_double_v4 port_memory_write_local_float64_v4
#define port_memory_write_private_float_double_v4 port_memory_write_private_float64_v4

// 8-vector of floating-point numbers (double size)
#define port_memory_write_global_float_double_v8 port_memory_write_global_float64_v8
#define port_memory_write_constant_float_double_v8 port_memory_write_constant_float64_v8
#define port_memory_write_local_float_double_v8 port_memory_write_local_float64_v8
#define port_memory_write_private_float_double_v8 port_memory_write_private_float64_v8

// 16-vector of floating-point numbers (double size)
#define port_memory_write_global_float_double_v16 port_memory_write_global_float64_v16
#define port_memory_write_constant_float_double_v16 port_memory_write_constant_float64_v16
#define port_memory_write_local_float_double_v16 port_memory_write_local_float64_v16
#define port_memory_write_private_float_double_v16 port_memory_write_private_float64_v16

#ifndef PORT_FEATURE_DEFAULT_INTEGER_64

// Default unsigned integer
#define port_memory_write_global_uint port_memory_write_global_uint32
#define port_memory_write_constant_uint port_memory_write_constant_uint32
#define port_memory_write_local_uint port_memory_write_local_uint32
#define port_memory_write_private_uint port_memory_write_private_uint32

// 2-vector of default unsigned integers (single size)
#define port_memory_write_global_uint_v2 port_memory_write_global_uint32_v2
#define port_memory_write_constant_uint_v2 port_memory_write_constant_uint32_v2
#define port_memory_write_local_uint_v2 port_memory_write_local_uint32_v2
#define port_memory_write_private_uint_v2 port_memory_write_private_uint32_v2

// 3-vector of default unsigned integers (single size)
#define port_memory_write_global_uint_v3 port_memory_write_global_uint32_v3
#define port_memory_write_constant_uint_v3 port_memory_write_constant_uint32_v3
#define port_memory_write_local_uint_v3 port_memory_write_local_uint32_v3
#define port_memory_write_private_uint_v3 port_memory_write_private_uint32_v3

// 4-vector of default unsigned integers (single size)
#define port_memory_write_global_uint_v4 port_memory_write_global_uint32_v4
#define port_memory_write_constant_uint_v4 port_memory_write_constant_uint32_v4
#define port_memory_write_local_uint_v4 port_memory_write_local_uint32_v4
#define port_memory_write_private_uint_v4 port_memory_write_private_uint32_v4

// 8-vector of default unsigned integers (single size)
#define port_memory_write_global_uint_v8 port_memory_write_global_uint32_v8
#define port_memory_write_constant_uint_v8 port_memory_write_constant_uint32_v8
#define port_memory_write_local_uint_v8 port_memory_write_local_uint32_v8
#define port_memory_write_private_uint_v8 port_memory_write_private_uint32_v8

// 16-vector of default unsigned integers (single size)
#define port_memory_write_global_uint_v16 port_memory_write_global_uint32_v16
#define port_memory_write_constant_uint_v16 port_memory_write_constant_uint32_v16
#define port_memory_write_local_uint_v16 port_memory_write_local_uint32_v16
#define port_memory_write_private_uint_v16 port_memory_write_private_uint32_v16

// Default signed integer
#define port_memory_write_global_sint port_memory_write_global_sint32
#define port_memory_write_constant_sint port_memory_write_constant_sint32
#define port_memory_write_local_sint port_memory_write_local_sint32
#define port_memory_write_private_sint port_memory_write_private_sint32

// 2-vector of default signed integers (single size)
#define port_memory_write_global_sint_v2 port_memory_write_global_sint32_v2
#define port_memory_write_constant_sint_v2 port_memory_write_constant_sint32_v2
#define port_memory_write_local_sint_v2 port_memory_write_local_sint32_v2
#define port_memory_write_private_sint_v2 port_memory_write_private_sint32_v2

// 3-vector of default signed integers (single size)
#define port_memory_write_global_sint_v3 port_memory_write_global_sint32_v3
#define port_memory_write_constant_sint_v3 port_memory_write_constant_sint32_v3
#define port_memory_write_local_sint_v3 port_memory_write_local_sint32_v3
#define port_memory_write_private_sint_v3 port_memory_write_private_sint32_v3

// 4-vector of default signed integers (single size)
#define port_memory_write_global_sint_v4 port_memory_write_global_sint32_v4
#define port_memory_write_constant_sint_v4 port_memory_write_constant_sint32_v4
#define port_memory_write_local_sint_v4 port_memory_write_local_sint32_v4
#define port_memory_write_private_sint_v4 port_memory_write_private_sint32_v4

// 8-vector of default signed integers (single size)
#define port_memory_write_global_sint_v8 port_memory_write_global_sint32_v8
#define port_memory_write_constant_sint_v8 port_memory_write_constant_sint32_v8
#define port_memory_write_local_sint_v8 port_memory_write_local_sint32_v8
#define port_memory_write_private_sint_v8 port_memory_write_private_sint32_v8

// 16-vector of default signed integers (single size)
#define port_memory_write_global_sint_v16 port_memory_write_global_sint32_v16
#define port_memory_write_constant_sint_v16 port_memory_write_constant_sint32_v16
#define port_memory_write_local_sint_v16 port_memory_write_local_sint32_v16
#define port_memory_write_private_sint_v16 port_memory_write_private_sint32_v16

#else // PORT_FEATURE_DEFAULT_INTEGER_64

// Default unsigned integer
#define port_memory_write_global_uint port_memory_write_global_uint64
#define port_memory_write_constant_uint port_memory_write_constant_uint64
#define port_memory_write_local_uint port_memory_write_local_uint64
#define port_memory_write_private_uint port_memory_write_private_uint64

// 2-vector of default unsigned integers (single size)
#define port_memory_write_global_uint_v2 port_memory_write_global_uint64_v2
#define port_memory_write_constant_uint_v2 port_memory_write_constant_uint64_v2
#define port_memory_write_local_uint_v2 port_memory_write_local_uint64_v2
#define port_memory_write_private_uint_v2 port_memory_write_private_uint64_v2

// 3-vector of default unsigned integers (single size)
#define port_memory_write_global_uint_v3 port_memory_write_global_uint64_v3
#define port_memory_write_constant_uint_v3 port_memory_write_constant_uint64_v3
#define port_memory_write_local_uint_v3 port_memory_write_local_uint64_v3
#define port_memory_write_private_uint_v3 port_memory_write_private_uint64_v3

// 4-vector of default unsigned integers (single size)
#define port_memory_write_global_uint_v4 port_memory_write_global_uint64_v4
#define port_memory_write_constant_uint_v4 port_memory_write_constant_uint64_v4
#define port_memory_write_local_uint_v4 port_memory_write_local_uint64_v4
#define port_memory_write_private_uint_v4 port_memory_write_private_uint64_v4

// 8-vector of default unsigned integers (single size)
#define port_memory_write_global_uint_v8 port_memory_write_global_uint64_v8
#define port_memory_write_constant_uint_v8 port_memory_write_constant_uint64_v8
#define port_memory_write_local_uint_v8 port_memory_write_local_uint64_v8
#define port_memory_write_private_uint_v8 port_memory_write_private_uint64_v8

// 16-vector of default unsigned integers (single size)
#define port_memory_write_global_uint_v16 port_memory_write_global_uint64_v16
#define port_memory_write_constant_uint_v16 port_memory_write_constant_uint64_v16
#define port_memory_write_local_uint_v16 port_memory_write_local_uint64_v16
#define port_memory_write_private_uint_v16 port_memory_write_private_uint64_v16

// Default signed integer
#define port_memory_write_global_sint port_memory_write_global_sint64
#define port_memory_write_constant_sint port_memory_write_constant_sint64
#define port_memory_write_local_sint port_memory_write_local_sint64
#define port_memory_write_private_sint port_memory_write_private_sint64

// 2-vector of default signed integers (single size)
#define port_memory_write_global_sint_v2 port_memory_write_global_sint64_v2
#define port_memory_write_constant_sint_v2 port_memory_write_constant_sint64_v2
#define port_memory_write_local_sint_v2 port_memory_write_local_sint64_v2
#define port_memory_write_private_sint_v2 port_memory_write_private_sint64_v2

// 3-vector of default signed integers (single size)
#define port_memory_write_global_sint_v3 port_memory_write_global_sint64_v3
#define port_memory_write_constant_sint_v3 port_memory_write_constant_sint64_v3
#define port_memory_write_local_sint_v3 port_memory_write_local_sint64_v3
#define port_memory_write_private_sint_v3 port_memory_write_private_sint64_v3

// 4-vector of default signed integers (single size)
#define port_memory_write_global_sint_v4 port_memory_write_global_sint64_v4
#define port_memory_write_constant_sint_v4 port_memory_write_constant_sint64_v4
#define port_memory_write_local_sint_v4 port_memory_write_local_sint64_v4
#define port_memory_write_private_sint_v4 port_memory_write_private_sint64_v4

// 8-vector of default signed integers (single size)
#define port_memory_write_global_sint_v8 port_memory_write_global_sint64_v8
#define port_memory_write_constant_sint_v8 port_memory_write_constant_sint64_v8
#define port_memory_write_local_sint_v8 port_memory_write_local_sint64_v8
#define port_memory_write_private_sint_v8 port_memory_write_private_sint64_v8

// 16-vector of default signed integers (single size)
#define port_memory_write_global_sint_v16 port_memory_write_global_sint64_v16
#define port_memory_write_constant_sint_v16 port_memory_write_constant_sint64_v16
#define port_memory_write_local_sint_v16 port_memory_write_local_sint64_v16
#define port_memory_write_private_sint_v16 port_memory_write_private_sint64_v16

#endif // PORT_FEATURE_DEFAULT_INTEGER_64

#ifndef PORT_FEATURE_DEFAULT_FLOAT_64

// Default floating-point number
#define port_memory_write_global_float port_memory_write_global_float32
#define port_memory_write_constant_float port_memory_write_constant_float32
#define port_memory_write_local_float port_memory_write_local_float32
#define port_memory_write_private_float port_memory_write_private_float32

// 2-vector of default floating-point numbers (single size)
#define port_memory_write_global_float_v2 port_memory_write_global_float32_v2
#define port_memory_write_constant_float_v2 port_memory_write_constant_float32_v2
#define port_memory_write_local_float_v2 port_memory_write_local_float32_v2
#define port_memory_write_private_float_v2 port_memory_write_private_float32_v2

// 3-vector of default floating-point numbers (single size)
#define port_memory_write_global_float_v3 port_memory_write_global_float32_v3
#define port_memory_write_constant_float_v3 port_memory_write_constant_float32_v3
#define port_memory_write_local_float_v3 port_memory_write_local_float32_v3
#define port_memory_write_private_float_v3 port_memory_write_private_float32_v3

// 4-vector of default floating-point numbers (single size)
#define port_memory_write_global_float_v4 port_memory_write_global_float32_v4
#define port_memory_write_constant_float_v4 port_memory_write_constant_float32_v4
#define port_memory_write_local_float_v4 port_memory_write_local_float32_v4
#define port_memory_write_private_float_v4 port_memory_write_private_float32_v4

// 8-vector of default floating-point numbers (single size)
#define port_memory_write_global_float_v8 port_memory_write_global_float32_v8
#define port_memory_write_constant_float_v8 port_memory_write_constant_float32_v8
#define port_memory_write_local_float_v8 port_memory_write_local_float32_v8
#define port_memory_write_private_float_v8 port_memory_write_private_float32_v8

// 16-vector of default floating-point numbers (single size)
#define port_memory_write_global_float_v16 port_memory_write_global_float32_v16
#define port_memory_write_constant_float_v16 port_memory_write_constant_float32_v16
#define port_memory_write_local_float_v16 port_memory_write_local_float32_v16
#define port_memory_write_private_float_v16 port_memory_write_private_float32_v16

#else // PORT_FEATURE_DEFAULT_FLOAT_64

// Default floating-point number
#define port_memory_write_global_float port_memory_write_global_float64
#define port_memory_write_constant_float port_memory_write_constant_float64
#define port_memory_write_local_float port_memory_write_local_float64
#define port_memory_write_private_float port_memory_write_private_float64

// 2-vector of default floating-point numbers (single size)
#define port_memory_write_global_float_v2 port_memory_write_global_float64_v2
#define port_memory_write_constant_float_v2 port_memory_write_constant_float64_v2
#define port_memory_write_local_float_v2 port_memory_write_local_float64_v2
#define port_memory_write_private_float_v2 port_memory_write_private_float64_v2

// 3-vector of default floating-point numbers (single size)
#define port_memory_write_global_float_v3 port_memory_write_global_float64_v3
#define port_memory_write_constant_float_v3 port_memory_write_constant_float64_v3
#define port_memory_write_local_float_v3 port_memory_write_local_float64_v3
#define port_memory_write_private_float_v3 port_memory_write_private_float64_v3

// 4-vector of default floating-point numbers (single size)
#define port_memory_write_global_float_v4 port_memory_write_global_float64_v4
#define port_memory_write_constant_float_v4 port_memory_write_constant_float64_v4
#define port_memory_write_local_float_v4 port_memory_write_local_float64_v4
#define port_memory_write_private_float_v4 port_memory_write_private_float64_v4

// 8-vector of default floating-point numbers (single size)
#define port_memory_write_global_float_v8 port_memory_write_global_float64_v8
#define port_memory_write_constant_float_v8 port_memory_write_constant_float64_v8
#define port_memory_write_local_float_v8 port_memory_write_local_float64_v8
#define port_memory_write_private_float_v8 port_memory_write_private_float64_v8

// 16-vector of default floating-point numbers (single size)
#define port_memory_write_global_float_v16 port_memory_write_global_float64_v16
#define port_memory_write_constant_float_v16 port_memory_write_constant_float64_v16
#define port_memory_write_local_float_v16 port_memory_write_local_float64_v16
#define port_memory_write_private_float_v16 port_memory_write_private_float64_v16

#endif // PORT_FEATURE_DEFAULT_FLOAT_64

#endif // _PORT_CDEV_MEMORY_FUN_H_

