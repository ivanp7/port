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
 * @brief Functions for writing built-in types to memory.
 */

#pragma once
#ifndef _PORT_MEMORY_WRITE_FUN_H_
#define _PORT_MEMORY_WRITE_FUN_H_

#include "port/pointer.typ.h"


///////////////////////////////////////////////////////////////////////////////
// Functions for built-in types (generic address space)
///////////////////////////////////////////////////////////////////////////////

// Unsigned integer (8-bit)
void port_memory_write_uint8(port_void_ptr_t memory, size_t offset, port_uint8_t value);
void port_memory_write_uint8_v2(port_void_ptr_t memory, size_t offset, port_uint8_v2_t value);
void port_memory_write_uint8_v3(port_void_ptr_t memory, size_t offset, port_uint8_v3_t value);
void port_memory_write_uint8_v4(port_void_ptr_t memory, size_t offset, port_uint8_v4_t value);
void port_memory_write_uint8_v8(port_void_ptr_t memory, size_t offset, port_uint8_v8_t value);
void port_memory_write_uint8_v16(port_void_ptr_t memory, size_t offset, port_uint8_v16_t value);

// Unsigned integer (16-bit)
void port_memory_write_uint16(port_void_ptr_t memory, size_t offset, port_uint16_t value);
void port_memory_write_uint16_v2(port_void_ptr_t memory, size_t offset, port_uint16_v2_t value);
void port_memory_write_uint16_v3(port_void_ptr_t memory, size_t offset, port_uint16_v3_t value);
void port_memory_write_uint16_v4(port_void_ptr_t memory, size_t offset, port_uint16_v4_t value);
void port_memory_write_uint16_v8(port_void_ptr_t memory, size_t offset, port_uint16_v8_t value);
void port_memory_write_uint16_v16(port_void_ptr_t memory, size_t offset, port_uint16_v16_t value);

// Unsigned integer (32-bit)
void port_memory_write_uint32(port_void_ptr_t memory, size_t offset, port_uint32_t value);
void port_memory_write_uint32_v2(port_void_ptr_t memory, size_t offset, port_uint32_v2_t value);
void port_memory_write_uint32_v3(port_void_ptr_t memory, size_t offset, port_uint32_v3_t value);
void port_memory_write_uint32_v4(port_void_ptr_t memory, size_t offset, port_uint32_v4_t value);
void port_memory_write_uint32_v8(port_void_ptr_t memory, size_t offset, port_uint32_v8_t value);
void port_memory_write_uint32_v16(port_void_ptr_t memory, size_t offset, port_uint32_v16_t value);

// Unsigned integer (64-bit)
void port_memory_write_uint64(port_void_ptr_t memory, size_t offset, port_uint64_t value);
void port_memory_write_uint64_v2(port_void_ptr_t memory, size_t offset, port_uint64_v2_t value);
void port_memory_write_uint64_v3(port_void_ptr_t memory, size_t offset, port_uint64_v3_t value);
void port_memory_write_uint64_v4(port_void_ptr_t memory, size_t offset, port_uint64_v4_t value);
void port_memory_write_uint64_v8(port_void_ptr_t memory, size_t offset, port_uint64_v8_t value);
void port_memory_write_uint64_v16(port_void_ptr_t memory, size_t offset, port_uint64_v16_t value);

// Signed integer (8-bit)
void port_memory_write_sint8(port_void_ptr_t memory, size_t offset, port_sint8_t value);
void port_memory_write_sint8_v2(port_void_ptr_t memory, size_t offset, port_sint8_v2_t value);
void port_memory_write_sint8_v3(port_void_ptr_t memory, size_t offset, port_sint8_v3_t value);
void port_memory_write_sint8_v4(port_void_ptr_t memory, size_t offset, port_sint8_v4_t value);
void port_memory_write_sint8_v8(port_void_ptr_t memory, size_t offset, port_sint8_v8_t value);
void port_memory_write_sint8_v16(port_void_ptr_t memory, size_t offset, port_sint8_v16_t value);

// Signed integer (16-bit)
void port_memory_write_sint16(port_void_ptr_t memory, size_t offset, port_sint16_t value);
void port_memory_write_sint16_v2(port_void_ptr_t memory, size_t offset, port_sint16_v2_t value);
void port_memory_write_sint16_v3(port_void_ptr_t memory, size_t offset, port_sint16_v3_t value);
void port_memory_write_sint16_v4(port_void_ptr_t memory, size_t offset, port_sint16_v4_t value);
void port_memory_write_sint16_v8(port_void_ptr_t memory, size_t offset, port_sint16_v8_t value);
void port_memory_write_sint16_v16(port_void_ptr_t memory, size_t offset, port_sint16_v16_t value);

// Signed integer (32-bit)
void port_memory_write_sint32(port_void_ptr_t memory, size_t offset, port_sint32_t value);
void port_memory_write_sint32_v2(port_void_ptr_t memory, size_t offset, port_sint32_v2_t value);
void port_memory_write_sint32_v3(port_void_ptr_t memory, size_t offset, port_sint32_v3_t value);
void port_memory_write_sint32_v4(port_void_ptr_t memory, size_t offset, port_sint32_v4_t value);
void port_memory_write_sint32_v8(port_void_ptr_t memory, size_t offset, port_sint32_v8_t value);
void port_memory_write_sint32_v16(port_void_ptr_t memory, size_t offset, port_sint32_v16_t value);

// Signed integer (64-bit)
void port_memory_write_sint64(port_void_ptr_t memory, size_t offset, port_sint64_t value);
void port_memory_write_sint64_v2(port_void_ptr_t memory, size_t offset, port_sint64_v2_t value);
void port_memory_write_sint64_v3(port_void_ptr_t memory, size_t offset, port_sint64_v3_t value);
void port_memory_write_sint64_v4(port_void_ptr_t memory, size_t offset, port_sint64_v4_t value);
void port_memory_write_sint64_v8(port_void_ptr_t memory, size_t offset, port_sint64_v8_t value);
void port_memory_write_sint64_v16(port_void_ptr_t memory, size_t offset, port_sint64_v16_t value);

// Floating-point number (16-bit)
void port_memory_write_float16(port_void_ptr_t memory, size_t offset, port_float32_t value);
void port_memory_write_float16_v2(port_void_ptr_t memory, size_t offset, port_float32_v2_t value);
void port_memory_write_float16_v3(port_void_ptr_t memory, size_t offset, port_float32_v3_t value);
void port_memory_write_float16_v4(port_void_ptr_t memory, size_t offset, port_float32_v4_t value);
void port_memory_write_float16_v8(port_void_ptr_t memory, size_t offset, port_float32_v8_t value);
void port_memory_write_float16_v16(port_void_ptr_t memory, size_t offset, port_float32_v16_t value);

// Floating-point number (32-bit)
void port_memory_write_float32(port_void_ptr_t memory, size_t offset, port_float32_t value);
void port_memory_write_float32_v2(port_void_ptr_t memory, size_t offset, port_float32_v2_t value);
void port_memory_write_float32_v3(port_void_ptr_t memory, size_t offset, port_float32_v3_t value);
void port_memory_write_float32_v4(port_void_ptr_t memory, size_t offset, port_float32_v4_t value);
void port_memory_write_float32_v8(port_void_ptr_t memory, size_t offset, port_float32_v8_t value);
void port_memory_write_float32_v16(port_void_ptr_t memory, size_t offset, port_float32_v16_t value);

