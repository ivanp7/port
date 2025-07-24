#include "test.h"

#include "port/memory.fun.h"
#include "port/memory/copy.fun.h"
#include "port/memory/read.fun.h"
#include "port/memory/write.fun.h"
#include "port/memory.def.h"
#include "port/float.fun.h"
#include "port/constants.def.h"
#include "port/vector.def.h"

#include <tgmath.h>

#define NUM_BITS 16
#define NUM_UNITS (1 << NUM_BITS)

typedef void (*memcpy_fn)(port_memory_ptr_t restrict,
        port_const_memory_ptr_t restrict,
        size_t);

static
port_uint8_t test_memcpy(memcpy_fn fn)
{
    port_memory_unit_t src[NUM_UNITS], dest[NUM_UNITS] = {0};
    for (port_uint32_t i = 0; i < NUM_UNITS; i++)
        src[i].as_uint_single = i << (i % (32 - NUM_BITS + 1));

    fn(dest, src, NUM_UNITS);

    for (port_uint32_t i = 0; i < NUM_UNITS; i++)
        if (dest[i].as_uint_single != src[i].as_uint_single)
            return 0;

    return 1;
}

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

TEST(port_memory_at_global)
{
    port_memory_unit_t unit0 = {0};
    port_memory_unit_t unit1 = {0};
    port_memory_unit_t unit2 = {0};
    port_const_memory_ptr_t memory_table[3] = {&unit0, &unit1, &unit2};

    port_memory_ref_t ref;
    port_const_memory_ptr_t ptr;

    ref = -1;
    ptr = port_memory_at_global(ref, (port_memory_ref_format_t){0, 0}, &unit2, memory_table);
    ASSERT_EQ(ptr - &unit2, 1, ptrdiff_t, "%ti");

    ref = -10;
    ptr = port_memory_at_global(ref, (port_memory_ref_format_t){10, 20}, NULL, memory_table);
    ASSERT_EQ(ptr - &unit0, 10, ptrdiff_t, "%ti");

    port_uint8_t num_idx_bits = 2;
    port_uint8_t offset_shift = 8;

    ref = PORT_MEMORY_REF_FAR(port_memory_ref_t, num_idx_bits, 0, 0);
    ptr = port_memory_at_global(ref, (port_memory_ref_format_t){num_idx_bits, offset_shift}, NULL, memory_table);
    ASSERT_EQ(ptr - &unit0, 0, ptrdiff_t, "%ti");

    ref = PORT_MEMORY_REF_FAR(port_memory_ref_t, num_idx_bits, 1, 10);
    ptr = port_memory_at_global(ref, (port_memory_ref_format_t){num_idx_bits, offset_shift}, NULL, memory_table + 1);
    ASSERT_EQ(ptr - &unit2, 10 << offset_shift, ptrdiff_t, "%ti");

    ref = PORT_MEMORY_REF_FAR(port_memory_ref_t, num_idx_bits, 0, 5);
    ptr = port_memory_at_global(ref, (port_memory_ref_format_t){num_idx_bits, offset_shift}, NULL, memory_table + 2);
    ASSERT_EQ(ptr - &unit2, 5 << offset_shift, ptrdiff_t, "%ti");
}

TEST(port_memory_copy_global_to_private)
{
    ASSERT_TRUE(test_memcpy(port_memory_copy_global_to_private));
}

TEST(port_memory_copy_constant_to_private)
{
    ASSERT_TRUE(test_memcpy(port_memory_copy_constant_to_private));
}

TEST(port_memory_copy_local_to_private)
{
    ASSERT_TRUE(test_memcpy(port_memory_copy_local_to_private));
}

TEST(port_memory_copy_private_to_private)
{
    ASSERT_TRUE(test_memcpy(port_memory_copy_private_to_private));
}

TEST(port_memory_copy_global_to_local)
{
    ASSERT_TRUE(test_memcpy(port_memory_copy_global_to_local));
}

TEST(port_memory_copy_constant_to_local)
{
    ASSERT_TRUE(test_memcpy(port_memory_copy_constant_to_local));
}

