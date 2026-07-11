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
 * @brief Macros for bit operations.
 */

#pragma once
#ifndef _PORT_BIT_DEF_H_
#define _PORT_BIT_DEF_H_

#include "port/types.typ.h"


///////////////////////////////////////////////////////////////////////////////
// Sizes of types
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Number of bits in a byte.
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_CHAR_BIT CHAR_BIT
#else
#  define PORT_CHAR_BIT CL_CHAR_BIT
#endif

/**
 * @brief Total number of bits used by a type.
 */
#define PORT_SIZEOF_BITS(type)  (sizeof(type) * PORT_CHAR_BIT)

/**
 * @brief Binary logarithm of size of a quarter-width type.
 */
#define PORT_SIZEOF_LOG2__Q  0
/**
 * @brief Binary logarithm of size of a half-width type.
 */
#define PORT_SIZEOF_LOG2__H  1
/**
 * @brief Binary logarithm of size of a single-width type.
 */
#define PORT_SIZEOF_LOG2__S  2
/**
 * @brief Binary logarithm of size of a double-width type.
 */
#define PORT_SIZEOF_LOG2__D  3

/**
 * @brief Binary logarithm of size of a maximum-width type.
 */
#define PORT_SIZEOF_LOG2__W  PORT_SIZEOF_LOG2__D

/**
 * @brief Minimum number of bits required to store log2(sizeof(type)).
 */
#define PORT_SIZEOF_LOG2_NUM_BITS  2

/**
 * @brief Calculate size of a type from log2(size).
 */
#define PORT_SIZEOF_EXP2(sizeof_log2)   ((size_t)1 << (sizeof_log2))

///////////////////////////////////////////////////////////////////////////////
// Operations on integers
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Round an unsigned integer up to the smallest number divisible by (1 << unit_bits).
 */
#define PORT_UINT_ROUND_UP(type, value, unit_bits) \
    (((type)(value) + ((type)1 << (unit_bits)) - 1) & ~(((type)1 << (unit_bits)) - 1))

/**
 * @brief Calculate minimum number of units greater than or equal to a value.
 *
 * This expression is equal to `PORT_UINT_ROUND_UP(value, unit_bits) / (1 << unit_bits)`.
 */
#define PORT_UINT_NUM_UNITS(type, value, unit_bits) \
    (((type)(value) + ((type)1 << (unit_bits)) - 1) >> (unit_bits))

///////////////////////////////////////////////////////////////////////////////
// Masks
///////////////////////////////////////////////////////////////////////////////

#define PORT_BIT8(n)  ((port_uint8_t)1 << (n))  ///< 8-bit mask with nth bit set.
#define PORT_BIT16(n) ((port_uint16_t)1 << (n)) ///< 16-bit mask with nth bit set.
#define PORT_BIT32(n) ((port_uint32_t)1 << (n)) ///< 32-bit mask with nth bit set.
#define PORT_BIT64(n) ((port_uint64_t)1 << (n)) ///< 64-bit mask with nth bit set.

#define PORT_ZMASK8(n)  (PORT_BIT8(n) - 1)  ///< 8-bit mask with 0<=n<8 lower bits set.
#define PORT_ZMASK16(n) (PORT_BIT16(n) - 1) ///< 16-bit mask with 0<=n<16 lower bits set.
#define PORT_ZMASK32(n) (PORT_BIT32(n) - 1) ///< 32-bit mask with 0<=n<32 lower bits set.
#define PORT_ZMASK64(n) (PORT_BIT64(n) - 1) ///< 64-bit mask with 0<=n<64 lower bits set.

#define PORT_NZMASK8(n)  ((port_uint8_t)-1 >> (8 - (n)))   ///< 8-bit mask with 0<n<=8 lower bits set.
#define PORT_NZMASK16(n) ((port_uint16_t)-1 >> (16 - (n))) ///< 16-bit mask with 0<n<=16 lower bits set.
#define PORT_NZMASK32(n) ((port_uint32_t)-1 >> (32 - (n))) ///< 32-bit mask with 0<n<=32 lower bits set.
#define PORT_NZMASK64(n) ((port_uint64_t)-1 >> (64 - (n))) ///< 64-bit mask with 0<n<=64 lower bits set.

