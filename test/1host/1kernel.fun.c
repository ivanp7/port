#include "test.h"

#include "port/host/kernel.fun.h"
#include "port/host/kernel.typ.h"
#include "port/host/memory.typ.h"
#include "port/host/memory.def.h"
#include "port/host/storage.typ.h"

#include <stdalign.h>

struct memory_operation_properties {
    alignas(PORT_ALIGNMENT_MAX) char memory[10240];
    port_size_t offset;

    port_size_t bytes_allocd;
    port_size_t bytes_mapped;

    port_size_t num_allocd;
    port_size_t num_freed;

    port_size_t num_mapped;
    port_size_t num_unmapped;
};

static port_void_ptr_t alloc_func(
        port_size_t num_bytes,
        port_size_t alignment,
        port_void_ptr_t properties)
{
    struct memory_operation_properties *prop = properties;

    if (alignment == 0)
        alignment = PORT_ALIGNMENT_MAX;

    prop->offset = (prop->offset + (alignment - 1)) & ~(alignment - 1);
    port_void_ptr_t ptr = prop->memory + prop->offset;

    prop->offset += num_bytes;
    prop->bytes_allocd += num_bytes;
    prop->num_allocd++;

    return ptr;
}

static void free_func(
        port_void_ptr_t memory,
        port_void_ptr_t properties)
{
    (void) memory;

    struct memory_operation_properties *prop = properties;

    prop->num_freed++;
}

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
    .operations = {.alloc_fn = alloc_func, .free_fn = free_func, .map_fn = map_func, .unmap_fn = unmap_func}, \
    .properties = {.alloc = &prop, .map = &prop}, \
}

///////////////////////////////////////////////////////////////////////////////

#define LEN 10
#define LEN2 (LEN/2)

TEST(port_kargs_alloc_copy_cstate_sizes)
{
    struct memory_operation_properties prop_host = {0};
    MEMORY_ALLOCATOR(ma_host, prop_host);

    port_size_t sizes_mem[LEN];
    for (port_size_t i = 0; i < LEN; i++)
        sizes_mem[i] = i;

    port_kargs_cstate_sizes_t sizes_src = {.sizes = sizes_mem, .num_of = LEN}, sizes_dest = {0};

    ASSERT_TRUE(port_kargs_alloc_copy_cstate_sizes(&sizes_dest, &sizes_src, &ma_host));

    ASSERT_EQ(prop_host.bytes_allocd, sizeof(port_size_t) * LEN, unsigned, "%u");
    ASSERT_EQ(prop_host.bytes_mapped, 0, unsigned, "%u");

    ASSERT_EQ(prop_host.num_allocd, 1, unsigned, "%u");
    ASSERT_EQ(prop_host.num_freed, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_mapped, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_unmapped, 0, unsigned, "%u");

    ASSERT_EQ(sizes_dest.num_of, LEN, unsigned, "%u");
    ASSERT_NE(sizes_dest.sizes, NULL, port_void_ptr_t, "%p");
    for (port_size_t i = 0; i < LEN; i++)
        ASSERT_EQ(sizes_dest.sizes[i], sizes_src.sizes[i], unsigned, "%u");

    prop_host = (struct memory_operation_properties){0};
    sizes_src.num_of = 0;

    ASSERT_TRUE(port_kargs_alloc_copy_cstate_sizes(&sizes_dest, &sizes_src, &ma_host));

    ASSERT_EQ(prop_host.bytes_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.bytes_mapped, 0, unsigned, "%u");

    ASSERT_EQ(prop_host.num_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_freed, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_mapped, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_unmapped, 0, unsigned, "%u");

    ASSERT_EQ(sizes_dest.num_of, 0, unsigned, "%u");
    ASSERT_EQ(sizes_dest.sizes, NULL, port_void_ptr_t, "%p");
}

TEST(port_kargs_free_cstate_sizes)
{
    struct memory_operation_properties prop_host = {0};
    MEMORY_ALLOCATOR(ma_host, prop_host);

    port_kargs_cstate_sizes_t sizes = {.sizes = (port_void_ptr_t)-1, .num_of = LEN};

    port_kargs_free_cstate_sizes(&sizes, &ma_host);

    ASSERT_EQ(prop_host.bytes_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.bytes_mapped, 0, unsigned, "%u");

    ASSERT_EQ(prop_host.num_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_freed, 1, unsigned, "%u");
    ASSERT_EQ(prop_host.num_mapped, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_unmapped, 0, unsigned, "%u");

    ASSERT_EQ(sizes.num_of, 0, unsigned, "%u");
    ASSERT_EQ(sizes.sizes, NULL, port_void_ptr_t, "%p");
}

TEST(port_kargs_alloc_cstate_arrays)
{
    struct memory_operation_properties prop_host = {0};
    MEMORY_ALLOCATOR(ma_host, prop_host);

    port_kargs_cstate_sizes_t sizes = {.num_of = LEN};
    port_kargs_cstate_ptrs_t ptrs = {0};

    ASSERT_TRUE(port_kargs_alloc_cstate_arrays(&ptrs, &sizes, &ma_host));

    ASSERT_EQ(prop_host.bytes_allocd, sizeof(port_void_ptr_t) * LEN, unsigned, "%u");
    ASSERT_EQ(prop_host.bytes_mapped, 0, unsigned, "%u");

    ASSERT_EQ(prop_host.num_allocd, 1, unsigned, "%u");
    ASSERT_EQ(prop_host.num_freed, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_mapped, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_unmapped, 0, unsigned, "%u");

    ASSERT_NE(ptrs.arrays, NULL, port_void_ptr_t, "%p");

    prop_host = (struct memory_operation_properties){0};
    sizes.num_of = 0;

    ASSERT_TRUE(port_kargs_alloc_cstate_arrays(&ptrs, &sizes, &ma_host));

    ASSERT_EQ(prop_host.bytes_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.bytes_mapped, 0, unsigned, "%u");

    ASSERT_EQ(prop_host.num_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_freed, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_mapped, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_unmapped, 0, unsigned, "%u");

    ASSERT_EQ(ptrs.arrays, NULL, port_void_ptr_t, "%p");
}

