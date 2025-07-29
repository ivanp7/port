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
#define port_memory_read_uint_quarter port_memory_read_uint8
#define port_memory_read_local_uint_quarter port_memory_read_local_uint8
#define port_memory_read_global_uint_quarter port_memory_read_global_uint8
#define port_memory_read_constant_uint_quarter port_memory_read_constant_uint8

// 2-vector of unsigned integers (quarter size)
#define port_memory_read_uint_quarter_v2 port_memory_read_uint8_v2
#define port_memory_read_local_uint_quarter_v2 port_memory_read_local_uint8_v2
#define port_memory_read_global_uint_quarter_v2 port_memory_read_global_uint8_v2
#define port_memory_read_constant_uint_quarter_v2 port_memory_read_constant_uint8_v2

// 3-vector of unsigned integers (quarter size)
#define port_memory_read_uint_quarter_v3 port_memory_read_uint8_v3
#define port_memory_read_local_uint_quarter_v3 port_memory_read_local_uint8_v3
#define port_memory_read_global_uint_quarter_v3 port_memory_read_global_uint8_v3
#define port_memory_read_constant_uint_quarter_v3 port_memory_read_constant_uint8_v3

// 4-vector of unsigned integers (quarter size)
#define port_memory_read_uint_quarter_v4 port_memory_read_uint8_v4
#define port_memory_read_local_uint_quarter_v4 port_memory_read_local_uint8_v4
#define port_memory_read_global_uint_quarter_v4 port_memory_read_global_uint8_v4
#define port_memory_read_constant_uint_quarter_v4 port_memory_read_constant_uint8_v4

// 8-vector of unsigned integers (quarter size)
#define port_memory_read_uint_quarter_v8 port_memory_read_uint8_v8
#define port_memory_read_local_uint_quarter_v8 port_memory_read_local_uint8_v8
#define port_memory_read_global_uint_quarter_v8 port_memory_read_global_uint8_v8
#define port_memory_read_constant_uint_quarter_v8 port_memory_read_constant_uint8_v8

// 16-vector of unsigned integers (quarter size)
#define port_memory_read_uint_quarter_v16 port_memory_read_uint8_v16
#define port_memory_read_local_uint_quarter_v16 port_memory_read_local_uint8_v16
#define port_memory_read_global_uint_quarter_v16 port_memory_read_global_uint8_v16
#define port_memory_read_constant_uint_quarter_v16 port_memory_read_constant_uint8_v16


// Unsigned integer (half size)
#define port_memory_read_uint_half port_memory_read_uint16
#define port_memory_read_local_uint_half port_memory_read_local_uint16
#define port_memory_read_global_uint_half port_memory_read_global_uint16
#define port_memory_read_constant_uint_half port_memory_read_constant_uint16

// 2-vector of unsigned integers (half size)
#define port_memory_read_uint_half_v2 port_memory_read_uint16_v2
#define port_memory_read_local_uint_half_v2 port_memory_read_local_uint16_v2
#define port_memory_read_global_uint_half_v2 port_memory_read_global_uint16_v2
#define port_memory_read_constant_uint_half_v2 port_memory_read_constant_uint16_v2

// 3-vector of unsigned integers (half size)
#define port_memory_read_uint_half_v3 port_memory_read_uint16_v3
#define port_memory_read_local_uint_half_v3 port_memory_read_local_uint16_v3
#define port_memory_read_global_uint_half_v3 port_memory_read_global_uint16_v3
#define port_memory_read_constant_uint_half_v3 port_memory_read_constant_uint16_v3

// 4-vector of unsigned integers (half size)
#define port_memory_read_uint_half_v4 port_memory_read_uint16_v4
#define port_memory_read_local_uint_half_v4 port_memory_read_local_uint16_v4
#define port_memory_read_global_uint_half_v4 port_memory_read_global_uint16_v4
#define port_memory_read_constant_uint_half_v4 port_memory_read_constant_uint16_v4

// 8-vector of unsigned integers (half size)
#define port_memory_read_uint_half_v8 port_memory_read_uint16_v8
#define port_memory_read_local_uint_half_v8 port_memory_read_local_uint16_v8
#define port_memory_read_global_uint_half_v8 port_memory_read_global_uint16_v8
#define port_memory_read_constant_uint_half_v8 port_memory_read_constant_uint16_v8

// 16-vector of unsigned integers (half size)
#define port_memory_read_uint_half_v16 port_memory_read_uint16_v16
#define port_memory_read_local_uint_half_v16 port_memory_read_local_uint16_v16
#define port_memory_read_global_uint_half_v16 port_memory_read_global_uint16_v16
#define port_memory_read_constant_uint_half_v16 port_memory_read_constant_uint16_v16


// Unsigned integer (single size)
#define port_memory_read_uint_single port_memory_read_uint32
#define port_memory_read_local_uint_single port_memory_read_local_uint32
#define port_memory_read_global_uint_single port_memory_read_global_uint32
#define port_memory_read_constant_uint_single port_memory_read_constant_uint32

