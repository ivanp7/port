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
 * @brief Pseudorandom number generation.
 */

#pragma once
#ifndef _PORT_RANDOM_FUN_H_
#define _PORT_RANDOM_FUN_H_

#include "port/random.typ.h"


///////////////////////////////////////////////////////////////////////////////
// Pseudorandom number generator
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Generate next pseudorandom 32-bit unsigned integer.
 *
 * @return Next pseudorandom unsigned integer.
 */
port_random_t
port_random_next(
        port_random_t prev ///< [in] Previous pseudorandom unsigned integer.
);

///////////////////////////////////////////////////////////////////////////////
// Pseudorandom numbers
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Generate pseudorandom 32-bit unsigned integer.
 *
 * @return 32-bit unsigned integer.
 */
port_uint32_t
port_random_uint32(
        port_random_t *rnd ///< [in,out] Pseudorandom number generator state.
);

/**
 * @brief Generate pseudorandom single-width unsigned integer.
 *
 * @return Single-width unsigned integer.
 */
#define port_random_uints   port_random_uint32

/**
 * @brief Generate pseudorandom 64-bit unsigned integer.
 *
 * @return 64-bit unsigned integer.
 */
port_uint64_t
port_random_uint64(
        port_random_t *rnd ///< [in,out] Pseudorandom number generator state.
);

/**
 * @brief Generate pseudorandom double-width unsigned integer.
 *
 * @return Double-width unsigned integer.
 */
#define port_random_uintd   port_random_uint64

/**
 * @brief Generate pseudorandom 32-bit floating-point number.
 *
 * @return 32-bit floating-point number in [0; 1).
 */
port_float32_t
port_random_float32(
        port_random_t *rnd ///< [in,out] Pseudorandom number generator state.
);

/**
 * @brief Generate pseudorandom single-width floating-point number.
 *
 * @return Single-width floating-point number in [0; 1).
 */
#define port_random_floats  port_random_float32

/**
 * @brief Generate pseudorandom 64-bit floating-point number.
 *
 * @return 64-bit floating-point number in [0; 1).
 */
port_float64_t
port_random_float64(
        port_random_t *rnd ///< [in,out] Pseudorandom number generator state.
);

/**
 * @brief Generate pseudorandom double-width floating-point number.
 *
 * @return Double-width floating-point number in [0; 1).
 */
#define port_random_floatd  port_random_float64

///////////////////////////////////////////////////////////////////////////////
// Low-discrepancy sequences
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Compute a 32-bit floating-point element of a low-discrepancy sequence.
 *
 * The irrational number must be in (0; 1).
 *
 * @return 32-bit floating-point number in [0; 1).
 */
port_float32_t
port_random_float32_low_discr_seq(
        port_uint32_t seq_index, ///< [in] Index of a low-discrepancy sequence element.
        port_float32_t irrational ///< [in] An irrational number defining the sequence.
);

/**
 * @brief Compute a single-width floating-point element of a low-discrepancy sequence.
 *
 * The irrational number must be in (0; 1).
 *
 * @return Single-width floating-point number in [0; 1).
 */
#define port_random_floats_low_discr_seq    port_random_float32_low_discr_seq

/**
 * @brief Compute a 64-bit floating-point element of a low-discrepancy sequence.
 *
 * The irrational number must be in (0; 1).
 *
 * @return 64-bit floating-point number in [0; 1).
 */
port_float64_t
port_random_float64_low_discr_seq(
        port_uint64_t seq_index, ///< [in] Index of a low-discrepancy sequence element.
        port_float64_t irrational ///< [in] An irrational number defining the sequence.
);

/**
 * @brief Compute a double-width floating-point element of a low-discrepancy sequence.
 *
 * The irrational number must be in (0; 1).
 *
 * @return Double-width floating-point number in [0; 1).
 */
#define port_random_floatd_low_discr_seq    port_random_float64_low_discr_seq

///////////////////////////////////////////////////////////////////////////////
// Pseudorandom integers with custom distribution
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Pick an outcome with custom distribution (8-bit CDF values).
 *
 * Number of CDF values must be less than number of outcomes by 1.
 * Pointer to CDF array may be set to NULL, which enables the uniform distribution.
 *
 * CDF must be a monotonic (non-decreasing) sequence.
 * The chosen index is the first one which satisfies the following condition:
 * cdf[index] > random_number, where 0 <= index < num_outcomes - 1.
 * If cdf[index] <= random_number for all such index values, then num_outcomes - 1 is returned.
 *
 * @warning num_outcomes cannot be 0.
 *
 * @return Index of a chosen outcome.
 */
port_uint8_t
port_random_custom_distrib_uint8(
        port_uint8_t num_outcomes, ///< [in] Number of outcomes.
        const port_uint8_t cdf[],  ///< [in] Cumulative distribution function.
        port_random_t *rnd ///< [in,out] Pseudorandom integer.
);

/**
 * @brief Pick an outcome with custom distribution (quarter-width CDF values).
 *
 * @see port_random_custom_distrib_uint8()
 *
 * @return Index of a chosen outcome.
 */
#define port_random_custom_distrib_uintq    port_random_custom_distrib_uint8

/**
 * @brief Pick an outcome with custom distribution (16-bit CDF values).
 *
 * @see port_random_custom_distrib_uint8()
 *
 * @return Index of a chosen outcome.
 */
port_uint16_t
port_random_custom_distrib_uint16(
        port_uint16_t num_outcomes, ///< [in] Number of outcomes.
        const port_uint16_t cdf[],  ///< [in] Cumulative distribution function.
        port_random_t *rnd ///< [in,out] Pseudorandom integer.
);

/**
 * @brief Pick an outcome with custom distribution (half-width CDF values).
 *
 * @see port_random_custom_distrib_uint8()
 *
 * @return Index of a chosen outcome.
 */
#define port_random_custom_distrib_uinth    port_random_custom_distrib_uint16

/**
 * @brief Pick an outcome with custom distribution (32-bit CDF values).
 *
 * @see port_random_custom_distrib_uint8()
 *
 * @return Index of a chosen outcome.
 */
port_uint32_t
port_random_custom_distrib_uint32(
        port_uint32_t num_outcomes, ///< [in] Number of outcomes.
        const port_uint32_t cdf[],  ///< [in] Cumulative distribution function.
        port_random_t *rnd ///< [in,out] Pseudorandom integer.
);

/**
 * @brief Pick an outcome with custom distribution (single-width CDF values).
 *
 * @see port_random_custom_distrib_uint8()
 *
 * @return Index of a chosen outcome.
 */
#define port_random_custom_distrib_uints    port_random_custom_distrib_uint32

#endif // _PORT_RANDOM_FUN_H_

