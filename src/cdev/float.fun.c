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

#include <port/cdev/float.fun.h>
#include <port/cdev/bit.def.h>
#include <port/cdev/vector.def.h>

///////////////////////////////////////////////////////////////////////////////
// float16 -> float32
///////////////////////////////////////////////////////////////////////////////

#define F16_MNT_NBITS 10 // number of mantissa bits
#define F16_EXP_NBITS 5  // number of exponent bits
#define F16_SGN_BITP (F16_MNT_NBITS + F16_EXP_NBITS) // sign bit position
#define F16_EXP_BIAS 0x0F // exponent bias
#define F16_EXP_INF 0x1F  // exponent value for infinity and NaN
#define F16_DEFAULT_NAN_MANTISSA 0x0200 // mantissa to be used when float32 NaN payload does not fit into float16 mantissa

#define F32_MNT_NBITS 23 // number of mantissa bits
#define F32_EXP_NBITS 8  // number of exponent bits
#define F32_SGN_BITP (F32_MNT_NBITS + F32_EXP_NBITS) // sign bit position
#define F32_EXP_BIAS 0x7F // exponent bias
#define F32_EXP_INF 0xFF  // exponent value for infinity and NaN

port_float32_t
port_convert_float16_to_float32(
        port_uint16_t value)
{
#ifdef __OPENCL_C_VERSION__
    return vload_half(0, (half*)&value);
#elif defined(__GNUC__)
    union {
        port_uint16_t as_uint;
        _Float16 as_float;
    } u = {.as_uint = value};
    return (port_float32_t)u.as_float;
#else
    union {
        port_uint32_t as_uint;
        port_float32_t as_float;
    } u = {.as_uint = (value & PORT_BIT32(F16_SGN_BITP)) << (F32_SGN_BITP - F16_SGN_BITP)}; // sign bit

    port_uint8_t value_exp = (value >> F16_MNT_NBITS) & PORT_NZMASK16(F16_EXP_NBITS); // exponent
    value &= PORT_NZMASK16(F16_MNT_NBITS); // mantissa

    if (value_exp == F16_EXP_INF) // infinity or NaN
        value_exp = F32_EXP_INF;
    else if (value_exp != 0) // normal numbers
        value_exp += F32_EXP_BIAS - F16_EXP_BIAS;
    else if (value != 0) // non-zero subnormal numbers
    {
        // Calculate exponent shift needed to normalize the number
        port_uint16_t shift = PORT_CLZ16(value) - (16 - F16_MNT_NBITS);

        // Normalize the number
        value = (value << (shift + 1)) & PORT_NZMASK16(F16_MNT_NBITS); // drop the explicit leading 1
        value_exp = (F32_EXP_BIAS - F16_EXP_BIAS) - shift;
    }

    u.as_uint |= (port_uint32_t)value_exp << F32_MNT_NBITS;
    u.as_uint |= (port_uint32_t)value << (F32_MNT_NBITS - F16_MNT_NBITS);

    return u.as_float;
#endif
}

port_float32_v2_t
port_convert_float16_to_float32_v2(
        port_uint16_v2_t value)
{
#ifdef __OPENCL_C_VERSION__
    return vloada_half2(0, (half*)&value);
#else
    port_float32_v2_t v;
    PORT_V2_FUNC1(v, port_convert_float16_to_float32, value);
    return v;
#endif
}

port_float32_v3_t
port_convert_float16_to_float32_v3(
        port_uint16_v3_t value)
{
#ifdef __OPENCL_C_VERSION__
    return vloada_half3(0, (half*)&value);
#else
    port_float32_v3_t v;
    PORT_V3_FUNC1(v, port_convert_float16_to_float32, value);
    return v;
#endif
}

port_float32_v4_t
port_convert_float16_to_float32_v4(
        port_uint16_v4_t value)
{
#ifdef __OPENCL_C_VERSION__
    return vloada_half4(0, (half*)&value);
#else
    port_float32_v4_t v;
    PORT_V4_FUNC1(v, port_convert_float16_to_float32, value);
    return v;
#endif
}

port_float32_v8_t
port_convert_float16_to_float32_v8(
        port_uint16_v8_t value)
{
#ifdef __OPENCL_C_VERSION__
    return vloada_half8(0, (half*)&value);
#else
    port_float32_v8_t v;
    PORT_V8_FUNC1(v, port_convert_float16_to_float32, value);
    return v;
#endif
}

port_float32_v16_t
port_convert_float16_to_float32_v16(
        port_uint16_v16_t value)
{
#ifdef __OPENCL_C_VERSION__
    return vloada_half16(0, (half*)&value);
#else
    port_float32_v16_t v;
    PORT_V16_FUNC1(v, port_convert_float16_to_float32, value);
    return v;
#endif
}

///////////////////////////////////////////////////////////////////////////////
// float32 -> float16
///////////////////////////////////////////////////////////////////////////////