// 2-vector of unsigned integers (single size)
#define port_memory_read_uint_single_v2 port_memory_read_uint32_v2
#define port_memory_read_local_uint_single_v2 port_memory_read_local_uint32_v2
#define port_memory_read_global_uint_single_v2 port_memory_read_global_uint32_v2
#define port_memory_read_constant_uint_single_v2 port_memory_read_constant_uint32_v2

// 3-vector of unsigned integers (single size)
#define port_memory_read_uint_single_v3 port_memory_read_uint32_v3
#define port_memory_read_local_uint_single_v3 port_memory_read_local_uint32_v3
#define port_memory_read_global_uint_single_v3 port_memory_read_global_uint32_v3
#define port_memory_read_constant_uint_single_v3 port_memory_read_constant_uint32_v3

// 4-vector of unsigned integers (single size)
#define port_memory_read_uint_single_v4 port_memory_read_uint32_v4
#define port_memory_read_local_uint_single_v4 port_memory_read_local_uint32_v4
#define port_memory_read_global_uint_single_v4 port_memory_read_global_uint32_v4
#define port_memory_read_constant_uint_single_v4 port_memory_read_constant_uint32_v4

// 8-vector of unsigned integers (single size)
#define port_memory_read_uint_single_v8 port_memory_read_uint32_v8
#define port_memory_read_local_uint_single_v8 port_memory_read_local_uint32_v8
#define port_memory_read_global_uint_single_v8 port_memory_read_global_uint32_v8
#define port_memory_read_constant_uint_single_v8 port_memory_read_constant_uint32_v8

// 16-vector of unsigned integers (single size)
#define port_memory_read_uint_single_v16 port_memory_read_uint32_v16
#define port_memory_read_local_uint_single_v16 port_memory_read_local_uint32_v16
#define port_memory_read_global_uint_single_v16 port_memory_read_global_uint32_v16
#define port_memory_read_constant_uint_single_v16 port_memory_read_constant_uint32_v16


// Unsigned integer (double size)
#define port_memory_read_uint_double port_memory_read_uint64
#define port_memory_read_local_uint_double port_memory_read_local_uint64
#define port_memory_read_global_uint_double port_memory_read_global_uint64
#define port_memory_read_constant_uint_double port_memory_read_constant_uint64

// 2-vector of unsigned integers (double size)
#define port_memory_read_uint_double_v2 port_memory_read_uint64_v2
#define port_memory_read_local_uint_double_v2 port_memory_read_local_uint64_v2
#define port_memory_read_global_uint_double_v2 port_memory_read_global_uint64_v2
#define port_memory_read_constant_uint_double_v2 port_memory_read_constant_uint64_v2

// 3-vector of unsigned integers (double size)
#define port_memory_read_uint_double_v3 port_memory_read_uint64_v3
#define port_memory_read_local_uint_double_v3 port_memory_read_local_uint64_v3
#define port_memory_read_global_uint_double_v3 port_memory_read_global_uint64_v3
#define port_memory_read_constant_uint_double_v3 port_memory_read_constant_uint64_v3

// 4-vector of unsigned integers (double size)
#define port_memory_read_uint_double_v4 port_memory_read_uint64_v4
#define port_memory_read_local_uint_double_v4 port_memory_read_local_uint64_v4
#define port_memory_read_global_uint_double_v4 port_memory_read_global_uint64_v4
#define port_memory_read_constant_uint_double_v4 port_memory_read_constant_uint64_v4

// 8-vector of unsigned integers (double size)
#define port_memory_read_uint_double_v8 port_memory_read_uint64_v8
#define port_memory_read_local_uint_double_v8 port_memory_read_local_uint64_v8
#define port_memory_read_global_uint_double_v8 port_memory_read_global_uint64_v8
#define port_memory_read_constant_uint_double_v8 port_memory_read_constant_uint64_v8

// 16-vector of unsigned integers (double size)
#define port_memory_read_uint_double_v16 port_memory_read_uint64_v16
#define port_memory_read_local_uint_double_v16 port_memory_read_local_uint64_v16
#define port_memory_read_global_uint_double_v16 port_memory_read_global_uint64_v16
#define port_memory_read_constant_uint_double_v16 port_memory_read_constant_uint64_v16


// Signed integer (quarter size)
#define port_memory_read_sint_quarter port_memory_read_sint8
#define port_memory_read_local_sint_quarter port_memory_read_local_sint8
#define port_memory_read_global_sint_quarter port_memory_read_global_sint8
#define port_memory_read_constant_sint_quarter port_memory_read_constant_sint8

