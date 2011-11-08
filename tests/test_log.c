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

#define ENABLE_LOG_DEBUG 1
#include <flibc/log.h>
#include <flibc/flibc.h>

#include "libtest.h"

TEST_DEF(test_log)
{
	/* only test if there macro issues */
        log_open("flibc_test_log", LOG_PID, LOG_USER);

        log_write(LOG_INFO, "Hello World !");

        log_info("It's a log info message");
        log_notice("It's a log notice message");
        log_error("It's a log error message");
        log_debug("It's a log debug message");

        log_close();

        TEST_ASSERT(1);
}

int main(void)
{
        TEST_MODULE_INIT("flibc/log");

        TEST_RUN(test_log);

        return TEST_MODULE_RETURN;
}