// Floating-point number (64-bit)
void port_memory_write_float64(port_void_ptr_t memory, size_t offset, port_float64_t value);
void port_memory_write_float64_v2(port_void_ptr_t memory, size_t offset, port_float64_v2_t value);
void port_memory_write_float64_v3(port_void_ptr_t memory, size_t offset, port_float64_v3_t value);
void port_memory_write_float64_v4(port_void_ptr_t memory, size_t offset, port_float64_v4_t value);
void port_memory_write_float64_v8(port_void_ptr_t memory, size_t offset, port_float64_v8_t value);
void port_memory_write_float64_v16(port_void_ptr_t memory, size_t offset, port_float64_v16_t value);

#ifdef __OPENCL_C_VERSION__

///////////////////////////////////////////////////////////////////////////////
// Functions for built-in types (named address spaces)
///////////////////////////////////////////////////////////////////////////////

// Unsigned integer (8-bit)
void port_memory_write_local_uint8(port_local_void_ptr_t memory, size_t offset, port_uint8_t value);
void port_memory_write_global_uint8(port_global_void_ptr_t memory, size_t offset, port_uint8_t value);

// 2-vector of unsigned integers (8-bit)
void port_memory_write_local_uint8_v2(port_local_void_ptr_t memory, size_t offset, port_uint8_v2_t value);
void port_memory_write_global_uint8_v2(port_global_void_ptr_t memory, size_t offset, port_uint8_v2_t value);

// 3-vector of unsigned integers (8-bit)
void port_memory_write_local_uint8_v3(port_local_void_ptr_t memory, size_t offset, port_uint8_v3_t value);
void port_memory_write_global_uint8_v3(port_global_void_ptr_t memory, size_t offset, port_uint8_v3_t value);

// 4-vector of unsigned integers (8-bit)
void port_memory_write_local_uint8_v4(port_local_void_ptr_t memory, size_t offset, port_uint8_v4_t value);
void port_memory_write_global_uint8_v4(port_global_void_ptr_t memory, size_t offset, port_uint8_v4_t value);

// 8-vector of unsigned integers (8-bit)
void port_memory_write_local_uint8_v8(port_local_void_ptr_t memory, size_t offset, port_uint8_v8_t value);
void port_memory_write_global_uint8_v8(port_global_void_ptr_t memory, size_t offset, port_uint8_v8_t value);

// 16-vector of unsigned integers (8-bit)
void port_memory_write_local_uint8_v16(port_local_void_ptr_t memory, size_t offset, port_uint8_v16_t value);
void port_memory_write_global_uint8_v16(port_global_void_ptr_t memory, size_t offset, port_uint8_v16_t value);


// Unsigned integer (16-bit)
void port_memory_write_local_uint16(port_local_void_ptr_t memory, size_t offset, port_uint16_t value);
void port_memory_write_global_uint16(port_global_void_ptr_t memory, size_t offset, port_uint16_t value);

// 2-vector of unsigned integers (16-bit)
void port_memory_write_local_uint16_v2(port_local_void_ptr_t memory, size_t offset, port_uint16_v2_t value);
void port_memory_write_global_uint16_v2(port_global_void_ptr_t memory, size_t offset, port_uint16_v2_t value);

// 3-vector of unsigned integers (16-bit)
void port_memory_write_local_uint16_v3(port_local_void_ptr_t memory, size_t offset, port_uint16_v3_t value);
void port_memory_write_global_uint16_v3(port_global_void_ptr_t memory, size_t offset, port_uint16_v3_t value);

// 4-vector of unsigned integers (16-bit)
void port_memory_write_local_uint16_v4(port_local_void_ptr_t memory, size_t offset, port_uint16_v4_t value);
void port_memory_write_global_uint16_v4(port_global_void_ptr_t memory, size_t offset, port_uint16_v4_t value);

// 8-vector of unsigned integers (16-bit)
void port_memory_write_local_uint16_v8(port_local_void_ptr_t memory, size_t offset, port_uint16_v8_t value);
void port_memory_write_global_uint16_v8(port_global_void_ptr_t memory, size_t offset, port_uint16_v8_t value);

// 16-vector of unsigned integers (16-bit)
void port_memory_write_local_uint16_v16(port_local_void_ptr_t memory, size_t offset, port_uint16_v16_t value);
void port_memory_write_global_uint16_v16(port_global_void_ptr_t memory, size_t offset, port_uint16_v16_t value);


// Unsigned integer (32-bit)
void port_memory_write_local_uint32(port_local_void_ptr_t memory, size_t offset, port_uint32_t value);
void port_memory_write_global_uint32(port_global_void_ptr_t memory, size_t offset, port_uint32_t value);

// 2-vector of unsigned integers (32-bit)
void port_memory_write_local_uint32_v2(port_local_void_ptr_t memory, size_t offset, port_uint32_v2_t value);
void port_memory_write_global_uint32_v2(port_global_void_ptr_t memory, size_t offset, port_uint32_v2_t value);

// 3-vector of unsigned integers (32-bit)
void port_memory_write_local_uint32_v3(port_local_void_ptr_t memory, size_t offset, port_uint32_v3_t value);
void port_memory_write_global_uint32_v3(port_global_void_ptr_t memory, size_t offset, port_uint32_v3_t value);

// 4-vector of unsigned integers (32-bit)
void port_memory_write_local_uint32_v4(port_local_void_ptr_t memory, size_t offset, port_uint32_v4_t value);
void port_memory_write_global_uint32_v4(port_global_void_ptr_t memory, size_t offset, port_uint32_v4_t value);

// 8-vector of unsigned integers (32-bit)
void port_memory_write_local_uint32_v8(port_local_void_ptr_t memory, size_t offset, port_uint32_v8_t value);
void port_memory_write_global_uint32_v8(port_global_void_ptr_t memory, size_t offset, port_uint32_v8_t value);

// 16-vector of unsigned integers (32-bit)
void port_memory_write_local_uint32_v16(port_local_void_ptr_t memory, size_t offset, port_uint32_v16_t value);
void port_memory_write_global_uint32_v16(port_global_void_ptr_t memory, size_t offset, port_uint32_v16_t value);


// Unsigned integer (64-bit)
void port_memory_write_local_uint64(port_local_void_ptr_t memory, size_t offset, port_uint64_t value);
void port_memory_write_global_uint64(port_global_void_ptr_t memory, size_t offset, port_uint64_t value);

// 2-vector of unsigned integers (64-bit)
void port_memory_write_local_uint64_v2(port_local_void_ptr_t memory, size_t offset, port_uint64_v2_t value);
void port_memory_write_global_uint64_v2(port_global_void_ptr_t memory, size_t offset, port_uint64_v2_t value);

// 3-vector of unsigned integers (64-bit)
void port_memory_write_local_uint64_v3(port_local_void_ptr_t memory, size_t offset, port_uint64_v3_t value);
void port_memory_write_global_uint64_v3(port_global_void_ptr_t memory, size_t offset, port_uint64_v3_t value);

// 4-vector of unsigned integers (64-bit)
void port_memory_write_local_uint64_v4(port_local_void_ptr_t memory, size_t offset, port_uint64_v4_t value);
void port_memory_write_global_uint64_v4(port_global_void_ptr_t memory, size_t offset, port_uint64_v4_t value);

// 8-vector of unsigned integers (64-bit)
void port_memory_write_local_uint64_v8(port_local_void_ptr_t memory, size_t offset, port_uint64_v8_t value);
void port_memory_write_global_uint64_v8(port_global_void_ptr_t memory, size_t offset, port_uint64_v8_t value);

