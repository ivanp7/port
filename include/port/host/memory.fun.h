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
 * @brief Segmented memory operations.
 */

#pragma once
#ifndef _PORT_HOST_MEMORY_FUN_H_
#define _PORT_HOST_MEMORY_FUN_H_

#include <port/cdev/types.typ.h>

struct port_segmented_memory;
struct port_data_storage;
struct port_memory_operations;
struct port_memory_operation_properties;

/**
 * @brief Initialize segmented memory from a data storage.
 *
 * @return True on success, otherwise false.
 */
port_bool_t
port_init_segmented_memory_from_data_storage(
        struct port_segmented_memory *memory, ///< [out] Segmented memory.
        struct port_data_storage *storage, ///< [in] Data storage.

        struct port_memory_operations *op, ///< [in] Memory operations.
        struct port_memory_operation_properties *prop ///< [in] Properties for memory operations.
);

/**
 * @brief Free memory owned by segmented memory and set fields to default values.
 */
void
port_reset_segmented_memory(
        struct port_segmented_memory *memory, ///< [in,out] Segmented memory.

        struct port_memory_operations *op, ///< [in] Memory operations.
        struct port_memory_operation_properties *prop ///< [in] Properties for memory operations.
);

#endif // _PORT_HOST_MEMORY_FUN_H_

