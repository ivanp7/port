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
 * @brief Segmented memory operations.
 */

#include <port/host/memory.fun.h>
#include <port/host/memory.typ.h>
#include <port/host/storage.typ.h>

#include <string.h>

port_bool_t
port_init_segmented_memory_from_data_storage(
        port_segmented_memory_t *memory,
        port_data_storage_t *storage,

        const port_memory_operations_t *op,
        const port_memory_operation_properties_t *prop)
{
    if ((memory == NULL) || (storage == NULL) || (op == NULL) || (prop == NULL))
        return false;
    else if ((op->alloc_fn == NULL) || (op->free_fn == NULL) || (op->map_fn == NULL) || (op->unmap_fn == NULL))
        return false;

    port_segmented_memory_t mem = {0};

    // Copy sections -> segments
    mem.num_segments = storage->num.sections;
    mem.segments = malloc(sizeof(*mem.segments) * mem.num_segments);
    if (mem.segments == NULL)
        goto failure;
    for (port_size_t i = 0; i < mem.num_segments; i++)
        mem.segments[i] = NULL;

    for (port_size_t i = 0; i < mem.num_segments; i++)
    {
        if (storage->size.sections[i] == 0)
            continue;

        mem.segments[i] = op->alloc_fn(storage->size.sections[i], 0, prop->alloc_properties);
        if (mem.segments[i] == NULL)
            goto failure;

        if (!op->map_fn(mem.segments[i], storage->size.sections[i], prop->map_properties))
            goto failure;

        memcpy(mem.segments[i], storage->content.sections[i], storage->size.sections[i]);

        if (!op->unmap_fn(mem.segments[i], prop->map_properties))
            goto failure;
    }

    // First symbol is a root pointer
    if (storage->num.symbols > 0)
    {
        port_uint_single_t symbol_section_idx = storage->symbol.section_idx[0];
        port_uint_single_t symbol_value = storage->symbol.values[0];
        port_uint_single_t section_size = storage->size.sections[symbol_section_idx];

        if ((symbol_section_idx >= storage->num.sections) || (symbol_value > section_size))
            goto failure;

        if (symbol_value < section_size)
            mem.root = (char*)storage->content.sections[symbol_section_idx] + symbol_value;
    }

    // The rest symbols are a memory table
    if (storage->num.symbols > 1)
    {
        port_size_t table_size = sizeof(*mem.table) * (storage->num.symbols - 1);

        mem.table = op->alloc_fn(table_size, 0, prop->alloc_properties);
        if (mem.table == NULL)
            goto failure;

        if (!op->map_fn(mem.table, table_size, prop->map_properties))
            goto failure;

        for (port_uint_single_t i = 1; i < storage->num.symbols; i++)
        {
            port_uint_single_t symbol_section_idx = storage->symbol.section_idx[i];
            port_uint_single_t symbol_value = storage->symbol.values[i];
            port_uint_single_t section_size = storage->size.sections[symbol_section_idx];

            if ((symbol_section_idx >= storage->num.sections) || (symbol_value > section_size))
                goto failure;

            if (symbol_value < section_size)
                mem.table[i - 1] = (char*)storage->content.sections[symbol_section_idx] + symbol_value;
        }

        if (!op->unmap_fn(mem.table, prop->map_properties))
            goto failure;
    }

    *memory = mem;

    return true;

failure:
    port_reset_segmented_memory(&mem, op, prop);
    return false;
}

void
port_reset_segmented_memory(
        port_segmented_memory_t *memory,

        const port_memory_operations_t *op,
        const port_memory_operation_properties_t *prop)
{
    if ((memory == NULL) || (op == NULL) || (prop == NULL))
        return;
    else if (op->free_fn == NULL)
        return;

    op->free_fn(memory->table, prop->alloc_properties);

    if (memory->segments != NULL)
    {
        for (port_size_t i = 0; i < memory->num_segments; i++)
            op->free_fn(memory->segments[i], prop->alloc_properties);

        free(memory->segments);
    }

    *memory = (port_segmented_memory_t){0};
}

