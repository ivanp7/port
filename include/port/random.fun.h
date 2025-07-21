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
 * @brief Pseudorandom number generation.
 */

#pragma once
#ifndef _PORT_RANDOM_FUN_H_
#define _PORT_RANDOM_FUN_H_

#include "port/types.typ.h"

/**
 * @brief Maximum possible pseudorandom 32-bit integer.
 */
#define PORT_RANDOM_UINT32_MAX PORT_UINT32_MAX

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
 * @brief Pick an outcome randomly with custom distribution (quarter-unit CDF values).
 *
 * Each CDF value occupies a unit quarter (8 bits), so there are 4 values per unit.
 *
 * Number of CDF values must be less than number of outcomes by 1.
 * Pointer to CDF array may be set to NULL, which enables the uniform distribution.
 *
 * CDF must be a monotonic non-decreasing function.
 * The chosen index is the first one which satisfies the following condition:
 * cdf[index] > random_number, where 0 <= index < num_outcomes - 1.
 * If cdf[index] <= random_number for all such index values, then num_outcomes - 1 is returned.
 *
 * @warning num_outcomes cannot be 0.
 *
 * @return Index of a randomly chosen outcome.
 */
port_uint_quarter_t
port_random_custom_distrib_uint_quarter(
        port_uint_quarter_t num_outcomes, ///< [in] Number of outcomes.
        const port_uint_quarter_t cdf[],  ///< [in] Cumulative distribution function.
        port_uint32_t *rnd ///< [in,out] Pseudorandom integer.
);

/**
 * @brief Pick an outcome randomly with custom distribution (half-unit CDF values).
 *
 * Each CDF value occupies a unit half (16 bits), so there are 2 values per unit.
 *
 * @see port_random_custom_distrib_uint_quarter()
 *
 * @return Index of a randomly chosen outcome.
 */
port_uint_half_t
port_random_custom_distrib_uint_half(
        port_uint_half_t num_outcomes, ///< [in] Number of outcomes.
        const port_uint_half_t cdf[],  ///< [in] Cumulative distribution function.
        port_uint32_t *rnd ///< [in,out] Pseudorandom integer.
);

/**
 * @brief Pick an outcome randomly with custom distribution (single-unit CDF values).
 *
 * Each CDF value occupies a whole unit (32 bits), so there is 1 value per unit.
 *
 * @see port_random_custom_distrib_uint_quarter()
 *
 * @return Index of a randomly chosen outcome.
 */
port_uint_single_t
port_random_custom_distrib_uint_single(
        port_uint_single_t num_outcomes, ///< [in] Number of outcomes.
        const port_uint_single_t cdf[],  ///< [in] Cumulative distribution function.
        port_uint32_t *rnd ///< [in,out] Pseudorandom integer.
);

#endif // _PORT_RANDOM_FUN_H_

