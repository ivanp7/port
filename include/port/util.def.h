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
 * @brief Miscellaneous utility macros.
 */

#pragma once
#ifndef _PORT_UTIL_DEF_H_
#define _PORT_UTIL_DEF_H_

/**
 * @brief Swap values in two places.
 */
#define PORT_SWAP(type, place1, place2) do { \
    type _port_swap_temp_var_ = place1; \
    place1 = place2;                    \
    place2 = _port_swap_temp_var_;      \
} while (0)

#endif // _PORT_UTIL_DEF_H_

