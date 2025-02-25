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
 * @brief Constants for OpenCL memory handling on host.
 */

#pragma once
#ifndef _PORT_HOST_OPENCL_MEMORY_DEF_H_
#define _PORT_HOST_OPENCL_MEMORY_DEF_H_

#include <port/host/opencl/memory.fun.h>

/**
 * @brief OpenCL memory operations.
 */
#define PORT_MEMORY_ALLOCATOR_OPERATIONS_OPENCL { \
    .alloc_fn = port_memory_opencl_alloc,   \
    .free_fn = port_memory_opencl_free,     \
    .map_fn = port_memory_opencl_map,       \
    .unmap_fn = port_memory_opencl_unmap,   \
}

#endif // _PORT_HOST_OPENCL_MEMORY_DEF_H_

