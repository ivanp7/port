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
 * @brief Macros for built-in scalar type conversions.
 */

#pragma once
#ifndef _PORT_CDEV_CONVERT_DEF_H_
#define _PORT_CDEV_CONVERT_DEF_H_

#ifndef __OPENCL_C_VERSION__
#  include <port/cdev/vector.def.h>
#endif

///////////////////////////////////////////////////////////////////////////////
// Absolute types
///////////////////////////////////////////////////////////////////////////////

#ifdef __OPENCL_C_VERSION__

#define PORT_CONVERT_TO_UINT8(value) convert_uchar(value) ///< Convert value to unsigned 8-bit integer.
#define PORT_CONVERT_TO_SINT8(value) convert_char(value) ///< Convert value to signed 8-bit integer.
#define PORT_CONVERT_TO_UINT16(value) convert_ushort(value) ///< Convert value to unsigned 16-bit integer.
#define PORT_CONVERT_TO_SINT16(value) convert_short(value) ///< Convert value to signed 16-bit integer.
#define PORT_CONVERT_TO_UINT32(value) convert_uint(value) ///< Convert value to unsigned 32-bit integer.
#define PORT_CONVERT_TO_SINT32(value) convert_int(value) ///< Convert value to signed 32-bit integer.
#define PORT_CONVERT_TO_UINT64(value) convert_ulong(value) ///< Convert value to unsigned 64-bit integer.
#define PORT_CONVERT_TO_SINT64(value) convert_long(value) ///< Convert value to signed 64-bit integer.
#define PORT_CONVERT_TO_FLOAT32(value) convert_float(value) ///< Convert value to 32-bit floating-point number.
#define PORT_CONVERT_TO_FLOAT64(value) convert_double(value) ///< Convert value to 64-bit floating-point number.

/**
 * @brief Convert value to 2-vector of unsigned 8-bit integers.
 */
#define PORT_CONVERT_TO_UINT8_V2(r, value) do { (r).xy = convert_uchar2((value).xy); } while(0)
/**
 * @brief Convert value to 2-vector of signed 8-bit integers.
 */
#define PORT_CONVERT_TO_SINT8_V2(r, value) do { (r).xy = convert_char2((value).xy); } while(0)
/**
 * @brief Convert value to 2-vector of unsigned 16-bit integers.
 */
#define PORT_CONVERT_TO_UINT16_V2(r, value) do { (r).xy = convert_ushort2((value).xy); } while(0)
/**
 * @brief Convert value to 2-vector of signed 16-bit integers.
 */
#define PORT_CONVERT_TO_SINT16_V2(r, value) do { (r).xy = convert_short2((value).xy); } while(0)
/**
 * @brief Convert value to 2-vector of unsigned 32-bit integers.
 */
#define PORT_CONVERT_TO_UINT32_V2(r, value) do { (r).xy = convert_uint2((value).xy); } while(0)
/**
 * @brief Convert value to 2-vector of signed 32-bit integers.
 */
#define PORT_CONVERT_TO_SINT32_V2(r, value) do { (r).xy = convert_int2((value).xy); } while(0)
/**
 * @brief Convert value to 2-vector of unsigned 64-bit integers.
 */
#define PORT_CONVERT_TO_UINT64_V2(r, value) do { (r).xy = convert_ulong2((value).xy); } while(0)
/**
 * @brief Convert value to 2-vector of signed 64-bit integers.
 */
#define PORT_CONVERT_TO_SINT64_V2(r, value) do { (r).xy = convert_long2((value).xy); } while(0)
/**
 * @brief Convert value to 2-vector of 32-bit floating-point numbers.
 */
#define PORT_CONVERT_TO_FLOAT32_V2(r, value) do { (r).xy = convert_float2((value).xy); } while(0)
/**
 * @brief Convert value to 2-vector of 64-bit floating-point numbers.
 */
#define PORT_CONVERT_TO_FLOAT64_V2(r, value) do { (r).xy = convert_double2((value).xy); } while(0)

/**
 * @brief Convert value to 3-vector of unsigned 8-bit integers.
 */
#define PORT_CONVERT_TO_UINT8_V3(r, value) do { (r).xyz = convert_uchar3((value).xyz); } while(0)
/**
 * @brief Convert value to 3-vector of signed 8-bit integers.
 */
#define PORT_CONVERT_TO_SINT8_V3(r, value) do { (r).xyz = convert_char3((value).xyz); } while(0)
/**
 * @brief Convert value to 3-vector of unsigned 16-bit integers.
 */
#define PORT_CONVERT_TO_UINT16_V3(r, value) do { (r).xyz = convert_ushort3((value).xyz); } while(0)
/**
 * @brief Convert value to 3-vector of signed 16-bit integers.
 */
#define PORT_CONVERT_TO_SINT16_V3(r, value) do { (r).xyz = convert_short3((value).xyz); } while(0)
/**
 * @brief Convert value to 3-vector of unsigned 32-bit integers.
 */
#define PORT_CONVERT_TO_UINT32_V3(r, value) do { (r).xyz = convert_uint3((value).xyz); } while(0)
/**
 * @brief Convert value to 3-vector of signed 32-bit integers.
 */
#define PORT_CONVERT_TO_SINT32_V3(r, value) do { (r).xyz = convert_int3((value).xyz); } while(0)
/**
 * @brief Convert value to 3-vector of unsigned 64-bit integers.
 */
#define PORT_CONVERT_TO_UINT64_V3(r, value) do { (r).xyz = convert_ulong3((value).xyz); } while(0)
/**
 * @brief Convert value to 3-vector of signed 64-bit integers.
 */
