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
 * @brief Functions for processing kernel arguments on host.
 */

#include <port/host/kernel.fun.h>
#include <port/host/kernel.typ.h>
#include <port/host/memory.fun.h>
#include <port/host/memory.typ.h>
#include <port/host/storage.typ.h>
#include <port/host/cpu/memory.fun.h>

#include <assert.h>
#include <stdalign.h>
#include <string.h>

#define ALLOC(ptr, sz, algn, ma) do { \
    (ptr) = (ma)->operations.alloc_fn((sz), (algn), (ma)->properties.alloc); \
    if ((ptr) == NULL) goto failure; \
} while (0)

#define ALLOC_ARRAY(arr, num, type, ma) do {                    \
    ALLOC((arr), sizeof(*(arr)) * (num), alignof(type), (ma));  \
    for (port_size_t index = 0; index < (num); index++)         \
        (arr)[index] = 0;                                       \
} while (0)

#define FREE(ptr, ma) do { \
    (ma)->operations.free_fn((ptr), (ma)->properties.alloc); \
    (ptr) = NULL; \
} while (0)

#define MEMCOPY(dest, src, sz, ma_dest, ma_src) do { \
    if (!port_memory_map_copy_unmap((dest), (src), (sz), (ma_dest), (ma_src))) \
        goto failure; \
} while (0)

///////////////////////////////////////////////////////////////////////////////
// Computation states
///////////////////////////////////////////////////////////////////////////////

port_bool_t
port_kargs_alloc_copy_cstate_sizes(
        port_kargs_cstate_sizes_t *sizes_dest,
        const port_kargs_cstate_sizes_t *sizes_src,

        const port_memory_allocator_t *ma_host)
{
    assert(sizes_dest != NULL);
    assert(sizes_src != NULL);
    assert(ma_host != NULL);
    assert(ma_host->operations.alloc_fn != NULL);

    *sizes_dest = (port_kargs_cstate_sizes_t){0};

    port_size_t num_of = sizes_src->num_of;

    if (num_of > 0)
    {
        ALLOC_ARRAY(sizes_dest->sizes, num_of, port_size_t, ma_host);

        memcpy(sizes_dest->sizes, sizes_src->sizes, sizeof(*sizes_dest->sizes) * num_of);
        sizes_dest->num_of = num_of;
    }

    return true;

failure:
    port_kargs_free_cstate_sizes(sizes_dest, ma_host);
    return false;
}

void
port_kargs_free_cstate_sizes(
        port_kargs_cstate_sizes_t *sizes,

        const port_memory_allocator_t *ma_host)
{
    assert(sizes != NULL);
    assert(ma_host != NULL);
    assert(ma_host->operations.free_fn != NULL);

    FREE(sizes->sizes, ma_host);
    sizes->num_of = 0;
}

port_bool_t
port_kargs_alloc_cstate_arrays(
        port_kargs_cstate_ptrs_t *ptrs,
        const port_kargs_cstate_sizes_t *sizes,

        const port_memory_allocator_t *ma_host)
{
    assert(ptrs != NULL);
    assert(sizes != NULL);
    assert(ma_host != NULL);
    assert(ma_host->operations.alloc_fn != NULL);

    *ptrs = (port_kargs_cstate_ptrs_t){0};

    if (sizes->num_of > 0)
        ALLOC_ARRAY(ptrs->arrays, sizes->num_of, port_void_ptr_t, ma_host);

    return true;

failure:
    port_kargs_free_cstate_arrays(ptrs, sizes, ma_host);
    return false;
}

void
port_kargs_free_cstate_arrays(
        port_kargs_cstate_ptrs_t *ptrs,
        const port_kargs_cstate_sizes_t *sizes,

        const port_memory_allocator_t *ma_host)
{
    (void) sizes;

    assert(ptrs != NULL);
    // assert(sizes != NULL);
    assert(ma_host != NULL);
    assert(ma_host->operations.free_fn != NULL);

    FREE(ptrs->arrays, ma_host);
}

