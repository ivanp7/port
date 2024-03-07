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
 * @brief Constants and macros for memory model types.
 */

#pragma once
#ifndef _PORT_CDEV_MEMORY_DEF_H_
#define _PORT_CDEV_MEMORY_DEF_H_

#include <port/cdev/bit.def.h>

///////////////////////////////////////////////////////////////////////////////
// Memory reference
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Number of bits enough to store any valid memory table index length --
 * number of index bits in far memory references.
 *
 * For 32-bit memory references, the value is 5 (2^5 = 32).
 * For 16-bit memory references, the value is 4 (2^4 = 16).
 * For  8-bit memory references, the value is 3 (2^3 = 8).
 */
#define PORT_MEMORY_REF_NUM_IDXLEN_BITS(ref_type) (sizeof(ref_type) / 2 + 3)

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

#endif // _PORT_CDEV_MEMORY_DEF_H_