TEST(port_kargs_free_cstate_arrays)
{
    struct memory_operation_properties prop_host = {0};
    MEMORY_ALLOCATOR(ma_host, prop_host);

    port_kargs_cstate_sizes_t sizes = {.num_of = LEN};
    port_kargs_cstate_ptrs_t ptrs = {.arrays = (port_void_ptr_t)-1};

    port_kargs_free_cstate_arrays(&ptrs, &sizes, &ma_host);

    ASSERT_EQ(prop_host.bytes_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.bytes_mapped, 0, unsigned, "%u");

    ASSERT_EQ(prop_host.num_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_freed, 1, unsigned, "%u");
    ASSERT_EQ(prop_host.num_mapped, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_unmapped, 0, unsigned, "%u");

    ASSERT_EQ(ptrs.arrays, NULL, port_void_ptr_t, "%p");
}

TEST(port_kargs_alloc_cstate_memory)
{
    struct memory_operation_properties prop_cdev = {0};
    MEMORY_ALLOCATOR(ma_cdev, prop_cdev);

    port_void_ptr_t ptrs_mem[LEN] = {0};

    port_size_t sizes_mem[LEN];
    for (port_size_t i = 0; i < LEN; i++)
        sizes_mem[i] = i;

    port_kargs_cstate_sizes_t sizes = {.sizes = sizes_mem, .num_of = LEN};
    port_kargs_cstate_ptrs_t ptrs = {.arrays = ptrs_mem};

    ASSERT_TRUE(port_kargs_alloc_cstate_memory(&ptrs, &sizes, &ma_cdev));

    ASSERT_EQ(prop_cdev.bytes_allocd, LEN * (LEN - 1) / 2, unsigned, "%u");
    ASSERT_EQ(prop_cdev.bytes_mapped, 0, unsigned, "%u");

    ASSERT_EQ(prop_cdev.num_allocd, LEN - 1, unsigned, "%u");
    ASSERT_EQ(prop_cdev.num_freed, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev.num_mapped, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev.num_unmapped, 0, unsigned, "%u");

    ASSERT_EQ(ptrs.arrays[0], NULL, port_void_ptr_t, "%p");
    for (port_size_t i = 1; i < LEN; i++)
        ASSERT_NE(ptrs.arrays[i], NULL, port_void_ptr_t, "%p");
}

TEST(port_kargs_free_cstate_memory)
{
    struct memory_operation_properties prop_cdev = {0};
    MEMORY_ALLOCATOR(ma_cdev, prop_cdev);

    port_void_ptr_t ptrs_mem[LEN] = {0};
    for (port_size_t i = 0; i < LEN; i++)
        ptrs_mem[i] = (port_void_ptr_t)-1;

    port_kargs_cstate_sizes_t sizes = {.num_of = LEN};
    port_kargs_cstate_ptrs_t ptrs = {.arrays = ptrs_mem};

    port_kargs_free_cstate_memory(&ptrs, &sizes, &ma_cdev);

    ASSERT_EQ(prop_cdev.bytes_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev.bytes_mapped, 0, unsigned, "%u");

    ASSERT_EQ(prop_cdev.num_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev.num_freed, LEN, unsigned, "%u");
    ASSERT_EQ(prop_cdev.num_mapped, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev.num_unmapped, 0, unsigned, "%u");

    for (port_size_t i = 0; i < LEN; i++)
        ASSERT_EQ(ptrs.arrays[i], NULL, port_void_ptr_t, "%p");
}

TEST(port_kargs_copy_cstate_memory)
{
    struct memory_operation_properties prop_cdev_dest = {0}, prop_cdev_src = {0};
    MEMORY_ALLOCATOR(ma_cdev_dest, prop_cdev_dest);
    MEMORY_ALLOCATOR(ma_cdev_src, prop_cdev_src);

    port_uint32_t mem_dest[4] = {0}, mem_src[4] = {0xDEAD, 0xBEEF, 0xABBA, 0x1337};

    port_size_t sizes_mem[4];
    for (port_size_t i = 0; i < 4; i++)
        sizes_mem[i] = sizeof(port_uint32_t);

    port_void_ptr_t ptrs_dest_mem[4] = {0}, ptrs_src_mem[4] = {0};
    ptrs_src_mem[1] = &mem_src[1];
    ptrs_dest_mem[2] = &mem_dest[2];
    ptrs_src_mem[3] = &mem_src[3];
    ptrs_dest_mem[3] = &mem_dest[3];

    port_kargs_cstate_sizes_t sizes = {.sizes = sizes_mem, .num_of = 4};
    port_kargs_cstate_ptrs_t ptrs_dest = {.arrays = ptrs_dest_mem},
                             ptrs_src = {.arrays = ptrs_src_mem};

    ASSERT_TRUE(port_kargs_copy_cstate_memory(&ptrs_dest, &ptrs_src, &sizes, &ma_cdev_dest, &ma_cdev_src));

    ASSERT_EQ(prop_cdev_dest.bytes_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev_dest.bytes_mapped, 4, unsigned, "%u");

    ASSERT_EQ(prop_cdev_dest.num_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev_dest.num_freed, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev_dest.num_mapped, 1, unsigned, "%u");
    ASSERT_EQ(prop_cdev_dest.num_unmapped, 1, unsigned, "%u");

    ASSERT_EQ(prop_cdev_src.bytes_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev_src.bytes_mapped, 4, unsigned, "%u");

    ASSERT_EQ(prop_cdev_src.num_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev_src.num_freed, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev_src.num_mapped, 1, unsigned, "%u");
    ASSERT_EQ(prop_cdev_src.num_unmapped, 1, unsigned, "%u");

    ASSERT_EQ(mem_dest[0], 0, unsigned, "%u");
    ASSERT_EQ(mem_dest[1], 0, unsigned, "%u");
    ASSERT_EQ(mem_dest[2], 0, unsigned, "%u");
    ASSERT_EQ(mem_dest[3], mem_src[3], unsigned, "%u");
}

///////////////////////////////////////////////////////////////////////////////

