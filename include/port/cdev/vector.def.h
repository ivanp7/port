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
 * @brief Portable macros for operations on built-in vector types.
 */

#pragma once
#ifndef _PORT_CDEV_VECTOR_DEF_H_
#define _PORT_CDEV_VECTOR_DEF_H_

///////////////////////////////////////////////////////////////////////////////
// Literal
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief 2-vector literal.
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V2(x, y) \
    (x, y)
#else
#  define PORT_V2(x, y) \
    {.s = {x, y}}
#endif

/**
 * @brief 2-vector literal from a scalar.
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V2_S(v) \
    (v)
#else
#  define PORT_V2_S(v) \
    {.s = {v, v}}
#endif

/**
 * @brief 3-vector literal.
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V3(x, y, z) \
    (x, y, z)
#else
#  define PORT_V3(x, y, z) \
    {.s = {x, y, z}}
#endif

/**
 * @brief 3-vector literal from a scalar.
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V3_S(v) \
    (v)
#else
#  define PORT_V3_S(v) \
    {.s = {v, v, v}}
#endif

/**
 * @brief 4-vector literal.
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V4(x, y, z, w) \
    (x, y, z, w)
#else
#  define PORT_V4(x, y, z, w) \
    {.s = {x, y, z, w}}
#endif

/**
 * @brief 4-vector literal from a scalar.
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V4_S(v) \
    (v)
#else
#  define PORT_V4_S(v) \
    {.s = {v, v, v, v}}
#endif

/**
 * @brief 8-vector literal.
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V8(s0, s1, s2, s3, s4, s5, s6, s7) \
    (s0, s1, s2, s3, s4, s5, s6, s7)
#else
#  define PORT_V8(s0, s1, s2, s3, s4, s5, s6, s7) \
    {.s = {s0, s1, s2, s3, s4, s5, s6, s7}}
#endif

/**
 * @brief 8-vector literal from a scalar.
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V8_S(v) \
    (v)
#else
#  define PORT_V8_S(v) \
    {.s = {v, v, v, v, v, v, v, v}}
#endif

/**
 * @brief 16-vector literal.
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V16(s0, s1, s2, s3, s4, s5, s6, s7, \
        s8, s9, sA, sB, sC, sD, sE, sF) \
    (s0, s1, s2, s3, s4, s5, s6, s7, \
            s8, s9, sA, sB, sC, sD, sE, sF)
#else
#  define PORT_V16(s0, s1, s2, s3, s4, s5, s6, s7, \
        s8, s9, sA, sB, sC, sD, sE, sF) \
    {.s = {s0, s1, s2, s3, s4, s5, s6, s7, \
        s8, s9, sA, sB, sC, sD, sE, sF}}
#endif

/**
 * @brief 16-vector literal from a scalar.
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V16_S(v) \
    (v)
#else
#  define PORT_V16_S(v) \
    {.s = {v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v}}
#endif

///////////////////////////////////////////////////////////////////////////////
// Access to vector element by index
///////////////////////////////////////////////////////////////////////////////

#ifdef __OPENCL_C_VERSION__

/**
 * @brief Get element of 2-vector by index.
 */
#  define PORT_V2_ELT(v, i) \
    ((i)<1 ? (v).x : (v).y)

/**
 * @brief Get element of 3-vector by index.
 */
#  define PORT_V3_ELT(v, i) \
    ((i)<2 ? PORT_V2_ELT(v, i) : (v).z)

/**
 * @brief Get element of 4-vector by index.
 */
#  define PORT_V4_ELT(v, i) \
    ((i)<2 ? PORT_V2_ELT(v, i) : ((i)<3 ? (v).z : (v).w))

/**
 * @brief Get element of 8-vector by index.
 */
#  define PORT_V8_ELT(v, i) \
    ((i)<4 ? PORT_V4_ELT(v, i) : \
     ((i)<6 ? ((i)<5 ? (v).s4 : (v).s5) : \
              ((i)<7 ? (v).s6 : (v).s7)))

/**
 * @brief Get element of 16-vector by index.
 */
