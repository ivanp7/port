#include "test.h"

#include "port/memory.fun.h"
#include "port/memory/copy.fun.h"
#include "port/memory/read.fun.h"
#include "port/memory/write.fun.h"
#include "port/memory/unit.typ.h"
#include "port/memory.def.h"
#include "port/constants.def.h"
#include "port/float.fun.h"
#include "port/vector.def.h"

#include <tgmath.h>

TEST(PORT_MEMORY_REF_IS_FAR)
{
    ASSERT_TRUE(PORT_MEMORY_REF_IS_FAR(1));
    ASSERT_TRUE(PORT_MEMORY_REF_IS_FAR(0));
    ASSERT_FALSE(PORT_MEMORY_REF_IS_FAR(-1));
}

TEST(PORT_MEMORY_REF_FAR)
{
    ASSERT_EQ(PORT_MEMORY_REF_FAR(port_memory_ref_t, 0, 0, 1), 0x1, port_uint_single_t, "%X");
    ASSERT_EQ(PORT_MEMORY_REF_FAR(port_memory_ref_t, 1, 0, 1), 0x2, port_uint_single_t, "%X");
    ASSERT_EQ(PORT_MEMORY_REF_FAR(port_memory_ref_t, 1, 1, 1), 0x3, port_uint_single_t, "%X");
    ASSERT_EQ(PORT_MEMORY_REF_FAR(port_memory_ref_t, 2, 0, 1), 0x4, port_uint_single_t, "%X");
    ASSERT_EQ(PORT_MEMORY_REF_FAR(port_memory_ref_t, 2, 1, 1), 0x5, port_uint_single_t, "%X");
    ASSERT_EQ(PORT_MEMORY_REF_FAR(port_memory_ref_t, 2, 2, 1), 0x6, port_uint_single_t, "%X");
    ASSERT_EQ(PORT_MEMORY_REF_FAR(port_memory_ref_t, 2, 3, 1), 0x7, port_uint_single_t, "%X");
    ASSERT_EQ(PORT_MEMORY_REF_FAR(port_memory_ref_t, 3, 0, 1), 0x8, port_uint_single_t, "%X");
    ASSERT_EQ(PORT_MEMORY_REF_FAR(port_memory_ref_t, 3, 0, 2), 0x10, port_uint_single_t, "%X");
    ASSERT_EQ(PORT_MEMORY_REF_FAR(port_memory_ref_t, 4, 0, 0xACAB), 0xACAB0, port_uint_single_t, "%X");
    ASSERT_EQ(PORT_MEMORY_REF_FAR(port_memory_ref_t, 30, 0, 1), 0x40000000, port_uint_single_t, "%X");
    ASSERT_EQ(PORT_MEMORY_REF_FAR(port_memory_ref_t, 30, 0xDEADBEE, 1), 0x4DEADBEE, port_uint_single_t, "%X");
    ASSERT_EQ(PORT_MEMORY_REF_FAR(port_memory_ref_t, 13, 7331, 1337), 0xA73CA3, port_uint_single_t, "%X");
}

TEST(PORT_MEMORY_REF_FAR__TABLE_INDEX)
{
    ASSERT_EQ(PORT_MEMORY_REF_FAR__TABLE_INDEX(0xACAB5, 4), 5, port_uint_single_t, "%X");
    ASSERT_EQ(PORT_MEMORY_REF_FAR__TABLE_INDEX(0x4DEADBEE, 30), 0xDEADBEE, port_uint_single_t, "%X");
    ASSERT_EQ(PORT_MEMORY_REF_FAR__TABLE_INDEX(0xA73CA3, 13), 7331, port_uint_single_t, "%X");
}

