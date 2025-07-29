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
 * @brief Memory unit type.
 */

#pragma once
#ifndef _PORT_MEMORY_UNIT_TYP_H_
#define _PORT_MEMORY_UNIT_TYP_H_

#include "port/types.typ.h"

/**
 * @brief Standard memory unit.
 */
typedef union port_memory_unit {
    // As unsigned integer
    port_uint_single_t as_uint_single;

    port_uint_half_t as_uint_half[2];
    port_uint_half_v2_t as_uint_half_v2;

    port_uint_quarter_t as_uint_quarter[4];
    port_uint_quarter_v2_t as_uint_quarter_v2[2];
    port_uint_quarter_v4_t as_uint_quarter_v4;

    // As signed integer
    port_sint_single_t as_sint_single;

    port_sint_half_t as_sint_half[2];
    port_sint_half_v2_t as_sint_half_v2;

    port_sint_quarter_t as_sint_quarter[4];
    port_sint_quarter_v2_t as_sint_quarter_v2[2];
    port_sint_quarter_v4_t as_sint_quarter_v4;

    // As floating-point number
    port_float_single_t as_float_single;
} port_memory_unit_t;

#define PORT_MEMORY_UNIT__AS_FLOAT_HALF     as_uint_half    ///< Field for accesing unit as float_half
#define PORT_MEMORY_UNIT__AS_FLOAT_HALF_V2  as_uint_half_v2 ///< Field for accesing unit as float_half_v2

#define PORT_MEMORY_UNIT__AS_REF          as_sint_single  ///< Field for accessing packed memory reference (single size).
#define PORT_MEMORY_UNIT__AS_REF_HALF     as_sint_half    ///< Field for accessing packed memory reference (half size).
#define PORT_MEMORY_UNIT__AS_REF_QUARTER  as_sint_quarter ///< Field for accessing packed memory reference (quarter size).

/**
 * @brief Type punning union for double size types.
 */
typedef union port_memory_unit_double {
    port_memory_unit_t as_unit[2];

    port_uint_double_t as_uint_double;
    port_sint_double_t as_sint_double;

    port_float_double_t as_float_double;
} port_memory_unit_double_t;

#endif // _PORT_MEMORY_UNIT_TYP_H_

