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
 * log.h
 *
 * - The pretty things here are first log_* macros (log_info, log_debug, ...).
 *   Macros log_open, log_close and log_write are just to harmonize
 *   use of log interface;
 * - You can enable log_debug() by defining ENABLE_LOG_DEBUG macro.
 * - You can enable color logs by defining ENABLE_VT102_COLOR macro
 *   (before any flibc includes).
 */

#include <syslog.h>

#include <flibc/vt102.h>

#define log_info(fmt, ...)                                          \
	log_write(LOG_INFO, fmt, ##__VA_ARGS__)

#define log_notice(fmt, ...)                                        \
        log_write(LOG_NOTICE, VT102_COLOR_PURPLE(fmt), ##__VA_ARGS__)

#define log_warn(fmt, ...)                                         \
        log_write(LOG_ERR, VT102_COLOR_YELLOW(fmt), ##__VA_ARGS__)

#define log_error(fmt, ...)                                         \
        log_write(LOG_ERR, VT102_COLOR_RED(fmt), ##__VA_ARGS__)

#if defined(ENABLE_LOG_DEBUG)
#define log_debug(fmt, ...)                                         \
        log_write(LOG_DEBUG, "in %s:%04d - " fmt,                   \
                  __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define log_debug(fmt, ...) do {;} while(0)
#endif

/*
 * log_open - wrapper macro to openlog
 *
 *  Open a connection to the system logger.
 *
 * (view syslog man page for more documentation)
 */
#define log_open(ident, opt, facility) \
        openlog(ident, opt, facility)

/*
 * log_close - wrapper macro to closelog
 *
 *  Close the connection used for the system logger.
 *
 * (view syslog man page for more documentation)
 */
#define log_close() \
        closelog()

/*
 * log_write - wrapper macro to syslog
 *
 *  Write message to the system logger.
 *
 * (view syslog man page for more documentation)
 */
#define log_write(priority, fmt, ...) \
        syslog(priority, fmt, ##__VA_ARGS__)

#endif
