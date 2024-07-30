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
#include <port/cdev/work.typ.h>

struct port_memory_operations;
struct port_memory_operation_properties;

///////////////////////////////////////////////////////////////////////////////
// Kernel arguments meta information
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Kernel arguments metainfo copy allocation function.
 *
 * @return Allocated kernel arguments metainfo copy, or NULL in case of failure.
 */
typedef port_void_ptr_t (*port_kargs_metainfo_alloc_copy_func_t)(
        port_const_void_ptr_t metainfo ///< [in] Host information of kernel arguments.
);

/**
 * @brief Kernel arguments metainfo copy deallocation function.
 *
 * @return True on success, otherwise false.
 */
typedef port_bool_t (*port_kargs_metainfo_free_func_t)(
        port_void_ptr_t metainfo ///< [in] Host information of kernel arguments.
);

/**
 * @brief Kernel work size getter for kernel arguments metainfo.
 *
 * @return Maximum work size for the kernel.
 */
typedef port_work_size_t (*port_kargs_metainfo_work_size_getter_func_t)(
        port_const_void_ptr_t metainfo, ///< [in] Host information of kernel arguments.
        const char *kernel_name ///< [in] Kernel name.
);

///////////////////////////////////////////////////////////////////////////////
// Kernel arguments
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Kernel arguments allocation function.
 *
 * @return Allocated kernel arguments, or NULL in case of failure.
 */
typedef port_void_ptr_t (*port_kargs_alloc_func_t)(
        port_const_void_ptr_t metainfo, ///< [in] Host information of kernel arguments.

        const struct port_memory_operations *op, ///< [in] Memory operations.
        const struct port_memory_operation_properties *prop ///< [in] Properties for memory operations.
);

/**
 * @brief Kernel arguments copy allocation function.
 *
 * @return Allocated kernel arguments, or NULL in case of failure.
 */
typedef port_void_ptr_t (*port_kargs_alloc_copy_func_t)(
        port_const_void_ptr_t metainfo_src, ///< [in] Host information of kernel arguments to be copied.
        port_const_void_ptr_t src, ///< [in] Kernel arguments data to be copied.

        port_bool_t writable_only, ///< [in] Whether to copy writable data only.

        const struct port_memory_operations *op_dest, ///< [in] Memory operations for destination arguments.
        const struct port_memory_operation_properties *prop_dest, ///< [in] Properties for memory operations for destination arguments.

        const struct port_memory_operations *op_src, ///< [in] Memory operations for source arguments.
        const struct port_memory_operation_properties *prop_src ///< [in] Properties for memory operations for source arguments.
);

/**
 * @brief Kernel arguments copy function.
 *
 * @return True on success, otherwise false.
 */
typedef port_bool_t (*port_kargs_copy_func_t)(
        port_void_ptr_t dest, ///< [out] Kernel arguments to copy to.
        port_const_void_ptr_t metainfo_dest, ///< [in] Host information of kernel arguments to copy to.

        port_const_void_ptr_t src, ///< [in] Kernel arguments to be copied.
        port_const_void_ptr_t metainfo_src, ///< [in] Host information of kernel arguments to be copied.

        port_bool_t writable_only, ///< [in] Whether to copy writable data only.

        const struct port_memory_operations *op_dest, ///< [in] Memory operations for destination arguments.
        const struct port_memory_operation_properties *prop_dest, ///< [in] Properties for memory operations for destination arguments.

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
        port_const_void_ptr_t metainfo, ///< [in] Host information of kernel arguments.

        const struct port_memory_operations *op, ///< [in] Memory operations.
        const struct port_memory_operation_properties *prop ///< [in] Properties for memory operations.
);

#endif // _PORT_HOST_KERNEL_TYP_H_