#define PORT_CONVERT_TO_SINT64_V3(r, value) do { (r).xyz = convert_long3((value).xyz); } while(0)
/**
 * @brief Convert value to 3-vector of 32-bit floating-point numbers.
 */
#define PORT_CONVERT_TO_FLOAT32_V3(r, value) do { (r).xyz = convert_float3((value).xyz); } while(0)
/**
 * @brief Convert value to 3-vector of 64-bit floating-point numbers.
 */
#define PORT_CONVERT_TO_FLOAT64_V3(r, value) do { (r).xyz = convert_double3((value).xyz); } while(0)

/**
 * @brief Convert value to 4-vector of unsigned 8-bit integers.
 */
#define PORT_CONVERT_TO_UINT8_V4(r, value) do { (r).xyzw = convert_uchar4((value).xyzw); } while(0)
/**
 * @brief Convert value to 4-vector of signed 8-bit integers.
 */
#define PORT_CONVERT_TO_SINT8_V4(r, value) do { (r).xyzw = convert_char4((value).xyzw); } while(0)
/**
 * @brief Convert value to 4-vector of unsigned 16-bit integers.
 */
#define PORT_CONVERT_TO_UINT16_V4(r, value) do { (r).xyzw = convert_ushort4((value).xyzw); } while(0)
/**
 * @brief Convert value to 4-vector of signed 16-bit integers.
 */
#define PORT_CONVERT_TO_SINT16_V4(r, value) do { (r).xyzw = convert_short4((value).xyzw); } while(0)
/**
 * @brief Convert value to 4-vector of unsigned 32-bit integers.
 */
#define PORT_CONVERT_TO_UINT32_V4(r, value) do { (r).xyzw = convert_uint4((value).xyzw); } while(0)
/**
 * @brief Convert value to 4-vector of signed 32-bit integers.
 */
#define PORT_CONVERT_TO_SINT32_V4(r, value) do { (r).xyzw = convert_int4((value).xyzw); } while(0)
/**
 * @brief Convert value to 4-vector of unsigned 64-bit integers.
 */
#define PORT_CONVERT_TO_UINT64_V4(r, value) do { (r).xyzw = convert_ulong4((value).xyzw); } while(0)
/**
 * @brief Convert value to 4-vector of signed 64-bit integers.
 */
#define PORT_CONVERT_TO_SINT64_V4(r, value) do { (r).xyzw = convert_long4((value).xyzw); } while(0)
/**
 * @brief Convert value to 4-vector of 32-bit floating-point numbers.
 */
#define PORT_CONVERT_TO_FLOAT32_V4(r, value) do { (r).xyzw = convert_float4((value).xyzw); } while(0)
/**
 * @brief Convert value to 4-vector of 64-bit floating-point numbers.
 */
#define PORT_CONVERT_TO_FLOAT64_V4(r, value) do { (r).xyzw = convert_double4((value).xyzw); } while(0)

/**
 * @brief Convert value to 8-vector of unsigned 8-bit integers.
 */
#define PORT_CONVERT_TO_UINT8_V8(r, value) do { (r).s01234567 = convert_uchar8((value).s01234567); } while(0)
/**
 * @brief Convert value to 8-vector of signed 8-bit integers.
 */
#define PORT_CONVERT_TO_SINT8_V8(r, value) do { (r).s01234567 = convert_char8((value).s01234567); } while(0)
/**
 * @brief Convert value to 8-vector of unsigned 16-bit integers.
 */
#define PORT_CONVERT_TO_UINT16_V8(r, value) do { (r).s01234567 = convert_ushort8((value).s01234567); } while(0)
/**
 * @brief Convert value to 8-vector of signed 16-bit integers.
 */
#define PORT_CONVERT_TO_SINT16_V8(r, value) do { (r).s01234567 = convert_short8((value).s01234567); } while(0)
/**
 * @brief Convert value to 8-vector of unsigned 32-bit integers.
 */
#define PORT_CONVERT_TO_UINT32_V8(r, value) do { (r).s01234567 = convert_uint8((value).s01234567); } while(0)
/**
 * @brief Convert value to 8-vector of signed 32-bit integers.
 */
#define PORT_CONVERT_TO_SINT32_V8(r, value) do { (r).s01234567 = convert_int8((value).s01234567); } while(0)
/**
 * @brief Convert value to 8-vector of unsigned 64-bit integers.
 */
#define PORT_CONVERT_TO_UINT64_V8(r, value) do { (r).s01234567 = convert_ulong8((value).s01234567); } while(0)
/**
 * @brief Convert value to 8-vector of signed 64-bit integers.
 */
#define PORT_CONVERT_TO_SINT64_V8(r, value) do { (r).s01234567 = convert_long8((value).s01234567); } while(0)
/**
 * @brief Convert value to 8-vector of 32-bit floating-point numbers.
 */
#define PORT_CONVERT_TO_FLOAT32_V8(r, value) do { (r).s01234567 = convert_float8((value).s01234567); } while(0)
/**
 * @brief Convert value to 8-vector of 64-bit floating-point numbers.
 */
#define PORT_CONVERT_TO_FLOAT64_V8(r, value) do { (r).s01234567 = convert_double8((value).s01234567); } while(0)

/**
 * @brief Convert value to 16-vector of unsigned 8-bit integers.
 */
#define PORT_CONVERT_TO_UINT8_V16(r, value) do { (r).s0123456789ABCDEF = convert_uchar16((value).s0123456789ABCDEF); } while(0)
/**
 * @brief Convert value to 16-vector of signed 8-bit integers.
 */
