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
 * @brief Functions for memory operations.
 */

#include <port/host/cpu/memory.fun.h>

#include <stdlib.h>

port_memory_ptr_t
port_memory_cpu_alloc(
        port_size_t num_bytes,
        port_size_t alignment,
        port_void_ptr_t properties)
{
    (void) properties;

    if (num_bytes == 0)
        return NULL;

    if (alignment == 0)
        return malloc(num_bytes);
    else
        return aligned_alloc(alignment, num_bytes);
}

void
port_memory_cpu_free(
        port_memory_ptr_t memory,
        port_void_ptr_t properties)
{
    (void) properties;

    free(memory);
}

port_bool_t
port_memory_cpu_map(
        port_memory_ptr_t memory,
        port_size_t num_bytes,
        port_void_ptr_t properties)
{
    (void) memory;
    (void) num_bytes;
    (void) properties;

    return true;
}

port_bool_t
port_memory_cpu_unmap(
        port_memory_ptr_t memory,
        port_void_ptr_t properties)
{
    (void) memory;
    (void) properties;

    return true;
}