port_bool_t
port_kargs_alloc_cstate_memory(
        port_kargs_cstate_ptrs_t *ptrs,
        const port_kargs_cstate_sizes_t *sizes,

        const port_memory_allocator_t *ma_cdev)
{
    assert(ptrs != NULL);
    assert(sizes != NULL);
    assert(ma_cdev != NULL);
    assert(ma_cdev->operations.alloc_fn != NULL);

    if (ptrs->arrays != NULL)
    {
        for (port_size_t i = 0; i < sizes->num_of; i++)
        {
            if (sizes->sizes[i] > 0)
                ALLOC(ptrs->arrays[i], sizes->sizes[i], 0, ma_cdev);
        }
    }

    return true;

failure:
    port_kargs_free_cstate_memory(ptrs, sizes, ma_cdev);
    return false;
}

void
port_kargs_free_cstate_memory(
        port_kargs_cstate_ptrs_t *ptrs,
        const port_kargs_cstate_sizes_t *sizes,

        const port_memory_allocator_t *ma_cdev)
{
    assert(ptrs != NULL);
    assert(sizes != NULL);
    assert(ma_cdev != NULL);
    assert(ma_cdev->operations.free_fn != NULL);

    if (ptrs->arrays != NULL)
    {
        for (port_size_t i = 0; i < sizes->num_of; i++)
            FREE(ptrs->arrays[i], ma_cdev);
    }
}

port_bool_t
port_kargs_copy_cstate_memory(
        port_kargs_cstate_ptrs_t *ptrs_dest,
        const port_kargs_cstate_ptrs_t *ptrs_src,
        const port_kargs_cstate_sizes_t *sizes,

        const port_memory_allocator_t *ma_cdev_dest,
        const port_memory_allocator_t *ma_cdev_src)
{
    assert(ptrs_dest != NULL);
    assert(ptrs_src != NULL);
    assert(sizes != NULL);
    assert(ma_cdev_dest != NULL);
    assert(ma_cdev_src != NULL);

    if ((sizes->num_of > 0) && (ptrs_dest->arrays != NULL) && (ptrs_src->arrays != NULL))
    {
        assert(sizes->sizes != NULL);

        for (port_size_t i = 0; i < sizes->num_of; i++)
        {
            port_size_t size = sizes->sizes[i];

            if ((size > 0) && (ptrs_dest->arrays[i] != NULL) && (ptrs_src->arrays[i] != NULL))
                MEMCOPY(ptrs_dest->arrays[i], ptrs_src->arrays[i], size, ma_cdev_dest, ma_cdev_src);
        }
    }

    return true;

failure:
    return false;
}

///////////////////////////////////////////////////////////////////////////////
// Computation parameters
///////////////////////////////////////////////////////////////////////////////

port_bool_t
port_kargs_alloc_copy_cparam_sizes(
        port_kargs_cparam_sizes_t *sizes_dest,
        const port_kargs_cparam_sizes_t *sizes_src,

        const port_memory_allocator_t *ma_host)
{
    assert(sizes_dest != NULL);
    assert(sizes_src != NULL);
    assert(ma_host != NULL);
    assert(ma_host->operations.alloc_fn != NULL);

    *sizes_dest = (port_kargs_cparam_sizes_t){0};

    {
        port_size_t num_of = sizes_src->structures.num_of;

        if (num_of > 0)
        {
            ALLOC_ARRAY(sizes_dest->structures.sizes, num_of, port_size_t, ma_host);

            memcpy(sizes_dest->structures.sizes, sizes_src->structures.sizes,
                    sizeof(*sizes_dest->structures.sizes) * num_of);
            sizes_dest->structures.num_of = num_of;
        }
    }

    {
        port_size_t num_of = sizes_src->arrays.num_of;

        if (num_of > 0)
        {
            ALLOC_ARRAY(sizes_dest->arrays.sizes, num_of, port_size_t, ma_host);

            memcpy(sizes_dest->arrays.sizes, sizes_src->arrays.sizes,
                    sizeof(*sizes_dest->arrays.sizes) * num_of);
            sizes_dest->arrays.num_of = num_of;
        }
    }

    return true;

failure:
    port_kargs_free_cparam_sizes(sizes_dest, ma_host);
    return false;
}

