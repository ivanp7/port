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

/**
 * @brief Follow memory reference.
 *
 * See description of PORT_MEMORY_AT().
 *
 * @return Pointer to referenced memory.
 */
port_const_global_memory_ptr_t
port_memory_at(
        port_memory_ref_t ref, ///< [in] Memory reference.

        port_memory_ref_format_t format, ///< [in] Memory reference format.

        port_const_global_memory_ptr_t base_ptr, ///< [in] Base address for near memory reference.
        port_memory_table_t memory_table ///< [in] Table of memory pointers for far memory reference.
);

#endif // _PORT_MEMORY_FUN_H_