#define PORT_CONVERT_TO_SINT8_V16(r, value) do { (r).s0123456789ABCDEF = convert_char16((value).s0123456789ABCDEF); } while(0)
/**
 * @brief Convert value to 16-vector of unsigned 16-bit integers.
 */
#define PORT_CONVERT_TO_UINT16_V16(r, value) do { (r).s0123456789ABCDEF = convert_ushort16((value).s0123456789ABCDEF); } while(0)
/**
 * @brief Convert value to 16-vector of signed 16-bit integers.
 */
#define PORT_CONVERT_TO_SINT16_V16(r, value) do { (r).s0123456789ABCDEF = convert_short16((value).s0123456789ABCDEF); } while(0)
/**
 * @brief Convert value to 16-vector of unsigned 32-bit integers.
 */
#define PORT_CONVERT_TO_UINT32_V16(r, value) do { (r).s0123456789ABCDEF = convert_uint16((value).s0123456789ABCDEF); } while(0)
/**
 * @brief Convert value to 16-vector of signed 32-bit integers.
 */
#define PORT_CONVERT_TO_SINT32_V16(r, value) do { (r).s0123456789ABCDEF = convert_int16((value).s0123456789ABCDEF); } while(0)
/**
 * @brief Convert value to 16-vector of unsigned 64-bit integers.
 */
#define PORT_CONVERT_TO_UINT64_V16(r, value) do { (r).s0123456789ABCDEF = convert_ulong16((value).s0123456789ABCDEF); } while(0)
/**
 * @brief Convert value to 16-vector of signed 64-bit integers.
 */
#define PORT_CONVERT_TO_SINT64_V16(r, value) do { (r).s0123456789ABCDEF = convert_long16((value).s0123456789ABCDEF); } while(0)
/**
 * @brief Convert value to 16-vector of 32-bit floating-point numbers.
 */
#define PORT_CONVERT_TO_FLOAT32_V16(r, value) do { (r).s0123456789ABCDEF = convert_float16((value).s0123456789ABCDEF); } while(0)
/**
 * @brief Convert value to 16-vector of 64-bit floating-point numbers.
 */
#define PORT_CONVERT_TO_FLOAT64_V16(r, value) do { (r).s0123456789ABCDEF = convert_double16((value).s0123456789ABCDEF); } while(0)

#else // __OPENCL_C_VERSION__

#define PORT_CONVERT_TO_UINT8(value) ((port_uint8_t)(value)) ///< Convert value to unsigned 8-bit integer.
#define PORT_CONVERT_TO_SINT8(value) ((port_sint8_t)(value)) ///< Convert value to signed 8-bit integer.
#define PORT_CONVERT_TO_UINT16(value) ((port_uint16_t)(value)) ///< Convert value to unsigned 16-bit integer.
#define PORT_CONVERT_TO_SINT16(value) ((port_sint16_t)(value)) ///< Convert value to signed 16-bit integer.
#define PORT_CONVERT_TO_UINT32(value) ((port_uint32_t)(value)) ///< Convert value to unsigned 32-bit integer.
#define PORT_CONVERT_TO_SINT32(value) ((port_sint32_t)(value)) ///< Convert value to signed 32-bit integer.
#define PORT_CONVERT_TO_UINT64(value) ((port_uint64_t)(value)) ///< Convert value to unsigned 64-bit integer.
#define PORT_CONVERT_TO_SINT64(value) ((port_sint64_t)(value)) ///< Convert value to signed 64-bit integer.
#define PORT_CONVERT_TO_FLOAT32(value) ((port_float32_t)(value)) ///< Convert value to 32-bit floating-point number.
#define PORT_CONVERT_TO_FLOAT64(value) ((port_float64_t)(value)) ///< Convert value to 64-bit floating-point number.

/**
 * @brief Convert value to 2-vector of unsigned 8-bit integers.
 */
#define PORT_CONVERT_TO_UINT8_V2(r, value) PORT_V2_OP1(r, (port_uint8_t), value)
/**
 * @brief Convert value to 2-vector of signed 8-bit integers.
 */
#define PORT_CONVERT_TO_SINT8_V2(r, value) PORT_V2_OP1(r, (port_sint8_t), value)
/**
 * @brief Convert value to 2-vector of unsigned 16-bit integers.
 */
#define PORT_CONVERT_TO_UINT16_V2(r, value) PORT_V2_OP1(r, (port_uint16_t), value)
/**
 * @brief Convert value to 2-vector of signed 16-bit integers.
 */
#define PORT_CONVERT_TO_SINT16_V2(r, value) PORT_V2_OP1(r, (port_sint16_t), value)
/**
 * @brief Convert value to 2-vector of unsigned 32-bit integers.
 */
#define PORT_CONVERT_TO_UINT32_V2(r, value) PORT_V2_OP1(r, (port_uint32_t), value)
/**
 * @brief Convert value to 2-vector of signed 32-bit integers.
 */
#define PORT_CONVERT_TO_SINT32_V2(r, value) PORT_V2_OP1(r, (port_sint32_t), value)
/**
 * @brief Convert value to 2-vector of unsigned 64-bit integers.
 */
#define PORT_CONVERT_TO_UINT64_V2(r, value) PORT_V2_OP1(r, (port_uint64_t), value)
/**
 * @brief Convert value to 2-vector of signed 64-bit integers.
 */
#define PORT_CONVERT_TO_SINT64_V2(r, value) PORT_V2_OP1(r, (port_sint64_t), value)
/**
 * @brief Convert value to 2-vector of 32-bit floating-point numbers.
 */
#define PORT_CONVERT_TO_FLOAT32_V2(r, value) PORT_V2_OP1(r, (port_float32_t), value)
/**
 * @brief Convert value to 2-vector of 64-bit floating-point numbers.
 */
