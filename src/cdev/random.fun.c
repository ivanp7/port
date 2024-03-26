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

#include <port/cdev/random.fun.h>
#include <port/cdev/bit.def.h>

#ifndef __OPENCL_C_VERSION__
#  include <assert.h>
#endif

port_uint32_t
port_random_uint32(
        port_uint32_t prev)
{
    // Constants are taken from "Numerical recipies in C. The art of scientific computing"
    return (port_uint32_t)1664525u * prev + (port_uint32_t)1013904223u;
}

port_uint64_t
port_random_uint64(
        port_uint32_t *rnd)
{
#ifndef __OPENCL_C_VERSION__
    assert(rnd != NULL);
#endif

    port_uint32_t rnd_local = *rnd;
    port_uint64_t result = rnd_local;
    rnd_local = port_random_uint32(rnd_local);
    result = (result << 32) | rnd_local;
    *rnd = port_random_uint32(rnd_local);

    return result;
}

port_uint_t
port_random_uint(
        port_uint32_t *rnd)
{
#ifndef __OPENCL_C_VERSION__
    assert(rnd != NULL);
#endif

#ifndef PORT_FEATURE_DEFAULT_INTEGER_64
    port_uint32_t rnd_local = *rnd;
    *rnd = port_random_uint32(rnd_local);
    return rnd_local;
#else
    return port_random_uint64(rnd);
#endif
}

port_float32_t
port_random_float32(
        port_uint32_t *rnd)
{
#ifndef __OPENCL_C_VERSION__
    assert(rnd != NULL);
#endif

    // Hack is taken from "Numerical recipies in C. The art of scientific computing"
    port_uint32_t rnd_local = *rnd;
    *rnd = port_random_uint32(rnd_local);

    union {
        port_uint32_t as_uint32;
        port_float32_t as_float32;
    } u = {.as_uint32 = (rnd_local & (port_uint32_t)0x007FFFFFu) | (port_uint32_t)0x3F800000u};

    return u.as_float32 - 1.0f;
}

port_float64_t
port_random_float64(
        port_uint32_t *rnd)
{
#ifndef __OPENCL_C_VERSION__
    assert(rnd != NULL);
#endif

    port_uint32_t rnd_local1 = *rnd;
    port_uint32_t rnd_local2 = port_random_uint32(rnd_local1);
    *rnd = port_random_uint32(rnd_local2);

    union {
        port_uint64_t as_uint64;
        port_float64_t as_float64;
    } u = {.as_uint64 = PORT_UPSAMPLE32((rnd_local1 & (port_uint32_t)0x000FFFFFu) |
            (port_uint32_t)0x3FF00000u, rnd_local2)};

    return u.as_float64 - 1.0;
}

port_uint8_t
port_random_set_bit_quarter(
        port_uint_single_t mask,
        port_const_memory_ptr_t thresholds,

        port_uint32_t *rnd)
{
#ifndef __OPENCL_C_VERSION__
    assert(rnd != NULL);
#endif

    if (mask == 0)
        return PORT_NUM_BITS(mask); // lowest invalid bit number

    port_uint8_t num_bits = PORT_POPCOUNT(mask);

    port_uint32_t rnd_local = *rnd;
    *rnd = port_random_uint32(rnd_local);

    if (thresholds != NULL)
    {
        port_memory_unit_t unit = {0};
        port_uint_quarter_t threshold;
#ifndef __OPENCL_C_VERSION__
#  ifndef NDEBUG
        port_uint_quarter_t prev_threshold = 0;
#  endif
#endif

        rnd_local &= PORT_NZMASK32(PORT_NUM_BITS(threshold));

        // Iterate unless random number is less than threshold
        for (port_uint8_t i = 0; i < num_bits-1; i++)
        {
            if (i % 4 == 0)
                unit = thresholds[i / 4];

            threshold = unit.as_uint_quarter[i % 4];

#ifndef __OPENCL_C_VERSION__
#  ifndef NDEBUG
            assert(prev_threshold <= threshold);
            prev_threshold = threshold;
#  endif
#endif

            if (rnd_local < threshold)
                break;

            // Clear least significant 1-bit
            mask &= mask - 1;
        }
    }
    else
    {
        // Clear uniformly chosen number of least significant 1-bits
        for (port_uint8_t i = rnd_local % num_bits; i > 0; i--)
            mask &= mask - 1;
    }

    return PORT_CTZ(mask);
}

port_uint8_t
port_random_set_bit_half(
        port_uint_single_t mask,
        port_const_memory_ptr_t thresholds,

        port_uint32_t *rnd)
{
#ifndef __OPENCL_C_VERSION__
    assert(rnd != NULL);
#endif

    if (mask == 0)
        return PORT_NUM_BITS(mask); // lowest invalid bit number

    port_uint8_t num_bits = PORT_POPCOUNT(mask);

    port_uint32_t rnd_local = *rnd;
    *rnd = port_random_uint32(rnd_local);

    if (thresholds != NULL)
    {
        port_memory_unit_t unit = {0};
        port_uint_half_t threshold;
#ifndef __OPENCL_C_VERSION__
#  ifndef NDEBUG
        port_uint_half_t prev_threshold = 0;
#  endif
#endif

        rnd_local &= PORT_NZMASK32(PORT_NUM_BITS(threshold));

        // Iterate unless random number is less than threshold
        for (port_uint8_t i = 0; i < num_bits-1; i++)
        {
            if (i % 2 == 0)
                unit = thresholds[i / 2];

            threshold = unit.as_uint_half[i % 2];

#ifndef __OPENCL_C_VERSION__
#  ifndef NDEBUG
            assert(prev_threshold <= threshold);
            prev_threshold = threshold;
#  endif
#endif

            if (rnd_local < threshold)
                break;

            // Clear least significant 1-bit
            mask &= mask - 1;
        }
    }
    else
    {
        // Clear uniformly chosen number of least significant 1-bits
        for (port_uint8_t i = rnd_local % num_bits; i > 0; i--)
            mask &= mask - 1;
    }

    return PORT_CTZ(mask);
}

