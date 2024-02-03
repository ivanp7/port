#include <test.h>

#include <port/cdev/memory.fun.h>
#include <port/cdev/memory.def.h>

#define NUM_BITS 16
#define NUM_UNITS (1 << NUM_BITS)

typedef void (*memcpy_fn)(port_memory_ptr_t restrict,
        port_const_memory_ptr_t restrict,
        port_size_t);

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

TEST(PORT_MEMORY_REF_NUM_IDXLEN_BITS)
{
    ASSERT_EQ(PORT_MEMORY_REF_NUM_IDXLEN_BITS(port_memory_ref_quarter_t), 3, port_uint32_t, "%u");
    ASSERT_EQ(PORT_MEMORY_REF_NUM_IDXLEN_BITS(port_memory_ref_half_t), 4, port_uint32_t, "%u");
    ASSERT_EQ(PORT_MEMORY_REF_NUM_IDXLEN_BITS(port_memory_ref_t), 5, port_uint32_t, "%u");
}

TEST(PORT_MEMORY_REF_FAR)
{
    ASSERT_EQ(PORT_MEMORY_REF_FAR(port_memory_ref_t, 13, 7331, 1337), 0xA73CA3, port_uint_single_t, "%X");
}

TEST(PORT_MEMORY_REF_FAR_PARSE)
{
    port_uint_single_t idx = 0, offset = 0;
    PORT_MEMORY_REF_FAR_PARSE(0xA73CA3, port_memory_ref_t, 13, &idx, &offset);
    ASSERT_EQ(idx, 7331, port_uint_single_t, "%u");
    ASSERT_EQ(offset, 1337, port_uint_single_t, "%u");
}

TEST(port_memory_reference)
{
    port_memory_unit_t unit0 = {0};
    port_memory_unit_t unit1 = {0};
    port_memory_unit_t unit2 = {0};
    port_const_memory_ptr_t memory_table[3] = {&unit0, &unit1, &unit2};

    port_memory_ref_t ref;
    port_const_memory_ptr_t ptr;

    ref = -1;
    ptr = port_memory_reference(ref, 0, 0, &unit2, memory_table);
    ASSERT_EQ(ptr - &unit2, 1, port_ptrdiff_t, "%ti");

    ref = -10;
    ptr = port_memory_reference(ref, 10, 20, (port_const_memory_ptr_t)NULL, memory_table);
    ASSERT_EQ(ptr - &unit0, 10, port_ptrdiff_t, "%ti");

    port_uint8_t num_idx_bits = 2;
    port_uint8_t offset_shift = 8;

    ref = PORT_MEMORY_REF_FAR(port_memory_ref_t, num_idx_bits, 0, 0);
    ptr = port_memory_reference(ref, num_idx_bits, offset_shift, (port_const_memory_ptr_t)NULL, memory_table);
    ASSERT_EQ(ptr - &unit0, 0, port_ptrdiff_t, "%ti");

    ref = PORT_MEMORY_REF_FAR(port_memory_ref_t, num_idx_bits, 1, 10);
    ptr = port_memory_reference(ref, num_idx_bits, offset_shift, (port_const_memory_ptr_t)NULL, memory_table + 1);
    ASSERT_EQ(ptr - &unit2, 10 << offset_shift, port_ptrdiff_t, "%ti");

    ref = PORT_MEMORY_REF_FAR(port_memory_ref_t, num_idx_bits, 0, 5);
    ptr = port_memory_reference(ref, num_idx_bits, offset_shift, (port_const_memory_ptr_t)NULL, memory_table + 2);
    ASSERT_EQ(ptr - &unit2, 5 << offset_shift, port_ptrdiff_t, "%ti");
}

TEST(port_memcpy_global_to_private)
{
    ASSERT_TRUE(test_memcpy(port_memcpy_global_to_private));
}