void
port_kargs_free_cparam_sizes(
        port_kargs_cparam_sizes_t *sizes,

        const port_memory_allocator_t *ma_host)
{
    assert(sizes != NULL);
    assert(ma_host != NULL);
    assert(ma_host->operations.free_fn != NULL);

    FREE(sizes->structures.sizes, ma_host);
    sizes->structures.num_of = 0;

    FREE(sizes->arrays.sizes, ma_host);
    sizes->arrays.num_of = 0;
}

port_bool_t
port_kargs_alloc_cparam_arrays(
        port_kargs_cparam_ptrs_t *ptrs,
        const port_kargs_cparam_sizes_t *sizes,

        const port_memory_allocator_t *ma_host)
{
    assert(ptrs != NULL);
    assert(sizes != NULL);
    assert(ma_host != NULL);
    assert(ma_host->operations.alloc_fn != NULL);

    *ptrs = (port_kargs_cparam_ptrs_t){0};

    if (sizes->structures.num_of > 0)
        ALLOC_ARRAY(ptrs->structures, sizes->structures.num_of, port_void_ptr_t, ma_host);

    if (sizes->arrays.num_of > 0)
        ALLOC_ARRAY(ptrs->arrays, sizes->arrays.num_of, port_void_ptr_t, ma_host);

    return true;

failure:
    port_kargs_free_cparam_arrays(ptrs, sizes, ma_host);
    return false;
}

void
port_kargs_free_cparam_arrays(
        port_kargs_cparam_ptrs_t *ptrs,
        const port_kargs_cparam_sizes_t *sizes,

        const port_memory_allocator_t *ma_host)
{
    (void) sizes;

    assert(ptrs != NULL);
    // assert(sizes != NULL);
    assert(ma_host != NULL);
    assert(ma_host->operations.free_fn != NULL);

    FREE(ptrs->structures, ma_host);
    FREE(ptrs->arrays, ma_host);
}

port_bool_t
port_kargs_alloc_cparam_memory(
        port_kargs_cparam_ptrs_t *ptrs,
        const port_kargs_cparam_sizes_t *sizes,

        const port_memory_allocator_t *ma_host,
        const port_memory_allocator_t *ma_cdev)
{
    assert(ptrs != NULL);
    assert(sizes != NULL);
    assert(ma_host != NULL);
    assert(ma_host->operations.alloc_fn != NULL);
    assert(ma_cdev != NULL);
    assert(ma_cdev->operations.alloc_fn != NULL);

    if (ptrs->structures != NULL)
    {
        for (port_size_t i = 0; i < sizes->structures.num_of; i++)
            if (sizes->structures.sizes[i] > 0)
                ALLOC(ptrs->structures[i], sizes->structures.sizes[i], 0, ma_host);
    }

    if (ptrs->arrays != NULL)
    {
        for (port_size_t i = 0; i < sizes->arrays.num_of; i++)
            if (sizes->arrays.sizes[i] > 0)
                ALLOC(ptrs->arrays[i], sizes->arrays.sizes[i], 0, ma_cdev);
    }

    return true;

failure:
    port_kargs_free_cparam_memory(ptrs, sizes, ma_host, ma_cdev);
    return false;
}

void
port_kargs_free_cparam_memory(
        port_kargs_cparam_ptrs_t *ptrs,
        const port_kargs_cparam_sizes_t *sizes,

        const port_memory_allocator_t *ma_host,
        const port_memory_allocator_t *ma_cdev)
{
    assert(ptrs != NULL);
    assert(sizes != NULL);
    assert(ma_host != NULL);
    assert(ma_host->operations.free_fn != NULL);
    assert(ma_cdev != NULL);
    assert(ma_cdev->operations.free_fn != NULL);

    if (ptrs->structures != NULL)
    {
        for (port_size_t i = 0; i < sizes->structures.num_of; i++)
            FREE(ptrs->structures[i], ma_host);
    }

    if (ptrs->arrays != NULL)
    {
        for (port_size_t i = 0; i < sizes->arrays.num_of; i++)
            FREE(ptrs->arrays[i], ma_cdev);
    }
}

