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

///////////////////////////////////////////////////////////////////////////////
// Memory operations
///////////////////////////////////////////////////////////////////////////////

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
// Data storage
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Data storage header.
 */
typedef struct port_data_storage_header {
    port_uint_single_t format;    ///< Description of the data storage format.
    port_uint_single_t full_size; ///< Full size of the data storage.

    struct {
        port_uint_single_t num_entries;    ///< Number of entries in a table.
        port_uint_single_t entries_offset; ///< Offset of table entries.
    } string_table,     ///< Strings.
        section_table,  ///< Data sections.
        symbol_table,   ///< Symbols (references into sections).
        property_table; ///< Properties (named values).

    struct {
        port_uint_single_t contents_size;   ///< Size of contents.
        port_uint_single_t contents_offset; ///< Offset to contents.
    } strings,      ///< Strings.
        sections,   ///< Data sections.
        properties; ///< Properties.
} port_data_storage_header_t;

/**
 * @brief Entry of data storage string table.
 */
typedef struct port_data_storage_string_table_entry {
    port_uint_single_t length; ///< String length.
    port_uint_single_t offset; ///< String offset.
} port_data_storage_string_table_entry_t;

/**
 * @brief Entry of data storage section table.
 */
typedef struct port_data_storage_section_table_entry {
    port_uint_single_t name_str_idx; ///< String table index of section name string.
    port_uint_single_t size;         ///< Section size.
    port_uint_single_t offset;       ///< Section offset.
} port_data_storage_section_table_entry_t;

/**
 * @brief Entry of data storage symbol table.
 *
 * Symbols have no contents.
 */
typedef struct port_data_storage_symbol_table_entry {
    port_uint_single_t name_str_idx; ///< String table index of symbol name string.
    port_uint_single_t section_idx;  ///< Index of section the symbol is relative to.
    port_uint_single_t value;        ///< Symbol offset relative to the section beginning.
} port_data_storage_symbol_table_entry_t;

/**
 * @brief Entry of data storage property table.
 */
typedef struct port_data_storage_property_table_entry {
    port_uint_single_t name_str_idx; ///< String table index of property name string.
    port_uint_single_t size;         ///< Property value size.
    port_uint_single_t offset;       ///< Property value offset.
} port_data_storage_property_table_entry_t;

#endif // _PORT_HOST_BASE_MEMORY_TYP_H_

