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
 * @brief Macros for kernel arguments setter functions.
 */

#pragma once
#ifndef _PORT_HOST_OPENCL_KARGS_SETTER_DEF_H_
#define _PORT_HOST_OPENCL_KARGS_SETTER_DEF_H_

/**
 * @brief Declarator for an arguments setter for an OpenCL kernel.
 *
 * See description of port_kargs_setter_t type.
 */
#define PORT_KARGS_SETTER(name) \
    cl_int name(cl_kernel kernel, cl_ulong arg_mask, port_const_void_ptr_t data)

#endif // _PORT_HOST_OPENCL_KARGS_SETTER_DEF_H_

