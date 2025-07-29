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
 * @brief Pseudorandom number generation.
 */

#pragma once
#ifndef _PORT_RANDOM_TYP_H_
#define _PORT_RANDOM_TYP_H_

#include "port/types.typ.h"
#include "port/types.def.h"

/**
 * @brief Maximum possible pseudorandom 32-bit integer.
 */
#define PORT_RANDOM_MAX PORT_UINT32_MAX

/**
 * @brief Pseudorandom number generator state.
 */
typedef port_uint32_t port_random_t;

#endif // _PORT_RANDOM_TYP_H_

