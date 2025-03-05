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
 * @brief Types for handling kernel arguments.
 */

#pragma once
#ifndef _PORT_HOST_KERNEL_TYP_H_
#define _PORT_HOST_KERNEL_TYP_H_

#include "port/cdev/memory.typ.h"
#include "port/cdev/work.typ.h"

struct port_memory_allocator;
struct port_memory_allocator_properties;

///////////////////////////////////////////////////////////////////////////////
// Computation states
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Pointers to computation state data.
 */
typedef struct port_kargs_cstate_ptrs {
    port_void_ptr_t *arrays; ///< Computation state arrays.
} port_kargs_cstate_ptrs_t;

/**
 * @brief Sizes of computation state data.
 */
typedef struct port_kargs_cstate_sizes {
    port_size_t *sizes; ///< Array of sizes.
    port_size_t num_of; ///< Number of elements in array of sizes.
} port_kargs_cstate_sizes_t;

///////////////////////////////////////////////////////////////////////////////
// Computation parameters
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Pointers to computation parameters data.
 */
typedef struct port_kargs_cparam_ptrs {
    port_void_ptr_t *structures; ///< Computation parameter structures.
    port_void_ptr_t *arrays;     ///< Computation parameter arrays.
} port_kargs_cparam_ptrs_t;

/**
 * @brief Sizes of computation parameters data.
 */
typedef struct port_kargs_cparam_sizes {
    struct {
        port_size_t *sizes; ///< Array of sizes.
        port_size_t num_of; ///< Number of elements in array of sizes.
    } structures, ///< Sizes of computation parameter structures.
        arrays;   ///< Sizes of computation parameter arrays.
} port_kargs_cparam_sizes_t;

///////////////////////////////////////////////////////////////////////////////
// Segmented memory
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Pointers to segmented memory data.
 */
typedef struct port_kargs_segmented_memory_ptrs {
    port_void_ptr_t *segments; ///< Array of pointers to memory segments.

    port_void_ptr_t *table; ///< Table of pointers into the memory segments.
    port_void_ptr_t root;   ///< Root pointer of segmented memory.
} port_kargs_segmented_memory_ptrs_t;

/**
 * @brief Sizes of segmented memory data.
 */
typedef struct port_kargs_segmented_memory_sizes {
    port_size_t *segment_sizes; ///< Sizes of segments.
    port_size_t num_segments;   ///< Number of segments.

    port_size_t num_table_entries; ///< Number of table entries.
} port_kargs_segmented_memory_sizes_t;

/**
 * @brief Segmented memory symbol.
 */
typedef struct port_kargs_segmented_memory_symbol {
    port_size_t segment_idx; ///< Index of memory segment.
    port_size_t value;       ///< Offset from the segment beginning.
} port_kargs_segmented_memory_symbol_t;

/**
 * @brief Segmented memory table.
 */
typedef struct port_kargs_segmented_memory_table {
    port_kargs_segmented_memory_symbol_t root_symbol;     ///< Symbol defining root pointer.
    port_kargs_segmented_memory_symbol_t table_symbols[]; ///< Symbols defining memory table entries.
} port_kargs_segmented_memory_table_t;

///////////////////////////////////////////////////////////////////////////////
// Kernel arguments meta information
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Kernel arguments metainfo copy allocation function.
 *
 * @return Allocated kernel arguments metainfo, or NULL in case of failure.
 */
typedef port_void_ptr_t (*port_kargs_metainfo_alloc_copy_func_t)(
        port_const_void_ptr_t metainfo, ///< [in] Meta information of kernel arguments.

        const struct port_memory_allocator *ma_host ///< [in] Host memory allocator.
);

/**
 * @brief Kernel arguments metainfo copy deallocation function.
 *
 * @return True on success, otherwise false.
 */
