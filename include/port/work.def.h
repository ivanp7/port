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
 * @brief Macros for work-item counting.
 */

#pragma once
#ifndef _PORT_WORK_DEF_H_
#define _PORT_WORK_DEF_H_

#include "port/work.typ.h"

#ifdef __OPENCL_C_VERSION__

#  define PORT_WORK_ITEM_INDEX_PARAMETER(work_item_idx) // nothing

/**
 * @brief Define and initialize kernel function local variable for work-item index.
 */
#  define PORT_WORK_ITEM_INDEX_INITIALIZE(work_item_idx) \
    port_work_item_index_t work_item_idx = get_global_id(0)

#else

/**
 * @brief Declare kernel function parameter for work-item index.
 */
#  define PORT_WORK_ITEM_INDEX_PARAMETER(work_item_idx) \
    , port_work_item_index_t work_item_idx

#  define PORT_WORK_ITEM_INDEX_INITIALIZE(work_item_idx) // nothing

#endif

#endif // _PORT_WORK_DEF_H_

