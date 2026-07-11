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
 * @brief Operations on floating-point numbers.
 */

#pragma once
#ifndef _PORT_FLOAT_FUN_H_
#define _PORT_FLOAT_FUN_H_

#include "port/types.typ.h"

#ifndef __OPENCL_C_VERSION__
#  include <stdbool.h>
#endif


///////////////////////////////////////////////////////////////////////////////
// Miscellaneous functions
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Clamp 32-bit floating-point number between minimum and maximum.
 *
 * @return Clamped value.
 */
port_float32_t
port_float32_clamp(
        port_float32_t value, ///< [in] Value to clamp.

        port_float32_t minval, ///< [in] Minimum value.
        port_float32_t maxval  ///< [in] Maximum value.
);

/**
 * @brief Clamp single-width floating-point number between minimum and maximum.
 *
 * @return Clamped value.
 */
#define port_floats_clamp   port_float32_clamp

/**
 * @brief Clamp 64-bit floating-point number between minimum and maximum.
 *
 * @return Clamped value.
 */
port_float64_t
port_float64_clamp(
        port_float64_t value, ///< [in] Value to clamp.

        port_float64_t minval, ///< [in] Minimum value.
        port_float64_t maxval  ///< [in] Maximum value.
);

/**
 * @brief Clamp double-width floating-point number between minimum and maximum.
 *
 * @return Clamped value.
 */
#define port_floatd_clamp   port_float64_clamp

/**
 * @brief Calculate distance between 32-bit floating-point numbers in ULPs.
 *
 * If either of values is infinity or NaN, the maximum value is returned.
 *
 * @return ULP distance.
 */
port_uint32_t
port_float32_ulp_distance(
        port_float32_t value1, ///< [in] First number.
        port_float32_t value2  ///< [in] Second number.
);

/**
 * @brief Calculate distance between single-width floating-point numbers in ULPs.
 *
 * If either of values is infinity or NaN, the maximum value is returned.
 *
 * @return ULP distance.
 */
#define port_floats_ulp_distance    port_float32_ulp_distance

/**
 * @brief Calculate distance between 64-bit floating-point numbers in ULPs.
 *
 * If either of values is infinity or NaN, the maximum value is returned.
 *
 * @return ULP distance.
 */
port_uint64_t
port_float64_ulp_distance(
        port_float64_t value1, ///< [in] First number.
        port_float64_t value2  ///< [in] Second number.
);

/**
 * @brief Calculate distance between double-width floating-point numbers in ULPs.
 *
 * If either of values is infinity or NaN, the maximum value is returned.
 *
 * @return ULP distance.
 */
#define port_floatd_ulp_distance    port_float64_ulp_distance

/**
 * @brief Check if 32-bit floating-point numbers are (almost) equal.
 *
 * Values in [0; 1) are treated specially, as if ULPs are the same as in [1; 2).
 * Zero tolerance forces exact equality.
 *
 * @return True if number are (almost) equal, otherwise false.
 */
bool
port_float32_equal(
        port_float32_t value1, ///< [in] First value.
        port_float32_t value2, ///< [in] Second value.

        port_uint32_t tolerance ///< [in] Inexact equality tolerance.
);

/**
 * @brief Check if single-width floating-point numbers are (almost) equal.
 *
 * Values in [0; 1) are treated specially, as if ULPs are the same as in [1; 2).
 * Zero tolerance forces exact equality.
 *
 * @return True if number are (almost) equal, otherwise false.
 */
#define port_floats_equal   port_float32_equal

/**
 * @brief Check if 64-bit floating-point numbers are (almost) equal.
 *
 * Values in [0; 1) are treated specially, as if ULPs are the same as in [1; 2).
 * Zero tolerance forces exact equality.
 *
 * @return True if number are (almost) equal, otherwise false.
 */
bool
port_float64_equal(
        port_float64_t value1, ///< [in] First value.
        port_float64_t value2, ///< [in] Second value.

        port_uint64_t tolerance ///< [in] Inexact equality tolerance.
);

/**
 * @brief Check if double-width floating-point numbers are (almost) equal.
 *
 * Values in [0; 1) are treated specially, as if ULPs are the same as in [1; 2).
 * Zero tolerance forces exact equality.
 *
 * @return True if number are (almost) equal, otherwise false.
 */