#  define PORT_V16_ELT(v, i) \
    ((i)<8 ? PORT_V8_ELT(v, i) : \
     ((i)<12 ? ((i)<10 ? ((i)<9 ? (v).s8 : (v).s9) : \
                         ((i)<11 ? (v).sA : (v).sB)) : \
               ((i)<14 ? ((i)<13 ? (v).sC : (v).sD) : \
                         ((i)<15 ? (v).sE : (v).sF))))

/**
 * @brief Set element of 2-vector by index.
 */
#  define PORT_V2_SET_ELT(v, i, value) \
    ((i)<1 ? ((v).x = (value)) : ((v).y = (value)))

/**
 * @brief Set element of 3-vector by index.
 */
#  define PORT_V3_SET_ELT(v, i, value) \
    ((i)<2 ? PORT_V2_SET_ELT(v, i, value) : ((v).z = (value)))

/**
 * @brief Set element of 4-vector by index.
 */
#  define PORT_V4_SET_ELT(v, i, value) \
    ((i)<2 ? PORT_V2_SET_ELT(v, i, value) : \
     ((i)<3 ? ((v).z = (value)) : ((v).w = (value))))

/**
 * @brief Set element of 8-vector by index.
 */
#  define PORT_V8_SET_ELT(v, i, value) \
    ((i)<4 ? PORT_V4_SET_ELT(v, i, value) : \
     ((i)<6 ? ((i)<5 ? ((v).s4 = (value)) : ((v).s5 = (value))) : \
              ((i)<7 ? ((v).s6 = (value)) : ((v).s7 = (value)))))

/**
 * @brief Set element of 16-vector by index.
 */
#  define PORT_V16_SET_ELT(v, i, value) \
    ((i)<8 ? PORT_V8_SET_ELT(v, i, value) : \
     ((i)<12 ? ((i)<10 ? ((i)< 9 ? ((v).s8 = (value)) : ((v).s9 = (value))) : \
                         ((i)<11 ? ((v).sA = (value)) : ((v).sB = (value)))): \
               ((i)<14 ? ((i)<13 ? ((v).sC = (value)) : ((v).sD = (value))) : \
                         ((i)<15 ? ((v).sE = (value)) : ((v).sF = (value))))))

#else // __OPENCL_C_VERSION__

/**
 * @brief Get element of 2-vector by index.
 */
#  define PORT_V2_ELT(v, i) (v).s[i]

/**
 * @brief Get element of 3-vector by index.
 */
#  define PORT_V3_ELT(v, i) (v).s[i]

/**
 * @brief Get element of 4-vector by index.
 */
#  define PORT_V4_ELT(v, i) (v).s[i]

/**
 * @brief Get element of 8-vector by index.
 */
#  define PORT_V8_ELT(v, i) (v).s[i]

/**
 * @brief Get element of 16-vector by index.
 */
#  define PORT_V16_ELT(v, i) (v).s[i]

/**
 * @brief Set element of 2-vector by index.
 */
#  define PORT_V2_SET_ELT(v, i, value) ((v).s[i] = (value))

/**
 * @brief Set element of 3-vector by index.
 */
#  define PORT_V3_SET_ELT(v, i, value) ((v).s[i] = (value))

/**
 * @brief Set element of 4-vector by index.
 */
#  define PORT_V4_SET_ELT(v, i, value) ((v).s[i] = (value))

/**
 * @brief Set element of 8-vector by index.
 */
#  define PORT_V8_SET_ELT(v, i, value) ((v).s[i] = (value))

/**
 * @brief Set element of 16-vector by index.
 */
#  define PORT_V16_SET_ELT(v, i, value) ((v).s[i] = (value))

#endif

///////////////////////////////////////////////////////////////////////////////
// Permutation of elements
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief 3-vector cyclic element left shift (x <- y, y <- z, z <- x).
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V3_LSHIFT(v, ignored) do { \
    (v).xyz = (v).yzx;  \
} while(0)
#else
#  define PORT_V3_LSHIFT(v, type) do { \
    type _temp_ = (v).x;    \
    (v).x = (v).y;          \
    (v).y = (v).z;          \
    (v).z = _temp_;         \
} while(0)
#endif