#define PORT_CONVERT_TO_FLOAT64_V2(r, value) PORT_V2_OP1(r, (port_float64_t), value)

/**
 * @brief Convert value to 3-vector of unsigned 8-bit integers.
 */
#define PORT_CONVERT_TO_UINT8_V3(r, value) PORT_V3_OP1(r, (port_uint8_t), value)
/**
 * @brief Convert value to 3-vector of signed 8-bit integers.
 */
#define PORT_CONVERT_TO_SINT8_V3(r, value) PORT_V3_OP1(r, (port_sint8_t), value)
/**
 * @brief Convert value to 3-vector of unsigned 16-bit integers.
 */
#define PORT_CONVERT_TO_UINT16_V3(r, value) PORT_V3_OP1(r, (port_uint16_t), value)
/**
 * @brief Convert value to 3-vector of signed 16-bit integers.
 */
#define PORT_CONVERT_TO_SINT16_V3(r, value) PORT_V3_OP1(r, (port_sint16_t), value)
/**
 * @brief Convert value to 3-vector of unsigned 32-bit integers.
 */
#define PORT_CONVERT_TO_UINT32_V3(r, value) PORT_V3_OP1(r, (port_uint32_t), value)
/**
 * @brief Convert value to 3-vector of signed 32-bit integers.
 */
#define PORT_CONVERT_TO_SINT32_V3(r, value) PORT_V3_OP1(r, (port_sint32_t), value)
/**
 * @brief Convert value to 3-vector of unsigned 64-bit integers.
 */
#define PORT_CONVERT_TO_UINT64_V3(r, value) PORT_V3_OP1(r, (port_uint64_t), value)
/**
 * @brief Convert value to 3-vector of signed 64-bit integers.
 */
#define PORT_CONVERT_TO_SINT64_V3(r, value) PORT_V3_OP1(r, (port_sint64_t), value)
/**
 * @brief Convert value to 3-vector of 32-bit floating-point numbers.
 */
#define PORT_CONVERT_TO_FLOAT32_V3(r, value) PORT_V3_OP1(r, (port_float32_t), value)
/**
 * @brief Convert value to 3-vector of 64-bit floating-point numbers.
 */
#define PORT_CONVERT_TO_FLOAT64_V3(r, value) PORT_V3_OP1(r, (port_float64_t), value)

/**
 * @brief Convert value to 4-vector of unsigned 8-bit integers.
 */
#define PORT_CONVERT_TO_UINT8_V4(r, value) PORT_V4_OP1(r, (port_uint8_t), value)
/**
 * @brief Convert value to 4-vector of signed 8-bit integers.
 */
#define PORT_CONVERT_TO_SINT8_V4(r, value) PORT_V4_OP1(r, (port_sint8_t), value)
/**
 * @brief Convert value to 4-vector of unsigned 16-bit integers.
 */
#define PORT_CONVERT_TO_UINT16_V4(r, value) PORT_V4_OP1(r, (port_uint16_t), value)
/**
 * @brief Convert value to 4-vector of signed 16-bit integers.
 */
#define PORT_CONVERT_TO_SINT16_V4(r, value) PORT_V4_OP1(r, (port_sint16_t), value)
/**
 * @brief Convert value to 4-vector of unsigned 32-bit integers.
 */
#define PORT_CONVERT_TO_UINT32_V4(r, value) PORT_V4_OP1(r, (port_uint32_t), value)
/**
 * @brief Convert value to 4-vector of signed 32-bit integers.
 */
#define PORT_CONVERT_TO_SINT32_V4(r, value) PORT_V4_OP1(r, (port_sint32_t), value)
/**
 * @brief Convert value to 4-vector of unsigned 64-bit integers.
 */
#define PORT_CONVERT_TO_UINT64_V4(r, value) PORT_V4_OP1(r, (port_uint64_t), value)
/**
 * @brief Convert value to 4-vector of signed 64-bit integers.
 */
#define PORT_CONVERT_TO_SINT64_V4(r, value) PORT_V4_OP1(r, (port_sint64_t), value)
/**
 * @brief Convert value to 4-vector of 32-bit floating-point numbers.
 */
#define PORT_CONVERT_TO_FLOAT32_V4(r, value) PORT_V4_OP1(r, (port_float32_t), value)
/**
 * @brief Convert value to 4-vector of 64-bit floating-point numbers.
 */
#define PORT_CONVERT_TO_FLOAT64_V4(r, value) PORT_V4_OP1(r, (port_float64_t), value)

/**
 * @brief Convert value to 8-vector of unsigned 8-bit integers.
 */
#define PORT_CONVERT_TO_UINT8_V8(r, value) PORT_V8_OP1(r, (port_uint8_t), value)
/**
 * @brief Convert value to 8-vector of signed 8-bit integers.
 */
#define PORT_CONVERT_TO_SINT8_V8(r, value) PORT_V8_OP1(r, (port_sint8_t), value)
/**
 * @brief Convert value to 8-vector of unsigned 16-bit integers.
 */
#define PORT_CONVERT_TO_UINT16_V8(r, value) PORT_V8_OP1(r, (port_uint16_t), value)
/**
 * @brief Convert value to 8-vector of signed 16-bit integers.
 */
#define PORT_CONVERT_TO_SINT16_V8(r, value) PORT_V8_OP1(r, (port_sint16_t), value)
/**
 * @brief Convert value to 8-vector of unsigned 32-bit integers.
 */
#define PORT_CONVERT_TO_UINT32_V8(r, value) PORT_V8_OP1(r, (port_uint32_t), value)
/**
 * @brief Convert value to 8-vector of signed 32-bit integers.
 */
