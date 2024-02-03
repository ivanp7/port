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
 * @brief Limits of built-in scalar types.
 */

#pragma once
#ifndef _PORT_CDEV_TYPES_DEF_H_
#define _PORT_CDEV_TYPES_DEF_H_

#ifndef __OPENCL_C_VERSION__
#  include <CL/cl.h>
#endif

///////////////////////////////////////////////////////////////////////////////
// Absolute types
///////////////////////////////////////////////////////////////////////////////

#ifdef __OPENCL_C_VERSION__

#define PORT_UINT8_MAX UCHAR_MAX ///< Maximum value of unsigned 8-bit integer (255).
#define PORT_SINT8_MAX CHAR_MAX  ///< Maximum value of signed 8-bit integer (+127).
#define PORT_SINT8_MIN CHAR_MIN  ///< Minimum value of signed 8-bit integer (-128).

#define PORT_UINT16_MAX USHRT_MAX ///< Maximum value of unsigned 16-bit integer (65535).
#define PORT_SINT16_MAX SHRT_MAX  ///< Maximum value of signed 16-bit integer (+32767).
#define PORT_SINT16_MIN SHRT_MIN  ///< Minimum value of signed 16-bit integer (-32768).

#define PORT_UINT32_MAX UINT_MAX ///< Maximum value of unsigned 32-bit integer (4294967295).
#define PORT_SINT32_MAX INT_MAX  ///< Maximum value of signed 32-bit integer (+2147483647).
#define PORT_SINT32_MIN INT_MIN  ///< Minimum value of signed 32-bit integer (-2147483648).

#define PORT_UINT64_MAX ULONG_MAX ///< Maximum value of unsigned 64-bit integer (18446744073709551615).
#define PORT_SINT64_MAX LONG_MAX  ///< Maximum value of signed 64-bit integer (+9223372036854775807).
#define PORT_SINT64_MIN LONG_MIN  ///< Minimum value of signed 64-bit integer (-9223372036854775808).

#define PORT_FLOAT32_MAX FLT_MAX ///< Maximum finite value of 32-bit floating-point number (0x1.fffffp127f).
#define PORT_FLOAT32_MIN FLT_MIN ///< Minimum positive value of 32-bit floating-point number (0x1.0p-126f).
#define PORT_FLOAT32_EPS FLT_EPSILON ///< Minimum value of 32-bit floating-point number greater than 1 minus 1 (0x1.0p-23f).
#define PORT_FLOAT32_RADIX FLT_RADIX ///< Radix of 32-bit floating-point number (2).
#define PORT_FLOAT32_MANT_DIG FLT_MANT_DIG ///< Number of mantissa digits in 32-bit floating-point number (24).
#define PORT_FLOAT32_MAX_EXP FLT_MAX_EXP ///< Maximum exponent of 32-bit floating-point number (+128).
#define PORT_FLOAT32_MIN_EXP FLT_MIN_EXP ///< Minimum exponent of 32-bit floating-point number (-125).
#define PORT_FLOAT32_DIG FLT_DIG ///< Number of significant decimal digits in 32-bit floating-point number (6).
#define PORT_FLOAT32_MAX_EXP10 FLT_MAX_10_EXP ///< Maximum decimal exponent of 32-bit floating-point number (+38).
#define PORT_FLOAT32_MIN_EXP10 FLT_MIN_10_EXP ///< Minimum decimal exponent of 32-bit floating-point number (-37).

#define PORT_FLOAT64_MAX DBL_MAX ///< Maximum finite value of 64-bit floating-point number (0x1.fffffffffffffp1023).
#define PORT_FLOAT64_MIN DBL_MIN ///< Minimum positive value of 64-bit floating-point number (0x1.0p-1022).
#define PORT_FLOAT64_EPS DBL_EPSILON ///< Minimum value of 64-bit floating-point number greater than 1 minus 1 (0x1.0p-52).
#define PORT_FLOAT64_RADIX DBL_RADIX ///< Radix of 64-bit floating-point number (2).
#define PORT_FLOAT64_MANT_DIG DBL_MANT_DIG ///< Number of mantissa digits in 64-bit floating-point number (53).
#define PORT_FLOAT64_MAX_EXP DBL_MAX_EXP ///< Maximum exponent of 64-bit floating-point number (+1024).
#define PORT_FLOAT64_MIN_EXP DBL_MIN_EXP ///< Minimum exponent of 64-bit floating-point number (-1021).
#define PORT_FLOAT64_DIG DBL_DIG ///< Number of significant decimal digits in 64-bit floating-point number (15).
#define PORT_FLOAT64_MAX_EXP10 DBL_MAX_10_EXP ///< Maximum decimal exponent of 64-bit floating-point number (+308).
#define PORT_FLOAT64_MIN_EXP10 DBL_MIN_10_EXP ///< Minimum decimal exponent of 64-bit floating-point number (-307).

