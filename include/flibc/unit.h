/*
 * Copyright (c) 2011-2012 Anthony Viallard
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

#ifndef _FLIBC_UNIT_H_
#define _FLIBC_UNIT_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <flibc/vt102.h>

/*
 * unit.h - unit test framework
 *
 * - You can enable color logs by defining ENABLE_VT102_COLOR macro
 *   (before any flibc includes).
 *
 * Architecture:
 * -------------
 *
 *  - a C file for unit test is composed of main() function
 *    with a definition of the "test module";
 *  - a "test module" is a set of test;
 *  - a test is composed of assert to test some conditions.
 *
 * Example:
 * --------
 *
 * #include <flibc/unit.h>
 *
 * TEST_DEF(test_foo)
 * {
 *	TEST_ASSERT(0 + 0 == 0);
 * }
 * 
 * int main(void)
 * {
 *      TEST_MODULE_INIT("foo");
 *
 *      TEST_RUN(test_foo);
 *
 *      return TEST_MODULE_RETURN;
 * }
 */

/*
 * Test return struct
 */
struct test_result {
        int ret;
	int line;
	char msg[256];
};

/*
 * Print messages following what happens
 */
#define TEST_PRINT_ERROR(m, ...)                                \
        printf(VT102_COLOR_RED(m "\n"), ##__VA_ARGS__)
#define TEST_PRINT_RUNTIME_ERROR(m, ...)                        \
        printf(VT102_COLOR_LIGHT_RED(m "\n"), ##__VA_ARGS__)
#define TEST_PRINT_WARNING(m, ...)                              \
        printf(VT102_COLOR_YELLOW(m "\n"), ##__VA_ARGS__)
#define TEST_PRINT_OK(m, ...)                                   \
        printf(VT102_COLOR_GREEN(m "\n"), ##__VA_ARGS__)

/*
 * Run a test definition
 */
#define TEST_RUN(func) do                                               \
	{								\
		struct test_result tr;                                  \
		tr.ret = 0;                                             \
									\
		func(&tr);                                              \
		if(tr.ret != 0)                                         \
		{							\
			TEST_PRINT_ERROR("KO: %s (line:%d): %s",        \
                                    #func, tr.line, tr.msg);            \
		}							\
		else							\
		{							\
			TEST_PRINT_OK("OK: %s", #func);                 \
		}							\
		main_return |= tr.ret;                                  \
	} while(0)

/*
 * Define a test function (Unit Test)
 *
 * A test function return -1 if test has failed, 0 otherwise
 */
#define TEST_DEF(name)                                  \
	static void name(struct test_result* __tr)

/*
 * Produce assertions
 */
#define TEST_RAW_ASSERT(test, message, ...) do                  \
	{							\
		if(!(test))					\
		{						\
			__tr->ret = -1;                         \
			__tr->line = __LINE__;			\
			snprintf(__tr->msg,			\
				 sizeof(__tr->msg),		\
				 message, ##__VA_ARGS__);	\
			return;                                 \
		}						\
	} while(0)

#define TEST_ASSERT(condition)                                  \
        TEST_RAW_ASSERT(condition, "Condition isn't TRUE")

/*
 * Define a test module of unit tests
 */
#define TEST_MODULE_INIT(name)                                  \
	int main_return = 0;                                    \
	printf(VT102_COLOR_BLUE("@@ TEST " name " @@\n"))

#define TEST_MODULE_RETURN main_return

#endif
