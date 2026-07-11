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

#include "port/random.fun.h"
#include "port/bit.def.h"
#include "port/types.def.h"

#ifndef __OPENCL_C_VERSION__
#  include <tgmath.h>
#  include <assert.h>
#endif


///////////////////////////////////////////////////////////////////////////////
// Pseudorandom number generator
///////////////////////////////////////////////////////////////////////////////

port_random_t
port_random_next(
        port_random_t prev)
{
    // Constants are taken from "Numerical recipies in C. The art of scientific computing"
    return (port_random_t)PORT_UINT32(1664525) * prev + (port_random_t)PORT_UINT32(1013904223);
}

///////////////////////////////////////////////////////////////////////////////
// Pseudorandom numbers
///////////////////////////////////////////////////////////////////////////////

port_uint32_t
port_random_uint32(
        port_random_t *rnd)
{
#ifndef __OPENCL_C_VERSION__
    assert(rnd != NULL);
#endif

    port_random_t rnd_local = *rnd;
    rnd_local = port_random_next(rnd_local);
    *rnd = rnd_local;

    return rnd_local;
}

port_uint64_t
port_random_uint64(
        port_random_t *rnd)
{
#ifndef __OPENCL_C_VERSION__
    assert(rnd != NULL);
#endif

    port_random_t rnd_local = *rnd;
    port_uint64_t result = rnd_local;
    rnd_local = port_random_next(rnd_local);
    result = (result << 32) | rnd_local;
    *rnd = port_random_next(rnd_local);

    return result;
}

port_float32_t
port_random_float32(
        port_random_t *rnd)
{
#ifndef __OPENCL_C_VERSION__
    assert(rnd != NULL);
#endif

    // Hack is taken from "Numerical recipies in C. The art of scientific computing"
    port_random_t rnd_local = *rnd;
    *rnd = port_random_next(rnd_local);

    union {
        port_random_t as_uint32;
        port_float32_t as_float32;
    } u = {.as_uint32 = (rnd_local & (port_random_t)PORT_UINT32(0x007FFFFF)) |
        (port_random_t)PORT_UINT32(0x3F800000)};

    return u.as_float32 - PORT_FLOAT32(1.0);
}

port_float64_t
port_random_float64(
        port_random_t *rnd)
{
#ifndef __OPENCL_C_VERSION__
    assert(rnd != NULL);
#endif

    port_random_t rnd_local1 = *rnd;
    port_random_t rnd_local2 = port_random_next(rnd_local1);
    *rnd = port_random_next(rnd_local2);

    union {
        port_uint64_t as_uint64;
        port_float64_t as_float64;
    } u = {.as_uint64 = PORT_UPSAMPLE32((rnd_local1 & (port_random_t)PORT_UINT32(0x000FFFFF)) |
            (port_random_t)PORT_UINT32(0x3FF00000), rnd_local2)};

    return u.as_float64 - PORT_FLOAT64(1.0);
}

///////////////////////////////////////////////////////////////////////////////
// Low-discrepancy sequences
///////////////////////////////////////////////////////////////////////////////

port_float32_t
port_random_float32_low_discr_seq(
        port_uint32_t seq_index,
        port_float32_t irrational)
{
#ifndef __OPENCL_C_VERSION__
    assert((irrational > PORT_FLOAT32(0.0)) && (irrational < PORT_FLOAT32(1.0)));
#endif

    port_float32_t v = seq_index & PORT_ZMASK32(24); // all integers up to 2^24 are representable in float32

    v = fma(v, irrational, -floor(v * irrational));
    if (v < PORT_FLOAT32(0.0))
        v += PORT_FLOAT32(1.0);

    return v;
}

port_float64_t
port_random_float64_low_discr_seq(
        port_uint64_t seq_index,
        port_float64_t irrational)
{
#ifndef __OPENCL_C_VERSION__
    assert((irrational > PORT_FLOAT64(0.0)) && (irrational < PORT_FLOAT64(1.0)));
#endif

    port_float64_t v = seq_index & PORT_ZMASK64(53); // all integers up to 2^53 are representable in float64

    v = fma(v, irrational, -floor(v * irrational));
    if (v < PORT_FLOAT64(0.0))
        v += PORT_FLOAT64(1.0);

    return v;
}

