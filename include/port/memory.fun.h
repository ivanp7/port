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
 * @brief Operations on memory.
 */

#pragma once
#ifndef _PORT_MEMORY_FUN_H_
#define _PORT_MEMORY_FUN_H_

#include "port/memory.typ.h"
#include "port/pointer.typ.h"

/**
 * @brief Follow memory reference in generic memory.
 *
 * @see PORT_MEMORY_AT()
 *
 * @return Pointer to referenced memory.
 */
port_const_void_ptr_t
port_memory_at(
        port_memory_ref_t ref, ///< [in] Memory reference.
        port_memory_ref_format_t format, ///< [in] Memory reference format.

        port_const_void_ptr_t base_ptr, ///< [in] Base address for near memory reference.
        const PORT_KW_CONSTANT port_const_void_ptr_t *memory_table ///< [in] Table of memory pointers for far memory reference.
);

#ifdef __OPENCL_C_VERSION__

/**
 * @brief Follow memory reference in local memory.
 *
 * @see port_memory_at()
 *
 * @return Pointer to referenced memory.
 */
port_const_local_void_ptr_t
port_memory_at_local(
        port_memory_ref_t ref, ///< [in] Memory reference.
        port_memory_ref_format_t format, ///< [in] Memory reference format.

        port_const_local_void_ptr_t base_ptr, ///< [in] Base address for near memory reference.
        const PORT_KW_CONSTANT port_const_local_void_ptr_t *memory_table ///< [in] Table of memory pointers for far memory reference.
);

/**
 * @brief Follow memory reference in global memory.
 *
 * @see port_memory_at()
 *
 * @return Pointer to referenced memory.
 */
port_const_global_void_ptr_t
port_memory_at_global(
        port_memory_ref_t ref, ///< [in] Memory reference.
        port_memory_ref_format_t format, ///< [in] Memory reference format.

        port_const_global_void_ptr_t base_ptr, ///< [in] Base address for near memory reference.
        const PORT_KW_CONSTANT port_const_global_void_ptr_t *memory_table ///< [in] Table of memory pointers for far memory reference.
);

/**
 * @brief Follow memory reference in constant memory.
 *
 * @see port_memory_at()
 *
 * @return Pointer to referenced memory.
 */
port_constant_void_ptr_t
port_memory_at_constant(
        port_memory_ref_t ref, ///< [in] Memory reference.
        port_memory_ref_format_t format, ///< [in] Memory reference format.

        port_constant_void_ptr_t base_ptr, ///< [in] Base address for near memory reference.
        const PORT_KW_CONSTANT port_constant_void_ptr_t *memory_table ///< [in] Table of memory pointers for far memory reference.
);

#else // __OPENCL_C_VERSION__

#  define port_memory_at_local      port_memory_at
#  define port_memory_at_global     port_memory_at
#  define port_memory_at_constant   port_memory_at

#endif // __OPENCL_C_VERSION__

#endif // _PORT_MEMORY_FUN_H_

