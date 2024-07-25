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
 * @brief Types for kernel arguments operations.
 */

#pragma once
#ifndef _PORT_HOST_KERNEL_TYP_H_
#define _PORT_HOST_KERNEL_TYP_H_

#include <port/cdev/memory.typ.h>
#include <port/cdev/work_item.typ.h>

struct port_memory_operations;
struct port_memory_operation_properties;

/**
 * @brief Kernel arguments allocation function.
 *
 * @return True on success, otherwise false.
 */
typedef port_bool_t (*port_kargs_alloc_func_t)(
        port_void_ptr_t kargs, ///< [out] Kernel arguments to allocate.

        port_const_void_ptr_t alloc_opts, ///< [in] Allocator options.

        const struct port_memory_operations *op, ///< [in] Memory operations.
        const struct port_memory_operation_properties *prop ///< [in] Properties for memory operations.
);

/**
 * @brief Kernel arguments copy allocation function.
 *
 * @return True on success, otherwise false.
 */
typedef port_bool_t (*port_kargs_alloc_copy_func_t)(
        port_void_ptr_t kargs, ///< [out] Kernel arguments to allocate.
        port_const_void_ptr_t kargs_src, ///< [in] Kernel arguments to be copied.

        const struct port_memory_operations *op, ///< [in] Memory operations.
        const struct port_memory_operation_properties *prop, ///< [in] Properties for memory operations.

        const struct port_memory_operations *op_src, ///< [in] Memory operations for source arguments.
        const struct port_memory_operation_properties *prop_src ///< [in] Properties for memory operations for source arguments.
);

/**
 * @brief Kernel arguments copy function.
 *
 * @return True on success, otherwise false.
 */
typedef port_bool_t (*port_kargs_copy_func_t)(
        port_void_ptr_t kargs, ///< [in,out] Kernel arguments to copy to.
        port_const_void_ptr_t kargs_src, ///< [in] Kernel arguments to be copied.

        port_bool_t writable_only, ///< [in] Whether to copy writable data only.

        const struct port_memory_operations *op, ///< [in] Memory operations.
        const struct port_memory_operation_properties *prop, ///< [in] Properties for memory operations.

        const struct port_memory_operations *op_src, ///< [in] Memory operations for source arguments.
        const struct port_memory_operation_properties *prop_src ///< [in] Properties for memory operations for source arguments.
);

/**
 * @brief Kernel arguments deallocation function.
 *
 * @return True on success, otherwise false.
 */
typedef port_bool_t (*port_kargs_free_func_t)(
        port_void_ptr_t kargs, ///< [in] Kernel arguments to deallocate.

        const struct port_memory_operations *op, ///< [in] Memory operations.
        const struct port_memory_operation_properties *prop ///< [in] Properties for memory operations.
);

#endif // _PORT_HOST_KERNEL_TYP_H_

