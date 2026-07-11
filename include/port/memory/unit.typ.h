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
    port_uints_t as_uints;

    port_uinth_t as_uinth[2];
    port_uinth_v2_t as_uinth_v2;

    port_uintq_t as_uintq[4];
    port_uintq_v2_t as_uintq_v2[2];
    port_uintq_v4_t as_uintq_v4;

    // As signed integer
    port_sints_t as_sints;

    port_sinth_t as_sinth[2];
    port_sinth_v2_t as_sinth_v2;

    port_sintq_t as_sintq[4];
    port_sintq_v2_t as_sintq_v2[2];
    port_sintq_v4_t as_sintq_v4;

    // As floating-point number
    port_floats_t as_floats;
} port_memory_unit_t;

#define PORT_MEMORY_UNIT__AS_FLOATH     as_uinth    ///< Field for accesing unit as floath
#define PORT_MEMORY_UNIT__AS_FLOATH_V2  as_uinth_v2 ///< Field for accesing unit as floath_v2

#define PORT_MEMORY_UNIT__AS_REF        as_sints  ///< Field for accessing packed memory reference (single size).
#define PORT_MEMORY_UNIT__AS_REFH       as_sinth    ///< Field for accessing packed memory reference (half size).
#define PORT_MEMORY_UNIT__AS_REFQ       as_sintq ///< Field for accessing packed memory reference (quarter size).

/**
 * @brief Type punning union for double size types.
 */
typedef union port_memory_unitd {
    port_memory_unit_t as_unit[2];

    port_uintd_t as_uintd;
    port_sintd_t as_sintd;

    port_floatd_t as_floatd;
} port_memory_unitd_t;

#endif // _PORT_MEMORY_UNIT_TYP_H_

