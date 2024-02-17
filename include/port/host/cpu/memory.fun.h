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
 * @brief Functions for memory operations.
 */

#pragma once
#ifndef _PORT_HOST_CPU_MEMORY_FUN_H_
#define _PORT_HOST_CPU_MEMORY_FUN_H_

#include <port/cdev/memory.typ.h>

/**
 * @brief Memory allocator function.
 *
 * If alignment is 0, malloc() is used, otherwise aligned_alloc() is used.
 *
 * Parameter properties is ignored.
 *
 * @return Newly allocated memory or NULL.
 */
port_void_ptr_t
port_memory_cpu_alloc(
        port_size_t num_bytes, ///< [in] Number of bytes to allocate.
        port_size_t alignment, ///< [in] Memory alignment.
        port_void_ptr_t properties ///< [in] Memory allocator properties.
);

/**
 * @brief Memory deallocator function.
 *
 * free() is used for memory deallocation.
 *
 * Parameter properties is ignored.
 */
void
port_memory_cpu_free(
        port_void_ptr_t memory, ///< [in] Memory to deallocate.
        port_void_ptr_t properties ///< [in] Memory deallocator properties.
);

/**
 * @brief Memory mapping function.
 *
 * This function does nothing.
 *
 * @return True if succeed, otherwise false.
 */
port_bool_t
port_memory_cpu_map(
        port_void_ptr_t memory, ///< [in] Memory to map.
        port_size_t num_bytes, ///< [in] Number of bytes to allocate.
        port_void_ptr_t properties ///< [in] Memory mapping properties.
);

/**
 * @brief Memory unmapping function.
 *
 * This function does nothing.
 *
 * @return True if succeed, otherwise false.
 */
port_bool_t
port_memory_cpu_unmap(
        port_void_ptr_t memory, ///< [in] Memory to unmap.
        port_void_ptr_t properties ///< [in] Memory unmapping properties.
);

#endif // _PORT_HOST_CPU_MEMORY_FUN_H_