TEST(port_memory_copy_local_to_local)
{
    ASSERT_TRUE(test_memcpy(port_memory_copy_local_to_local));
}

TEST(port_memory_copy_private_to_local)
{
    ASSERT_TRUE(test_memcpy(port_memory_copy_private_to_local));
}

TEST(port_memory_copy_global_to_global)
{
    ASSERT_TRUE(test_memcpy(port_memory_copy_global_to_global));
}

TEST(port_memory_copy_local_to_global)
{
    ASSERT_TRUE(test_memcpy(port_memory_copy_local_to_global));
}

TEST(port_memory_copy_constant_to_global)
{
    ASSERT_TRUE(test_memcpy(port_memory_copy_constant_to_global));
}

TEST(port_memory_copy_private_to_global)
{
    ASSERT_TRUE(test_memcpy(port_memory_copy_private_to_global));
}

TEST(port_memory_read_private_uint8)
{
    port_memory_unit_t memory[] = {{.as_uint_quarter = {0x00, 0x10, 0x55, 0x68}},
        {.as_uint_quarter = {0xAA, 0xBC, 0xED, 0xFF}}};

    ASSERT_EQ(port_memory_read_private_uint8(memory, 0), 0x00, port_uint8_t, "%X");
    ASSERT_EQ(port_memory_read_private_uint8(memory, 1), 0x10, port_uint8_t, "%X");
    ASSERT_EQ(port_memory_read_private_uint8(memory, 2), 0x55, port_uint8_t, "%X");
    ASSERT_EQ(port_memory_read_private_uint8(memory, 3), 0x68, port_uint8_t, "%X");
    ASSERT_EQ(port_memory_read_private_uint8(memory, 4), 0xAA, port_uint8_t, "%X");
    ASSERT_EQ(port_memory_read_private_uint8(memory, 5), 0xBC, port_uint8_t, "%X");
    ASSERT_EQ(port_memory_read_private_uint8(memory, 6), 0xED, port_uint8_t, "%X");
    ASSERT_EQ(port_memory_read_private_uint8(memory, 7), 0xFF, port_uint8_t, "%X");
}

TEST(port_memory_read_private_uint16)
{
    port_memory_unit_t memory[] = {{.as_uint_half = {0x0010, 0x5568}},
        {.as_uint_half = {0xAABC, 0xEDFF}}};

    ASSERT_EQ(port_memory_read_private_uint16(memory, 0), 0x0010, port_uint16_t, "%X");
    ASSERT_EQ(port_memory_read_private_uint16(memory, 1), 0x5568, port_uint16_t, "%X");
    ASSERT_EQ(port_memory_read_private_uint16(memory, 2), 0xAABC, port_uint16_t, "%X");
    ASSERT_EQ(port_memory_read_private_uint16(memory, 3), 0xEDFF, port_uint16_t, "%X");
}

TEST(port_memory_read_private_uint32)
{
    port_memory_unit_t memory[] = {{.as_uint_single = 0x00105568},
        {.as_uint_single = 0xAABCEDFF}};

    ASSERT_EQ(port_memory_read_private_uint32(memory, 0), 0x00105568, port_uint32_t, "%X");
    ASSERT_EQ(port_memory_read_private_uint32(memory, 1), 0xAABCEDFF, port_uint32_t, "%X");
}

TEST(port_memory_read_private_uint64)
{
    port_memory_unit_double_t double_units[2] = {{.as_uint_double = 0x00105568AABCEDFFull},
        {.as_uint_double = 0xFEEDDEADABBAACABull}};

    port_memory_unit_t memory[] = {double_units[0].as_unit[0], double_units[0].as_unit[1],
        double_units[1].as_unit[0], double_units[1].as_unit[1]};

    ASSERT_EQ(port_memory_read_private_uint64(memory, 0), double_units[0].as_uint_double, port_uint64_t, "%lX");
    ASSERT_EQ(port_memory_read_private_uint64(memory, 1), double_units[1].as_uint_double, port_uint64_t, "%lX");
}