#define PORT_CONVERT_TO_SINT32_V8(r, value) PORT_V8_OP1(r, (port_sint32_t), value)
/**
 * @brief Convert value to 8-vector of unsigned 64-bit integers.
 */
#define PORT_CONVERT_TO_UINT64_V8(r, value) PORT_V8_OP1(r, (port_uint64_t), value)
/**
 * @brief Convert value to 8-vector of signed 64-bit integers.
 */
#define PORT_CONVERT_TO_SINT64_V8(r, value) PORT_V8_OP1(r, (port_sint64_t), value)
/**
 * @brief Convert value to 8-vector of 32-bit floating-point numbers.
 */
#define PORT_CONVERT_TO_FLOAT32_V8(r, value) PORT_V8_OP1(r, (port_float32_t), value)
/**
 * @brief Convert value to 8-vector of 64-bit floating-point numbers.
 */
#define PORT_CONVERT_TO_FLOAT64_V8(r, value) PORT_V8_OP1(r, (port_float64_t), value)

/**
 * @brief Convert value to 16-vector of unsigned 8-bit integers.
 */
#define PORT_CONVERT_TO_UINT8_V16(r, value) PORT_V16_OP1(r, (port_uint8_t), value)
/**
 * @brief Convert value to 16-vector of signed 8-bit integers.
 */
#define PORT_CONVERT_TO_SINT8_V16(r, value) PORT_V16_OP1(r, (port_sint8_t), value)
/**
 * @brief Convert value to 16-vector of unsigned 16-bit integers.
 */
#define PORT_CONVERT_TO_UINT16_V16(r, value) PORT_V16_OP1(r, (port_uint16_t), value)
/**
 * @brief Convert value to 16-vector of signed 16-bit integers.
 */
#define PORT_CONVERT_TO_SINT16_V16(r, value) PORT_V16_OP1(r, (port_sint16_t), value)
/**
 * @brief Convert value to 16-vector of unsigned 32-bit integers.
 */
#define PORT_CONVERT_TO_UINT32_V16(r, value) PORT_V16_OP1(r, (port_uint32_t), value)
/**
 * @brief Convert value to 16-vector of signed 32-bit integers.
 */
#define PORT_CONVERT_TO_SINT32_V16(r, value) PORT_V16_OP1(r, (port_sint32_t), value)
/**
 * @brief Convert value to 16-vector of unsigned 64-bit integers.
 */
#define PORT_CONVERT_TO_UINT64_V16(r, value) PORT_V16_OP1(r, (port_uint64_t), value)
/**
 * @brief Convert value to 16-vector of signed 64-bit integers.
 */
#define PORT_CONVERT_TO_SINT64_V16(r, value) PORT_V16_OP1(r, (port_sint64_t), value)
/**
 * @brief Convert value to 16-vector of 32-bit floating-point numbers.
 */
#define PORT_CONVERT_TO_FLOAT32_V16(r, value) PORT_V16_OP1(r, (port_float32_t), value)
/**
 * @brief Convert value to 16-vector of 64-bit floating-point numbers.
 */
#define PORT_CONVERT_TO_FLOAT64_V16(r, value) PORT_V16_OP1(r, (port_float64_t), value)

#endif // __OPENCL_C_VERSION__

///////////////////////////////////////////////////////////////////////////////
// Relative types
///////////////////////////////////////////////////////////////////////////////

#define PORT_CONVERT_TO_UINT_QUARTER(value) PORT_CONVERT_TO_UINT8(value) ///< Convert value to unsigned integer (quarter size).
#define PORT_CONVERT_TO_UINT_QUARTER_V2(r, value) PORT_CONVERT_TO_UINT8_V2(r, value) ///< Convert value to 2-vector of unsigned integers (quarter size).
#define PORT_CONVERT_TO_UINT_QUARTER_V3(r, value) PORT_CONVERT_TO_UINT8_V3(r, value) ///< Convert value to 3-vector of unsigned integers (quarter size).
#define PORT_CONVERT_TO_UINT_QUARTER_V4(r, value) PORT_CONVERT_TO_UINT8_V4(r, value) ///< Convert value to 4-vector of unsigned integers (quarter size).
#define PORT_CONVERT_TO_UINT_QUARTER_V8(r, value) PORT_CONVERT_TO_UINT8_V8(r, value) ///< Convert value to 8-vector of unsigned integers (quarter size).
#define PORT_CONVERT_TO_UINT_QUARTER_V16(r, value) PORT_CONVERT_TO_UINT8_V16(r, value) ///< Convert value to 16-vector of unsigned integers (quarter size).

#define PORT_CONVERT_TO_SINT_QUARTER(value) PORT_CONVERT_TO_SINT8(value) ///< Convert value to signed integer (quarter size).
#define PORT_CONVERT_TO_SINT_QUARTER_V2(r, value) PORT_CONVERT_TO_SINT8_V2(r, value) ///< Convert value to 2-vector of signed integers (quarter size).
#define PORT_CONVERT_TO_SINT_QUARTER_V3(r, value) PORT_CONVERT_TO_SINT8_V3(r, value) ///< Convert value to 3-vector of signed integers (quarter size).
#define PORT_CONVERT_TO_SINT_QUARTER_V4(r, value) PORT_CONVERT_TO_SINT8_V4(r, value) ///< Convert value to 4-vector of signed integers (quarter size).
#define PORT_CONVERT_TO_SINT_QUARTER_V8(r, value) PORT_CONVERT_TO_SINT8_V8(r, value) ///< Convert value to 8-vector of signed integers (quarter size).
#define PORT_CONVERT_TO_SINT_QUARTER_V16(r, value) PORT_CONVERT_TO_SINT8_V16(r, value) ///< Convert value to 16-vector of signed integers (quarter size).