TEST(port_memcpy_constant_to_private)
{
    ASSERT_TRUE(test_memcpy(port_memcpy_constant_to_private));
}

TEST(port_memcpy_local_to_private)
{
    ASSERT_TRUE(test_memcpy(port_memcpy_local_to_private));
}

TEST(port_memcpy_private_to_private)
{
    ASSERT_TRUE(test_memcpy(port_memcpy_private_to_private));
}

TEST(port_memcpy_global_to_local)
{
    ASSERT_TRUE(test_memcpy(port_memcpy_global_to_local));
}

TEST(port_memcpy_constant_to_local)
{
    ASSERT_TRUE(test_memcpy(port_memcpy_constant_to_local));
}

TEST(port_memcpy_local_to_local)
{
    ASSERT_TRUE(test_memcpy(port_memcpy_local_to_local));
}

TEST(port_memcpy_private_to_local)
{
    ASSERT_TRUE(test_memcpy(port_memcpy_private_to_local));
}

TEST(port_memcpy_global_to_global)
{
    ASSERT_TRUE(test_memcpy(port_memcpy_global_to_global));
}

TEST(port_memcpy_local_to_global)
{
    ASSERT_TRUE(test_memcpy(port_memcpy_local_to_global));
}

TEST(port_memcpy_constant_to_global)
{
    ASSERT_TRUE(test_memcpy(port_memcpy_constant_to_global));
}

TEST(port_memcpy_private_to_global)
{
    ASSERT_TRUE(test_memcpy(port_memcpy_private_to_global));
}

TEST(port_memread_uint64)
{
    port_uint64_t value = 0x11223344AABBCCDDull;
    port_memory_unit_double_t units = {.as_uint_double = value};

    port_uint64_t result = port_memread_uint64(units.as_units);

    ASSERT_EQ(result, value, port_uint64_t, "%lX");
}

TEST(port_memread_sint64)
{
    port_sint64_t value = -0x11223344AABBCCDDll;
    port_memory_unit_double_t units = {.as_sint_double = value};

    port_sint64_t result = port_memread_sint64(units.as_units);

    ASSERT_EQ(result, value, port_sint64_t, "%lX");
}

TEST(port_memwrite_uint64)
{
    port_uint64_t value = 0x11223344AABBCCDDull;
    port_memory_unit_double_t units = {.as_uint_double = 0};

    port_memwrite_uint64(units.as_units, value);

    ASSERT_EQ(units.as_uint_double, value, port_uint64_t, "%lX");
}

TEST(port_memwrite_sint64)
{
    port_sint64_t value = -0x11223344AABBCCDDull;
    port_memory_unit_double_t units = {.as_sint_double = 0};

    port_memwrite_sint64(units.as_units, value);

    ASSERT_EQ(units.as_sint_double, value, port_sint64_t, "%lX");
}

TEST(port_memread_uint)
{
    port_uint_t value = 0x11223344;
#ifdef PORT_FEATURE_DEFAULT_INTEGER_64
    value <<= 16;
#endif

    port_const_memory_ptr_t mem;
#ifndef PORT_FEATURE_DEFAULT_INTEGER_64
    port_memory_unit_t unit = {.as_uint_single = value};
    mem = &unit;
#else
    port_memory_unit_double_t units = {.as_uint_double = value};
    mem = units.as_units;
#endif

    port_uint_t result = port_memread_uint(mem);

#ifndef PORT_FEATURE_DEFAULT_INTEGER_64
    ASSERT_EQ(result, value, port_uint_t, "%X");
#else
    ASSERT_EQ(result, value, port_uint_t, "%lX");
#endif
}

