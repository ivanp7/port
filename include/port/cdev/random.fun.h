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
 * @brief Pseudorandom number generation.
 */

#pragma once
#ifndef _PORT_CDEV_RANDOM_FUN_H_
#define _PORT_CDEV_RANDOM_FUN_H_

#include <port/cdev/memory.typ.h>

/**
 * @brief Generate next pseudorandom 32-bit unsigned integer.
 *
 * @return Next pseudorandom unsigned integer.
 */
port_uint32_t
port_random_uint32(
        port_uint32_t prev ///< [in] Previous pseudorandom unsigned integer.
);

/**
 * @brief Generate pseudorandom 64-bit unsigned integer.
 *
 * @return 64-bit unsigned integer.
 */
port_uint64_t
port_random_uint64(
        port_uint32_t *rnd ///< [in,out] Pseudorandom number generator state.
);

/**
 * @brief Generate pseudorandom unsigned integer.
 *
 * @return Unsigned integer.
 */
port_uint_t
port_random_uint(
        port_uint32_t *rnd ///< [in,out] Pseudorandom number generator state.
);

/**
 * @brief Generate 32-bit floating-point number uniformly distributed over [0; 1).
 *
 * @return 32-bit floating-point number.
 */
port_float32_t
port_random_float32(
        port_uint32_t *rnd ///< [in,out] Pseudorandom number generator state.
);

/**
 * @brief Generate 64-bit floating-point number uniformly distributed over [0; 1).
 *
 * @return 64-bit floating-point number.
 */
port_float64_t
port_random_float64(
        port_uint32_t *rnd ///< [in,out] Pseudorandom number generator state.
);

#ifndef PORT_FEATURE_DEFAULT_FLOAT_64
#  define port_random_float port_random_float32
#else
#  define port_random_float port_random_float64
#endif

/**
 * @brief Pick a set bit from a mask randomly, using quarter-unit thresholds.
 *
 * Each threshold number consumes a quarter of unit (8 bits), so
 * there are 4 thresholds per unit.
 * Number of thresholds is less than number of set bits by 1.
 * Thresholds memory may be set to NULL, in that case bits are picked uniformly.
 *
 * If mask is 0, the lowest invalid bit number is returned.
 *
 * @return Number of selected bit.
 */
port_uint8_t
port_random_set_bit_quarter(
        port_uint_single_t mask, ///< [in] Mask of allowed bits to pick.
        port_const_memory_ptr_t thresholds, ///< [in] Sequence of thresholds.

        port_uint32_t *rnd ///< [in,out] Pseudorandom integer.
);

/**
 * @brief Pick a set bit from a mask randomly, using half-unit thresholds.
 *
 * Each threshold number consumes a half of unit (16 bits), so
 * there are 2 thresholds per unit.
 * Number of thresholds is less than number of set bits by 1.
 * Thresholds memory may be set to NULL, in that case bits are picked uniformly.
 *
 * If mask is 0, the lowest invalid bit number is returned.
 *
 * @return Number of selected bit.
 */
port_uint8_t
port_random_set_bit_half(
        port_uint_single_t mask, ///< [in] Mask of allowed bits to pick.
        port_const_memory_ptr_t thresholds, ///< [in] Sequence of thresholds.

        port_uint32_t *rnd ///< [in,out] Pseudorandom integer.
);

#endif // _PORT_CDEV_RANDOM_FUN_H_