TEST(port_kargs_alloc_copy_cparam_sizes)
{
    struct memory_operation_properties prop_host = {0};
    MEMORY_ALLOCATOR(ma_host, prop_host);

    port_size_t str_sizes_mem[LEN], arr_sizes_mem[LEN2];
    for (port_size_t i = 0; i < LEN; i++)
    {
        str_sizes_mem[i] = i;
        if (i < LEN2)
            arr_sizes_mem[i] = i;
    }

    port_kargs_cparam_sizes_t sizes_src = {.structures = {.sizes = str_sizes_mem, .num_of = LEN},
        .arrays = {.sizes = arr_sizes_mem, .num_of = LEN2}}, sizes_dest = {0};

    ASSERT_TRUE(port_kargs_alloc_copy_cparam_sizes(&sizes_dest, &sizes_src, &ma_host));

    ASSERT_EQ(prop_host.bytes_allocd, sizeof(port_size_t) * (LEN + LEN2), unsigned, "%u");
    ASSERT_EQ(prop_host.bytes_mapped, 0, unsigned, "%u");

    ASSERT_EQ(prop_host.num_allocd, 2, unsigned, "%u");
    ASSERT_EQ(prop_host.num_freed, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_mapped, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_unmapped, 0, unsigned, "%u");

    ASSERT_EQ(sizes_dest.structures.num_of, LEN, unsigned, "%u");
    ASSERT_NE(sizes_dest.structures.sizes, NULL, port_void_ptr_t, "%p");
    for (port_size_t i = 0; i < LEN; i++)
        ASSERT_EQ(sizes_dest.structures.sizes[i], sizes_src.structures.sizes[i], unsigned, "%u");

    ASSERT_EQ(sizes_dest.arrays.num_of, LEN2, unsigned, "%u");
    ASSERT_NE(sizes_dest.arrays.sizes, NULL, port_void_ptr_t, "%p");
    for (port_size_t i = 0; i < LEN2; i++)
        ASSERT_EQ(sizes_dest.arrays.sizes[i], sizes_src.arrays.sizes[i], unsigned, "%u");

    prop_host = (struct memory_operation_properties){0};
    sizes_src.structures.num_of = 0;
    sizes_src.arrays.num_of = 0;

    ASSERT_TRUE(port_kargs_alloc_copy_cparam_sizes(&sizes_dest, &sizes_src, &ma_host));

    ASSERT_EQ(prop_host.bytes_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.bytes_mapped, 0, unsigned, "%u");

    ASSERT_EQ(prop_host.num_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_freed, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_mapped, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_unmapped, 0, unsigned, "%u");

    ASSERT_EQ(sizes_dest.structures.num_of, 0, unsigned, "%u");
    ASSERT_EQ(sizes_dest.structures.sizes, NULL, port_void_ptr_t, "%p");

    ASSERT_EQ(sizes_dest.arrays.num_of, 0, unsigned, "%u");
    ASSERT_EQ(sizes_dest.arrays.sizes, NULL, port_void_ptr_t, "%p");
}

TEST(port_kargs_free_cparam_sizes)
{
    struct memory_operation_properties prop_host = {0};
    MEMORY_ALLOCATOR(ma_host, prop_host);

    port_kargs_cparam_sizes_t sizes = {
        .structures = {.sizes = (port_void_ptr_t)-1, .num_of = LEN},
        .arrays = {.sizes = (port_void_ptr_t)-1, .num_of = LEN2}};

    port_kargs_free_cparam_sizes(&sizes, &ma_host);

    ASSERT_EQ(prop_host.bytes_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.bytes_mapped, 0, unsigned, "%u");

    ASSERT_EQ(prop_host.num_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_freed, 2, unsigned, "%u");
    ASSERT_EQ(prop_host.num_mapped, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_unmapped, 0, unsigned, "%u");

    ASSERT_EQ(sizes.structures.num_of, 0, unsigned, "%u");
    ASSERT_EQ(sizes.structures.sizes, NULL, port_void_ptr_t, "%p");

    ASSERT_EQ(sizes.arrays.num_of, 0, unsigned, "%u");
    ASSERT_EQ(sizes.arrays.sizes, NULL, port_void_ptr_t, "%p");
}

TEST(port_kargs_alloc_cparam_arrays)
{
    struct memory_operation_properties prop_host = {0};
    MEMORY_ALLOCATOR(ma_host, prop_host);

    port_kargs_cparam_sizes_t sizes = {.structures = {.num_of = LEN}, .arrays = {.num_of = LEN2}};
    port_kargs_cparam_ptrs_t ptrs = {0};

    ASSERT_TRUE(port_kargs_alloc_cparam_arrays(&ptrs, &sizes, &ma_host));

    ASSERT_EQ(prop_host.bytes_allocd, sizeof(port_void_ptr_t) * (LEN + LEN2), unsigned, "%u");
    ASSERT_EQ(prop_host.bytes_mapped, 0, unsigned, "%u");

    ASSERT_EQ(prop_host.num_allocd, 2, unsigned, "%u");
    ASSERT_EQ(prop_host.num_freed, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_mapped, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_unmapped, 0, unsigned, "%u");

    ASSERT_NE(ptrs.structures, NULL, port_void_ptr_t, "%p");
    ASSERT_NE(ptrs.arrays, NULL, port_void_ptr_t, "%p");

    prop_host = (struct memory_operation_properties){0};
    sizes.structures.num_of = 0;
    sizes.arrays.num_of = 0;

    ASSERT_TRUE(port_kargs_alloc_cparam_arrays(&ptrs, &sizes, &ma_host));

    ASSERT_EQ(prop_host.bytes_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.bytes_mapped, 0, unsigned, "%u");

    ASSERT_EQ(prop_host.num_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_freed, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_mapped, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_unmapped, 0, unsigned, "%u");

    ASSERT_EQ(ptrs.structures, NULL, port_void_ptr_t, "%p");
    ASSERT_EQ(ptrs.arrays, NULL, port_void_ptr_t, "%p");
}

