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
 * @brief Memory operations on host.
 */

#include <port/host/memory.fun.h>
#include <port/host/memory.typ.h>

#include <assert.h>
#include <string.h>

port_bool_t
port_memory_map_copy_unmap(
        port_void_ptr_t mem_dest,
        port_const_void_ptr_t mem_src,

        port_size_t size,

        const port_memory_allocator_t *ma_dest,
        const port_memory_allocator_t *ma_src)
{
    assert(mem_dest != NULL);
    assert(mem_src != NULL);
    assert(ma_dest != NULL);
    assert(ma_dest->operations.map_fn != NULL);
    assert(ma_dest->operations.unmap_fn != NULL);
    assert(ma_src != NULL);
    assert(ma_src->operations.map_fn != NULL);
    assert(ma_src->operations.unmap_fn != NULL);

    if (size == 0)
        return true;

    if (!ma_src->operations.map_fn((port_void_ptr_t)mem_src, size, ma_src->properties.map))
        return false;

    if (!ma_dest->operations.map_fn(mem_dest, size, ma_dest->properties.map))
    {
#ifndef NDEBUG
        port_bool_t result =
#endif
            ma_src->operations.unmap_fn((port_void_ptr_t)mem_src, ma_src->properties.map); // attempt to undo previous map_fn() call
        assert(result == true);

        return false;
    }

    memcpy(mem_dest, mem_src, size);

#ifndef NDEBUG
    port_bool_t result =
#endif
        ma_dest->operations.unmap_fn(mem_dest, ma_dest->properties.map);
    assert(result == true);

#ifndef NDEBUG
    result =
#endif
        ma_src->operations.unmap_fn((port_void_ptr_t)mem_src, ma_src->properties.map);
    assert(result == true);

    return true;
}

