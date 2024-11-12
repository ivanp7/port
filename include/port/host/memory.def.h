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
 * @brief Constants for memory handling on host.
 */

#pragma once
#ifndef _PORT_HOST_MEMORY_DEF_H_
#define _PORT_HOST_MEMORY_DEF_H_

#include <port/cdev/memory.typ.h>

#include <stdalign.h>

/**
 * @brief Alignment of largest data type supported by OpenCL.
 */
#define PORT_ALIGNMENT_MAX alignof(port_uint64_v16_t)

#endif // _PORT_HOST_MEMORY_DEF_H_