TEST(port_kargs_free_cparam_arrays)
{
    struct memory_operation_properties prop_host = {0};
    MEMORY_ALLOCATOR(ma_host, prop_host);

    port_kargs_cparam_sizes_t sizes = {.structures = {.num_of = LEN}, .arrays = {.num_of = LEN2}};
    port_kargs_cparam_ptrs_t ptrs = {.structures = (port_void_ptr_t)-1, .arrays = (port_void_ptr_t)-1};

    port_kargs_free_cparam_arrays(&ptrs, &sizes, &ma_host);

    ASSERT_EQ(prop_host.bytes_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.bytes_mapped, 0, unsigned, "%u");

    ASSERT_EQ(prop_host.num_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_freed, 2, unsigned, "%u");
    ASSERT_EQ(prop_host.num_mapped, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_unmapped, 0, unsigned, "%u");

    ASSERT_EQ(ptrs.structures, NULL, port_void_ptr_t, "%p");
    ASSERT_EQ(ptrs.arrays, NULL, port_void_ptr_t, "%p");
}

TEST(port_kargs_alloc_cparam_memory)
{
    struct memory_operation_properties prop_host = {0};
    MEMORY_ALLOCATOR(ma_host, prop_host);
    struct memory_operation_properties prop_cdev = {0};
    MEMORY_ALLOCATOR(ma_cdev, prop_cdev);

    port_void_ptr_t ptrs_str_mem[LEN] = {0}, ptrs_arr_mem[LEN2] = {0};

    port_size_t str_sizes_mem[LEN], arr_sizes_mem[LEN2];
    for (port_size_t i = 0; i < LEN; i++)
    {
        str_sizes_mem[i] = i;
        if (i < LEN2)
            arr_sizes_mem[i] = i;
    }

    port_kargs_cparam_sizes_t sizes = {.structures = {.sizes = str_sizes_mem, .num_of = LEN},
        .arrays = {.sizes = arr_sizes_mem, .num_of = LEN2}};
    port_kargs_cparam_ptrs_t ptrs = {.structures = ptrs_str_mem, .arrays = ptrs_arr_mem};

    ASSERT_TRUE(port_kargs_alloc_cparam_memory(&ptrs, &sizes, &ma_host, &ma_cdev));

    ASSERT_EQ(prop_host.bytes_allocd, LEN * (LEN - 1) / 2, unsigned, "%u");
    ASSERT_EQ(prop_host.bytes_mapped, 0, unsigned, "%u");

    ASSERT_EQ(prop_host.num_allocd, LEN - 1, unsigned, "%u");
    ASSERT_EQ(prop_host.num_freed, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_mapped, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_unmapped, 0, unsigned, "%u");

    ASSERT_EQ(prop_cdev.bytes_allocd, LEN2 * (LEN2 - 1) / 2, unsigned, "%u");
    ASSERT_EQ(prop_cdev.bytes_mapped, 0, unsigned, "%u");

    ASSERT_EQ(prop_cdev.num_allocd, LEN2 - 1, unsigned, "%u");
    ASSERT_EQ(prop_cdev.num_freed, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev.num_mapped, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev.num_unmapped, 0, unsigned, "%u");

    ASSERT_EQ(ptrs.structures[0], NULL, port_void_ptr_t, "%p");
    ASSERT_EQ(ptrs.arrays[0], NULL, port_void_ptr_t, "%p");
    for (port_size_t i = 1; i < LEN; i++)
    {
        ASSERT_NE(ptrs.structures[i], NULL, port_void_ptr_t, "%p");
        if (i < LEN2)
            ASSERT_NE(ptrs.arrays[i], NULL, port_void_ptr_t, "%p");
    }
}

TEST(port_kargs_free_cparam_memory)
{
    struct memory_operation_properties prop_host = {0};
    MEMORY_ALLOCATOR(ma_host, prop_host);
    struct memory_operation_properties prop_cdev = {0};
    MEMORY_ALLOCATOR(ma_cdev, prop_cdev);

    port_void_ptr_t ptrs_str_mem[LEN] = {0}, ptrs_arr_mem[LEN2] = {0};
    for (port_size_t i = 0; i < LEN; i++)
    {
        ptrs_str_mem[i] = (port_void_ptr_t)-1;
        if (i < LEN2)
            ptrs_arr_mem[i] = (port_void_ptr_t)-1;
    }

    port_kargs_cparam_sizes_t sizes = {.structures = {.num_of = LEN}, .arrays = {.num_of = LEN2}};
    port_kargs_cparam_ptrs_t ptrs = {.structures = ptrs_str_mem, .arrays = ptrs_arr_mem};

    port_kargs_free_cparam_memory(&ptrs, &sizes, &ma_host, &ma_cdev);

    ASSERT_EQ(prop_host.bytes_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.bytes_mapped, 0, unsigned, "%u");

    ASSERT_EQ(prop_host.num_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_freed, LEN, unsigned, "%u");
    ASSERT_EQ(prop_host.num_mapped, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_unmapped, 0, unsigned, "%u");

    ASSERT_EQ(prop_cdev.bytes_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev.bytes_mapped, 0, unsigned, "%u");

    ASSERT_EQ(prop_cdev.num_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev.num_freed, LEN2, unsigned, "%u");
    ASSERT_EQ(prop_cdev.num_mapped, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev.num_unmapped, 0, unsigned, "%u");

    for (port_size_t i = 0; i < LEN; i++)
    {
        ASSERT_EQ(ptrs.structures[i], NULL, port_void_ptr_t, "%p");
        if (i < LEN2)
            ASSERT_EQ(ptrs.arrays[i], NULL, port_void_ptr_t, "%p");
    }
}

