#define _POSIX_C_SOURCE 200809L // for fmemopen() and open_memstream()

#include <test.h>

#include <port/host/storage.fun.h>
#include <port/host/storage.typ.h>

#include <stdio.h>
#include <string.h>

TEST(port_check_data_storage_file_header_validity)
{
    port_data_storage_file_header_t file_header = {0}, copy;
    ASSERT_TRUE(port_check_data_storage_file_header_validity(&file_header));

    file_header.full_size = 1000;
    ASSERT_TRUE(port_check_data_storage_file_header_validity(&file_header));

    file_header.string_table.num_entries = 3;
    file_header.string_table.entries_offset = 0;

    file_header.section_table.num_entries = 2;
    file_header.section_table.entries_offset = 24;

    file_header.symbol_table.num_entries = 10;
    file_header.symbol_table.entries_offset = 48;

    file_header.property_table.num_entries = 5;
    file_header.property_table.entries_offset = 168;

    file_header.strings.contents_size = 10;
    file_header.strings.contents_offset = 228;

    file_header.sections.contents_size = 500;
    file_header.sections.contents_offset = 238;

    file_header.properties.contents_size = 262;
    file_header.properties.contents_offset = 738;

    ASSERT_TRUE(port_check_data_storage_file_header_validity(&file_header));

    copy = file_header;
    copy.string_table.entries_offset = 990;
    ASSERT_FALSE(port_check_data_storage_file_header_validity(&copy));

    copy = file_header;
    copy.string_table.entries_offset = 1010;
    ASSERT_FALSE(port_check_data_storage_file_header_validity(&copy));

    copy = file_header;
    copy.section_table.entries_offset = 990;
    ASSERT_FALSE(port_check_data_storage_file_header_validity(&copy));

    copy = file_header;
    copy.section_table.entries_offset = 1010;
    ASSERT_FALSE(port_check_data_storage_file_header_validity(&copy));

    copy = file_header;
    copy.symbol_table.entries_offset = 990;
    ASSERT_FALSE(port_check_data_storage_file_header_validity(&copy));

    copy = file_header;
    copy.symbol_table.entries_offset = 1010;
    ASSERT_FALSE(port_check_data_storage_file_header_validity(&copy));

    copy = file_header;
    copy.property_table.entries_offset = 990;
    ASSERT_FALSE(port_check_data_storage_file_header_validity(&copy));

    copy = file_header;
    copy.property_table.entries_offset = 1010;
    ASSERT_FALSE(port_check_data_storage_file_header_validity(&copy));

    copy = file_header;
    copy.strings.contents_size = 1000;
    ASSERT_FALSE(port_check_data_storage_file_header_validity(&copy));

    copy = file_header;
    copy.strings.contents_offset = 1001;
    ASSERT_FALSE(port_check_data_storage_file_header_validity(&copy));

    copy = file_header;
    copy.sections.contents_size = 1000;
    ASSERT_FALSE(port_check_data_storage_file_header_validity(&copy));

    copy = file_header;
    copy.sections.contents_offset = 1001;
    ASSERT_FALSE(port_check_data_storage_file_header_validity(&copy));

    copy = file_header;
    copy.properties.contents_size++;
    ASSERT_FALSE(port_check_data_storage_file_header_validity(&copy));

    copy = file_header;
    copy.properties.contents_offset = 1001;
    ASSERT_FALSE(port_check_data_storage_file_header_validity(&copy));

    //////

    copy = file_header;
    copy.strings.contents_size = 0;
    ASSERT_FALSE(port_check_data_storage_file_header_validity(&copy));

    copy = file_header;
    copy.sections.contents_size = 0;
    ASSERT_FALSE(port_check_data_storage_file_header_validity(&copy));

    copy = file_header;
    copy.properties.contents_size = 0;
    ASSERT_FALSE(port_check_data_storage_file_header_validity(&copy));

    //////

    copy = file_header;
    copy.string_table.entries_offset++;
    ASSERT_FALSE(port_check_data_storage_file_header_validity(&copy));

    copy = file_header;
    copy.section_table.entries_offset++;
    ASSERT_FALSE(port_check_data_storage_file_header_validity(&copy));

    copy = file_header;
    copy.symbol_table.entries_offset++;
    ASSERT_FALSE(port_check_data_storage_file_header_validity(&copy));

    copy = file_header;
    copy.property_table.entries_offset++;
    ASSERT_FALSE(port_check_data_storage_file_header_validity(&copy));

    copy = file_header;
    copy.strings.contents_size++;
    ASSERT_FALSE(port_check_data_storage_file_header_validity(&copy));

    copy = file_header;
    copy.strings.contents_offset++;
    ASSERT_FALSE(port_check_data_storage_file_header_validity(&copy));

    copy = file_header;
    copy.sections.contents_size++;
    ASSERT_FALSE(port_check_data_storage_file_header_validity(&copy));

    copy = file_header;
    copy.sections.contents_offset++;
    ASSERT_FALSE(port_check_data_storage_file_header_validity(&copy));

    copy = file_header;
    copy.properties.contents_size++;
    ASSERT_FALSE(port_check_data_storage_file_header_validity(&copy));

    copy = file_header;
    copy.properties.contents_offset++;
    ASSERT_FALSE(port_check_data_storage_file_header_validity(&copy));
}

