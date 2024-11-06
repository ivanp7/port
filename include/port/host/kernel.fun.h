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
 * @brief Functions for processing kernel arguments on host.
 */

#pragma once
#ifndef _PORT_HOST_KERNEL_FUN_H_
#define _PORT_HOST_KERNEL_FUN_H_

#include <port/cdev/work.typ.h>

struct port_kargs_cstate_ptrs;
struct port_kargs_cstate_sizes;
struct port_kargs_cparam_ptrs;
struct port_kargs_cparam_sizes;
struct port_kargs_segmented_memory_ptrs;
struct port_kargs_segmented_memory_sizes;
struct port_kargs_segmented_memory_table;

struct port_memory_operations_with_properties;

struct port_data_storage;

///////////////////////////////////////////////////////////////////////////////
// Computation states
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Allocate copy of arrays of sizes of computation states memory.
 *
 * @return True on success, otherwise false.
 */
port_bool_t
port_kargs_alloc_copy_cstate_sizes(
        struct port_kargs_cstate_sizes *sizes_dest, ///< [out] Sizes of computation state data (destination).
        const struct port_kargs_cstate_sizes *sizes_src, ///< [in] Sizes of computation state data (source).

        const struct port_memory_operations_with_properties *op_host ///< [in] Host memory operations.
);

/**
 * @brief Free arrays of sizes of computation states memory.
 */
void
port_kargs_free_cstate_sizes(
        struct port_kargs_cstate_sizes *sizes, ///< [in] Sizes of computation state data.

        const struct port_memory_operations_with_properties *op_host ///< [in] Host memory operations.
);

/**
 * @brief Allocate arrays of pointers to computation states memory.
 *
 * @return True on success, otherwise false.
 */
port_bool_t
port_kargs_alloc_cstate_arrays(
        struct port_kargs_cstate_ptrs *ptrs, ///< [out] Pointers to computation state data.
        const struct port_kargs_cstate_sizes *sizes, ///< [in] Sizes of computation state data.

        const struct port_memory_operations_with_properties *op_host ///< [in] Host memory operations.
);

/**
 * @brief Free arrays of pointers to computation states memory.
 */
void
port_kargs_free_cstate_arrays(
        struct port_kargs_cstate_ptrs *ptrs, ///< [in] Pointers to computation state data.
        const struct port_kargs_cstate_sizes *sizes, ///< [in] Sizes of computation state data.

        const struct port_memory_operations_with_properties *op_host ///< [in] Host memory operations.
);

/**
 * @brief Allocate memory for computation states.
 *
 * @return True on success, otherwise false.
 */
port_bool_t
port_kargs_alloc_cstate_memory(
        struct port_kargs_cstate_ptrs *ptrs, ///< [out] Pointers to computation state data.
        const struct port_kargs_cstate_sizes *sizes, ///< [in] Sizes of computation state data.

        const struct port_memory_operations_with_properties *op_cdev ///< [in] Compute device memory operations.
);

/**
 * @brief Free memory for computation states.
 */
void
port_kargs_free_cstate_memory(
        struct port_kargs_cstate_ptrs *ptrs, ///< [in] Pointers to computation state data.
        const struct port_kargs_cstate_sizes *sizes, ///< [in] Sizes of computation state data.

        const struct port_memory_operations_with_properties *op_cdev ///< [in] Compute device memory operations.
);

/**
 * @brief Copy computation states.
 *
 * @return True on success, otherwise false.
 */
port_bool_t
port_kargs_copy_cstate_memory(
        struct port_kargs_cstate_ptrs *ptrs_dest, ///< [out] Structure storing computation state data (destination).
        const struct port_kargs_cstate_ptrs *ptrs_src, ///< [in] Structure storing computation state data (source).
        const struct port_kargs_cstate_sizes *sizes, ///< [in] Sizes of computation state data.

        const struct port_memory_operations_with_properties *op_dest_cdev, ///< [in] Compute device memory operations (destination).
        const struct port_memory_operations_with_properties *op_src_cdev   ///< [in] Compute device memory operations (source).
);

///////////////////////////////////////////////////////////////////////////////
// Computation parameters
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Allocate copy of arrays of sizes of computation parameters memory.
 *
 * @return True on success, otherwise false.
 */
port_bool_t
port_kargs_alloc_copy_cparam_sizes(
        struct port_kargs_cparam_sizes *sizes_dest, ///< [out] Sizes of computation parameter data (destination).
        const struct port_kargs_cparam_sizes *sizes_src, ///< [in] Sizes of computation parameter data (source).

        const struct port_memory_operations_with_properties *op_host ///< [in] Host memory operations.
);