port_uint16_t
port_convert_float32_to_float16(
        port_float32_t value)
{
    port_uint16_t result;
#ifdef __OPENCL_C_VERSION__
    vstore_half_rte(value, 0, (half*)&result);
#elif defined(__GNUC__)
    union {
        port_uint16_t as_uint;
        _Float16 as_float;
    } u = {.as_float = value};
    return u.as_uint;
#else
    union {
        port_uint32_t as_uint;
        port_float32_t as_float;
    } u = {.as_float = value};
    result = (u.as_uint & PORT_BIT32(F32_SGN_BITP)) >> (F32_SGN_BITP - F16_SGN_BITP); // sign bit

    port_uint8_t value_exp = (u.as_uint >> F32_MNT_NBITS) & PORT_NZMASK32(F32_EXP_NBITS); // exponent
    u.as_uint &= PORT_NZMASK32(F32_MNT_NBITS); // mantissa

    if (value_exp == F32_EXP_INF) // infinity or NaN
    {
        value_exp = F16_EXP_INF;

        if (u.as_uint != 0) // NaN
        {
            if ((u.as_uint & PORT_NZMASK32(F32_MNT_NBITS - F16_MNT_NBITS)) == 0) // NaN mantissa is representable
                u.as_uint >>= F32_MNT_NBITS - F16_MNT_NBITS;
            else // NaN mantissa is not representable, replace it
                u.as_uint = F16_DEFAULT_NAN_MANTISSA;
        }
    }
    else if (value_exp >= F16_EXP_INF + (F32_EXP_BIAS - F16_EXP_BIAS)) // overflow to infinity
    {
        value_exp = F16_EXP_INF;
        u.as_uint = 0;
    }
    else if (value_exp >= 1 + (F32_EXP_BIAS - F16_EXP_BIAS)) // normal numbers
    {
        value_exp -= F32_EXP_BIAS - F16_EXP_BIAS;

        // Decrease mantissa precision and round
        u.as_uint >>= F32_MNT_NBITS - F16_MNT_NBITS - 1;
        u.as_uint = (u.as_uint >> 1) + (u.as_uint & 1);

        value_exp += (u.as_uint & PORT_BIT32(F16_MNT_NBITS)) >> F16_MNT_NBITS; // overflow bit adds to exponent
        u.as_uint &= PORT_NZMASK32(F16_MNT_NBITS);
    }
    else if (value_exp > (F32_EXP_BIAS - F16_EXP_BIAS) - F16_MNT_NBITS) // subnormal numbers
    {
        value_exp = (F32_EXP_BIAS - F16_EXP_BIAS) - value_exp; // exponent shift

        // Add the explicit leading 1
        u.as_uint |= PORT_BIT32(F32_MNT_NBITS);

        // Decrease mantissa precision and round
        u.as_uint >>= (F32_MNT_NBITS - F16_MNT_NBITS) + value_exp;
        u.as_uint = (u.as_uint >> 1) + (u.as_uint & 1);

        value_exp = (u.as_uint & PORT_BIT32(F16_MNT_NBITS)) >> F16_MNT_NBITS; // overflow bit is exponent
        u.as_uint &= PORT_NZMASK32(F16_MNT_NBITS);
    }
    else // underflow to zero
    {
        value_exp = 0;
        u.as_uint = 0;
    }

    result |= (port_uint16_t)value_exp << F16_MNT_NBITS;
    result |= u.as_uint;
#endif
    return result;
}

port_uint16_v2_t
port_convert_float32_to_float16_v2(
        port_float32_v2_t value)
{
    port_uint16_v2_t v;
#ifdef __OPENCL_C_VERSION__
    vstorea_half2_rte(value, 0, (half*)&v);
#else
    PORT_V2_FUNC1(v, port_convert_float32_to_float16, value);
#endif
    return v;
}

port_uint16_v3_t
port_convert_float32_to_float16_v3(
        port_float32_v3_t value)
{
    port_uint16_v3_t v;
#ifdef __OPENCL_C_VERSION__
    vstorea_half3_rte(value, 0, (half*)&v);
#else
    PORT_V3_FUNC1(v, port_convert_float32_to_float16, value);
#endif
    return v;
}

port_uint16_v4_t
port_convert_float32_to_float16_v4(
        port_float32_v4_t value)
{
    port_uint16_v4_t v;
#ifdef __OPENCL_C_VERSION__
    vstorea_half4_rte(value, 0, (half*)&v);
#else
    PORT_V4_FUNC1(v, port_convert_float32_to_float16, value);
#endif
    return v;
}

port_uint16_v8_t
port_convert_float32_to_float16_v8(
        port_float32_v8_t value)
{
    port_uint16_v8_t v;
#ifdef __OPENCL_C_VERSION__
    vstorea_half8_rte(value, 0, (half*)&v);
#else
    PORT_V8_FUNC1(v, port_convert_float32_to_float16, value);
#endif
    return v;
}

port_uint16_v16_t
port_convert_float32_to_float16_v16(
        port_float32_v16_t value)
{
    port_uint16_v16_t v;
#ifdef __OPENCL_C_VERSION__
    vstorea_half16_rte(value, 0, (half*)&v);
#else
    PORT_V16_FUNC1(v, port_convert_float32_to_float16, value);
#endif
    return v;
}