TEST(port_init_data_storage_from_file)
{
    port_uint_single_t buffer[] = {
        0x1BADC0DE, // file_header.format
        200, // file_header.full_size

        3, // file_header.string_table.num_entries
        4, // file_header.string_table.entries_offset

        2, // file_header.section_table.num_entries
        44, // file_header.section_table.entries_offset

        3, // file_header.symbol_table.num_entries
        100, // file_header.symbol_table.entries_offset

        3, // file_header.property_table.num_entries
        144, // file_header.property_table.entries_offset

        11, // file_header.strings.contents_size,
        32, // file_header.strings.contents_offset

        32, // file_header.sections.contents_size,
        68, // file_header.sections.contents_offset

        8, // file_header.properties.contents_size,
        180, // file_header.properties.contents_offset

        0xDEAD, // skipped

        // string table entry #1
        3, // length
        0, // offset
        // string table entry #2
        6, // length
        3, // offset
        // string table entry #3
        1, // length
        9, // offset

        0xDEAD, // skipped

        // strings FIXME
        (union {port_uint_single_t as_uint; char str[4];}){.str = "1sts"}.as_uint,
        (union {port_uint_single_t as_uint; char str[4];}){.str = "econ"}.as_uint,
        (union {port_uint_single_t as_uint; char str[4];}){.str = "d3+ "}.as_uint,
        /* '1' | ('s' >> 8) | ('t' >> 16) | ('s' >> 24), */
        /* 'e' | ('c' >> 8) | ('o' >> 16) | ('n' >> 24), */
        /* 'd' | ('3' >> 8), */

        // section table entry #1
        0, // name_str_idx
        24, // size
        0, // offset
        // section table entry #2
        1, // name_str_idx
        16, // size
        16, // offset

        // sections
        0xAAAAAAAA, 0xBBBBBBBB, 0xCCCCCCCC, 0xDDDDDDDD, 0xEEEEEEEE, 0xFFFFFFFF,
        0x88888888, 0x77777777,

        // symbol table entry #1
        2, // name_str_idx
        0, // section_idx
        4, // value
        // symbol table entry #2
        1, // name_str_idx
        0, // section_idx
        24, // value
        // symbol table entry #3
        0, // name_str_idx
        1, // section_idx
        0, // value

        0xDEAD, // skipped
        0xDEAD, // skipped

        // property table entry #1
        1, // name_str_idx
        0, // size
        0, // offset
        // property table entry #2
        1, // name_str_idx
        4, // size
        0, // offset
        // property table entry #3
        2, // name_str_idx
        4, // size
        4, // offset

        // properties
        0x12345678, 0x87654321,
    };

    FILE *file = fmemopen(buffer, sizeof(buffer), "r");
    ASSERT_TRUE(file != NULL);

    port_data_storage_t storage = {0};
    port_uint_single_t format;
    ASSERT_EQ(port_init_data_storage_from_file(&storage, &format, 0, 0, file), 0,
            port_uint8_t, "%u");

    fclose(file);

    ASSERT_EQ(format, 0x1BADC0DE, port_uint_single_t, "%u");

    ASSERT_EQ(storage.num_strings, 3, port_uint_single_t, "%u");
    ASSERT_TRUE(storage.strings != NULL);
    ASSERT_TRUE(strcmp(storage.strings[0], "1st") == 0);
    ASSERT_TRUE(strcmp(storage.strings[1], "second") == 0);
    ASSERT_TRUE(strcmp(storage.strings[2], "3") == 0);

    ASSERT_EQ(storage.num_sections, 2, port_uint_single_t, "%u");
    ASSERT_TRUE(storage.section_name_str_idx != NULL);
    ASSERT_EQ(storage.section_name_str_idx[0], 0, port_uint_single_t, "%u");
    ASSERT_EQ(storage.section_name_str_idx[1], 1, port_uint_single_t, "%u");
    ASSERT_TRUE(storage.sections != NULL);
    ASSERT_TRUE(storage.sections[0] != NULL);
    ASSERT_TRUE(storage.sections[1] != NULL);
    ASSERT_EQ(((port_uint_single_t*)storage.sections[0])[0], 0xAAAAAAAA, port_uint_single_t, "%u");
    ASSERT_EQ(((port_uint_single_t*)storage.sections[0])[1], 0xBBBBBBBB, port_uint_single_t, "%u");
    ASSERT_EQ(((port_uint_single_t*)storage.sections[0])[2], 0xCCCCCCCC, port_uint_single_t, "%u");
    ASSERT_EQ(((port_uint_single_t*)storage.sections[0])[3], 0xDDDDDDDD, port_uint_single_t, "%u");
    ASSERT_EQ(((port_uint_single_t*)storage.sections[0])[4], 0xEEEEEEEE, port_uint_single_t, "%u");
    ASSERT_EQ(((port_uint_single_t*)storage.sections[0])[5], 0xFFFFFFFF, port_uint_single_t, "%u");
    ASSERT_TRUE(storage.section_sizes != NULL);
    ASSERT_EQ(storage.section_sizes[0], 24, port_uint_single_t, "%u");
    ASSERT_EQ(((port_uint_single_t*)storage.sections[1])[0], 0xEEEEEEEE, port_uint_single_t, "%u");
    ASSERT_EQ(((port_uint_single_t*)storage.sections[1])[1], 0xFFFFFFFF, port_uint_single_t, "%u");
    ASSERT_EQ(((port_uint_single_t*)storage.sections[1])[2], 0x88888888, port_uint_single_t, "%u");
    ASSERT_EQ(((port_uint_single_t*)storage.sections[1])[3], 0x77777777, port_uint_single_t, "%u");
    ASSERT_EQ(storage.section_sizes[1], 16, port_uint_single_t, "%u");

    ASSERT_EQ(storage.num_symbols, 3, port_uint_single_t, "%u");
    ASSERT_TRUE(storage.symbol_name_str_idx != NULL);
    ASSERT_EQ(storage.symbol_name_str_idx[0], 2, port_uint_single_t, "%u");
    ASSERT_EQ(storage.symbol_name_str_idx[1], 1, port_uint_single_t, "%u");
    ASSERT_EQ(storage.symbol_name_str_idx[2], 0, port_uint_single_t, "%u");
    ASSERT_TRUE(storage.symbol_section_idx != NULL);
    ASSERT_EQ(storage.symbol_section_idx[0], 0, port_uint_single_t, "%u");
    ASSERT_EQ(storage.symbol_section_idx[1], 0, port_uint_single_t, "%u");
    ASSERT_EQ(storage.symbol_section_idx[2], 1, port_uint_single_t, "%u");
    ASSERT_TRUE(storage.symbol_values != NULL);
    ASSERT_EQ(storage.symbol_values[0], 4, port_uint_single_t, "%u");
    ASSERT_EQ(storage.symbol_values[1], 24, port_uint_single_t, "%u");
    ASSERT_EQ(storage.symbol_values[2], 0, port_uint_single_t, "%u");

    ASSERT_EQ(storage.num_properties, 3, port_uint_single_t, "%u");
    ASSERT_TRUE(storage.property_name_str_idx != NULL);
    ASSERT_EQ(storage.property_name_str_idx[0], 1, port_uint_single_t, "%u");
    ASSERT_EQ(storage.property_name_str_idx[1], 1, port_uint_single_t, "%u");
    ASSERT_EQ(storage.property_name_str_idx[2], 2, port_uint_single_t, "%u");
    ASSERT_TRUE(storage.property_values != NULL);
    ASSERT_TRUE(storage.property_values[0] == NULL);
    ASSERT_TRUE(storage.property_values[1] != NULL);
    ASSERT_TRUE(storage.property_values[2] != NULL);
    ASSERT_EQ(((port_uint_single_t*)storage.property_values[1])[0], 0x12345678, port_uint_single_t, "%u");
    ASSERT_EQ(((port_uint_single_t*)storage.property_values[2])[0], 0x87654321, port_uint_single_t, "%u");
    ASSERT_TRUE(storage.property_value_sizes != NULL);
    ASSERT_EQ(((port_uint_single_t*)storage.property_value_sizes)[0], 0, port_uint_single_t, "%u");
    ASSERT_EQ(((port_uint_single_t*)storage.property_value_sizes)[1], 4, port_uint_single_t, "%u");
    ASSERT_EQ(((port_uint_single_t*)storage.property_value_sizes)[2], 4, port_uint_single_t, "%u");

    port_reset_data_storage(&storage);
}

