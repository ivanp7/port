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
 * @brief Data storage representation and format.
 */

#include "port/host/storage.fun.h"
#include "port/host/storage.typ.h"

#include <stdlib.h>
#include <string.h>
#include <limits.h>

port_bool_t
port_check_data_storage_file_header_validity(
        const port_data_storage_file_header_t *file_header)
{
    if (file_header == NULL)
        return false;

    // Check tables and contents are within file size
    {
        if (file_header->string_table.entries_offset > file_header->full_size)
            return false;

        if (file_header->string_table.num_entries * sizeof(port_data_storage_file_string_table_entry_t) >
                file_header->full_size - file_header->string_table.entries_offset)
            return false;

        if (file_header->strings.contents_offset > file_header->full_size)
            return false;

        if (file_header->strings.contents_size > file_header->full_size - file_header->strings.contents_offset)
            return false;
    }

    {
        if (file_header->property_table.entries_offset > file_header->full_size)
            return false;

        if (file_header->property_table.num_entries * sizeof(port_data_storage_file_property_table_entry_t) >
                file_header->full_size - file_header->property_table.entries_offset)
            return false;

        if (file_header->properties.contents_offset > file_header->full_size)
            return false;

        if (file_header->properties.contents_size > file_header->full_size - file_header->properties.contents_offset)
            return false;
    }

    {
        if (file_header->section_table.entries_offset > file_header->full_size)
            return false;

        if (file_header->section_table.num_entries * sizeof(port_data_storage_file_section_table_entry_t) >
                file_header->full_size - file_header->section_table.entries_offset)
            return false;

        if (file_header->sections.contents_offset > file_header->full_size)
            return false;

        if (file_header->sections.contents_size > file_header->full_size - file_header->sections.contents_offset)
            return false;
    }

    {
        if (file_header->symbol_table.entries_offset > file_header->full_size)
            return false;

        if (file_header->symbol_table.num_entries * sizeof(port_data_storage_file_symbol_table_entry_t) >
                file_header->full_size - file_header->symbol_table.entries_offset)
            return false;
    }

    // Check contents are not empty for non-empty tables
    if ((file_header->string_table.num_entries > 0) && (file_header->strings.contents_size == 0))
        return false;

    if ((file_header->property_table.num_entries > 0) && (file_header->properties.contents_size == 0))
        return false;

    if ((file_header->section_table.num_entries > 0) && (file_header->sections.contents_size == 0))
        return false;

    // Check tables and contents don't collide
#define CHECK_COLLISION(offset1, size1, offset2, size2) do { \
    if ((file_header->size1 > 0) && (file_header->size2 > 0) && \
            (file_header->offset1 + file_header->size1 > file_header->offset2) && \
            (file_header->offset2 + file_header->size2 > file_header->offset1)) \
        return false; } while (0)

    if (file_header->string_table.num_entries > 0)
    {
        CHECK_COLLISION(string_table.entries_offset,
                string_table.num_entries * sizeof(port_data_storage_file_string_table_entry_t),
                property_table.entries_offset,
                property_table.num_entries * sizeof(port_data_storage_file_property_table_entry_t));

        CHECK_COLLISION(string_table.entries_offset,
                string_table.num_entries * sizeof(port_data_storage_file_string_table_entry_t),
                section_table.entries_offset,
                section_table.num_entries * sizeof(port_data_storage_file_section_table_entry_t));

        CHECK_COLLISION(string_table.entries_offset,
                string_table.num_entries * sizeof(port_data_storage_file_string_table_entry_t),
                symbol_table.entries_offset,
                symbol_table.num_entries * sizeof(port_data_storage_file_symbol_table_entry_t));

        CHECK_COLLISION(string_table.entries_offset,
                string_table.num_entries * sizeof(port_data_storage_file_string_table_entry_t),
                strings.contents_offset,
                strings.contents_size);

        CHECK_COLLISION(string_table.entries_offset,
                string_table.num_entries * sizeof(port_data_storage_file_string_table_entry_t),
                properties.contents_offset,
                properties.contents_size);

        CHECK_COLLISION(string_table.entries_offset,
                string_table.num_entries * sizeof(port_data_storage_file_string_table_entry_t),
                sections.contents_offset,
                sections.contents_size);
    }

    if (file_header->property_table.num_entries > 0)
    {
        CHECK_COLLISION(property_table.entries_offset,
                property_table.num_entries * sizeof(port_data_storage_file_property_table_entry_t),
                section_table.entries_offset,
                section_table.num_entries * sizeof(port_data_storage_file_section_table_entry_t));

        CHECK_COLLISION(property_table.entries_offset,
                property_table.num_entries * sizeof(port_data_storage_file_property_table_entry_t),
                symbol_table.entries_offset,
                symbol_table.num_entries * sizeof(port_data_storage_file_symbol_table_entry_t));

        CHECK_COLLISION(property_table.entries_offset,
                property_table.num_entries * sizeof(port_data_storage_file_property_table_entry_t),
                strings.contents_offset,
                strings.contents_size);

        CHECK_COLLISION(property_table.entries_offset,
                property_table.num_entries * sizeof(port_data_storage_file_property_table_entry_t),
                properties.contents_offset,
                properties.contents_size);

        CHECK_COLLISION(property_table.entries_offset,
                property_table.num_entries * sizeof(port_data_storage_file_property_table_entry_t),
                sections.contents_offset,
                sections.contents_size);
    }

    if (file_header->section_table.num_entries > 0)
    {
        CHECK_COLLISION(section_table.entries_offset,
                section_table.num_entries * sizeof(port_data_storage_file_section_table_entry_t),
                symbol_table.entries_offset,
                symbol_table.num_entries * sizeof(port_data_storage_file_symbol_table_entry_t));

        CHECK_COLLISION(section_table.entries_offset,
                section_table.num_entries * sizeof(port_data_storage_file_section_table_entry_t),
                strings.contents_offset,
                strings.contents_size);

        CHECK_COLLISION(section_table.entries_offset,
                section_table.num_entries * sizeof(port_data_storage_file_section_table_entry_t),
                properties.contents_offset,
                properties.contents_size);

        CHECK_COLLISION(section_table.entries_offset,
                section_table.num_entries * sizeof(port_data_storage_file_section_table_entry_t),
                sections.contents_offset,
                sections.contents_size);
    }

    if (file_header->symbol_table.num_entries > 0)
    {
        CHECK_COLLISION(symbol_table.entries_offset,
                symbol_table.num_entries * sizeof(port_data_storage_file_symbol_table_entry_t),
                strings.contents_offset,
                strings.contents_size);

        CHECK_COLLISION(symbol_table.entries_offset,
                symbol_table.num_entries * sizeof(port_data_storage_file_symbol_table_entry_t),
                properties.contents_offset,
                properties.contents_size);

        CHECK_COLLISION(symbol_table.entries_offset,
                symbol_table.num_entries * sizeof(port_data_storage_file_symbol_table_entry_t),
                sections.contents_offset,
                sections.contents_size);
    }

    if (file_header->strings.contents_size > 0)
    {
        CHECK_COLLISION(strings.contents_offset,
                strings.contents_size,
                properties.contents_offset,
                properties.contents_size);

        CHECK_COLLISION(strings.contents_offset,
                strings.contents_size,
                sections.contents_offset,
                sections.contents_size);
    }

    if (file_header->properties.contents_size > 0)
    {
        CHECK_COLLISION(properties.contents_offset,
                properties.contents_size,
                sections.contents_offset,
                sections.contents_size);
    }