TEST(PORT_MEMORY_REF_FAR__OFFSET)
{
    ASSERT_EQ(PORT_MEMORY_REF_FAR__OFFSET(0xACAB5, 4), 0xACAB, port_uint_single_t, "%X");
    ASSERT_EQ(PORT_MEMORY_REF_FAR__OFFSET(0x4DEADBEE, 30), 1, port_uint_single_t, "%X");
    ASSERT_EQ(PORT_MEMORY_REF_FAR__OFFSET(0xA73CA3, 13), 1337, port_uint_single_t, "%X");
}

TEST(port_memory_at)
{
    port_memory_unit_t unit0 = {0};
    port_memory_unit_t unit1 = {0};
    port_memory_unit_t unit2 = {0};
    port_const_void_ptr_t memory_table[3] = {&unit0, &unit1, &unit2};

    port_memory_ref_t ref;
    const port_memory_unit_t *ptr;

    ref = -1;
    ptr = port_memory_at(ref, (port_memory_ref_format_t){.near = {2}}, &unit2, memory_table);
    ASSERT_EQ(ptr - &unit2, 1, ptrdiff_t, "%ti");

    ref = -10;
    ptr = port_memory_at(ref, (port_memory_ref_format_t){.near = {2}}, NULL, memory_table);
    ASSERT_EQ(ptr - &unit0, 10, ptrdiff_t, "%ti");

    port_uint8_t num_idx_bits = 2;
    port_uint8_t offset_shift = 8;

    ref = PORT_MEMORY_REF_FAR(port_memory_ref_t, num_idx_bits, 0, 0);
    ptr = port_memory_at(ref, (port_memory_ref_format_t){.far = {num_idx_bits, offset_shift + 2}}, NULL, memory_table);
    ASSERT_EQ(ptr - &unit0, 0, ptrdiff_t, "%ti");

    ref = PORT_MEMORY_REF_FAR(port_memory_ref_t, num_idx_bits, 1, 10);
    ptr = port_memory_at(ref, (port_memory_ref_format_t){.far = {num_idx_bits, offset_shift + 2}}, NULL, memory_table + 1);
    ASSERT_EQ(ptr - &unit2, 10 << offset_shift, ptrdiff_t, "%ti");

    ref = PORT_MEMORY_REF_FAR(port_memory_ref_t, num_idx_bits, 0, 5);
    ptr = port_memory_at(ref, (port_memory_ref_format_t){.far = {num_idx_bits, offset_shift + 2}}, NULL, memory_table + 2);
    ASSERT_EQ(ptr - &unit2, 5 << offset_shift, ptrdiff_t, "%ti");
}

TEST(port_memory_copy)
{
#define NUM_BITS 16
#define NUM_UNITS (1 << NUM_BITS)

    port_memory_unit_t src[NUM_UNITS], dest[NUM_UNITS] = {0};
    for (port_uint32_t i = 0; i < NUM_UNITS; i++)
        src[i].as_uint_single = i << (i % (32 - NUM_BITS + 1));

    port_memory_copy(dest, src, sizeof(port_memory_unit_t) * NUM_UNITS);

    for (port_uint32_t i = 0; i < NUM_UNITS; i++)
        ASSERT_EQ(dest[i].as_uint_single, src[i].as_uint_single, port_uint_single_t, "%u");

#undef NUM_UNITS
#undef NUM_BITS
}

TEST(port_memory_read_uint8)
{
    port_uint8_t memory[] = {0x00, 0x10, 0x55, 0x68, 0xAA, 0xBC, 0xED, 0xFF};

    ASSERT_EQ(port_memory_read_uint8(memory, 0), 0x00, port_uint8_t, "%X");
    ASSERT_EQ(port_memory_read_uint8(memory, 1), 0x10, port_uint8_t, "%X");
    ASSERT_EQ(port_memory_read_uint8(memory, 2), 0x55, port_uint8_t, "%X");
    ASSERT_EQ(port_memory_read_uint8(memory, 3), 0x68, port_uint8_t, "%X");
    ASSERT_EQ(port_memory_read_uint8(memory, 4), 0xAA, port_uint8_t, "%X");
    ASSERT_EQ(port_memory_read_uint8(memory, 5), 0xBC, port_uint8_t, "%X");
    ASSERT_EQ(port_memory_read_uint8(memory, 6), 0xED, port_uint8_t, "%X");
    ASSERT_EQ(port_memory_read_uint8(memory, 7), 0xFF, port_uint8_t, "%X");
}