TEST(port_write_data_storage_to_file)
{
    char *strings[] = {"hello", "world", "!!!"};

    port_uint_single_t section_name_str_idx[] = {0, 1};
    port_void_ptr_t sections[] = {"12345678", "abcdefgh"};
    port_uint_single_t section_sizes[] = {8, 8};

    port_uint_single_t symbol_name_str_idx[] = {0, 1, 2, 2};
    port_uint_single_t symbol_section_idx[] = {0, 0, 1, 1};
    port_uint_single_t symbol_values[] = {0, 8, 0, 8};

    port_uint_single_t property_name_str_idx[] = {0, 1};
    port_uint_single_t values[] = {0x12345678, 0xABCDEF01};
    port_void_ptr_t property_values[] = {&values[0], &values[1]};
    port_uint_single_t property_value_sizes[] = {sizeof(values[0]), sizeof(values[1])};

    port_data_storage_t storage = {
        .num_strings = 3,
        .strings = strings,

        .num_sections = 2,
        .section_name_str_idx = section_name_str_idx,
        .sections = sections,
        .section_sizes = section_sizes,

        .num_symbols = 4,
        .symbol_name_str_idx = symbol_name_str_idx,
        .symbol_section_idx = symbol_section_idx,
        .symbol_values = symbol_values,

        .num_properties = 2,
        .property_name_str_idx = property_name_str_idx,
        .property_values = property_values,
        .property_value_sizes = property_value_sizes,
    };

    char *buffer = NULL;
    port_size_t buffer_size = 0;

    FILE *file = open_memstream(&buffer, &buffer_size);
    ASSERT_TRUE(file != NULL);

    port_uint_single_t format = 0;
    port_uint_single_t full_size = 0;
    ASSERT_EQ(port_write_data_storage_to_file(&storage, 0x1BADC0DE, &full_size, file),
            0, port_uint8_t, "%u");

    fclose(file);

    ASSERT_EQ(buffer_size, sizeof(port_data_storage_file_header_t) + full_size,
            port_uint_single_t, "%u");
    ASSERT_EQ(full_size, 8*3 + 12*(2+4+2) + (5+5+3) + (8+8) + (4+4), port_uint8_t, "%u");

    port_data_storage_t storage2 = {0};

    file = fmemopen(buffer, buffer_size, "r");
    ASSERT_TRUE(file != NULL);

    ASSERT_EQ(port_init_data_storage_from_file(&storage2, &format, 0, 0, file), 0,
            port_uint8_t, "%u");

    fclose(file);
    free(buffer);

    ASSERT_EQ(format, 0x1BADC0DE, port_uint_single_t, "%u");

    ASSERT_EQ(storage2.num_strings, storage.num_strings, port_uint_single_t, "%u");
    ASSERT_TRUE(storage2.strings != NULL);
    for (port_uint_single_t i = 0; i < storage.num_strings; i++)
        ASSERT_TRUE(strcmp(storage2.strings[i], storage.strings[i]) == 0);

    ASSERT_EQ(storage2.num_sections, storage.num_sections, port_uint_single_t, "%u");
    ASSERT_TRUE(storage2.section_name_str_idx != NULL);
    ASSERT_TRUE(storage2.sections != NULL);
    ASSERT_TRUE(storage2.section_sizes != NULL);
    for (port_uint_single_t i = 0; i < storage.num_sections; i++)
    {
        ASSERT_EQ(storage2.section_name_str_idx[i], storage.section_name_str_idx[i],
                port_uint_single_t, "%u");
        ASSERT_EQ(storage2.section_sizes[i], storage.section_sizes[i],
                port_uint_single_t, "%u");

        if (storage2.section_sizes[i] == storage.section_sizes[i])
        {
            for (port_uint_single_t j = 0; j < storage.section_sizes[i]; j++)
                ASSERT_EQ(((char*)storage2.sections[i])[j],
                        ((char*)storage.sections[i])[j], port_uint8_t, "%u");
        }
    }

    ASSERT_EQ(storage2.num_symbols, storage.num_symbols, port_uint_single_t, "%u");
    ASSERT_TRUE(storage2.symbol_name_str_idx != NULL);
    ASSERT_TRUE(storage2.symbol_section_idx != NULL);
    ASSERT_TRUE(storage2.symbol_values != NULL);
    for (port_uint_single_t i = 0; i < storage.num_symbols; i++)
    {
        ASSERT_EQ(storage2.symbol_name_str_idx[i], storage.symbol_name_str_idx[i],
                port_uint_single_t, "%u");
        ASSERT_EQ(storage2.symbol_section_idx[i], storage.symbol_section_idx[i],
                port_uint_single_t, "%u");
        ASSERT_EQ(storage2.symbol_values[i], storage.symbol_values[i],
                port_uint_single_t, "%u");
    }

    ASSERT_EQ(storage2.num_properties, storage.num_properties, port_uint_single_t, "%u");
    ASSERT_TRUE(storage2.property_name_str_idx != NULL);
    ASSERT_TRUE(storage2.property_values != NULL);
    ASSERT_TRUE(storage2.property_value_sizes != NULL);
    for (port_uint_single_t i = 0; i < storage.num_properties; i++)
    {
        ASSERT_EQ(storage2.property_name_str_idx[i], storage.property_name_str_idx[i],
                port_uint_single_t, "%u");
        ASSERT_EQ(storage2.property_value_sizes[i], storage.property_value_sizes[i],
                port_uint_single_t, "%u");

        if (storage2.property_value_sizes[i] == storage.property_value_sizes[i])
        {
            for (port_uint_single_t j = 0; j < storage.property_value_sizes[i]; j++)
                ASSERT_EQ(((char*)storage2.property_values[i])[j],
                        ((char*)storage.property_values[i])[j], port_uint8_t, "%u");
        }
    }

    port_reset_data_storage(&storage2);
}