TEST(port_kargs_copy_cparam_memory)
{
    struct memory_operation_properties prop_host = {0};
    MEMORY_ALLOCATOR(ma_host, prop_host);
    struct memory_operation_properties prop_cdev_dest = {0}, prop_cdev_src = {0};
    MEMORY_ALLOCATOR(ma_cdev_dest, prop_cdev_dest);
    MEMORY_ALLOCATOR(ma_cdev_src, prop_cdev_src);

    port_uint32_t str_mem_dest[4] = {0}, str_mem_src[4] = {0xDEAD, 0xBEEF, 0xABBA, 0x1337};
    port_uint32_t arr_mem_dest[4] = {0}, arr_mem_src[4] = {0xDEAD, 0xBEEF, 0xABBA, 0x1337};

    port_size_t sizes_mem[4];
    for (port_size_t i = 0; i < 4; i++)
        sizes_mem[i] = sizeof(port_uint32_t);

    port_void_ptr_t ptrs_str_dest_mem[4] = {0}, ptrs_str_src_mem[4] = {0};
    ptrs_str_src_mem[1] = &str_mem_src[1];
    ptrs_str_dest_mem[2] = &str_mem_dest[2];
    ptrs_str_src_mem[3] = &str_mem_src[3];
    ptrs_str_dest_mem[3] = &str_mem_dest[3];

    port_void_ptr_t ptrs_arr_dest_mem[4] = {0}, ptrs_arr_src_mem[4] = {0};
    ptrs_arr_src_mem[1] = &arr_mem_src[1];
    ptrs_arr_dest_mem[2] = &arr_mem_dest[2];
    ptrs_arr_src_mem[3] = &arr_mem_src[3];
    ptrs_arr_dest_mem[3] = &arr_mem_dest[3];

    port_kargs_cparam_sizes_t sizes = {.structures = {.sizes = sizes_mem, .num_of = 4}, .arrays = {.sizes = sizes_mem, .num_of = 4}};
    port_kargs_cparam_ptrs_t ptrs_dest = {.structures = ptrs_str_dest_mem, .arrays = ptrs_arr_dest_mem},
                             ptrs_src = {.structures = ptrs_str_src_mem, .arrays = ptrs_arr_src_mem};

    ASSERT_TRUE(port_kargs_copy_cparam_memory(&ptrs_dest, &ptrs_src, &sizes, &ma_host, &ma_cdev_dest, &ma_cdev_src));

    ASSERT_EQ(prop_host.bytes_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.bytes_mapped, 2*4, unsigned, "%u");

    ASSERT_EQ(prop_host.num_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_freed, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_mapped, 2, unsigned, "%u");
    ASSERT_EQ(prop_host.num_unmapped, 2, unsigned, "%u");

    ASSERT_EQ(prop_cdev_dest.bytes_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev_dest.bytes_mapped, 4, unsigned, "%u");

    ASSERT_EQ(prop_cdev_dest.num_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev_dest.num_freed, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev_dest.num_mapped, 1, unsigned, "%u");
    ASSERT_EQ(prop_cdev_dest.num_unmapped, 1, unsigned, "%u");

    ASSERT_EQ(prop_cdev_src.bytes_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev_src.bytes_mapped, 4, unsigned, "%u");

    ASSERT_EQ(prop_cdev_src.num_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev_src.num_freed, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev_src.num_mapped, 1, unsigned, "%u");
    ASSERT_EQ(prop_cdev_src.num_unmapped, 1, unsigned, "%u");

    ASSERT_EQ(str_mem_dest[0], 0, unsigned, "%u");
    ASSERT_EQ(str_mem_dest[1], 0, unsigned, "%u");
    ASSERT_EQ(str_mem_dest[2], 0, unsigned, "%u");
    ASSERT_EQ(str_mem_dest[3], str_mem_src[3], unsigned, "%u");

    ASSERT_EQ(arr_mem_dest[0], 0, unsigned, "%u");
    ASSERT_EQ(arr_mem_dest[1], 0, unsigned, "%u");
    ASSERT_EQ(arr_mem_dest[2], 0, unsigned, "%u");
    ASSERT_EQ(arr_mem_dest[3], arr_mem_src[3], unsigned, "%u");
}

///////////////////////////////////////////////////////////////////////////////

TEST(port_kargs_alloc_copy_segmented_memory_sizes)
{
    struct memory_operation_properties prop_host = {0};
    MEMORY_ALLOCATOR(ma_host, prop_host);

    port_size_t sizes_mem[LEN];
    for (port_size_t i = 0; i < LEN; i++)
        sizes_mem[i] = i;

    port_kargs_segmented_memory_sizes_t sizes_src = {.segment_sizes = sizes_mem,
        .num_segments = LEN, .num_table_entries = LEN2}, sizes_dest = {0};

    ASSERT_TRUE(port_kargs_alloc_copy_segmented_memory_sizes(&sizes_dest, &sizes_src, &ma_host));

    ASSERT_EQ(prop_host.bytes_allocd, sizeof(port_size_t) * LEN, unsigned, "%u");
    ASSERT_EQ(prop_host.bytes_mapped, 0, unsigned, "%u");

    ASSERT_EQ(prop_host.num_allocd, 1, unsigned, "%u");
    ASSERT_EQ(prop_host.num_freed, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_mapped, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_unmapped, 0, unsigned, "%u");

    ASSERT_EQ(sizes_dest.num_segments, LEN, unsigned, "%u");
    ASSERT_EQ(sizes_dest.num_table_entries, LEN2, unsigned, "%u");
    ASSERT_NE(sizes_dest.segment_sizes, NULL, port_void_ptr_t, "%p");
    for (port_size_t i = 0; i < LEN; i++)
        ASSERT_EQ(sizes_dest.segment_sizes[i], sizes_src.segment_sizes[i], unsigned, "%u");

    prop_host = (struct memory_operation_properties){0};
    sizes_src.num_segments = 0;
    sizes_src.num_table_entries = 0;

    ASSERT_TRUE(port_kargs_alloc_copy_segmented_memory_sizes(&sizes_dest, &sizes_src, &ma_host));

    ASSERT_EQ(prop_host.bytes_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.bytes_mapped, 0, unsigned, "%u");

    ASSERT_EQ(prop_host.num_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_freed, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_mapped, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_unmapped, 0, unsigned, "%u");

    ASSERT_EQ(sizes_dest.num_segments, 0, unsigned, "%u");
    ASSERT_EQ(sizes_dest.num_table_entries, 0, unsigned, "%u");
    ASSERT_EQ(sizes_dest.segment_sizes, NULL, port_void_ptr_t, "%p");
}