#define PORT_CONVERT_TO_UINT_HALF(value) PORT_CONVERT_TO_UINT16(value) ///< Convert value to unsigned integer (half size).
#define PORT_CONVERT_TO_UINT_HALF_V2(r, value) PORT_CONVERT_TO_UINT16_V2(r, value) ///< Convert value to 2-vector of unsigned integers (half size).
#define PORT_CONVERT_TO_UINT_HALF_V3(r, value) PORT_CONVERT_TO_UINT16_V3(r, value) ///< Convert value to 3-vector of unsigned integers (half size).
#define PORT_CONVERT_TO_UINT_HALF_V4(r, value) PORT_CONVERT_TO_UINT16_V4(r, value) ///< Convert value to 4-vector of unsigned integers (half size).
#define PORT_CONVERT_TO_UINT_HALF_V8(r, value) PORT_CONVERT_TO_UINT16_V8(r, value) ///< Convert value to 8-vector of unsigned integers (half size).
#define PORT_CONVERT_TO_UINT_HALF_V16(r, value) PORT_CONVERT_TO_UINT16_V16(r, value) ///< Convert value to 16-vector of unsigned integers (half size).

#define PORT_CONVERT_TO_SINT_HALF(value) PORT_CONVERT_TO_SINT16(value) ///< Convert value to signed integer (half size).
#define PORT_CONVERT_TO_SINT_HALF_V2(r, value) PORT_CONVERT_TO_SINT16_V2(r, value) ///< Convert value to 2-vector of signed integers (half size).
#define PORT_CONVERT_TO_SINT_HALF_V3(r, value) PORT_CONVERT_TO_SINT16_V3(r, value) ///< Convert value to 3-vector of signed integers (half size).
#define PORT_CONVERT_TO_SINT_HALF_V4(r, value) PORT_CONVERT_TO_SINT16_V4(r, value) ///< Convert value to 4-vector of signed integers (half size).
#define PORT_CONVERT_TO_SINT_HALF_V8(r, value) PORT_CONVERT_TO_SINT16_V8(r, value) ///< Convert value to 8-vector of signed integers (half size).
#define PORT_CONVERT_TO_SINT_HALF_V16(r, value) PORT_CONVERT_TO_SINT16_V16(r, value) ///< Convert value to 16-vector of signed integers (half size).

#define PORT_CONVERT_TO_UINT_SINGLE(value) PORT_CONVERT_TO_UINT32(value) ///< Convert value to unsigned integer (single size).
#define PORT_CONVERT_TO_UINT_SINGLE_V2(r, value) PORT_CONVERT_TO_UINT32_V2(r, value) ///< Convert value to 2-vector of unsigned integers (single size).
#define PORT_CONVERT_TO_UINT_SINGLE_V3(r, value) PORT_CONVERT_TO_UINT32_V3(r, value) ///< Convert value to 3-vector of unsigned integers (single size).
#define PORT_CONVERT_TO_UINT_SINGLE_V4(r, value) PORT_CONVERT_TO_UINT32_V4(r, value) ///< Convert value to 4-vector of unsigned integers (single size).
#define PORT_CONVERT_TO_UINT_SINGLE_V8(r, value) PORT_CONVERT_TO_UINT32_V8(r, value) ///< Convert value to 8-vector of unsigned integers (single size).
#define PORT_CONVERT_TO_UINT_SINGLE_V16(r, value) PORT_CONVERT_TO_UINT32_V16(r, value) ///< Convert value to 16-vector of unsigned integers (single size).

#define PORT_CONVERT_TO_SINT_SINGLE(value) PORT_CONVERT_TO_SINT32(value) ///< Convert value to signed integer (single size).
#define PORT_CONVERT_TO_SINT_SINGLE_V2(r, value) PORT_CONVERT_TO_SINT32_V2(r, value) ///< Convert value to 2-vector of signed integers (single size).
#define PORT_CONVERT_TO_SINT_SINGLE_V3(r, value) PORT_CONVERT_TO_SINT32_V3(r, value) ///< Convert value to 3-vector of signed integers (single size).
#define PORT_CONVERT_TO_SINT_SINGLE_V4(r, value) PORT_CONVERT_TO_SINT32_V4(r, value) ///< Convert value to 4-vector of signed integers (single size).
#define PORT_CONVERT_TO_SINT_SINGLE_V8(r, value) PORT_CONVERT_TO_SINT32_V8(r, value) ///< Convert value to 8-vector of signed integers (single size).
#define PORT_CONVERT_TO_SINT_SINGLE_V16(r, value) PORT_CONVERT_TO_SINT32_V16(r, value) ///< Convert value to 16-vector of signed integers (single size).

#define PORT_CONVERT_TO_UINT_DOUBLE(value) PORT_CONVERT_TO_UINT64(value) ///< Convert value to unsigned integer (double size).
#define PORT_CONVERT_TO_UINT_DOUBLE_V2(r, value) PORT_CONVERT_TO_UINT64_V2(r, value) ///< Convert value to 2-vector of unsigned integers (double size).
#define PORT_CONVERT_TO_UINT_DOUBLE_V3(r, value) PORT_CONVERT_TO_UINT64_V3(r, value) ///< Convert value to 3-vector of unsigned integers (double size).
#define PORT_CONVERT_TO_UINT_DOUBLE_V4(r, value) PORT_CONVERT_TO_UINT64_V4(r, value) ///< Convert value to 4-vector of unsigned integers (double size).
#define PORT_CONVERT_TO_UINT_DOUBLE_V8(r, value) PORT_CONVERT_TO_UINT64_V8(r, value) ///< Convert value to 8-vector of unsigned integers (double size).
#define PORT_CONVERT_TO_UINT_DOUBLE_V16(r, value) PORT_CONVERT_TO_UINT64_V16(r, value) ///< Convert value to 16-vector of unsigned integers (double size).