/**
 * @brief 3-vector cyclic element right shift (x -> y, y -> z, z -> x).
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V3_RSHIFT(v, ignored) do { \
    (v).xyz = (v).zxy;  \
} while(0)
#else
#  define PORT_V3_RSHIFT(v, type) do { \
    type _temp_ = (v).x;    \
    (v).x = (v).z;          \
    (v).z = (v).y;          \
    (v).y = _temp_;         \
} while(0)
#endif

///////////////////////////////////////////////////////////////////////////////
// Binary operator
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief 2-vector binary operator (r = a OPERATOR b).
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V2_OP2(r, a, op, b) do { \
    (r).xy = (a).xy op (b).xy; \
} while(0)
#else
#  define PORT_V2_OP2(r, a, op, b) do { \
    (r).x = (a).x op (b).x; \
    (r).y = (a).y op (b).y; \
} while(0)
#endif

/**
 * @brief 3-vector binary operator (r = a OPERATOR b).
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V3_OP2(r, a, op, b) do { \
    (r).xyz = (a).xyz op (b).xyz; \
} while(0)
#else
#  define PORT_V3_OP2(r, a, op, b) do { \
    (r).x = (a).x op (b).x; \
    (r).y = (a).y op (b).y; \
    (r).z = (a).z op (b).z; \
} while(0)
#endif

/**
 * @brief 4-vector binary operator (r = a OPERATOR b).
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V4_OP2(r, a, op, b) do { \
    (r).xyzw = (a).xyzw op (b).xyzw; \
} while(0)
#else
#  define PORT_V4_OP2(r, a, op, b) do { \
    (r).x = (a).x op (b).x; \
    (r).y = (a).y op (b).y; \
    (r).z = (a).z op (b).z; \
    (r).w = (a).w op (b).w; \
} while(0)
#endif

/**
 * @brief 8-vector binary operator (r = a OPERATOR b).
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V8_OP2(r, a, op, b) do { \
    (r).s01234567 = (a).s01234567 op (b).s01234567; \
} while(0)
#else
#  define PORT_V8_OP2(r, a, op, b) do { \
    (r).s0 = (a).s0 op (b).s0; \
    (r).s1 = (a).s1 op (b).s1; \
    (r).s2 = (a).s2 op (b).s2; \
    (r).s3 = (a).s3 op (b).s3; \
    (r).s4 = (a).s4 op (b).s4; \
    (r).s5 = (a).s5 op (b).s5; \
    (r).s6 = (a).s6 op (b).s6; \
    (r).s7 = (a).s7 op (b).s7; \
} while(0)
#endif

/**
 * @brief 16-vector binary operator (r = a OPERATOR b).
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V16_OP2(r, a, op, b) do { \
    (r).s0123456789ABCDEF = (a).s0123456789ABCDEF op (b).s0123456789ABCDEF; \
} while(0)
#else
#  define PORT_V16_OP2(r, a, op, b) do { \
    (r).s0 = (a).s0 op (b).s0; \
    (r).s1 = (a).s1 op (b).s1; \
    (r).s2 = (a).s2 op (b).s2; \
    (r).s3 = (a).s3 op (b).s3; \
    (r).s4 = (a).s4 op (b).s4; \
    (r).s5 = (a).s5 op (b).s5; \
    (r).s6 = (a).s6 op (b).s6; \
    (r).s7 = (a).s7 op (b).s7; \
    (r).s8 = (a).s8 op (b).s8; \
    (r).s9 = (a).s9 op (b).s9; \
    (r).sA = (a).sA op (b).sA; \
    (r).sB = (a).sB op (b).sB; \
    (r).sC = (a).sC op (b).sC; \
    (r).sD = (a).sD op (b).sD; \
    (r).sE = (a).sE op (b).sE; \
    (r).sF = (a).sF op (b).sF; \
} while(0)
#endif

///////////////////////////////////////////////////////////////////////////////
// Binary operator (vector op scalar)
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief 2-vector binary operator (r = a OPERATOR b, b is scalar).
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V2S_OP2(r, a, op, b) do { \
    (r).xy = (a).xy op (b); \
} while(0)
#else
#  define PORT_V2S_OP2(r, a, op, b) do { \
    (r).x = (a).x op (b); \
    (r).y = (a).y op (b); \
} while(0)
#endif

/**
 * @brief 3-vector binary operator (r = a OPERATOR b, b is scalar).
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V3S_OP2(r, a, op, b) do { \
    (r).xyz = (a).xyz op (b); \
} while(0)
#else
#  define PORT_V3S_OP2(r, a, op, b) do { \
    (r).x = (a).x op (b); \
    (r).y = (a).y op (b); \
    (r).z = (a).z op (b); \
} while(0)
#endif

/**
 * @brief 4-vector binary operator (r = a OPERATOR b, b is scalar).
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V4S_OP2(r, a, op, b) do { \
    (r).xyzw = (a).xyzw op (b); \
} while(0)
#else
#  define PORT_V4S_OP2(r, a, op, b) do { \
    (r).x = (a).x op (b); \
    (r).y = (a).y op (b); \
    (r).z = (a).z op (b); \
    (r).w = (a).w op (b); \
} while(0)
#endif

/**
 * @brief 8-vector binary operator (r = a OPERATOR b, b is scalar).
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V8S_OP2(r, a, op, b) do { \
    (r).s01234567 = (a).s01234567 op (b); \
} while(0)
#else
#  define PORT_V8S_OP2(r, a, op, b) do { \
    (r).s0 = (a).s0 op (b); \
    (r).s1 = (a).s1 op (b); \
    (r).s2 = (a).s2 op (b); \
    (r).s3 = (a).s3 op (b); \
    (r).s4 = (a).s4 op (b); \
    (r).s5 = (a).s5 op (b); \
    (r).s6 = (a).s6 op (b); \
    (r).s7 = (a).s7 op (b); \
} while(0)
#endif

/**
 * @brief 16-vector binary operator (r = a OPERATOR b, b is scalar).
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V16S_OP2(r, a, op, b) do { \
    (r).s0123456789ABCDEF = (a).s0123456789ABCDEF op (b); \
} while(0)
#else
#  define PORT_V16S_OP2(r, a, op, b) do { \
    (r).s0 = (a).s0 op (b); \
    (r).s1 = (a).s1 op (b); \
    (r).s2 = (a).s2 op (b); \
    (r).s3 = (a).s3 op (b); \
    (r).s4 = (a).s4 op (b); \
    (r).s5 = (a).s5 op (b); \
    (r).s6 = (a).s6 op (b); \
    (r).s7 = (a).s7 op (b); \
    (r).s8 = (a).s8 op (b); \
    (r).s9 = (a).s9 op (b); \
    (r).sA = (a).sA op (b); \
    (r).sB = (a).sB op (b); \
    (r).sC = (a).sC op (b); \
    (r).sD = (a).sD op (b); \
    (r).sE = (a).sE op (b); \
    (r).sF = (a).sF op (b); \
} while(0)
#endif

///////////////////////////////////////////////////////////////////////////////
// Binary operator (scalar op vector)
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief 2-vector binary operator (r = a OPERATOR b, a is scalar).
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_SV2_OP2(r, a, op, b) do { \
    (r).xy = (a) op (b).xy; \
} while(0)
#else
#  define PORT_SV2_OP2(r, a, op, b) do { \
    (r).x = (a) op (b).x; \
    (r).y = (a) op (b).y; \
} while(0)
#endif

/**
 * @brief 3-vector binary operator (r = a OPERATOR b, a is scalar).
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_SV3_OP2(r, a, op, b) do { \
    (r).xyz = (a) op (b).xyz; \
} while(0)
#else
#  define PORT_SV3_OP2(r, a, op, b) do { \
    (r).x = (a) op (b).x; \
    (r).y = (a) op (b).y; \
    (r).z = (a) op (b).z; \
} while(0)
#endif

/**
 * @brief 4-vector binary operator (r = a OPERATOR b, a is scalar).
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_SV4_OP2(r, a, op, b) do { \
    (r).xyzw = (a) op (b).xyzw; \
} while(0)
#else
#  define PORT_SV4_OP2(r, a, op, b) do { \
    (r).x = (a) op (b).x; \
    (r).y = (a) op (b).y; \
    (r).z = (a) op (b).z; \
    (r).w = (a) op (b).w; \
} while(0)
#endif

/**
 * @brief 8-vector binary operator (r = a OPERATOR b, a is scalar).
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_SV8_OP2(r, a, op, b) do { \
    (r).s01234567 = (a) op (b).s01234567; \
} while(0)
#else
#  define PORT_SV8_OP2(r, a, op, b) do { \
    (r).s0 = (a) op (b).s0; \
    (r).s1 = (a) op (b).s1; \
    (r).s2 = (a) op (b).s2; \
    (r).s3 = (a) op (b).s3; \
    (r).s4 = (a) op (b).s4; \
    (r).s5 = (a) op (b).s5; \
    (r).s6 = (a) op (b).s6; \
    (r).s7 = (a) op (b).s7; \
} while(0)
#endif

/**
 * @brief 16-vector binary operator (r = a OPERATOR b, a is scalar).
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_SV16_OP2(r, a, op, b) do { \
    (r).s0123456789ABCDEF = (a) op (b).s0123456789ABCDEF; \
} while(0)
#else
#  define PORT_SV16_OP2(r, a, op, b) do { \
    (r).s0 = (a) op (b).s0; \
    (r).s1 = (a) op (b).s1; \
    (r).s2 = (a) op (b).s2; \
    (r).s3 = (a) op (b).s3; \
    (r).s4 = (a) op (b).s4; \
    (r).s5 = (a) op (b).s5; \
    (r).s6 = (a) op (b).s6; \
    (r).s7 = (a) op (b).s7; \
    (r).s8 = (a) op (b).s8; \
    (r).s9 = (a) op (b).s9; \
    (r).sA = (a) op (b).sA; \
    (r).sB = (a) op (b).sB; \
    (r).sC = (a) op (b).sC; \
    (r).sD = (a) op (b).sD; \
    (r).sE = (a) op (b).sE; \
    (r).sF = (a) op (b).sF; \
} while(0)
#endif

///////////////////////////////////////////////////////////////////////////////
// Unary operator
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief 2-vector unary operator (r = OPERATOR a).
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V2_OP1(r, op, a) do { \
    (r).xy = op((a).xy); \
} while(0)
#else
#  define PORT_V2_OP1(r, op, a) do { \
    (r).x = op((a).x); \
    (r).y = op((a).y); \
} while(0)
#endif

/**
 * @brief 3-vector unary operator (r = OPERATOR a).
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V3_OP1(r, op, a) do { \
    (r).xyz = op((a).xyz); \
} while(0)
#else
#  define PORT_V3_OP1(r, op, a) do { \
    (r).x = op((a).x); \
    (r).y = op((a).y); \
    (r).z = op((a).z); \
} while(0)
#endif

/**
 * @brief 4-vector unary operator (r = OPERATOR a).
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V4_OP1(r, op, a) do { \
    (r).xyzw = op((a).xyzw); \
} while(0)
#else
#  define PORT_V4_OP1(r, op, a) do { \
    (r).x = op((a).x); \
    (r).y = op((a).y); \
    (r).z = op((a).z); \
    (r).w = op((a).w); \
} while(0)
#endif

/**
 * @brief 8-vector unary operator (r = OPERATOR a).
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V8_OP1(r, op, a) do { \
    (r).s01234567 = op((a).s01234567); \
} while(0)
#else
#  define PORT_V8_OP1(r, op, a) do { \
    (r).s0 = op((a).s0); \
    (r).s1 = op((a).s1); \
    (r).s2 = op((a).s2); \
    (r).s3 = op((a).s3); \
    (r).s4 = op((a).s4); \
    (r).s5 = op((a).s5); \
    (r).s6 = op((a).s6); \
    (r).s7 = op((a).s7); \
} while(0)
#endif

/**
 * @brief 16-vector unary operator (r = OPERATOR a).
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V16_OP1(r, op, a) do { \
    (r).s0123456789ABCDEF = op((a).s0123456789ABCDEF); \
} while(0)
#else
#  define PORT_V16_OP1(r, op, a) do { \
    (r).s0 = op((a).s0); \
    (r).s1 = op((a).s1); \
    (r).s2 = op((a).s2); \
    (r).s3 = op((a).s3); \
    (r).s4 = op((a).s4); \
    (r).s5 = op((a).s5); \
    (r).s6 = op((a).s6); \
    (r).s7 = op((a).s7); \
    (r).s8 = op((a).s8); \
    (r).s9 = op((a).s9); \
    (r).sA = op((a).sA); \
    (r).sB = op((a).sB); \
    (r).sC = op((a).sC); \
    (r).sD = op((a).sD); \
    (r).sE = op((a).sE); \
    (r).sF = op((a).sF); \
} while(0)
#endif

///////////////////////////////////////////////////////////////////////////////
// Assignment
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief 2-vector assignment.
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V2_ASSIGN(r, a) do { \
    (r).xy = (a).xy; \
} while(0)
#else
#  define PORT_V2_ASSIGN(r, a) do { \
    (r).x = (a).x; \
    (r).y = (a).y; \
} while(0)
#endif

/**
 * @brief 3-vector assignment.
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V3_ASSIGN(r, a) do { \
    (r).xyz = (a).xyz; \
} while(0)
#else
#  define PORT_V3_ASSIGN(r, a) do { \
    (r).x = (a).x; \
    (r).y = (a).y; \
    (r).z = (a).z; \
} while(0)
#endif

/**
 * @brief 4-vector assignment.
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V4_ASSIGN(r, a) do { \
    (r).xyzw = (a).xyzw; \
} while(0)
#else
#  define PORT_V4_ASSIGN(r, a) do { \
    (r).x = (a).x; \
    (r).y = (a).y; \
    (r).z = (a).z; \
    (r).w = (a).w; \
} while(0)
#endif

/**
 * @brief 8-vector assignment.
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V8_ASSIGN(r, a) do { \
    (r).s01234567 = (a).s01234567; \
} while(0)
#else
#  define PORT_V8_ASSIGN(r, a) do { \
    (r).s0 = (a).s0; \
    (r).s1 = (a).s1; \
    (r).s2 = (a).s2; \
    (r).s3 = (a).s3; \
    (r).s4 = (a).s4; \
    (r).s5 = (a).s5; \
    (r).s6 = (a).s6; \
    (r).s7 = (a).s7; \
} while(0)
#endif

/**
 * @brief 16-vector assignment.
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V16_ASSIGN(r, a) do { \
    (r).s0123456789ABCDEF = (a).s0123456789ABCDEF; \
} while(0)
#else
#  define PORT_V16_ASSIGN(r, a) do { \
    (r).s0 = (a).s0; \
    (r).s1 = (a).s1; \
    (r).s2 = (a).s2; \
    (r).s3 = (a).s3; \
    (r).s4 = (a).s4; \
    (r).s5 = (a).s5; \
    (r).s6 = (a).s6; \
    (r).s7 = (a).s7; \
    (r).s8 = (a).s8; \
    (r).s9 = (a).s9; \
    (r).sA = (a).sA; \
    (r).sB = (a).sB; \
    (r).sC = (a).sC; \
    (r).sD = (a).sD; \
    (r).sE = (a).sE; \
    (r).sF = (a).sF; \
} while(0)
#endif

///////////////////////////////////////////////////////////////////////////////
// Function taking 1 argument
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief 2-vector function taking 1 argument (r = FUNCTION(a)).
 */