// 2-vector of signed integers (quarter size)
#define port_memory_read_sint_quarter_v2 port_memory_read_sint8_v2
#define port_memory_read_local_sint_quarter_v2 port_memory_read_local_sint8_v2
#define port_memory_read_global_sint_quarter_v2 port_memory_read_global_sint8_v2
#define port_memory_read_constant_sint_quarter_v2 port_memory_read_constant_sint8_v2

// 3-vector of signed integers (quarter size)
#define port_memory_read_sint_quarter_v3 port_memory_read_sint8_v3
#define port_memory_read_local_sint_quarter_v3 port_memory_read_local_sint8_v3
#define port_memory_read_global_sint_quarter_v3 port_memory_read_global_sint8_v3
#define port_memory_read_constant_sint_quarter_v3 port_memory_read_constant_sint8_v3

// 4-vector of signed integers (quarter size)
#define port_memory_read_sint_quarter_v4 port_memory_read_sint8_v4
#define port_memory_read_local_sint_quarter_v4 port_memory_read_local_sint8_v4
#define port_memory_read_global_sint_quarter_v4 port_memory_read_global_sint8_v4
#define port_memory_read_constant_sint_quarter_v4 port_memory_read_constant_sint8_v4

// 8-vector of signed integers (quarter size)
#define port_memory_read_sint_quarter_v8 port_memory_read_sint8_v8
#define port_memory_read_local_sint_quarter_v8 port_memory_read_local_sint8_v8
#define port_memory_read_global_sint_quarter_v8 port_memory_read_global_sint8_v8
#define port_memory_read_constant_sint_quarter_v8 port_memory_read_constant_sint8_v8

// 16-vector of signed integers (quarter size)
#define port_memory_read_sint_quarter_v16 port_memory_read_sint8_v16
#define port_memory_read_local_sint_quarter_v16 port_memory_read_local_sint8_v16
#define port_memory_read_global_sint_quarter_v16 port_memory_read_global_sint8_v16
#define port_memory_read_constant_sint_quarter_v16 port_memory_read_constant_sint8_v16


// Signed integer (half size)
#define port_memory_read_sint_half port_memory_read_sint16
#define port_memory_read_local_sint_half port_memory_read_local_sint16
#define port_memory_read_global_sint_half port_memory_read_global_sint16
#define port_memory_read_constant_sint_half port_memory_read_constant_sint16

// 2-vector of signed integers (half size)
#define port_memory_read_sint_half_v2 port_memory_read_sint16_v2
#define port_memory_read_local_sint_half_v2 port_memory_read_local_sint16_v2
#define port_memory_read_global_sint_half_v2 port_memory_read_global_sint16_v2
#define port_memory_read_constant_sint_half_v2 port_memory_read_constant_sint16_v2

// 3-vector of signed integers (half size)
#define port_memory_read_sint_half_v3 port_memory_read_sint16_v3
#define port_memory_read_local_sint_half_v3 port_memory_read_local_sint16_v3
#define port_memory_read_global_sint_half_v3 port_memory_read_global_sint16_v3
#define port_memory_read_constant_sint_half_v3 port_memory_read_constant_sint16_v3

// 4-vector of signed integers (half size)
#define port_memory_read_sint_half_v4 port_memory_read_sint16_v4
#define port_memory_read_local_sint_half_v4 port_memory_read_local_sint16_v4
#define port_memory_read_global_sint_half_v4 port_memory_read_global_sint16_v4
#define port_memory_read_constant_sint_half_v4 port_memory_read_constant_sint16_v4

// 8-vector of signed integers (half size)
#define port_memory_read_sint_half_v8 port_memory_read_sint16_v8
#define port_memory_read_local_sint_half_v8 port_memory_read_local_sint16_v8
#define port_memory_read_global_sint_half_v8 port_memory_read_global_sint16_v8
#define port_memory_read_constant_sint_half_v8 port_memory_read_constant_sint16_v8

// 16-vector of signed integers (half size)
#define port_memory_read_sint_half_v16 port_memory_read_sint16_v16
#define port_memory_read_local_sint_half_v16 port_memory_read_local_sint16_v16
#define port_memory_read_global_sint_half_v16 port_memory_read_global_sint16_v16
#define port_memory_read_constant_sint_half_v16 port_memory_read_constant_sint16_v16


// Signed integer (single size)
#define port_memory_read_sint_single port_memory_read_sint32
#define port_memory_read_local_sint_single port_memory_read_local_sint32
#define port_memory_read_global_sint_single port_memory_read_global_sint32
#define port_memory_read_constant_sint_single port_memory_read_constant_sint32

// 2-vector of signed integers (single size)
#define port_memory_read_sint_single_v2 port_memory_read_sint32_v2
#define port_memory_read_local_sint_single_v2 port_memory_read_local_sint32_v2
#define port_memory_read_global_sint_single_v2 port_memory_read_global_sint32_v2
#define port_memory_read_constant_sint_single_v2 port_memory_read_constant_sint32_v2

