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
 * @brief Macros for concurrent processing functions.
 */

#pragma once
#ifndef _PORT_HOST_CPU_PFUNC_DEF_H_
#define _PORT_HOST_CPU_PFUNC_DEF_H_

/**
 * @brief Declarator of a concurrent processing function.
 *
 * See description of port_pfunc_t type.
 */
#define PORT_PFUNC(name) \
    void name(port_void_ptr_t data, port_uint32_t work_item_idx, port_uint16_t thread_idx)

#endif // _PORT_HOST_CPU_PFUNC_DEF_H_

