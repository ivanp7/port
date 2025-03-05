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
 * @brief Memory operations on host.
 */

#pragma once
#ifndef _PORT_HOST_MEMORY_FUN_H_
#define _PORT_HOST_MEMORY_FUN_H_

#include "port/cdev/memory.typ.h"

struct port_memory_allocator;

/**
 * @brief Map, copy, unmap memory contents.
 *
 * Memory regions must not overlap.
 *
 * @return True on success, otherwise false.
 */
port_bool_t
port_memory_map_copy_unmap(
        port_void_ptr_t mem_dest,      ///< [out] Destination memory.
        port_const_void_ptr_t mem_src, ///< [in] Source memory.

        port_size_t size, ///< [in] Number of copied bytes.

        const struct port_memory_allocator *ma_dest, ///< [in] Memory allocator (destination).
        const struct port_memory_allocator *ma_src   ///< [in] Memory allocator (source).
);

#endif // _PORT_HOST_MEMORY_FUN_H_