#define port_floatd_equal   port_float64_equal

///////////////////////////////////////////////////////////////////////////////
// Summation algorithms
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Sum two 32-bit floating-point numbers with a round-off error.
 *
 * @return Sum and a round-off error.
 */
port_float32_v2_t
port_float32_two_sum(
        port_float32_t a, ///< [in] First value.
        port_float32_t b  ///< [in] Second value.
);

/**
 * @brief Sum two single-width floating-point numbers with a round-off error.
 *
 * @return Sum and a round-off error.
 */
#define port_floats_two_sum port_float32_two_sum

/**
 * @brief Sum two 64-bit floating-point numbers with a round-off error.
 *
 * @return Sum and a round-off error.
 */
port_float64_v2_t
port_float64_two_sum(
        port_float64_t a, ///< [in] First value.
        port_float64_t b  ///< [in] Second value.
);

/**
 * @brief Sum two double-width floating-point numbers with a round-off error.
 *
 * @return Sum and a round-off error.
 */
#define port_floatd_two_sum port_float64_two_sum

/**
 * @brief Sum 32-bit floating-point numbers using the Neumaier algorithm.
 *
 * @return Sum and a compensation value.
 */
port_float32_v2_t
port_float32_neumaier_sum(
        const port_float32_t values[], ///< [in] Array of values to sum.
        size_t num_values ///< [in] Size of the array of values.
);

/**
 * @brief Sum single-width floating-point numbers using the Neumaier algorithm.
 *
 * @return Sum and a compensation value.
 */
#define port_floats_neumaier_sum    port_float32_neumaier_sum

/**
 * @brief Sum 64-bit floating-point numbers using the Neumaier algorithm.
 *
 * @return Sum and a compensation value.
 */
port_float64_v2_t
port_float64_neumaier_sum(
        const port_float64_t values[], ///< [in] Array of values to sum.
        size_t num_values ///< [in] Size of the array of values.
);

/**
 * @brief Sum double-width floating-point numbers using the Neumaier algorithm.
 *
 * @return Sum and a compensation value.
 */
#define port_floatd_neumaier_sum    port_float64_neumaier_sum

/**
 * @brief Sum 32-bit floating-point numbers using the Shewchuk algorithm (with at most 16 partial sums).
 *
 * @return Sum of input values.
 */
port_float32_t
port_float32_shewchuk16_sum(
        const port_float32_t values[], ///< [in] Array of values to sum.
        size_t num_values ///< [in] Size of the array of values.
);

/**
 * @brief Sum single-width floating-point numbers using the Shewchuk algorithm (with at most 16 partial sums).
 *
 * @return Sum of input values.
 */
#define port_floats_shewchuk16_sum  port_float32_shewchuk16_sum

/**
 * @brief Sum 64-bit floating-point numbers using the Shewchuk algorithm (with at most 16 partial sums).
 *
 * @return Sum of input values.
 */
port_float64_t
port_float64_shewchuk16_sum(
        const port_float64_t values[], ///< [in] Array of values to sum.
        size_t num_values ///< [in] Size of the array of values.
);

/**
 * @brief Sum double-width floating-point numbers using the Shewchuk algorithm (with at most 16 partial sums).
 *
 * @return Sum of input values.
 */
#define port_floatd_shewchuk16_sum  port_float64_shewchuk16_sum

///////////////////////////////////////////////////////////////////////////////
// Multiplication algorithms
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Multiply two 32-bit floating-point numbers with a round-off error.
 *
 * @return Product and a round-off error.
 */
port_float32_v2_t
port_float32_two_product(
        port_float32_t a, ///< [in] First value.
        port_float32_t b  ///< [in] Second value.
);

/**
 * @brief Multiply two single-width floating-point numbers with a round-off error.
 *
 * @return Product and a round-off error.
 */
#define port_floats_two_product port_float32_two_product

/**
 * @brief Multiply two 64-bit floating-point numbers with a round-off error.
 *
 * @return Product and a round-off error.
 */
port_float64_v2_t
port_float64_two_product(
        port_float64_t a, ///< [in] First value.
        port_float64_t b  ///< [in] Second value.
);