TEST(port_memread_sint)
{
    port_sint_t value = -0x11223344;
#ifdef PORT_FEATURE_DEFAULT_INTEGER_64
    value <<= 16;
#endif

    port_const_memory_ptr_t mem;
#ifndef PORT_FEATURE_DEFAULT_INTEGER_64
    port_memory_unit_t unit = {.as_sint_single = value};
    mem = &unit;
#else
    port_memory_unit_double_t units = {.as_sint_double = value};
    mem = units.as_units;
#endif

    port_sint_t result = port_memread_sint(mem);

#ifndef PORT_FEATURE_DEFAULT_INTEGER_64
    ASSERT_EQ(result, value, port_sint_t, "%X");
#else
    ASSERT_EQ(result, value, port_sint_t, "%lX");
#endif
}

TEST(port_memwrite_uint)
{
    port_uint_t value = 0x11223344;
#ifdef PORT_FEATURE_DEFAULT_INTEGER_64
    value <<= 16;
#endif

    port_memory_ptr_t mem;
#ifndef PORT_FEATURE_DEFAULT_INTEGER_64
    port_memory_unit_t unit = {.as_uint_single = 0};
    mem = &unit;
#else
    port_memory_unit_double_t units = {.as_uint_double = 0};
    mem = units.as_units;
#endif

    port_memwrite_uint(mem, value);

#ifndef PORT_FEATURE_DEFAULT_INTEGER_64
    ASSERT_EQ(unit.as_uint_single, value, port_uint_t, "%X");
#else
    ASSERT_EQ(units.as_uint_double, value, port_uint_t, "%lX");
#endif
}

TEST(port_memwrite_sint)
{
    port_sint_t value = -0x11223344;
#ifdef PORT_FEATURE_DEFAULT_INTEGER_64
    value <<= 16;
#endif

    port_memory_ptr_t mem;
#ifndef PORT_FEATURE_DEFAULT_INTEGER_64
    port_memory_unit_t unit = {.as_sint_single = 0};
    mem = &unit;
#else
    port_memory_unit_double_t units = {.as_sint_double = 0};
    mem = units.as_units;
#endif

    port_memwrite_sint(mem, value);

#ifndef PORT_FEATURE_DEFAULT_INTEGER_64
    ASSERT_EQ(unit.as_sint_single, value, port_sint_t, "%X");
#else
    ASSERT_EQ(units.as_sint_double, value, port_sint_t, "%lX");
#endif
}

TEST(port_memread_float64)
{
    port_float64_t value = 12.34e5;
    port_memory_unit_double_t units = {.as_float_double = value};

    port_float64_t result = port_memread_float64(units.as_units);

    ASSERT_EQ(result, value, port_float64_t, "%g");
}

TEST(port_memwrite_float64)
{
    port_float64_t value = 12.34e5;
    port_memory_unit_double_t units = {.as_float_double = 0.0};

    port_memwrite_float64(units.as_units, value);

    ASSERT_EQ(units.as_float_double, value, port_float64_t, "%g");
}

TEST(port_memread_float)
{
    port_float_t value = 12.34e5;

    port_const_memory_ptr_t mem;
#ifndef PORT_FEATURE_DEFAULT_FLOAT_64
    port_memory_unit_t unit = {.as_float_single = value};
    mem = &unit;
#else
    port_memory_unit_double_t units = {.as_float_double = value};
    mem = units.as_units;
#endif

    port_float_t result = port_memread_float(mem);

    ASSERT_EQ(result, value, port_float_t, "%g");
}

TEST(port_memwrite_float)
{
    port_float_t value = 12.34e5;

    port_memory_ptr_t mem;
#ifndef PORT_FEATURE_DEFAULT_FLOAT_64
    port_memory_unit_t unit = {.as_float_single = 0.0};
    mem = &unit;
#else
    port_memory_unit_double_t units = {.as_float_double = 0.0};
    mem = units.as_units;
#endif

    port_memwrite_float(mem, value);

#ifndef PORT_FEATURE_DEFAULT_FLOAT_64
    ASSERT_EQ(unit.as_float_single, value, port_float_t, "%g");
#else
    ASSERT_EQ(units.as_float_double, value, port_float_t, "%g");
#endif
}

