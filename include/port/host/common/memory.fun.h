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
 * @brief Functions for memory operations.
 */

#pragma once
#ifndef _PORT_HOST_COMMON_MEMORY_FUN_H_
#define _PORT_HOST_COMMON_MEMORY_FUN_H_

#include <port/host/common/memory.typ.h>

/**
 * @brief Destroy list of memory storage sections.
 */
void
port_memory_storage_destroy_section_list(
        port_memory_storage_section_t *section_list_head ///< [in] Head of section list.
);

/**
 * @brief Destroy list of memory storage symbols.
 */
void
port_memory_storage_destroy_symbol_list(
        port_memory_storage_symbol_t *symbol_list_head ///< [in] Head of symbol list.
);

///////////////////////////////////////////////////////////////////////////////
// BFD
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Initialize BFD library.
 */
void
port_memory_storage_init_bfd(
        void
);

/**
 * @brief Create a BFD storage.
 *
 * Reading can be done from a stream or from a file opened by its name.
 * Writing can be done to an opened file only, writing to a stream is not supported.
 *
 * @return BFD storage.
 */
port_void_ptr_t
port_memory_storage_open_bfd(
        port_bool_t for_writing, ///< [in] Whether file is opened for writing.
        port_void_ptr_t stream,  ///< [in] Stream to read.
        const char *filename,    ///< [in] File to open or file name associated with the stream.
        const char *target       ///< [in] BFD target.
);

/**
 * @brief Close a BFD storage and complete any pending operations.
 *
 * If BFD is opened using a stream, it is also closed.
 *
 * @return True if succeed, otherwise false.
 */
port_bool_t
port_memory_storage_close_bfd(
        port_void_ptr_t bfd_storage, ///< [in] BFD storage.
        port_bool_t complete_operations ///< [in] Whether to complete any pending operations.
);

/**
 * @brief Read lists of sections and symbols from a BFD storage.
 *
 * @return True if succeed, otherwise false.
 */
port_bool_t
port_memory_storage_read_bfd(
        port_void_ptr_t bfd_storage, ///< [in] BFD storage.

        port_memory_storage_section_filter_func_t section_filter, ///< [in] Section filter function.
        port_memory_storage_symbol_filter_func_t symbol_filter,   ///< [in] Symbol filter function.

        port_memory_storage_section_t **section_list_head, ///< [out] Head of section list.
        port_memory_storage_section_t **section_list_tail, ///< [out] Tail of section list.
        port_size_t *num_sections, ///< [out] Number of sections.

        port_memory_storage_symbol_t **symbol_list_head, ///< [out] Head of symbol list.
        port_memory_storage_symbol_t **symbol_list_tail, ///< [out] Tail of symbol list.
        port_size_t *num_symbols ///< [out] Number of symbols.
);

/**
 * @brief Write lists of sections and symbols to a BFD storage.
 *
 * @return True if succeed, otherwise false.
 */
port_bool_t
port_memory_storage_write_bfd(
        port_void_ptr_t bfd_storage, ///< [in,out] BFD storage.

        port_memory_storage_section_t *section_list_head, ///< [in] Head of section list.
        port_memory_storage_symbol_t *symbol_list_head    ///< [in] Head of symbol list.
);

/**
 * @brief Copy section contents.
 *
 * @return True if succeed, otherwise false.
 */
port_bool_t
port_memory_storage_section_contents_bfd(
        port_memory_storage_section_t *section, ///< [in] Memory storage section.
        port_size_t offset, ///< [in] Offset of the copied area in units.
        port_size_t size,   ///< [in] Size of the copied area in units.

        port_memory_ptr_t memory ///< [out] Memory to copy section contents into.
);

#endif // _PORT_HOST_COMMON_MEMORY_FUN_H_