// 16-vector of unsigned integers (64-bit)
void port_memory_write_local_uint64_v16(port_local_void_ptr_t memory, size_t offset, port_uint64_v16_t value);
void port_memory_write_global_uint64_v16(port_global_void_ptr_t memory, size_t offset, port_uint64_v16_t value);


// Signed integer (8-bit)
void port_memory_write_local_sint8(port_local_void_ptr_t memory, size_t offset, port_sint8_t value);
void port_memory_write_global_sint8(port_global_void_ptr_t memory, size_t offset, port_sint8_t value);

// 2-vector of signed integers (8-bit)
void port_memory_write_local_sint8_v2(port_local_void_ptr_t memory, size_t offset, port_sint8_v2_t value);
void port_memory_write_global_sint8_v2(port_global_void_ptr_t memory, size_t offset, port_sint8_v2_t value);

// 3-vector of signed integers (8-bit)
void port_memory_write_local_sint8_v3(port_local_void_ptr_t memory, size_t offset, port_sint8_v3_t value);
void port_memory_write_global_sint8_v3(port_global_void_ptr_t memory, size_t offset, port_sint8_v3_t value);

// 4-vector of signed integers (8-bit)
void port_memory_write_local_sint8_v4(port_local_void_ptr_t memory, size_t offset, port_sint8_v4_t value);
void port_memory_write_global_sint8_v4(port_global_void_ptr_t memory, size_t offset, port_sint8_v4_t value);

// 8-vector of signed integers (8-bit)
void port_memory_write_local_sint8_v8(port_local_void_ptr_t memory, size_t offset, port_sint8_v8_t value);
void port_memory_write_global_sint8_v8(port_global_void_ptr_t memory, size_t offset, port_sint8_v8_t value);

// 16-vector of signed integers (8-bit)
void port_memory_write_local_sint8_v16(port_local_void_ptr_t memory, size_t offset, port_sint8_v16_t value);
void port_memory_write_global_sint8_v16(port_global_void_ptr_t memory, size_t offset, port_sint8_v16_t value);


// Signed integer (16-bit)
void port_memory_write_local_sint16(port_local_void_ptr_t memory, size_t offset, port_sint16_t value);
void port_memory_write_global_sint16(port_global_void_ptr_t memory, size_t offset, port_sint16_t value);

// 2-vector of signed integers (16-bit)
void port_memory_write_local_sint16_v2(port_local_void_ptr_t memory, size_t offset, port_sint16_v2_t value);
void port_memory_write_global_sint16_v2(port_global_void_ptr_t memory, size_t offset, port_sint16_v2_t value);

// 3-vector of signed integers (16-bit)
void port_memory_write_local_sint16_v3(port_local_void_ptr_t memory, size_t offset, port_sint16_v3_t value);
void port_memory_write_global_sint16_v3(port_global_void_ptr_t memory, size_t offset, port_sint16_v3_t value);

// 4-vector of signed integers (16-bit)
void port_memory_write_local_sint16_v4(port_local_void_ptr_t memory, size_t offset, port_sint16_v4_t value);
void port_memory_write_global_sint16_v4(port_global_void_ptr_t memory, size_t offset, port_sint16_v4_t value);

// 8-vector of signed integers (16-bit)
void port_memory_write_local_sint16_v8(port_local_void_ptr_t memory, size_t offset, port_sint16_v8_t value);
void port_memory_write_global_sint16_v8(port_global_void_ptr_t memory, size_t offset, port_sint16_v8_t value);

// 16-vector of signed integers (16-bit)
void port_memory_write_local_sint16_v16(port_local_void_ptr_t memory, size_t offset, port_sint16_v16_t value);
void port_memory_write_global_sint16_v16(port_global_void_ptr_t memory, size_t offset, port_sint16_v16_t value);


// Signed integer (32-bit)
void port_memory_write_local_sint32(port_local_void_ptr_t memory, size_t offset, port_sint32_t value);
void port_memory_write_global_sint32(port_global_void_ptr_t memory, size_t offset, port_sint32_t value);

// 2-vector of signed integers (32-bit)
void port_memory_write_local_sint32_v2(port_local_void_ptr_t memory, size_t offset, port_sint32_v2_t value);
void port_memory_write_global_sint32_v2(port_global_void_ptr_t memory, size_t offset, port_sint32_v2_t value);

// 3-vector of signed integers (32-bit)
void port_memory_write_local_sint32_v3(port_local_void_ptr_t memory, size_t offset, port_sint32_v3_t value);
void port_memory_write_global_sint32_v3(port_global_void_ptr_t memory, size_t offset, port_sint32_v3_t value);

// 4-vector of signed integers (32-bit)
void port_memory_write_local_sint32_v4(port_local_void_ptr_t memory, size_t offset, port_sint32_v4_t value);
void port_memory_write_global_sint32_v4(port_global_void_ptr_t memory, size_t offset, port_sint32_v4_t value);

// 8-vector of signed integers (32-bit)
void port_memory_write_local_sint32_v8(port_local_void_ptr_t memory, size_t offset, port_sint32_v8_t value);
void port_memory_write_global_sint32_v8(port_global_void_ptr_t memory, size_t offset, port_sint32_v8_t value);

// 16-vector of signed integers (32-bit)
void port_memory_write_local_sint32_v16(port_local_void_ptr_t memory, size_t offset, port_sint32_v16_t value);
void port_memory_write_global_sint32_v16(port_global_void_ptr_t memory, size_t offset, port_sint32_v16_t value);


// Signed integer (64-bit)
void port_memory_write_local_sint64(port_local_void_ptr_t memory, size_t offset, port_sint64_t value);
void port_memory_write_global_sint64(port_global_void_ptr_t memory, size_t offset, port_sint64_t value);

// 2-vector of signed integers (64-bit)
void port_memory_write_local_sint64_v2(port_local_void_ptr_t memory, size_t offset, port_sint64_v2_t value);
void port_memory_write_global_sint64_v2(port_global_void_ptr_t memory, size_t offset, port_sint64_v2_t value);

// 3-vector of signed integers (64-bit)
void port_memory_write_local_sint64_v3(port_local_void_ptr_t memory, size_t offset, port_sint64_v3_t value);
void port_memory_write_global_sint64_v3(port_global_void_ptr_t memory, size_t offset, port_sint64_v3_t value);

// 4-vector of signed integers (64-bit)
void port_memory_write_local_sint64_v4(port_local_void_ptr_t memory, size_t offset, port_sint64_v4_t value);
void port_memory_write_global_sint64_v4(port_global_void_ptr_t memory, size_t offset, port_sint64_v4_t value);

// 8-vector of signed integers (64-bit)
void port_memory_write_local_sint64_v8(port_local_void_ptr_t memory, size_t offset, port_sint64_v8_t value);
void port_memory_write_global_sint64_v8(port_global_void_ptr_t memory, size_t offset, port_sint64_v8_t value);

// 16-vector of signed integers (64-bit)
void port_memory_write_local_sint64_v16(port_local_void_ptr_t memory, size_t offset, port_sint64_v16_t value);
void port_memory_write_global_sint64_v16(port_global_void_ptr_t memory, size_t offset, port_sint64_v16_t value);


// Floating-point number (16-bit)
void port_memory_write_local_float16(port_local_void_ptr_t memory, size_t offset, port_float32_t value);
void port_memory_write_global_float16(port_global_void_ptr_t memory, size_t offset, port_float32_t value);