TEST(port_memory_read_uint16)
{
    port_uint16_t memory[] = {0x0010, 0x5568, 0xAABC, 0xEDFF};

    ASSERT_EQ(port_memory_read_uint16(memory, 0), 0x0010, port_uint16_t, "%X");
    ASSERT_EQ(port_memory_read_uint16(memory, 1), 0x5568, port_uint16_t, "%X");
    ASSERT_EQ(port_memory_read_uint16(memory, 2), 0xAABC, port_uint16_t, "%X");
    ASSERT_EQ(port_memory_read_uint16(memory, 3), 0xEDFF, port_uint16_t, "%X");
}

TEST(port_memory_read_uint32)
{
    port_uint32_t memory[] = {0x00105568, 0xAABCEDFF};

    ASSERT_EQ(port_memory_read_uint32(memory, 0), 0x00105568, port_uint32_t, "%X");
    ASSERT_EQ(port_memory_read_uint32(memory, 1), 0xAABCEDFF, port_uint32_t, "%X");
}

TEST(port_memory_read_uint64)
{
    port_uint64_t memory[] = {0x00105568AABCEDFFull, 0xFEEDDEADABBAACABull};

    ASSERT_EQ(port_memory_read_uint64(memory, 0), 0x00105568AABCEDFFull, port_uint64_t, "%lX");
    ASSERT_EQ(port_memory_read_uint64(memory, 1), 0xFEEDDEADABBAACABull, port_uint64_t, "%lX");
}

TEST(port_memory_read_float16)
{
    port_uint16_t memory[] = {port_convert_float32_to_float16(1.0f), port_convert_float32_to_float16(0.5f),
        port_convert_float32_to_float16(PORT_M_NAN), port_convert_float32_to_float16(PORT_M_INFINITY)};

    ASSERT_EQ(port_memory_read_float16(memory, 0), 1.0f, port_float32_t, "%g");
    ASSERT_EQ(port_memory_read_float16(memory, 1), 0.5f, port_float32_t, "%g");
    ASSERT_TRUE(isnan(port_memory_read_float16(memory, 2)));
    ASSERT_TRUE(isinf(port_memory_read_float16(memory, 3)));
}

TEST(port_memory_read_float32)
{
    port_float32_t memory[] = {1.5f, 10.0f};

    ASSERT_EQ(port_memory_read_float32(memory, 0), 1.5f, port_float32_t, "%g");
    ASSERT_EQ(port_memory_read_float32(memory, 1), 10.0f, port_float32_t, "%g");
}

TEST(port_memory_read_float64)
{
    port_float64_t memory[] = {1.5625, 1234.5};

    ASSERT_EQ(port_memory_read_float64(memory, 0), 1.5625, port_float64_t, "%g");
    ASSERT_EQ(port_memory_read_float64(memory, 1), 1234.5, port_float64_t, "%g");
}

TEST(port_memory_read_uint8_v16)
{
    port_uint8_t memory[20];
    for (port_uint8_t i = 0; i < 5; i++)
        for (port_uint8_t j = 0; j < 4; j++)
            memory[i*4 + j] = i*4 + j + 100;

    port_uint8_v16_t vector;

    for (port_uint8_t offset = 0; offset <= 4; offset++)
    {
        vector = port_memory_read_uint8_v16(memory, offset);

        for (port_uint8_t i = 0; i < 16; i++)
            ASSERT_EQ(vector.s[i], 100 + i + offset, port_uint8_t, "%u");
    }
}