port_bool_t
port_kargs_copy_cparam_memory(
        port_kargs_cparam_ptrs_t *ptrs_dest,
        const port_kargs_cparam_ptrs_t *ptrs_src,
        const port_kargs_cparam_sizes_t *sizes,

        const port_memory_allocator_t *ma_host,
        const port_memory_allocator_t *ma_cdev_dest,
        const port_memory_allocator_t *ma_cdev_src)
{
    assert(ptrs_dest != NULL);
    assert(ptrs_src != NULL);
    assert(sizes != NULL);
    assert(ma_host != NULL);
    assert(ma_cdev_dest != NULL);
    assert(ma_cdev_src != NULL);

    if ((sizes->structures.num_of > 0) && (ptrs_dest->structures != NULL) && (ptrs_src->structures != NULL))
    {
        assert(sizes->structures.sizes != NULL);

        for (port_size_t i = 0; i < sizes->structures.num_of; i++)
        {
            port_size_t size = sizes->structures.sizes[i];

            if ((size > 0) && (ptrs_dest->structures[i] != NULL) && (ptrs_src->structures[i] != NULL))
                MEMCOPY(ptrs_dest->structures[i], ptrs_src->structures[i], size, ma_host, ma_host);
        }
    }

    if ((sizes->arrays.num_of > 0) && (ptrs_dest->arrays != NULL) && (ptrs_src->arrays != NULL))
    {
        assert(sizes->arrays.sizes != NULL);

        for (port_size_t i = 0; i < sizes->arrays.num_of; i++)
        {
            port_size_t size = sizes->arrays.sizes[i];

            if ((size > 0) && (ptrs_dest->arrays[i] != NULL) && (ptrs_src->arrays[i] != NULL))
                MEMCOPY(ptrs_dest->arrays[i], ptrs_src->arrays[i], size, ma_cdev_dest, ma_cdev_src);
        }
    }

    return true;

failure:
    return false;
}

///////////////////////////////////////////////////////////////////////////////
// Segmented memory
///////////////////////////////////////////////////////////////////////////////

port_bool_t
port_kargs_alloc_copy_segmented_memory_sizes(
        port_kargs_segmented_memory_sizes_t *sizes_dest,
        const port_kargs_segmented_memory_sizes_t *sizes_src,

        const port_memory_allocator_t *ma_host)
{
    assert(sizes_dest != NULL);
    assert(sizes_src != NULL);
    assert(ma_host != NULL);
    assert(ma_host->operations.alloc_fn != NULL);

    *sizes_dest = (port_kargs_segmented_memory_sizes_t){0};

    port_size_t num_segments = sizes_src->num_segments;

    if (num_segments > 0)
    {
        ALLOC_ARRAY(sizes_dest->segment_sizes, num_segments, port_size_t, ma_host);

        memcpy(sizes_dest->segment_sizes, sizes_src->segment_sizes,
                sizeof(*sizes_dest->segment_sizes) * num_segments);
        sizes_dest->num_segments = num_segments;
        sizes_dest->num_table_entries = sizes_src->num_table_entries;
    }

    return true;

failure:
    port_kargs_free_segmented_memory_sizes(sizes_dest, ma_host);
    return false;
}

void
port_kargs_free_segmented_memory_sizes(
        port_kargs_segmented_memory_sizes_t *sizes,

        const port_memory_allocator_t *ma_host)
{
    assert(sizes != NULL);
    assert(ma_host != NULL);
    assert(ma_host->operations.free_fn != NULL);

    FREE(sizes->segment_sizes, ma_host);
    sizes->num_segments = 0;
    sizes->num_table_entries = 0;
}

