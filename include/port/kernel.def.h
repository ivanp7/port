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
 * @brief Macros for kernel functions.
 */

#pragma once
#ifndef _PORT_KERNEL_DEF_H_
#define _PORT_KERNEL_DEF_H_

#include "port/keywords.def.h"

#ifndef __OPENCL_C_VERSION__
#  include "archi/res_thread/api/work.typ.h" // for ARCHI_THREAD_GROUP_WORK_FUNC()
#endif

/**
 * @brief Kernel function return type.
 */
#define PORT_KERNEL  PORT_KW_KERNEL void

#ifndef __OPENCL_C_VERSION__

/**
 * @brief Kernel wrapper function for concurrent processing on CPU.
 */
#  define PORT_KERNEL_WRAPPER_FUNC(name)  ARCHI_THREAD_GROUP_WORK_FUNC(name)

#endif

#endif // _PORT_KERNEL_DEF_H_

