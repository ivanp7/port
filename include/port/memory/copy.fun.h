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
 * @brief Functions for copying memory.
 */

#pragma once
#ifndef _PORT_MEMORY_COPY_FUN_H_
#define _PORT_MEMORY_COPY_FUN_H_

#include "port/pointer.typ.h"

///////////////////////////////////////////////////////////////////////////////
// Generic memory
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Copy bytes from generic memory to generic memory.
 */
void
port_memory_copy(
        port_void_ptr_t restrict dest, ///< [in] Destination.
        port_const_void_ptr_t restrict src, ///< [in] Source.
        size_t num_bytes ///< [in] Number of bytes to copy.
);

#ifdef __OPENCL_C_VERSION__

///////////////////////////////////////////////////////////////////////////////
// Private source
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Copy bytes from private memory to private memory.
 */
void
port_memory_copy_private_to_private(
        port_private_void_ptr_t restrict dest, ///< [in] Destination.
        port_const_private_void_ptr_t restrict src, ///< [in] Source.
        size_t num_bytes ///< [in] Number of bytes to copy.
);

/**
 * @brief Copy bytes from private memory to local memory.
 */
void
port_memory_copy_private_to_local(
        port_local_void_ptr_t restrict dest, ///< [in] Destination.
        port_const_private_void_ptr_t restrict src, ///< [in] Source.
        size_t num_bytes ///< [in] Number of bytes to copy.
);

/**
 * @brief Copy bytes from private memory to global memory.
 */
void
port_memory_copy_private_to_global(
        port_global_void_ptr_t restrict dest, ///< [in] Destination.
        port_const_private_void_ptr_t restrict src, ///< [in] Source.
        size_t num_bytes ///< [in] Number of bytes to copy.
);

///////////////////////////////////////////////////////////////////////////////
// Local source
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Copy bytes from local memory to private memory.
 */
void
port_memory_copy_local_to_private(
        port_private_void_ptr_t restrict dest, ///< [in] Destination.
        port_const_local_void_ptr_t restrict src, ///< [in] Source.
        size_t num_bytes ///< [in] Number of bytes to copy.
);

/**
 * @brief Copy bytes from local memory to local memory.
 */
void
port_memory_copy_local_to_local(
        port_local_void_ptr_t restrict dest, ///< [in] Destination.
        port_const_local_void_ptr_t restrict src, ///< [in] Source.
        size_t num_bytes ///< [in] Number of bytes to copy.
);

/**
 * @brief Copy bytes from local memory to global memory.
 */
void
port_memory_copy_local_to_global(
        port_global_void_ptr_t restrict dest, ///< [in] Destination.
        port_const_local_void_ptr_t restrict src, ///< [in] Source.
        size_t num_bytes ///< [in] Number of bytes to copy.
);

///////////////////////////////////////////////////////////////////////////////
// Global source
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Copy bytes from global memory to private memory.
 */
void
port_memory_copy_global_to_private(
        port_private_void_ptr_t restrict dest, ///< [in] Destination.
        port_const_global_void_ptr_t restrict src, ///< [in] Source.
        size_t num_bytes ///< [in] Number of bytes to copy.
);

/**
 * @brief Copy bytes from global memory to local memory.
 */
void
port_memory_copy_global_to_local(
        port_local_void_ptr_t restrict dest, ///< [in] Destination.
        port_const_global_void_ptr_t restrict src, ///< [in] Source.
        size_t num_bytes ///< [in] Number of bytes to copy.
);

/**
 * @brief Copy bytes from global memory to global memory.
 */
void
port_memory_copy_global_to_global(
        port_global_void_ptr_t restrict dest, ///< [in] Destination.
        port_const_global_void_ptr_t restrict src, ///< [in] Source.
        size_t num_bytes ///< [in] Number of bytes to copy.
);

///////////////////////////////////////////////////////////////////////////////
// Constant source
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Copy bytes from constant memory to private memory.
 */
void
port_memory_copy_constant_to_private(
        port_private_void_ptr_t restrict dest, ///< [in] Destination.
        port_constant_void_ptr_t restrict src, ///< [in] Source.
        size_t num_bytes ///< [in] Number of bytes to copy.
);

/**
 * @brief Copy bytes from constant memory to local memory.
 */
void
port_memory_copy_constant_to_local(
        port_local_void_ptr_t restrict dest, ///< [in] Destination.
        port_constant_void_ptr_t restrict src, ///< [in] Source.
        size_t num_bytes ///< [in] Number of bytes to copy.
);

/**
 * @brief Copy bytes from constant memory to global memory.
 */
void
port_memory_copy_constant_to_global(
        port_global_void_ptr_t restrict dest, ///< [in] Destination.
        port_constant_void_ptr_t restrict src, ///< [in] Source.
        size_t num_bytes ///< [in] Number of bytes to copy.
);

#else // __OPENCL_C_VERSION__

#  define port_memory_copy_private_to_private   port_memory_copy
#  define port_memory_copy_private_to_local     port_memory_copy
#  define port_memory_copy_private_to_global    port_memory_copy

#  define port_memory_copy_local_to_private     port_memory_copy
#  define port_memory_copy_local_to_local       port_memory_copy
#  define port_memory_copy_local_to_global      port_memory_copy

#  define port_memory_copy_global_to_private    port_memory_copy
#  define port_memory_copy_global_to_local      port_memory_copy
#  define port_memory_copy_global_to_global     port_memory_copy

#  define port_memory_copy_constant_to_private  port_memory_copy
#  define port_memory_copy_constant_to_local    port_memory_copy
#  define port_memory_copy_constant_to_global   port_memory_copy

#endif // __OPENCL_C_VERSION__

#endif // _PORT_MEMORY_COPY_FUN_H_

