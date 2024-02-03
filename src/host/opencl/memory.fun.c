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

#include <port/host/opencl/memory.fun.h>
#include <port/host/opencl/memory.typ.h>

#include <CL/cl.h>

port_void_ptr_t
port_memory_opencl_alloc(
        port_size_t num_bytes,
        port_size_t alignment,
        port_void_ptr_t properties)
{
    port_memory_opencl_alloc_properties_t *p = properties;
    if (p == NULL)
        return NULL;

    return clSVMAlloc(p->context, p->svm_mem_flags, num_bytes, alignment);
}

void
port_memory_opencl_free(
        port_void_ptr_t memory,
        port_void_ptr_t properties)
{
    port_memory_opencl_alloc_properties_t *p = properties;
    if (p == NULL)
        return;

    clSVMFree(p->context, memory);
}

port_bool_t
port_memory_opencl_map(
        port_void_ptr_t memory,
        port_size_t num_bytes,
        port_void_ptr_t properties)
{
    port_memory_opencl_map_properties_t *p = properties;
    if (p == NULL)
        return false;

    return CL_SUCCESS == clEnqueueSVMMap(p->command_queue, CL_TRUE, p->map_flags, memory, num_bytes,
            0, (const cl_event*)NULL, (cl_event*)NULL);
}

port_bool_t
port_memory_opencl_unmap(
        port_void_ptr_t memory,
        port_void_ptr_t properties)
{
    port_memory_opencl_map_properties_t *p = properties;
    if (p == NULL)
        return false;

    return CL_SUCCESS == clEnqueueSVMUnmap(p->command_queue, memory,
            0, (const cl_event*)NULL, (cl_event*)NULL);
}

