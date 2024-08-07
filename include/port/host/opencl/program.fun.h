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
 * @brief OpenCL program builder.
 */

#pragma once
#ifndef _PORT_HOST_OPENCL_PROGRAM_FUN_H_
#define _PORT_HOST_OPENCL_PROGRAM_FUN_H_

#include <CL/cl.h>
#include <stdio.h>

struct port_opencl_program_source;

/**
 * @brief Allocate and concatenate string of compiler/linker flags.
 *
 * @return Allocated string of OpenCL compiler/linker flags.
 */
const char*
port_opencl_concat_flags(
        const char *flags[] ///< [in] Strings to concatenate.
);

/**
 * @brief Create, compile and link OpenCL program.
 *
 * @return OpenCL program object.
 */
cl_program
port_opencl_build_program(
        cl_context context,  ///< [in] Valid OpenCL context.
        cl_uint num_devices, ///< [in] Number of devices listed in the device list.
        const cl_device_id *device_list, ///< [in] List of devices to build the program for.

        cl_uint num_inputs, ///< [in] Number of input sets of sources.
        const struct port_opencl_program_source *inputs[], ///< [in] Input sets of sources.

        cl_uint num_libraries,        ///< [in] Number of linked libraries.
        const cl_program libraries[], ///< [in] Libraries to link.

        const char *cflags, ///< [in] Compiler flags.
        const char *lflags, ///< [in] Linker flags.

        FILE *stream, ///< [out] Stream to log program build process into, or NULL.
        cl_int *error ///< [out] Address to put error code into, or NULL.
);

#endif // _PORT_HOST_OPENCL_PROGRAM_FUN_H_

