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
 * @brief Data storage representation and format.
 */

#pragma once
#ifndef _PORT_HOST_STORAGE_TYP_H_
#define _PORT_HOST_STORAGE_TYP_H_

#include <port/cdev/memory.typ.h>

///////////////////////////////////////////////////////////////////////////////
// Storage representation in memory
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Data storage in memory.
 */
typedef struct port_data_storage {
    struct {
        port_void_ptr_t *sections; ///< Sections.
        port_void_ptr_t *properties; ///< Values of properties.
        char **strings; ///< Array of strings used as names of sections, symbols, properties.
    } content; ///< Contents of things.

    struct {
        port_uint_single_t *sections; ///< Sizes of sections.
        port_uint_single_t *properties; ///< Sizes of properties values.
    } size; // Sizes of contents.

    struct {
        port_uint_single_t *section_idx; ///< Indices of sections symbols belong to.
        port_uint_single_t *values; ///< Values (offsets) of symbols.
    } symbol; ///< Symbols.

    struct {
        port_uint_single_t *sections; ///< Indices of strings that are section names.
        port_uint_single_t *symbols; ///< Indices of strings that are symbol names.
        port_uint_single_t *properties; ///< Indices of strings that are property names.
    } name_str_idx; ///< Indices of strings that are thing names.

    struct {
        port_uint_single_t sections; ///< Number of sections.
        port_uint_single_t symbols; ///< Number of symbols.
        port_uint_single_t properties; ///< Number of properties.
        port_uint_single_t strings; ///< Number of strings.
    } num; ///< Numbers of things.
} port_data_storage_t;

///////////////////////////////////////////////////////////////////////////////
// Storage file format
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Data storage header.
 */
typedef struct port_data_storage_file_header {
    port_uint_single_t format;    ///< Description of the data storage format.
    port_uint_single_t full_size; ///< Full size of the data storage excluding header.

    struct {
        port_uint_single_t num_entries;    ///< Number of entries in a table.
        port_uint_single_t entries_offset; ///< Offset of table entries.
    } string_table,     ///< Strings.
        property_table, ///< Properties (named values).
        section_table,  ///< Data sections.
        symbol_table;   ///< Symbols (references into sections).

    struct {
        port_uint_single_t contents_size;   ///< Size of contents.
        port_uint_single_t contents_offset; ///< Offset to contents.
    } strings,      ///< Strings.
        properties, ///< Properties.
        sections;   ///< Data sections.
} port_data_storage_file_header_t;

/**
 * @brief Entry of data storage string table.
 */
typedef struct port_data_storage_file_string_table_entry {
    port_uint_single_t length; ///< String length.
    port_uint_single_t offset; ///< String offset.
} port_data_storage_file_string_table_entry_t;

/**
 * @brief Entry of data storage property table.
 */
typedef struct port_data_storage_file_property_table_entry {
    port_uint_single_t name_str_idx; ///< String table index of property name string.
    port_uint_single_t size;         ///< Property value size.
    port_uint_single_t offset;       ///< Property value offset.
} port_data_storage_file_property_table_entry_t;

/**
 * @brief Entry of data storage section table.
 */
typedef struct port_data_storage_file_section_table_entry {
    port_uint_single_t name_str_idx; ///< String table index of section name string.
    port_uint_single_t size;         ///< Section size.
    port_uint_single_t offset;       ///< Section offset.
} port_data_storage_file_section_table_entry_t;

/**
 * @brief Entry of data storage symbol table.
 *
 * Symbols have no contents.
 */
typedef struct port_data_storage_file_symbol_table_entry {
    port_uint_single_t name_str_idx; ///< String table index of symbol name string.
    port_uint_single_t section_idx;  ///< Index of section the symbol is relative to.
    port_uint_single_t value;        ///< Symbol offset relative to the section beginning.
} port_data_storage_file_symbol_table_entry_t;

#endif // _PORT_HOST_STORAGE_TYP_H_