port_bool_t
port_kargs_alloc_segmented_memory_arrays(
        port_kargs_segmented_memory_ptrs_t *ptrs,
        const port_kargs_segmented_memory_sizes_t *sizes,

        const port_memory_allocator_t *ma_host)
{
    assert(ptrs != NULL);
    assert(sizes != NULL);
    assert(ma_host != NULL);
    assert(ma_host->operations.alloc_fn != NULL);

    *ptrs = (port_kargs_segmented_memory_ptrs_t){0};

    if (sizes->num_segments > 0)
        ALLOC_ARRAY(ptrs->segments, sizes->num_segments, port_void_ptr_t, ma_host);

    return true;

failure:
    port_kargs_free_segmented_memory_arrays(ptrs, sizes, ma_host);
    return false;
}

void
port_kargs_free_segmented_memory_arrays(
        port_kargs_segmented_memory_ptrs_t *ptrs,
        const port_kargs_segmented_memory_sizes_t *sizes,

        const port_memory_allocator_t *ma_host)
{
    (void) sizes;

    assert(ptrs != NULL);
    // assert(sizes != NULL);
    assert(ma_host != NULL);
    assert(ma_host->operations.free_fn != NULL);

    FREE(ptrs->segments, ma_host);
}

port_bool_t
port_kargs_alloc_segmented_memory_memory(
        port_kargs_segmented_memory_ptrs_t *ptrs,
        const port_kargs_segmented_memory_sizes_t *sizes,

        const port_memory_allocator_t *ma_cdev)
{
    assert(ptrs != NULL);
    assert(sizes != NULL);
    assert(ma_cdev != NULL);
    assert(ma_cdev->operations.alloc_fn != NULL);

    if (ptrs->segments != NULL)
    {
        for (port_size_t i = 0; i < sizes->num_segments; i++)
            if (sizes->segment_sizes[i] > 0)
                ALLOC(ptrs->segments[i], sizes->segment_sizes[i], alignof(port_memory_unit_t), ma_cdev);
    }

    ALLOC_ARRAY(ptrs->table, sizes->num_table_entries, port_void_ptr_t, ma_cdev);

    return true;

failure:
    port_kargs_free_segmented_memory_memory(ptrs, sizes, ma_cdev);
    return false;
}

void
port_kargs_free_segmented_memory_memory(
        port_kargs_segmented_memory_ptrs_t *ptrs,
        const port_kargs_segmented_memory_sizes_t *sizes,

        const port_memory_allocator_t *ma_cdev)
{
    assert(ptrs != NULL);
    assert(sizes != NULL);
    assert(ma_cdev != NULL);
    assert(ma_cdev->operations.free_fn != NULL);

    if (ptrs->segments != NULL)
    {
        for (port_size_t i = 0; i < sizes->num_segments; i++)
            FREE(ptrs->segments[i], ma_cdev);
    }

    FREE(ptrs->table, ma_cdev);
    ptrs->root = NULL;
}

port_bool_t
port_kargs_copy_segmented_memory_memory(
        port_kargs_segmented_memory_ptrs_t *ptrs_dest,
        const port_kargs_segmented_memory_ptrs_t *ptrs_src,
        const port_kargs_segmented_memory_sizes_t *sizes,

        const port_memory_allocator_t *ma_cdev_dest,
        const port_memory_allocator_t *ma_cdev_src)
{
    assert(ptrs_dest != NULL);
    assert(ptrs_src != NULL);
    assert(sizes != NULL);
    assert(ma_cdev_dest != NULL);
    assert(ma_cdev_src != NULL);

    if ((sizes->num_segments > 0) && (ptrs_dest->segments != NULL) && (ptrs_src->segments != NULL))
    {
        assert(sizes->segment_sizes != NULL);

        for (port_size_t i = 0; i < sizes->num_segments; i++)
        {
            port_size_t size = sizes->segment_sizes[i];

            if ((size > 0) && (ptrs_dest->segments[i] != NULL) && (ptrs_src->segments[i] != NULL))
                MEMCOPY(ptrs_dest->segments[i], ptrs_src->segments[i], size, ma_cdev_dest, ma_cdev_src);
        }
    }

    return true;

failure:
    return false;
}