// 2-vector of floating-point numbers (16-bit)
void port_memory_write_local_float16_v2(port_local_void_ptr_t memory, size_t offset, port_float32_v2_t value);
void port_memory_write_global_float16_v2(port_global_void_ptr_t memory, size_t offset, port_float32_v2_t value);

// 3-vector of floating-point numbers (16-bit)
void port_memory_write_local_float16_v3(port_local_void_ptr_t memory, size_t offset, port_float32_v3_t value);
void port_memory_write_global_float16_v3(port_global_void_ptr_t memory, size_t offset, port_float32_v3_t value);

// 4-vector of floating-point numbers (16-bit)
void port_memory_write_local_float16_v4(port_local_void_ptr_t memory, size_t offset, port_float32_v4_t value);
void port_memory_write_global_float16_v4(port_global_void_ptr_t memory, size_t offset, port_float32_v4_t value);

// 8-vector of floating-point numbers (16-bit)
void port_memory_write_local_float16_v8(port_local_void_ptr_t memory, size_t offset, port_float32_v8_t value);
void port_memory_write_global_float16_v8(port_global_void_ptr_t memory, size_t offset, port_float32_v8_t value);

// 16-vector of floating-point numbers (16-bit)
void port_memory_write_local_float16_v16(port_local_void_ptr_t memory, size_t offset, port_float32_v16_t value);
void port_memory_write_global_float16_v16(port_global_void_ptr_t memory, size_t offset, port_float32_v16_t value);


// Floating-point number (32-bit)
void port_memory_write_local_float32(port_local_void_ptr_t memory, size_t offset, port_float32_t value);
void port_memory_write_global_float32(port_global_void_ptr_t memory, size_t offset, port_float32_t value);

// 2-vector of floating-point numbers (32-bit)
void port_memory_write_local_float32_v2(port_local_void_ptr_t memory, size_t offset, port_float32_v2_t value);
void port_memory_write_global_float32_v2(port_global_void_ptr_t memory, size_t offset, port_float32_v2_t value);

// 3-vector of floating-point numbers (32-bit)
void port_memory_write_local_float32_v3(port_local_void_ptr_t memory, size_t offset, port_float32_v3_t value);
void port_memory_write_global_float32_v3(port_global_void_ptr_t memory, size_t offset, port_float32_v3_t value);

// 4-vector of floating-point numbers (32-bit)
void port_memory_write_local_float32_v4(port_local_void_ptr_t memory, size_t offset, port_float32_v4_t value);
void port_memory_write_global_float32_v4(port_global_void_ptr_t memory, size_t offset, port_float32_v4_t value);

// 8-vector of floating-point numbers (32-bit)
void port_memory_write_local_float32_v8(port_local_void_ptr_t memory, size_t offset, port_float32_v8_t value);
void port_memory_write_global_float32_v8(port_global_void_ptr_t memory, size_t offset, port_float32_v8_t value);

// 16-vector of floating-point numbers (32-bit)
void port_memory_write_local_float32_v16(port_local_void_ptr_t memory, size_t offset, port_float32_v16_t value);
void port_memory_write_global_float32_v16(port_global_void_ptr_t memory, size_t offset, port_float32_v16_t value);


// Floating-point number (64-bit)
void port_memory_write_local_float64(port_local_void_ptr_t memory, size_t offset, port_float64_t value);
void port_memory_write_global_float64(port_global_void_ptr_t memory, size_t offset, port_float64_t value);

// 2-vector of floating-point numbers (64-bit)
void port_memory_write_local_float64_v2(port_local_void_ptr_t memory, size_t offset, port_float64_v2_t value);
void port_memory_write_global_float64_v2(port_global_void_ptr_t memory, size_t offset, port_float64_v2_t value);

// 3-vector of floating-point numbers (64-bit)
void port_memory_write_local_float64_v3(port_local_void_ptr_t memory, size_t offset, port_float64_v3_t value);
void port_memory_write_global_float64_v3(port_global_void_ptr_t memory, size_t offset, port_float64_v3_t value);

// 4-vector of floating-point numbers (64-bit)
void port_memory_write_local_float64_v4(port_local_void_ptr_t memory, size_t offset, port_float64_v4_t value);
void port_memory_write_global_float64_v4(port_global_void_ptr_t memory, size_t offset, port_float64_v4_t value);

// 8-vector of floating-point numbers (64-bit)
void port_memory_write_local_float64_v8(port_local_void_ptr_t memory, size_t offset, port_float64_v8_t value);
void port_memory_write_global_float64_v8(port_global_void_ptr_t memory, size_t offset, port_float64_v8_t value);

// 16-vector of floating-point numbers (64-bit)
void port_memory_write_local_float64_v16(port_local_void_ptr_t memory, size_t offset, port_float64_v16_t value);
void port_memory_write_global_float64_v16(port_global_void_ptr_t memory, size_t offset, port_float64_v16_t value);

#else // __OPENCL_C_VERSION__

// Unsigned integer (8-bit)
#  define port_memory_write_local_uint8              port_memory_write_uint8
#  define port_memory_write_global_uint8             port_memory_write_uint8

// 2-vector of unsigned integers (8-bit)
#  define port_memory_write_local_uint8_v2           port_memory_write_uint8_v2
#  define port_memory_write_global_uint8_v2          port_memory_write_uint8_v2

// 3-vector of unsigned integers (8-bit)
#  define port_memory_write_local_uint8_v3           port_memory_write_uint8_v3
#  define port_memory_write_global_uint8_v3          port_memory_write_uint8_v3

// 4-vector of unsigned integers (8-bit)
#  define port_memory_write_local_uint8_v4           port_memory_write_uint8_v4
#  define port_memory_write_global_uint8_v4          port_memory_write_uint8_v4

// 8-vector of unsigned integers (8-bit)
#  define port_memory_write_local_uint8_v8           port_memory_write_uint8_v8
#  define port_memory_write_global_uint8_v8          port_memory_write_uint8_v8

// 16-vector of unsigned integers (8-bit)
#  define port_memory_write_local_uint8_v16          port_memory_write_uint8_v16
#  define port_memory_write_global_uint8_v16         port_memory_write_uint8_v16


// Unsigned integer (16-bit)
#  define port_memory_write_local_uint16             port_memory_write_uint16
#  define port_memory_write_global_uint16            port_memory_write_uint16

// 2-vector of unsigned integers (16-bit)
#  define port_memory_write_local_uint16_v2          port_memory_write_uint16_v2
#  define port_memory_write_global_uint16_v2         port_memory_write_uint16_v2

// 3-vector of unsigned integers (16-bit)
#  define port_memory_write_local_uint16_v3          port_memory_write_uint16_v3
#  define port_memory_write_global_uint16_v3         port_memory_write_uint16_v3

// 4-vector of unsigned integers (16-bit)
#  define port_memory_write_local_uint16_v4          port_memory_write_uint16_v4
#  define port_memory_write_global_uint16_v4         port_memory_write_uint16_v4

// 8-vector of unsigned integers (16-bit)
#  define port_memory_write_local_uint16_v8          port_memory_write_uint16_v8
#  define port_memory_write_global_uint16_v8         port_memory_write_uint16_v8

// 16-vector of unsigned integers (16-bit)
#  define port_memory_write_local_uint16_v16         port_memory_write_uint16_v16
#  define port_memory_write_global_uint16_v16        port_memory_write_uint16_v16


