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
 * @brief Operations on floating-point numbers.
 */

#pragma once
#ifndef _PORT_FLOAT_FUN_H_
#define _PORT_FLOAT_FUN_H_

#include "port/types.typ.h"

///////////////////////////////////////////////////////////////////////////////
// ULP distance between floating-point numbers
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Calculate distance between 32-bit floating-point numbers in ULPs.
 *
 * If either of values is infinity or NaN, the maximum value is returned.
 *
 * @return ULP distance.
 */
port_uint32_t
port_float32_ulp_distance(
        port_float32_t value1,
        port_float32_t value2
);

/**
 * @brief Calculate distance between 64-bit floating-point numbers in ULPs.
 *
 * If either of values is infinity or NaN, the maximum value is returned.
 *
 * @return ULP distance.
 */
port_uint64_t
port_float64_ulp_distance(
        port_float64_t value1,
        port_float64_t value2
);

#ifndef PORT_FEATURE_DEFAULT_FLOAT_64
#  define port_float_ulp_distance port_float32_ulp_distance
#else
#  define port_float_ulp_distance port_float64_ulp_distance
#endif

///////////////////////////////////////////////////////////////////////////////
// float16 -> float32 conversions
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
// float32 -> float16 conversions
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

#endif // _PORT_FLOAT_FUN_H_

