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
// Data storage
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Data storage header.
 *
 * Because and due to symbols don't have contents,
 * symbol_table.contents_offset field have no ordinary meaning and
 * is to be ignored or interpreted specially.
 */
typedef struct port_data_storage_header {
    port_uint_single_t magic; ///< File format identification constant.
    port_uint_quarter_t header_size; ///< Header size in bytes.

    port_uint_quarter_t format[7]; ///< File format properties.
    port_uint_single_t full_size; ///< Full size of the data storage in memory units (including the header).

    struct {
        port_uint_single_t num_entries;     ///< Number of entries in a table.
        port_uint_single_t entries_offset;  ///< Offset of table entries in memory units.
        port_uint_single_t contents_offset; ///< Offset of contents of table entries in memory units.
    } string_table,         ///< Strings.
        section_table,      ///< Data sections.
        symbol_table,       ///< Symbols (references into sections).
        symbol_array_table; ///< Symbol arrays.
} port_data_storage_header_t;

/**
 * @brief Entry of data storage string table.
 */
typedef struct port_data_storage_string_table_entry {
    port_uint_single_t length; ///< String length in bytes.
    port_uint_single_t offset; ///< String offset in memory units.
} port_data_storage_string_table_entry_t;

/**
 * @brief Entry of data storage section table.
 */
typedef struct port_data_storage_section_table_entry {
    port_uint_single_t name_str_idx; ///< String table index of section name string.
    port_uint_single_t size;         ///< Section size in memory units.
    port_uint_single_t offset;       ///< Section offset in memory units.
} port_data_storage_section_table_entry_t;

/**
 * @brief Entry of data storage symbol table.
 *
 * Symbols have no contents.
 */
typedef struct port_data_storage_symbol_table_entry {
    port_uint_single_t name_str_idx; ///< String table index of symbol name string.
    port_uint_single_t section_idx;  ///< Index of section the symbol is relative to.
    port_uint_single_t value;        ///< Symbol offset in memory units relative to the section beginning.
} port_data_storage_symbol_table_entry_t;

/**
 * @brief Entry of data storage symbol array table.
 *
 * Array contents are table indices of symbols.
 */
typedef struct port_data_storage_symbol_array_table_entry {
    port_uint_single_t name_str_idx; ///< String table index of symbol array name string.
    port_uint_single_t num_elements; ///< Number of symbols in the array.
    port_uint_single_t offset;       ///< Array offset in memory units.
} port_data_storage_symbol_array_table_entry_t;

#endif // _PORT_HOST_COMMON_MEMORY_TYP_H_