/**
 * @brief Free arrays of sizes of computation parameters memory.
 */
void
port_kargs_free_cparam_sizes(
        struct port_kargs_cparam_sizes *sizes, ///< [in] Sizes of computation parameter data.

        const struct port_memory_operations_with_properties *op_host ///< [in] Host memory operations.
);

/**
 * @brief Allocate arrays of pointers to computation parameters memory.
 *
 * @return True on success, otherwise false.
 */
port_bool_t
port_kargs_alloc_cparam_arrays(
        struct port_kargs_cparam_ptrs *ptrs, ///< [out] Pointers to computation parameter data.
        const struct port_kargs_cparam_sizes *sizes, ///< [in] Sizes of computation parameter data.

        const struct port_memory_operations_with_properties *op_host ///< [in] Host memory operations.
);

/**
 * @brief Free arrays of pointers to computation parameters memory.
 */
void
port_kargs_free_cparam_arrays(
        struct port_kargs_cparam_ptrs *ptrs, ///< [in] Pointers to computation parameter data.
        const struct port_kargs_cparam_sizes *sizes, ///< [in] Sizes of computation parameter data.

        const struct port_memory_operations_with_properties *op_host ///< [in] Host memory operations.
);

/**
 * @brief Allocate memory for computation parameters.
 *
 * @return True on success, otherwise false.
 */
port_bool_t
port_kargs_alloc_cparam_memory(
        struct port_kargs_cparam_ptrs *ptrs, ///< [out] Pointers to computation parameter data.
        const struct port_kargs_cparam_sizes *sizes, ///< [in] Sizes of computation parameter data.

        const struct port_memory_operations_with_properties *op_host, ///< [in] Host memory operations.
        const struct port_memory_operations_with_properties *op_cdev  ///< [in] Compute device memory operations.
);

/**
 * @brief Free memory for computation parameters.
 */
void
port_kargs_free_cparam_memory(
        struct port_kargs_cparam_ptrs *ptrs, ///< [in] Pointers to computation parameter data.
        const struct port_kargs_cparam_sizes *sizes, ///< [in] Sizes of computation parameter data.

        const struct port_memory_operations_with_properties *op_host, ///< [in] Host memory operations.
        const struct port_memory_operations_with_properties *op_cdev  ///< [in] Compute device memory operations.
);

/**
 * @brief Copy computation parameters.
 *
 * @return True on success, otherwise false.
 */
port_bool_t
port_kargs_copy_cparam_memory(
        struct port_kargs_cparam_ptrs *ptrs_dest, ///< [out] Structure storing computation parameter data (destination).
        const struct port_kargs_cparam_ptrs *ptrs_src, ///< [in] Structure storing computation parameter data (source).
        const struct port_kargs_cparam_sizes *sizes, ///< [in] Sizes of computation parameter data.

        const struct port_memory_operations_with_properties *op_dest_cdev, ///< [in] Compute device memory operations (destination).
        const struct port_memory_operations_with_properties *op_src_cdev   ///< [in] Compute device memory operations (source).
);

///////////////////////////////////////////////////////////////////////////////
// Segmented memory
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Allocate copy of arrays of sizes of segmented memory data.
 *
 * @return True on success, otherwise false.
 */
port_bool_t
port_kargs_alloc_copy_segmented_memory_sizes(
        struct port_kargs_segmented_memory_sizes *sizes_dest, ///< [out] Sizes of segmented memory data (destination).
        const struct port_kargs_segmented_memory_sizes *sizes_src, ///< [in] Sizes of segmented memory data (source).

        const struct port_memory_operations_with_properties *op_host ///< [in] Host memory operations.
);

/**
 * @brief Free arrays of sizes of segmented memory data.
 */
void
port_kargs_free_segmented_memory_sizes(
        struct port_kargs_segmented_memory_sizes *sizes, ///< [in] Sizes of segmented memory data.

        const struct port_memory_operations_with_properties *op_host ///< [in] Host memory operations.
);

/**
 * @brief Allocate copy of segmented memory table.
 *
 * @return Pointer to new segmented memory table.
 */
struct port_kargs_segmented_memory_table*
port_kargs_alloc_copy_segmented_memory_table(
        const struct port_kargs_segmented_memory_table *table_src, ///< [in] Segmented memory table (source).

        const struct port_memory_operations_with_properties *op_host ///< [in] Host memory operations.
);

/**
 * @brief Free segmented memory table.
 *
 * This function invalidates table pointer.
 */