// 3-vector of signed integers (single size)
#define port_memory_read_sint_single_v3 port_memory_read_sint32_v3
#define port_memory_read_local_sint_single_v3 port_memory_read_local_sint32_v3
#define port_memory_read_global_sint_single_v3 port_memory_read_global_sint32_v3
#define port_memory_read_constant_sint_single_v3 port_memory_read_constant_sint32_v3

// 4-vector of signed integers (single size)
#define port_memory_read_sint_single_v4 port_memory_read_sint32_v4
#define port_memory_read_local_sint_single_v4 port_memory_read_local_sint32_v4
#define port_memory_read_global_sint_single_v4 port_memory_read_global_sint32_v4
#define port_memory_read_constant_sint_single_v4 port_memory_read_constant_sint32_v4

// 8-vector of signed integers (single size)
#define port_memory_read_sint_single_v8 port_memory_read_sint32_v8
#define port_memory_read_local_sint_single_v8 port_memory_read_local_sint32_v8
#define port_memory_read_global_sint_single_v8 port_memory_read_global_sint32_v8
#define port_memory_read_constant_sint_single_v8 port_memory_read_constant_sint32_v8

// 16-vector of signed integers (single size)
#define port_memory_read_sint_single_v16 port_memory_read_sint32_v16
#define port_memory_read_local_sint_single_v16 port_memory_read_local_sint32_v16
#define port_memory_read_global_sint_single_v16 port_memory_read_global_sint32_v16
#define port_memory_read_constant_sint_single_v16 port_memory_read_constant_sint32_v16


// Signed integer (double size)
#define port_memory_read_sint_double port_memory_read_sint64
#define port_memory_read_local_sint_double port_memory_read_local_sint64
#define port_memory_read_global_sint_double port_memory_read_global_sint64
#define port_memory_read_constant_sint_double port_memory_read_constant_sint64

// 2-vector of signed integers (double size)
#define port_memory_read_sint_double_v2 port_memory_read_sint64_v2
#define port_memory_read_local_sint_double_v2 port_memory_read_local_sint64_v2
#define port_memory_read_global_sint_double_v2 port_memory_read_global_sint64_v2
#define port_memory_read_constant_sint_double_v2 port_memory_read_constant_sint64_v2

// 3-vector of signed integers (double size)
#define port_memory_read_sint_double_v3 port_memory_read_sint64_v3
#define port_memory_read_local_sint_double_v3 port_memory_read_local_sint64_v3
#define port_memory_read_global_sint_double_v3 port_memory_read_global_sint64_v3
#define port_memory_read_constant_sint_double_v3 port_memory_read_constant_sint64_v3

// 4-vector of signed integers (double size)
#define port_memory_read_sint_double_v4 port_memory_read_sint64_v4
#define port_memory_read_local_sint_double_v4 port_memory_read_local_sint64_v4
#define port_memory_read_global_sint_double_v4 port_memory_read_global_sint64_v4
#define port_memory_read_constant_sint_double_v4 port_memory_read_constant_sint64_v4

// 8-vector of signed integers (double size)
#define port_memory_read_sint_double_v8 port_memory_read_sint64_v8
#define port_memory_read_local_sint_double_v8 port_memory_read_local_sint64_v8
#define port_memory_read_global_sint_double_v8 port_memory_read_global_sint64_v8
#define port_memory_read_constant_sint_double_v8 port_memory_read_constant_sint64_v8

// 16-vector of signed integers (double size)
#define port_memory_read_sint_double_v16 port_memory_read_sint64_v16
#define port_memory_read_local_sint_double_v16 port_memory_read_local_sint64_v16
#define port_memory_read_global_sint_double_v16 port_memory_read_global_sint64_v16
#define port_memory_read_constant_sint_double_v16 port_memory_read_constant_sint64_v16


// Floating-point number (half size)
#define port_memory_read_float_half port_memory_read_float16
#define port_memory_read_local_float_half port_memory_read_local_float16
#define port_memory_read_global_float_half port_memory_read_global_float16
#define port_memory_read_constant_float_half port_memory_read_constant_float16

// 2-vector of floating-point numbers (half size)
#define port_memory_read_float_half_v2 port_memory_read_float16_v2
#define port_memory_read_local_float_half_v2 port_memory_read_local_float16_v2
#define port_memory_read_global_float_half_v2 port_memory_read_global_float16_v2
#define port_memory_read_constant_float_half_v2 port_memory_read_constant_float16_v2

// 3-vector of floating-point numbers (half size)
#define port_memory_read_float_half_v3 port_memory_read_float16_v3
#define port_memory_read_local_float_half_v3 port_memory_read_local_float16_v3
#define port_memory_read_global_float_half_v3 port_memory_read_global_float16_v3
#define port_memory_read_constant_float_half_v3 port_memory_read_constant_float16_v3