#define PORT_V2_FUNC1(r, func, a) PORT_V2_OP1(r, func, a)

/**
 * @brief 3-vector function taking 1 argument (r = FUNCTION(a)).
 */
#define PORT_V3_FUNC1(r, func, a) PORT_V3_OP1(r, func, a)

/**
 * @brief 4-vector function taking 1 argument (r = FUNCTION(a)).
 */
#define PORT_V4_FUNC1(r, func, a) PORT_V4_OP1(r, func, a)

/**
 * @brief 8-vector function taking 1 argument (r = FUNCTION(a)).
 */
#define PORT_V8_FUNC1(r, func, a) PORT_V8_OP1(r, func, a)

/**
 * @brief 16-vector function taking 1 argument (r = FUNCTION(a)).
 */
#define PORT_V16_FUNC1(r, func, a) PORT_V16_OP1(r, func, a)

///////////////////////////////////////////////////////////////////////////////
// Function taking 2 arguments
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief 2-vector function taking 2 arguments (r = FUNCTION(a, b)).
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V2_FUNC2(r, func, a, b) do { \
    (r).xy = func((a).xy, (b).xy); \
} while(0)
#else
#  define PORT_V2_FUNC2(r, func, a, b) do { \
    (r).x = func((a).x, (b).x); \
    (r).y = func((a).y, (b).y); \
} while(0)
#endif