void
port_kargs_free_segmented_memory_table(
        struct port_kargs_segmented_memory_table *table, ///< [in] Segmented memory table.

        const struct port_memory_operations_with_properties *op_host ///< [in] Host memory operations.
);

/**
 * @brief Allocate arrays of pointers to segmented memory data.
 *
 * @return True on success, otherwise false.
 */
port_bool_t
port_kargs_alloc_segmented_memory_arrays(
        struct port_kargs_segmented_memory_ptrs *ptrs, ///< [out] Pointers to segmented memory data.
        const struct port_kargs_segmented_memory_sizes *sizes, ///< [in] Sizes of segmented memory data.

        const struct port_memory_operations_with_properties *op_host ///< [in] Host memory operations.
);

/**
 * @brief Free arrays of pointers to segmented memory data.
 */
void
port_kargs_free_segmented_memory_arrays(
        struct port_kargs_segmented_memory_ptrs *ptrs, ///< [in] Pointers to segmented memory data.
        const struct port_kargs_segmented_memory_sizes *sizes, ///< [in] Sizes of segmented memory data.

        const struct port_memory_operations_with_properties *op_host ///< [in] Host memory operations.
);

/**
 * @brief Allocate segmented memory.
 *
 * @return True on success, otherwise false.
 */
port_bool_t
port_kargs_alloc_segmented_memory_memory(
        struct port_kargs_segmented_memory_ptrs *ptrs, ///< [out] Pointers to segmented memory data.
        const struct port_kargs_segmented_memory_sizes *sizes, ///< [in] Sizes of segmented memory data.
        const struct port_kargs_segmented_memory_table *table, ///< [in] Segmented memory table.

        const struct port_memory_operations_with_properties *op_cdev ///< [in] Compute device memory operations.
);

/**
 * @brief Free segmented memory.
 */
void
port_kargs_free_segmented_memory_memory(
        struct port_kargs_segmented_memory_ptrs *ptrs, ///< [in] Pointers to segmented memory data.
        const struct port_kargs_segmented_memory_sizes *sizes, ///< [in] Sizes of segmented memory data.
        const struct port_kargs_segmented_memory_table *table, ///< [in] Segmented memory table.

        const struct port_memory_operations_with_properties *op_cdev ///< [in] Compute device memory operations.
);

/**
 * @brief Copy segmented memory.
 *
 * @return True on success, otherwise false.
 */
port_bool_t
port_kargs_copy_segmented_memory_memory(
        struct port_kargs_segmented_memory_ptrs *ptrs_dest, ///< [out] Structure storing segmented memory data (destination).
        const struct port_kargs_segmented_memory_ptrs *ptrs_src, ///< [in] Structure storing segmented memory data (source).
        const struct port_kargs_segmented_memory_sizes *sizes, ///< [in] Sizes of segmented memory data.

        const struct port_memory_operations_with_properties *op_dest_cdev, ///< [in] Compute device memory operations (destination).
        const struct port_memory_operations_with_properties *op_src_cdev   ///< [in] Compute device memory operations (source).
);

/**
 * @brief Write segmented memory table.
 *
 * @return True on success, otherwise false.
 */
port_bool_t
port_kargs_write_segmented_memory_table(
        struct port_kargs_segmented_memory_ptrs *ptrs, ///< [out] Pointers to segmented memory data.
        const struct port_kargs_segmented_memory_sizes *sizes, ///< [in] Sizes of segmented memory data.
        const struct port_kargs_segmented_memory_table *table, ///< [in] Segmented memory table.

        const struct port_memory_operations_with_properties *op_cdev ///< [in] Compute device memory operations.
);

/**
 * @brief Construct segmented memory from a data storage.
 *
 * Root symbol is expected to be stored in the property with name "root".
 *
 * @return True on success, otherwise false.
 */
port_bool_t
port_kargs_construct_segmented_memory_from_data_storage(
        struct port_kargs_segmented_memory_ptrs *ptrs, ///< [out] Pointers to segmented memory data.
        struct port_kargs_segmented_memory_sizes *sizes, ///< [out] Sizes of segmented memory data.
        struct port_kargs_segmented_memory_table **table, ///< [out] Segmented memory table.

        const struct port_data_storage *storage, ///< [in] Data storage.

        const struct port_memory_operations_with_properties *op_host, ///< [in] Host memory operations.
        const struct port_memory_operations_with_properties *op_cdev  ///< [in] Compute device memory operations.
);

#endif // _PORT_HOST_KERNEL_FUN_H_

