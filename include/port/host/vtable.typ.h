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
 * @brief Type of vtable structure for libraries using Port.
 */

#pragma once
#ifndef _PORT_HOST_VTABLE_TYP_H_
#define _PORT_HOST_VTABLE_TYP_H_

#include <port/host/kernel.typ.h>
#include <port/host/cpu/pfunc.typ.h>
#include <port/host/opencl/kargs_setter.typ.h>

struct port_opencl_program_source;

/**
 * @brief Kernel function description for vtable structure.
 */
typedef struct port_vtable_kernel_description {
    char *kernel_name; ///< Kernel name.

    port_size_t work_type; ///< Type of work done by the kernel.

    struct {
        port_pfunc_t pfunc; ///< Concurrent processing function.
    } cpu; ///< Kernel description for CPU.

    struct {
        port_kargs_setter_t kargs_setter_fn; ///< Kernel arguments setter function.

        cl_ulong arg_mask_in;  ///< Mask of kernel input arguments.
        cl_ulong arg_mask_out; ///< Mask of kernel output arguments.
    } opencl; ///< Kernel description for OpenCL.
} port_vtable_kernel_description_t;

/**
 * @brief Vtable structure for libraries using Port.
 */
typedef struct port_vtable {
    port_uint32_t magic;   ///< Value uniquely identifying Port vtable structure.
    port_uint32_t version; ///< Value determining vtable version and compatibility.

    port_kargs_operations_t kargs_operations; ///< Operations on kernel arguments.
    port_vtable_kernel_description_t *kernel_descriptions; ///< Descriptions of kernels provided by the library.

    struct {
        struct port_opencl_program_source **program_sources; ///< Array of OpenCL program sources.
    } opencl; ///< OpenCL-related resources.
} port_vtable_t;

#endif // _PORT_HOST_VTABLE_TYP_H_