#else // __OPENCL_C_VERSION__

#define PORT_UINT8_MAX CL_UCHAR_MAX ///< Maximum value of unsigned 8-bit integer (255).
#define PORT_SINT8_MAX CL_CHAR_MAX  ///< Maximum value of signed 8-bit integer (+127).
#define PORT_SINT8_MIN CL_CHAR_MIN  ///< Minimum value of signed 8-bit integer (-128).

#define PORT_UINT16_MAX CL_USHRT_MAX ///< Maximum value of unsigned 16-bit integer (65535).
#define PORT_SINT16_MAX CL_SHRT_MAX  ///< Maximum value of signed 16-bit integer (+32767).
#define PORT_SINT16_MIN CL_SHRT_MIN  ///< Minimum value of signed 16-bit integer (-32768).

#define PORT_UINT32_MAX CL_UINT_MAX ///< Maximum value of unsigned 32-bit integer (4294967295).
#define PORT_SINT32_MAX CL_INT_MAX  ///< Maximum value of signed 32-bit integer (+2147483647).
#define PORT_SINT32_MIN CL_INT_MIN  ///< Minimum value of signed 32-bit integer (-2147483648).

#define PORT_UINT64_MAX CL_ULONG_MAX ///< Maximum value of unsigned 64-bit integer (18446744073709551615).
#define PORT_SINT64_MAX CL_LONG_MAX  ///< Maximum value of signed 64-bit integer (+9223372036854775807).
#define PORT_SINT64_MIN CL_LONG_MIN  ///< Minimum value of signed 64-bit integer (-9223372036854775808).

#define PORT_FLOAT32_MAX CL_FLT_MAX ///< Maximum finite value of 32-bit floating-point number (0x1.fffffp127f).
#define PORT_FLOAT32_MIN CL_FLT_MIN ///< Minimum positive value of 32-bit floating-point number (0x1.0p-126f).
#define PORT_FLOAT32_EPS CL_FLT_EPSILON ///< Minimum value of 32-bit floating-point number greater than 1 minus 1 (0x1.0p-23f).
#define PORT_FLOAT32_RADIX CL_FLT_RADIX ///< Radix of 32-bit floating-point number (2).
#define PORT_FLOAT32_MANT_DIG CL_FLT_MANT_DIG ///< Number of mantissa digits in 32-bit floating-point number (24).
#define PORT_FLOAT32_MAX_EXP CL_FLT_MAX_EXP ///< Maximum exponent of 32-bit floating-point number (+128).
#define PORT_FLOAT32_MIN_EXP CL_FLT_MIN_EXP ///< Minimum exponent of 32-bit floating-point number (-125).
#define PORT_FLOAT32_DIG CL_FLT_DIG ///< Number of significant decimal digits in 32-bit floating-point number (6).
#define PORT_FLOAT32_MAX_EXP10 CL_FLT_MAX_10_EXP ///< Maximum decimal exponent of 32-bit floating-point number (+38).
#define PORT_FLOAT32_MIN_EXP10 CL_FLT_MIN_10_EXP ///< Minimum decimal exponent of 32-bit floating-point number (-37).

#define PORT_FLOAT64_MAX CL_DBL_MAX ///< Maximum finite value of 64-bit floating-point number (0x1.fffffffffffffp1023).
#define PORT_FLOAT64_MIN CL_DBL_MIN ///< Minimum positive value of 64-bit floating-point number (0x1.0p-1022).
#define PORT_FLOAT64_EPS CL_DBL_EPSILON ///< Minimum value of 64-bit floating-point number greater than 1 minus 1 (0x1.0p-52).
#define PORT_FLOAT64_RADIX CL_DBL_RADIX ///< Radix of 64-bit floating-point number (2).
#define PORT_FLOAT64_MANT_DIG CL_DBL_MANT_DIG ///< Number of mantissa digits in 64-bit floating-point number (53).
#define PORT_FLOAT64_MAX_EXP CL_DBL_MAX_EXP ///< Maximum exponent of 64-bit floating-point number (+1024).
#define PORT_FLOAT64_MIN_EXP CL_DBL_MIN_EXP ///< Minimum exponent of 64-bit floating-point number (-1021).
#define PORT_FLOAT64_DIG CL_DBL_DIG ///< Number of significant decimal digits in 64-bit floating-point number (15).
#define PORT_FLOAT64_MAX_EXP10 CL_DBL_MAX_10_EXP ///< Maximum decimal exponent of 64-bit floating-point number (+308).
#define PORT_FLOAT64_MIN_EXP10 CL_DBL_MIN_10_EXP ///< Minimum decimal exponent of 64-bit floating-point number (-307).