// 4-vector of floating-point numbers (half size)
#define port_memory_read_float_half_v4 port_memory_read_float16_v4
#define port_memory_read_local_float_half_v4 port_memory_read_local_float16_v4
#define port_memory_read_global_float_half_v4 port_memory_read_global_float16_v4
#define port_memory_read_constant_float_half_v4 port_memory_read_constant_float16_v4

// 8-vector of floating-point numbers (half size)
#define port_memory_read_float_half_v8 port_memory_read_float16_v8
#define port_memory_read_local_float_half_v8 port_memory_read_local_float16_v8
#define port_memory_read_global_float_half_v8 port_memory_read_global_float16_v8
#define port_memory_read_constant_float_half_v8 port_memory_read_constant_float16_v8

// 16-vector of floating-point numbers (half size)
#define port_memory_read_float_half_v16 port_memory_read_float16_v16
#define port_memory_read_local_float_half_v16 port_memory_read_local_float16_v16
#define port_memory_read_global_float_half_v16 port_memory_read_global_float16_v16
#define port_memory_read_constant_float_half_v16 port_memory_read_constant_float16_v16


// Floating-point number (single size)
#define port_memory_read_float_single port_memory_read_float32
#define port_memory_read_local_float_single port_memory_read_local_float32
#define port_memory_read_global_float_single port_memory_read_global_float32
#define port_memory_read_constant_float_single port_memory_read_constant_float32

// 2-vector of floating-point numbers (single size)
#define port_memory_read_float_single_v2 port_memory_read_float32_v2
#define port_memory_read_local_float_single_v2 port_memory_read_local_float32_v2
#define port_memory_read_global_float_single_v2 port_memory_read_global_float32_v2
#define port_memory_read_constant_float_single_v2 port_memory_read_constant_float32_v2

// 3-vector of floating-point numbers (single size)
#define port_memory_read_float_single_v3 port_memory_read_float32_v3
#define port_memory_read_local_float_single_v3 port_memory_read_local_float32_v3
#define port_memory_read_global_float_single_v3 port_memory_read_global_float32_v3
#define port_memory_read_constant_float_single_v3 port_memory_read_constant_float32_v3

// 4-vector of floating-point numbers (single size)
#define port_memory_read_float_single_v4 port_memory_read_float32_v4
#define port_memory_read_local_float_single_v4 port_memory_read_local_float32_v4
#define port_memory_read_global_float_single_v4 port_memory_read_global_float32_v4
#define port_memory_read_constant_float_single_v4 port_memory_read_constant_float32_v4

// 8-vector of floating-point numbers (single size)
#define port_memory_read_float_single_v8 port_memory_read_float32_v8
#define port_memory_read_local_float_single_v8 port_memory_read_local_float32_v8
#define port_memory_read_global_float_single_v8 port_memory_read_global_float32_v8
#define port_memory_read_constant_float_single_v8 port_memory_read_constant_float32_v8

// 16-vector of floating-point numbers (single size)
#define port_memory_read_float_single_v16 port_memory_read_float32_v16
#define port_memory_read_local_float_single_v16 port_memory_read_local_float32_v16
#define port_memory_read_global_float_single_v16 port_memory_read_global_float32_v16
#define port_memory_read_constant_float_single_v16 port_memory_read_constant_float32_v16


// Floating-point number (double size)
#define port_memory_read_float_double port_memory_read_float64
#define port_memory_read_local_float_double port_memory_read_local_float64
#define port_memory_read_global_float_double port_memory_read_global_float64
#define port_memory_read_constant_float_double port_memory_read_constant_float64

// 2-vector of floating-point numbers (double size)
#define port_memory_read_float_double_v2 port_memory_read_float64_v2
#define port_memory_read_local_float_double_v2 port_memory_read_local_float64_v2
#define port_memory_read_global_float_double_v2 port_memory_read_global_float64_v2
#define port_memory_read_constant_float_double_v2 port_memory_read_constant_float64_v2

// 3-vector of floating-point numbers (double size)
#define port_memory_read_float_double_v3 port_memory_read_float64_v3
#define port_memory_read_local_float_double_v3 port_memory_read_local_float64_v3
#define port_memory_read_global_float_double_v3 port_memory_read_global_float64_v3
#define port_memory_read_constant_float_double_v3 port_memory_read_constant_float64_v3

// 4-vector of floating-point numbers (double size)
#define port_memory_read_float_double_v4 port_memory_read_float64_v4
#define port_memory_read_local_float_double_v4 port_memory_read_local_float64_v4
#define port_memory_read_global_float_double_v4 port_memory_read_global_float64_v4
#define port_memory_read_constant_float_double_v4 port_memory_read_constant_float64_v4

// 8-vector of floating-point numbers (double size)
#define port_memory_read_float_double_v8 port_memory_read_float64_v8
#define port_memory_read_local_float_double_v8 port_memory_read_local_float64_v8
#define port_memory_read_global_float_double_v8 port_memory_read_global_float64_v8
#define port_memory_read_constant_float_double_v8 port_memory_read_constant_float64_v8

