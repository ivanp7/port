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
 * @brief Types for memory operations.
 */

#pragma once
#ifndef _PORT_HOST_OPENCL_MEMORY_TYP_H_
#define _PORT_HOST_OPENCL_MEMORY_TYP_H_

#include <CL/cl.h>

/**
 * @brief OpenCL memory allocator properties.
 */
typedef struct port_memory_opencl_alloc_properties {
    cl_context context;
    cl_svm_mem_flags svm_mem_flags;
} port_memory_opencl_alloc_properties_t;

/**
 * @brief OpenCL memory mapping properties.
 */
typedef struct port_memory_opencl_map_properties {
    cl_command_queue command_queue;
    cl_map_flags map_flags;
} port_memory_opencl_map_properties_t;

#endif // _PORT_HOST_OPENCL_MEMORY_TYP_H_

