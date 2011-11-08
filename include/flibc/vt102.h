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

#ifndef _FLIBC_VT102_H_
#define _FLIBC_VT102_H_

/*
 * vt102.h
 *
 * - You can enable color in vt102 module by defining ENABLE_VT102_COLOR macro.
 */

#define VT102_ESCAPE                  "\033"

#if defined(ENABLE_VT102_COLOR)
 #define VT102_COLOR_RESET            VT102_ESCAPE "[0m"

 #define VT102_COLOR_BLACK(txt)       VT102_ESCAPE "[0;30m" txt VT102_COLOR_RESET
 #define VT102_COLOR_RED(txt)         VT102_ESCAPE "[0;31m" txt VT102_COLOR_RESET
 #define VT102_COLOR_GREEN(txt)       VT102_ESCAPE "[0;32m" txt VT102_COLOR_RESET
 #define VT102_COLOR_BROWN(txt)       VT102_ESCAPE "[0;33m" txt VT102_COLOR_RESET
 #define VT102_COLOR_BLUE(txt)        VT102_ESCAPE "[0;34m" txt VT102_COLOR_RESET
 #define VT102_COLOR_PURPLE(txt)      VT102_ESCAPE "[0;35m" txt VT102_COLOR_RESET
 #define VT102_COLOR_CYAN(txt)        VT102_ESCAPE "[0;36m" txt VT102_COLOR_RESET
 #define VT102_COLOR_GRAY(txt)        VT102_ESCAPE "[0;37m" txt VT102_COLOR_RESET

 #define VT102_COLOR_DARK_GRAY(txt)   VT102_ESCAPE "[1;30m" txt VT102_COLOR_RESET
 #define VT102_COLOR_LIGHT_RED(txt)   VT102_ESCAPE "[1;31m" txt VT102_COLOR_RESET
 #define VT102_COLOR_LIGHT_GREEN(txt) VT102_ESCAPE "[1;32m" txt VT102_COLOR_RESET
 #define VT102_COLOR_YELLOW(txt)      VT102_ESCAPE "[1;33m" txt VT102_COLOR_RESET
 #define VT102_COLOR_LIGHT_BLUE(txt)  VT102_ESCAPE "[1;34m" txt VT102_COLOR_RESET
 #define VT102_COLOR_LIGHT_PURPLE(txt)VT102_ESCAPE "[1;35m" txt VT102_COLOR_RESET
 #define VT102_COLOR_LIGHT_CYAN(txt)  VT102_ESCAPE "[1;36m" txt VT102_COLOR_RESET
 #define VT102_COLOR_WHITE(txt)       VT102_ESCAPE "[1;37m" txt VT102_COLOR_RESET
#else
 #define VT102_COLOR_BLACK(txt)       txt
 #define VT102_COLOR_RED(txt)         txt
 #define VT102_COLOR_GREEN(txt)       txt
 #define VT102_COLOR_BROWN(txt)       txt
 #define VT102_COLOR_BLUE(txt)        txt
 #define VT102_COLOR_PURPLE(txt)      txt
 #define VT102_COLOR_CYAN(txt)        txt
 #define VT102_COLOR_GRAY(txt)        txt

 #define VT102_COLOR_DARK_GRAY(txt)   txt
 #define VT102_COLOR_LIGHT_RED(txt)   txt
 #define VT102_COLOR_LIGHT_GREEN(txt) txt
 #define VT102_COLOR_YELLOW(txt)      txt
 #define VT102_COLOR_LIGHT_BLUE(txt)  txt
 #define VT102_COLOR_LIGHT_PURPLE(txt)txt
 #define VT102_COLOR_LIGHT_CYAN(txt)  txt
 #define VT102_COLOR_WHITE(txt)       txt
#endif

#endif