// Unsigned integer (32-bit)
#  define port_memory_write_local_uint32             port_memory_write_uint32
#  define port_memory_write_global_uint32            port_memory_write_uint32

// 2-vector of unsigned integers (32-bit)
#  define port_memory_write_local_uint32_v2          port_memory_write_uint32_v2
#  define port_memory_write_global_uint32_v2         port_memory_write_uint32_v2

// 3-vector of unsigned integers (32-bit)
#  define port_memory_write_local_uint32_v3          port_memory_write_uint32_v3
#  define port_memory_write_global_uint32_v3         port_memory_write_uint32_v3

// 4-vector of unsigned integers (32-bit)
#  define port_memory_write_local_uint32_v4          port_memory_write_uint32_v4
#  define port_memory_write_global_uint32_v4         port_memory_write_uint32_v4

// 8-vector of unsigned integers (32-bit)
#  define port_memory_write_local_uint32_v8          port_memory_write_uint32_v8
#  define port_memory_write_global_uint32_v8         port_memory_write_uint32_v8

// 16-vector of unsigned integers (32-bit)
#  define port_memory_write_local_uint32_v16         port_memory_write_uint32_v16
#  define port_memory_write_global_uint32_v16        port_memory_write_uint32_v16


// Unsigned integer (64-bit)
#  define port_memory_write_local_uint64             port_memory_write_uint64
#  define port_memory_write_global_uint64            port_memory_write_uint64

// 2-vector of unsigned integers (64-bit)
#  define port_memory_write_local_uint64_v2          port_memory_write_uint64_v2
#  define port_memory_write_global_uint64_v2         port_memory_write_uint64_v2

// 3-vector of unsigned integers (64-bit)
#  define port_memory_write_local_uint64_v3          port_memory_write_uint64_v3
#  define port_memory_write_global_uint64_v3         port_memory_write_uint64_v3

// 4-vector of unsigned integers (64-bit)
#  define port_memory_write_local_uint64_v4          port_memory_write_uint64_v4
#  define port_memory_write_global_uint64_v4         port_memory_write_uint64_v4

// 8-vector of unsigned integers (64-bit)
#  define port_memory_write_local_uint64_v8          port_memory_write_uint64_v8
#  define port_memory_write_global_uint64_v8         port_memory_write_uint64_v8

// 16-vector of unsigned integers (64-bit)
#  define port_memory_write_local_uint64_v16         port_memory_write_uint64_v16
#  define port_memory_write_global_uint64_v16        port_memory_write_uint64_v16


// Signed integer (8-bit)
#  define port_memory_write_local_sint8              port_memory_write_sint8
#  define port_memory_write_global_sint8             port_memory_write_sint8

// 2-vector of signed integers (8-bit)
#  define port_memory_write_local_sint8_v2           port_memory_write_sint8_v2
#  define port_memory_write_global_sint8_v2          port_memory_write_sint8_v2

// 3-vector of signed integers (8-bit)
#  define port_memory_write_local_sint8_v3           port_memory_write_sint8_v3
#  define port_memory_write_global_sint8_v3          port_memory_write_sint8_v3

// 4-vector of signed integers (8-bit)
#  define port_memory_write_local_sint8_v4           port_memory_write_sint8_v4
#  define port_memory_write_global_sint8_v4          port_memory_write_sint8_v4

// 8-vector of signed integers (8-bit)
#  define port_memory_write_local_sint8_v8           port_memory_write_sint8_v8
#  define port_memory_write_global_sint8_v8          port_memory_write_sint8_v8

// 16-vector of signed integers (8-bit)
#  define port_memory_write_local_sint8_v16          port_memory_write_sint8_v16
#  define port_memory_write_global_sint8_v16         port_memory_write_sint8_v16


// Signed integer (16-bit)
#  define port_memory_write_local_sint16             port_memory_write_sint16
#  define port_memory_write_global_sint16            port_memory_write_sint16

// 2-vector of signed integers (16-bit)
#  define port_memory_write_local_sint16_v2          port_memory_write_sint16_v2
#  define port_memory_write_global_sint16_v2         port_memory_write_sint16_v2

// 3-vector of signed integers (16-bit)
#  define port_memory_write_local_sint16_v3          port_memory_write_sint16_v3
#  define port_memory_write_global_sint16_v3         port_memory_write_sint16_v3

// 4-vector of signed integers (16-bit)
#  define port_memory_write_local_sint16_v4          port_memory_write_sint16_v4
#  define port_memory_write_global_sint16_v4         port_memory_write_sint16_v4

// 8-vector of signed integers (16-bit)
#  define port_memory_write_local_sint16_v8          port_memory_write_sint16_v8
#  define port_memory_write_global_sint16_v8         port_memory_write_sint16_v8

// 16-vector of signed integers (16-bit)
#  define port_memory_write_local_sint16_v16         port_memory_write_sint16_v16
#  define port_memory_write_global_sint16_v16        port_memory_write_sint16_v16


// Signed integer (32-bit)
#  define port_memory_write_local_sint32             port_memory_write_sint32
#  define port_memory_write_global_sint32            port_memory_write_sint32

// 2-vector of signed integers (32-bit)
#  define port_memory_write_local_sint32_v2          port_memory_write_sint32_v2
#  define port_memory_write_global_sint32_v2         port_memory_write_sint32_v2

// 3-vector of signed integers (32-bit)
#  define port_memory_write_local_sint32_v3          port_memory_write_sint32_v3
#  define port_memory_write_global_sint32_v3         port_memory_write_sint32_v3

// 4-vector of signed integers (32-bit)
#  define port_memory_write_local_sint32_v4          port_memory_write_sint32_v4
#  define port_memory_write_global_sint32_v4         port_memory_write_sint32_v4

// 8-vector of signed integers (32-bit)
#  define port_memory_write_local_sint32_v8          port_memory_write_sint32_v8
#  define port_memory_write_global_sint32_v8         port_memory_write_sint32_v8

// 16-vector of signed integers (32-bit)
#  define port_memory_write_local_sint32_v16         port_memory_write_sint32_v16
#  define port_memory_write_global_sint32_v16        port_memory_write_sint32_v16


// Signed integer (64-bit)
#  define port_memory_write_local_sint64             port_memory_write_sint64
#  define port_memory_write_global_sint64            port_memory_write_sint64

// 2-vector of signed integers (64-bit)
#  define port_memory_write_local_sint64_v2          port_memory_write_sint64_v2
#  define port_memory_write_global_sint64_v2         port_memory_write_sint64_v2

// 3-vector of signed integers (64-bit)
#  define port_memory_write_local_sint64_v3          port_memory_write_sint64_v3
#  define port_memory_write_global_sint64_v3         port_memory_write_sint64_v3

// 4-vector of signed integers (64-bit)
#  define port_memory_write_local_sint64_v4          port_memory_write_sint64_v4
#  define port_memory_write_global_sint64_v4         port_memory_write_sint64_v4

// 8-vector of signed integers (64-bit)
#  define port_memory_write_local_sint64_v8          port_memory_write_sint64_v8
#  define port_memory_write_global_sint64_v8         port_memory_write_sint64_v8

// 16-vector of signed integers (64-bit)
#  define port_memory_write_local_sint64_v16         port_memory_write_sint64_v16
#  define port_memory_write_global_sint64_v16        port_memory_write_sint64_v16


// Floating-point number (16-bit)
#  define port_memory_write_local_float16            port_memory_write_float16
#  define port_memory_write_global_float16           port_memory_write_float16