/**
 * @brief Multiply two double-width floating-point numbers with a round-off error.
 *
 * @return Product and a round-off error.
 */
#define port_floatd_two_product port_float64_two_product

/**
 * @brief Multiply 32-bit floating-point numbers.
 *
 * @return Product and a round-off error.
 */
port_float32_v2_t
port_float32_multi_product(
        const port_float32_t values[], ///< [in] Array of values to multiply.
        size_t num_values ///< [in] Size of the array of values.
);

/**
 * @brief Multiply single-width floating-point numbers.
 *
 * @return Product and a round-off error.
 */
#define port_floats_multi_product   port_float32_multi_product

/**
 * @brief Multiply 64-bit floating-point numbers.
 *
 * @return Product and a round-off error.
 */
port_float64_v2_t
port_float64_multi_product(
        const port_float64_t values[], ///< [in] Array of values to multiply.
        size_t num_values ///< [in] Size of the array of values.
);

/**
 * @brief Multiply double-width floating-point numbers.
 *
 * @return Product and a round-off error.
 */
#define port_floatd_multi_product   port_float64_multi_product

///////////////////////////////////////////////////////////////////////////////
// float16 -> float32 conversions
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Convert 16-bit floating-point number to 32-bit.
 *
 * Format of float16 is IEEE 754.
 *
 * @return 32-bit float.
 */
port_float32_t
port_convert_float16_to_float32(
        port_uint16_t value ///< [in] 16-bit float value.
);

/**
 * @brief Convert half-width floating-point number to single-width.
 *
 * Format of float16 is IEEE 754.
 *
 * @return Single-width float.
 */
#define port_convert_floath_to_floats port_convert_float16_to_float32

/**
 * @brief Convert 2-vector of 16-bit floating-point numbers to 32-bit.
 *
 * Format of float16 is IEEE 754.
 *
 * @return 32-bit float 2-vector.
 */
port_float32_v2_t
port_convert_float16_to_float32_v2(
        port_uint16_v2_t value ///< [in] 16-bit float vector.
);

/**
 * @brief Convert 2-vector of half-width floating-point numbers to single-width.
 *
 * Format of float16 is IEEE 754.
 *
 * @return Single-width float 2-vector.
 */
#define port_convert_floath_to_floats_v2 port_convert_float16_to_float32_v2

/**
 * @brief Convert 3-vector of 16-bit floating-point numbers to 32-bit.
 *
 * Format of float16 is IEEE 754.
 *
 * @return 32-bit float 3-vector.
 */
port_float32_v3_t
port_convert_float16_to_float32_v3(
        port_uint16_v3_t value ///< [in] 16-bit float vector.
);

/**
 * @brief Convert 3-vector of half-width floating-point numbers to single-width.
 *
 * Format of float16 is IEEE 754.
 *
 * @return Single-width float 3-vector.
 */
#define port_convert_floath_to_floats_v3 port_convert_float16_to_float32_v3

/**
 * @brief Convert 4-vector of 16-bit floating-point numbers to 32-bit.
 *
 * Format of float16 is IEEE 754.
 *
 * @return 32-bit float 4-vector.
 */
port_float32_v4_t
port_convert_float16_to_float32_v4(
        port_uint16_v4_t value ///< [in] 16-bit float vector.
);

/**
 * @brief Convert 4-vector of half-width floating-point numbers to single-width.
 *
 * Format of float16 is IEEE 754.
 *
 * @return Single-width float 4-vector.
 */
#define port_convert_floath_to_floats_v4 port_convert_float16_to_float32_v4

/**
 * @brief Convert 8-vector of 16-bit floating-point numbers to 32-bit.
 *
 * Format of float16 is IEEE 754.
 *
 * @return 32-bit float 8-vector.
 */
port_float32_v8_t
port_convert_float16_to_float32_v8(
        port_uint16_v8_t value ///< [in] 16-bit float vector.
);

/**
 * @brief Convert 8-vector of half-width floating-point numbers to single-width.
 *
 * Format of float16 is IEEE 754.
 *
 * @return Single-width float 8-vector.
 */
#define port_convert_floath_to_floats_v8 port_convert_float16_to_float32_v8

/**
 * @brief Convert 16-vector of 16-bit floating-point numbers to 32-bit.
 *
 * Format of float16 is IEEE 754.
 *
 * @return 32-bit float 16-vector.
 */