#endif // __OPENCL_C_VERSION__

///////////////////////////////////////////////////////////////////////////////
// Relative types
///////////////////////////////////////////////////////////////////////////////

#define PORT_UINT_QUARTER_MAX PORT_UINT8_MAX ///< Maximum value of unsigned integer (quarter size).
#define PORT_SINT_QUARTER_MAX PORT_SINT8_MAX ///< Maximum value of signed integer (quarter size).
#define PORT_SINT_QUARTER_MIN PORT_SINT8_MIN ///< Minimum value of signed integer (quarter size).

#define PORT_UINT_HALF_MAX PORT_UINT16_MAX ///< Maximum value of unsigned integer (half size).
#define PORT_SINT_HALF_MAX PORT_SINT16_MAX ///< Maximum value of signed integer (half size).
#define PORT_SINT_HALF_MIN PORT_SINT16_MIN ///< Minimum value of signed integer (half size).

#define PORT_UINT_SINGLE_MAX PORT_UINT32_MAX ///< Maximum value of unsigned integer (single size).
#define PORT_SINT_SINGLE_MAX PORT_SINT32_MAX ///< Maximum value of signed integer (single size).
#define PORT_SINT_SINGLE_MIN PORT_SINT32_MIN ///< Minimum value of signed integer (single size).

#define PORT_UINT_DOUBLE_MAX PORT_UINT64_MAX ///< Maximum value of unsigned integer (double size).
#define PORT_SINT_DOUBLE_MAX PORT_SINT64_MAX ///< Maximum value of signed integer (double size).
#define PORT_SINT_DOUBLE_MIN PORT_SINT64_MIN ///< Minimum value of signed integer (double size).

#define PORT_FLOAT_SINGLE_MAX PORT_FLOAT32_MAX ///< Maximum finite value of floating-point number (single size).
#define PORT_FLOAT_SINGLE_MIN PORT_FLOAT32_MIN ///< Minimum positive value of floating-point number (single size).
#define PORT_FLOAT_SINGLE_EPS PORT_FLOAT32_EPS ///< Minimum value of floating-point number (single size) greater than 1 minus 1.
#define PORT_FLOAT_SINGLE_RADIX PORT_FLOAT32_RADIX ///< Radix of floating-point number (single size).
#define PORT_FLOAT_SINGLE_MANT_DIG PORT_FLOAT32_MANT_DIG ///< Number of mantissa digits in floating-point number (single size).
#define PORT_FLOAT_SINGLE_MAX_EXP PORT_FLOAT32_MAX_EXP ///< Maximum exponent of floating-point number (single size).
#define PORT_FLOAT_SINGLE_MIN_EXP PORT_FLOAT32_MIN_EXP ///< Minimum exponent of floating-point number (single size).
#define PORT_FLOAT_SINGLE_DIG PORT_FLOAT32_DIG ///< Number of significant decimal digits in floating-point number (single size).
#define PORT_FLOAT_SINGLE_MAX_EXP10 PORT_FLOAT32_MAX_EXP10 ///< Maximum decimal exponent of floating-point number (single size).
#define PORT_FLOAT_SINGLE_MIN_EXP10 PORT_FLOAT32_MIN_EXP10 ///< Minimum decimal exponent of floating-point number (single size).

#define PORT_FLOAT_DOUBLE_MAX PORT_FLOAT64_MAX ///< Maximum finite value of floating-point number (double size).
#define PORT_FLOAT_DOUBLE_MIN PORT_FLOAT64_MIN ///< Minimum positive value of floating-point number (double size).
#define PORT_FLOAT_DOUBLE_EPS PORT_FLOAT64_EPS ///< Minimum value of floating-point number (double size) greater than 1 minus 1.
#define PORT_FLOAT_DOUBLE_RADIX PORT_FLOAT64_RADIX ///< Radix of floating-point number (double size).
#define PORT_FLOAT_DOUBLE_MANT_DIG PORT_FLOAT64_MANT_DIG ///< Number of mantissa digits in floating-point number (double size).
#define PORT_FLOAT_DOUBLE_MAX_EXP PORT_FLOAT64_MAX_EXP ///< Maximum exponent of floating-point number (double size).
#define PORT_FLOAT_DOUBLE_MIN_EXP PORT_FLOAT64_MIN_EXP ///< Minimum exponent of floating-point number (double size).
#define PORT_FLOAT_DOUBLE_DIG PORT_FLOAT64_DIG ///< Number of significant decimal digits in floating-point number (double size).
#define PORT_FLOAT_DOUBLE_MAX_EXP10 PORT_FLOAT64_MAX_EXP10 ///< Maximum decimal exponent of floating-point number (double size).
#define PORT_FLOAT_DOUBLE_MIN_EXP10 PORT_FLOAT64_MIN_EXP10 ///< Minimum decimal exponent of floating-point number (double size).

