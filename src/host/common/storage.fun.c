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

#include <port/host/storage.fun.h>
#include <port/host/storage.typ.h>

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

    // Check contents are not empty for non-empty tables
    if ((file_header->string_table.num_entries > 0) && (file_header->strings.contents_size == 0))
        return false;

    if ((file_header->section_table.num_entries > 0) && (file_header->sections.contents_size == 0))
        return false;

    if ((file_header->property_table.num_entries > 0) && (file_header->properties.contents_size == 0))
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
                section_table.entries_offset,
                section_table.num_entries * sizeof(port_data_storage_file_section_table_entry_t));

        CHECK_COLLISION(string_table.entries_offset,
                string_table.num_entries * sizeof(port_data_storage_file_string_table_entry_t),
                symbol_table.entries_offset,
                symbol_table.num_entries * sizeof(port_data_storage_file_symbol_table_entry_t));

        CHECK_COLLISION(string_table.entries_offset,
                string_table.num_entries * sizeof(port_data_storage_file_string_table_entry_t),
                property_table.entries_offset,
                property_table.num_entries * sizeof(port_data_storage_file_property_table_entry_t));

        CHECK_COLLISION(string_table.entries_offset,
                string_table.num_entries * sizeof(port_data_storage_file_string_table_entry_t),
                strings.contents_offset,
                strings.contents_size);

        CHECK_COLLISION(string_table.entries_offset,
                string_table.num_entries * sizeof(port_data_storage_file_string_table_entry_t),
                sections.contents_offset,
                sections.contents_size);

        CHECK_COLLISION(string_table.entries_offset,
                string_table.num_entries * sizeof(port_data_storage_file_string_table_entry_t),
                properties.contents_offset,
                properties.contents_size);
    }

    if (file_header->section_table.num_entries > 0)
    {
        CHECK_COLLISION(section_table.entries_offset,
                section_table.num_entries * sizeof(port_data_storage_file_section_table_entry_t),
                symbol_table.entries_offset,
                symbol_table.num_entries * sizeof(port_data_storage_file_symbol_table_entry_t));

        CHECK_COLLISION(section_table.entries_offset,
                section_table.num_entries * sizeof(port_data_storage_file_section_table_entry_t),
                property_table.entries_offset,
                property_table.num_entries * sizeof(port_data_storage_file_property_table_entry_t));

        CHECK_COLLISION(section_table.entries_offset,
                section_table.num_entries * sizeof(port_data_storage_file_section_table_entry_t),
                strings.contents_offset,
                strings.contents_size);

        CHECK_COLLISION(section_table.entries_offset,
                section_table.num_entries * sizeof(port_data_storage_file_section_table_entry_t),
                sections.contents_offset,
                sections.contents_size);

        CHECK_COLLISION(section_table.entries_offset,
                section_table.num_entries * sizeof(port_data_storage_file_section_table_entry_t),
                properties.contents_offset,
                properties.contents_size);
    }

    if (file_header->symbol_table.num_entries > 0)
    {
        CHECK_COLLISION(symbol_table.entries_offset,
                symbol_table.num_entries * sizeof(port_data_storage_file_symbol_table_entry_t),
                property_table.entries_offset,
                property_table.num_entries * sizeof(port_data_storage_file_property_table_entry_t));

        CHECK_COLLISION(symbol_table.entries_offset,
                symbol_table.num_entries * sizeof(port_data_storage_file_symbol_table_entry_t),
                strings.contents_offset,
                strings.contents_size);

        CHECK_COLLISION(symbol_table.entries_offset,
                symbol_table.num_entries * sizeof(port_data_storage_file_symbol_table_entry_t),
                sections.contents_offset,
                sections.contents_size);

        CHECK_COLLISION(symbol_table.entries_offset,
                symbol_table.num_entries * sizeof(port_data_storage_file_symbol_table_entry_t),
                properties.contents_offset,
                properties.contents_size);
    }

    if (file_header->property_table.num_entries > 0)
    {
        CHECK_COLLISION(property_table.entries_offset,
                property_table.num_entries * sizeof(port_data_storage_file_property_table_entry_t),
                strings.contents_offset,
                strings.contents_size);

        CHECK_COLLISION(property_table.entries_offset,
                property_table.num_entries * sizeof(port_data_storage_file_property_table_entry_t),
                sections.contents_offset,
                sections.contents_size);

        CHECK_COLLISION(property_table.entries_offset,
                property_table.num_entries * sizeof(port_data_storage_file_property_table_entry_t),
                properties.contents_offset,
                properties.contents_size);
    }

    if (file_header->strings.contents_size > 0)
    {
        CHECK_COLLISION(strings.contents_offset,
                strings.contents_size,
                sections.contents_offset,
                sections.contents_size);

        CHECK_COLLISION(strings.contents_offset,
                strings.contents_size,
                properties.contents_offset,
                properties.contents_size);
    }

    if (file_header->sections.contents_size > 0)
    {
        CHECK_COLLISION(sections.contents_offset,
                sections.contents_size,
                properties.contents_offset,
                properties.contents_size);
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
    port_data_storage_file_section_table_entry_t *section_table = NULL;
    port_data_storage_file_symbol_table_entry_t *symbol_table = NULL;
    port_data_storage_file_property_table_entry_t *property_table = NULL;

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

    section_table = malloc(sizeof(*section_table) * file_header.section_table.num_entries);
    ALLOC_CHECK(section_table);
    FSEEK(file_header.section_table.entries_offset);
    FREAD(section_table, sizeof(*section_table) * file_header.section_table.num_entries);

    symbol_table = malloc(sizeof(*symbol_table) * file_header.symbol_table.num_entries);
    ALLOC_CHECK(symbol_table);
    FSEEK(file_header.symbol_table.entries_offset);
    FREAD(symbol_table, sizeof(*symbol_table) * file_header.symbol_table.num_entries);

    property_table = malloc(sizeof(*property_table) * file_header.property_table.num_entries);
    ALLOC_CHECK(property_table);
    FSEEK(file_header.property_table.entries_offset);
    FREAD(property_table, sizeof(*property_table) * file_header.property_table.num_entries);

    // Check validity of tables entries
    for (port_uint_single_t i = 0; i < file_header.string_table.num_entries; i++)
    {
        if ((string_table[i].offset > file_header.strings.contents_size) ||
                (string_table[i].length > file_header.strings.contents_size - string_table[i].offset))
            ERROR(1);
    }

    for (port_uint_single_t i = 0; i < file_header.section_table.num_entries; i++)
    {
        if ((section_table[i].name_str_idx >= file_header.string_table.num_entries) ||
                (section_table[i].offset > file_header.sections.contents_size) ||
                (section_table[i].size > file_header.sections.contents_size - section_table[i].offset))
            ERROR(1);
    }

    for (port_uint_single_t i = 0; i < file_header.symbol_table.num_entries; i++)
    {
        if ((symbol_table[i].name_str_idx >= file_header.string_table.num_entries) ||
                (symbol_table[i].section_idx >= file_header.section_table.num_entries))
            ERROR(1);
    }

    for (port_uint_single_t i = 0; i < file_header.property_table.num_entries; i++)
    {
        if ((property_table[i].name_str_idx >= file_header.string_table.num_entries) ||
                (property_table[i].offset > file_header.properties.contents_size) ||
                (property_table[i].size > file_header.properties.contents_size - property_table[i].offset))
            ERROR(1);
    }

    // Set output parameters
    if (format != NULL)
        *format = file_header.format;

    if (storage != NULL)
    {
        // Create data storage representation in memory
        st.num_strings = file_header.string_table.num_entries;
        if (st.num_strings > 0)
        {

            st.strings = malloc(sizeof(*st.strings) * st.num_strings);
            ALLOC_CHECK(st.strings);
            for (port_uint_single_t i = 0; i < st.num_strings; i++)
                st.strings[i] = NULL;

            for (port_uint_single_t i = 0; i < st.num_strings; i++)
            {
                st.strings[i] = malloc((port_size_t)string_table[i].length + 1);
                ALLOC_CHECK(st.strings[i]);

                if (string_table[i].length > 0)
                {
                    FSEEK(file_header.strings.contents_offset + string_table[i].offset);
                    FREAD(st.strings[i], string_table[i].length);
                }
                st.strings[i][string_table[i].length] = '\0';
            }
        }

        st.num_sections = file_header.section_table.num_entries;
        if (st.num_sections > 0)
        {
            st.section_name_str_idx = malloc(sizeof(*st.section_name_str_idx) * st.num_sections);
            ALLOC_CHECK(st.section_name_str_idx);

            st.sections = malloc(sizeof(*st.sections) * st.num_sections);
            ALLOC_CHECK(st.sections);
            for (port_uint_single_t i = 0; i < st.num_sections; i++)
                st.sections[i] = NULL;

            st.section_sizes = malloc(sizeof(*st.section_sizes) * st.num_sections);
            ALLOC_CHECK(st.section_sizes);

            for (port_uint_single_t i = 0; i < st.num_sections; i++)
            {
                st.section_name_str_idx[i] = section_table[i].name_str_idx;

                if (section_table[i].size > 0)
                {
                    st.sections[i] = malloc(section_table[i].size);
                    ALLOC_CHECK(st.sections[i]);

                    FSEEK(file_header.sections.contents_offset + section_table[i].offset);
                    FREAD(st.sections[i], section_table[i].size);
                }

                st.section_sizes[i] = section_table[i].size;
            }
        }

        st.num_symbols = file_header.symbol_table.num_entries;
        if (st.num_symbols > 0)
        {
            st.symbol_name_str_idx = malloc(sizeof(*st.symbol_name_str_idx) * st.num_symbols);
            ALLOC_CHECK(st.symbol_name_str_idx);

            st.symbol_section_idx = malloc(sizeof(*st.symbol_section_idx) * st.num_symbols);
            ALLOC_CHECK(st.symbol_section_idx);

            st.symbol_values = malloc(sizeof(*st.symbol_values) * st.num_symbols);
            ALLOC_CHECK(st.symbol_values);

            for (port_uint_single_t i = 0; i < st.num_symbols; i++)
            {
                st.symbol_name_str_idx[i] = symbol_table[i].name_str_idx;
                st.symbol_section_idx[i] = symbol_table[i].section_idx;
                st.symbol_values[i] = symbol_table[i].value;

                // Set all invalid symbol to "the first after the last"
                if (st.symbol_values[i] > section_table[symbol_table[i].section_idx].size)
                    st.symbol_values[i] = section_table[symbol_table[i].section_idx].size;
            }
        }

        st.num_properties = file_header.property_table.num_entries;
        if (st.num_properties > 0)
        {
            st.property_name_str_idx = malloc(sizeof(*st.property_name_str_idx) * st.num_properties);
            ALLOC_CHECK(st.property_name_str_idx);

            st.property_values = malloc(sizeof(*st.property_values) * st.num_properties);
            ALLOC_CHECK(st.property_values);
            for (port_uint_single_t i = 0; i < st.num_properties; i++)
                st.property_values[i] = NULL;

            st.property_value_sizes = malloc(sizeof(*st.property_value_sizes) * st.num_properties);
            ALLOC_CHECK(st.property_value_sizes);

            for (port_uint_single_t i = 0; i < st.num_properties; i++)
            {
                st.property_name_str_idx[i] = property_table[i].name_str_idx;

                if (property_table[i].size > 0)
                {
                    st.property_values[i] = malloc(property_table[i].size);
                    ALLOC_CHECK(st.property_values[i]);

                    FSEEK(file_header.properties.contents_offset + property_table[i].offset);
                    FREAD(st.property_values[i], property_table[i].size);
                }

                st.property_value_sizes[i] = property_table[i].size;
            }
        }

        *storage = st;
    }

    free(string_table);
    free(section_table);
    free(symbol_table);
    free(property_table);

    fseek(file, global_offset + file_header.full_size, SEEK_SET);
    return 0;

failure:
    port_reset_data_storage(&st);

    free(string_table);
    free(section_table);
    free(symbol_table);
    free(property_table);

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
    port_size_t string_table_size = sizeof(port_data_storage_file_string_table_entry_t) * storage->num_strings;
    port_size_t section_table_size = sizeof(port_data_storage_file_section_table_entry_t) * storage->num_sections;
    port_size_t symbol_table_size = sizeof(port_data_storage_file_symbol_table_entry_t) * storage->num_symbols;
    port_size_t property_table_size = sizeof(port_data_storage_file_property_table_entry_t) * storage->num_properties;

    port_size_t all_tables_size = string_table_size + section_table_size +
        symbol_table_size + property_table_size;

    port_size_t strings_contents_size = 0, sections_contents_size = 0, properties_contents_size = 0;

    for (port_uint_single_t i = 0; i < storage->num_strings; i++)
        strings_contents_size += strlen(storage->strings[i]);

    for (port_uint_single_t i = 0; i < storage->num_sections; i++)
        sections_contents_size += storage->section_sizes[i];

    for (port_uint_single_t i = 0; i < storage->num_properties; i++)
        properties_contents_size += storage->property_value_sizes[i];

    port_size_t all_contents_size = strings_contents_size + sections_contents_size + properties_contents_size;

    if (all_tables_size + all_contents_size > (port_uint_single_t)-1)
        return 1;

    if (full_size != NULL)
        *full_size = all_tables_size + all_contents_size;

    // Check indices
    for (port_uint_single_t i = 0; i < storage->num_sections; i++)
    {
        if (storage->section_name_str_idx[i] >= storage->num_strings)
            return 2;
    }

    for (port_uint_single_t i = 0; i < storage->num_symbols; i++)
    {
        if ((storage->symbol_name_str_idx[i] >= storage->num_strings) ||
                (storage->symbol_section_idx[i] >= storage->num_sections))
            return 2;
    }

    for (port_uint_single_t i = 0; i < storage->num_properties; i++)
    {
        if (storage->property_name_str_idx[i] >= storage->num_strings)
            return 2;
    }

    // Write file header
    if (file == NULL)
        return 0;

    port_data_storage_file_header_t file_header = {
        .format = format, .full_size = all_tables_size + all_contents_size,
        .string_table = {.num_entries = storage->num_strings, .entries_offset = 0},
        .section_table = {.num_entries = storage->num_sections, .entries_offset = string_table_size},
        .symbol_table = {.num_entries = storage->num_symbols, .entries_offset =
            string_table_size + section_table_size},
        .property_table = {.num_entries = storage->num_properties, .entries_offset =
            string_table_size + section_table_size + symbol_table_size},
        .strings = {.contents_size = strings_contents_size, .contents_offset = all_tables_size},
        .sections = {.contents_size = sections_contents_size, .contents_offset =
            all_tables_size + strings_contents_size},
        .properties = {.contents_size = properties_contents_size, .contents_offset =
            all_tables_size + strings_contents_size + sections_contents_size},
    };

    FWRITE(&file_header, sizeof(file_header));

    // Write tables
    port_uint_single_t offset = 0;

    for (port_uint_single_t i = 0; i < storage->num_strings; i++)
    {
        port_size_t length = strlen(storage->strings[i]);
        port_data_storage_file_string_table_entry_t string_table_entry = {
            .length = length, .offset = offset};
        offset += length;

        FWRITE(&string_table_entry, sizeof(string_table_entry));
    }

    offset = 0;

    for (port_uint_single_t i = 0; i < storage->num_sections; i++)
    {
        port_data_storage_file_section_table_entry_t section_table_entry = {
            .name_str_idx = storage->section_name_str_idx[i],
            .size = storage->section_sizes[i], .offset = offset};
        offset += storage->section_sizes[i];

        FWRITE(&section_table_entry, sizeof(section_table_entry));
    }

    for (port_uint_single_t i = 0; i < storage->num_symbols; i++)
    {
        port_data_storage_file_symbol_table_entry_t symbol_table_entry = {
            .name_str_idx = storage->symbol_name_str_idx[i],
            .section_idx = storage->symbol_section_idx[i],
            .value = storage->symbol_values[i]};

        FWRITE(&symbol_table_entry, sizeof(symbol_table_entry));
    }

    offset = 0;

    for (port_uint_single_t i = 0; i < storage->num_properties; i++)
    {
        port_data_storage_file_property_table_entry_t property_table_entry = {
            .name_str_idx = storage->property_name_str_idx[i],
            .size = storage->property_value_sizes[i], .offset = offset};
        offset += storage->property_value_sizes[i];

        FWRITE(&property_table_entry, sizeof(property_table_entry));
    }

    // Write contents
    for (port_uint_single_t i = 0; i < storage->num_strings; i++)
        FWRITE(storage->strings[i], strlen(storage->strings[i]));

    for (port_uint_single_t i = 0; i < storage->num_sections; i++)
        FWRITE(storage->sections[i], storage->section_sizes[i]);

    for (port_uint_single_t i = 0; i < storage->num_properties; i++)
        FWRITE(storage->property_values[i], storage->property_value_sizes[i]);

    return 0;
}

#undef FWRITE

void
port_reset_data_storage(
        port_data_storage_t *storage)
{
    if (storage == NULL)
        return;

    if (storage->strings != NULL)
    {
        for (port_uint_single_t i = 0; i < storage->num_strings; i++)
            free(storage->strings[i]);

        free(storage->strings);
    }

    free(storage->section_name_str_idx);
    if (storage->sections != NULL)
    {
        for (port_uint_single_t i = 0; i < storage->num_sections; i++)
            free(storage->sections[i]);

        free(storage->sections);
    }
    free(storage->section_sizes);

    free(storage->symbol_name_str_idx);
    free(storage->symbol_section_idx);
    free(storage->symbol_values);

    free(storage->property_name_str_idx);
    if (storage->property_values != NULL)
    {
        for (port_uint_single_t i = 0; i < storage->num_properties; i++)
            free(storage->property_values[i]);

        free(storage->property_values);
    }
    free(storage->property_value_sizes);

    *storage = (port_data_storage_t){0};
}