port_kargs_segmented_memory_table_t*
port_kargs_alloc_copy_segmented_memory_table(
        const port_kargs_segmented_memory_table_t *table_src,

        port_size_t num_table_symbols,

        const port_memory_allocator_t *ma_host)
{
    assert(table_src != NULL);
    assert(ma_host != NULL);
    assert(ma_host->operations.alloc_fn != NULL);

    port_kargs_segmented_memory_table_t *table_dest = NULL;
    port_size_t size = sizeof(*table_dest) + sizeof(*table_dest->table_symbols) * num_table_symbols;

    ALLOC(table_dest, size, alignof(port_kargs_segmented_memory_table_t), ma_host);
    memcpy(table_dest, table_src, size);

    return table_dest;

failure:
    port_kargs_free_segmented_memory_table(table_dest, ma_host);
    return NULL;
}

void
port_kargs_free_segmented_memory_table(
        port_kargs_segmented_memory_table_t *table,

        const port_memory_allocator_t *ma_host)
{
    assert(table != NULL);
    assert(ma_host != NULL);
    assert(ma_host->operations.free_fn != NULL);

    FREE(table, ma_host);
}

port_bool_t
port_kargs_write_segmented_memory_table(
        port_kargs_segmented_memory_ptrs_t *ptrs,
        const port_kargs_segmented_memory_sizes_t *sizes,
        const port_kargs_segmented_memory_table_t *table,

        const port_memory_allocator_t *ma_cdev)
{
    (void) sizes;

    assert(ptrs != NULL);
    // assert(sizes != NULL);
    assert(table != NULL);
    assert(ma_cdev != NULL);
    assert(ma_cdev->operations.map_fn != NULL);
    assert(ma_cdev->operations.unmap_fn != NULL);

    // Root symbol
    assert(table->root_symbol.segment_idx < sizes->num_segments);
    assert(table->root_symbol.value <= sizes->segment_sizes[table->root_symbol.segment_idx]);

    ptrs->root = (char*)ptrs->segments[table->root_symbol.segment_idx] + table->root_symbol.value;

    // Table symbols
    port_size_t num_symbols = sizes->num_table_entries;

    if ((num_symbols > 0) && (ptrs->table != NULL))
    {
        assert(sizes->segment_sizes != NULL);
        assert(ptrs->segments != NULL);

        if (!ma_cdev->operations.map_fn(ptrs->table,
                    sizeof(*ptrs->table) * num_symbols, ma_cdev->properties.map))
            return false;

        for (port_size_t i = 0; i < num_symbols; i++)
        {
            assert(table->table_symbols[i].segment_idx < sizes->num_segments);
            assert(table->table_symbols[i].value <=
                    sizes->segment_sizes[table->table_symbols[i].segment_idx]);

            ptrs->table[i] = (char*)ptrs->segments[table->table_symbols[i].segment_idx] +
                table->table_symbols[i].value;
        }

        if (!ma_cdev->operations.unmap_fn(ptrs->table, ma_cdev->properties.map))
            return false;
    }

    return true;
}