// 16-vector of floating-point numbers (double size)
#define port_memory_read_float_double_v16 port_memory_read_float64_v16
#define port_memory_read_local_float_double_v16 port_memory_read_local_float64_v16
#define port_memory_read_global_float_double_v16 port_memory_read_global_float64_v16
#define port_memory_read_constant_float_double_v16 port_memory_read_constant_float64_v16

#ifndef PORT_FEATURE_DEFAULT_INTEGER_64

// Default unsigned integer
#define port_memory_read_uint port_memory_read_uint32
#define port_memory_read_local_uint port_memory_read_local_uint32
#define port_memory_read_global_uint port_memory_read_global_uint32
#define port_memory_read_constant_uint port_memory_read_constant_uint32

// 2-vector of default unsigned integers (single size)
#define port_memory_read_uint_v2 port_memory_read_uint32_v2
#define port_memory_read_local_uint_v2 port_memory_read_local_uint32_v2
#define port_memory_read_global_uint_v2 port_memory_read_global_uint32_v2
#define port_memory_read_constant_uint_v2 port_memory_read_constant_uint32_v2

// 3-vector of default unsigned integers (single size)
#define port_memory_read_uint_v3 port_memory_read_uint32_v3
#define port_memory_read_local_uint_v3 port_memory_read_local_uint32_v3
#define port_memory_read_global_uint_v3 port_memory_read_global_uint32_v3
#define port_memory_read_constant_uint_v3 port_memory_read_constant_uint32_v3

// 4-vector of default unsigned integers (single size)
#define port_memory_read_uint_v4 port_memory_read_uint32_v4
#define port_memory_read_local_uint_v4 port_memory_read_local_uint32_v4
#define port_memory_read_global_uint_v4 port_memory_read_global_uint32_v4
#define port_memory_read_constant_uint_v4 port_memory_read_constant_uint32_v4

// 8-vector of default unsigned integers (single size)
#define port_memory_read_uint_v8 port_memory_read_uint32_v8
#define port_memory_read_local_uint_v8 port_memory_read_local_uint32_v8
#define port_memory_read_global_uint_v8 port_memory_read_global_uint32_v8
#define port_memory_read_constant_uint_v8 port_memory_read_constant_uint32_v8

// 16-vector of default unsigned integers (single size)
#define port_memory_read_uint_v16 port_memory_read_uint32_v16
#define port_memory_read_local_uint_v16 port_memory_read_local_uint32_v16
#define port_memory_read_global_uint_v16 port_memory_read_global_uint32_v16
#define port_memory_read_constant_uint_v16 port_memory_read_constant_uint32_v16


// Default signed integer
#define port_memory_read_sint port_memory_read_sint32
#define port_memory_read_local_sint port_memory_read_local_sint32
#define port_memory_read_global_sint port_memory_read_global_sint32
#define port_memory_read_constant_sint port_memory_read_constant_sint32

// 2-vector of default signed integers (single size)
#define port_memory_read_sint_v2 port_memory_read_sint32_v2
#define port_memory_read_local_sint_v2 port_memory_read_local_sint32_v2
#define port_memory_read_global_sint_v2 port_memory_read_global_sint32_v2
#define port_memory_read_constant_sint_v2 port_memory_read_constant_sint32_v2

// 3-vector of default signed integers (single size)
#define port_memory_read_sint_v3 port_memory_read_sint32_v3
#define port_memory_read_local_sint_v3 port_memory_read_local_sint32_v3
#define port_memory_read_global_sint_v3 port_memory_read_global_sint32_v3
#define port_memory_read_constant_sint_v3 port_memory_read_constant_sint32_v3

// 4-vector of default signed integers (single size)
#define port_memory_read_sint_v4 port_memory_read_sint32_v4
#define port_memory_read_local_sint_v4 port_memory_read_local_sint32_v4
#define port_memory_read_global_sint_v4 port_memory_read_global_sint32_v4
#define port_memory_read_constant_sint_v4 port_memory_read_constant_sint32_v4

// 8-vector of default signed integers (single size)
#define port_memory_read_sint_v8 port_memory_read_sint32_v8
#define port_memory_read_local_sint_v8 port_memory_read_local_sint32_v8
#define port_memory_read_global_sint_v8 port_memory_read_global_sint32_v8
#define port_memory_read_constant_sint_v8 port_memory_read_constant_sint32_v8

// 16-vector of default signed integers (single size)
#define port_memory_read_sint_v16 port_memory_read_sint32_v16
#define port_memory_read_local_sint_v16 port_memory_read_local_sint32_v16
#define port_memory_read_global_sint_v16 port_memory_read_global_sint32_v16
#define port_memory_read_constant_sint_v16 port_memory_read_constant_sint32_v16

#else // PORT_FEATURE_DEFAULT_INTEGER_64