TEST(port_memory_read_uint16_v8)
{
    port_uint16_t memory[10];
    for (port_uint8_t i = 0; i < 5; i++)
        for (port_uint8_t j = 0; j < 2; j++)
            memory[i*2 + j] = i*2 + j + 32760;

    port_uint16_v8_t vector;

    for (port_uint8_t offset = 0; offset <= 2; offset++)
    {
        vector = port_memory_read_uint16_v8(memory, offset);

        for (port_uint8_t i = 0; i < 8; i++)
            ASSERT_EQ(vector.s[i], 32760 + i + offset, port_uint16_t, "%u");
    }
}

TEST(port_memory_read_uint32_v4)
{
    port_uint32_t memory[5];
    for (port_uint8_t i = 0; i < 5; i++)
        memory[i] = i + 0xFFFFFFFD;

    port_uint32_v4_t vector;

    for (port_uint8_t offset = 0; offset <= 1; offset++)
    {
        vector = port_memory_read_uint32_v4(memory, offset);

        for (port_uint8_t i = 0; i < 4; i++)
            ASSERT_EQ(vector.s[i], 0xFFFFFFFD + i + offset, port_uint32_t, "%X");
    }
}

TEST(port_memory_read_uint64_v2)
{
    port_uint64_t memory[] = {0x00105568AABCEDFFull, 0xFEEDDEADABBAACABull,
         0x1122334455667788ull, 0xAABBCCDDEEFF0034ull};

    port_uint64_v2_t vector;

    for (port_uint8_t offset = 0; offset <= 2; offset++)
    {
        vector = port_memory_read_uint64_v2(memory, offset);

        for (port_uint8_t i = 0; i < 2; i++)
            ASSERT_EQ(vector.s[i], memory[offset + i], port_uint64_t, "%lX");
    }
}

TEST(port_memory_read_float16_v4)
{
    port_uint16_t memory[6];
    for (port_uint8_t i = 0; i < 3; i++)
        for (port_uint8_t j = 0; j < 2; j++)
            memory[i*2 + j] = port_convert_float32_to_float16(i*2 + j);

    port_float32_v4_t vector;

    for (port_uint8_t offset = 0; offset <= 2; offset++)
    {
        vector = port_memory_read_float16_v4(memory, offset);

        for (port_uint8_t i = 0; i < 4; i++)
            ASSERT_EQ(vector.s[i], i + offset, port_float32_t, "%g");
    }
}

TEST(port_memory_read_float32_v4)
{
    port_float32_t memory[5];
    for (port_uint8_t i = 0; i < 5; i++)
            memory[i] = i;

    port_float32_v4_t vector;

    for (port_uint8_t offset = 0; offset <= 1; offset++)
    {
        vector = port_memory_read_float32_v4(memory, offset);

        for (port_uint8_t i = 0; i < 4; i++)
            ASSERT_EQ(vector.s[i], i + offset, port_float32_t, "%g");
    }
}

TEST(port_memory_read_float64_v2)
{
    port_float64_t memory[] = {1.5625, 0.25, -PORT_M_INFINITY, 0.1111};

    port_float64_v2_t vector;

    for (port_uint8_t offset = 0; offset <= 2; offset++)
    {
        vector = port_memory_read_float64_v2(memory, offset);

        for (port_uint8_t i = 0; i < 2; i++)
            ASSERT_EQ(vector.s[i], memory[i + offset], port_float64_t, "%g");
    }
}

