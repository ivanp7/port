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
 * @brief Type of concurrent processing functions.
 */

#pragma once
#ifndef _PORT_HOST_CPU_PFUNC_TYP_H_
#define _PORT_HOST_CPU_PFUNC_TYP_H_

#include <port/cdev/memory.typ.h>

/**
 * @brief Concurrent processing function.
 *
 * This function type is guaranteed to be equivalent to station_pfunc_t from Station library.
 */
typedef void (*port_pfunc_t)(
        port_void_ptr_t data,        ///< [in,out] Processed data.
        port_uint32_t work_item_idx, ///< [in] Index of the current work item.
        port_uint16_t thread_idx     ///< [in] Index of the current thread.
);

#endif // _PORT_HOST_CPU_PFUNC_TYP_H_