#define PORT_BITQ(n) PORT_BIT8(n)  ///< Quarter-width mask with nth bit set.
#define PORT_BITH(n) PORT_BIT16(n) ///< Half-width mask with nth bit set.
#define PORT_BITS(n) PORT_BIT32(n) ///< Single-width mask with nth bit set.
#define PORT_BITD(n) PORT_BIT64(n) ///< Double-width mask with nth bit set.

#define PORT_ZMASKQ(n) PORT_ZMASK8(n)  ///< Quarter-width mask with 0<=n<8 lower bits set.
#define PORT_ZMASKH(n) PORT_ZMASK16(n) ///< Half-width mask with 0<=n<16 lower bits set.
#define PORT_ZMASKS(n) PORT_ZMASK32(n) ///< Single-width mask with 0<=n<32 lower bits set.
#define PORT_ZMASKD(n) PORT_ZMASK64(n) ///< Double-width mask with 0<=n<64 lower bits set.

#define PORT_NZMASKQ(n) PORT_NZMASK8(n)  ///< Quarter-width mask with 0<n<=8 lower bits set.
#define PORT_NZMASKH(n) PORT_NZMASK16(n) ///< Half-width mask with 0<n<=16 lower bits set.
#define PORT_NZMASKS(n) PORT_NZMASK32(n) ///< Single-width mask with 0<n<=32 lower bits set.
#define PORT_NZMASKD(n) PORT_NZMASK64(n) ///< Double-width mask with 0<n<=64 lower bits set.

///////////////////////////////////////////////////////////////////////////////
// Operations on bits
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Construct an octet from separate bits.
 */
#define PORT_OCTET(msb, b6, b5, b4, b3, b2, b1, lsb) \
    (((port_uint8_t)!!(lsb)) |      \
     ((port_uint8_t)!!(b1) << 1) |  \
     ((port_uint8_t)!!(b2) << 2) |  \
     ((port_uint8_t)!!(b3) << 3) |  \
     ((port_uint8_t)!!(b4) << 4) |  \
     ((port_uint8_t)!!(b5) << 5) |  \
     ((port_uint8_t)!!(b6) << 6) |  \
     ((port_uint8_t)!!(msb) << 7))

/**
 * @brief Concatenate bits.
 *
 * lsval must be no longer than 'shift' bits.
 */
#define PORT_BIT_CONCAT(type, msval, shift, lsval) \
    (((type)(msval) << (shift)) | (type)(lsval))

/**
 * @brief Extract most significant bits.
 */
#define PORT_BIT_EXTRACT_MS(type, value, shift) \
    ((type)((value) >> (shift)))
/**
 * @brief Extract least significant bits.
 */
#define PORT_BIT_EXTRACT_LS(type, value, length) \
    ((type)(value) & (((type)1 << (length)) - 1))
/**
 * @brief Extract bits.
 */
#define PORT_BIT_EXTRACT(type, value, shift, length) \
    PORT_BIT_EXTRACT_LS(type, PORT_BIT_EXTRACT_MS(type, (value), (shift)), (length))

///////////////////////////////////////////////////////////////////////////////
// upsample()
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Make 16-bit unsigned integer from two 8-bit unsigned integers.
 */
#if defined(__OPENCL_C_VERSION__)
#  define PORT_UPSAMPLE8(hi, lo) upsample((port_uint8_t)(hi), (port_uint8_t)(lo))
#else
#  define PORT_UPSAMPLE8(hi, lo) (((port_uint16_t)(hi) << 8) | (port_uint16_t)(lo))
#endif

/**
 * @brief Make half-width unsigned integer from two quarter-width unsigned integers.
 */
#define PORT_UPSAMPLEQ(hi, lo)  PORT_UPSAMPLE8((hi), (lo))