TEST(port_kargs_free_segmented_memory_sizes)
{
    struct memory_operation_properties prop_host = {0};
    MEMORY_ALLOCATOR(ma_host, prop_host);

    port_kargs_segmented_memory_sizes_t sizes = {
        .segment_sizes = (port_void_ptr_t)-1, .num_segments = LEN, .num_table_entries = LEN2};

    port_kargs_free_segmented_memory_sizes(&sizes, &ma_host);

    ASSERT_EQ(prop_host.bytes_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.bytes_mapped, 0, unsigned, "%u");

    ASSERT_EQ(prop_host.num_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_freed, 1, unsigned, "%u");
    ASSERT_EQ(prop_host.num_mapped, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_unmapped, 0, unsigned, "%u");

    ASSERT_EQ(sizes.num_segments, 0, unsigned, "%u");
    ASSERT_EQ(sizes.num_table_entries, 0, unsigned, "%u");
    ASSERT_EQ(sizes.segment_sizes, NULL, port_void_ptr_t, "%p");
}

TEST(port_kargs_alloc_segmented_memory_arrays)
{
    struct memory_operation_properties prop_host = {0};
    MEMORY_ALLOCATOR(ma_host, prop_host);

    port_kargs_segmented_memory_sizes_t sizes = {.num_segments = LEN};
    port_kargs_segmented_memory_ptrs_t ptrs = {0};

    ASSERT_TRUE(port_kargs_alloc_segmented_memory_arrays(&ptrs, &sizes, &ma_host));

    ASSERT_EQ(prop_host.bytes_allocd, sizeof(port_void_ptr_t) * LEN, unsigned, "%u");
    ASSERT_EQ(prop_host.bytes_mapped, 0, unsigned, "%u");

    ASSERT_EQ(prop_host.num_allocd, 1, unsigned, "%u");
    ASSERT_EQ(prop_host.num_freed, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_mapped, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_unmapped, 0, unsigned, "%u");

    ASSERT_NE(ptrs.segments, NULL, port_void_ptr_t, "%p");

    prop_host = (struct memory_operation_properties){0};
    sizes.num_segments = 0;

    ASSERT_TRUE(port_kargs_alloc_segmented_memory_arrays(&ptrs, &sizes, &ma_host));

    ASSERT_EQ(prop_host.bytes_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.bytes_mapped, 0, unsigned, "%u");

    ASSERT_EQ(prop_host.num_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_freed, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_mapped, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_unmapped, 0, unsigned, "%u");

    ASSERT_EQ(ptrs.segments, NULL, port_void_ptr_t, "%p");
}

TEST(port_kargs_free_segmented_memory_arrays)
{
    struct memory_operation_properties prop_host = {0};
    MEMORY_ALLOCATOR(ma_host, prop_host);

    port_kargs_segmented_memory_sizes_t sizes = {.num_segments = LEN};
    port_kargs_segmented_memory_ptrs_t ptrs = {.segments = (port_void_ptr_t)-1};

    port_kargs_free_segmented_memory_arrays(&ptrs, &sizes, &ma_host);

    ASSERT_EQ(prop_host.bytes_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.bytes_mapped, 0, unsigned, "%u");

    ASSERT_EQ(prop_host.num_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_freed, 1, unsigned, "%u");
    ASSERT_EQ(prop_host.num_mapped, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_unmapped, 0, unsigned, "%u");

    ASSERT_EQ(ptrs.segments, NULL, port_void_ptr_t, "%p");
}

TEST(port_kargs_alloc_segmented_memory_memory)
{
    struct memory_operation_properties prop_cdev = {0};
    MEMORY_ALLOCATOR(ma_cdev, prop_cdev);

    port_void_ptr_t ptrs_mem[LEN] = {0};

    port_size_t sizes_mem[LEN];
    for (port_size_t i = 0; i < LEN; i++)
        sizes_mem[i] = i;

    port_kargs_segmented_memory_sizes_t sizes = {.segment_sizes = sizes_mem, .num_segments = LEN,
        .num_table_entries = LEN2};
    port_kargs_segmented_memory_ptrs_t ptrs = {.segments = ptrs_mem};

    ASSERT_TRUE(port_kargs_alloc_segmented_memory_memory(&ptrs, &sizes, &ma_cdev));

    ASSERT_EQ(prop_cdev.bytes_allocd, LEN * (LEN - 1) / 2 + sizeof(port_void_ptr_t) * LEN2, unsigned, "%u");
    ASSERT_EQ(prop_cdev.bytes_mapped, 0, unsigned, "%u");

    ASSERT_EQ(prop_cdev.num_allocd, LEN, unsigned, "%u");
    ASSERT_EQ(prop_cdev.num_freed, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev.num_mapped, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev.num_unmapped, 0, unsigned, "%u");

    ASSERT_EQ(ptrs.segments[0], NULL, port_void_ptr_t, "%p");
    for (port_size_t i = 1; i < LEN; i++)
        ASSERT_NE(ptrs.segments[i], NULL, port_void_ptr_t, "%p");

    ASSERT_NE(ptrs.table, NULL, port_void_ptr_t, "%p");
}

TEST(port_kargs_free_segmented_memory_memory)
{
    struct memory_operation_properties prop_cdev = {0};
    MEMORY_ALLOCATOR(ma_cdev, prop_cdev);

    port_void_ptr_t ptrs_mem[LEN] = {0};
    for (port_size_t i = 0; i < LEN; i++)
        ptrs_mem[i] = (port_void_ptr_t)-1;

    port_kargs_segmented_memory_sizes_t sizes = {.num_segments = LEN};
    port_kargs_segmented_memory_ptrs_t ptrs = {.segments = ptrs_mem, .table = (port_void_ptr_t)-1,
        .root = (port_void_ptr_t)-1};

    port_kargs_free_segmented_memory_memory(&ptrs, &sizes, &ma_cdev);

    ASSERT_EQ(prop_cdev.bytes_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev.bytes_mapped, 0, unsigned, "%u");

    ASSERT_EQ(prop_cdev.num_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev.num_freed, LEN + 1, unsigned, "%u");
    ASSERT_EQ(prop_cdev.num_mapped, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev.num_unmapped, 0, unsigned, "%u");

    for (port_size_t i = 0; i < LEN; i++)
        ASSERT_EQ(ptrs.segments[i], NULL, port_void_ptr_t, "%p");

    ASSERT_EQ(ptrs.table, NULL, port_void_ptr_t, "%p");
    ASSERT_EQ(ptrs.root, NULL, port_void_ptr_t, "%p");
}

