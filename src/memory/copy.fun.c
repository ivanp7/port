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
 * @brief Functions for copying memory.
 */

#include "port/memory/copy.fun.h"

#ifndef __OPENCL_C_VERSION__
#  include <string.h> // for memcpy()
#  include <assert.h>
#endif

///////////////////////////////////////////////////////////////////////////////
// Generic memory
///////////////////////////////////////////////////////////////////////////////

void
port_memory_copy(
        port_void_ptr_t restrict dest,
        port_const_void_ptr_t restrict src,
        size_t num_bytes)
{
#ifdef __OPENCL_C_VERSION__
    for (size_t i = 0; i < num_bytes; i++)
        ((char*)dest)[i] = ((const char*)src)[i];
#else
    assert(dest != NULL);
    assert(src != NULL);

    memcpy(dest, src, num_bytes);
#endif
}

#ifdef __OPENCL_C_VERSION__

///////////////////////////////////////////////////////////////////////////////
// Private source
///////////////////////////////////////////////////////////////////////////////

void
port_memory_copy_private_to_private(
        port_private_void_ptr_t restrict dest,
        port_const_private_void_ptr_t restrict src,
        size_t num_bytes)
{
    for (size_t i = 0; i < num_bytes; i++)
        ((__private char*)dest)[i] = ((const __private char*)src)[i];
}

void
port_memory_copy_private_to_local(
        port_local_void_ptr_t restrict dest,
        port_const_private_void_ptr_t restrict src,
        size_t num_bytes)
{
    for (size_t i = 0; i < num_bytes; i++)
        ((__local char*)dest)[i] = ((const __private char*)src)[i];
}

void
port_memory_copy_private_to_global(
        port_global_void_ptr_t restrict dest,
        port_const_private_void_ptr_t restrict src,
        size_t num_bytes)
{
    for (size_t i = 0; i < num_bytes; i++)
        ((__global char*)dest)[i] = ((const __private char*)src)[i];
}

///////////////////////////////////////////////////////////////////////////////
// Local source
///////////////////////////////////////////////////////////////////////////////

void
port_memory_copy_local_to_private(
        port_private_void_ptr_t restrict dest,
        port_const_local_void_ptr_t restrict src,
        size_t num_bytes)
{
    for (size_t i = 0; i < num_bytes; i++)
        ((__private char*)dest)[i] = ((const __local char*)src)[i];
}

void
port_memory_copy_local_to_local(
        port_local_void_ptr_t restrict dest,
        port_const_local_void_ptr_t restrict src,
        size_t num_bytes)
{
    for (size_t i = 0; i < num_bytes; i++)
        ((__local char*)dest)[i] = ((const __local char*)src)[i];
}

void
port_memory_copy_local_to_global(
        port_global_void_ptr_t restrict dest,
        port_const_local_void_ptr_t restrict src,
        size_t num_bytes)
{
    for (size_t i = 0; i < num_bytes; i++)
        ((__global char*)dest)[i] = ((const __local char*)src)[i];
}

///////////////////////////////////////////////////////////////////////////////
// Global source
///////////////////////////////////////////////////////////////////////////////

void
port_memory_copy_global_to_private(
        port_private_void_ptr_t restrict dest,
        port_const_global_void_ptr_t restrict src,
        size_t num_bytes)
{
    for (size_t i = 0; i < num_bytes; i++)
        ((__private char*)dest)[i] = ((const __global char*)src)[i];
}

void
port_memory_copy_global_to_local(
        port_local_void_ptr_t restrict dest,
        port_const_global_void_ptr_t restrict src,
        size_t num_bytes)
{
    for (size_t i = 0; i < num_bytes; i++)
        ((__local char*)dest)[i] = ((const __global char*)src)[i];
}

void
port_memory_copy_global_to_global(
        port_global_void_ptr_t restrict dest,
        port_const_global_void_ptr_t restrict src,
        size_t num_bytes)
{
    for (size_t i = 0; i < num_bytes; i++)
        ((__global char*)dest)[i] = ((const __global char*)src)[i];
}

///////////////////////////////////////////////////////////////////////////////
// Constant source
///////////////////////////////////////////////////////////////////////////////

void
port_memory_copy_constant_to_private(
        port_private_void_ptr_t restrict dest,
        port_constant_void_ptr_t restrict src,
        size_t num_bytes)
{
    for (size_t i = 0; i < num_bytes; i++)
        ((__private char*)dest)[i] = ((const __constant char*)src)[i];
}

void
port_memory_copy_constant_to_local(
        port_local_void_ptr_t restrict dest,
        port_constant_void_ptr_t restrict src,
        size_t num_bytes)
{
    for (size_t i = 0; i < num_bytes; i++)
        ((__local char*)dest)[i] = ((const __constant char*)src)[i];
}

void
port_memory_copy_constant_to_global(
        port_global_void_ptr_t restrict dest,
        port_constant_void_ptr_t restrict src,
        size_t num_bytes)
{
    for (size_t i = 0; i < num_bytes; i++)
        ((__global char*)dest)[i] = ((const __constant char*)src)[i];
}

#endif // __OPENCL_C_VERSION__

