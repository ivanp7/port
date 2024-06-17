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
 * @brief Function types for memory operations.
 */

#pragma once
#ifndef _PORT_HOST_BASE_MEMORY_TYP_H_
#define _PORT_HOST_BASE_MEMORY_TYP_H_

#include <port/cdev/memory.typ.h>

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

#endif // _PORT_HOST_BASE_MEMORY_TYP_H_

