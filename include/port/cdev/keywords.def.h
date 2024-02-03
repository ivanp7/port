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
 * @brief Portable macros for programming language keywords.
 */

#pragma once
#ifndef _PORT_CDEV_KEYWORDS_DEF_H_
#define _PORT_CDEV_KEYWORDS_DEF_H_

#ifdef __OPENCL_C_VERSION__

/**
 * @brief OpenCL C __global keyword.
 */
#  define PORT_KW_GLOBAL __global
/**
 * @brief OpenCL C __constant keyword.
 */
#  define PORT_KW_CONSTANT __constant
/**
 * @brief OpenCL C __local keyword.
 */
#  define PORT_KW_LOCAL __local
/**
 * @brief OpenCL C __private keyword.
 */
#  define PORT_KW_PRIVATE __private

/**
 * @brief OpenCL C __read_only keyword.
 */
#  define PORT_KW_READ_ONLY __read_only
/**
 * @brief OpenCL C __write_only keyword.
 */
#  define PORT_KW_WRITE_ONLY __write_only
/**
 * @brief OpenCL C __read_write keyword.
 */
#  define PORT_KW_READ_WRITE __read_write

/**
 * @brief OpenCL C __kernel keyword.
 */
#  define PORT_KW_KERNEL __kernel

#else

#  define PORT_KW_GLOBAL
#  define PORT_KW_CONSTANT
#  define PORT_KW_LOCAL
#  define PORT_KW_PRIVATE

#  define PORT_KW_READ_ONLY
#  define PORT_KW_WRITE_ONLY
#  define PORT_KW_READ_WRITE

#  define PORT_KW_KERNEL

#endif

#endif // _PORT_CDEV_KEYWORDS_DEF_H_

