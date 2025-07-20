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
 * @brief Constants and macros for memory model types.
 */

#pragma once
#ifndef _PORT_MEMORY_DEF_H_
#define _PORT_MEMORY_DEF_H_

#include "port/bit.def.h"

/**
 * @brief Check if memory reference is far.
 *
 * Meaning of a memory reference value is different depending on its sign.
 * If reference >= 0, then it is a far reference, otherwise it is a near reference.
 */
#define PORT_MEMORY_REF_IS_FAR(ref) ((ref) >= 0)

/**
 * @brief Construct far memory reference.
 *
 * Layout of far memory reference:
 *
 * reference = (offset << num_tidx_bits) | table_index
 *
 * [...offset|table_index]
 *            ^^^^^^^^^^^
 *          <num_tidx_bits>
 */
#define PORT_MEMORY_REF_FAR(ref_type, num_tidx_bits, table_index, offset) \
    PORT_CONCAT_BITS(ref_type, (offset), (num_tidx_bits), (table_index))

/**
 * @brief Extract memory table index from a far reference.
 */
#define PORT_MEMORY_REF_FAR__TABLE_INDEX(ref, num_tidx_bits) \
    PORT_EXTRACT_LSBITS(port_uint_single_t, (ref), (num_tidx_bits))

/**
 * @brief Extract offset from a far reference.
 */
#define PORT_MEMORY_REF_FAR__OFFSET(ref, num_tidx_bits) \
    PORT_EXTRACT_MSBITS(size_t, (ref), (num_tidx_bits))

/**
 * @brief Follow far memory reference.
 *
 * address = memory_table[reference.table_index] + (reference.offset << offset_shift).
 */
#define PORT_MEMORY_FAR_AT(ref, num_tidx_bits, offset_shift, memory_table) \
    ((memory_table)[PORT_MEMORY_REF_FAR__TABLE_INDEX((ref), (num_tidx_bits))] \
     + (PORT_MEMORY_REF_FAR__OFFSET((ref), (num_tidx_bits)) << (offset_shift)))

/**
 * @brief Follow near memory reference.
 *
 * Reference is a local offset in memory units,
 * so address = base_ptr - reference.
 *
 * If base_ptr is NULL, alt_base_ptr is used instead.
 */
#define PORT_MEMORY_NEAR_AT(ref, base_ptr, alt_base_ptr) \
    (((base_ptr) ? (base_ptr) : (alt_base_ptr)) - (ref))

/**
 * @brief Follow memory reference.
 */
#define PORT_MEMORY_AT(ref, num_tidx_bits, offset_shift, base_ptr, memory_table) \
    (PORT_MEMORY_REF_IS_FAR(ref) ? \
     PORT_MEMORY_FAR_AT((ref), (num_tidx_bits), (offset_shift), (memory_table)) : \
     PORT_MEMORY_NEAR_AT((ref), (base_ptr), (memory_table)[0]))

/**
 * @brief Number of bits enough for storing any bit number in port_memory_ref_quarter_t.
 */
#define PORT_MEMORY_REF_QUARTER_LOGBITSIZE  3
/**
 * @brief Number of bits enough for storing any bit number in port_memory_ref_half_t.
 */
#define PORT_MEMORY_REF_HALF_LOGBITSIZE     4
/**
 * @brief Number of bits enough for storing any bit number in port_memory_ref_t.
 */
#define PORT_MEMORY_REF_LOGBITSIZE          5

#endif // _PORT_MEMORY_DEF_H_

