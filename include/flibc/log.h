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

#ifndef _FLIBC_LOG_H_
#define _FLIBC_LOG_H_

/*
 * log module
 * -----------------------
 *
 * - You can enable log_debug() by defining ENABLE_LOG_DEBUG macro
 */

#include <syslog.h>

#include "flibc/vt102.h"

#define log_info(fmt, ...)                                          \
	log_write(LOG_INFO, fmt, ##__VA_ARGS__)

#define log_notice(fmt, ...)                                        \
        log_write(LOG_NOTICE, VT102_COLOR_PURPLE(fmt), ##__VA_ARGS__)
        
#define log_error(fmt, ...)                                         \
        log_write(LOG_ERR, VT102_COLOR_RED(fmt), ##__VA_ARGS__)

#if defined(ENABLE_LOG_DEBUG)
#define log_debug(fmt, ...)                                         \
        log_write(LOG_DEBUG, "in %s:%04d - " fmt,                   \
                  __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define log_debug(fmt, ...) do {;} while(0)
#endif

void log_open(const char *ident);
void log_close(void);
void log_write(int level, const char *fmt, ...);

#endif