port_bool_t
port_kargs_construct_segmented_memory_from_data_storage(
        port_kargs_segmented_memory_ptrs_t *ptrs,
        port_kargs_segmented_memory_sizes_t *sizes,
        port_kargs_segmented_memory_table_t **table,

        const port_data_storage_t *storage,

        const port_memory_allocator_t *ma_host,
        const port_memory_allocator_t *ma_cdev)
{
    assert(ptrs != NULL);
    assert(sizes != NULL);
    assert(table != NULL);
    assert(storage != NULL);
    assert(ma_host != NULL);
    assert(ma_cdev != NULL);

    // Allocate temporary memory arrays
    port_uint8_t step = 0;
    port_bool_t result = false;

    port_size_t num_table_symbols = storage->num.symbols;

    port_kargs_segmented_memory_table_t *table_src = malloc(
            sizeof(*table_src) + sizeof(table_src->table_symbols[0]) * num_table_symbols);
    if (table_src == NULL)
        goto cleanup;

    step++;

    port_size_t num_segments = storage->num.sections;

    port_kargs_segmented_memory_sizes_t sizes_src = {
        .segment_sizes = malloc(sizeof(*sizes->segment_sizes) * num_segments),
        .num_segments = num_segments,
        .num_table_entries = num_table_symbols,
    };
    if (sizes_src.segment_sizes == NULL)
        goto cleanup;

    step++;

    port_kargs_segmented_memory_ptrs_t ptrs_src = {
        .segments = malloc(sizeof(*ptrs->segments) * sizes_src.num_segments),
    };
    if (ptrs_src.segments == NULL)
        goto cleanup;

    step++;

    // Assign temporary memory pointers and values
    table_src->root_symbol = (port_kargs_segmented_memory_symbol_t){0};
    for (port_uint_single_t i = 0; i < storage->num.properties; i++)
        if (!strcmp(storage->content.strings[storage->name_str_idx.properties[i]], "root"))
        {
            if (storage->size.properties[i] == sizeof(port_uint_single_t) * 2)
            {
                port_uint_single_t *root_symbol = storage->content.properties[i];

                table_src->root_symbol = (port_kargs_segmented_memory_symbol_t){
                    .segment_idx = root_symbol[0],
                    .value = root_symbol[1],
                };
            }

            break;
        }

    for (port_size_t i = 0; i < num_table_symbols; i++)
        table_src->table_symbols[i] = (port_kargs_segmented_memory_symbol_t){
            .segment_idx = storage->symbol.section_idx[i],
            .value = storage->symbol.values[i],
        };

    for (port_size_t i = 0; i < num_segments; i++)
    {
        sizes_src.segment_sizes[i] = storage->size.sections[i];
        ptrs_src.segments[i] = storage->content.sections[i];
    }

    // Construct segmented memory
    if (!port_kargs_alloc_copy_segmented_memory_sizes(sizes, &sizes_src, ma_host))
        goto cleanup;

    step++;

    *table = port_kargs_alloc_copy_segmented_memory_table(table_src, num_table_symbols, ma_host);
    if (*table == NULL)
        goto cleanup;

    step++;

    if (!port_kargs_alloc_segmented_memory_arrays(ptrs, &sizes_src, ma_host))
        goto cleanup;

    step++;

    if (!port_kargs_alloc_segmented_memory_memory(ptrs, &sizes_src, ma_cdev))
        goto cleanup;

    step++;

    {
        port_memory_allocator_t ma_cdev_src = {.operations = {
            .map_fn = port_memory_cpu_map, .unmap_fn = port_memory_cpu_unmap}};

        if (!port_kargs_copy_segmented_memory_memory(ptrs, &ptrs_src, &sizes_src, ma_cdev, &ma_cdev_src))
            goto cleanup;
    }

    if (!port_kargs_write_segmented_memory_table(ptrs, &sizes_src, table_src, ma_cdev))
        goto cleanup;

    step = 3; // don't free output resources
    result = true;

    // Clean up resources
cleanup:
    if (step >= 7)
        port_kargs_free_segmented_memory_memory(ptrs, &sizes_src, ma_cdev);
    if (step >= 6)
        port_kargs_free_segmented_memory_arrays(ptrs, &sizes_src, ma_host);
    if (step >= 5)
        port_kargs_free_segmented_memory_table(*table, ma_host);
    if (step >= 4)
        port_kargs_free_segmented_memory_sizes(sizes, ma_host);

    if (step >= 3)
        free(ptrs_src.segments);
    if (step >= 2)
        free(sizes_src.segment_sizes);
    if (step >= 1)
        free(table_src);

    return result;
}