port_float32_v16_t
port_convert_float16_to_float32_v16(
        port_uint16_v16_t value ///< [in] 16-bit float vector.
);

/**
 * @brief Convert 16-vector of half-width floating-point numbers to single-width.
 *
 * Format of float16 is IEEE 754.
 *
 * @return Single-width float 16-vector.
 */
#define port_convert_floath_to_floats_v16 port_convert_float16_to_float32_v16

///////////////////////////////////////////////////////////////////////////////
// float32 -> float16 conversions
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Convert 32-bit floating-point number to 16-bit.
 *
 * Format of float16 is IEEE 754.
 *
 * @return 16-bit float.
 */
port_uint16_t
port_convert_float32_to_float16(
        port_float32_t value ///< [in] 32-bit float value.
);

/**
 * @brief Convert single-width floating-point number to half-width.
 *
 * Format of float16 is IEEE 754.
 *
 * @return Half-width float.
 */
#define port_convert_floats_to_floath port_convert_float32_to_float16

/**
 * @brief Convert 2-vector of 32-bit floating-point numbers to 16-bit.
 *
 * Format of float16 is IEEE 754.
 *
 * @return 16-bit float 2-vector.
 */
port_uint16_v2_t
port_convert_float32_to_float16_v2(
        port_float32_v2_t value ///< [in] 32-bit float vector.
);

/**
 * @brief Convert 2-vector of single-width floating-point numbers to half-width.
 *
 * Format of float16 is IEEE 754.
 *
 * @return Half-width float 2-vector.
 */
#define port_convert_floats_to_floath_v2 port_convert_float32_to_float16_v2

/**
 * @brief Convert 3-vector of 32-bit floating-point numbers to 16-bit.
 *
 * Format of float16 is IEEE 754.
 *
 * @return 16-bit float 3-vector.
 */
port_uint16_v3_t
port_convert_float32_to_float16_v3(
        port_float32_v3_t value ///< [in] 32-bit float vector.
);

/**
 * @brief Convert 3-vector of single-width floating-point numbers to half-width.
 *
 * Format of float16 is IEEE 754.
 *
 * @return Half-width float 3-vector.
 */
#define port_convert_floats_to_floath_v3 port_convert_float32_to_float16_v3

/**
 * @brief Convert 4-vector of 32-bit floating-point numbers to 16-bit.
 *
 * Format of float16 is IEEE 754.
 *
 * @return 16-bit float 4-vector.
 */
port_uint16_v4_t
port_convert_float32_to_float16_v4(
        port_float32_v4_t value ///< [in] 32-bit float vector.
);

/**
 * @brief Convert 4-vector of single-width floating-point numbers to half-width.
 *
 * Format of float16 is IEEE 754.
 *
 * @return Half-width float 4-vector.
 */
#define port_convert_floats_to_floath_v4 port_convert_float32_to_float16_v4

/**
 * @brief Convert 8-vector of 32-bit floating-point numbers to 16-bit.
 *
 * Format of float16 is IEEE 754.
 *
 * @return 16-bit float 8-vector.
 */
port_uint16_v8_t
port_convert_float32_to_float16_v8(
        port_float32_v8_t value ///< [in] 32-bit float vector.
);

/**
 * @brief Convert 8-vector of single-width floating-point numbers to half-width.
 *
 * Format of float16 is IEEE 754.
 *
 * @return Half-width float 8-vector.
 */
#define port_convert_floats_to_floath_v8 port_convert_float32_to_float16_v8

/**
 * @brief Convert 16-vector of 32-bit floating-point numbers to 16-bit.
 *
 * Format of float16 is IEEE 754.
 *
 * @return 16-bit float 16-vector.
 */
port_uint16_v16_t
port_convert_float32_to_float16_v16(
        port_float32_v16_t value ///< [in] 32-bit float vector.
);

/**
 * @brief Convert 16-vector of single-width floating-point numbers to half-width.
 *
 * Format of float16 is IEEE 754.
 *
 * @return Half-width float 16-vector.
 */
#define port_convert_floats_to_floath_v16 port_convert_float32_to_float16_v16

#endif // _PORT_FLOAT_FUN_H_

