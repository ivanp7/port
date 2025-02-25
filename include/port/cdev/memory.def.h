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
#ifndef _PORT_CDEV_MEMORY_DEF_H_
#define _PORT_CDEV_MEMORY_DEF_H_

#include <port/cdev/bit.def.h>
#include <port/cdev/types.def.h>

///////////////////////////////////////////////////////////////////////////////
// Memory reference
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Construct far memory reference.
 *
 * Layout of far memory reference:
 *
 * [...offset|memory_table_index]
 *            ^^^^^^^^^^^^^^^^^^
 *               num_idx_bits
 */
#define PORT_MEMORY_REF_FAR(ref_type, num_idx_bits, idx, offset) \
    PORT_CONCAT_BITS(ref_type, offset, num_idx_bits, idx)

/**
 * @brief Check if memory reference is far.
 */
#define PORT_MEMORY_REF_IS_FAR(ref) ((ref) >= 0)

/**
 * @brief Parse far memory reference.
 */
#define PORT_MEMORY_REF_FAR_PARSE(ref, ref_type, num_idx_bits, idx_ptr, offset_ptr) do { \
    PORT_EXTRACT_LSBITS_TO((idx_ptr), ref_type, (ref), (num_idx_bits));                  \
    PORT_EXTRACT_MSBITS_TO((offset_ptr), ref_type, (ref), (num_idx_bits));               \
} while (0)

/**
 * @brief Follow memory reference.
 *
 * Meaning of a memory reference value is different depending on its sign.
 *
 * If reference < 0, then it is a local offset in memory units,
 * so address = base_ptr - reference
 *
 * If reference >= 0, then its value is interpreted as
 * reference = (offset << num_idx_bits) | memory_table_index,
 * so address = memory_table[memory_table_index] + (offset << offset_shift).
 *
 * If base_ptr is NULL, memory_table[0] is used instead.
 */
#define PORT_MEMORY_REFERENCE(ref, num_idx_bits, offset_shift, base_ptr, memory_table) \
    (PORT_MEMORY_REF_IS_FAR(ref) ?                                  \
     (memory_table)[(ref) & PORT_SINGLE_ZMASK(num_idx_bits)] +      \
     ((port_size_t)((ref) >> (num_idx_bits)) << (offset_shift)) :   \
     (((base_ptr) ? (base_ptr) : (memory_table)[0]) - (ref)))

/**
 * @brief Number of bits enough to store any valid memory table index length --
 * number of index bits in far memory references.
 *
 * For 32-bit memory references, the value is 5 (2^5 = 32).
 * For 16-bit memory references, the value is 4 (2^4 = 16).
 * For  8-bit memory references, the value is 3 (2^3 = 8).
 */
#define PORT_MEMORY_REF_NUM_IDXLEN_BITS(ref_type) \
    (sizeof(ref_type) / 2 + PORT_NUM_BYTE_BITS_LOG2)

/**
 * @brief Invalid value of a memory reference log2(size).
 */
#define PORT_MEMORY_REF_SIZE_INVALID PORT_TYPE_SIZE_DOUBLE

/**
 * @brief Normalize unit-byte pair of indices.
 */
#define PORT_MEMORY_IDX_NORMALIZE(unit_idx, subunit_idx, subunit_size) do {  \
    (unit_idx) += (subunit_idx) >> (PORT_TYPE_SIZE_SINGLE - (subunit_size)); \
    (subunit_idx) &= (1 << (PORT_TYPE_SIZE_SINGLE - (subunit_size))) - 1;    \
} while (0)

#endif // _PORT_CDEV_MEMORY_DEF_H_