typedef void (*port_kargs_metainfo_free_func_t)(
        port_void_ptr_t metainfo, ///< [in] Meta information of kernel arguments.

        const struct port_memory_allocator *ma_host ///< [in] Host memory allocator.
);

/**
 * @brief Kernel work size getter for kernel arguments metainfo.
 *
 * @return Maximum work size for the kernel.
 */
typedef port_work_size_t (*port_kargs_metainfo_work_size_getter_func_t)(
        port_const_void_ptr_t metainfo, ///< [in] Meta information of kernel arguments.
        port_size_t work_type ///< [in] Index of work type.
);

///////////////////////////////////////////////////////////////////////////////
// Kernel arguments
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Kernel arguments allocation function.
 *
 * @return Allocated kernel arguments, or NULL in case of failure.
 */
typedef port_void_ptr_t (*port_kargs_alloc_func_t)(
        port_const_void_ptr_t metainfo, ///< [in] Meta information of kernel arguments.

        const struct port_memory_allocator *ma_host, ///< [in] Host memory allocator.
        const struct port_memory_allocator *ma_cdev, ///< [in] Compute device memory allocator (read-write).
        const struct port_memory_allocator_properties *ma_prop_cdev_ro, ///< [in] Compute device memory allocator properties (read-only).
        const struct port_memory_allocator_properties *ma_prop_cdev_wo  ///< [in] Compute device memory allocator properties (write-only).
);

/**
 * @brief Kernel arguments deallocation function.
 */
typedef void (*port_kargs_free_func_t)(
        port_void_ptr_t kargs, ///< [in] Kernel arguments to deallocate.

        const struct port_memory_allocator *ma_host, ///< [in] Host memory allocator.
        const struct port_memory_allocator *ma_cdev  ///< [in] Compute device memory allocator.
);

/**
 * @brief Kernel arguments copy function.
 *
 * Meta information of source and destination must be compatible for copying.
 *
 * @return True on success, otherwise false.
 */
typedef port_bool_t (*port_kargs_copy_func_t)(
        port_void_ptr_t kargs_dest,      ///< [out] Kernel arguments to copy to.
        port_const_void_ptr_t kargs_src, ///< [in] Kernel arguments to be copied.

        port_bool_t copy_read_only, ///< [in] Whether to copy read-only (by kernels) data too.

        const struct port_memory_allocator *ma_host,      ///< [in] Host memory allocator.
        const struct port_memory_allocator *ma_cdev_dest, ///< [in] Compute device memory allocator for destination memory.
        const struct port_memory_allocator *ma_cdev_src   ///< [in] Compute device memory allocator for source memory.
);

/**
 * @brief Meta information getter function for kernel arguments structure.
 *
 * @return Meta information of kernel arguments.
 */
typedef port_const_void_ptr_t (*port_kargs_metainfo_getter_func_t)(
        port_const_void_ptr_t kargs ///< [in] Kernel arguments.
);

///////////////////////////////////////////////////////////////////////////////
// Kernel arguments
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Set of operations on kernel arguments.
 */
typedef struct port_kargs_operations {
    struct {
        port_kargs_metainfo_alloc_copy_func_t alloc_copy_fn; ///< Kernel arguments metainfo copy allocation function.
        port_kargs_metainfo_free_func_t free_fn; ///< Kernel arguments metainfo deallocation function.
        port_kargs_metainfo_work_size_getter_func_t work_size_getter_fn; ///< Kernel work size getter function.
    } metainfo; ///< Kernel arguments meta information.

    port_kargs_alloc_func_t alloc_fn; ///< Kernel arguments allocation function.
    port_kargs_free_func_t free_fn;   ///< Kernel arguments deallocation function.
    port_kargs_copy_func_t copy_fn;   ///< Kernel arguments copy function.
    port_kargs_metainfo_getter_func_t metainfo_getter_fn; ///< Kernel arguments metainfo getter function.
} port_kargs_operations_t;

#endif // _PORT_HOST_KERNEL_TYP_H_