TEST(port_kargs_copy_segmented_memory_memory)
{
    struct memory_operation_properties prop_cdev_dest = {0}, prop_cdev_src = {0};
    MEMORY_ALLOCATOR(ma_cdev_dest, prop_cdev_dest);
    MEMORY_ALLOCATOR(ma_cdev_src, prop_cdev_src);

    port_uint32_t mem_dest[4] = {0}, mem_src[4] = {0xDEAD, 0xBEEF, 0xABBA, 0x1337};

    port_size_t sizes_mem[4];
    for (port_size_t i = 0; i < 4; i++)
        sizes_mem[i] = sizeof(port_uint32_t);

    port_void_ptr_t ptrs_dest_mem[4] = {0}, ptrs_src_mem[4] = {0};
    ptrs_src_mem[1] = &mem_src[1];
    ptrs_dest_mem[2] = &mem_dest[2];
    ptrs_src_mem[3] = &mem_src[3];
    ptrs_dest_mem[3] = &mem_dest[3];

    port_kargs_segmented_memory_sizes_t sizes = {.segment_sizes = sizes_mem, .num_segments = 4};
    port_kargs_segmented_memory_ptrs_t ptrs_dest = {.segments = ptrs_dest_mem},
                             ptrs_src = {.segments = ptrs_src_mem};

    ASSERT_TRUE(port_kargs_copy_segmented_memory_memory(&ptrs_dest, &ptrs_src, &sizes, &ma_cdev_dest, &ma_cdev_src));

    ASSERT_EQ(prop_cdev_dest.bytes_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev_dest.bytes_mapped, 4, unsigned, "%u");

    ASSERT_EQ(prop_cdev_dest.num_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev_dest.num_freed, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev_dest.num_mapped, 1, unsigned, "%u");
    ASSERT_EQ(prop_cdev_dest.num_unmapped, 1, unsigned, "%u");

    ASSERT_EQ(prop_cdev_src.bytes_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev_src.bytes_mapped, 4, unsigned, "%u");

    ASSERT_EQ(prop_cdev_src.num_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev_src.num_freed, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev_src.num_mapped, 1, unsigned, "%u");
    ASSERT_EQ(prop_cdev_src.num_unmapped, 1, unsigned, "%u");

    ASSERT_EQ(mem_dest[0], 0, unsigned, "%u");
    ASSERT_EQ(mem_dest[1], 0, unsigned, "%u");
    ASSERT_EQ(mem_dest[2], 0, unsigned, "%u");
    ASSERT_EQ(mem_dest[3], mem_src[3], unsigned, "%u");
}

TEST(port_kargs_alloc_copy_segmented_memory_table)
{
    struct memory_operation_properties prop_host = {0};
    MEMORY_ALLOCATOR(ma_host, prop_host);

#define SIZE (sizeof(port_kargs_segmented_memory_table_t) + sizeof(port_kargs_segmented_memory_symbol_t) * LEN)

    union {
        port_kargs_segmented_memory_table_t as_table;
        char as_bytes[SIZE];
    } src = {.as_table = {.root_symbol = {.segment_idx = 13, .value = 37}}};

    for (port_size_t i = 0; i < LEN; i++)
        src.as_table.table_symbols[i] = (port_kargs_segmented_memory_symbol_t){.segment_idx = i, .value = i*i};

    port_kargs_segmented_memory_table_t *table_dest =
        port_kargs_alloc_copy_segmented_memory_table(&src.as_table, LEN, &ma_host);

    ASSERT_NE(table_dest, NULL, port_void_ptr_t, "%p");

    ASSERT_EQ(prop_host.bytes_allocd, SIZE, unsigned, "%u");
    ASSERT_EQ(prop_host.bytes_mapped, 0, unsigned, "%u");

    ASSERT_EQ(prop_host.num_allocd, 1, unsigned, "%u");
    ASSERT_EQ(prop_host.num_freed, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_mapped, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_unmapped, 0, unsigned, "%u");

    ASSERT_EQ(table_dest->root_symbol.segment_idx, 13, unsigned, "%u");
    ASSERT_EQ(table_dest->root_symbol.value, 37, unsigned, "%u");

    for (port_size_t i = 0; i < LEN; i++)
    {
        ASSERT_EQ(table_dest->table_symbols[i].segment_idx, src.as_table.table_symbols[i].segment_idx, unsigned, "%u");
        ASSERT_EQ(table_dest->table_symbols[i].value, src.as_table.table_symbols[i].value, unsigned, "%u");
    }

#undef SIZE
}

TEST(port_kargs_free_segmented_memory_table)
{
    struct memory_operation_properties prop_host = {0};
    MEMORY_ALLOCATOR(ma_host, prop_host);

    port_kargs_segmented_memory_table_t *table = (port_void_ptr_t)-1;

    port_kargs_free_segmented_memory_table(table, &ma_host);

    ASSERT_EQ(prop_host.bytes_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.bytes_mapped, 0, unsigned, "%u");

    ASSERT_EQ(prop_host.num_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_freed, 1, unsigned, "%u");
    ASSERT_EQ(prop_host.num_mapped, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_unmapped, 0, unsigned, "%u");
}

