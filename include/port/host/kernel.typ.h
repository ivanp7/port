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
 * @brief Types for kernels.
 */

#pragma once
#ifndef _PORT_HOST_KERNEL_TYP_H
#define _PORT_HOST_KERNEL_TYP_H

#include <port/cdev/memory.typ.h>

struct port_segmented_memory;

/**
 * @brief Set of kernel arguments divided by type.
 */
typedef struct port_kernel_arguments {
    port_void_ptr_t parameters; ///< Computation parameters for kernels.

    struct {
        struct port_segmented_memory *memory; ///< Array of pointers to segmented data.
        port_void_ptr_t layout; ///< Layout (array index -> field correspondence).
    } data; ///< Data for computation.

    struct {
        struct port_segmented_memory *memory; ///< Pointer to segmented memory with contents.
        port_void_ptr_t layout; ///< Layout (table index -> field correspondence).
    } state; ///< State of computation.
} port_kernel_arguments_t;

#endif // _PORT_HOST_KERNEL_TYP_H

