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
 * @brief Memory model types.
 */

#pragma once
#ifndef _PORT_MEMORY_TYP_H_
#define _PORT_MEMORY_TYP_H_

#include "port/types.typ.h"

/**
 * @brief Memory reference.
 */
typedef port_sint_single_t port_memory_ref_t;
/**
 * @brief Memory reference (half size).
 */
typedef port_sint_half_t port_memory_ref_half_t;
/**
 * @brief Memory reference (quarter size).
 */
typedef port_sint_quarter_t port_memory_ref_quarter_t;

/**
 * @brief Memory reference format.
 */
typedef struct port_memory_ref_format {
    struct {
        port_uint8_t num_tidx_bits; ///< Number of table index bits.
        port_uint8_t offset_lshift; ///< Offset scale (left shift).
    } far; ///< Format of far memory references.

    struct {
        port_uint8_t offset_lshift; ///< Offset scale (left shift).
    } near; ///< Format of near memory references.
} port_memory_ref_format_t;

#endif // _PORT_MEMORY_TYP_H_