/**
 * @brief Make 32-bit unsigned integer from two 16-bit unsigned integers.
 */
#if defined(__OPENCL_C_VERSION__)
#  define PORT_UPSAMPLE16(hi, lo) upsample((port_uint16_t)(hi), (port_uint16_t)(lo))
#else
#  define PORT_UPSAMPLE16(hi, lo) (((port_uint32_t)(hi) << 16) | (port_uint32_t)(lo))
#endif

/**
 * @brief Make single-width unsigned integer from two half-width unsigned integers.
 */
#define PORT_UPSAMPLEH(hi, lo)  PORT_UPSAMPLE16((hi), (lo))

/**
 * @brief Make 64-bit unsigned integer from two 32-bit unsigned integers.
 */
#if defined(__OPENCL_C_VERSION__)
#  define PORT_UPSAMPLE32(hi, lo) upsample((port_uint32_t)(hi), (port_uint32_t)(lo))
#else
#  define PORT_UPSAMPLE32(hi, lo) (((port_uint64_t)(hi) << 32) | (port_uint64_t)(lo))
#endif

/**
 * @brief Make double-width unsigned integer from two single-width unsigned integers.
 */
#define PORT_UPSAMPLES(hi, lo)  PORT_UPSAMPLE32((hi), (lo))

///////////////////////////////////////////////////////////////////////////////
// popcount()
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Number of set bits in 8-bit unsigned integer.
 */
#if defined(__OPENCL_C_VERSION__)
#  define PORT_POPCOUNT8(n) popcount((port_uint8_t)(n))
#elif defined(__GNUC__)
#  define PORT_POPCOUNT8(n) __builtin_popcount((port_uint8_t)(n))
#else
static inline
port_uint8_t
PORT_POPCOUNT8(
        port_uint8_t n)
{
    return (port_uint8_t[256]){
        0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
    }[n];
}
#endif

/**
 * @brief Number of set bits in quarter-width unsigned integer.
 */
#define PORT_POPCOUNTQ(n)   PORT_POPCOUNT8((n))

/**
 * @brief Number of set bits in 16-bit unsigned integer.
 */
#if defined(__OPENCL_C_VERSION__)
#  define PORT_POPCOUNT16(n) popcount((port_uint16_t)(n))
#elif defined(__GNUC__)
#  define PORT_POPCOUNT16(n) __builtin_popcount((port_uint16_t)(n))
#else
#  define PORT_POPCOUNT16(n) (PORT_POPCOUNT8((port_uint8_t)(n) >> 8) + \
        PORT_POPCOUNT8((port_uint8_t)(n) & (port_uint8_t)0xFF))
#endif

/**
 * @brief Number of set bits in half-width unsigned integer.
 */
#define PORT_POPCOUNTH(n)   PORT_POPCOUNT16((n))

/**
 * @brief Number of set bits in 32-bit unsigned integer.
 */
#if defined(__OPENCL_C_VERSION__)
#  define PORT_POPCOUNT32(n) popcount((port_uint32_t)(n))
#elif defined(__GNUC__)
#  define PORT_POPCOUNT32(n) __builtin_popcount((port_uint32_t)(n))
#else
#  define PORT_POPCOUNT32(n) (PORT_POPCOUNT16(port_uint16_t(n) >> 16) + \
        PORT_POPCOUNT16(port_uint16_t(n) & (port_uint16_t)0xFFFF))
#endif

/**
 * @brief Number of set bits in single-width unsigned integer.
 */
#define PORT_POPCOUNTS(n)   PORT_POPCOUNT32((n))

/**
 * @brief Number of set bits in 64-bit unsigned integer.
 */
#if defined(__OPENCL_C_VERSION__)
#  define PORT_POPCOUNT64(n) popcount((port_uint64_t)(n))
#elif defined(__GNUC__)
#  define PORT_POPCOUNT64(n) __builtin_popcountll((port_uint64_t)(n))
#else
#  define PORT_POPCOUNT64(n) (PORT_POPCOUNT32((port_uint32_t)(n) >> 32) + \
        PORT_POPCOUNT32((port_uint32_t)(n) & (port_uint32_t)0xFFFFFFFF))
