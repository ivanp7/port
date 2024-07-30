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
 * @brief Type of vtable structure for libraries using Port.
 */

#pragma once
#ifndef _PORT_HOST_VTABLE_TYP_H_
#define _PORT_HOST_VTABLE_TYP_H_

#include <port/host/kernel.typ.h>

struct port_pfunc_description;
struct port_kargs_setter_description;
struct port_opencl_program_source;

/**
 * @brief Vtable structure for libraries using Port.
 */
typedef struct port_vtable {
    port_uint32_t magic;   ///< Value uniquely identifying Port vtable structure.
    port_uint32_t version; ///< Value determining vtable version and compatibility.

    struct {
        struct {
            port_kargs_metainfo_alloc_copy_func_t alloc_copy_fn; ///< Kernel arguments metainfo copy allocation function.
            port_kargs_metainfo_free_func_t free_fn; ///< Kernel arguments metainfo deallocation function.
            port_kargs_metainfo_work_size_getter_func_t work_size_getter_fn; ///< Kernel work size getter function.
        } metainfo; ///< Kernel arguments meta information.

        port_kargs_alloc_func_t alloc_fn; ///< Kernel arguments allocation function.
        port_kargs_alloc_copy_func_t alloc_copy_fn; ///< Kernel arguments copy allocation function.
        port_kargs_copy_func_t copy_fn; ///< Kernel arguments copy function.
        port_kargs_free_func_t free_fn; ///< Kernel arguments deallocation function.
    } kargs;

    const struct port_pfunc_description *pfuncs; ///< Concurrent processing wrappers of kernels.
    const struct port_kargs_setter_description *kargs_setters; ///< Kernel arguments setters.

    const struct port_opencl_program_source **program_sources; ///< Array of OpenCL program sources.
} port_vtable_t;

#endif // _PORT_HOST_VTABLE_TYP_H_

