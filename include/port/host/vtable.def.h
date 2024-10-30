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
 * @brief Constants for vtable structure for libraries using Port.
 */

#pragma once
#ifndef _PORT_HOST_VTABLE_DEF_H_
#define _PORT_HOST_VTABLE_DEF_H_

/**
 * @brief Magic number - value uniquely identifying Port vtable structure.
 */
#define PORT_VTABLE_MAGIC 0xBEA981E1
/**
 * @brief Version - value determining vtable version and compatibility.
 */
#define PORT_VTABLE_VERSION 20241030

#endif // _PORT_HOST_VTABLE_DEF_H_