TEST(port_memory_read_private_float16)
{
    port_memory_unit_t memory[] = {{.PORT_MEMORY_UNIT__AS_FLOAT_HALF = {port_convert_float32_to_float16(1.0f),
        port_convert_float32_to_float16(0.5f)}},
        {.PORT_MEMORY_UNIT__AS_FLOAT_HALF = {port_convert_float32_to_float16(PORT_M_NAN),
                              port_convert_float32_to_float16(PORT_M_INFINITY)}}};

    ASSERT_EQ(port_memory_read_private_float16(memory, 0), 1.0f, port_float32_t, "%g");
    ASSERT_EQ(port_memory_read_private_float16(memory, 1), 0.5f, port_float32_t, "%g");
    ASSERT_TRUE(isnan(port_memory_read_private_float16(memory, 2)));
    ASSERT_TRUE(isinf(port_memory_read_private_float16(memory, 3)));
}

TEST(port_memory_read_private_float32)
{
    port_memory_unit_t memory[] = {{.as_float_single = 1.5f},
        {.as_float_single = 10.0f}};

    ASSERT_EQ(port_memory_read_private_float32(memory, 0), 1.5f, port_float32_t, "%g");
    ASSERT_EQ(port_memory_read_private_float32(memory, 1), 10.0f, port_float32_t, "%g");
}

TEST(port_memory_read_private_float64)
{
    port_memory_unit_double_t double_units[2] = {{.as_float_double = 1.5625},
        {.as_float_double = 1234.5}};

    port_memory_unit_t memory[] = {double_units[0].as_unit[0], double_units[0].as_unit[1],
        double_units[1].as_unit[0], double_units[1].as_unit[1]};

    ASSERT_EQ(port_memory_read_private_float64(memory, 0), double_units[0].as_float_double, port_float64_t, "%g");
    ASSERT_EQ(port_memory_read_private_float64(memory, 1), double_units[1].as_float_double, port_float64_t, "%g");
}

TEST(port_memory_read_private_memory_ref_quarter)
{
    port_memory_unit_t memory[] = {{.as_ref_quarter = {0x00, 0x10, 0x55, 0x7F}},
        {.as_ref_quarter = {-1, -63, -64, -128}}};

    ASSERT_EQ(port_memory_read_private_memory_ref_quarter(memory, 0), 0x00, port_memory_ref_quarter_t, "%X");
    ASSERT_EQ(port_memory_read_private_memory_ref_quarter(memory, 1), 0x10, port_memory_ref_quarter_t, "%X");
    ASSERT_EQ(port_memory_read_private_memory_ref_quarter(memory, 2), 0x55, port_memory_ref_quarter_t, "%X");
    ASSERT_EQ(port_memory_read_private_memory_ref_quarter(memory, 3), 0x7F, port_memory_ref_quarter_t, "%X");
    ASSERT_EQ(port_memory_read_private_memory_ref_quarter(memory, 4), -1, port_memory_ref_quarter_t, "%X");
    ASSERT_EQ(port_memory_read_private_memory_ref_quarter(memory, 5), -63, port_memory_ref_quarter_t, "%X");
    ASSERT_EQ(port_memory_read_private_memory_ref_quarter(memory, 6), -64, port_memory_ref_quarter_t, "%X");
    ASSERT_EQ(port_memory_read_private_memory_ref_quarter(memory, 7), -128, port_memory_ref_quarter_t, "%X");
}

TEST(port_memory_read_private_memory_ref_half)
{
    port_memory_unit_t memory[] = {{.as_ref_half = {0x0000, 0x7FFF}},
        {.as_ref_half = {-1, -32768}}};

    ASSERT_EQ(port_memory_read_private_memory_ref_half(memory, 0), 0x0000, port_memory_ref_half_t, "%X");
    ASSERT_EQ(port_memory_read_private_memory_ref_half(memory, 1), 0x7FFF, port_memory_ref_half_t, "%X");
    ASSERT_EQ(port_memory_read_private_memory_ref_half(memory, 2), -1, port_memory_ref_half_t, "%X");
    ASSERT_EQ(port_memory_read_private_memory_ref_half(memory, 3), -32768, port_memory_ref_half_t, "%X");
}

