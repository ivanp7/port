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
 * @brief Operations on floating-point numbers.
 */

#pragma once
#ifndef _PORT_CDEV_FLOAT_FUN_H_
#define _PORT_CDEV_FLOAT_FUN_H_

#include <port/cdev/types.typ.h>

///////////////////////////////////////////////////////////////////////////////
// Comparisons
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Check if 32-bit floating-point number is (almost) equal to zero.
 *
 * @return Comparison result.
 */
port_bool_t
port_float32_almost_equal_to_0(
        port_float32_t value ///< [in] Tested value.
);

/**
 * @brief Check if 64-bit floating-point number is (almost) equal to zero.
 *
 * @return Comparison result.
 */
port_bool_t
port_float64_almost_equal_to_0(
        port_float64_t value ///< [in] Tested value.
);

/**
 * @brief Check if 32-bit floating-point number is (almost) equal to one.
 *
 * @return Comparison result.
 */
port_bool_t
port_float32_almost_equal_to_1(
        port_float32_t value ///< [in] Tested value.
);

/**
 * @brief Check if 64-bit floating-point number is (almost) equal to one.
 *
 * @return Comparison result.
 */
port_bool_t
port_float64_almost_equal_to_1(
        port_float64_t value ///< [in] Tested value.
);

/**
 * @brief Check if 32-bit floating-point numbers are (almost) equal.
 *
 * @return Comparison result.
 */
port_bool_t
port_float32_almost_equal(
        port_float32_t value1, ///< [in] First value.
        port_float32_t value2  ///< [in] Second value.
);

/**
 * @brief Check if 64-bit floating-point numbers are (almost) equal.
 *
 * @return Comparison result.
 */
port_bool_t
port_float64_almost_equal(
        port_float64_t value1, ///< [in] First value.
        port_float64_t value2  ///< [in] Second value.
);

#ifndef PORT_FEATURE_DEFAULT_FLOAT_64
#  define port_float_almost_equal_to_0 port_float32_almost_equal_to_0
#  define port_float_almost_equal_to_1 port_float32_almost_equal_to_1
#  define port_float_almost_equal port_float32_almost_equal
#else
#  define port_float_almost_equal_to_0 port_float64_almost_equal_to_0
#  define port_float_almost_equal_to_1 port_float64_almost_equal_to_1
#  define port_float_almost_equal port_float64_almost_equal
#endif

///////////////////////////////////////////////////////////////////////////////
// clamp()
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

#ifndef PORT_FEATURE_DEFAULT_FLOAT_64
#  define port_float_clamp port_float32_clamp
#else
#  define port_float_clamp port_float64_clamp
#endif

///////////////////////////////////////////////////////////////////////////////
// float16 -> float32
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Convert half precision floating-point number to single precision.
 *
 * Format of float16 is IEEE 754.
 *
 * @return Single precision float.
 */
port_float32_t
port_convert_float16_to_float32(
        port_uint16_t value ///< [in] Half precision float value.
);

/**
 * @brief Convert 2-vector of half precision floating-point numbers to single precision.
 *
 * Format of float16 is IEEE 754.
 *
 * @return Single precision float 2-vector.
 */
port_float32_v2_t
port_convert_float16_to_float32_v2(
        port_uint16_v2_t value ///< [in] Half precision float vector.
);

/**
 * @brief Convert 3-vector of half precision floating-point numbers to single precision.
 *
 * Format of float16 is IEEE 754.
 *
 * @return Single precision float 3-vector.
 */
port_float32_v3_t
port_convert_float16_to_float32_v3(
        port_uint16_v3_t value ///< [in] Half precision float vector.
);

/**
 * @brief Convert 4-vector of half precision floating-point numbers to single precision.
 *
 * Format of float16 is IEEE 754.
 *
 * @return Single precision float 4-vector.
 */
port_float32_v4_t
port_convert_float16_to_float32_v4(
        port_uint16_v4_t value ///< [in] Half precision float vector.
);

/**
 * @brief Convert 8-vector of half precision floating-point numbers to single precision.
 *
 * Format of float16 is IEEE 754.
 *
 * @return Single precision float 8-vector.
 */
port_float32_v8_t
port_convert_float16_to_float32_v8(
        port_uint16_v8_t value ///< [in] Half precision float vector.
);

/**
 * @brief Convert 16-vector of half precision floating-point numbers to single precision.
 *
 * Format of float16 is IEEE 754.
 *
 * @return Single precision float 16-vector.
 */
port_float32_v16_t
port_convert_float16_to_float32_v16(
        port_uint16_v16_t value ///< [in] Half precision float vector.
);

///////////////////////////////////////////////////////////////////////////////
// float32 -> float16
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Convert single precision floating-point number to half precision.
 *
 * Format of float16 is IEEE 754.
 *
 * @return Half precision float.
 */
port_uint16_t
port_convert_float32_to_float16(
        port_float32_t value ///< [in] Single precision float value.
);

/**
 * @brief Convert 2-vector of single precision floating-point numbers to half precision.
 *
 * Format of float16 is IEEE 754.
 *
 * @return Half precision float 2-vector.
 */
port_uint16_v2_t
port_convert_float32_to_float16_v2(
        port_float32_v2_t value ///< [in] Single precision float vector.
);

/**
 * @brief Convert 3-vector of single precision floating-point numbers to half precision.
 *
 * Format of float16 is IEEE 754.
 *
 * @return Half precision float 3-vector.
 */
port_uint16_v3_t
port_convert_float32_to_float16_v3(
        port_float32_v3_t value ///< [in] Single precision float vector.
);

/**
 * @brief Convert 4-vector of single precision floating-point numbers to half precision.
 *
 * Format of float16 is IEEE 754.
 *
 * @return Half precision float 4-vector.
 */
port_uint16_v4_t
port_convert_float32_to_float16_v4(
        port_float32_v4_t value ///< [in] Single precision float vector.
);

/**
 * @brief Convert 8-vector of single precision floating-point numbers to half precision.
 *
 * Format of float16 is IEEE 754.
 *
 * @return Half precision float 8-vector.
 */
port_uint16_v8_t
port_convert_float32_to_float16_v8(
        port_float32_v8_t value ///< [in] Single precision float vector.
);

/**
 * @brief Convert 16-vector of single precision floating-point numbers to half precision.
 *
 * Format of float16 is IEEE 754.
 *
 * @return Half precision float 16-vector.
 */
port_uint16_v16_t
port_convert_float32_to_float16_v16(
        port_float32_v16_t value ///< [in] Single precision float vector.
);

#endif // _PORT_CDEV_FLOAT_FUN_H_

