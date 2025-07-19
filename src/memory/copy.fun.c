/****************************************************************************
 * Copyright (C) 2020-2025 by Ivan Podmazov                                 *
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
 * @brief Memory copy operations.
 */

#include "port/memory/copy.fun.h"

#ifndef __OPENCL_C_VERSION__
#  include <string.h> // for memcpy()
#  include <assert.h>
#endif

#ifdef __OPENCL_C_VERSION__

#  define MEMCPY_IMPL \
    for (size_t i = 0; i < num_units; i++) dest[i] = src[i];

#else

#  define MEMCPY_IMPL     \
    assert(dest != NULL); \
    assert(src != NULL);  \
    memcpy(dest, src, sizeof(port_memory_unit_t) * num_units);

#endif

void
port_memory_copy_global_to_private(
        port_private_memory_ptr_t restrict dest,
        port_const_global_memory_ptr_t restrict src,
        size_t num_units)
{
    MEMCPY_IMPL
}

void
port_memory_copy_constant_to_private(
        port_private_memory_ptr_t restrict dest,
        port_constant_memory_ptr_t restrict src,
        size_t num_units)
{
    MEMCPY_IMPL
}

void
port_memory_copy_local_to_private(
        port_private_memory_ptr_t restrict dest,
        port_const_local_memory_ptr_t restrict src,
        size_t num_units)
{
    MEMCPY_IMPL
}

void
port_memory_copy_private_to_private(
        port_private_memory_ptr_t restrict dest,
        port_const_private_memory_ptr_t restrict src,
        size_t num_units)
{
    MEMCPY_IMPL
}

void
port_memory_copy_global_to_local(
        port_local_memory_ptr_t restrict dest,
        port_const_global_memory_ptr_t restrict src,
        size_t num_units)
{
    MEMCPY_IMPL
}

void
port_memory_copy_constant_to_local(
        port_local_memory_ptr_t restrict dest,
        port_constant_memory_ptr_t restrict src,
        size_t num_units)
{
    MEMCPY_IMPL
}

void
port_memory_copy_local_to_local(
        port_local_memory_ptr_t restrict dest,
        port_const_local_memory_ptr_t restrict src,
        size_t num_units)
{
    MEMCPY_IMPL
}

void
port_memory_copy_private_to_local(
        port_local_memory_ptr_t restrict dest,
        port_const_private_memory_ptr_t restrict src,
        size_t num_units)
{
    MEMCPY_IMPL
}

void
port_memory_copy_global_to_global(
        port_global_memory_ptr_t restrict dest,
        port_const_global_memory_ptr_t restrict src,
        size_t num_units)
{
    MEMCPY_IMPL
}

void
port_memory_copy_local_to_global(
        port_global_memory_ptr_t restrict dest,
        port_const_local_memory_ptr_t restrict src,
        size_t num_units)
{
    MEMCPY_IMPL
}

void
port_memory_copy_constant_to_global(
        port_global_memory_ptr_t restrict dest,
        port_constant_memory_ptr_t restrict src,
        size_t num_units)
{
    MEMCPY_IMPL
}

void
port_memory_copy_private_to_global(
        port_global_memory_ptr_t restrict dest,
        port_const_private_memory_ptr_t restrict src,
        size_t num_units)
{
    MEMCPY_IMPL
}

