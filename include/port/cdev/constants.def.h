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
 * @brief Frequently used math constants.
 */

#pragma once
#ifndef _PORT_CDEV_CONSTANTS_DEF_H_
#define _PORT_CDEV_CONSTANTS_DEF_H_

#ifndef __OPENCL_C_VERSION__
#  include <CL/cl.h>
#endif

#ifdef __OPENCL_C_VERSION__

#define PORT_M1_E M_E_F ///< e (2.71828), single precision
#define PORT_M2_E M_E   ///< e (2.71828), double precision

#define PORT_M1_LOG2E M_LOG2E_F ///< log2(e) (1.4427), single precision
#define PORT_M2_LOG2E M_LOG2E   ///< log2(e) (1.4427), double precision

#define PORT_M1_LOG10E M_LOG10E_F ///< log10(e) (0.4343), single precision
#define PORT_M2_LOG10E M_LOG10E   ///< log10(e) (0.4343), double precision

#define PORT_M1_LN2 M_LN2_F ///< ln(2) (0.6931), single precision
#define PORT_M2_LN2 M_LN2   ///< ln(2) (0.6931), double precision

#define PORT_M1_LN10 M_LN10_F ///< ln(10) (2.3026), single precision
#define PORT_M2_LN10 M_LN10   ///< ln(10) (2.3026), double precision

#define PORT_M1_PI M_PI_F ///< pi (3.1416), single precision
#define PORT_M2_PI M_PI   ///< pi (3.1416), double precision

#define PORT_M1_PI_2 M_PI_2_F ///< pi/2 (1.5708), single precision
#define PORT_M2_PI_2 M_PI_2   ///< pi/2 (1.5708), double precision

#define PORT_M1_PI_4 M_PI_4_F ///< pi/4 (0.7854), single precision
#define PORT_M2_PI_4 M_PI_4   ///< pi/4 (0.7854), double precision

#define PORT_M1_1_PI M_1_PI_F ///< 1/pi (0.31831), single precision
#define PORT_M2_1_PI M_1_PI   ///< 1/pi (0.31831), double precision

#define PORT_M1_2_PI M_2_PI_F ///< 2/pi (0.63662), single precision
#define PORT_M2_2_PI M_2_PI   ///< 2/pi (0.63662), double precision

#define PORT_M1_2_SQRTPI M_2_SQRTPI_F ///< 2/sqrt(pi) (1.12838), single precision
#define PORT_M2_2_SQRTPI M_2_SQRTPI   ///< 2/sqrt(pi) (1.12838), double precision

#define PORT_M1_SQRT2 M_SQRT2_F ///< sqrt(2) (1.4142), single precision
#define PORT_M2_SQRT2 M_SQRT2   ///< sqrt(2) (1.4142), double precision

#define PORT_M1_SQRT1_2 M_SQRT1_2_F ///< sqrt(1/2) (0.7071), single precision
#define PORT_M2_SQRT1_2 M_SQRT1_2   ///< sqrt(1/2) (0.7071), double precision

#define PORT_M_INFINITY INFINITY ///< +infinity
#define PORT_M_NAN NAN ///< Not-a-Number (NaN)

#else

#define PORT_M1_E CL_M_E_F ///< e (2.71828), single precision
#define PORT_M2_E CL_M_E   ///< e (2.71828), double precision

#define PORT_M1_LOG2E CL_M_LOG2E_F ///< log2(e) (1.4427), single precision
#define PORT_M2_LOG2E CL_M_LOG2E   ///< log2(e) (1.4427), double precision

#define PORT_M1_LOG10E CL_M_LOG10E_F ///< log10(e) (0.4343), single precision
#define PORT_M2_LOG10E CL_M_LOG10E   ///< log10(e) (0.4343), double precision

#define PORT_M1_LN2 CL_M_LN2_F ///< ln(2) (0.6931), single precision
#define PORT_M2_LN2 CL_M_LN2   ///< ln(2) (0.6931), double precision

#define PORT_M1_LN10 CL_M_LN10_F ///< ln(10) (2.3026), single precision
#define PORT_M2_LN10 CL_M_LN10   ///< ln(10) (2.3026), double precision

#define PORT_M1_PI CL_M_PI_F ///< pi (3.1415), single precision
#define PORT_M2_PI CL_M_PI   ///< pi (3.1415), double precision

#define PORT_M1_PI_2 CL_M_PI_2_F ///< pi/2 (1.5708), single precision
#define PORT_M2_PI_2 CL_M_PI_2   ///< pi/2 (1.5708), double precision