#define PORT_CONVERT_TO_SINT_DOUBLE(value) PORT_CONVERT_TO_SINT64(value) ///< Convert value to signed integer (double size).
#define PORT_CONVERT_TO_SINT_DOUBLE_V2(r, value) PORT_CONVERT_TO_SINT64_V2(r, value) ///< Convert value to 2-vector of signed integers (double size).
#define PORT_CONVERT_TO_SINT_DOUBLE_V3(r, value) PORT_CONVERT_TO_SINT64_V3(r, value) ///< Convert value to 3-vector of signed integers (double size).
#define PORT_CONVERT_TO_SINT_DOUBLE_V4(r, value) PORT_CONVERT_TO_SINT64_V4(r, value) ///< Convert value to 4-vector of signed integers (double size).
#define PORT_CONVERT_TO_SINT_DOUBLE_V8(r, value) PORT_CONVERT_TO_SINT64_V8(r, value) ///< Convert value to 8-vector of signed integers (double size).
#define PORT_CONVERT_TO_SINT_DOUBLE_V16(r, value) PORT_CONVERT_TO_SINT64_V16(r, value) ///< Convert value to 16-vector of signed integers (double size).

#define PORT_CONVERT_TO_FLOAT_SINGLE(value) PORT_CONVERT_TO_FLOAT32(value) ///< Convert value to floating-point number (single size).
#define PORT_CONVERT_TO_FLOAT_SINGLE_V2(r, value) PORT_CONVERT_TO_FLOAT32_V2(r, value) ///< Convert value to 2-vector of floating-point numbers (single size).
#define PORT_CONVERT_TO_FLOAT_SINGLE_V3(r, value) PORT_CONVERT_TO_FLOAT32_V3(r, value) ///< Convert value to 3-vector of floating-point numbers (single size).
#define PORT_CONVERT_TO_FLOAT_SINGLE_V4(r, value) PORT_CONVERT_TO_FLOAT32_V4(r, value) ///< Convert value to 4-vector of floating-point numbers (single size).
#define PORT_CONVERT_TO_FLOAT_SINGLE_V8(r, value) PORT_CONVERT_TO_FLOAT32_V8(r, value) ///< Convert value to 8-vector of floating-point numbers (single size).
#define PORT_CONVERT_TO_FLOAT_SINGLE_V16(r, value) PORT_CONVERT_TO_FLOAT32_V16(r, value) ///< Convert value to 16-vector of floating-point numbers (single size).

#define PORT_CONVERT_TO_FLOAT_DOUBLE(value) PORT_CONVERT_TO_FLOAT64(value) ///< Convert value to floating-point number (double size).
#define PORT_CONVERT_TO_FLOAT_DOUBLE_V2(r, value) PORT_CONVERT_TO_FLOAT64_V2(r, value) ///< Convert value to 2-vector of floating-point numbers (double size).
#define PORT_CONVERT_TO_FLOAT_DOUBLE_V3(r, value) PORT_CONVERT_TO_FLOAT64_V3(r, value) ///< Convert value to 3-vector of floating-point numbers (double size).
#define PORT_CONVERT_TO_FLOAT_DOUBLE_V4(r, value) PORT_CONVERT_TO_FLOAT64_V4(r, value) ///< Convert value to 4-vector of floating-point numbers (double size).
#define PORT_CONVERT_TO_FLOAT_DOUBLE_V8(r, value) PORT_CONVERT_TO_FLOAT64_V8(r, value) ///< Convert value to 8-vector of floating-point numbers (double size).
#define PORT_CONVERT_TO_FLOAT_DOUBLE_V16(r, value) PORT_CONVERT_TO_FLOAT64_V16(r, value) ///< Convert value to 16-vector of floating-point numbers (double size).

///////////////////////////////////////////////////////////////////////////////
// Default types
///////////////////////////////////////////////////////////////////////////////

#ifndef PORT_FEATURE_DEFAULT_INTEGER_64

#define PORT_CONVERT_TO_UINT(value) PORT_CONVERT_TO_UINT32(value) ///< Convert value to default unsigned integer.
#define PORT_CONVERT_TO_UINT_V2(r, value) PORT_CONVERT_TO_UINT32_V2(r, value) ///< Convert value to 2-vector of default unsigned integers.
#define PORT_CONVERT_TO_UINT_V3(r, value) PORT_CONVERT_TO_UINT32_V3(r, value) ///< Convert value to 3-vector of default unsigned integers.
#define PORT_CONVERT_TO_UINT_V4(r, value) PORT_CONVERT_TO_UINT32_V4(r, value) ///< Convert value to 4-vector of default unsigned integers.
#define PORT_CONVERT_TO_UINT_V8(r, value) PORT_CONVERT_TO_UINT32_V8(r, value) ///< Convert value to 8-vector of default unsigned integers.
#define PORT_CONVERT_TO_UINT_V16(r, value) PORT_CONVERT_TO_UINT32_V16(r, value) ///< Convert value to 16-vector of default unsigned integers.

