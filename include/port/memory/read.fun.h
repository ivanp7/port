/****************************************************************************
 * Copyright (C) 2020-2026 by Ivan Podmazov                                 *
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

#pragma once
#ifndef _PORT_MEMORY_READ_FUN_H_
#define _PORT_MEMORY_READ_FUN_H_

#include "port/pointer.typ.h"


///////////////////////////////////////////////////////////////////////////////
// Functions for built-in types (generic address space)
///////////////////////////////////////////////////////////////////////////////

// Unsigned integer (8-bit)
port_uint8_t port_memory_read_uint8(port_const_void_ptr_t memory, size_t offset);
port_uint8_v2_t port_memory_read_uint8_v2(port_const_void_ptr_t memory, size_t offset);
port_uint8_v3_t port_memory_read_uint8_v3(port_const_void_ptr_t memory, size_t offset);
port_uint8_v4_t port_memory_read_uint8_v4(port_const_void_ptr_t memory, size_t offset);
port_uint8_v8_t port_memory_read_uint8_v8(port_const_void_ptr_t memory, size_t offset);
port_uint8_v16_t port_memory_read_uint8_v16(port_const_void_ptr_t memory, size_t offset);

// Unsigned integer (16-bit)
port_uint16_t port_memory_read_uint16(port_const_void_ptr_t memory, size_t offset);
port_uint16_v2_t port_memory_read_uint16_v2(port_const_void_ptr_t memory, size_t offset);
port_uint16_v3_t port_memory_read_uint16_v3(port_const_void_ptr_t memory, size_t offset);
port_uint16_v4_t port_memory_read_uint16_v4(port_const_void_ptr_t memory, size_t offset);
port_uint16_v8_t port_memory_read_uint16_v8(port_const_void_ptr_t memory, size_t offset);
port_uint16_v16_t port_memory_read_uint16_v16(port_const_void_ptr_t memory, size_t offset);

// Unsigned integer (32-bit)
port_uint32_t port_memory_read_uint32(port_const_void_ptr_t memory, size_t offset);
port_uint32_v2_t port_memory_read_uint32_v2(port_const_void_ptr_t memory, size_t offset);
port_uint32_v3_t port_memory_read_uint32_v3(port_const_void_ptr_t memory, size_t offset);
port_uint32_v4_t port_memory_read_uint32_v4(port_const_void_ptr_t memory, size_t offset);
port_uint32_v8_t port_memory_read_uint32_v8(port_const_void_ptr_t memory, size_t offset);
port_uint32_v16_t port_memory_read_uint32_v16(port_const_void_ptr_t memory, size_t offset);

// Unsigned integer (64-bit)
port_uint64_t port_memory_read_uint64(port_const_void_ptr_t memory, size_t offset);
port_uint64_v2_t port_memory_read_uint64_v2(port_const_void_ptr_t memory, size_t offset);
port_uint64_v3_t port_memory_read_uint64_v3(port_const_void_ptr_t memory, size_t offset);
port_uint64_v4_t port_memory_read_uint64_v4(port_const_void_ptr_t memory, size_t offset);
port_uint64_v8_t port_memory_read_uint64_v8(port_const_void_ptr_t memory, size_t offset);
port_uint64_v16_t port_memory_read_uint64_v16(port_const_void_ptr_t memory, size_t offset);

// Signed integer (8-bit)
port_sint8_t port_memory_read_sint8(port_const_void_ptr_t memory, size_t offset);
port_sint8_v2_t port_memory_read_sint8_v2(port_const_void_ptr_t memory, size_t offset);
port_sint8_v3_t port_memory_read_sint8_v3(port_const_void_ptr_t memory, size_t offset);
port_sint8_v4_t port_memory_read_sint8_v4(port_const_void_ptr_t memory, size_t offset);
port_sint8_v8_t port_memory_read_sint8_v8(port_const_void_ptr_t memory, size_t offset);
port_sint8_v16_t port_memory_read_sint8_v16(port_const_void_ptr_t memory, size_t offset);

// Signed integer (16-bit)
port_sint16_t port_memory_read_sint16(port_const_void_ptr_t memory, size_t offset);
port_sint16_v2_t port_memory_read_sint16_v2(port_const_void_ptr_t memory, size_t offset);
port_sint16_v3_t port_memory_read_sint16_v3(port_const_void_ptr_t memory, size_t offset);
port_sint16_v4_t port_memory_read_sint16_v4(port_const_void_ptr_t memory, size_t offset);
port_sint16_v8_t port_memory_read_sint16_v8(port_const_void_ptr_t memory, size_t offset);
port_sint16_v16_t port_memory_read_sint16_v16(port_const_void_ptr_t memory, size_t offset);

// Signed integer (32-bit)
port_sint32_t port_memory_read_sint32(port_const_void_ptr_t memory, size_t offset);
port_sint32_v2_t port_memory_read_sint32_v2(port_const_void_ptr_t memory, size_t offset);
port_sint32_v3_t port_memory_read_sint32_v3(port_const_void_ptr_t memory, size_t offset);
port_sint32_v4_t port_memory_read_sint32_v4(port_const_void_ptr_t memory, size_t offset);
port_sint32_v8_t port_memory_read_sint32_v8(port_const_void_ptr_t memory, size_t offset);
port_sint32_v16_t port_memory_read_sint32_v16(port_const_void_ptr_t memory, size_t offset);

// Signed integer (64-bit)
port_sint64_t port_memory_read_sint64(port_const_void_ptr_t memory, size_t offset);
port_sint64_v2_t port_memory_read_sint64_v2(port_const_void_ptr_t memory, size_t offset);
port_sint64_v3_t port_memory_read_sint64_v3(port_const_void_ptr_t memory, size_t offset);
port_sint64_v4_t port_memory_read_sint64_v4(port_const_void_ptr_t memory, size_t offset);
port_sint64_v8_t port_memory_read_sint64_v8(port_const_void_ptr_t memory, size_t offset);
port_sint64_v16_t port_memory_read_sint64_v16(port_const_void_ptr_t memory, size_t offset);

// Floating-point number (16-bit)
port_float32_t port_memory_read_float16(port_const_void_ptr_t memory, size_t offset);
port_float32_v2_t port_memory_read_float16_v2(port_const_void_ptr_t memory, size_t offset);
port_float32_v3_t port_memory_read_float16_v3(port_const_void_ptr_t memory, size_t offset);
port_float32_v4_t port_memory_read_float16_v4(port_const_void_ptr_t memory, size_t offset);
port_float32_v8_t port_memory_read_float16_v8(port_const_void_ptr_t memory, size_t offset);
port_float32_v16_t port_memory_read_float16_v16(port_const_void_ptr_t memory, size_t offset);

// Floating-point number (32-bit)
port_float32_t port_memory_read_float32(port_const_void_ptr_t memory, size_t offset);
port_float32_v2_t port_memory_read_float32_v2(port_const_void_ptr_t memory, size_t offset);
port_float32_v3_t port_memory_read_float32_v3(port_const_void_ptr_t memory, size_t offset);
port_float32_v4_t port_memory_read_float32_v4(port_const_void_ptr_t memory, size_t offset);
port_float32_v8_t port_memory_read_float32_v8(port_const_void_ptr_t memory, size_t offset);
port_float32_v16_t port_memory_read_float32_v16(port_const_void_ptr_t memory, size_t offset);

// Floating-point number (64-bit)
port_float64_t port_memory_read_float64(port_const_void_ptr_t memory, size_t offset);
port_float64_v2_t port_memory_read_float64_v2(port_const_void_ptr_t memory, size_t offset);
port_float64_v3_t port_memory_read_float64_v3(port_const_void_ptr_t memory, size_t offset);
port_float64_v4_t port_memory_read_float64_v4(port_const_void_ptr_t memory, size_t offset);
port_float64_v8_t port_memory_read_float64_v8(port_const_void_ptr_t memory, size_t offset);
port_float64_v16_t port_memory_read_float64_v16(port_const_void_ptr_t memory, size_t offset);

#ifdef __OPENCL_C_VERSION__

///////////////////////////////////////////////////////////////////////////////
// Functions for built-in types (named address spaces)
///////////////////////////////////////////////////////////////////////////////

// Unsigned integer (8-bit)
port_uint8_t port_memory_read_local_uint8(port_const_local_void_ptr_t memory, size_t offset);
port_uint8_t port_memory_read_global_uint8(port_const_global_void_ptr_t memory, size_t offset);
port_uint8_t port_memory_read_constant_uint8(port_constant_void_ptr_t memory, size_t offset);

// 2-vector of unsigned integers (8-bit)
port_uint8_v2_t port_memory_read_local_uint8_v2(port_const_local_void_ptr_t memory, size_t offset);
port_uint8_v2_t port_memory_read_global_uint8_v2(port_const_global_void_ptr_t memory, size_t offset);
port_uint8_v2_t port_memory_read_constant_uint8_v2(port_constant_void_ptr_t memory, size_t offset);

// 3-vector of unsigned integers (8-bit)
port_uint8_v3_t port_memory_read_local_uint8_v3(port_const_local_void_ptr_t memory, size_t offset);
port_uint8_v3_t port_memory_read_global_uint8_v3(port_const_global_void_ptr_t memory, size_t offset);
port_uint8_v3_t port_memory_read_constant_uint8_v3(port_constant_void_ptr_t memory, size_t offset);

// 4-vector of unsigned integers (8-bit)
port_uint8_v4_t port_memory_read_local_uint8_v4(port_const_local_void_ptr_t memory, size_t offset);
port_uint8_v4_t port_memory_read_global_uint8_v4(port_const_global_void_ptr_t memory, size_t offset);
port_uint8_v4_t port_memory_read_constant_uint8_v4(port_constant_void_ptr_t memory, size_t offset);

// 8-vector of unsigned integers (8-bit)
port_uint8_v8_t port_memory_read_local_uint8_v8(port_const_local_void_ptr_t memory, size_t offset);
port_uint8_v8_t port_memory_read_global_uint8_v8(port_const_global_void_ptr_t memory, size_t offset);
port_uint8_v8_t port_memory_read_constant_uint8_v8(port_constant_void_ptr_t memory, size_t offset);

// 16-vector of unsigned integers (8-bit)
port_uint8_v16_t port_memory_read_local_uint8_v16(port_const_local_void_ptr_t memory, size_t offset);
port_uint8_v16_t port_memory_read_global_uint8_v16(port_const_global_void_ptr_t memory, size_t offset);
port_uint8_v16_t port_memory_read_constant_uint8_v16(port_constant_void_ptr_t memory, size_t offset);


// Unsigned integer (16-bit)
port_uint16_t port_memory_read_local_uint16(port_const_local_void_ptr_t memory, size_t offset);
port_uint16_t port_memory_read_global_uint16(port_const_global_void_ptr_t memory, size_t offset);
port_uint16_t port_memory_read_constant_uint16(port_constant_void_ptr_t memory, size_t offset);

// 2-vector of unsigned integers (16-bit)
port_uint16_v2_t port_memory_read_local_uint16_v2(port_const_local_void_ptr_t memory, size_t offset);
port_uint16_v2_t port_memory_read_global_uint16_v2(port_const_global_void_ptr_t memory, size_t offset);
port_uint16_v2_t port_memory_read_constant_uint16_v2(port_constant_void_ptr_t memory, size_t offset);

// 3-vector of unsigned integers (16-bit)
port_uint16_v3_t port_memory_read_local_uint16_v3(port_const_local_void_ptr_t memory, size_t offset);
port_uint16_v3_t port_memory_read_global_uint16_v3(port_const_global_void_ptr_t memory, size_t offset);
port_uint16_v3_t port_memory_read_constant_uint16_v3(port_constant_void_ptr_t memory, size_t offset);

// 4-vector of unsigned integers (16-bit)
port_uint16_v4_t port_memory_read_local_uint16_v4(port_const_local_void_ptr_t memory, size_t offset);
port_uint16_v4_t port_memory_read_global_uint16_v4(port_const_global_void_ptr_t memory, size_t offset);
port_uint16_v4_t port_memory_read_constant_uint16_v4(port_constant_void_ptr_t memory, size_t offset);

// 8-vector of unsigned integers (16-bit)
port_uint16_v8_t port_memory_read_local_uint16_v8(port_const_local_void_ptr_t memory, size_t offset);
port_uint16_v8_t port_memory_read_global_uint16_v8(port_const_global_void_ptr_t memory, size_t offset);
port_uint16_v8_t port_memory_read_constant_uint16_v8(port_constant_void_ptr_t memory, size_t offset);

// 16-vector of unsigned integers (16-bit)
port_uint16_v16_t port_memory_read_local_uint16_v16(port_const_local_void_ptr_t memory, size_t offset);
port_uint16_v16_t port_memory_read_global_uint16_v16(port_const_global_void_ptr_t memory, size_t offset);
port_uint16_v16_t port_memory_read_constant_uint16_v16(port_constant_void_ptr_t memory, size_t offset);


// Unsigned integer (32-bit)
port_uint32_t port_memory_read_local_uint32(port_const_local_void_ptr_t memory, size_t offset);
port_uint32_t port_memory_read_global_uint32(port_const_global_void_ptr_t memory, size_t offset);
port_uint32_t port_memory_read_constant_uint32(port_constant_void_ptr_t memory, size_t offset);

// 2-vector of unsigned integers (32-bit)
port_uint32_v2_t port_memory_read_local_uint32_v2(port_const_local_void_ptr_t memory, size_t offset);
port_uint32_v2_t port_memory_read_global_uint32_v2(port_const_global_void_ptr_t memory, size_t offset);
port_uint32_v2_t port_memory_read_constant_uint32_v2(port_constant_void_ptr_t memory, size_t offset);

// 3-vector of unsigned integers (32-bit)
port_uint32_v3_t port_memory_read_local_uint32_v3(port_const_local_void_ptr_t memory, size_t offset);
port_uint32_v3_t port_memory_read_global_uint32_v3(port_const_global_void_ptr_t memory, size_t offset);
port_uint32_v3_t port_memory_read_constant_uint32_v3(port_constant_void_ptr_t memory, size_t offset);

// 4-vector of unsigned integers (32-bit)
port_uint32_v4_t port_memory_read_local_uint32_v4(port_const_local_void_ptr_t memory, size_t offset);
port_uint32_v4_t port_memory_read_global_uint32_v4(port_const_global_void_ptr_t memory, size_t offset);
port_uint32_v4_t port_memory_read_constant_uint32_v4(port_constant_void_ptr_t memory, size_t offset);

// 8-vector of unsigned integers (32-bit)
port_uint32_v8_t port_memory_read_local_uint32_v8(port_const_local_void_ptr_t memory, size_t offset);
port_uint32_v8_t port_memory_read_global_uint32_v8(port_const_global_void_ptr_t memory, size_t offset);
port_uint32_v8_t port_memory_read_constant_uint32_v8(port_constant_void_ptr_t memory, size_t offset);

// 16-vector of unsigned integers (32-bit)
port_uint32_v16_t port_memory_read_local_uint32_v16(port_const_local_void_ptr_t memory, size_t offset);
port_uint32_v16_t port_memory_read_global_uint32_v16(port_const_global_void_ptr_t memory, size_t offset);
port_uint32_v16_t port_memory_read_constant_uint32_v16(port_constant_void_ptr_t memory, size_t offset);


// Unsigned integer (64-bit)
port_uint64_t port_memory_read_local_uint64(port_const_local_void_ptr_t memory, size_t offset);
port_uint64_t port_memory_read_global_uint64(port_const_global_void_ptr_t memory, size_t offset);
port_uint64_t port_memory_read_constant_uint64(port_constant_void_ptr_t memory, size_t offset);

// 2-vector of unsigned integers (64-bit)
port_uint64_v2_t port_memory_read_local_uint64_v2(port_const_local_void_ptr_t memory, size_t offset);
port_uint64_v2_t port_memory_read_global_uint64_v2(port_const_global_void_ptr_t memory, size_t offset);
port_uint64_v2_t port_memory_read_constant_uint64_v2(port_constant_void_ptr_t memory, size_t offset);

// 3-vector of unsigned integers (64-bit)
port_uint64_v3_t port_memory_read_local_uint64_v3(port_const_local_void_ptr_t memory, size_t offset);
port_uint64_v3_t port_memory_read_global_uint64_v3(port_const_global_void_ptr_t memory, size_t offset);
port_uint64_v3_t port_memory_read_constant_uint64_v3(port_constant_void_ptr_t memory, size_t offset);

// 4-vector of unsigned integers (64-bit)
port_uint64_v4_t port_memory_read_local_uint64_v4(port_const_local_void_ptr_t memory, size_t offset);
port_uint64_v4_t port_memory_read_global_uint64_v4(port_const_global_void_ptr_t memory, size_t offset);
port_uint64_v4_t port_memory_read_constant_uint64_v4(port_constant_void_ptr_t memory, size_t offset);

// 8-vector of unsigned integers (64-bit)
port_uint64_v8_t port_memory_read_local_uint64_v8(port_const_local_void_ptr_t memory, size_t offset);
port_uint64_v8_t port_memory_read_global_uint64_v8(port_const_global_void_ptr_t memory, size_t offset);
port_uint64_v8_t port_memory_read_constant_uint64_v8(port_constant_void_ptr_t memory, size_t offset);

// 16-vector of unsigned integers (64-bit)
port_uint64_v16_t port_memory_read_local_uint64_v16(port_const_local_void_ptr_t memory, size_t offset);
port_uint64_v16_t port_memory_read_global_uint64_v16(port_const_global_void_ptr_t memory, size_t offset);
port_uint64_v16_t port_memory_read_constant_uint64_v16(port_constant_void_ptr_t memory, size_t offset);


// Signed integer (8-bit)
port_sint8_t port_memory_read_local_sint8(port_const_local_void_ptr_t memory, size_t offset);
port_sint8_t port_memory_read_global_sint8(port_const_global_void_ptr_t memory, size_t offset);
port_sint8_t port_memory_read_constant_sint8(port_constant_void_ptr_t memory, size_t offset);

// 2-vector of signed integers (8-bit)
port_sint8_v2_t port_memory_read_local_sint8_v2(port_const_local_void_ptr_t memory, size_t offset);
port_sint8_v2_t port_memory_read_global_sint8_v2(port_const_global_void_ptr_t memory, size_t offset);
port_sint8_v2_t port_memory_read_constant_sint8_v2(port_constant_void_ptr_t memory, size_t offset);

// 3-vector of signed integers (8-bit)
port_sint8_v3_t port_memory_read_local_sint8_v3(port_const_local_void_ptr_t memory, size_t offset);
port_sint8_v3_t port_memory_read_global_sint8_v3(port_const_global_void_ptr_t memory, size_t offset);
port_sint8_v3_t port_memory_read_constant_sint8_v3(port_constant_void_ptr_t memory, size_t offset);

// 4-vector of signed integers (8-bit)
port_sint8_v4_t port_memory_read_local_sint8_v4(port_const_local_void_ptr_t memory, size_t offset);
port_sint8_v4_t port_memory_read_global_sint8_v4(port_const_global_void_ptr_t memory, size_t offset);
port_sint8_v4_t port_memory_read_constant_sint8_v4(port_constant_void_ptr_t memory, size_t offset);

// 8-vector of signed integers (8-bit)
port_sint8_v8_t port_memory_read_local_sint8_v8(port_const_local_void_ptr_t memory, size_t offset);
port_sint8_v8_t port_memory_read_global_sint8_v8(port_const_global_void_ptr_t memory, size_t offset);
port_sint8_v8_t port_memory_read_constant_sint8_v8(port_constant_void_ptr_t memory, size_t offset);

// 16-vector of signed integers (8-bit)
port_sint8_v16_t port_memory_read_local_sint8_v16(port_const_local_void_ptr_t memory, size_t offset);
port_sint8_v16_t port_memory_read_global_sint8_v16(port_const_global_void_ptr_t memory, size_t offset);
port_sint8_v16_t port_memory_read_constant_sint8_v16(port_constant_void_ptr_t memory, size_t offset);


// Signed integer (16-bit)
port_sint16_t port_memory_read_local_sint16(port_const_local_void_ptr_t memory, size_t offset);
port_sint16_t port_memory_read_global_sint16(port_const_global_void_ptr_t memory, size_t offset);
port_sint16_t port_memory_read_constant_sint16(port_constant_void_ptr_t memory, size_t offset);

// 2-vector of signed integers (16-bit)
port_sint16_v2_t port_memory_read_local_sint16_v2(port_const_local_void_ptr_t memory, size_t offset);
port_sint16_v2_t port_memory_read_global_sint16_v2(port_const_global_void_ptr_t memory, size_t offset);
port_sint16_v2_t port_memory_read_constant_sint16_v2(port_constant_void_ptr_t memory, size_t offset);

// 3-vector of signed integers (16-bit)
port_sint16_v3_t port_memory_read_local_sint16_v3(port_const_local_void_ptr_t memory, size_t offset);
port_sint16_v3_t port_memory_read_global_sint16_v3(port_const_global_void_ptr_t memory, size_t offset);
port_sint16_v3_t port_memory_read_constant_sint16_v3(port_constant_void_ptr_t memory, size_t offset);

// 4-vector of signed integers (16-bit)
port_sint16_v4_t port_memory_read_local_sint16_v4(port_const_local_void_ptr_t memory, size_t offset);
port_sint16_v4_t port_memory_read_global_sint16_v4(port_const_global_void_ptr_t memory, size_t offset);
port_sint16_v4_t port_memory_read_constant_sint16_v4(port_constant_void_ptr_t memory, size_t offset);

// 8-vector of signed integers (16-bit)
port_sint16_v8_t port_memory_read_local_sint16_v8(port_const_local_void_ptr_t memory, size_t offset);
port_sint16_v8_t port_memory_read_global_sint16_v8(port_const_global_void_ptr_t memory, size_t offset);
port_sint16_v8_t port_memory_read_constant_sint16_v8(port_constant_void_ptr_t memory, size_t offset);

// 16-vector of signed integers (16-bit)
port_sint16_v16_t port_memory_read_local_sint16_v16(port_const_local_void_ptr_t memory, size_t offset);
port_sint16_v16_t port_memory_read_global_sint16_v16(port_const_global_void_ptr_t memory, size_t offset);
port_sint16_v16_t port_memory_read_constant_sint16_v16(port_constant_void_ptr_t memory, size_t offset);


// Signed integer (32-bit)
port_sint32_t port_memory_read_local_sint32(port_const_local_void_ptr_t memory, size_t offset);
port_sint32_t port_memory_read_global_sint32(port_const_global_void_ptr_t memory, size_t offset);
port_sint32_t port_memory_read_constant_sint32(port_constant_void_ptr_t memory, size_t offset);

// 2-vector of signed integers (32-bit)
port_sint32_v2_t port_memory_read_local_sint32_v2(port_const_local_void_ptr_t memory, size_t offset);
port_sint32_v2_t port_memory_read_global_sint32_v2(port_const_global_void_ptr_t memory, size_t offset);
port_sint32_v2_t port_memory_read_constant_sint32_v2(port_constant_void_ptr_t memory, size_t offset);

// 3-vector of signed integers (32-bit)
port_sint32_v3_t port_memory_read_local_sint32_v3(port_const_local_void_ptr_t memory, size_t offset);
port_sint32_v3_t port_memory_read_global_sint32_v3(port_const_global_void_ptr_t memory, size_t offset);
port_sint32_v3_t port_memory_read_constant_sint32_v3(port_constant_void_ptr_t memory, size_t offset);

// 4-vector of signed integers (32-bit)
port_sint32_v4_t port_memory_read_local_sint32_v4(port_const_local_void_ptr_t memory, size_t offset);
port_sint32_v4_t port_memory_read_global_sint32_v4(port_const_global_void_ptr_t memory, size_t offset);
port_sint32_v4_t port_memory_read_constant_sint32_v4(port_constant_void_ptr_t memory, size_t offset);

// 8-vector of signed integers (32-bit)
port_sint32_v8_t port_memory_read_local_sint32_v8(port_const_local_void_ptr_t memory, size_t offset);
port_sint32_v8_t port_memory_read_global_sint32_v8(port_const_global_void_ptr_t memory, size_t offset);
port_sint32_v8_t port_memory_read_constant_sint32_v8(port_constant_void_ptr_t memory, size_t offset);

// 16-vector of signed integers (32-bit)
port_sint32_v16_t port_memory_read_local_sint32_v16(port_const_local_void_ptr_t memory, size_t offset);
port_sint32_v16_t port_memory_read_global_sint32_v16(port_const_global_void_ptr_t memory, size_t offset);
port_sint32_v16_t port_memory_read_constant_sint32_v16(port_constant_void_ptr_t memory, size_t offset);


// Signed integer (64-bit)
port_sint64_t port_memory_read_local_sint64(port_const_local_void_ptr_t memory, size_t offset);
port_sint64_t port_memory_read_global_sint64(port_const_global_void_ptr_t memory, size_t offset);
port_sint64_t port_memory_read_constant_sint64(port_constant_void_ptr_t memory, size_t offset);

// 2-vector of signed integers (64-bit)
port_sint64_v2_t port_memory_read_local_sint64_v2(port_const_local_void_ptr_t memory, size_t offset);
port_sint64_v2_t port_memory_read_global_sint64_v2(port_const_global_void_ptr_t memory, size_t offset);
port_sint64_v2_t port_memory_read_constant_sint64_v2(port_constant_void_ptr_t memory, size_t offset);

// 3-vector of signed integers (64-bit)
port_sint64_v3_t port_memory_read_local_sint64_v3(port_const_local_void_ptr_t memory, size_t offset);
port_sint64_v3_t port_memory_read_global_sint64_v3(port_const_global_void_ptr_t memory, size_t offset);
port_sint64_v3_t port_memory_read_constant_sint64_v3(port_constant_void_ptr_t memory, size_t offset);

// 4-vector of signed integers (64-bit)
port_sint64_v4_t port_memory_read_local_sint64_v4(port_const_local_void_ptr_t memory, size_t offset);
port_sint64_v4_t port_memory_read_global_sint64_v4(port_const_global_void_ptr_t memory, size_t offset);
port_sint64_v4_t port_memory_read_constant_sint64_v4(port_constant_void_ptr_t memory, size_t offset);

// 8-vector of signed integers (64-bit)
port_sint64_v8_t port_memory_read_local_sint64_v8(port_const_local_void_ptr_t memory, size_t offset);
port_sint64_v8_t port_memory_read_global_sint64_v8(port_const_global_void_ptr_t memory, size_t offset);
port_sint64_v8_t port_memory_read_constant_sint64_v8(port_constant_void_ptr_t memory, size_t offset);

// 16-vector of signed integers (64-bit)
port_sint64_v16_t port_memory_read_local_sint64_v16(port_const_local_void_ptr_t memory, size_t offset);
port_sint64_v16_t port_memory_read_global_sint64_v16(port_const_global_void_ptr_t memory, size_t offset);
port_sint64_v16_t port_memory_read_constant_sint64_v16(port_constant_void_ptr_t memory, size_t offset);


// Floating-point number (16-bit)
port_float32_t port_memory_read_local_float16(port_const_local_void_ptr_t memory, size_t offset);
port_float32_t port_memory_read_global_float16(port_const_global_void_ptr_t memory, size_t offset);
port_float32_t port_memory_read_constant_float16(port_constant_void_ptr_t memory, size_t offset);

// 2-vector of floating-point numbers (16-bit)
port_float32_v2_t port_memory_read_local_float16_v2(port_const_local_void_ptr_t memory, size_t offset);
port_float32_v2_t port_memory_read_global_float16_v2(port_const_global_void_ptr_t memory, size_t offset);
port_float32_v2_t port_memory_read_constant_float16_v2(port_constant_void_ptr_t memory, size_t offset);

// 3-vector of floating-point numbers (16-bit)
port_float32_v3_t port_memory_read_local_float16_v3(port_const_local_void_ptr_t memory, size_t offset);
port_float32_v3_t port_memory_read_global_float16_v3(port_const_global_void_ptr_t memory, size_t offset);
port_float32_v3_t port_memory_read_constant_float16_v3(port_constant_void_ptr_t memory, size_t offset);

// 4-vector of floating-point numbers (16-bit)
port_float32_v4_t port_memory_read_local_float16_v4(port_const_local_void_ptr_t memory, size_t offset);
port_float32_v4_t port_memory_read_global_float16_v4(port_const_global_void_ptr_t memory, size_t offset);
port_float32_v4_t port_memory_read_constant_float16_v4(port_constant_void_ptr_t memory, size_t offset);

// 8-vector of floating-point numbers (16-bit)
port_float32_v8_t port_memory_read_local_float16_v8(port_const_local_void_ptr_t memory, size_t offset);
port_float32_v8_t port_memory_read_global_float16_v8(port_const_global_void_ptr_t memory, size_t offset);
port_float32_v8_t port_memory_read_constant_float16_v8(port_constant_void_ptr_t memory, size_t offset);

// 16-vector of floating-point numbers (16-bit)
port_float32_v16_t port_memory_read_local_float16_v16(port_const_local_void_ptr_t memory, size_t offset);
port_float32_v16_t port_memory_read_global_float16_v16(port_const_global_void_ptr_t memory, size_t offset);
port_float32_v16_t port_memory_read_constant_float16_v16(port_constant_void_ptr_t memory, size_t offset);


// Floating-point number (32-bit)
port_float32_t port_memory_read_local_float32(port_const_local_void_ptr_t memory, size_t offset);
port_float32_t port_memory_read_global_float32(port_const_global_void_ptr_t memory, size_t offset);
port_float32_t port_memory_read_constant_float32(port_constant_void_ptr_t memory, size_t offset);

// 2-vector of floating-point numbers (32-bit)
port_float32_v2_t port_memory_read_local_float32_v2(port_const_local_void_ptr_t memory, size_t offset);
port_float32_v2_t port_memory_read_global_float32_v2(port_const_global_void_ptr_t memory, size_t offset);
port_float32_v2_t port_memory_read_constant_float32_v2(port_constant_void_ptr_t memory, size_t offset);

// 3-vector of floating-point numbers (32-bit)
port_float32_v3_t port_memory_read_local_float32_v3(port_const_local_void_ptr_t memory, size_t offset);
port_float32_v3_t port_memory_read_global_float32_v3(port_const_global_void_ptr_t memory, size_t offset);
port_float32_v3_t port_memory_read_constant_float32_v3(port_constant_void_ptr_t memory, size_t offset);

// 4-vector of floating-point numbers (32-bit)
port_float32_v4_t port_memory_read_local_float32_v4(port_const_local_void_ptr_t memory, size_t offset);
port_float32_v4_t port_memory_read_global_float32_v4(port_const_global_void_ptr_t memory, size_t offset);
port_float32_v4_t port_memory_read_constant_float32_v4(port_constant_void_ptr_t memory, size_t offset);

// 8-vector of floating-point numbers (32-bit)
port_float32_v8_t port_memory_read_local_float32_v8(port_const_local_void_ptr_t memory, size_t offset);
port_float32_v8_t port_memory_read_global_float32_v8(port_const_global_void_ptr_t memory, size_t offset);
port_float32_v8_t port_memory_read_constant_float32_v8(port_constant_void_ptr_t memory, size_t offset);

// 16-vector of floating-point numbers (32-bit)
port_float32_v16_t port_memory_read_local_float32_v16(port_const_local_void_ptr_t memory, size_t offset);
port_float32_v16_t port_memory_read_global_float32_v16(port_const_global_void_ptr_t memory, size_t offset);
port_float32_v16_t port_memory_read_constant_float32_v16(port_constant_void_ptr_t memory, size_t offset);


// Floating-point number (64-bit)
port_float64_t port_memory_read_local_float64(port_const_local_void_ptr_t memory, size_t offset);
port_float64_t port_memory_read_global_float64(port_const_global_void_ptr_t memory, size_t offset);
port_float64_t port_memory_read_constant_float64(port_constant_void_ptr_t memory, size_t offset);

// 2-vector of floating-point numbers (64-bit)
port_float64_v2_t port_memory_read_local_float64_v2(port_const_local_void_ptr_t memory, size_t offset);
port_float64_v2_t port_memory_read_global_float64_v2(port_const_global_void_ptr_t memory, size_t offset);
port_float64_v2_t port_memory_read_constant_float64_v2(port_constant_void_ptr_t memory, size_t offset);

// 3-vector of floating-point numbers (64-bit)
port_float64_v3_t port_memory_read_local_float64_v3(port_const_local_void_ptr_t memory, size_t offset);
port_float64_v3_t port_memory_read_global_float64_v3(port_const_global_void_ptr_t memory, size_t offset);
port_float64_v3_t port_memory_read_constant_float64_v3(port_constant_void_ptr_t memory, size_t offset);

// 4-vector of floating-point numbers (64-bit)
port_float64_v4_t port_memory_read_local_float64_v4(port_const_local_void_ptr_t memory, size_t offset);
port_float64_v4_t port_memory_read_global_float64_v4(port_const_global_void_ptr_t memory, size_t offset);
port_float64_v4_t port_memory_read_constant_float64_v4(port_constant_void_ptr_t memory, size_t offset);

// 8-vector of floating-point numbers (64-bit)
port_float64_v8_t port_memory_read_local_float64_v8(port_const_local_void_ptr_t memory, size_t offset);
port_float64_v8_t port_memory_read_global_float64_v8(port_const_global_void_ptr_t memory, size_t offset);
port_float64_v8_t port_memory_read_constant_float64_v8(port_constant_void_ptr_t memory, size_t offset);

// 16-vector of floating-point numbers (64-bit)
port_float64_v16_t port_memory_read_local_float64_v16(port_const_local_void_ptr_t memory, size_t offset);
port_float64_v16_t port_memory_read_global_float64_v16(port_const_global_void_ptr_t memory, size_t offset);
port_float64_v16_t port_memory_read_constant_float64_v16(port_constant_void_ptr_t memory, size_t offset);

#else // __OPENCL_C_VERSION__

// Unsigned integer (8-bit)
#  define port_memory_read_local_uint8              port_memory_read_uint8
#  define port_memory_read_global_uint8             port_memory_read_uint8
#  define port_memory_read_constant_uint8           port_memory_read_uint8

// 2-vector of unsigned integers (8-bit)
#  define port_memory_read_local_uint8_v2           port_memory_read_uint8_v2
#  define port_memory_read_global_uint8_v2          port_memory_read_uint8_v2
#  define port_memory_read_constant_uint8_v2        port_memory_read_uint8_v2

// 3-vector of unsigned integers (8-bit)
#  define port_memory_read_local_uint8_v3           port_memory_read_uint8_v3
#  define port_memory_read_global_uint8_v3          port_memory_read_uint8_v3
#  define port_memory_read_constant_uint8_v3        port_memory_read_uint8_v3

// 4-vector of unsigned integers (8-bit)
#  define port_memory_read_local_uint8_v4           port_memory_read_uint8_v4
#  define port_memory_read_global_uint8_v4          port_memory_read_uint8_v4
#  define port_memory_read_constant_uint8_v4        port_memory_read_uint8_v4

// 8-vector of unsigned integers (8-bit)
#  define port_memory_read_local_uint8_v8           port_memory_read_uint8_v8
#  define port_memory_read_global_uint8_v8          port_memory_read_uint8_v8
#  define port_memory_read_constant_uint8_v8        port_memory_read_uint8_v8

// 16-vector of unsigned integers (8-bit)
#  define port_memory_read_local_uint8_v16          port_memory_read_uint8_v16
#  define port_memory_read_global_uint8_v16         port_memory_read_uint8_v16
#  define port_memory_read_constant_uint8_v16       port_memory_read_uint8_v16


// Unsigned integer (16-bit)
#  define port_memory_read_local_uint16             port_memory_read_uint16
#  define port_memory_read_global_uint16            port_memory_read_uint16
#  define port_memory_read_constant_uint16          port_memory_read_uint16

// 2-vector of unsigned integers (16-bit)
#  define port_memory_read_local_uint16_v2          port_memory_read_uint16_v2
#  define port_memory_read_global_uint16_v2         port_memory_read_uint16_v2
#  define port_memory_read_constant_uint16_v2       port_memory_read_uint16_v2

// 3-vector of unsigned integers (16-bit)
#  define port_memory_read_local_uint16_v3          port_memory_read_uint16_v3
#  define port_memory_read_global_uint16_v3         port_memory_read_uint16_v3
#  define port_memory_read_constant_uint16_v3       port_memory_read_uint16_v3

// 4-vector of unsigned integers (16-bit)
#  define port_memory_read_local_uint16_v4          port_memory_read_uint16_v4
#  define port_memory_read_global_uint16_v4         port_memory_read_uint16_v4
#  define port_memory_read_constant_uint16_v4       port_memory_read_uint16_v4

// 8-vector of unsigned integers (16-bit)
#  define port_memory_read_local_uint16_v8          port_memory_read_uint16_v8
#  define port_memory_read_global_uint16_v8         port_memory_read_uint16_v8
#  define port_memory_read_constant_uint16_v8       port_memory_read_uint16_v8

// 16-vector of unsigned integers (16-bit)
#  define port_memory_read_local_uint16_v16         port_memory_read_uint16_v16
#  define port_memory_read_global_uint16_v16        port_memory_read_uint16_v16
#  define port_memory_read_constant_uint16_v16      port_memory_read_uint16_v16


// Unsigned integer (32-bit)
#  define port_memory_read_local_uint32             port_memory_read_uint32
#  define port_memory_read_global_uint32            port_memory_read_uint32
#  define port_memory_read_constant_uint32          port_memory_read_uint32

// 2-vector of unsigned integers (32-bit)
#  define port_memory_read_local_uint32_v2          port_memory_read_uint32_v2
#  define port_memory_read_global_uint32_v2         port_memory_read_uint32_v2
#  define port_memory_read_constant_uint32_v2       port_memory_read_uint32_v2

// 3-vector of unsigned integers (32-bit)
#  define port_memory_read_local_uint32_v3          port_memory_read_uint32_v3
#  define port_memory_read_global_uint32_v3         port_memory_read_uint32_v3
#  define port_memory_read_constant_uint32_v3       port_memory_read_uint32_v3

// 4-vector of unsigned integers (32-bit)
#  define port_memory_read_local_uint32_v4          port_memory_read_uint32_v4
#  define port_memory_read_global_uint32_v4         port_memory_read_uint32_v4
#  define port_memory_read_constant_uint32_v4       port_memory_read_uint32_v4

// 8-vector of unsigned integers (32-bit)
#  define port_memory_read_local_uint32_v8          port_memory_read_uint32_v8
#  define port_memory_read_global_uint32_v8         port_memory_read_uint32_v8
#  define port_memory_read_constant_uint32_v8       port_memory_read_uint32_v8

// 16-vector of unsigned integers (32-bit)
#  define port_memory_read_local_uint32_v16         port_memory_read_uint32_v16
#  define port_memory_read_global_uint32_v16        port_memory_read_uint32_v16
#  define port_memory_read_constant_uint32_v16      port_memory_read_uint32_v16


// Unsigned integer (64-bit)
#  define port_memory_read_local_uint64             port_memory_read_uint64
#  define port_memory_read_global_uint64            port_memory_read_uint64
#  define port_memory_read_constant_uint64          port_memory_read_uint64

// 2-vector of unsigned integers (64-bit)
#  define port_memory_read_local_uint64_v2          port_memory_read_uint64_v2
#  define port_memory_read_global_uint64_v2         port_memory_read_uint64_v2
#  define port_memory_read_constant_uint64_v2       port_memory_read_uint64_v2

// 3-vector of unsigned integers (64-bit)
#  define port_memory_read_local_uint64_v3          port_memory_read_uint64_v3
#  define port_memory_read_global_uint64_v3         port_memory_read_uint64_v3
#  define port_memory_read_constant_uint64_v3       port_memory_read_uint64_v3

// 4-vector of unsigned integers (64-bit)
#  define port_memory_read_local_uint64_v4          port_memory_read_uint64_v4
#  define port_memory_read_global_uint64_v4         port_memory_read_uint64_v4
#  define port_memory_read_constant_uint64_v4       port_memory_read_uint64_v4

// 8-vector of unsigned integers (64-bit)
#  define port_memory_read_local_uint64_v8          port_memory_read_uint64_v8
#  define port_memory_read_global_uint64_v8         port_memory_read_uint64_v8
#  define port_memory_read_constant_uint64_v8       port_memory_read_uint64_v8

// 16-vector of unsigned integers (64-bit)
#  define port_memory_read_local_uint64_v16         port_memory_read_uint64_v16
#  define port_memory_read_global_uint64_v16        port_memory_read_uint64_v16
#  define port_memory_read_constant_uint64_v16      port_memory_read_uint64_v16


// Signed integer (8-bit)
#  define port_memory_read_local_sint8              port_memory_read_sint8
#  define port_memory_read_global_sint8             port_memory_read_sint8
#  define port_memory_read_constant_sint8           port_memory_read_sint8

// 2-vector of signed integers (8-bit)
#  define port_memory_read_local_sint8_v2           port_memory_read_sint8_v2
#  define port_memory_read_global_sint8_v2          port_memory_read_sint8_v2
#  define port_memory_read_constant_sint8_v2        port_memory_read_sint8_v2

// 3-vector of signed integers (8-bit)
#  define port_memory_read_local_sint8_v3           port_memory_read_sint8_v3
#  define port_memory_read_global_sint8_v3          port_memory_read_sint8_v3
#  define port_memory_read_constant_sint8_v3        port_memory_read_sint8_v3

// 4-vector of signed integers (8-bit)
#  define port_memory_read_local_sint8_v4           port_memory_read_sint8_v4
#  define port_memory_read_global_sint8_v4          port_memory_read_sint8_v4
#  define port_memory_read_constant_sint8_v4        port_memory_read_sint8_v4

// 8-vector of signed integers (8-bit)
#  define port_memory_read_local_sint8_v8           port_memory_read_sint8_v8
#  define port_memory_read_global_sint8_v8          port_memory_read_sint8_v8
#  define port_memory_read_constant_sint8_v8        port_memory_read_sint8_v8

// 16-vector of signed integers (8-bit)
#  define port_memory_read_local_sint8_v16          port_memory_read_sint8_v16
#  define port_memory_read_global_sint8_v16         port_memory_read_sint8_v16
#  define port_memory_read_constant_sint8_v16       port_memory_read_sint8_v16


// Signed integer (16-bit)
#  define port_memory_read_local_sint16             port_memory_read_sint16
#  define port_memory_read_global_sint16            port_memory_read_sint16
#  define port_memory_read_constant_sint16          port_memory_read_sint16

// 2-vector of signed integers (16-bit)
#  define port_memory_read_local_sint16_v2          port_memory_read_sint16_v2
#  define port_memory_read_global_sint16_v2         port_memory_read_sint16_v2
#  define port_memory_read_constant_sint16_v2       port_memory_read_sint16_v2

// 3-vector of signed integers (16-bit)
#  define port_memory_read_local_sint16_v3          port_memory_read_sint16_v3
#  define port_memory_read_global_sint16_v3         port_memory_read_sint16_v3
#  define port_memory_read_constant_sint16_v3       port_memory_read_sint16_v3

// 4-vector of signed integers (16-bit)
#  define port_memory_read_local_sint16_v4          port_memory_read_sint16_v4
#  define port_memory_read_global_sint16_v4         port_memory_read_sint16_v4
#  define port_memory_read_constant_sint16_v4       port_memory_read_sint16_v4

// 8-vector of signed integers (16-bit)
#  define port_memory_read_local_sint16_v8          port_memory_read_sint16_v8
#  define port_memory_read_global_sint16_v8         port_memory_read_sint16_v8
#  define port_memory_read_constant_sint16_v8       port_memory_read_sint16_v8

// 16-vector of signed integers (16-bit)
#  define port_memory_read_local_sint16_v16         port_memory_read_sint16_v16
#  define port_memory_read_global_sint16_v16        port_memory_read_sint16_v16
#  define port_memory_read_constant_sint16_v16      port_memory_read_sint16_v16


// Signed integer (32-bit)
#  define port_memory_read_local_sint32             port_memory_read_sint32
#  define port_memory_read_global_sint32            port_memory_read_sint32
#  define port_memory_read_constant_sint32          port_memory_read_sint32

// 2-vector of signed integers (32-bit)
#  define port_memory_read_local_sint32_v2          port_memory_read_sint32_v2
#  define port_memory_read_global_sint32_v2         port_memory_read_sint32_v2
#  define port_memory_read_constant_sint32_v2       port_memory_read_sint32_v2

// 3-vector of signed integers (32-bit)
#  define port_memory_read_local_sint32_v3          port_memory_read_sint32_v3
#  define port_memory_read_global_sint32_v3         port_memory_read_sint32_v3
#  define port_memory_read_constant_sint32_v3       port_memory_read_sint32_v3

// 4-vector of signed integers (32-bit)
#  define port_memory_read_local_sint32_v4          port_memory_read_sint32_v4
#  define port_memory_read_global_sint32_v4         port_memory_read_sint32_v4
#  define port_memory_read_constant_sint32_v4       port_memory_read_sint32_v4

// 8-vector of signed integers (32-bit)
#  define port_memory_read_local_sint32_v8          port_memory_read_sint32_v8
#  define port_memory_read_global_sint32_v8         port_memory_read_sint32_v8
#  define port_memory_read_constant_sint32_v8       port_memory_read_sint32_v8

// 16-vector of signed integers (32-bit)
#  define port_memory_read_local_sint32_v16         port_memory_read_sint32_v16
#  define port_memory_read_global_sint32_v16        port_memory_read_sint32_v16
#  define port_memory_read_constant_sint32_v16      port_memory_read_sint32_v16


// Signed integer (64-bit)
#  define port_memory_read_local_sint64             port_memory_read_sint64
#  define port_memory_read_global_sint64            port_memory_read_sint64
#  define port_memory_read_constant_sint64          port_memory_read_sint64

// 2-vector of signed integers (64-bit)
#  define port_memory_read_local_sint64_v2          port_memory_read_sint64_v2
#  define port_memory_read_global_sint64_v2         port_memory_read_sint64_v2
#  define port_memory_read_constant_sint64_v2       port_memory_read_sint64_v2

// 3-vector of signed integers (64-bit)
#  define port_memory_read_local_sint64_v3          port_memory_read_sint64_v3
#  define port_memory_read_global_sint64_v3         port_memory_read_sint64_v3
#  define port_memory_read_constant_sint64_v3       port_memory_read_sint64_v3

// 4-vector of signed integers (64-bit)
#  define port_memory_read_local_sint64_v4          port_memory_read_sint64_v4
#  define port_memory_read_global_sint64_v4         port_memory_read_sint64_v4
#  define port_memory_read_constant_sint64_v4       port_memory_read_sint64_v4

// 8-vector of signed integers (64-bit)
#  define port_memory_read_local_sint64_v8          port_memory_read_sint64_v8
#  define port_memory_read_global_sint64_v8         port_memory_read_sint64_v8
#  define port_memory_read_constant_sint64_v8       port_memory_read_sint64_v8

// 16-vector of signed integers (64-bit)
#  define port_memory_read_local_sint64_v16         port_memory_read_sint64_v16
#  define port_memory_read_global_sint64_v16        port_memory_read_sint64_v16
#  define port_memory_read_constant_sint64_v16      port_memory_read_sint64_v16


// Floating-point number (16-bit)
#  define port_memory_read_local_float16            port_memory_read_float16
#  define port_memory_read_global_float16           port_memory_read_float16
#  define port_memory_read_constant_float16         port_memory_read_float16

// 2-vector of floating-point numbers (16-bit)
#  define port_memory_read_local_float16_v2         port_memory_read_float16_v2
#  define port_memory_read_global_float16_v2        port_memory_read_float16_v2
#  define port_memory_read_constant_float16_v2      port_memory_read_float16_v2

// 3-vector of floating-point numbers (16-bit)
#  define port_memory_read_local_float16_v3         port_memory_read_float16_v3
#  define port_memory_read_global_float16_v3        port_memory_read_float16_v3
#  define port_memory_read_constant_float16_v3      port_memory_read_float16_v3

// 4-vector of floating-point numbers (16-bit)
#  define port_memory_read_local_float16_v4         port_memory_read_float16_v4
#  define port_memory_read_global_float16_v4        port_memory_read_float16_v4
#  define port_memory_read_constant_float16_v4      port_memory_read_float16_v4

// 8-vector of floating-point numbers (16-bit)
#  define port_memory_read_local_float16_v8         port_memory_read_float16_v8
#  define port_memory_read_global_float16_v8        port_memory_read_float16_v8
#  define port_memory_read_constant_float16_v8      port_memory_read_float16_v8

// 16-vector of floating-point numbers (16-bit)
#  define port_memory_read_local_float16_v16        port_memory_read_float16_v16
#  define port_memory_read_global_float16_v16       port_memory_read_float16_v16
#  define port_memory_read_constant_float16_v16     port_memory_read_float16_v16


// Floating-point number (32-bit)
#  define port_memory_read_local_float32            port_memory_read_float32
#  define port_memory_read_global_float32           port_memory_read_float32
#  define port_memory_read_constant_float32         port_memory_read_float32

// 2-vector of floating-point numbers (32-bit)
#  define port_memory_read_local_float32_v2         port_memory_read_float32_v2
#  define port_memory_read_global_float32_v2        port_memory_read_float32_v2
#  define port_memory_read_constant_float32_v2      port_memory_read_float32_v2

// 3-vector of floating-point numbers (32-bit)
#  define port_memory_read_local_float32_v3         port_memory_read_float32_v3
#  define port_memory_read_global_float32_v3        port_memory_read_float32_v3
#  define port_memory_read_constant_float32_v3      port_memory_read_float32_v3

// 4-vector of floating-point numbers (32-bit)
#  define port_memory_read_local_float32_v4         port_memory_read_float32_v4
#  define port_memory_read_global_float32_v4        port_memory_read_float32_v4
#  define port_memory_read_constant_float32_v4      port_memory_read_float32_v4

// 8-vector of floating-point numbers (32-bit)
#  define port_memory_read_local_float32_v8         port_memory_read_float32_v8
#  define port_memory_read_global_float32_v8        port_memory_read_float32_v8
#  define port_memory_read_constant_float32_v8      port_memory_read_float32_v8

// 16-vector of floating-point numbers (32-bit)
#  define port_memory_read_local_float32_v16        port_memory_read_float32_v16
#  define port_memory_read_global_float32_v16       port_memory_read_float32_v16
#  define port_memory_read_constant_float32_v16     port_memory_read_float32_v16


// Floating-point number (64-bit)
#  define port_memory_read_local_float64            port_memory_read_float64
#  define port_memory_read_global_float64           port_memory_read_float64
#  define port_memory_read_constant_float64         port_memory_read_float64

// 2-vector of floating-point numbers (64-bit)
#  define port_memory_read_local_float64_v2         port_memory_read_float64_v2
#  define port_memory_read_global_float64_v2        port_memory_read_float64_v2
#  define port_memory_read_constant_float64_v2      port_memory_read_float64_v2

// 3-vector of floating-point numbers (64-bit)
#  define port_memory_read_local_float64_v3         port_memory_read_float64_v3
#  define port_memory_read_global_float64_v3        port_memory_read_float64_v3
#  define port_memory_read_constant_float64_v3      port_memory_read_float64_v3

// 4-vector of floating-point numbers (64-bit)
#  define port_memory_read_local_float64_v4         port_memory_read_float64_v4
#  define port_memory_read_global_float64_v4        port_memory_read_float64_v4
#  define port_memory_read_constant_float64_v4      port_memory_read_float64_v4

// 8-vector of floating-point numbers (64-bit)
#  define port_memory_read_local_float64_v8         port_memory_read_float64_v8
#  define port_memory_read_global_float64_v8        port_memory_read_float64_v8
#  define port_memory_read_constant_float64_v8      port_memory_read_float64_v8

// 16-vector of floating-point numbers (64-bit)
#  define port_memory_read_local_float64_v16        port_memory_read_float64_v16
#  define port_memory_read_global_float64_v16       port_memory_read_float64_v16
#  define port_memory_read_constant_float64_v16     port_memory_read_float64_v16

#endif // __OPENCL_C_VERSION__

///////////////////////////////////////////////////////////////////////////////
// Aliases for typedefs of built-in types
///////////////////////////////////////////////////////////////////////////////

// Unsigned integer (quarter size)
#define port_memory_read_uintq port_memory_read_uint8
#define port_memory_read_local_uintq port_memory_read_local_uint8
#define port_memory_read_global_uintq port_memory_read_global_uint8
#define port_memory_read_constant_uintq port_memory_read_constant_uint8

// 2-vector of unsigned integers (quarter size)
#define port_memory_read_uintq_v2 port_memory_read_uint8_v2
#define port_memory_read_local_uintq_v2 port_memory_read_local_uint8_v2
#define port_memory_read_global_uintq_v2 port_memory_read_global_uint8_v2
#define port_memory_read_constant_uintq_v2 port_memory_read_constant_uint8_v2

// 3-vector of unsigned integers (quarter size)
#define port_memory_read_uintq_v3 port_memory_read_uint8_v3
#define port_memory_read_local_uintq_v3 port_memory_read_local_uint8_v3
#define port_memory_read_global_uintq_v3 port_memory_read_global_uint8_v3
#define port_memory_read_constant_uintq_v3 port_memory_read_constant_uint8_v3

// 4-vector of unsigned integers (quarter size)
#define port_memory_read_uintq_v4 port_memory_read_uint8_v4
#define port_memory_read_local_uintq_v4 port_memory_read_local_uint8_v4
#define port_memory_read_global_uintq_v4 port_memory_read_global_uint8_v4
#define port_memory_read_constant_uintq_v4 port_memory_read_constant_uint8_v4

// 8-vector of unsigned integers (quarter size)
#define port_memory_read_uintq_v8 port_memory_read_uint8_v8
#define port_memory_read_local_uintq_v8 port_memory_read_local_uint8_v8
#define port_memory_read_global_uintq_v8 port_memory_read_global_uint8_v8
#define port_memory_read_constant_uintq_v8 port_memory_read_constant_uint8_v8

// 16-vector of unsigned integers (quarter size)
#define port_memory_read_uintq_v16 port_memory_read_uint8_v16
#define port_memory_read_local_uintq_v16 port_memory_read_local_uint8_v16
#define port_memory_read_global_uintq_v16 port_memory_read_global_uint8_v16
#define port_memory_read_constant_uintq_v16 port_memory_read_constant_uint8_v16


// Unsigned integer (half size)
#define port_memory_read_uinth port_memory_read_uint16
#define port_memory_read_local_uinth port_memory_read_local_uint16
#define port_memory_read_global_uinth port_memory_read_global_uint16
#define port_memory_read_constant_uinth port_memory_read_constant_uint16

// 2-vector of unsigned integers (half size)
#define port_memory_read_uinth_v2 port_memory_read_uint16_v2
#define port_memory_read_local_uinth_v2 port_memory_read_local_uint16_v2
#define port_memory_read_global_uinth_v2 port_memory_read_global_uint16_v2
#define port_memory_read_constant_uinth_v2 port_memory_read_constant_uint16_v2

// 3-vector of unsigned integers (half size)
#define port_memory_read_uinth_v3 port_memory_read_uint16_v3
#define port_memory_read_local_uinth_v3 port_memory_read_local_uint16_v3
#define port_memory_read_global_uinth_v3 port_memory_read_global_uint16_v3
#define port_memory_read_constant_uinth_v3 port_memory_read_constant_uint16_v3

// 4-vector of unsigned integers (half size)
#define port_memory_read_uinth_v4 port_memory_read_uint16_v4
#define port_memory_read_local_uinth_v4 port_memory_read_local_uint16_v4
#define port_memory_read_global_uinth_v4 port_memory_read_global_uint16_v4
#define port_memory_read_constant_uinth_v4 port_memory_read_constant_uint16_v4

// 8-vector of unsigned integers (half size)
#define port_memory_read_uinth_v8 port_memory_read_uint16_v8
#define port_memory_read_local_uinth_v8 port_memory_read_local_uint16_v8
#define port_memory_read_global_uinth_v8 port_memory_read_global_uint16_v8
#define port_memory_read_constant_uinth_v8 port_memory_read_constant_uint16_v8

// 16-vector of unsigned integers (half size)
#define port_memory_read_uinth_v16 port_memory_read_uint16_v16
#define port_memory_read_local_uinth_v16 port_memory_read_local_uint16_v16
#define port_memory_read_global_uinth_v16 port_memory_read_global_uint16_v16
#define port_memory_read_constant_uinth_v16 port_memory_read_constant_uint16_v16


// Unsigned integer (single size)
#define port_memory_read_uints port_memory_read_uint32
#define port_memory_read_local_uints port_memory_read_local_uint32
#define port_memory_read_global_uints port_memory_read_global_uint32
#define port_memory_read_constant_uints port_memory_read_constant_uint32

// 2-vector of unsigned integers (single size)
#define port_memory_read_uints_v2 port_memory_read_uint32_v2
#define port_memory_read_local_uints_v2 port_memory_read_local_uint32_v2
#define port_memory_read_global_uints_v2 port_memory_read_global_uint32_v2
#define port_memory_read_constant_uints_v2 port_memory_read_constant_uint32_v2

// 3-vector of unsigned integers (single size)
#define port_memory_read_uints_v3 port_memory_read_uint32_v3
#define port_memory_read_local_uints_v3 port_memory_read_local_uint32_v3
#define port_memory_read_global_uints_v3 port_memory_read_global_uint32_v3
#define port_memory_read_constant_uints_v3 port_memory_read_constant_uint32_v3

// 4-vector of unsigned integers (single size)
#define port_memory_read_uints_v4 port_memory_read_uint32_v4
#define port_memory_read_local_uints_v4 port_memory_read_local_uint32_v4
#define port_memory_read_global_uints_v4 port_memory_read_global_uint32_v4
#define port_memory_read_constant_uints_v4 port_memory_read_constant_uint32_v4

// 8-vector of unsigned integers (single size)
#define port_memory_read_uints_v8 port_memory_read_uint32_v8
#define port_memory_read_local_uints_v8 port_memory_read_local_uint32_v8
#define port_memory_read_global_uints_v8 port_memory_read_global_uint32_v8
#define port_memory_read_constant_uints_v8 port_memory_read_constant_uint32_v8

// 16-vector of unsigned integers (single size)
#define port_memory_read_uints_v16 port_memory_read_uint32_v16
#define port_memory_read_local_uints_v16 port_memory_read_local_uint32_v16
#define port_memory_read_global_uints_v16 port_memory_read_global_uint32_v16
#define port_memory_read_constant_uints_v16 port_memory_read_constant_uint32_v16


// Unsigned integer (double size)
#define port_memory_read_uintd port_memory_read_uint64
#define port_memory_read_local_uintd port_memory_read_local_uint64
#define port_memory_read_global_uintd port_memory_read_global_uint64
#define port_memory_read_constant_uintd port_memory_read_constant_uint64

// 2-vector of unsigned integers (double size)
#define port_memory_read_uintd_v2 port_memory_read_uint64_v2
#define port_memory_read_local_uintd_v2 port_memory_read_local_uint64_v2
#define port_memory_read_global_uintd_v2 port_memory_read_global_uint64_v2
#define port_memory_read_constant_uintd_v2 port_memory_read_constant_uint64_v2

// 3-vector of unsigned integers (double size)
#define port_memory_read_uintd_v3 port_memory_read_uint64_v3
#define port_memory_read_local_uintd_v3 port_memory_read_local_uint64_v3
#define port_memory_read_global_uintd_v3 port_memory_read_global_uint64_v3
#define port_memory_read_constant_uintd_v3 port_memory_read_constant_uint64_v3

// 4-vector of unsigned integers (double size)
#define port_memory_read_uintd_v4 port_memory_read_uint64_v4
#define port_memory_read_local_uintd_v4 port_memory_read_local_uint64_v4
#define port_memory_read_global_uintd_v4 port_memory_read_global_uint64_v4
#define port_memory_read_constant_uintd_v4 port_memory_read_constant_uint64_v4

// 8-vector of unsigned integers (double size)
#define port_memory_read_uintd_v8 port_memory_read_uint64_v8
#define port_memory_read_local_uintd_v8 port_memory_read_local_uint64_v8
#define port_memory_read_global_uintd_v8 port_memory_read_global_uint64_v8
#define port_memory_read_constant_uintd_v8 port_memory_read_constant_uint64_v8

// 16-vector of unsigned integers (double size)
#define port_memory_read_uintd_v16 port_memory_read_uint64_v16
#define port_memory_read_local_uintd_v16 port_memory_read_local_uint64_v16
#define port_memory_read_global_uintd_v16 port_memory_read_global_uint64_v16
#define port_memory_read_constant_uintd_v16 port_memory_read_constant_uint64_v16


// Signed integer (quarter size)
#define port_memory_read_sintq port_memory_read_sint8
#define port_memory_read_local_sintq port_memory_read_local_sint8
#define port_memory_read_global_sintq port_memory_read_global_sint8
#define port_memory_read_constant_sintq port_memory_read_constant_sint8

// 2-vector of signed integers (quarter size)
#define port_memory_read_sintq_v2 port_memory_read_sint8_v2
#define port_memory_read_local_sintq_v2 port_memory_read_local_sint8_v2
#define port_memory_read_global_sintq_v2 port_memory_read_global_sint8_v2
#define port_memory_read_constant_sintq_v2 port_memory_read_constant_sint8_v2

// 3-vector of signed integers (quarter size)
#define port_memory_read_sintq_v3 port_memory_read_sint8_v3
#define port_memory_read_local_sintq_v3 port_memory_read_local_sint8_v3
#define port_memory_read_global_sintq_v3 port_memory_read_global_sint8_v3
#define port_memory_read_constant_sintq_v3 port_memory_read_constant_sint8_v3

// 4-vector of signed integers (quarter size)
#define port_memory_read_sintq_v4 port_memory_read_sint8_v4
#define port_memory_read_local_sintq_v4 port_memory_read_local_sint8_v4
#define port_memory_read_global_sintq_v4 port_memory_read_global_sint8_v4
#define port_memory_read_constant_sintq_v4 port_memory_read_constant_sint8_v4

// 8-vector of signed integers (quarter size)
#define port_memory_read_sintq_v8 port_memory_read_sint8_v8
#define port_memory_read_local_sintq_v8 port_memory_read_local_sint8_v8
#define port_memory_read_global_sintq_v8 port_memory_read_global_sint8_v8
#define port_memory_read_constant_sintq_v8 port_memory_read_constant_sint8_v8

// 16-vector of signed integers (quarter size)
#define port_memory_read_sintq_v16 port_memory_read_sint8_v16
#define port_memory_read_local_sintq_v16 port_memory_read_local_sint8_v16
#define port_memory_read_global_sintq_v16 port_memory_read_global_sint8_v16
#define port_memory_read_constant_sintq_v16 port_memory_read_constant_sint8_v16


// Signed integer (half size)
#define port_memory_read_sinth port_memory_read_sint16
#define port_memory_read_local_sinth port_memory_read_local_sint16
#define port_memory_read_global_sinth port_memory_read_global_sint16
#define port_memory_read_constant_sinth port_memory_read_constant_sint16

// 2-vector of signed integers (half size)
#define port_memory_read_sinth_v2 port_memory_read_sint16_v2
#define port_memory_read_local_sinth_v2 port_memory_read_local_sint16_v2
#define port_memory_read_global_sinth_v2 port_memory_read_global_sint16_v2
#define port_memory_read_constant_sinth_v2 port_memory_read_constant_sint16_v2

// 3-vector of signed integers (half size)
#define port_memory_read_sinth_v3 port_memory_read_sint16_v3
#define port_memory_read_local_sinth_v3 port_memory_read_local_sint16_v3
#define port_memory_read_global_sinth_v3 port_memory_read_global_sint16_v3
#define port_memory_read_constant_sinth_v3 port_memory_read_constant_sint16_v3

// 4-vector of signed integers (half size)
#define port_memory_read_sinth_v4 port_memory_read_sint16_v4
#define port_memory_read_local_sinth_v4 port_memory_read_local_sint16_v4
#define port_memory_read_global_sinth_v4 port_memory_read_global_sint16_v4
#define port_memory_read_constant_sinth_v4 port_memory_read_constant_sint16_v4

// 8-vector of signed integers (half size)
#define port_memory_read_sinth_v8 port_memory_read_sint16_v8
#define port_memory_read_local_sinth_v8 port_memory_read_local_sint16_v8
#define port_memory_read_global_sinth_v8 port_memory_read_global_sint16_v8
#define port_memory_read_constant_sinth_v8 port_memory_read_constant_sint16_v8

// 16-vector of signed integers (half size)
#define port_memory_read_sinth_v16 port_memory_read_sint16_v16
#define port_memory_read_local_sinth_v16 port_memory_read_local_sint16_v16
#define port_memory_read_global_sinth_v16 port_memory_read_global_sint16_v16
#define port_memory_read_constant_sinth_v16 port_memory_read_constant_sint16_v16


// Signed integer (single size)
#define port_memory_read_sints port_memory_read_sint32
#define port_memory_read_local_sints port_memory_read_local_sint32
#define port_memory_read_global_sints port_memory_read_global_sint32
#define port_memory_read_constant_sints port_memory_read_constant_sint32

// 2-vector of signed integers (single size)
#define port_memory_read_sints_v2 port_memory_read_sint32_v2
#define port_memory_read_local_sints_v2 port_memory_read_local_sint32_v2
#define port_memory_read_global_sints_v2 port_memory_read_global_sint32_v2
#define port_memory_read_constant_sints_v2 port_memory_read_constant_sint32_v2

// 3-vector of signed integers (single size)
#define port_memory_read_sints_v3 port_memory_read_sint32_v3
#define port_memory_read_local_sints_v3 port_memory_read_local_sint32_v3
#define port_memory_read_global_sints_v3 port_memory_read_global_sint32_v3
#define port_memory_read_constant_sints_v3 port_memory_read_constant_sint32_v3

// 4-vector of signed integers (single size)
#define port_memory_read_sints_v4 port_memory_read_sint32_v4
#define port_memory_read_local_sints_v4 port_memory_read_local_sint32_v4
#define port_memory_read_global_sints_v4 port_memory_read_global_sint32_v4
#define port_memory_read_constant_sints_v4 port_memory_read_constant_sint32_v4

// 8-vector of signed integers (single size)
#define port_memory_read_sints_v8 port_memory_read_sint32_v8
#define port_memory_read_local_sints_v8 port_memory_read_local_sint32_v8
#define port_memory_read_global_sints_v8 port_memory_read_global_sint32_v8
#define port_memory_read_constant_sints_v8 port_memory_read_constant_sint32_v8

// 16-vector of signed integers (single size)
#define port_memory_read_sints_v16 port_memory_read_sint32_v16
#define port_memory_read_local_sints_v16 port_memory_read_local_sint32_v16
#define port_memory_read_global_sints_v16 port_memory_read_global_sint32_v16
#define port_memory_read_constant_sints_v16 port_memory_read_constant_sint32_v16


// Signed integer (double size)
#define port_memory_read_sintd port_memory_read_sint64
#define port_memory_read_local_sintd port_memory_read_local_sint64
#define port_memory_read_global_sintd port_memory_read_global_sint64
#define port_memory_read_constant_sintd port_memory_read_constant_sint64

// 2-vector of signed integers (double size)
#define port_memory_read_sintd_v2 port_memory_read_sint64_v2
#define port_memory_read_local_sintd_v2 port_memory_read_local_sint64_v2
#define port_memory_read_global_sintd_v2 port_memory_read_global_sint64_v2
#define port_memory_read_constant_sintd_v2 port_memory_read_constant_sint64_v2

// 3-vector of signed integers (double size)
#define port_memory_read_sintd_v3 port_memory_read_sint64_v3
#define port_memory_read_local_sintd_v3 port_memory_read_local_sint64_v3
#define port_memory_read_global_sintd_v3 port_memory_read_global_sint64_v3
#define port_memory_read_constant_sintd_v3 port_memory_read_constant_sint64_v3

// 4-vector of signed integers (double size)
#define port_memory_read_sintd_v4 port_memory_read_sint64_v4
#define port_memory_read_local_sintd_v4 port_memory_read_local_sint64_v4
#define port_memory_read_global_sintd_v4 port_memory_read_global_sint64_v4
#define port_memory_read_constant_sintd_v4 port_memory_read_constant_sint64_v4

// 8-vector of signed integers (double size)
#define port_memory_read_sintd_v8 port_memory_read_sint64_v8
#define port_memory_read_local_sintd_v8 port_memory_read_local_sint64_v8
#define port_memory_read_global_sintd_v8 port_memory_read_global_sint64_v8
#define port_memory_read_constant_sintd_v8 port_memory_read_constant_sint64_v8

// 16-vector of signed integers (double size)
#define port_memory_read_sintd_v16 port_memory_read_sint64_v16
#define port_memory_read_local_sintd_v16 port_memory_read_local_sint64_v16
#define port_memory_read_global_sintd_v16 port_memory_read_global_sint64_v16
#define port_memory_read_constant_sintd_v16 port_memory_read_constant_sint64_v16


// Floating-point number (half size)
#define port_memory_read_floath port_memory_read_float16
#define port_memory_read_local_floath port_memory_read_local_float16
#define port_memory_read_global_floath port_memory_read_global_float16
#define port_memory_read_constant_floath port_memory_read_constant_float16

// 2-vector of floating-point numbers (half size)
#define port_memory_read_floath_v2 port_memory_read_float16_v2
#define port_memory_read_local_floath_v2 port_memory_read_local_float16_v2
#define port_memory_read_global_floath_v2 port_memory_read_global_float16_v2
#define port_memory_read_constant_floath_v2 port_memory_read_constant_float16_v2

// 3-vector of floating-point numbers (half size)
#define port_memory_read_floath_v3 port_memory_read_float16_v3
#define port_memory_read_local_floath_v3 port_memory_read_local_float16_v3
#define port_memory_read_global_floath_v3 port_memory_read_global_float16_v3
#define port_memory_read_constant_floath_v3 port_memory_read_constant_float16_v3

// 4-vector of floating-point numbers (half size)
#define port_memory_read_floath_v4 port_memory_read_float16_v4
#define port_memory_read_local_floath_v4 port_memory_read_local_float16_v4
#define port_memory_read_global_floath_v4 port_memory_read_global_float16_v4
#define port_memory_read_constant_floath_v4 port_memory_read_constant_float16_v4

// 8-vector of floating-point numbers (half size)
#define port_memory_read_floath_v8 port_memory_read_float16_v8
#define port_memory_read_local_floath_v8 port_memory_read_local_float16_v8
#define port_memory_read_global_floath_v8 port_memory_read_global_float16_v8
#define port_memory_read_constant_floath_v8 port_memory_read_constant_float16_v8

// 16-vector of floating-point numbers (half size)
#define port_memory_read_floath_v16 port_memory_read_float16_v16
#define port_memory_read_local_floath_v16 port_memory_read_local_float16_v16
#define port_memory_read_global_floath_v16 port_memory_read_global_float16_v16
#define port_memory_read_constant_floath_v16 port_memory_read_constant_float16_v16


// Floating-point number (single size)
#define port_memory_read_floats port_memory_read_float32
#define port_memory_read_local_floats port_memory_read_local_float32
#define port_memory_read_global_floats port_memory_read_global_float32
#define port_memory_read_constant_floats port_memory_read_constant_float32

// 2-vector of floating-point numbers (single size)
#define port_memory_read_floats_v2 port_memory_read_float32_v2
#define port_memory_read_local_floats_v2 port_memory_read_local_float32_v2
#define port_memory_read_global_floats_v2 port_memory_read_global_float32_v2
#define port_memory_read_constant_floats_v2 port_memory_read_constant_float32_v2

// 3-vector of floating-point numbers (single size)
#define port_memory_read_floats_v3 port_memory_read_float32_v3
#define port_memory_read_local_floats_v3 port_memory_read_local_float32_v3
#define port_memory_read_global_floats_v3 port_memory_read_global_float32_v3
#define port_memory_read_constant_floats_v3 port_memory_read_constant_float32_v3

// 4-vector of floating-point numbers (single size)
#define port_memory_read_floats_v4 port_memory_read_float32_v4
#define port_memory_read_local_floats_v4 port_memory_read_local_float32_v4
#define port_memory_read_global_floats_v4 port_memory_read_global_float32_v4
#define port_memory_read_constant_floats_v4 port_memory_read_constant_float32_v4

// 8-vector of floating-point numbers (single size)
#define port_memory_read_floats_v8 port_memory_read_float32_v8
#define port_memory_read_local_floats_v8 port_memory_read_local_float32_v8
#define port_memory_read_global_floats_v8 port_memory_read_global_float32_v8
#define port_memory_read_constant_floats_v8 port_memory_read_constant_float32_v8

// 16-vector of floating-point numbers (single size)
#define port_memory_read_floats_v16 port_memory_read_float32_v16
#define port_memory_read_local_floats_v16 port_memory_read_local_float32_v16
#define port_memory_read_global_floats_v16 port_memory_read_global_float32_v16
#define port_memory_read_constant_floats_v16 port_memory_read_constant_float32_v16


// Floating-point number (double size)
#define port_memory_read_floatd port_memory_read_float64
#define port_memory_read_local_floatd port_memory_read_local_float64
#define port_memory_read_global_floatd port_memory_read_global_float64
#define port_memory_read_constant_floatd port_memory_read_constant_float64

// 2-vector of floating-point numbers (double size)
#define port_memory_read_floatd_v2 port_memory_read_float64_v2
#define port_memory_read_local_floatd_v2 port_memory_read_local_float64_v2
#define port_memory_read_global_floatd_v2 port_memory_read_global_float64_v2
#define port_memory_read_constant_floatd_v2 port_memory_read_constant_float64_v2

// 3-vector of floating-point numbers (double size)
#define port_memory_read_floatd_v3 port_memory_read_float64_v3
#define port_memory_read_local_floatd_v3 port_memory_read_local_float64_v3
#define port_memory_read_global_floatd_v3 port_memory_read_global_float64_v3
#define port_memory_read_constant_floatd_v3 port_memory_read_constant_float64_v3

// 4-vector of floating-point numbers (double size)
#define port_memory_read_floatd_v4 port_memory_read_float64_v4
#define port_memory_read_local_floatd_v4 port_memory_read_local_float64_v4
#define port_memory_read_global_floatd_v4 port_memory_read_global_float64_v4
#define port_memory_read_constant_floatd_v4 port_memory_read_constant_float64_v4

// 8-vector of floating-point numbers (double size)
#define port_memory_read_floatd_v8 port_memory_read_float64_v8
#define port_memory_read_local_floatd_v8 port_memory_read_local_float64_v8
#define port_memory_read_global_floatd_v8 port_memory_read_global_float64_v8
#define port_memory_read_constant_floatd_v8 port_memory_read_constant_float64_v8

// 16-vector of floating-point numbers (double size)
#define port_memory_read_floatd_v16 port_memory_read_float64_v16
#define port_memory_read_local_floatd_v16 port_memory_read_local_float64_v16
#define port_memory_read_global_floatd_v16 port_memory_read_global_float64_v16
#define port_memory_read_constant_floatd_v16 port_memory_read_constant_float64_v16

///////////////////////////////////////////////////////////////////////////////
// Aliases for other types
///////////////////////////////////////////////////////////////////////////////

// Memory references
#define port_memory_read_memory_ref port_memory_read_sints
#define port_memory_read_local_memory_ref port_memory_read_local_sints
#define port_memory_read_global_memory_ref port_memory_read_global_sints
#define port_memory_read_constant_memory_ref port_memory_read_constant_sints

#define port_memory_read_memory_refh port_memory_read_sinth
#define port_memory_read_local_memory_refh port_memory_read_local_sinth
#define port_memory_read_global_memory_refh port_memory_read_global_sinth
#define port_memory_read_constant_memory_refh port_memory_read_constant_sinth

#define port_memory_read_memory_refq port_memory_read_sintq
#define port_memory_read_local_memory_refq port_memory_read_local_sintq
#define port_memory_read_global_memory_refq port_memory_read_global_sintq
#define port_memory_read_constant_memory_refq port_memory_read_constant_sintq

#endif // _PORT_MEMORY_READ_FUN_H_

