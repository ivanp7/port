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
 * @brief Types for OpenCL program builder.
 */

#pragma once
#ifndef _PORT_HOST_OPENCL_PROGRAM_TYP_H_
#define _PORT_HOST_OPENCL_PROGRAM_TYP_H_

#include <stddef.h>

/**
 * @brief Logically indivisible set of sources for OpenCL program builder.
 */
typedef struct port_opencl_program_sources {
    unsigned int num_headers;  ///< Number of header files.
    const char **header_include_names; ///< #include names of header files.
    const char **headers; ///< Header files.
    size_t *header_sizes; ///< Sizes of header files.

    unsigned int num_sources;  ///< Number of source files.
    const char **source_names; ///< Names of source files.
    const char **sources; ///< Source files.
    size_t *source_sizes; ///< Sizes of source files.
} port_opencl_program_sources_t;

#endif // _PORT_HOST_OPENCL_PROGRAM_TYP_H_