// Default unsigned integer
#define port_memory_read_uint port_memory_read_uint64
#define port_memory_read_local_uint port_memory_read_local_uint64
#define port_memory_read_global_uint port_memory_read_global_uint64
#define port_memory_read_constant_uint port_memory_read_constant_uint64

// 2-vector of default unsigned integers (single size)
#define port_memory_read_uint_v2 port_memory_read_uint64_v2
#define port_memory_read_local_uint_v2 port_memory_read_local_uint64_v2
#define port_memory_read_global_uint_v2 port_memory_read_global_uint64_v2
#define port_memory_read_constant_uint_v2 port_memory_read_constant_uint64_v2

// 3-vector of default unsigned integers (single size)
#define port_memory_read_uint_v3 port_memory_read_uint64_v3
#define port_memory_read_local_uint_v3 port_memory_read_local_uint64_v3
#define port_memory_read_global_uint_v3 port_memory_read_global_uint64_v3
#define port_memory_read_constant_uint_v3 port_memory_read_constant_uint64_v3

// 4-vector of default unsigned integers (single size)
#define port_memory_read_uint_v4 port_memory_read_uint64_v4
#define port_memory_read_local_uint_v4 port_memory_read_local_uint64_v4
#define port_memory_read_global_uint_v4 port_memory_read_global_uint64_v4
#define port_memory_read_constant_uint_v4 port_memory_read_constant_uint64_v4

// 8-vector of default unsigned integers (single size)
#define port_memory_read_uint_v8 port_memory_read_uint64_v8
#define port_memory_read_local_uint_v8 port_memory_read_local_uint64_v8
#define port_memory_read_global_uint_v8 port_memory_read_global_uint64_v8
#define port_memory_read_constant_uint_v8 port_memory_read_constant_uint64_v8

// 16-vector of default unsigned integers (single size)
#define port_memory_read_uint_v16 port_memory_read_uint64_v16
#define port_memory_read_local_uint_v16 port_memory_read_local_uint64_v16
#define port_memory_read_global_uint_v16 port_memory_read_global_uint64_v16
#define port_memory_read_constant_uint_v16 port_memory_read_constant_uint64_v16


// Default signed integer
#define port_memory_read_sint port_memory_read_sint64
#define port_memory_read_local_sint port_memory_read_local_sint64
#define port_memory_read_global_sint port_memory_read_global_sint64
#define port_memory_read_constant_sint port_memory_read_constant_sint64

// 2-vector of default signed integers (single size)
#define port_memory_read_sint_v2 port_memory_read_sint64_v2
#define port_memory_read_local_sint_v2 port_memory_read_local_sint64_v2
#define port_memory_read_global_sint_v2 port_memory_read_global_sint64_v2
#define port_memory_read_constant_sint_v2 port_memory_read_constant_sint64_v2

// 3-vector of default signed integers (single size)
#define port_memory_read_sint_v3 port_memory_read_sint64_v3
#define port_memory_read_local_sint_v3 port_memory_read_local_sint64_v3
#define port_memory_read_global_sint_v3 port_memory_read_global_sint64_v3
#define port_memory_read_constant_sint_v3 port_memory_read_constant_sint64_v3

// 4-vector of default signed integers (single size)
#define port_memory_read_sint_v4 port_memory_read_sint64_v4
#define port_memory_read_local_sint_v4 port_memory_read_local_sint64_v4
#define port_memory_read_global_sint_v4 port_memory_read_global_sint64_v4
#define port_memory_read_constant_sint_v4 port_memory_read_constant_sint64_v4

// 8-vector of default signed integers (single size)
#define port_memory_read_sint_v8 port_memory_read_sint64_v8
#define port_memory_read_local_sint_v8 port_memory_read_local_sint64_v8
#define port_memory_read_global_sint_v8 port_memory_read_global_sint64_v8
#define port_memory_read_constant_sint_v8 port_memory_read_constant_sint64_v8

// 16-vector of default signed integers (single size)
#define port_memory_read_sint_v16 port_memory_read_sint64_v16
#define port_memory_read_local_sint_v16 port_memory_read_local_sint64_v16
#define port_memory_read_global_sint_v16 port_memory_read_global_sint64_v16
#define port_memory_read_constant_sint_v16 port_memory_read_constant_sint64_v16

#endif // PORT_FEATURE_DEFAULT_INTEGER_64

#ifndef PORT_FEATURE_DEFAULT_FLOAT_64

// Default floating-point number
#define port_memory_read_float port_memory_read_float32
#define port_memory_read_local_float port_memory_read_local_float32
#define port_memory_read_global_float port_memory_read_global_float32
#define port_memory_read_constant_float port_memory_read_constant_float32

// 2-vector of default floating-point numbers (single size)
#define port_memory_read_float_v2 port_memory_read_float32_v2
#define port_memory_read_local_float_v2 port_memory_read_local_float32_v2
#define port_memory_read_global_float_v2 port_memory_read_global_float32_v2
#define port_memory_read_constant_float_v2 port_memory_read_constant_float32_v2