/**
 * @brief 3-vector function taking 2 arguments (r = FUNCTION(a, b)).
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V3_FUNC2(r, func, a, b) do { \
    (r).xyz = func((a).xyz, (b).xyz); \
} while(0)
#else
#  define PORT_V3_FUNC2(r, func, a, b) do { \
    (r).x = func((a).x, (b).x); \
    (r).y = func((a).y, (b).y); \
    (r).z = func((a).z, (b).z); \
} while(0)
#endif

/**
 * @brief 4-vector function taking 2 arguments (r = FUNCTION(a, b)).
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V4_FUNC2(r, func, a, b) do { \
    (r).xyzw = func((a).xyzw, (b).xyzw); \
} while(0)
#else
#  define PORT_V4_FUNC2(r, func, a, b) do { \
    (r).x = func((a).x, (b).x); \
    (r).y = func((a).y, (b).y); \
    (r).z = func((a).z, (b).z); \
    (r).w = func((a).w, (b).w); \
} while(0)
#endif

/**
 * @brief 8-vector function taking 2 arguments (r = FUNCTION(a, b)).
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V8_FUNC2(r, func, a, b) do { \
    (r).s01234567 = func((a).s01234567, (b).s01234567); \
} while(0)
#else
#  define PORT_V8_FUNC2(r, func, a, b) do { \
    (r).s0 = func((a).s0, (b).s0); \
    (r).s1 = func((a).s1, (b).s1); \
    (r).s2 = func((a).s2, (b).s2); \
    (r).s3 = func((a).s3, (b).s3); \
    (r).s4 = func((a).s4, (b).s4); \
    (r).s5 = func((a).s5, (b).s5); \
    (r).s6 = func((a).s6, (b).s6); \
    (r).s7 = func((a).s7, (b).s7); \
} while(0)
#endif

/**
 * @brief 16-vector function taking 2 arguments (r = FUNCTION(a, b)).
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V16_FUNC2(r, func, a, b) do { \
    (r).s0123456789ABCDEF = func((a).s0123456789ABCDEF, (b).s0123456789ABCDEF); \
} while(0)
#else
#  define PORT_V16_FUNC2(r, func, a, b) do { \
    (r).s0 = func((a).s0, (b).s0); \
    (r).s1 = func((a).s1, (b).s1); \
    (r).s2 = func((a).s2, (b).s2); \
    (r).s3 = func((a).s3, (b).s3); \
    (r).s4 = func((a).s4, (b).s4); \
    (r).s5 = func((a).s5, (b).s5); \
    (r).s6 = func((a).s6, (b).s6); \
    (r).s7 = func((a).s7, (b).s7); \
    (r).s8 = func((a).s8, (b).s8); \
    (r).s9 = func((a).s9, (b).s9); \
    (r).sA = func((a).sA, (b).sA); \
    (r).sB = func((a).sB, (b).sB); \
    (r).sC = func((a).sC, (b).sC); \
    (r).sD = func((a).sD, (b).sD); \
    (r).sE = func((a).sE, (b).sE); \
    (r).sF = func((a).sF, (b).sF); \
} while(0)
#endif

///////////////////////////////////////////////////////////////////////////////
// Function taking 3 arguments
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief 2-vector function taking 3 arguments (r = FUNCTION(a, b, c)).
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V2_FUNC3(r, func, a, b, c) do { \
    (r).xy = func((a).xy, (b).xy, (c).xy); \
} while(0)
#else
#  define PORT_V2_FUNC3(r, func, a, b, c) do { \
    (r).x = func((a).x, (b).x, (c).x); \
    (r).y = func((a).y, (b).y, (c).y); \
} while(0)
#endif

/**
 * @brief 3-vector function taking 3 arguments (r = FUNCTION(a, b, c)).
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V3_FUNC3(r, func, a, b, c) do { \
    (r).xyz = func((a).xyz, (b).xyz, (c).xyz); \
} while(0)
#else
#  define PORT_V3_FUNC3(r, func, a, b, c) do { \
    (r).x = func((a).x, (b).x, (c).x); \
    (r).y = func((a).y, (b).y, (c).y); \
    (r).z = func((a).z, (b).z, (c).z); \
} while(0)
#endif

/**
 * @brief 4-vector function taking 3 arguments (r = FUNCTION(a, b, c)).
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V4_FUNC3(r, func, a, b, c) do { \
    (r).xyzw = func((a).xyzw, (b).xyzw, (c).xyzw); \
} while(0)
#else
#  define PORT_V4_FUNC3(r, func, a, b, c) do { \
    (r).x = func((a).x, (b).x, (c).x); \
    (r).y = func((a).y, (b).y, (c).y); \
    (r).z = func((a).z, (b).z, (c).z); \
    (r).w = func((a).w, (b).w, (c).w); \
} while(0)
#endif

/**
 * @brief 8-vector function taking 3 arguments (r = FUNCTION(a, b, c)).
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V8_FUNC3(r, func, a, b, c) do { \
    (r).s01234567 = func((a).s01234567, (b).s01234567, (c).s01234567); \
} while(0)
#else
#  define PORT_V8_FUNC3(r, func, a, b, c) do { \
    (r).s0 = func((a).s0, (b).s0, (c).s0); \
    (r).s1 = func((a).s1, (b).s1, (c).s1); \
    (r).s2 = func((a).s2, (b).s2, (c).s2); \
    (r).s3 = func((a).s3, (b).s3, (c).s3); \
    (r).s4 = func((a).s4, (b).s4, (c).s4); \
    (r).s5 = func((a).s5, (b).s5, (c).s5); \
    (r).s6 = func((a).s6, (b).s6, (c).s6); \
    (r).s7 = func((a).s7, (b).s7, (c).s7); \
} while(0)
#endif

/**
 * @brief 16-vector function taking 3 arguments (r = FUNCTION(a, b, c)).
 */