TEST(port_memory_read_private_memory_ref)
{
    port_memory_unit_t memory[] = {{.as_ref = 0}, {.as_ref = 0x7FFFFFFF}, {.as_ref = -1}};

    ASSERT_EQ(port_memory_read_private_memory_ref(memory, 0), 0, port_memory_ref_t, "%X");
    ASSERT_EQ(port_memory_read_private_memory_ref(memory, 1), 0x7FFFFFFF, port_memory_ref_t, "%X");
    ASSERT_EQ(port_memory_read_private_memory_ref(memory, 2), -1, port_memory_ref_t, "%X");
}

TEST(port_memory_read_private_uint8_v16)
{
    port_memory_unit_t memory[5];
    for (port_uint8_t i = 0; i < 5; i++)
        for (port_uint8_t j = 0; j < 4; j++)
            memory[i].as_uint_quarter[j] = i*4 + j + 100;

    port_uint8_v16_t vector;

    for (port_uint8_t offset = 0; offset <= 4; offset++)
    {
        vector = port_memory_read_private_uint8_v16(memory, offset);

        for (port_uint8_t i = 0; i < 16; i++)
            ASSERT_EQ(vector.s[i], 100 + i + offset, port_uint8_t, "%u");
    }
}

TEST(port_memory_read_private_uint16_v8)
{
    port_memory_unit_t memory[5];
    for (port_uint8_t i = 0; i < 5; i++)
        for (port_uint8_t j = 0; j < 2; j++)
            memory[i].as_uint_half[j] = i*2 + j + 32760;

    port_uint16_v8_t vector;

    for (port_uint8_t offset = 0; offset <= 2; offset++)
    {
        vector = port_memory_read_private_uint16_v8(memory, offset);

        for (port_uint8_t i = 0; i < 8; i++)
            ASSERT_EQ(vector.s[i], 32760 + i + offset, port_uint16_t, "%u");
    }
}

TEST(port_memory_read_private_uint32_v4)
{
    port_memory_unit_t memory[5];
    for (port_uint8_t i = 0; i < 5; i++)
        memory[i].as_uint_single = i + 0xFFFFFFFD;

    port_uint32_v4_t vector;

    for (port_uint8_t offset = 0; offset <= 1; offset++)
    {
        vector = port_memory_read_private_uint32_v4(memory, offset);

        for (port_uint8_t i = 0; i < 4; i++)
            ASSERT_EQ(vector.s[i], 0xFFFFFFFD + i + offset, port_uint32_t, "%X");
    }
}

TEST(port_memory_read_private_uint64_v2)
{
    port_memory_unit_double_t double_units[4] = {{.as_uint_double = 0x00105568AABCEDFFull},
        {.as_uint_double = 0xFEEDDEADABBAACABull},
        {.as_uint_double = 0x1122334455667788ull},
        {.as_uint_double = 0xAABBCCDDEEFF0034ull}};

    port_memory_unit_t memory[] = {double_units[0].as_unit[0], double_units[0].as_unit[1],
        double_units[1].as_unit[0], double_units[1].as_unit[1],
        double_units[2].as_unit[0], double_units[2].as_unit[1],
        double_units[3].as_unit[0], double_units[3].as_unit[1]};

    port_uint64_v2_t vector;

    for (port_uint8_t offset = 0; offset <= 2; offset++)
    {
        vector = port_memory_read_private_uint64_v2(memory, offset);

        for (port_uint8_t i = 0; i < 2; i++)
            ASSERT_EQ(vector.s[i], double_units[i + offset].as_uint_double, port_uint64_t, "%lX");
    }
}

TEST(port_memory_read_private_float16_v4)
{
    port_memory_unit_t memory[3];
    for (port_uint8_t i = 0; i < 3; i++)
        for (port_uint8_t j = 0; j < 2; j++)
            memory[i].PORT_MEMORY_UNIT__AS_FLOAT_HALF[j] = port_convert_float32_to_float16(i*2 + j);

    port_float32_v4_t vector;

    for (port_uint8_t offset = 0; offset <= 2; offset++)
    {
        vector = port_memory_read_private_float16_v4(memory, offset);

        for (port_uint8_t i = 0; i < 4; i++)
            ASSERT_EQ(vector.s[i], i + offset, port_float32_t, "%g");
    }
}

