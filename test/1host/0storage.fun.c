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

        3, // file_header.property_table.num_entries
        144, // file_header.property_table.entries_offset

        2, // file_header.section_table.num_entries
        44, // file_header.section_table.entries_offset

        3, // file_header.symbol_table.num_entries
        100, // file_header.symbol_table.entries_offset

        11, // file_header.strings.contents_size,
        32, // file_header.strings.contents_offset

        8, // file_header.properties.contents_size,
        180, // file_header.properties.contents_offset

        32, // file_header.sections.contents_size,
        68, // file_header.sections.contents_offset

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

        // strings
        (union {port_uint_single_t as_uint; char str[4];}){.str = "1sts"}.as_uint,
        (union {port_uint_single_t as_uint; char str[4];}){.str = "econ"}.as_uint,
        (union {port_uint_single_t as_uint; char str[4];}){.str = "d3+ "}.as_uint,

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
        23, // value
        // symbol table entry #3
        0, // name_str_idx
        1, // section_idx
        0xFFFFFFFF, // value

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

    ASSERT_EQ(storage.num.strings, 3, port_uint_single_t, "%u");
    ASSERT_TRUE(storage.content.strings != NULL);
    ASSERT_TRUE(strcmp(storage.content.strings[0], "1st") == 0);
    ASSERT_TRUE(strcmp(storage.content.strings[1], "second") == 0);
    ASSERT_TRUE(strcmp(storage.content.strings[2], "3") == 0);

    ASSERT_EQ(storage.num.properties, 3, port_uint_single_t, "%u");
    ASSERT_TRUE(storage.content.properties != NULL);
    ASSERT_TRUE(storage.content.properties[0] == NULL);
    ASSERT_TRUE(storage.content.properties[1] != NULL);
    ASSERT_TRUE(storage.content.properties[2] != NULL);
    ASSERT_EQ(((port_uint_single_t*)storage.content.properties[1])[0], 0x12345678,
            port_uint_single_t, "%u");
    ASSERT_EQ(((port_uint_single_t*)storage.content.properties[2])[0], 0x87654321,
            port_uint_single_t, "%u");
    ASSERT_TRUE(storage.size.properties != NULL);
    ASSERT_EQ(((port_uint_single_t*)storage.size.properties)[0], 0, port_uint_single_t, "%u");
    ASSERT_EQ(((port_uint_single_t*)storage.size.properties)[1], 4, port_uint_single_t, "%u");
    ASSERT_EQ(((port_uint_single_t*)storage.size.properties)[2], 4, port_uint_single_t, "%u");
    ASSERT_TRUE(storage.name_str_idx.properties != NULL);
    ASSERT_EQ(storage.name_str_idx.properties[0], 1, port_uint_single_t, "%u");
    ASSERT_EQ(storage.name_str_idx.properties[1], 1, port_uint_single_t, "%u");
    ASSERT_EQ(storage.name_str_idx.properties[2], 2, port_uint_single_t, "%u");

    ASSERT_EQ(storage.num.sections, 2, port_uint_single_t, "%u");
    ASSERT_TRUE(storage.content.sections != NULL);
    ASSERT_TRUE(storage.content.sections[0] != NULL);
    ASSERT_TRUE(storage.content.sections[1] != NULL);
    ASSERT_EQ(((port_uint_single_t*)storage.content.sections[0])[0], 0xAAAAAAAA, port_uint_single_t, "%u");
    ASSERT_EQ(((port_uint_single_t*)storage.content.sections[0])[1], 0xBBBBBBBB, port_uint_single_t, "%u");
    ASSERT_EQ(((port_uint_single_t*)storage.content.sections[0])[2], 0xCCCCCCCC, port_uint_single_t, "%u");
    ASSERT_EQ(((port_uint_single_t*)storage.content.sections[0])[3], 0xDDDDDDDD, port_uint_single_t, "%u");
    ASSERT_EQ(((port_uint_single_t*)storage.content.sections[0])[4], 0xEEEEEEEE, port_uint_single_t, "%u");
    ASSERT_EQ(((port_uint_single_t*)storage.content.sections[0])[5], 0xFFFFFFFF, port_uint_single_t, "%u");
    ASSERT_TRUE(storage.size.sections != NULL);
    ASSERT_EQ(storage.size.sections[0], 24, port_uint_single_t, "%u");
    ASSERT_EQ(((port_uint_single_t*)storage.content.sections[1])[0], 0xEEEEEEEE, port_uint_single_t, "%u");
    ASSERT_EQ(((port_uint_single_t*)storage.content.sections[1])[1], 0xFFFFFFFF, port_uint_single_t, "%u");
    ASSERT_EQ(((port_uint_single_t*)storage.content.sections[1])[2], 0x88888888, port_uint_single_t, "%u");
    ASSERT_EQ(((port_uint_single_t*)storage.content.sections[1])[3], 0x77777777, port_uint_single_t, "%u");
    ASSERT_EQ(storage.size.sections[1], 16, port_uint_single_t, "%u");
    ASSERT_TRUE(storage.name_str_idx.sections != NULL);
    ASSERT_EQ(storage.name_str_idx.sections[0], 0, port_uint_single_t, "%u");
    ASSERT_EQ(storage.name_str_idx.sections[1], 1, port_uint_single_t, "%u");

    ASSERT_EQ(storage.num.symbols, 3, port_uint_single_t, "%u");
    ASSERT_TRUE(storage.symbol.section_idx != NULL);
    ASSERT_EQ(storage.symbol.section_idx[0], 0, port_uint_single_t, "%u");
    ASSERT_EQ(storage.symbol.section_idx[1], 0, port_uint_single_t, "%u");
    ASSERT_EQ(storage.symbol.section_idx[2], 1, port_uint_single_t, "%u");
    ASSERT_TRUE(storage.symbol.values != NULL);
    ASSERT_EQ(storage.symbol.values[0], 4, port_uint_single_t, "%u");
    ASSERT_EQ(storage.symbol.values[1], 23, port_uint_single_t, "%u");
    ASSERT_EQ(storage.symbol.values[2], 16, port_uint_single_t, "%u");
    ASSERT_TRUE(storage.name_str_idx.symbols != NULL);
    ASSERT_EQ(storage.name_str_idx.symbols[0], 2, port_uint_single_t, "%u");
    ASSERT_EQ(storage.name_str_idx.symbols[1], 1, port_uint_single_t, "%u");
    ASSERT_EQ(storage.name_str_idx.symbols[2], 0, port_uint_single_t, "%u");

    port_reset_data_storage(&storage);
}

