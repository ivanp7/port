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
 * @brief Operations on memory.
 */

#pragma once
#ifndef _PORT_CDEV_MEMORY_FUN_H_
#define _PORT_CDEV_MEMORY_FUN_H_

#include <port/cdev/memory.typ.h>

///////////////////////////////////////////////////////////////////////////////
// Memory reference
///////////////////////////////////////////////////////////////////////////////

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
 *
 * @return Pointer to referenced memory.
 */
port_const_global_memory_ptr_t
port_memory_reference(
        port_memory_ref_t ref, ///< [in] Memory reference.

        port_uint8_t num_idx_bits, ///< [in] Number of index bits in far memory reference.
        port_uint8_t offset_shift, ///< [in] Argument for offset left shift in far memory reference.

        port_const_global_memory_ptr_t base_ptr, ///< [in] Base address for near references.
        port_memory_table_t memory_table ///< [in] Table of memory pointers for far references.
);

///////////////////////////////////////////////////////////////////////////////
// Memory copying
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Copy memory units from global memory to private memory.
 */
void
port_memcpy_global_to_private(
        port_private_memory_ptr_t restrict dest, ///< [out] Destination.
        port_const_global_memory_ptr_t restrict src, ///< [in] Source.
        port_size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from constant memory to private memory.
 */
void
port_memcpy_constant_to_private(
        port_private_memory_ptr_t restrict dest, ///< [out] Destination.
        port_constant_memory_ptr_t restrict src, ///< [in] Source.
        port_size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from local memory to private memory.
 */
void
port_memcpy_local_to_private(
        port_private_memory_ptr_t restrict dest, ///< [out] Destination.
        port_const_local_memory_ptr_t restrict src, ///< [in] Source.
        port_size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from private memory to private memory.
 */
void
port_memcpy_private_to_private(
        port_private_memory_ptr_t restrict dest, ///< [out] Destination.
        port_const_private_memory_ptr_t restrict src, ///< [in] Source.
        port_size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from global memory to local memory.
 */
void
port_memcpy_global_to_local(
        port_local_memory_ptr_t restrict dest, ///< [out] Destination.
        port_const_global_memory_ptr_t restrict src, ///< [in] Source.
        port_size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from constant memory to local memory.
 */
void
port_memcpy_constant_to_local(
        port_local_memory_ptr_t restrict dest, ///< [out] Destination.
        port_constant_memory_ptr_t restrict src, ///< [in] Source.
        port_size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from local memory to local memory.
 */
void
port_memcpy_local_to_local(
        port_local_memory_ptr_t restrict dest, ///< [out] Destination.
        port_const_local_memory_ptr_t restrict src, ///< [in] Source.
        port_size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from private memory to local memory.
 */
void
port_memcpy_private_to_local(
        port_local_memory_ptr_t restrict dest, ///< [out] Destination.
        port_const_private_memory_ptr_t restrict src, ///< [in] Source.
        port_size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from global memory to global memory.
 */
void
port_memcpy_global_to_global(
        port_global_memory_ptr_t restrict dest, ///< [out] Destination.
        port_const_global_memory_ptr_t restrict src, ///< [in] Source.
        port_size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from local memory to global memory.
 */
void
port_memcpy_local_to_global(
        port_global_memory_ptr_t restrict dest, ///< [out] Destination.
        port_const_local_memory_ptr_t restrict src, ///< [in] Source.
        port_size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from constant memory to global memory.
 */
void
port_memcpy_constant_to_global(
        port_global_memory_ptr_t restrict dest, ///< [out] Destination.
        port_constant_memory_ptr_t restrict src, ///< [in] Source.
        port_size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from private memory to global memory.
 */
void
port_memcpy_private_to_global(
        port_global_memory_ptr_t restrict dest, ///< [out] Destination.
        port_const_private_memory_ptr_t restrict src, ///< [in] Source.
        port_size_t num_units ///< [in] Number of units to copy.
);

///////////////////////////////////////////////////////////////////////////////
// Reading/writing of integers
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Read 64-bit unsigned integer from memory.
 *
 * @return Value read from memory.
 */
port_uint64_t
port_memread_uint64(
        port_const_memory_ptr_t memory ///< [in] Memory to read from.
);

/**
 * @brief Read 64-bit signed integer from memory.
 *
 * @return Value read from memory.
 */
port_sint64_t
port_memread_sint64(
        port_const_memory_ptr_t memory ///< [in] Memory to read from.
);

/**
 * @brief Write 64-bit unsigned integer to memory.
 */
void
port_memwrite_uint64(
        port_memory_ptr_t memory, ///< [out] Memory to write to.
        port_uint64_t value ///< [in] Value to write.
);

/**
 * @brief Write 64-bit signed integer to memory.
 */
void
port_memwrite_sint64(
        port_memory_ptr_t memory, ///< [out] Memory to write to.
        port_sint64_t value ///< [in] Value to write.
);

/**
 * @brief Read unsigned integer from memory.
 *
 * @return Value read from memory.
 */
port_uint_t
port_memread_uint(
        port_const_memory_ptr_t memory ///< [in] Memory to read from.
);

/**
 * @brief Read signed integer from memory.
 *
 * @return Value read from memory.
 */
port_sint_t
port_memread_sint(
        port_const_memory_ptr_t memory ///< [in] Memory to read from.
);

/**
 * @brief Write unsigned integer to memory.
 */
void
port_memwrite_uint(
        port_memory_ptr_t memory, ///< [out] Memory to write to.
        port_uint_t value ///< [in] Value to write.
);

/**
 * @brief Write signed integer to memory.
 */
void
port_memwrite_sint(
        port_memory_ptr_t memory, ///< [out] Memory to write to.
        port_sint_t value ///< [in] Value to write.
);

///////////////////////////////////////////////////////////////////////////////
// Reading/writing of floating-point numbers
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Read 64-bit floating-point number from memory.
 *
 * @return Value read from memory.
 */
port_float64_t
port_memread_float64(
        port_const_memory_ptr_t memory ///< [in] Memory to read from.
);

/**
 * @brief Write 64-bit floating-point number to memory.
 */
void
port_memwrite_float64(
        port_memory_ptr_t memory, ///< [out] Memory to write to.
        port_float64_t value ///< [in] Value to write.
);

/**
 * @brief Read floating-point number from memory.
 *
 * @return Value read from memory.
 */
port_float_t
port_memread_float(
        port_const_memory_ptr_t memory ///< [in] Memory to read from.
);

/**
 * @brief Write floating-point number to memory.
 */
void
port_memwrite_float(
        port_memory_ptr_t memory, ///< [out] Memory to write to.
        port_float_t value ///< [in] Value to write.
);

#endif // _PORT_CDEV_MEMORY_FUN_H_