#endif

/**
 * @brief Number of set bits in double-width unsigned integer.
 */
#define PORT_POPCOUNTD(n)   PORT_POPCOUNT64((n))

/**
 * @brief Number of set bits in unsigned integer.
 */
#if defined(__OPENCL_C_VERSION__)
#  define PORT_POPCOUNT(n) popcount((n))
#else
#  define PORT_POPCOUNT(n) _Generic((n), port_uint8_t: PORT_POPCOUNT8(n),  \
                                        port_uint16_t: PORT_POPCOUNT16(n), \
                                        port_uint32_t: PORT_POPCOUNT32(n), \
                                        port_uint64_t: PORT_POPCOUNT64(n))
#endif

///////////////////////////////////////////////////////////////////////////////
// clz()
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Number of leading zeros in 8-bit unsigned integer.
 */
#if defined(__OPENCL_C_VERSION__)
#  define PORT_CLZ8(n) clz((port_uint8_t)(n))
#elif defined(__GNUC__)
#  define PORT_CLZ8(n) ((port_uint8_t)(n) ? __builtin_clz((port_uint8_t)(n)) - 24 : 8)
#else
static inline
port_uint8_t
PORT_CLZ8(
        port_uint8_t n)
{
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n = ~n;
    return PORT_POPCOUNT8(n);
}
#endif

/**
 * @brief Number of leading zeros in quarter-width unsigned integer.
 */
#define PORT_CLZQ(n)    PORT_CLZ8((n))

/**
 * @brief Number of leading zeros in 16-bit unsigned integer.
 */
#if defined(__OPENCL_C_VERSION__)
#  define PORT_CLZ16(n) clz((port_uint16_t)(n))
#elif defined(__GNUC__)
#  define PORT_CLZ16(n) ((port_uint16_t)(n) ? __builtin_clz((port_uint16_t)(n)) - 16 : 16)
#else
static inline
port_uint16_t
PORT_CLZ16(
        port_uint16_t n)
{
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n = ~n;
    return PORT_POPCOUNT16(n);
}
#endif

/**
 * @brief Number of leading zeros in half-width unsigned integer.
 */
#define PORT_CLZH(n)    PORT_CLZ16((n))

/**
 * @brief Number of leading zeros in 32-bit unsigned integer.
 */
#if defined(__OPENCL_C_VERSION__)
#  define PORT_CLZ32(n) clz((port_uint32_t)(n))
#elif defined(__GNUC__)
#  define PORT_CLZ32(n) ((port_uint32_t)(n) ? __builtin_clz((port_uint32_t)(n)) : 32)
#else
static inline
port_uint32_t
PORT_CLZ32(
        port_uint32_t n)
{
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n = ~n;
    return PORT_POPCOUNT32(n);
}
#endif

/**
 * @brief Number of leading zeros in single-width unsigned integer.
 */
#define PORT_CLZS(n)    PORT_CLZ32((n))

/**
 * @brief Number of leading zeros in 64-bit unsigned integer.
 */
#if defined(__OPENCL_C_VERSION__)
#  define PORT_CLZ64(n) clz((port_uint64_t)(n))
#elif defined(__GNUC__)
#  define PORT_CLZ64(n) ((port_uint64_t)(n) ? __builtin_clzll((port_uint64_t)(n)) : 64)
#else
static inline
port_uint64_t
PORT_CLZ64(
        port_uint64_t n)
{
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n |= n >> 32;
    n = ~n;
    return PORT_POPCOUNT64(n);
}
#endif

/**
 * @brief Number of leading zeros in double-width unsigned integer.
 */
#define PORT_CLZD(n)    PORT_CLZ64((n))

/**
 * @brief Number of leading zeros in unsigned integer.
 */
