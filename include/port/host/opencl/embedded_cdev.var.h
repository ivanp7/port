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
 * @brief Embedded compute device specific code.
 */

#pragma once
#ifndef _PORT_HOST_OPENCL_EMBEDDED_CDEV_VAR_H_
#define _PORT_HOST_OPENCL_EMBEDDED_CDEV_VAR_H_

#include <stddef.h>

extern const unsigned int port_embedded_cdev_num_headers;           ///< Number of header files.
extern const char *const port_embedded_cdev_header_include_names[]; ///< #include names of header files.
extern const char *const port_embedded_cdev_headers[];              ///< Header files.
extern const size_t port_embedded_cdev_header_sizes[];              ///< Sizes of header files.

extern const unsigned int port_embedded_cdev_num_sources;   ///< Number of source files.
extern const char *const port_embedded_cdev_source_names[]; ///< Names of source files.
extern const char *const port_embedded_cdev_sources[];      ///< Source files.
extern const size_t port_embedded_cdev_source_sizes[];      ///< Sizes of source files.

#endif // _PORT_HOST_OPENCL_EMBEDDED_CDEV_VAR_H_