// 2-vector of floating-point numbers (16-bit)
#  define port_memory_write_local_float16_v2         port_memory_write_float16_v2
#  define port_memory_write_global_float16_v2        port_memory_write_float16_v2

// 3-vector of floating-point numbers (16-bit)
#  define port_memory_write_local_float16_v3         port_memory_write_float16_v3
#  define port_memory_write_global_float16_v3        port_memory_write_float16_v3

// 4-vector of floating-point numbers (16-bit)
#  define port_memory_write_local_float16_v4         port_memory_write_float16_v4
#  define port_memory_write_global_float16_v4        port_memory_write_float16_v4

// 8-vector of floating-point numbers (16-bit)
#  define port_memory_write_local_float16_v8         port_memory_write_float16_v8
#  define port_memory_write_global_float16_v8        port_memory_write_float16_v8

// 16-vector of floating-point numbers (16-bit)
#  define port_memory_write_local_float16_v16        port_memory_write_float16_v16
#  define port_memory_write_global_float16_v16       port_memory_write_float16_v16


// Floating-point number (32-bit)
#  define port_memory_write_local_float32            port_memory_write_float32
#  define port_memory_write_global_float32           port_memory_write_float32

// 2-vector of floating-point numbers (32-bit)
#  define port_memory_write_local_float32_v2         port_memory_write_float32_v2
#  define port_memory_write_global_float32_v2        port_memory_write_float32_v2

// 3-vector of floating-point numbers (32-bit)
#  define port_memory_write_local_float32_v3         port_memory_write_float32_v3
#  define port_memory_write_global_float32_v3        port_memory_write_float32_v3

// 4-vector of floating-point numbers (32-bit)
#  define port_memory_write_local_float32_v4         port_memory_write_float32_v4
#  define port_memory_write_global_float32_v4        port_memory_write_float32_v4

// 8-vector of floating-point numbers (32-bit)
#  define port_memory_write_local_float32_v8         port_memory_write_float32_v8
#  define port_memory_write_global_float32_v8        port_memory_write_float32_v8

// 16-vector of floating-point numbers (32-bit)
#  define port_memory_write_local_float32_v16        port_memory_write_float32_v16
#  define port_memory_write_global_float32_v16       port_memory_write_float32_v16


// Floating-point number (64-bit)
#  define port_memory_write_local_float64            port_memory_write_float64
#  define port_memory_write_global_float64           port_memory_write_float64

// 2-vector of floating-point numbers (64-bit)
#  define port_memory_write_local_float64_v2         port_memory_write_float64_v2
#  define port_memory_write_global_float64_v2        port_memory_write_float64_v2

// 3-vector of floating-point numbers (64-bit)
#  define port_memory_write_local_float64_v3         port_memory_write_float64_v3
#  define port_memory_write_global_float64_v3        port_memory_write_float64_v3

// 4-vector of floating-point numbers (64-bit)
#  define port_memory_write_local_float64_v4         port_memory_write_float64_v4
#  define port_memory_write_global_float64_v4        port_memory_write_float64_v4

// 8-vector of floating-point numbers (64-bit)
#  define port_memory_write_local_float64_v8         port_memory_write_float64_v8
#  define port_memory_write_global_float64_v8        port_memory_write_float64_v8

// 16-vector of floating-point numbers (64-bit)
#  define port_memory_write_local_float64_v16        port_memory_write_float64_v16
#  define port_memory_write_global_float64_v16       port_memory_write_float64_v16

#endif // __OPENCL_C_VERSION__

///////////////////////////////////////////////////////////////////////////////
// Aliases for typedefs of built-in types
///////////////////////////////////////////////////////////////////////////////

// Unsigned integer (quarter size)
#define port_memory_write_uintq port_memory_write_uint8
#define port_memory_write_local_uintq port_memory_write_local_uint8
#define port_memory_write_global_uintq port_memory_write_global_uint8

// 2-vector of unsigned integers (quarter size)
#define port_memory_write_uintq_v2 port_memory_write_uint8_v2
#define port_memory_write_local_uintq_v2 port_memory_write_local_uint8_v2
#define port_memory_write_global_uintq_v2 port_memory_write_global_uint8_v2

// 3-vector of unsigned integers (quarter size)
#define port_memory_write_uintq_v3 port_memory_write_uint8_v3
#define port_memory_write_local_uintq_v3 port_memory_write_local_uint8_v3
#define port_memory_write_global_uintq_v3 port_memory_write_global_uint8_v3

// 4-vector of unsigned integers (quarter size)
#define port_memory_write_uintq_v4 port_memory_write_uint8_v4
#define port_memory_write_local_uintq_v4 port_memory_write_local_uint8_v4
#define port_memory_write_global_uintq_v4 port_memory_write_global_uint8_v4

// 8-vector of unsigned integers (quarter size)
#define port_memory_write_uintq_v8 port_memory_write_uint8_v8
#define port_memory_write_local_uintq_v8 port_memory_write_local_uint8_v8
#define port_memory_write_global_uintq_v8 port_memory_write_global_uint8_v8

// 16-vector of unsigned integers (quarter size)
#define port_memory_write_uintq_v16 port_memory_write_uint8_v16
#define port_memory_write_local_uintq_v16 port_memory_write_local_uint8_v16
#define port_memory_write_global_uintq_v16 port_memory_write_global_uint8_v16


// Unsigned integer (half size)
#define port_memory_write_uinth port_memory_write_uint16
#define port_memory_write_local_uinth port_memory_write_local_uint16
#define port_memory_write_global_uinth port_memory_write_global_uint16

// 2-vector of unsigned integers (half size)
#define port_memory_write_uinth_v2 port_memory_write_uint16_v2
#define port_memory_write_local_uinth_v2 port_memory_write_local_uint16_v2
#define port_memory_write_global_uinth_v2 port_memory_write_global_uint16_v2

// 3-vector of unsigned integers (half size)
#define port_memory_write_uinth_v3 port_memory_write_uint16_v3
#define port_memory_write_local_uinth_v3 port_memory_write_local_uint16_v3
#define port_memory_write_global_uinth_v3 port_memory_write_global_uint16_v3

// 4-vector of unsigned integers (half size)
#define port_memory_write_uinth_v4 port_memory_write_uint16_v4
#define port_memory_write_local_uinth_v4 port_memory_write_local_uint16_v4
#define port_memory_write_global_uinth_v4 port_memory_write_global_uint16_v4

// 8-vector of unsigned integers (half size)
#define port_memory_write_uinth_v8 port_memory_write_uint16_v8
#define port_memory_write_local_uinth_v8 port_memory_write_local_uint16_v8
#define port_memory_write_global_uinth_v8 port_memory_write_global_uint16_v8

// 16-vector of unsigned integers (half size)
#define port_memory_write_uinth_v16 port_memory_write_uint16_v16
#define port_memory_write_local_uinth_v16 port_memory_write_local_uint16_v16
#define port_memory_write_global_uinth_v16 port_memory_write_global_uint16_v16


// Unsigned integer (single size)
#define port_memory_write_uints port_memory_write_uint32
#define port_memory_write_local_uints port_memory_write_local_uint32
#define port_memory_write_global_uints port_memory_write_global_uint32

// 2-vector of unsigned integers (single size)
#define port_memory_write_uints_v2 port_memory_write_uint32_v2
#define port_memory_write_local_uints_v2 port_memory_write_local_uint32_v2
#define port_memory_write_global_uints_v2 port_memory_write_global_uint32_v2