#undef CHECK_COLLISION

    return true;
}

#define ERROR(code) do { \
    error = (code); \
    goto failure; } while (0)

#define FSEEK(pos) do { \
    if (((port_uint_single_t)global_offset + (pos) > (port_uint_single_t)LONG_MAX) || \
            (fseek(file, (port_uint_single_t)global_offset + (pos), SEEK_SET) != 0)) { \
        ERROR(2); } } while (0)

#define FREAD(what, len) do { \
    if (fread((what), (len), 1, file) != 1) { \
        ERROR(3); } } while (0)

#define ALLOC_CHECK(what) do { \
    if ((what) == NULL) { \
        ERROR(4); } } while (0)

port_uint8_t
port_init_data_storage_from_file(
        port_data_storage_t *storage,
        port_uint_single_t *format,

        port_uint_single_t format_mask,
        port_uint_single_t format_magic,

        FILE *file)
{
    if (file == NULL)
        return 1;

    port_uint8_t error = 0;
    port_data_storage_t st = {0};

    port_data_storage_file_string_table_entry_t *string_table = NULL;
    port_data_storage_file_property_table_entry_t *property_table = NULL;
    port_data_storage_file_section_table_entry_t *section_table = NULL;
    port_data_storage_file_symbol_table_entry_t *symbol_table = NULL;

    // Read file header
    port_data_storage_file_header_t file_header;
    FREAD(&file_header, sizeof(file_header));

    // Get global offset
    long global_offset = ftell(file);
    if (global_offset < 0)
        ERROR(2);

    // Check format magic number
    if ((file_header.format & format_mask) != format_magic)
        ERROR(1);

    // Check for header validity
    if (!port_check_data_storage_file_header_validity(&file_header))
        ERROR(1);

    // Read tables
    string_table = malloc(sizeof(*string_table) * file_header.string_table.num_entries);
    ALLOC_CHECK(string_table);
    FSEEK(file_header.string_table.entries_offset);
    FREAD(string_table, sizeof(*string_table) * file_header.string_table.num_entries);

    property_table = malloc(sizeof(*property_table) * file_header.property_table.num_entries);
    ALLOC_CHECK(property_table);
    FSEEK(file_header.property_table.entries_offset);
    FREAD(property_table, sizeof(*property_table) * file_header.property_table.num_entries);

    section_table = malloc(sizeof(*section_table) * file_header.section_table.num_entries);
    ALLOC_CHECK(section_table);
    FSEEK(file_header.section_table.entries_offset);
    FREAD(section_table, sizeof(*section_table) * file_header.section_table.num_entries);

    symbol_table = malloc(sizeof(*symbol_table) * file_header.symbol_table.num_entries);
    ALLOC_CHECK(symbol_table);
    FSEEK(file_header.symbol_table.entries_offset);
    FREAD(symbol_table, sizeof(*symbol_table) * file_header.symbol_table.num_entries);

    // Check validity of tables entries
    for (port_uint_single_t i = 0; i < file_header.string_table.num_entries; i++)
    {
        if ((string_table[i].offset > file_header.strings.contents_size) ||
                (string_table[i].length > file_header.strings.contents_size - string_table[i].offset))
            ERROR(1);
    }

    for (port_uint_single_t i = 0; i < file_header.property_table.num_entries; i++)
    {
        if (((property_table[i].name_str_idx >= file_header.string_table.num_entries) &&
                    (property_table[i].name_str_idx != (port_uint_single_t)-1)) ||
                (property_table[i].offset > file_header.properties.contents_size) ||
                (property_table[i].size > file_header.properties.contents_size - property_table[i].offset))
            ERROR(1);
    }

    for (port_uint_single_t i = 0; i < file_header.section_table.num_entries; i++)
    {
        if (((section_table[i].name_str_idx >= file_header.string_table.num_entries) &&
                    (section_table[i].name_str_idx != (port_uint_single_t)-1)) ||
                (section_table[i].offset > file_header.sections.contents_size) ||
                (section_table[i].size > file_header.sections.contents_size - section_table[i].offset))
            ERROR(1);
    }

    for (port_uint_single_t i = 0; i < file_header.symbol_table.num_entries; i++)
    {
        if (((symbol_table[i].name_str_idx >= file_header.string_table.num_entries) &&
                    (symbol_table[i].name_str_idx != (port_uint_single_t)-1)) ||
                (symbol_table[i].section_idx >= file_header.section_table.num_entries) ||
                ((symbol_table[i].value >= section_table[symbol_table[i].section_idx].size) &&
                 (symbol_table[i].value != (port_uint_single_t)-1)))
            ERROR(1);
    }

    // Set output parameters
    if (format != NULL)
        *format = file_header.format;

    if (storage != NULL)
    {
        // Create data storage representation in memory
        st.num.strings = file_header.string_table.num_entries;
        if (st.num.strings > 0)
        {
            st.content.strings = malloc(sizeof(*st.content.strings) * st.num.strings);
            ALLOC_CHECK(st.content.strings);
            for (port_uint_single_t i = 0; i < st.num.strings; i++)
                st.content.strings[i] = NULL;

            for (port_uint_single_t i = 0; i < st.num.strings; i++)
            {
                st.content.strings[i] = malloc((port_size_t)string_table[i].length + 1);
                ALLOC_CHECK(st.content.strings[i]);
            }

            for (port_uint_single_t i = 0; i < st.num.strings; i++)
            {
                if (string_table[i].length > 0)
                {
                    FSEEK(file_header.strings.contents_offset + string_table[i].offset);
                    FREAD(st.content.strings[i], string_table[i].length);
                }
                st.content.strings[i][string_table[i].length] = '\0';
            }
        }

        st.num.properties = file_header.property_table.num_entries;
        if (st.num.properties > 0)
        {
            st.content.properties = malloc(sizeof(*st.content.properties) * st.num.properties);
            ALLOC_CHECK(st.content.properties);
            for (port_uint_single_t i = 0; i < st.num.properties; i++)
                st.content.properties[i] = NULL;

            for (port_uint_single_t i = 0; i < st.num.properties; i++)
            {
                if (property_table[i].size > 0)
                {
                    st.content.properties[i] = malloc(property_table[i].size);
                    ALLOC_CHECK(st.content.properties[i]);
                }
            }

            st.size.properties = malloc(sizeof(*st.size.properties) * st.num.properties);
            ALLOC_CHECK(st.size.properties);

            st.name_str_idx.properties = malloc(sizeof(*st.name_str_idx.properties) * st.num.properties);
            ALLOC_CHECK(st.name_str_idx.properties);

            for (port_uint_single_t i = 0; i < st.num.properties; i++)
            {
                if (property_table[i].size > 0)
                {
                    FSEEK(file_header.properties.contents_offset + property_table[i].offset);
                    FREAD(st.content.properties[i], property_table[i].size);
                }
                st.size.properties[i] = property_table[i].size;
                st.name_str_idx.properties[i] = property_table[i].name_str_idx;
            }
        }

        st.num.sections = file_header.section_table.num_entries;
        if (st.num.sections > 0)
        {
            st.content.sections = malloc(sizeof(*st.content.sections) * st.num.sections);
            ALLOC_CHECK(st.content.sections);
            for (port_uint_single_t i = 0; i < st.num.sections; i++)
                st.content.sections[i] = NULL;

            for (port_uint_single_t i = 0; i < st.num.sections; i++)
            {
                if (section_table[i].size > 0)
                {
                    st.content.sections[i] = malloc(section_table[i].size);
                    ALLOC_CHECK(st.content.sections[i]);
                }
            }

            st.size.sections = malloc(sizeof(*st.size.sections) * st.num.sections);
            ALLOC_CHECK(st.size.sections);

            st.name_str_idx.sections = malloc(sizeof(*st.name_str_idx.sections) * st.num.sections);
            ALLOC_CHECK(st.name_str_idx.sections);

            for (port_uint_single_t i = 0; i < st.num.sections; i++)
            {
                if (section_table[i].size > 0)
                {
                    FSEEK(file_header.sections.contents_offset + section_table[i].offset);
                    FREAD(st.content.sections[i], section_table[i].size);
                }
                st.size.sections[i] = section_table[i].size;
                st.name_str_idx.sections[i] = section_table[i].name_str_idx;
            }
        }

        st.num.symbols = file_header.symbol_table.num_entries;
        if (st.num.symbols > 0)
        {
            st.symbol.section_idx = malloc(sizeof(*st.symbol.section_idx) * st.num.symbols);
            ALLOC_CHECK(st.symbol.section_idx);

            st.symbol.values = malloc(sizeof(*st.symbol.values) * st.num.symbols);
            ALLOC_CHECK(st.symbol.values);

            st.name_str_idx.symbols = malloc(sizeof(*st.name_str_idx.symbols) * st.num.symbols);
            ALLOC_CHECK(st.name_str_idx.symbols);

            for (port_uint_single_t i = 0; i < st.num.symbols; i++)
            {
                st.symbol.section_idx[i] = symbol_table[i].section_idx;
                st.symbol.values[i] = symbol_table[i].value;
                st.name_str_idx.symbols[i] = symbol_table[i].name_str_idx;

                // Set invalid symbol to "the first after the last" byte
                if (st.symbol.values[i] == (port_uint_single_t)-1)
                    st.symbol.values[i] = section_table[st.symbol.section_idx[i]].size;
            }
        }

        *storage = st;
    }

    free(string_table);
    free(property_table);
    free(section_table);
    free(symbol_table);

    fseek(file, global_offset + file_header.full_size, SEEK_SET);
    return 0;

failure:
    port_reset_data_storage(&st);

    free(string_table);
    free(property_table);
    free(section_table);
    free(symbol_table);

    return error;
}