///////////////////////////////////////////////////////////////////////////////
// Pseudorandom integers with custom distribution
///////////////////////////////////////////////////////////////////////////////

port_uint8_t
port_random_custom_distrib_uint8(
        port_uint8_t num_outcomes,
        const port_uint8_t cdf[],
        port_random_t *rnd)
{
#ifndef __OPENCL_C_VERSION__
    assert(num_outcomes != 0);
    assert(rnd != NULL);
#endif

    if (num_outcomes == 1) // no randomness
        return 0;

    port_random_t rnd_local = *rnd;
    *rnd = port_random_next(rnd_local);

    if (cdf == NULL) // uniform distribution
        return rnd_local % num_outcomes;

    // Ensure the random number is in the CDF range
    port_uint8_t random_value = rnd_local;

    // Binary search
    port_uint8_t low = 0, high = num_outcomes - 2; // [0; num_outcomes-1) or [0; num_outcomes-2]
    while (low < high)
    {
        port_uint8_t mid = low + (high - low) / 2;

        // We want the smallest index for which (cdf[index] > random_value)
        if (cdf[mid] > random_value) // mid + 1 > index
            high = mid; // cut [mid + 1; high]
        else // mid < index
            low = mid + 1; // cut [low; mid]
    }

    if (cdf[low] > random_value)
        return low;
    else
        return low + 1;
}

port_uint16_t
port_random_custom_distrib_uint16(
        port_uint16_t num_outcomes,
        const port_uint16_t cdf[],
        port_random_t *rnd)
{
#ifndef __OPENCL_C_VERSION__
    assert(num_outcomes != 0);
    assert(rnd != NULL);
#endif

    if (num_outcomes == 1) // no randomness
        return 0;

    port_random_t rnd_local = *rnd;
    *rnd = port_random_next(rnd_local);

    if (cdf == NULL) // uniform distribution
        return rnd_local % num_outcomes;

    // Ensure the random number is in the CDF range
    port_uint16_t random_value = rnd_local;

    // Binary search
    port_uint16_t low = 0, high = num_outcomes - 2; // [0; num_outcomes-1) or [0; num_outcomes-2]
    while (low < high)
    {
        port_uint16_t mid = low + (high - low) / 2;

        // We want the smallest index for which (cdf[index] > random_value)
        if (cdf[mid] > random_value) // mid + 1 > index
            high = mid; // cut [mid + 1; high]
        else // mid < index
            low = mid + 1; // cut [low; mid]
    }

    if (cdf[low] > random_value)
        return low;
    else
        return low + 1;
}

port_uint32_t
port_random_custom_distrib_uint32(
        port_uint32_t num_outcomes,
        const port_uint32_t cdf[],
        port_random_t *rnd)
{
#ifndef __OPENCL_C_VERSION__
    assert(num_outcomes != 0);
    assert(rnd != NULL);
#endif

    if (num_outcomes == 1) // no randomness
        return 0;

    port_random_t rnd_local = *rnd;
    *rnd = port_random_next(rnd_local);

    if (cdf == NULL) // uniform distribution
        return rnd_local % num_outcomes;

    // Ensure the random number is in the CDF range
    port_uint32_t random_value = rnd_local;

    // Binary search
    port_uint32_t low = 0, high = num_outcomes - 2; // [0; num_outcomes-1) or [0; num_outcomes-2]
    while (low < high)
    {
        port_uint32_t mid = low + (high - low) / 2;

        // We want the smallest index for which (cdf[index] > random_value)
        if (cdf[mid] > random_value) // mid + 1 > index
            high = mid; // cut [mid + 1; high]
        else // mid < index
            low = mid + 1; // cut [low; mid]
    }

    if (cdf[low] > random_value)
        return low;
    else
        return low + 1;
}

