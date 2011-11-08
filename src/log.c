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

#include "flibc/log.h"

#include <stdlib.h>
#include <stdarg.h>

void log_open(const char *ident, int option, int facility)
{
	openlog(ident, option, facility);

	return;
}

void log_close(void)
{
	closelog();

	return;
}

void log_write(int priority, const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	vsyslog(priority, fmt, args);
	va_end(args);

	return;
}