TEST(port_memory_read_private_float32_v4)
{
    port_memory_unit_t memory[5];
    for (port_uint8_t i = 0; i < 5; i++)
            memory[i].as_float_single = i;

    port_float32_v4_t vector;

    for (port_uint8_t offset = 0; offset <= 1; offset++)
    {
        vector = port_memory_read_private_float32_v4(memory, offset);

        for (port_uint8_t i = 0; i < 4; i++)
            ASSERT_EQ(vector.s[i], i + offset, port_float32_t, "%g");
    }
}

TEST(port_memory_read_private_float64_v2)
{
    port_memory_unit_double_t double_units[4] = {{.as_float_double = 1.5625},
        {.as_float_double = 0.25},
        {.as_float_double = -PORT_M_INFINITY},
        {.as_float_double = 0.1111}};

    port_memory_unit_t memory[] = {double_units[0].as_unit[0], double_units[0].as_unit[1],
        double_units[1].as_unit[0], double_units[1].as_unit[1],
        double_units[2].as_unit[0], double_units[2].as_unit[1],
        double_units[3].as_unit[0], double_units[3].as_unit[1]};

    port_float64_v2_t vector;

    for (port_uint8_t offset = 0; offset <= 2; offset++)
    {
        vector = port_memory_read_private_float64_v2(memory, offset);

        for (port_uint8_t i = 0; i < 2; i++)
            ASSERT_EQ(vector.s[i], double_units[i + offset].as_float_double, port_float64_t, "%g");
    }
}

TEST(port_memory_write_private_uint8)
{
    port_memory_unit_t memory[2];

    port_memory_write_private_uint8(memory, 0x00, 0);
    port_memory_write_private_uint8(memory, 0x10, 1);
    port_memory_write_private_uint8(memory, 0x55, 2);
    port_memory_write_private_uint8(memory, 0x68, 3);
    port_memory_write_private_uint8(memory, 0xAA, 4);
    port_memory_write_private_uint8(memory, 0xBC, 5);
    port_memory_write_private_uint8(memory, 0xED, 6);
    port_memory_write_private_uint8(memory, 0xFF, 7);

    ASSERT_EQ(memory[0].as_uint_quarter[0], 0x00, port_uint8_t, "%X");
    ASSERT_EQ(memory[0].as_uint_quarter[1], 0x10, port_uint8_t, "%X");
    ASSERT_EQ(memory[0].as_uint_quarter[2], 0x55, port_uint8_t, "%X");
    ASSERT_EQ(memory[0].as_uint_quarter[3], 0x68, port_uint8_t, "%X");
    ASSERT_EQ(memory[1].as_uint_quarter[0], 0xAA, port_uint8_t, "%X");
    ASSERT_EQ(memory[1].as_uint_quarter[1], 0xBC, port_uint8_t, "%X");
    ASSERT_EQ(memory[1].as_uint_quarter[2], 0xED, port_uint8_t, "%X");
    ASSERT_EQ(memory[1].as_uint_quarter[3], 0xFF, port_uint8_t, "%X");
}

TEST(port_memory_write_private_uint16)
{
    port_memory_unit_t memory[2];

    port_memory_write_private_uint16(memory, 0x0010, 0);
    port_memory_write_private_uint16(memory, 0x5568, 1);
    port_memory_write_private_uint16(memory, 0xAABC, 2);
    port_memory_write_private_uint16(memory, 0xEDFF, 3);

    ASSERT_EQ(memory[0].as_uint_half[0], 0x0010, port_uint16_t, "%X");
    ASSERT_EQ(memory[0].as_uint_half[1], 0x5568, port_uint16_t, "%X");
    ASSERT_EQ(memory[1].as_uint_half[0], 0xAABC, port_uint16_t, "%X");
    ASSERT_EQ(memory[1].as_uint_half[1], 0xEDFF, port_uint16_t, "%X");
}