///////////////////////////////////////////////////////////////////////////////
// Default types
///////////////////////////////////////////////////////////////////////////////

#ifndef PORT_FEATURE_DEFAULT_INTEGER_64

#define PORT_UINT_MAX PORT_UINT32_MAX ///< Maximum value of default unsigned integer.
#define PORT_SINT_MAX PORT_SINT32_MAX ///< Maximum value of default signed integer.
#define PORT_SINT_MIN PORT_SINT32_MIN ///< Minimum value of default signed integer.

#else // PORT_FEATURE_DEFAULT_INTEGER_64

#define PORT_UINT_MAX PORT_UINT64_MAX ///< Maximum value of default unsigned integer.
#define PORT_SINT_MAX PORT_SINT64_MAX ///< Maximum value of default signed integer.
#define PORT_SINT_MIN PORT_SINT64_MIN ///< Minimum value of default signed integer.

#endif // PORT_FEATURE_DEFAULT_INTEGER_64

#define PORT_INT_RELSIZE (sizeof(port_uint_t) / sizeof(port_uint_single_t)) ///< Relative size of default integer.

#ifndef PORT_FEATURE_DEFAULT_FLOAT_64

#define PORT_FLOAT_MAX PORT_FLOAT32_MAX ///< Maximum finite value of default floating-point number.
#define PORT_FLOAT_MIN PORT_FLOAT32_MIN ///< Minimum positive value of default floating-point number.
#define PORT_FLOAT_EPS PORT_FLOAT32_EPS ///< Minimum value of default floating-point number greater than 1 minus 1.
#define PORT_FLOAT_RADIX PORT_FLOAT32_RADIX ///< Radix of default floating-point number.
#define PORT_FLOAT_MANT_DIG PORT_FLOAT32_MANT_DIG ///< Number of mantissa digits in default floating-point number.
#define PORT_FLOAT_MAX_EXP PORT_FLOAT32_MAX_EXP ///< Maximum exponent of default floating-point number.
#define PORT_FLOAT_MIN_EXP PORT_FLOAT32_MIN_EXP ///< Minimum exponent of default floating-point number.
#define PORT_FLOAT_DIG PORT_FLOAT32_DIG ///< Number of significant decimal digits in default floating-point number.
#define PORT_FLOAT_MAX_EXP10 PORT_FLOAT32_MAX_EXP10 ///< Maximum decimal exponent of default floating-point number.
#define PORT_FLOAT_MIN_EXP10 PORT_FLOAT32_MIN_EXP10 ///< Minimum decimal exponent of default floating-point number.

#define PORT_FLOAT(literal) literal##f ///< Literal of default floating-point number.

#else // PORT_FEATURE_DEFAULT_FLOAT_64

#define PORT_FLOAT_MAX PORT_FLOAT64_MAX ///< Maximum finite value of default floating-point number.
#define PORT_FLOAT_MIN PORT_FLOAT64_MIN ///< Minimum positive value of default floating-point number.
#define PORT_FLOAT_EPS PORT_FLOAT64_EPS ///< Minimum value of default floating-point number greater than 1 minus 1.
#define PORT_FLOAT_RADIX PORT_FLOAT64_RADIX ///< Radix of default floating-point number.
#define PORT_FLOAT_MANT_DIG PORT_FLOAT64_MANT_DIG ///< Number of mantissa digits in default floating-point number.
#define PORT_FLOAT_MAX_EXP PORT_FLOAT64_MAX_EXP ///< Maximum exponent of default floating-point number.
#define PORT_FLOAT_MIN_EXP PORT_FLOAT64_MIN_EXP ///< Minimum exponent of default floating-point number.
#define PORT_FLOAT_DIG PORT_FLOAT64_DIG ///< Number of significant decimal digits in default floating-point number.
#define PORT_FLOAT_MAX_EXP10 PORT_FLOAT64_MAX_EXP10 ///< Maximum decimal exponent of default floating-point number.
#define PORT_FLOAT_MIN_EXP10 PORT_FLOAT64_MIN_EXP10 ///< Minimum decimal exponent of default floating-point number.

#define PORT_FLOAT(literal) literal ///< Literal of default floating-point number.

#endif // PORT_FEATURE_DEFAULT_FLOAT_64

#define PORT_FLOAT_RELSIZE (sizeof(port_float_t) / sizeof(port_float_single_t)) ///< Relative size of default floating-point number.

#endif // _PORT_CDEV_TYPES_DEF_H_

