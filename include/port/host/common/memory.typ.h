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
#ifndef _PORT_HOST_COMMON_MEMORY_TYP_H_
#define _PORT_HOST_COMMON_MEMORY_TYP_H_

#include <port/cdev/memory.typ.h>

///////////////////////////////////////////////////////////////////////////////
// Memory operations
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Memory allocator function.
 *
 * @return Newly allocated memory or NULL.
 */
typedef port_memory_ptr_t (*port_memory_alloc_func_t)(
        port_size_t num_bytes, ///< [in] Number of bytes to allocate.
        port_size_t alignment, ///< [in] Memory alignment.
        port_void_ptr_t properties ///< [in] Memory allocator properties.
);

/**
 * @brief Memory deallocator function.
 */
typedef void (*port_memory_free_func_t)(
        port_memory_ptr_t memory, ///< [in] Memory to deallocate.
        port_void_ptr_t properties ///< [in] Memory deallocator properties.
);

/**
 * @brief Memory mapping function.
 *
 * @return True if succeed, otherwise false.
 */
typedef port_bool_t (*port_memory_map_func_t)(
        port_memory_ptr_t memory, ///< [in] Memory to map.
        port_size_t num_bytes, ///< [in] Number of bytes to allocate.
        port_void_ptr_t properties ///< [in] Memory mapping properties.
);

/**
 * @brief Memory unmapping function.
 *
 * @return True if succeed, otherwise false.
 */
typedef port_bool_t (*port_memory_unmap_func_t)(
        port_memory_ptr_t memory, ///< [in] Memory to unmap.
        port_void_ptr_t properties ///< [in] Memory unmapping properties.
);

///////////////////////////////////////////////////////////////////////////////
// Memory storage
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Memory storage section.
 */
typedef struct port_memory_storage_section {
    const char *name; ///< Section name (allocated).

    port_void_ptr_t storage; ///< Implementation-specific handle of storage the section is associated with.

    port_memory_ptr_t contents; ///< Section contents.
    port_size_t size; ///< Size of section contents in units.

    port_void_ptr_t data; ///< Custom application data.

    struct port_memory_storage_section *next; ///< Next section in the list.
} port_memory_storage_section_t;

/**
 * @brief Memory storage symbol.
 */
typedef struct port_memory_storage_symbol {
    const char *name; ///< Symbol name (allocated).

    port_memory_storage_section_t *section; ///< Section the symbol is relative to.
    port_size_t offset; ///< Offset of the symbol in units.

    port_void_ptr_t data; ///< Custom application data.

    struct port_memory_storage_symbol *next; ///< Next symbol in the list.
} port_memory_storage_symbol_t;

/**
 * @brief Memory storage section filter function.
 *
 * @return True if section passes the filter, otherwise false.
 */
typedef port_bool_t (*port_memory_storage_section_filter_func_t)(
        const char *section_name ///< [in] Section name.
);

/**
 * @brief Memory storage symbol filter function.
 *
 * @return True if symbol passes the filter, otherwise false.
 */
typedef port_bool_t (*port_memory_storage_symbol_filter_func_t)(
        const char *symbol_name, ///< [in] Symbol name.
        const char *section_name ///< [in] Section name.
);

#endif // _PORT_HOST_COMMON_MEMORY_TYP_H_