TEST(port_memory_write_private_uint32)
{
    port_memory_unit_t memory[2];

    port_memory_write_private_uint32(memory, 0x00105568, 0);
    port_memory_write_private_uint32(memory, 0xAABCEDFF, 1);

    ASSERT_EQ(memory[0].as_uint_single, 0x00105568, port_uint32_t, "%X");
    ASSERT_EQ(memory[1].as_uint_single, 0xAABCEDFF, port_uint32_t, "%X");
}

TEST(port_memory_write_private_uint64)
{
    port_memory_unit_t memory[4];

    port_memory_unit_double_t double_units[2] = {{.as_uint_double = 0x00105568AABCEDFFull},
        {.as_uint_double = 0xFEEDDEADABBAACABull}};

    port_memory_write_private_uint64(memory, double_units[0].as_uint_double, 0);
    port_memory_write_private_uint64(memory, double_units[1].as_uint_double, 1);

    ASSERT_EQ(memory[0].as_uint_single, double_units[0].as_unit[0].as_uint_single,
            port_uint_single_t, "%X");
    ASSERT_EQ(memory[1].as_uint_single, double_units[0].as_unit[1].as_uint_single,
            port_uint_single_t, "%X");
    ASSERT_EQ(memory[2].as_uint_single, double_units[1].as_unit[0].as_uint_single,
            port_uint_single_t, "%X");
    ASSERT_EQ(memory[3].as_uint_single, double_units[1].as_unit[1].as_uint_single,
            port_uint_single_t, "%X");
}

TEST(port_memory_write_private_float16)
{
    port_memory_unit_t memory[2];

    port_memory_write_private_float16(memory, 1.0f, 0);
    port_memory_write_private_float16(memory, 0.5f, 1);
    port_memory_write_private_float16(memory, PORT_M_NAN, 2);
    port_memory_write_private_float16(memory, PORT_M_INFINITY, 3);

    ASSERT_EQ(memory[0].PORT_MEMORY_UNIT__AS_FLOAT_HALF[0], port_convert_float32_to_float16(1.0f), port_float32_t, "%g");
    ASSERT_EQ(memory[0].PORT_MEMORY_UNIT__AS_FLOAT_HALF[1], port_convert_float32_to_float16(0.5f), port_float32_t, "%g");
    ASSERT_EQ(memory[1].PORT_MEMORY_UNIT__AS_FLOAT_HALF[0], port_convert_float32_to_float16(PORT_M_NAN), port_float32_t, "%g");
    ASSERT_EQ(memory[1].PORT_MEMORY_UNIT__AS_FLOAT_HALF[1], port_convert_float32_to_float16(PORT_M_INFINITY), port_float32_t, "%g");
}

TEST(port_memory_write_private_float32)
{
    port_memory_unit_t memory[2];

    port_memory_write_private_float32(memory, 1.5f, 0);
    port_memory_write_private_float32(memory, 10.0f, 1);

    ASSERT_EQ(memory[0].as_float_single, 1.5f, port_float32_t, "%g");
    ASSERT_EQ(memory[1].as_float_single, 10.0f, port_float32_t, "%g");
}

TEST(port_memory_write_private_float64)
{
    port_memory_unit_t memory[4];

    port_memory_unit_double_t double_units[2] = {{.as_float_double = 1.5625},
        {.as_float_double = 1234.5}};

    port_memory_write_private_float64(memory, double_units[0].as_float_double, 0);
    port_memory_write_private_float64(memory, double_units[1].as_float_double, 1);

    ASSERT_EQ(memory[0].as_uint_single, double_units[0].as_unit[0].as_uint_single,
            port_uint_single_t, "%X");
    ASSERT_EQ(memory[1].as_uint_single, double_units[0].as_unit[1].as_uint_single,
            port_uint_single_t, "%X");
    ASSERT_EQ(memory[2].as_uint_single, double_units[1].as_unit[0].as_uint_single,
            port_uint_single_t, "%X");
    ASSERT_EQ(memory[3].as_uint_single, double_units[1].as_unit[1].as_uint_single,
            port_uint_single_t, "%X");
}