// 3-vector of unsigned integers (single size)
#define port_memory_write_uints_v3 port_memory_write_uint32_v3
#define port_memory_write_local_uints_v3 port_memory_write_local_uint32_v3
#define port_memory_write_global_uints_v3 port_memory_write_global_uint32_v3

// 4-vector of unsigned integers (single size)
#define port_memory_write_uints_v4 port_memory_write_uint32_v4
#define port_memory_write_local_uints_v4 port_memory_write_local_uint32_v4
#define port_memory_write_global_uints_v4 port_memory_write_global_uint32_v4

// 8-vector of unsigned integers (single size)
#define port_memory_write_uints_v8 port_memory_write_uint32_v8
#define port_memory_write_local_uints_v8 port_memory_write_local_uint32_v8
#define port_memory_write_global_uints_v8 port_memory_write_global_uint32_v8

// 16-vector of unsigned integers (single size)
#define port_memory_write_uints_v16 port_memory_write_uint32_v16
#define port_memory_write_local_uints_v16 port_memory_write_local_uint32_v16
#define port_memory_write_global_uints_v16 port_memory_write_global_uint32_v16


// Unsigned integer (double size)
#define port_memory_write_uintd port_memory_write_uint64
#define port_memory_write_local_uintd port_memory_write_local_uint64
#define port_memory_write_global_uintd port_memory_write_global_uint64

// 2-vector of unsigned integers (double size)
#define port_memory_write_uintd_v2 port_memory_write_uint64_v2
#define port_memory_write_local_uintd_v2 port_memory_write_local_uint64_v2
#define port_memory_write_global_uintd_v2 port_memory_write_global_uint64_v2

// 3-vector of unsigned integers (double size)
#define port_memory_write_uintd_v3 port_memory_write_uint64_v3
#define port_memory_write_local_uintd_v3 port_memory_write_local_uint64_v3
#define port_memory_write_global_uintd_v3 port_memory_write_global_uint64_v3

// 4-vector of unsigned integers (double size)
#define port_memory_write_uintd_v4 port_memory_write_uint64_v4
#define port_memory_write_local_uintd_v4 port_memory_write_local_uint64_v4
#define port_memory_write_global_uintd_v4 port_memory_write_global_uint64_v4

// 8-vector of unsigned integers (double size)
#define port_memory_write_uintd_v8 port_memory_write_uint64_v8
#define port_memory_write_local_uintd_v8 port_memory_write_local_uint64_v8
#define port_memory_write_global_uintd_v8 port_memory_write_global_uint64_v8

// 16-vector of unsigned integers (double size)
#define port_memory_write_uintd_v16 port_memory_write_uint64_v16
#define port_memory_write_local_uintd_v16 port_memory_write_local_uint64_v16
#define port_memory_write_global_uintd_v16 port_memory_write_global_uint64_v16


// Signed integer (quarter size)
#define port_memory_write_sintq port_memory_write_sint8
#define port_memory_write_local_sintq port_memory_write_local_sint8
#define port_memory_write_global_sintq port_memory_write_global_sint8

// 2-vector of signed integers (quarter size)
#define port_memory_write_sintq_v2 port_memory_write_sint8_v2
#define port_memory_write_local_sintq_v2 port_memory_write_local_sint8_v2
#define port_memory_write_global_sintq_v2 port_memory_write_global_sint8_v2

// 3-vector of signed integers (quarter size)
#define port_memory_write_sintq_v3 port_memory_write_sint8_v3
#define port_memory_write_local_sintq_v3 port_memory_write_local_sint8_v3
#define port_memory_write_global_sintq_v3 port_memory_write_global_sint8_v3

// 4-vector of signed integers (quarter size)
#define port_memory_write_sintq_v4 port_memory_write_sint8_v4
#define port_memory_write_local_sintq_v4 port_memory_write_local_sint8_v4
#define port_memory_write_global_sintq_v4 port_memory_write_global_sint8_v4

// 8-vector of signed integers (quarter size)
#define port_memory_write_sintq_v8 port_memory_write_sint8_v8
#define port_memory_write_local_sintq_v8 port_memory_write_local_sint8_v8
#define port_memory_write_global_sintq_v8 port_memory_write_global_sint8_v8

// 16-vector of signed integers (quarter size)
#define port_memory_write_sintq_v16 port_memory_write_sint8_v16
#define port_memory_write_local_sintq_v16 port_memory_write_local_sint8_v16
#define port_memory_write_global_sintq_v16 port_memory_write_global_sint8_v16


// Signed integer (half size)
#define port_memory_write_sinth port_memory_write_sint16
#define port_memory_write_local_sinth port_memory_write_local_sint16
#define port_memory_write_global_sinth port_memory_write_global_sint16

// 2-vector of signed integers (half size)
#define port_memory_write_sinth_v2 port_memory_write_sint16_v2
#define port_memory_write_local_sinth_v2 port_memory_write_local_sint16_v2
#define port_memory_write_global_sinth_v2 port_memory_write_global_sint16_v2

// 3-vector of signed integers (half size)
#define port_memory_write_sinth_v3 port_memory_write_sint16_v3
#define port_memory_write_local_sinth_v3 port_memory_write_local_sint16_v3
#define port_memory_write_global_sinth_v3 port_memory_write_global_sint16_v3

// 4-vector of signed integers (half size)
#define port_memory_write_sinth_v4 port_memory_write_sint16_v4
#define port_memory_write_local_sinth_v4 port_memory_write_local_sint16_v4
#define port_memory_write_global_sinth_v4 port_memory_write_global_sint16_v4

// 8-vector of signed integers (half size)
#define port_memory_write_sinth_v8 port_memory_write_sint16_v8
#define port_memory_write_local_sinth_v8 port_memory_write_local_sint16_v8
#define port_memory_write_global_sinth_v8 port_memory_write_global_sint16_v8

// 16-vector of signed integers (half size)
#define port_memory_write_sinth_v16 port_memory_write_sint16_v16
#define port_memory_write_local_sinth_v16 port_memory_write_local_sint16_v16
#define port_memory_write_global_sinth_v16 port_memory_write_global_sint16_v16


// Signed integer (single size)
#define port_memory_write_sints port_memory_write_sint32
#define port_memory_write_local_sints port_memory_write_local_sint32
#define port_memory_write_global_sints port_memory_write_global_sint32

// 2-vector of signed integers (single size)
#define port_memory_write_sints_v2 port_memory_write_sint32_v2
#define port_memory_write_local_sints_v2 port_memory_write_local_sint32_v2
#define port_memory_write_global_sints_v2 port_memory_write_global_sint32_v2

// 3-vector of signed integers (single size)
#define port_memory_write_sints_v3 port_memory_write_sint32_v3
#define port_memory_write_local_sints_v3 port_memory_write_local_sint32_v3
#define port_memory_write_global_sints_v3 port_memory_write_global_sint32_v3

// 4-vector of signed integers (single size)
#define port_memory_write_sints_v4 port_memory_write_sint32_v4
#define port_memory_write_local_sints_v4 port_memory_write_local_sint32_v4
#define port_memory_write_global_sints_v4 port_memory_write_global_sint32_v4

// 8-vector of signed integers (single size)
#define port_memory_write_sints_v8 port_memory_write_sint32_v8
#define port_memory_write_local_sints_v8 port_memory_write_local_sint32_v8
#define port_memory_write_global_sints_v8 port_memory_write_global_sint32_v8

