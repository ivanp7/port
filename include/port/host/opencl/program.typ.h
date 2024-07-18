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
typedef struct port_opencl_program_source {
    struct {
        unsigned int num_files;  ///< Number of files.
        const char **file_paths; ///< Paths of files.
        const char **file_contents; ///< File contents.
        size_t *file_sizes; ///< Sizes of files.
    } header, source;
} port_opencl_program_source_t;

#endif // _PORT_HOST_OPENCL_PROGRAM_TYP_H_