TEST(port_memory_write_private_memory_ref_quarter)
{
    port_memory_unit_t memory[2];

    port_memory_write_private_memory_ref_quarter(memory, 0x00, 0);
    port_memory_write_private_memory_ref_quarter(memory, 0x10, 1);
    port_memory_write_private_memory_ref_quarter(memory, 0x55, 2);
    port_memory_write_private_memory_ref_quarter(memory, 0x7F, 3);
    port_memory_write_private_memory_ref_quarter(memory, -1, 4);
    port_memory_write_private_memory_ref_quarter(memory, -63, 5);
    port_memory_write_private_memory_ref_quarter(memory, -64, 6);
    port_memory_write_private_memory_ref_quarter(memory, -128, 7);

    ASSERT_EQ(memory[0].as_ref_quarter[0], 0x00, port_memory_ref_quarter_t, "%X");
    ASSERT_EQ(memory[0].as_ref_quarter[1], 0x10, port_memory_ref_quarter_t, "%X");
    ASSERT_EQ(memory[0].as_ref_quarter[2], 0x55, port_memory_ref_quarter_t, "%X");
    ASSERT_EQ(memory[0].as_ref_quarter[3], 0x7F, port_memory_ref_quarter_t, "%X");
    ASSERT_EQ(memory[1].as_ref_quarter[0], -1, port_memory_ref_quarter_t, "%X");
    ASSERT_EQ(memory[1].as_ref_quarter[1], -63, port_memory_ref_quarter_t, "%X");
    ASSERT_EQ(memory[1].as_ref_quarter[2], -64, port_memory_ref_quarter_t, "%X");
    ASSERT_EQ(memory[1].as_ref_quarter[3], -128, port_memory_ref_quarter_t, "%X");
}

TEST(port_memory_write_private_memory_ref_half)
{
    port_memory_unit_t memory[2];

    port_memory_write_private_memory_ref_half(memory, 0x0000, 0);
    port_memory_write_private_memory_ref_half(memory, 0x7FFF, 1);
    port_memory_write_private_memory_ref_half(memory, -1, 2);
    port_memory_write_private_memory_ref_half(memory, -32768, 3);

    ASSERT_EQ(memory[0].as_ref_half[0], 0x0000, port_memory_ref_half_t, "%X");
    ASSERT_EQ(memory[0].as_ref_half[1], 0x7FFF, port_memory_ref_half_t, "%X");
    ASSERT_EQ(memory[1].as_ref_half[0], -1, port_memory_ref_half_t, "%X");
    ASSERT_EQ(memory[1].as_ref_half[1], -32768, port_memory_ref_half_t, "%X");
}

TEST(port_memory_write_private_memory_ref)
{
    port_memory_unit_t memory[3];

    port_memory_write_private_memory_ref(memory, 0, 0);
    port_memory_write_private_memory_ref(memory, 0x7FFFFFFF, 1);
    port_memory_write_private_memory_ref(memory, -1, 2);

    ASSERT_EQ(memory[0].as_ref, 0, port_memory_ref_t, "%X");
    ASSERT_EQ(memory[1].as_ref, 0x7FFFFFFF, port_memory_ref_t, "%X");
    ASSERT_EQ(memory[2].as_ref, -1, port_memory_ref_t, "%X");
}

TEST(port_memory_write_private_uint8_v16)
{
    port_memory_unit_t memory[5];

    port_uint8_v16_t vector;
    for (port_uint8_t i = 0; i < 16; i++)
        vector.s[i] = 100 + i;

    for (port_uint8_t offset = 0; offset <= 4; offset++)
    {
        port_memory_write_private_uint8_v16(memory, vector, offset);

        for (port_uint8_t i = 0; i < 16; i++)
            ASSERT_EQ(memory[(offset + i) / 4].as_uint_quarter[(offset + i) % 4], 100 + i,
                    port_uint8_t, "%u");
    }
}