#ifdef __OPENCL_C_VERSION__
#  define PORT_V16_FUNC3(r, func, a, b, c) do { \
    (r).s0123456789ABCDEF = func((a).s0123456789ABCDEF, \
            (b).s0123456789ABCDEF, (c).s0123456789ABCDEF); \
} while(0)
#else
#  define PORT_V16_FUNC3(r, func, a, b, c) do { \
    (r).s0 = func((a).s0, (b).s0, (c).s0); \
    (r).s1 = func((a).s1, (b).s1, (c).s1); \
    (r).s2 = func((a).s2, (b).s2, (c).s2); \
    (r).s3 = func((a).s3, (b).s3, (c).s3); \
    (r).s4 = func((a).s4, (b).s4, (c).s4); \
    (r).s5 = func((a).s5, (b).s5, (c).s5); \
    (r).s6 = func((a).s6, (b).s6, (c).s6); \
    (r).s7 = func((a).s7, (b).s7, (c).s7); \
    (r).s8 = func((a).s8, (b).s8, (c).s8); \
    (r).s9 = func((a).s9, (b).s9, (c).s9); \
    (r).sA = func((a).sA, (b).sA, (c).sA); \
    (r).sB = func((a).sB, (b).sB, (c).sB); \
    (r).sC = func((a).sC, (b).sC, (c).sC); \
    (r).sD = func((a).sD, (b).sD, (c).sD); \
    (r).sE = func((a).sE, (b).sE, (c).sE); \
    (r).sF = func((a).sF, (b).sF, (c).sF); \
} while(0)
#endif

#endif // _PORT_CDEV_VECTOR_DEF_H_