#define PORT_CONVERT_TO_SINT(value) PORT_CONVERT_TO_SINT32(value) ///< Convert value to default signed integer.
#define PORT_CONVERT_TO_SINT_V2(r, value) PORT_CONVERT_TO_SINT32_V2(r, value) ///< Convert value to 2-vector of default signed integers.
#define PORT_CONVERT_TO_SINT_V3(r, value) PORT_CONVERT_TO_SINT32_V3(r, value) ///< Convert value to 3-vector of default signed integers.
#define PORT_CONVERT_TO_SINT_V4(r, value) PORT_CONVERT_TO_SINT32_V4(r, value) ///< Convert value to 4-vector of default signed integers.
#define PORT_CONVERT_TO_SINT_V8(r, value) PORT_CONVERT_TO_SINT32_V8(r, value) ///< Convert value to 8-vector of default signed integers.
#define PORT_CONVERT_TO_SINT_V16(r, value) PORT_CONVERT_TO_SINT32_V16(r, value) ///< Convert value to 16-vector of default signed integers.

#else // PORT_FEATURE_DEFAULT_INTEGER_64

#define PORT_CONVERT_TO_UINT(value) PORT_CONVERT_TO_UINT64(value) ///< Convert value to default unsigned integer.
#define PORT_CONVERT_TO_UINT_V2(r, value) PORT_CONVERT_TO_UINT64_V2(r, value) ///< Convert value to 2-vector of default unsigned integers.
#define PORT_CONVERT_TO_UINT_V3(r, value) PORT_CONVERT_TO_UINT64_V3(r, value) ///< Convert value to 3-vector of default unsigned integers.
#define PORT_CONVERT_TO_UINT_V4(r, value) PORT_CONVERT_TO_UINT64_V4(r, value) ///< Convert value to 4-vector of default unsigned integers.
#define PORT_CONVERT_TO_UINT_V8(r, value) PORT_CONVERT_TO_UINT64_V8(r, value) ///< Convert value to 8-vector of default unsigned integers.
#define PORT_CONVERT_TO_UINT_V16(r, value) PORT_CONVERT_TO_UINT64_V16(r, value) ///< Convert value to 16-vector of default unsigned integers.

#define PORT_CONVERT_TO_SINT(value) PORT_CONVERT_TO_SINT64(value) ///< Convert value to default signed integer.
#define PORT_CONVERT_TO_SINT_V2(r, value) PORT_CONVERT_TO_SINT64_V2(r, value) ///< Convert value to 2-vector of default signed integers.
#define PORT_CONVERT_TO_SINT_V3(r, value) PORT_CONVERT_TO_SINT64_V3(r, value) ///< Convert value to 3-vector of default signed integers.
#define PORT_CONVERT_TO_SINT_V4(r, value) PORT_CONVERT_TO_SINT64_V4(r, value) ///< Convert value to 4-vector of default signed integers.
#define PORT_CONVERT_TO_SINT_V8(r, value) PORT_CONVERT_TO_SINT64_V8(r, value) ///< Convert value to 8-vector of default signed integers.
#define PORT_CONVERT_TO_SINT_V16(r, value) PORT_CONVERT_TO_SINT64_V16(r, value) ///< Convert value to 16-vector of default signed integers.

#endif // PORT_FEATURE_DEFAULT_INTEGER_64

#ifndef PORT_FEATURE_DEFAULT_FLOAT_64

#define PORT_CONVERT_TO_FLOAT(value) PORT_CONVERT_TO_FLOAT32(value) ///< Convert value to default floating-point number.
#define PORT_CONVERT_TO_FLOAT_V2(r, value) PORT_CONVERT_TO_FLOAT32_V2(r, value) ///< Convert value to 2-vector of default floating-point numbers.
#define PORT_CONVERT_TO_FLOAT_V3(r, value) PORT_CONVERT_TO_FLOAT32_V3(r, value) ///< Convert value to 3-vector of default floating-point numbers.
#define PORT_CONVERT_TO_FLOAT_V4(r, value) PORT_CONVERT_TO_FLOAT32_V4(r, value) ///< Convert value to 4-vector of default floating-point numbers.
#define PORT_CONVERT_TO_FLOAT_V8(r, value) PORT_CONVERT_TO_FLOAT32_V8(r, value) ///< Convert value to 8-vector of default floating-point numbers.
#define PORT_CONVERT_TO_FLOAT_V16(r, value) PORT_CONVERT_TO_FLOAT32_V16(r, value) ///< Convert value to 16-vector of default floating-point numbers.

#else // PORT_FEATURE_DEFAULT_FLOAT_64

#define PORT_CONVERT_TO_FLOAT(value) PORT_CONVERT_TO_FLOAT64(value) ///< Convert value to default floating-point number.
#define PORT_CONVERT_TO_FLOAT_V2(r, value) PORT_CONVERT_TO_FLOAT64_V2(r, value) ///< Convert value to 2-vector of default floating-point numbers.
#define PORT_CONVERT_TO_FLOAT_V3(r, value) PORT_CONVERT_TO_FLOAT64_V3(r, value) ///< Convert value to 3-vector of default floating-point numbers.
#define PORT_CONVERT_TO_FLOAT_V4(r, value) PORT_CONVERT_TO_FLOAT64_V4(r, value) ///< Convert value to 4-vector of default floating-point numbers.
#define PORT_CONVERT_TO_FLOAT_V8(r, value) PORT_CONVERT_TO_FLOAT64_V8(r, value) ///< Convert value to 8-vector of default floating-point numbers.
#define PORT_CONVERT_TO_FLOAT_V16(r, value) PORT_CONVERT_TO_FLOAT64_V16(r, value) ///< Convert value to 16-vector of default floating-point numbers.

#endif // PORT_FEATURE_DEFAULT_FLOAT_64

#endif // _PORT_CDEV_CONVERT_DEF_H_