TEST(port_memory_write_private_uint16_v8)
{
    port_memory_unit_t memory[5];

    port_uint16_v8_t vector;
    for (port_uint8_t i = 0; i < 8; i++)
        vector.s[i] = 32760 + i;

    for (port_uint8_t offset = 0; offset <= 2; offset++)
    {
        port_memory_write_private_uint16_v8(memory, vector, offset);

        for (port_uint8_t i = 0; i < 8; i++)
            ASSERT_EQ(memory[(offset + i) / 2].as_uint_half[(offset + i) % 2], 32760 + i,
                    port_uint16_t, "%u");
    }
}

TEST(port_memory_write_private_uint32_v4)
{
    port_memory_unit_t memory[5];

    port_uint32_v4_t vector;
    for (port_uint8_t i = 0; i < 4; i++)
        vector.s[i] = i + 0xFFFFFFFD;

    for (port_uint8_t offset = 0; offset <= 1; offset++)
    {
        port_memory_write_private_uint32_v4(memory, vector, offset);

        for (port_uint8_t i = 0; i < 4; i++)
            ASSERT_EQ(memory[offset + i].as_uint_single, 0xFFFFFFFD + i, port_uint32_t, "%X");
    }
}

TEST(port_memory_write_private_uint64_v2)
{
    port_memory_unit_t memory[8];

    port_uint64_v2_t vector = PORT_V2(0x00105568AABCEDFFull, 0xFEEDDEADABBAACABull);

    for (port_uint8_t offset = 0; offset <= 2; offset++)
    {
        port_memory_write_private_uint64_v2(memory, vector, offset);

        for (port_uint8_t i = 0; i < 2; i++)
        {
            port_memory_unit_double_t u = {.as_uint_double = vector.s[i]};
            ASSERT_EQ(memory[(offset + i)*2 + 0].as_uint_single, u.as_unit[0].as_uint_single,
                    port_uint_single_t, "%X");
            ASSERT_EQ(memory[(offset + i)*2 + 1].as_uint_single, u.as_unit[1].as_uint_single,
                    port_uint_single_t, "%X");
        }
    }
}

TEST(port_memory_write_private_float16_v4)
{
    port_memory_unit_t memory[3];

    port_float32_v4_t vector;
    for (port_uint8_t i = 0; i < 4; i++)
        vector.s[i] = i*3.0f - 1.0f;

    for (port_uint8_t offset = 0; offset <= 2; offset++)
    {
        port_memory_write_private_float16_v4(memory, vector, offset);

        for (port_uint8_t i = 0; i < 4; i++)
            ASSERT_EQ(memory[(offset + i) / 2].PORT_MEMORY_UNIT__AS_FLOAT_HALF[(offset + i) % 2],
                    port_convert_float32_to_float16(i*3.0f - 1.0f), port_float32_t, "%g");
    }
}

TEST(port_memory_write_private_float32_v4)
{
    port_memory_unit_t memory[5];

    port_float32_v4_t vector;
    for (port_uint8_t i = 0; i < 4; i++)
        vector.s[i] = i*3.0f - 1.0f;

    for (port_uint8_t offset = 0; offset <= 1; offset++)
    {
        port_memory_write_private_float32_v4(memory, vector, offset);

        for (port_uint8_t i = 0; i < 4; i++)
            ASSERT_EQ(memory[offset + i].as_float_single, i*3.0f - 1.0f, port_float32_t, "%g");
    }
}

TEST(port_memory_write_private_float64_v2)
{
    port_memory_unit_t memory[8];

    port_float64_v2_t vector = PORT_V2(1.3625, -PORT_M_INFINITY);

    for (port_uint8_t offset = 0; offset <= 2; offset++)
    {
        port_memory_write_private_float64_v2(memory, vector, offset);

        for (port_uint8_t i = 0; i < 2; i++)
        {
            port_memory_unit_double_t u = {.as_float_double = vector.s[i]};
            ASSERT_EQ(memory[(offset + i)*2 + 0].as_uint_single, u.as_unit[0].as_uint_single,
                    port_uint_single_t, "%X");
            ASSERT_EQ(memory[(offset + i)*2 + 1].as_uint_single, u.as_unit[1].as_uint_single,
                    port_uint_single_t, "%X");
        }
    }
}