TEST(port_memory_write_uint8)
{
    port_uint8_t memory[8];

    port_memory_write_uint8(memory, 0, 0x00);
    port_memory_write_uint8(memory, 1, 0x10);
    port_memory_write_uint8(memory, 2, 0x55);
    port_memory_write_uint8(memory, 3, 0x68);
    port_memory_write_uint8(memory, 4, 0xAA);
    port_memory_write_uint8(memory, 5, 0xBC);
    port_memory_write_uint8(memory, 6, 0xED);
    port_memory_write_uint8(memory, 7, 0xFF);

    ASSERT_EQ(memory[0], 0x00, port_uint8_t, "%X");
    ASSERT_EQ(memory[1], 0x10, port_uint8_t, "%X");
    ASSERT_EQ(memory[2], 0x55, port_uint8_t, "%X");
    ASSERT_EQ(memory[3], 0x68, port_uint8_t, "%X");
    ASSERT_EQ(memory[4], 0xAA, port_uint8_t, "%X");
    ASSERT_EQ(memory[5], 0xBC, port_uint8_t, "%X");
    ASSERT_EQ(memory[6], 0xED, port_uint8_t, "%X");
    ASSERT_EQ(memory[7], 0xFF, port_uint8_t, "%X");
}

TEST(port_memory_write_uint16)
{
    port_uint16_t memory[4];

    port_memory_write_uint16(memory, 0, 0x0010);
    port_memory_write_uint16(memory, 1, 0x5568);
    port_memory_write_uint16(memory, 2, 0xAABC);
    port_memory_write_uint16(memory, 3, 0xEDFF);

    ASSERT_EQ(memory[0], 0x0010, port_uint16_t, "%X");
    ASSERT_EQ(memory[1], 0x5568, port_uint16_t, "%X");
    ASSERT_EQ(memory[2], 0xAABC, port_uint16_t, "%X");
    ASSERT_EQ(memory[3], 0xEDFF, port_uint16_t, "%X");
}

TEST(port_memory_write_uint32)
{
    port_uint32_t memory[2];

    port_memory_write_uint32(memory, 0, 0x00105568);
    port_memory_write_uint32(memory, 1, 0xAABCEDFF);

    ASSERT_EQ(memory[0], 0x00105568, port_uint32_t, "%X");
    ASSERT_EQ(memory[1], 0xAABCEDFF, port_uint32_t, "%X");
}

TEST(port_memory_write_uint64)
{
    port_uint64_t memory[2];

    port_memory_write_uint64(memory, 0, 0x00105568AABCEDFFull);
    port_memory_write_uint64(memory, 1, 0xFEEDDEADABBAACABull);

    ASSERT_EQ(memory[0], 0x00105568AABCEDFFull, port_uint64_t, "%lX");
    ASSERT_EQ(memory[1], 0xFEEDDEADABBAACABull, port_uint64_t, "%lX");
}

TEST(port_memory_write_float16)
{
    port_uint16_t memory[4];

    port_memory_write_float16(memory, 0, 1.0f);
    port_memory_write_float16(memory, 1, 0.5f);
    port_memory_write_float16(memory, 2, PORT_M_NAN);
    port_memory_write_float16(memory, 3, PORT_M_INFINITY);

    ASSERT_EQ(memory[0], port_convert_float32_to_float16(1.0f), port_float32_t, "%g");
    ASSERT_EQ(memory[1], port_convert_float32_to_float16(0.5f), port_float32_t, "%g");
    ASSERT_EQ(memory[2], port_convert_float32_to_float16(PORT_M_NAN), port_float32_t, "%g");
    ASSERT_EQ(memory[3], port_convert_float32_to_float16(PORT_M_INFINITY), port_float32_t, "%g");
}

TEST(port_memory_write_float32)
{
    port_float32_t memory[2];

    port_memory_write_float32(memory, 0, 1.5f);
    port_memory_write_float32(memory, 1, 10.0f);

    ASSERT_EQ(memory[0], 1.5f, port_float32_t, "%g");
    ASSERT_EQ(memory[1], 10.0f, port_float32_t, "%g");
}

TEST(port_memory_write_float64)
{
    port_float64_t memory[2];

    port_memory_write_float64(memory, 0, 1.5625);
    port_memory_write_float64(memory, 1, 1234.5);

    ASSERT_EQ(memory[0], 1.5625, port_float64_t, "%lg");
    ASSERT_EQ(memory[1], 1234.5, port_float64_t, "%lg");
}

