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
 * @brief Memory model types.
 */

#pragma once
#ifndef _PORT_MEMORY_TYP_H_
#define _PORT_MEMORY_TYP_H_

#include "port/types.typ.h"
#include "port/keywords.def.h"

///////////////////////////////////////////////////////////////////////////////
// Memory reference
///////////////////////////////////////////////////////////////////////////////

typedef port_sint_quarter_t port_memory_ref_quarter_t; ///< Memory reference (quarter size).
typedef port_sint_half_t port_memory_ref_half_t;       ///< Memory reference (half size).
typedef port_sint_single_t port_memory_ref_t;          ///< Memory reference.

///////////////////////////////////////////////////////////////////////////////
// Memory unit
///////////////////////////////////////////////////////////////////////////////

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

    port_uint_half_t as_float_half[2];    // no native float16 type
    port_uint_half_v2_t as_float_half_v2; // use integers instead

    // As memory reference
    port_memory_ref_t as_ref;
    port_memory_ref_half_t as_ref_half[2];
    port_memory_ref_quarter_t as_ref_quarter[4];
} port_memory_unit_t;

/**
 * @brief Type punning union for double size types.
 */
typedef union port_memory_unit_double {
    port_memory_unit_t as_units[2];

    port_uint_double_t as_uint_double;
    port_sint_double_t as_sint_double;

    port_float_double_t as_float_double;
} port_memory_unit_double_t;

///////////////////////////////////////////////////////////////////////////////
// Pointers to void
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Pointer to non-const void.
 */
typedef void* port_void_ptr_t;
/**
 * @brief Pointer to const void.
 */
typedef const void* port_const_void_ptr_t;

/**
 * @brief Pointer to private non-const void.
 */
typedef PORT_KW_PRIVATE void* port_private_void_ptr_t;
/**
 * @brief Pointer to private const void.
 */
typedef const PORT_KW_PRIVATE void* port_const_private_void_ptr_t;

/**
 * @brief Pointer to local non-const void.
 */
typedef PORT_KW_LOCAL void* port_local_void_ptr_t;
/**
 * @brief Pointer to local const void.
 */
typedef const PORT_KW_LOCAL void* port_const_local_void_ptr_t;

/**
 * @brief Pointer to constant void.
 */
typedef const PORT_KW_CONSTANT void* port_constant_void_ptr_t;

/**
 * @brief Pointer to global non-const void.
 */
typedef PORT_KW_GLOBAL void* port_global_void_ptr_t;
/**
 * @brief Pointer to global const void.
 */
typedef const PORT_KW_GLOBAL void* port_const_global_void_ptr_t;

///////////////////////////////////////////////////////////////////////////////
// Pointers to data
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Pointer to non-const memory units.
 */
typedef port_memory_unit_t* port_memory_ptr_t;
/**
 * @brief Pointer to const memory units.
 */
typedef const port_memory_unit_t* port_const_memory_ptr_t;

/**
 * @brief Pointer to private non-const memory units.
 */
typedef PORT_KW_PRIVATE port_memory_unit_t* port_private_memory_ptr_t;
/**
 * @brief Pointer to private const memory units.
 */
typedef const PORT_KW_PRIVATE port_memory_unit_t* port_const_private_memory_ptr_t;

/**
 * @brief Pointer to local non-const memory units.
 */
typedef PORT_KW_LOCAL port_memory_unit_t* port_local_memory_ptr_t;
/**
 * @brief Pointer to local const memory units.
 */
typedef const PORT_KW_LOCAL port_memory_unit_t* port_const_local_memory_ptr_t;

/**
 * @brief Pointer to constant memory units.
 */
typedef const PORT_KW_CONSTANT port_memory_unit_t* port_constant_memory_ptr_t;

/**
 * @brief Pointer to global non-const memory units.
 */
typedef PORT_KW_GLOBAL port_memory_unit_t* port_global_memory_ptr_t;
/**
 * @brief Pointer to global const memory units.
 */
typedef const PORT_KW_GLOBAL port_memory_unit_t* port_const_global_memory_ptr_t;

///////////////////////////////////////////////////////////////////////////////
// Pointers to pointers
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Table of memory pointers for far references.
 */
typedef const PORT_KW_CONSTANT port_const_global_memory_ptr_t* port_memory_table_t;

#endif // _PORT_MEMORY_TYP_H_

