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

#include "port/random.fun.h"
#include "port/bit.def.h"

#ifndef __OPENCL_C_VERSION__
#  include <assert.h>
#endif

port_random_t
port_random_next(
        port_random_t prev)
{
    // Constants are taken from "Numerical recipies in C. The art of scientific computing"
    return (port_random_t)1664525u * prev + (port_random_t)1013904223u;
}

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
    } u = {.as_uint32 = (rnd_local & (port_random_t)0x007FFFFFu) | (port_random_t)0x3F800000u};

    return u.as_float32 - 1.0f;
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
    } u = {.as_uint64 = PORT_UPSAMPLE32((rnd_local1 & (port_random_t)0x000FFFFFu) |
            (port_random_t)0x3FF00000u, rnd_local2)};

    return u.as_float64 - 1.0;
}

port_uint_quarter_t
port_random_custom_distrib_uint_quarter(
        port_uint_quarter_t num_outcomes,
        const port_uint_quarter_t cdf[],
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
    port_uint_quarter_t random_value = rnd_local;

    // Binary search
    port_uint_quarter_t low = 0, high = num_outcomes - 2; // [0; num_outcomes-1) or [0; num_outcomes-2]
    while (low < high)
    {
        port_uint_quarter_t mid = low + (high - low) / 2;

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

port_uint_half_t
port_random_custom_distrib_uint_half(
        port_uint_half_t num_outcomes,
        const port_uint_half_t cdf[],
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
    port_uint_half_t random_value = rnd_local;

    // Binary search
    port_uint_half_t low = 0, high = num_outcomes - 2; // [0; num_outcomes-1) or [0; num_outcomes-2]
    while (low < high)
    {
        port_uint_half_t mid = low + (high - low) / 2;

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

port_uint_single_t
port_random_custom_distrib_uint_single(
        port_uint_single_t num_outcomes,
        const port_uint_single_t cdf[],
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
    port_uint_single_t random_value = rnd_local;

    // Binary search
    port_uint_single_t low = 0, high = num_outcomes - 2; // [0; num_outcomes-1) or [0; num_outcomes-2]
    while (low < high)
    {
        port_uint_single_t mid = low + (high - low) / 2;

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

