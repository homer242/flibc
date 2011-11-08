/*
 * Copyright (c) 2011 Anthony Viallard
 *
 *    This file is part of Flibc.
 *
 * Flibc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Flibc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Flibc. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _FLIBC_MATH_H_
#define _FLIBC_MATH_H_

/*! \def min(x, y)
 */
#define min(x, y)                                   \
        ({                                          \
                typeof(x) _x = (x);                 \
                typeof(y) _y = (y);                 \
                _x < _y ? _x : _y;                  \
        })

/*! \def max(x, y)
 */
#define max(x, y)                                   \
        ({                                          \
                typeof(x) _x = (x);                 \
                typeof(y) _y = (y);                 \
                _x > _y ? _x : _y;                  \
        })

#endif