#define PORT_M1_PI_4 CL_M_PI_4_F ///< pi/4 (0.7854), single precision
#define PORT_M2_PI_4 CL_M_PI_4   ///< pi/4 (0.7854), double precision

#define PORT_M1_1_PI CL_M_1_PI_F ///< 1/pi (0.31831), single precision
#define PORT_M2_1_PI CL_M_1_PI   ///< 1/pi (0.31831), double precision

#define PORT_M1_2_PI CL_M_2_PI_F ///< 2/pi (0.63662), single precision
#define PORT_M2_2_PI CL_M_2_PI   ///< 2/pi (0.63662), double precision

#define PORT_M1_2_SQRTPI CL_M_2_SQRTPI_F ///< 2/sqrt(pi) (1.12838), single precision
#define PORT_M2_2_SQRTPI CL_M_2_SQRTPI   ///< 2/sqrt(pi) (1.12838), double precision

#define PORT_M1_SQRT2 CL_M_SQRT2_F ///< sqrt(2) (1.4142), single precision
#define PORT_M2_SQRT2 CL_M_SQRT2   ///< sqrt(2) (1.4142), double precision

#define PORT_M1_SQRT1_2 CL_M_SQRT1_2_F ///< sqrt(1/2) (0.7071), single precision
#define PORT_M2_SQRT1_2 CL_M_SQRT1_2   ///< sqrt(1/2) (0.7071), double precision

#define PORT_M_INFINITY CL_INFINITY ///< +infinity
#define PORT_M_NAN CL_NAN ///< Not-a-Number (NaN)

#endif

#ifndef PORT_FEATURE_DEFAULT_FLOAT_64

#define PORT_M_E PORT_M1_E ///< e (2.71828), default precision
#define PORT_M_LOG2E PORT_M1_LOG2E ///< log2(e) (1.4427), default precision
#define PORT_M_LOG10E PORT_M1_LOG10E ///< log10(e) (0.4343), default precision
#define PORT_M_LN2 PORT_M1_LN2 ///< ln(2) (0.6931), default precision
#define PORT_M_LN10 PORT_M1_LN10 ///< ln(10) (2.3026), default precision
#define PORT_M_PI PORT_M1_PI ///< pi (3.1416), default precision
#define PORT_M_PI_2 PORT_M1_PI_2 ///< pi/2 (1.5708), default precision
#define PORT_M_PI_4 PORT_M1_PI_4 ///< pi/4 (0.7854), default precision
#define PORT_M_1_PI PORT_M1_1_PI ///< 1/pi (0.31831), default precision
#define PORT_M_2_PI PORT_M1_2_PI ///< 2/pi (0.63662), default precision
#define PORT_M_2_SQRTPI PORT_M1_2_SQRTPI ///< 2/sqrt(pi) (1.12838), default precision
#define PORT_M_SQRT2 PORT_M1_SQRT2 ///< sqrt(2) (1.4142), default precision
#define PORT_M_SQRT1_2 PORT_M1_SQRT1_2 ///< sqrt(1/2) (0.7071), default precision

#else // PORT_FEATURE_DEFAULT_FLOAT_64

#define PORT_M_E PORT_M2_E ///< e (2.71828), default precision
#define PORT_M_LOG2E PORT_M2_LOG2E ///< log2(e) (1.4427), default precision
#define PORT_M_LOG10E PORT_M2_LOG10E ///< log10(e) (0.4343), default precision
#define PORT_M_LN2 PORT_M2_LN2 ///< ln(2) (0.6931), default precision
#define PORT_M_LN10 PORT_M2_LN10 ///< ln(10) (2.3026), default precision
#define PORT_M_PI PORT_M2_PI ///< pi (3.1416), default precision
#define PORT_M_PI_2 PORT_M2_PI_2 ///< pi/2 (1.5708), default precision
#define PORT_M_PI_4 PORT_M2_PI_4 ///< pi/4 (0.7854), default precision
#define PORT_M_1_PI PORT_M2_1_PI ///< 1/pi (0.31831), default precision
#define PORT_M_2_PI PORT_M2_2_PI ///< 2/pi (0.63662), default precision
#define PORT_M_2_SQRTPI PORT_M2_2_SQRTPI ///< 2/sqrt(pi) (1.12838), default precision
#define PORT_M_SQRT2 PORT_M2_SQRT2 ///< sqrt(2) (1.4142), default precision
#define PORT_M_SQRT1_2 PORT_M2_SQRT1_2 ///< sqrt(1/2) (0.7071), default precision

#endif // PORT_FEATURE_DEFAULT_FLOAT_64

#endif // _PORT_CDEV_CONSTANTS_DEF_H_

