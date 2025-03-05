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
 * @brief Data storage representation and format.
 */

#pragma once
#ifndef _PORT_HOST_STORAGE_FUN_H_
#define _PORT_HOST_STORAGE_FUN_H_

#include "port/cdev/types.typ.h"

#include <stdio.h>

struct port_data_storage;
struct port_data_storage_file_header;

/**
 * @brief Check validity of data storage file header.
 *
 * Header is valid if all of the following conditions are met:
 * 1) all tables and content segments lie within header.full_size;
 * 2) there are no empty contents of non-empty tables;
 * 3) tables and content segments do not collide.
 *
 * @return True if the header is valid, otherwise false.
 */
port_bool_t
port_check_data_storage_file_header_validity(
        const struct port_data_storage_file_header *file_header ///< [in] Data storage file header.
);

/**
 * @brief Initialize data storage with data read from a file.
 *
 * On success, file position indicator is set to
 * the first byte after data storage end.
 *
 * @return 0 on success, 1 on invalid file contents or format,
 * 2 on fseek() error, 3 on fread() error, 4 on malloc() error.
 */
port_uint8_t
port_init_data_storage_from_file(
        struct port_data_storage *storage, ///< [out] Data storage.
        port_uint_single_t *format, ///< [out] File format value.

        port_uint_single_t format_mask,  ///< [in] Mask to extract magic number from file format value.
        port_uint_single_t format_magic, ///< [in] Magic number of file format.

        FILE *file ///< [in] File to read.
);

/**
 * @brief Write data storage to a file.
 *
 * @return 0 on success, 1 on too large resulting file size,
 * 2 on invalid values of storage fields, 3 on fwrite() error.
 */
port_uint8_t
port_write_data_storage_to_file(
        const struct port_data_storage *storage, ///< [in] Data storage.
        port_uint_single_t format, ///< [in] File format (magic number).

        port_uint_single_t *full_size, ///< [out] Full size of the data storage excluding header.

        FILE *file ///< [out] File to write.
);

/**
 * @brief Free memory owned by storage and set fields to default values.
 */
void
port_reset_data_storage(
        struct port_data_storage *storage ///< [in,out] Data storage.
);

#endif // _PORT_HOST_STORAGE_FUN_H_