#undef ALLOC_CHECK
#undef FSEEK
#undef FREAD

#define FWRITE(what, len) do { \
    if ((what) != NULL) { \
        if (fwrite((what), (len), 1, file) != 1) \
            return 3; } } while (0)

port_uint8_t
port_write_data_storage_to_file(
        const port_data_storage_t *storage,
        port_uint_single_t format,

        port_uint_single_t *full_size,

        FILE *file)
{
    if (storage == NULL)
        return 0;

    // Calculate file size
    port_size_t string_table_size = sizeof(port_data_storage_file_string_table_entry_t) * storage->num.strings;
    port_size_t property_table_size = sizeof(port_data_storage_file_property_table_entry_t) * storage->num.properties;
    port_size_t section_table_size = sizeof(port_data_storage_file_section_table_entry_t) * storage->num.sections;
    port_size_t symbol_table_size = sizeof(port_data_storage_file_symbol_table_entry_t) * storage->num.symbols;

    port_size_t all_tables_size = string_table_size + property_table_size +
        section_table_size + symbol_table_size;

    port_size_t strings_contents_size = 0, properties_contents_size = 0, sections_contents_size = 0;

    for (port_uint_single_t i = 0; i < storage->num.strings; i++)
        strings_contents_size += strlen(storage->content.strings[i]);

    for (port_uint_single_t i = 0; i < storage->num.properties; i++)
        properties_contents_size += storage->size.properties[i];

    for (port_uint_single_t i = 0; i < storage->num.sections; i++)
        sections_contents_size += storage->size.sections[i];

    port_size_t all_contents_size = strings_contents_size + properties_contents_size + sections_contents_size;

    if (all_tables_size + all_contents_size > (port_uint_single_t)-1)
        return 1;

    if (full_size != NULL)
        *full_size = all_tables_size + all_contents_size;

    // Check indices
    for (port_uint_single_t i = 0; i < storage->num.properties; i++)
    {
        if ((storage->name_str_idx.properties[i] >= storage->num.strings) &&
                (storage->name_str_idx.properties[i] != (port_uint_single_t)-1))
            return 2;
    }

    for (port_uint_single_t i = 0; i < storage->num.sections; i++)
    {
        if ((storage->name_str_idx.sections[i] >= storage->num.strings) &&
                (storage->name_str_idx.sections[i] != (port_uint_single_t)-1))
            return 2;
    }

    for (port_uint_single_t i = 0; i < storage->num.symbols; i++)
    {
        if (((storage->name_str_idx.symbols[i] >= storage->num.strings) &&
                    (storage->name_str_idx.symbols[i] != (port_uint_single_t)-1)) ||
                (storage->symbol.section_idx[i] >= storage->num.sections) ||
                (storage->symbol.values[i] > storage->size.sections[storage->symbol.section_idx[i]]))
            return 2;
    }

    // Write file header
    if (file == NULL)
        return 0;

    port_data_storage_file_header_t file_header = {
        .format = format, .full_size = all_tables_size + all_contents_size,
        .string_table = {.num_entries = storage->num.strings, .entries_offset = 0},
        .property_table = {.num_entries = storage->num.properties, .entries_offset =
            string_table_size},
        .section_table = {.num_entries = storage->num.sections, .entries_offset =
            string_table_size + property_table_size},
        .symbol_table = {.num_entries = storage->num.symbols, .entries_offset =
            string_table_size + property_table_size + section_table_size},
        .strings = {.contents_size = strings_contents_size, .contents_offset = all_tables_size},
        .properties = {.contents_size = properties_contents_size, .contents_offset =
            all_tables_size + strings_contents_size},
        .sections = {.contents_size = sections_contents_size, .contents_offset =
            all_tables_size + strings_contents_size + properties_contents_size},
    };

    FWRITE(&file_header, sizeof(file_header));

    // Write tables
    port_uint_single_t offset = 0;

    for (port_uint_single_t i = 0; i < storage->num.strings; i++)
    {
        port_size_t length = strlen(storage->content.strings[i]);
        port_data_storage_file_string_table_entry_t string_table_entry = {
            .length = length, .offset = offset};
        offset += length;

        FWRITE(&string_table_entry, sizeof(string_table_entry));
    }

    offset = 0;

    for (port_uint_single_t i = 0; i < storage->num.properties; i++)
    {
        port_data_storage_file_property_table_entry_t property_table_entry = {
            .name_str_idx = storage->name_str_idx.properties[i],
            .size = storage->size.properties[i], .offset = offset};
        offset += storage->size.properties[i];

        FWRITE(&property_table_entry, sizeof(property_table_entry));
    }

    offset = 0;

    for (port_uint_single_t i = 0; i < storage->num.sections; i++)
    {
        port_data_storage_file_section_table_entry_t section_table_entry = {
            .name_str_idx = storage->name_str_idx.sections[i],
            .size = storage->size.sections[i], .offset = offset};
        offset += storage->size.sections[i];

        FWRITE(&section_table_entry, sizeof(section_table_entry));
    }

    for (port_uint_single_t i = 0; i < storage->num.symbols; i++)
    {
        port_data_storage_file_symbol_table_entry_t symbol_table_entry = {
            .name_str_idx = storage->name_str_idx.symbols[i],
            .section_idx = storage->symbol.section_idx[i],
            .value = storage->symbol.values[i]};

        // Set "the first after the last" byte symbol to invalid value
        if (symbol_table_entry.value == storage->size.sections[storage->symbol.section_idx[i]])
            symbol_table_entry.value = (port_uint_single_t)-1;

        FWRITE(&symbol_table_entry, sizeof(symbol_table_entry));
    }

    // Write contents
    for (port_uint_single_t i = 0; i < storage->num.strings; i++)
        FWRITE(storage->content.strings[i], strlen(storage->content.strings[i]));

    for (port_uint_single_t i = 0; i < storage->num.properties; i++)
        FWRITE(storage->content.properties[i], storage->size.properties[i]);

    for (port_uint_single_t i = 0; i < storage->num.sections; i++)
        FWRITE(storage->content.sections[i], storage->size.sections[i]);

    return 0;
}

#undef FWRITE

void
port_reset_data_storage(
        port_data_storage_t *storage)
{
    if (storage == NULL)
        return;

    if (storage->content.sections != NULL)
    {
        for (port_uint_single_t i = 0; i < storage->num.sections; i++)
            free(storage->content.sections[i]);
        free(storage->content.sections);
    }
    if (storage->content.properties != NULL)
    {
        for (port_uint_single_t i = 0; i < storage->num.properties; i++)
            free(storage->content.properties[i]);
        free(storage->content.properties);
    }
    if (storage->content.strings != NULL)
    {
        for (port_uint_single_t i = 0; i < storage->num.strings; i++)
            free(storage->content.strings[i]);
        free(storage->content.strings);
    }

    free(storage->size.sections);
    free(storage->size.properties);

    free(storage->symbol.section_idx);
    free(storage->symbol.values);

    free(storage->name_str_idx.sections);
    free(storage->name_str_idx.symbols);
    free(storage->name_str_idx.properties);

    *storage = (port_data_storage_t){0};
}

