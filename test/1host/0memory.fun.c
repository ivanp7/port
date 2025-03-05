#include "test.h"

#include "port/host/memory.fun.h"
#include "port/host/memory.typ.h"

struct memory_operation_properties {
    port_size_t bytes_mapped;

    port_size_t num_mapped;
    port_size_t num_unmapped;
};

static port_bool_t map_func(
        port_void_ptr_t memory,
        port_size_t num_bytes,
        port_void_ptr_t properties)
{
    (void) memory;

    struct memory_operation_properties *prop = properties;

    prop->bytes_mapped += num_bytes;
    prop->num_mapped++;

    return true;
}

static port_bool_t unmap_func(
        port_void_ptr_t memory,
        port_void_ptr_t properties)
{
    (void) memory;

    struct memory_operation_properties *prop = properties;

    prop->num_unmapped++;

    return true;
}

#define MEMORY_ALLOCATOR(name, prop) port_memory_allocator_t name = { \
    .operations = {.map_fn = map_func, .unmap_fn = unmap_func}, \
    .properties = {.map = &prop}, \
}

///////////////////////////////////////////////////////////////////////////////

TEST(port_memory_map_copy_unmap)
{
    struct memory_operation_properties prop_dest = {0}, prop_src = {0};
    MEMORY_ALLOCATOR(ma_dest, prop_dest);
    MEMORY_ALLOCATOR(ma_src, prop_src);

    char src[128], dest[128];
    for (port_size_t i = 0; i < 128; i++)
        src[i] = (i * i + 1) % 256;

    ASSERT_TRUE(port_memory_map_copy_unmap(dest, src, 0, &ma_dest, &ma_src));
    ASSERT_TRUE(port_memory_map_copy_unmap(dest, src, 128, &ma_dest, &ma_src));

    ASSERT_EQ(prop_dest.bytes_mapped, 128, unsigned, "%u");
    ASSERT_EQ(prop_dest.num_mapped, 1, unsigned, "%u");
    ASSERT_EQ(prop_dest.num_unmapped, 1, unsigned, "%u");

    ASSERT_EQ(prop_src.bytes_mapped, 128, unsigned, "%u");
    ASSERT_EQ(prop_src.num_mapped, 1, unsigned, "%u");
    ASSERT_EQ(prop_src.num_unmapped, 1, unsigned, "%u");

    for (port_size_t i = 0; i < 128; i++)
        ASSERT_EQ(dest[i], src[i], unsigned, "%u");
}