// 3-vector of default floating-point numbers (single size)
#define port_memory_read_float_v3 port_memory_read_float32_v3
#define port_memory_read_local_float_v3 port_memory_read_local_float32_v3
#define port_memory_read_global_float_v3 port_memory_read_global_float32_v3
#define port_memory_read_constant_float_v3 port_memory_read_constant_float32_v3

// 4-vector of default floating-point numbers (single size)
#define port_memory_read_float_v4 port_memory_read_float32_v4
#define port_memory_read_local_float_v4 port_memory_read_local_float32_v4
#define port_memory_read_global_float_v4 port_memory_read_global_float32_v4
#define port_memory_read_constant_float_v4 port_memory_read_constant_float32_v4

// 8-vector of default floating-point numbers (single size)
#define port_memory_read_float_v8 port_memory_read_float32_v8
#define port_memory_read_local_float_v8 port_memory_read_local_float32_v8
#define port_memory_read_global_float_v8 port_memory_read_global_float32_v8
#define port_memory_read_constant_float_v8 port_memory_read_constant_float32_v8

// 16-vector of default floating-point numbers (single size)
#define port_memory_read_float_v16 port_memory_read_float32_v16
#define port_memory_read_local_float_v16 port_memory_read_local_float32_v16
#define port_memory_read_global_float_v16 port_memory_read_global_float32_v16
#define port_memory_read_constant_float_v16 port_memory_read_constant_float32_v16

#else // PORT_FEATURE_DEFAULT_FLOAT_64

// Default floating-point number
#define port_memory_read_float port_memory_read_float64
#define port_memory_read_local_float port_memory_read_local_float64
#define port_memory_read_global_float port_memory_read_global_float64
#define port_memory_read_constant_float port_memory_read_constant_float64

// 2-vector of default floating-point numbers (single size)
#define port_memory_read_float_v2 port_memory_read_float64_v2
#define port_memory_read_local_float_v2 port_memory_read_local_float64_v2
#define port_memory_read_global_float_v2 port_memory_read_global_float64_v2
#define port_memory_read_constant_float_v2 port_memory_read_constant_float64_v2

// 3-vector of default floating-point numbers (single size)
#define port_memory_read_float_v3 port_memory_read_float64_v3
#define port_memory_read_local_float_v3 port_memory_read_local_float64_v3
#define port_memory_read_global_float_v3 port_memory_read_global_float64_v3
#define port_memory_read_constant_float_v3 port_memory_read_constant_float64_v3

// 4-vector of default floating-point numbers (single size)
#define port_memory_read_float_v4 port_memory_read_float64_v4
#define port_memory_read_local_float_v4 port_memory_read_local_float64_v4
#define port_memory_read_global_float_v4 port_memory_read_global_float64_v4
#define port_memory_read_constant_float_v4 port_memory_read_constant_float64_v4

// 8-vector of default floating-point numbers (single size)
#define port_memory_read_float_v8 port_memory_read_float64_v8
#define port_memory_read_local_float_v8 port_memory_read_local_float64_v8
#define port_memory_read_global_float_v8 port_memory_read_global_float64_v8
#define port_memory_read_constant_float_v8 port_memory_read_constant_float64_v8

// 16-vector of default floating-point numbers (single size)
#define port_memory_read_float_v16 port_memory_read_float64_v16
#define port_memory_read_local_float_v16 port_memory_read_local_float64_v16
#define port_memory_read_global_float_v16 port_memory_read_global_float64_v16
#define port_memory_read_constant_float_v16 port_memory_read_constant_float64_v16

#endif // PORT_FEATURE_DEFAULT_FLOAT_64

///////////////////////////////////////////////////////////////////////////////
// Aliases for other types
///////////////////////////////////////////////////////////////////////////////

// Memory references
#define port_memory_read_memory_ref port_memory_read_sint_single
#define port_memory_read_local_memory_ref port_memory_read_local_sint_single
#define port_memory_read_global_memory_ref port_memory_read_global_sint_single
#define port_memory_read_constant_memory_ref port_memory_read_constant_sint_single

#define port_memory_read_memory_ref_half port_memory_read_sint_half
#define port_memory_read_local_memory_ref_half port_memory_read_local_sint_half
#define port_memory_read_global_memory_ref_half port_memory_read_global_sint_half
#define port_memory_read_constant_memory_ref_half port_memory_read_constant_sint_half

#define port_memory_read_memory_ref_quarter port_memory_read_sint_quarter
#define port_memory_read_local_memory_ref_quarter port_memory_read_local_sint_quarter
#define port_memory_read_global_memory_ref_quarter port_memory_read_global_sint_quarter
#define port_memory_read_constant_memory_ref_quarter port_memory_read_constant_sint_quarter

#endif // _PORT_MEMORY_READ_FUN_H_