TEST(port_memory_write_uint8_v16)
{
    port_uint8_t memory[20];

    port_uint8_v16_t vector;
    for (port_uint8_t i = 0; i < 16; i++)
        vector.s[i] = 100 + i;

    for (port_uint8_t offset = 0; offset <= 4; offset++)
    {
        port_memory_write_uint8_v16(memory, offset, vector);

        for (port_uint8_t i = 0; i < 16; i++)
            ASSERT_EQ(memory[offset + i], 100 + i, port_uint8_t, "%u");
    }
}

TEST(port_memory_write_uint16_v8)
{
    port_uint16_t memory[10];

    port_uint16_v8_t vector;
    for (port_uint8_t i = 0; i < 8; i++)
        vector.s[i] = 32760 + i;

    for (port_uint8_t offset = 0; offset <= 2; offset++)
    {
        port_memory_write_uint16_v8(memory, offset, vector);

        for (port_uint8_t i = 0; i < 8; i++)
            ASSERT_EQ(memory[offset + i], 32760 + i, port_uint16_t, "%u");
    }
}

TEST(port_memory_write_uint32_v4)
{
    port_uint32_t memory[5];

    port_uint32_v4_t vector;
    for (port_uint8_t i = 0; i < 4; i++)
        vector.s[i] = i + 0xFFFFFFFD;

    for (port_uint8_t offset = 0; offset <= 1; offset++)
    {
        port_memory_write_uint32_v4(memory, offset, vector);

        for (port_uint8_t i = 0; i < 4; i++)
            ASSERT_EQ(memory[offset + i], 0xFFFFFFFD + i, port_uint32_t, "%X");
    }
}

TEST(port_memory_write_uint64_v2)
{
    port_uint64_t memory[4];

    port_uint64_v2_t vector = PORT_V2(0x00105568AABCEDFFull, 0xFEEDDEADABBAACABull);

    for (port_uint8_t offset = 0; offset <= 2; offset++)
    {
        port_memory_write_uint64_v2(memory, offset, vector);

        for (port_uint8_t i = 0; i < 2; i++)
            ASSERT_EQ(memory[offset + i], vector.s[i], port_uint64_t, "%lX");
    }
}

TEST(port_memory_write_float16_v4)
{
    port_uint16_t memory[6];

    port_float32_v4_t vector;
    for (port_uint8_t i = 0; i < 4; i++)
        vector.s[i] = i*3.0f - 1.0f;

    for (port_uint8_t offset = 0; offset <= 2; offset++)
    {
        port_memory_write_float16_v4(memory, offset, vector);

        for (port_uint8_t i = 0; i < 4; i++)
            ASSERT_EQ(memory[offset + i], port_convert_float32_to_float16(i*3.0f - 1.0f), port_float32_t, "%g");
    }
}

TEST(port_memory_write_float32_v4)
{
    port_float32_t memory[5];

    port_float32_v4_t vector;
    for (port_uint8_t i = 0; i < 4; i++)
        vector.s[i] = i*3.0f - 1.0f;

    for (port_uint8_t offset = 0; offset <= 1; offset++)
    {
        port_memory_write_float32_v4(memory, offset, vector);

        for (port_uint8_t i = 0; i < 4; i++)
            ASSERT_EQ(memory[offset + i], i*3.0f - 1.0f, port_float32_t, "%g");
    }
}

TEST(port_memory_write_float64_v2)
{
    port_float64_t memory[4];

    port_float64_v2_t vector = PORT_V2(1.3625, -PORT_M_INFINITY);

    for (port_uint8_t offset = 0; offset <= 2; offset++)
    {
        port_memory_write_float64_v2(memory, offset, vector);

        for (port_uint8_t i = 0; i < 2; i++)
            ASSERT_EQ(memory[offset + i], vector.s[i], port_float64_t, "%lg");
    }
}