TEST(port_kargs_write_segmented_memory_table)
{
    struct memory_operation_properties prop_cdev = {0};
    MEMORY_ALLOCATOR(ma_cdev, prop_cdev);

    char mem[4][128];
    port_void_ptr_t segments_arr[4] = {&mem[0], &mem[1], &mem[2], &mem[3]};
    port_size_t sizes_arr[4] = {128, 128, 128, 128};
    port_void_ptr_t table_arr[3] = {0};

#define SIZE (sizeof(port_kargs_segmented_memory_table_t) + sizeof(port_kargs_segmented_memory_symbol_t) * 3)

    union {
        port_kargs_segmented_memory_table_t as_table;
        char as_bytes[SIZE];
    } src = {.as_table = {.root_symbol = {.segment_idx = 3, .value = 37}}};
    src.as_table.table_symbols[0] = (port_kargs_segmented_memory_symbol_t){.segment_idx = 0, .value = 0};
    src.as_table.table_symbols[1] = (port_kargs_segmented_memory_symbol_t){.segment_idx = 2, .value = 64};
    src.as_table.table_symbols[2] = (port_kargs_segmented_memory_symbol_t){.segment_idx = 1, .value = 128};

    port_kargs_segmented_memory_sizes_t sizes = {.segment_sizes = sizes_arr, .num_segments = 4, .num_table_entries = 3};
    port_kargs_segmented_memory_ptrs_t ptrs = {.segments = segments_arr, .table = table_arr};

    ASSERT_TRUE(port_kargs_write_segmented_memory_table(&ptrs, &sizes, &src.as_table, &ma_cdev));

    ASSERT_EQ(prop_cdev.bytes_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev.bytes_mapped, sizeof(port_void_ptr_t) * 3, unsigned, "%u");

    ASSERT_EQ(prop_cdev.num_allocd, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev.num_freed, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev.num_mapped, 1, unsigned, "%u");
    ASSERT_EQ(prop_cdev.num_unmapped, 1, unsigned, "%u");

    ASSERT_EQ(table_arr[0], segments_arr[0], port_void_ptr_t, "%p");
    ASSERT_EQ(table_arr[1], (char*)segments_arr[2] + 64, port_void_ptr_t, "%p");
    ASSERT_EQ(table_arr[2], (char*)segments_arr[1] + 128, port_void_ptr_t, "%p");
    ASSERT_EQ(ptrs.root, (char*)segments_arr[3] + 37, port_void_ptr_t, "%p");
}

TEST(port_kargs_construct_segmented_memory_from_data_storage)
{
    struct memory_operation_properties prop_host = {0}, prop_cdev = {0};
    MEMORY_ALLOCATOR(ma_host, prop_host);
    MEMORY_ALLOCATOR(ma_cdev, prop_cdev);

    port_kargs_segmented_memory_ptrs_t ptrs = {0};
    port_kargs_segmented_memory_sizes_t sizes = {0};
    port_kargs_segmented_memory_table_t *table = NULL;

    char *strings[] = {"root", "section", "symbol"};

    port_uint_single_t property_name_str_idx[] = {0};
    port_uint_single_t values[] = {1, 7};
    port_void_ptr_t property_values[] = {&values[0]};
    port_uint_single_t property_value_sizes[] = {sizeof(port_uint_single_t) * 2};

    port_uint_single_t section_name_str_idx[] = {1, 1};
    port_void_ptr_t sections[] = {"12345678", "abcdefgh"};
    port_uint_single_t section_sizes[] = {8, 8};

    port_uint_single_t symbol_name_str_idx[] = {2, 2, 2};
    port_uint_single_t symbol_section_idx[] = {0, 1, 0};
    port_uint_single_t symbol_values[] = {0, 4, 8};

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
            .properties = 1,
            .sections = 2,
            .symbols = 3,
            .strings = 3,
        },
    };

    ASSERT_TRUE(port_kargs_construct_segmented_memory_from_data_storage(&ptrs, &sizes, &table,
                &storage, &ma_host, &ma_cdev));

    ASSERT_EQ(prop_host.bytes_allocd, 2*sizeof(port_void_ptr_t) + 2*sizeof(port_size_t) +
            sizeof(port_kargs_segmented_memory_table_t) + 3*sizeof(port_kargs_segmented_memory_symbol_t), unsigned, "%u");
    ASSERT_EQ(prop_host.bytes_mapped, 0, unsigned, "%u");

    ASSERT_EQ(prop_host.num_allocd, 3, unsigned, "%u");
    ASSERT_EQ(prop_host.num_freed, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_mapped, 0, unsigned, "%u");
    ASSERT_EQ(prop_host.num_unmapped, 0, unsigned, "%u");

    ASSERT_EQ(prop_cdev.bytes_allocd, 2*8 + 3*sizeof(port_void_ptr_t), unsigned, "%u");
    ASSERT_EQ(prop_cdev.bytes_mapped, 2*8 + 3*sizeof(port_void_ptr_t), unsigned, "%u");

    ASSERT_EQ(prop_cdev.num_allocd, 2 + 1, unsigned, "%u");
    ASSERT_EQ(prop_cdev.num_freed, 0, unsigned, "%u");
    ASSERT_EQ(prop_cdev.num_mapped, 2 + 1, unsigned, "%u");
    ASSERT_EQ(prop_cdev.num_unmapped, 2 + 1, unsigned, "%u");

    for (port_size_t i = 0; i < 2; i++)
    {
        for (port_size_t j = 0; j < 8; j++)
            ASSERT_EQ(((char*)ptrs.segments[i])[j], ((char*)sections[i])[j], unsigned, "%u");

        ASSERT_EQ(sizes.segment_sizes[i], 8, unsigned, "%u");
    }

    ASSERT_EQ(ptrs.table[0], ptrs.segments[0] + 0, port_void_ptr_t, "%p");
    ASSERT_EQ(ptrs.table[1], ptrs.segments[1] + 4, port_void_ptr_t, "%p");
    ASSERT_EQ(ptrs.table[2], ptrs.segments[0] + 8, port_void_ptr_t, "%p");
    ASSERT_EQ(ptrs.root, ptrs.segments[1] + 7, port_void_ptr_t, "%p");

    ASSERT_EQ(sizes.num_segments, 2, unsigned, "%u");
    ASSERT_EQ(sizes.num_table_entries, 3, unsigned, "%u");

    ASSERT_NE(table, NULL, port_void_ptr_t, "%p");
    ASSERT_EQ(table->root_symbol.segment_idx, 1, unsigned, "%u");
    ASSERT_EQ(table->root_symbol.value, 7, unsigned, "%u");
    ASSERT_EQ(table->table_symbols[0].segment_idx, 0, unsigned, "%u");
    ASSERT_EQ(table->table_symbols[0].value, 0, unsigned, "%u");
    ASSERT_EQ(table->table_symbols[1].segment_idx, 1, unsigned, "%u");
    ASSERT_EQ(table->table_symbols[1].value, 4, unsigned, "%u");
    ASSERT_EQ(table->table_symbols[2].segment_idx, 0, unsigned, "%u");
    ASSERT_EQ(table->table_symbols[2].value, 8, unsigned, "%u");
}