// 16-vector of signed integers (single size)
#define port_memory_write_sints_v16 port_memory_write_sint32_v16
#define port_memory_write_local_sints_v16 port_memory_write_local_sint32_v16
#define port_memory_write_global_sints_v16 port_memory_write_global_sint32_v16


// Signed integer (double size)
#define port_memory_write_sintd port_memory_write_sint64
#define port_memory_write_local_sintd port_memory_write_local_sint64
#define port_memory_write_global_sintd port_memory_write_global_sint64

// 2-vector of signed integers (double size)
#define port_memory_write_sintd_v2 port_memory_write_sint64_v2
#define port_memory_write_local_sintd_v2 port_memory_write_local_sint64_v2
#define port_memory_write_global_sintd_v2 port_memory_write_global_sint64_v2

// 3-vector of signed integers (double size)
#define port_memory_write_sintd_v3 port_memory_write_sint64_v3
#define port_memory_write_local_sintd_v3 port_memory_write_local_sint64_v3
#define port_memory_write_global_sintd_v3 port_memory_write_global_sint64_v3

// 4-vector of signed integers (double size)
#define port_memory_write_sintd_v4 port_memory_write_sint64_v4
#define port_memory_write_local_sintd_v4 port_memory_write_local_sint64_v4
#define port_memory_write_global_sintd_v4 port_memory_write_global_sint64_v4

// 8-vector of signed integers (double size)
#define port_memory_write_sintd_v8 port_memory_write_sint64_v8
#define port_memory_write_local_sintd_v8 port_memory_write_local_sint64_v8
#define port_memory_write_global_sintd_v8 port_memory_write_global_sint64_v8

// 16-vector of signed integers (double size)
#define port_memory_write_sintd_v16 port_memory_write_sint64_v16
#define port_memory_write_local_sintd_v16 port_memory_write_local_sint64_v16
#define port_memory_write_global_sintd_v16 port_memory_write_global_sint64_v16


// Floating-point number (half size)
#define port_memory_write_floath port_memory_write_float16
#define port_memory_write_local_floath port_memory_write_local_float16
#define port_memory_write_global_floath port_memory_write_global_float16

// 2-vector of floating-point numbers (half size)
#define port_memory_write_floath_v2 port_memory_write_float16_v2
#define port_memory_write_local_floath_v2 port_memory_write_local_float16_v2
#define port_memory_write_global_floath_v2 port_memory_write_global_float16_v2

// 3-vector of floating-point numbers (half size)
#define port_memory_write_floath_v3 port_memory_write_float16_v3
#define port_memory_write_local_floath_v3 port_memory_write_local_float16_v3
#define port_memory_write_global_floath_v3 port_memory_write_global_float16_v3

// 4-vector of floating-point numbers (half size)
#define port_memory_write_floath_v4 port_memory_write_float16_v4
#define port_memory_write_local_floath_v4 port_memory_write_local_float16_v4
#define port_memory_write_global_floath_v4 port_memory_write_global_float16_v4

// 8-vector of floating-point numbers (half size)
#define port_memory_write_floath_v8 port_memory_write_float16_v8
#define port_memory_write_local_floath_v8 port_memory_write_local_float16_v8
#define port_memory_write_global_floath_v8 port_memory_write_global_float16_v8

// 16-vector of floating-point numbers (half size)
#define port_memory_write_floath_v16 port_memory_write_float16_v16
#define port_memory_write_local_floath_v16 port_memory_write_local_float16_v16
#define port_memory_write_global_floath_v16 port_memory_write_global_float16_v16


// Floating-point number (single size)
#define port_memory_write_floats port_memory_write_float32
#define port_memory_write_local_floats port_memory_write_local_float32
#define port_memory_write_global_floats port_memory_write_global_float32

// 2-vector of floating-point numbers (single size)
#define port_memory_write_floats_v2 port_memory_write_float32_v2
#define port_memory_write_local_floats_v2 port_memory_write_local_float32_v2
#define port_memory_write_global_floats_v2 port_memory_write_global_float32_v2

// 3-vector of floating-point numbers (single size)
#define port_memory_write_floats_v3 port_memory_write_float32_v3
#define port_memory_write_local_floats_v3 port_memory_write_local_float32_v3
#define port_memory_write_global_floats_v3 port_memory_write_global_float32_v3

// 4-vector of floating-point numbers (single size)
#define port_memory_write_floats_v4 port_memory_write_float32_v4
#define port_memory_write_local_floats_v4 port_memory_write_local_float32_v4
#define port_memory_write_global_floats_v4 port_memory_write_global_float32_v4

// 8-vector of floating-point numbers (single size)
#define port_memory_write_floats_v8 port_memory_write_float32_v8
#define port_memory_write_local_floats_v8 port_memory_write_local_float32_v8
#define port_memory_write_global_floats_v8 port_memory_write_global_float32_v8

// 16-vector of floating-point numbers (single size)
#define port_memory_write_floats_v16 port_memory_write_float32_v16
#define port_memory_write_local_floats_v16 port_memory_write_local_float32_v16
#define port_memory_write_global_floats_v16 port_memory_write_global_float32_v16


// Floating-point number (double size)
#define port_memory_write_floatd port_memory_write_float64
#define port_memory_write_local_floatd port_memory_write_local_float64
#define port_memory_write_global_floatd port_memory_write_global_float64

// 2-vector of floating-point numbers (double size)
#define port_memory_write_floatd_v2 port_memory_write_float64_v2
#define port_memory_write_local_floatd_v2 port_memory_write_local_float64_v2
#define port_memory_write_global_floatd_v2 port_memory_write_global_float64_v2

// 3-vector of floating-point numbers (double size)
#define port_memory_write_floatd_v3 port_memory_write_float64_v3
#define port_memory_write_local_floatd_v3 port_memory_write_local_float64_v3
#define port_memory_write_global_floatd_v3 port_memory_write_global_float64_v3

// 4-vector of floating-point numbers (double size)
#define port_memory_write_floatd_v4 port_memory_write_float64_v4
#define port_memory_write_local_floatd_v4 port_memory_write_local_float64_v4
#define port_memory_write_global_floatd_v4 port_memory_write_global_float64_v4

// 8-vector of floating-point numbers (double size)
#define port_memory_write_floatd_v8 port_memory_write_float64_v8
#define port_memory_write_local_floatd_v8 port_memory_write_local_float64_v8
#define port_memory_write_global_floatd_v8 port_memory_write_global_float64_v8

// 16-vector of floating-point numbers (double size)
#define port_memory_write_floatd_v16 port_memory_write_float64_v16
#define port_memory_write_local_floatd_v16 port_memory_write_local_float64_v16
#define port_memory_write_global_floatd_v16 port_memory_write_global_float64_v16

///////////////////////////////////////////////////////////////////////////////
// Aliases for other types
///////////////////////////////////////////////////////////////////////////////

// Memory references
#define port_memory_write_memory_ref port_memory_write_sints
#define port_memory_write_local_memory_ref port_memory_write_local_sints
#define port_memory_write_global_memory_ref port_memory_write_global_sints

#define port_memory_write_memory_refh port_memory_write_sinth
#define port_memory_write_local_memory_refh port_memory_write_local_sinth
#define port_memory_write_global_memory_refh port_memory_write_global_sinth

#define port_memory_write_memory_refq port_memory_write_sintq
#define port_memory_write_local_memory_refq port_memory_write_local_sintq
#define port_memory_write_global_memory_refq port_memory_write_global_sintq

#endif // _PORT_MEMORY_WRITE_FUN_H_

