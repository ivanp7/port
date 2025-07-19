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
 * @brief Memory copy operations.
 */

#pragma once
#ifndef _PORT_MEMORY_COPY_FUN_H_
#define _PORT_MEMORY_COPY_FUN_H_

#include "port/memory.typ.h"

/**
 * @brief Copy memory units from global memory to private memory.
 */
void
port_memory_copy_global_to_private(
        port_private_memory_ptr_t restrict dest, ///< [out] Destination.
        port_const_global_memory_ptr_t restrict src, ///< [in] Source.
        size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from constant memory to private memory.
 */
void
port_memory_copy_constant_to_private(
        port_private_memory_ptr_t restrict dest, ///< [out] Destination.
        port_constant_memory_ptr_t restrict src, ///< [in] Source.
        size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from local memory to private memory.
 */
void
port_memory_copy_local_to_private(
        port_private_memory_ptr_t restrict dest, ///< [out] Destination.
        port_const_local_memory_ptr_t restrict src, ///< [in] Source.
        size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from private memory to private memory.
 */
void
port_memory_copy_private_to_private(
        port_private_memory_ptr_t restrict dest, ///< [out] Destination.
        port_const_private_memory_ptr_t restrict src, ///< [in] Source.
        size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from global memory to local memory.
 */
void
port_memory_copy_global_to_local(
        port_local_memory_ptr_t restrict dest, ///< [out] Destination.
        port_const_global_memory_ptr_t restrict src, ///< [in] Source.
        size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from constant memory to local memory.
 */
void
port_memory_copy_constant_to_local(
        port_local_memory_ptr_t restrict dest, ///< [out] Destination.
        port_constant_memory_ptr_t restrict src, ///< [in] Source.
        size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from local memory to local memory.
 */
void
port_memory_copy_local_to_local(
        port_local_memory_ptr_t restrict dest, ///< [out] Destination.
        port_const_local_memory_ptr_t restrict src, ///< [in] Source.
        size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from private memory to local memory.
 */
void
port_memory_copy_private_to_local(
        port_local_memory_ptr_t restrict dest, ///< [out] Destination.
        port_const_private_memory_ptr_t restrict src, ///< [in] Source.
        size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from global memory to global memory.
 */
void
port_memory_copy_global_to_global(
        port_global_memory_ptr_t restrict dest, ///< [out] Destination.
        port_const_global_memory_ptr_t restrict src, ///< [in] Source.
        size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from local memory to global memory.
 */
void
port_memory_copy_local_to_global(
        port_global_memory_ptr_t restrict dest, ///< [out] Destination.
        port_const_local_memory_ptr_t restrict src, ///< [in] Source.
        size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from constant memory to global memory.
 */
void
port_memory_copy_constant_to_global(
        port_global_memory_ptr_t restrict dest, ///< [out] Destination.
        port_constant_memory_ptr_t restrict src, ///< [in] Source.
        size_t num_units ///< [in] Number of units to copy.
);

/**
 * @brief Copy memory units from private memory to global memory.
 */
void
port_memory_copy_private_to_global(
        port_global_memory_ptr_t restrict dest, ///< [out] Destination.
        port_const_private_memory_ptr_t restrict src, ///< [in] Source.
        size_t num_units ///< [in] Number of units to copy.
);

#endif // _PORT_MEMORY_COPY_FUN_H_

