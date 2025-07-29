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
 * @brief Pointer types.
 */

#pragma once
#ifndef _PORT_POINTER_TYP_H_
#define _PORT_POINTER_TYP_H_

#include "port/types.typ.h"
#include "port/keywords.def.h"

///////////////////////////////////////////////////////////////////////
// Pointers to void
///////////////////////////////////////////////////////////////////////

/**
 * @brief Pointer to non-const void.
 */
typedef void* port_void_ptr_t;
/**
 * @brief Pointer to const void.
 */
typedef const void* port_const_void_ptr_t;

/**
 * @brief Pointer to private non-const void.
 */
typedef PORT_KW_PRIVATE void* port_private_void_ptr_t;
/**
 * @brief Pointer to private const void.
 */
typedef const PORT_KW_PRIVATE void* port_const_private_void_ptr_t;

/**
 * @brief Pointer to local non-const void.
 */
typedef PORT_KW_LOCAL void* port_local_void_ptr_t;
/**
 * @brief Pointer to local const void.
 */
typedef const PORT_KW_LOCAL void* port_const_local_void_ptr_t;

/**
 * @brief Pointer to global non-const void.
 */
typedef PORT_KW_GLOBAL void* port_global_void_ptr_t;
/**
 * @brief Pointer to global const void.
 */
typedef const PORT_KW_GLOBAL void* port_const_global_void_ptr_t;

/**
 * @brief Pointer to constant void.
 */
typedef const PORT_KW_CONSTANT void* port_constant_void_ptr_t;

///////////////////////////////////////////////////////////////////////
// Pointers to char
///////////////////////////////////////////////////////////////////////

/**
 * @brief Pointer to non-const char.
 */
typedef char* port_char_ptr_t;
/**
 * @brief Pointer to const char.
 */
typedef const char* port_const_char_ptr_t;

/**
 * @brief Pointer to private non-const char.
 */
typedef PORT_KW_PRIVATE char* port_private_char_ptr_t;
/**
 * @brief Pointer to private const char.
 */
typedef const PORT_KW_PRIVATE char* port_const_private_char_ptr_t;

/**
 * @brief Pointer to local non-const char.
 */
typedef PORT_KW_LOCAL char* port_local_char_ptr_t;
/**
 * @brief Pointer to local const char.
 */
typedef const PORT_KW_LOCAL char* port_const_local_char_ptr_t;

/**
 * @brief Pointer to global non-const char.
 */
typedef PORT_KW_GLOBAL char* port_global_char_ptr_t;
/**
 * @brief Pointer to global const char.
 */
typedef const PORT_KW_GLOBAL char* port_const_global_char_ptr_t;

/**
 * @brief Pointer to constant char.
 */
typedef const PORT_KW_CONSTANT char* port_constant_char_ptr_t;

#endif // _PORT_POINTER_TYP_H_