TEST(port_write_data_storage_to_file)
{
    char *strings[] = {"hello", "world", "!!!"};

    port_uint_single_t property_name_str_idx[] = {0, 1};
    port_uint_single_t values[] = {0x12345678, 0xABCDEF01};
    port_void_ptr_t property_values[] = {&values[0], &values[1]};
    port_uint_single_t property_value_sizes[] = {sizeof(values[0]), sizeof(values[1])};

    port_uint_single_t section_name_str_idx[] = {0, 1};
    port_void_ptr_t sections[] = {"12345678", "abcdefgh"};
    port_uint_single_t section_sizes[] = {8, 8};

    port_uint_single_t symbol_name_str_idx[] = {0, 1, 2, 2};
    port_uint_single_t symbol_section_idx[] = {0, 0, 1, 1};
    port_uint_single_t symbol_values[] = {0, 8, 0, 8};

    port_data_storage_t storage = {
        .content = {
            .sections = sections,
            .properties = property_values,
            .strings = strings,
        },

        .size = {
            .sections = section_sizes,
            .properties = property_value_sizes,
        },

        .symbol = {
            .section_idx = symbol_section_idx,
            .values = symbol_values,
        },

        .name_str_idx = {
            .sections = section_name_str_idx,
            .properties = property_name_str_idx,
            .symbols = symbol_name_str_idx,
        },

        .num = {
            .properties = 2,
            .sections = 2,
            .symbols = 4,
            .strings = 3,
        },
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

    ASSERT_EQ(storage2.num.strings, storage.num.strings, port_uint_single_t, "%u");
    ASSERT_TRUE(storage2.content.strings != NULL);
    for (port_uint_single_t i = 0; i < storage.num.strings; i++)
        ASSERT_TRUE(strcmp(storage2.content.strings[i], storage.content.strings[i]) == 0);

    ASSERT_EQ(storage2.num.properties, storage.num.properties, port_uint_single_t, "%u");
    ASSERT_TRUE(storage2.content.properties != NULL);
    ASSERT_TRUE(storage2.size.properties != NULL);
    ASSERT_TRUE(storage2.name_str_idx.properties != NULL);
    for (port_uint_single_t i = 0; i < storage.num.properties; i++)
    {
        ASSERT_EQ(storage2.size.properties[i], storage.size.properties[i],
                port_uint_single_t, "%u");
        ASSERT_EQ(storage2.name_str_idx.properties[i], storage.name_str_idx.properties[i],
                port_uint_single_t, "%u");

        if (storage2.size.properties[i] == storage.size.properties[i])
        {
            for (port_uint_single_t j = 0; j < storage.size.properties[i]; j++)
                ASSERT_EQ(((char*)storage2.content.properties[i])[j],
                        ((char*)storage.content.properties[i])[j], port_uint8_t, "%u");
        }
    }

    ASSERT_EQ(storage2.num.sections, storage.num.sections, port_uint_single_t, "%u");
    ASSERT_TRUE(storage2.content.sections != NULL);
    ASSERT_TRUE(storage2.size.sections != NULL);
    ASSERT_TRUE(storage2.name_str_idx.sections != NULL);
    for (port_uint_single_t i = 0; i < storage.num.sections; i++)
    {
        ASSERT_EQ(storage2.size.sections[i], storage.size.sections[i],
                port_uint_single_t, "%u");
        ASSERT_EQ(storage2.name_str_idx.sections[i], storage.name_str_idx.sections[i],
                port_uint_single_t, "%u");

        if (storage2.size.sections[i] == storage.size.sections[i])
        {
            for (port_uint_single_t j = 0; j < storage.size.sections[i]; j++)
                ASSERT_EQ(((char*)storage2.content.sections[i])[j],
                        ((char*)storage.content.sections[i])[j], port_uint8_t, "%u");
        }
    }

    ASSERT_EQ(storage2.num.symbols, storage.num.symbols, port_uint_single_t, "%u");
    ASSERT_TRUE(storage2.symbol.section_idx != NULL);
    ASSERT_TRUE(storage2.symbol.values != NULL);
    ASSERT_TRUE(storage2.name_str_idx.symbols != NULL);
    for (port_uint_single_t i = 0; i < storage.num.symbols; i++)
    {
        ASSERT_EQ(storage2.symbol.section_idx[i], storage.symbol.section_idx[i],
                port_uint_single_t, "%u");
        ASSERT_EQ(storage2.symbol.values[i], storage.symbol.values[i],
                port_uint_single_t, "%u");
        ASSERT_EQ(storage2.name_str_idx.symbols[i], storage.name_str_idx.symbols[i],
                port_uint_single_t, "%u");
    }

    port_reset_data_storage(&storage2);
}

