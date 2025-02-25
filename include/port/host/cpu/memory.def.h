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
 * @brief Constants for CPU memory handling on host.
 */

#pragma once
#ifndef _PORT_HOST_CPU_MEMORY_DEF_H_
#define _PORT_HOST_CPU_MEMORY_DEF_H_

#include <port/host/cpu/memory.fun.h>

/**
 * @brief CPU memory operations.
 */
#define PORT_MEMORY_ALLOCATOR_OPERATIONS_CPU { \
    .alloc_fn = port_memory_cpu_alloc,  \
    .free_fn = port_memory_cpu_free,    \
    .map_fn = port_memory_cpu_map,      \
    .unmap_fn = port_memory_cpu_unmap,  \
}

#endif // _PORT_HOST_CPU_MEMORY_DEF_H_

