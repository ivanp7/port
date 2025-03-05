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
 * @brief Types for memory handling on host.
 */

#pragma once
#ifndef _PORT_HOST_MEMORY_TYP_H_
#define _PORT_HOST_MEMORY_TYP_H_

#include "port/cdev/memory.typ.h"

#include <stdalign.h>

/**
 * @brief Alignment of largest data type supported by OpenCL.
 */
#define PORT_ALIGNMENT_MAX alignof(port_uint64_v16_t)

/**
 * @brief Memory allocator function.
 *
 * @return Newly allocated memory or NULL.
 */
typedef port_void_ptr_t (*port_memory_alloc_func_t)(
        port_size_t num_bytes, ///< [in] Number of bytes to allocate.
        port_size_t alignment, ///< [in] Memory alignment.
        port_void_ptr_t properties ///< [in] Memory allocator properties.
);

/**
 * @brief Memory deallocator function.
 */
typedef void (*port_memory_free_func_t)(
        port_void_ptr_t memory, ///< [in] Memory to deallocate.
        port_void_ptr_t properties ///< [in] Memory deallocator properties.
);

/**
 * @brief Memory mapping function.
 *
 * @return True if succeed, otherwise false.
 */
typedef port_bool_t (*port_memory_map_func_t)(
        port_void_ptr_t memory, ///< [in] Memory to map.
        port_size_t num_bytes, ///< [in] Number of bytes to allocate.
        port_void_ptr_t properties ///< [in] Memory mapping properties.
);

/**
 * @brief Memory unmapping function.
 *
 * @return True if succeed, otherwise false.
 */
typedef port_bool_t (*port_memory_unmap_func_t)(
        port_void_ptr_t memory, ///< [in] Memory to unmap.
        port_void_ptr_t properties ///< [in] Memory unmapping properties.
);

///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Memory allocator operations.
 */
typedef struct port_memory_allocator_operations {
    port_memory_alloc_func_t alloc_fn; ///< Memory allocation function.
    port_memory_free_func_t free_fn;   ///< Memory deallocation function.
    port_memory_map_func_t map_fn;     ///< Memory mapping function.
    port_memory_unmap_func_t unmap_fn; ///< Memory unmapping function.
} port_memory_allocator_operations_t;

/**
 * @brief Memory allocator properties.
 */
typedef struct port_memory_allocator_properties {
    port_void_ptr_t alloc; ///< Properties for allocator/deallocator functions.
    port_void_ptr_t map;   ///< Properties for mapping/unmapping functions.
} port_memory_allocator_properties_t;

/**
 * @brief Memory allocator.
 */
typedef struct port_memory_allocator {
    port_memory_allocator_operations_t operations; ///< Memory allocator operations.
    port_memory_allocator_properties_t properties; ///< Memory allocator properties.
} port_memory_allocator_t;

#endif // _PORT_HOST_MEMORY_TYP_H_