#if defined(__OPENCL_C_VERSION__)
#  define PORT_CLZ(n) clz((n))
#else
#  define PORT_CLZ(n) _Generic((n), port_uint8_t: PORT_CLZ8(n),  \
                                   port_uint16_t: PORT_CLZ16(n), \
                                   port_uint32_t: PORT_CLZ32(n), \
                                   port_uint64_t: PORT_CLZ64(n))
#endif

///////////////////////////////////////////////////////////////////////////////
// ctz()
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Number of trailing zeros in 8-bit unsigned integer.
 */
#if defined(__OPENCL_C_VERSION__)
#  define PORT_CTZ8(n) ctz((port_uint8_t)(n))
#elif defined(__GNUC__)
#  define PORT_CTZ8(n) ((port_uint8_t)(n) ? __builtin_ctz((port_uint8_t)(n)) : 8)
#else
static inline
port_uint8_t
PORT_CTZ8(
        port_uint8_t n)
{
    return n ? PORT_POPCOUNT8(n ^ (n - 1)) - 1 : 8;
}
#endif

/**
 * @brief Number of trailing zeros in quarter-width unsigned integer.
 */
#define PORT_CTZQ(n)    PORT_CTZ8((n))

/**
 * @brief Number of trailing zeros in 16-bit unsigned integer.
 */
#if defined(__OPENCL_C_VERSION__)
#  define PORT_CTZ16(n) ctz((port_uint16_t)(n))
#elif defined(__GNUC__)
#  define PORT_CTZ16(n) ((port_uint16_t)(n) ? __builtin_ctz((port_uint16_t)(n)) : 16)
#else
static inline
port_uint16_t
PORT_CTZ16(
        port_uint16_t n)
{
    return n ? PORT_POPCOUNT16(n ^ (n - 1)) - 1 : 16;
}
#endif

/**
 * @brief Number of trailing zeros in half-width unsigned integer.
 */
#define PORT_CTZH(n)    PORT_CTZ16((n))

/**
 * @brief Number of trailing zeros in 32-bit unsigned integer.
 */
#if defined(__OPENCL_C_VERSION__)
#  define PORT_CTZ32(n) ctz((port_uint32_t)(n))
#elif defined(__GNUC__)
#  define PORT_CTZ32(n) ((port_uint32_t)(n) ? __builtin_ctz((port_uint32_t)(n)) : 32)
#else
static inline
port_uint32_t
PORT_CTZ32(
        port_uint32_t n)
{
    return n ? PORT_POPCOUNT32(n ^ (n - 1)) - 1 : 32;
}
#endif

/**
 * @brief Number of trailing zeros in single-width unsigned integer.
 */
#define PORT_CTZS(n)    PORT_CTZ32((n))

/**
 * @brief Number of trailing zeros in 64-bit unsigned integer.
 */
#if defined(__OPENCL_C_VERSION__)
#  define PORT_CTZ64(n) ctz((port_uint64_t)(n))
#elif defined(__GNUC__)
#  define PORT_CTZ64(n) ((port_uint64_t)(n) ? __builtin_ctzll((port_uint64_t)(n)) : 64)
#else
static inline
port_uint64_t
PORT_CTZ64(
        port_uint64_t n)
{
    return n ? PORT_POPCOUNT64(n ^ (n - 1)) - 1 : 64;
}
#endif

/**
 * @brief Number of trailing zeros in double-width unsigned integer.
 */
#define PORT_CTZD(n)    PORT_CTZ64((n))

/**
 * @brief Number of trailing zeros in unsigned integer.
 */
#if defined(__OPENCL_C_VERSION__)
#  define PORT_CTZ(n) ctz((n))
#else
#  define PORT_CTZ(n) _Generic((n), port_uint8_t: PORT_CTZ8(n),  \
                                   port_uint16_t: PORT_CTZ16(n), \
                                   port_uint32_t: PORT_CTZ32(n), \
                                   port_uint64_t: PORT_CTZ64(n))
#endif

#endif // _PORT_BIT_DEF_H_

