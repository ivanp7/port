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
 * @brief Constants for OpenCL program builder.
 */

#pragma once
#ifndef _PORT_HOST_OPENCL_PROGRAM_DEF_H_
#define _PORT_HOST_OPENCL_PROGRAM_DEF_H_

#define PORT_OPENCL_CFLAGS_DEFAULT "-cl-std=CL3.0" ///< Default OpenCL compiler flags.
#define PORT_OPENCL_LFLAGS_DEFAULT ""              ///< Default OpenCL linker flags.

#define PORT_OPENCL_CFLAGS_FEATURE_DEFAULT_INTEGER_64 "-D PORT_FEATURE_DEFAULT_INTEGER_64" ///< Set default integer type size to 64 bits.
#define PORT_OPENCL_CFLAGS_FEATURE_DEFAULT_FLOAT_64   "-D PORT_FEATURE_DEFAULT_FLOAT_64"   ///< Set default floating-point type size to 64 bits.

#endif // _PORT_HOST_OPENCL_PROGRAM_DEF_H_

