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
 * @brief Type of kernel arguments setter functions.
 */

#pragma once
#ifndef _PORT_HOST_OPENCL_KARGS_SETTER_TYP_H_
#define _PORT_HOST_OPENCL_KARGS_SETTER_TYP_H_

#include <port/cdev/memory.typ.h>

#include <CL/cl.h>

/**
 * @brief Arguments setter function for an OpenCL kernel.
 *
 * arg_mask specifies which kernel arguments to set.
 *
 * @return CL_SUCCESS or error code returned by clSetKernelArg(),
 * clSetKernelArgSVMPointer(), or clSetKernelExecInfo().
 */
typedef cl_int (*port_kargs_setter_t)(
        cl_kernel kernel,  ///< [in] OpenCL kernel.
        cl_ulong arg_mask, ///< [in] Mask of kernel arguments to set.
        port_const_void_ptr_t data ///< [in] Data for kernel arguments.
);

/**
 * @brief Description of kernel arguments setter function.
 */
typedef struct port_kargs_setter_description {
    const char *kernel_name; ///< OpenCL kernel name.

    port_kargs_setter_t func; ///< Kernel arguments setter function.
    cl_ulong arg_mask_in;  ///< Mask of kernel input arguments.
    cl_ulong arg_mask_out; ///< Mask of kernel output arguments.
} port_kargs_setter_description_t;

#endif // _PORT_HOST_OPENCL_KARGS_SETTER_TYP_H_

