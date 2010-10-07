#ifndef _LIBTEST_H_
#define _LIBTEST_H_

#include <string.h>
#include <stdio.h>

#define TEST_RETURN_SUCCESS 0
#define TEST_RETURN_ERROR 1

/*
 * Color section
 */
#define COLOR_ESCAPE            "\033"
#define COLOR_RESET             COLOR_ESCAPE "[0m"

#define COLOR_BLUE(txt)         COLOR_ESCAPE "[0;34m" txt COLOR_RESET
#define COLOR_GREEN(txt)        COLOR_ESCAPE "[0;32m" txt COLOR_RESET
#define COLOR_RED(txt)          COLOR_ESCAPE "[0;31m" txt COLOR_RESET
#define COLOR_LIGHT_RED(txt)	COLOR_ESCAPE "[1;31m" txt COLOR_RESET
#define COLOR_YELLOW(txt)	COLOR_ESCAPE "[1;33m" txt COLOR_RESET

/*
 * Test return struct
 */
struct test_result_t {
        int ret;
	int line;
	char msg[256];
};

/*
 * Print messages following what happens
 */
#define PRINT_ERROR(m, ...) printf(COLOR_RED(m "\n"), ##__VA_ARGS__)
#define PRINT_RUNTIME_ERROR(m, ...) printf(COLOR_LIGHT_RED(m "\n"),\
                                           ##__VA_ARGS__)
#define PRINT_WARNING(m, ...) printf(COLOR_YELLOW(m "\n"), ##__VA_ARGS__)
#define PRINT_OK(m, ...) printf(COLOR_GREEN(m "\n"), ##__VA_ARGS__)

/*
 * Run a test definition
 */
#define TEST_RUN(func) do                                               \
	{								\
		struct test_result_t tr;                                \
		tr.ret = TEST_RETURN_SUCCESS;                           \
									\
		func(&tr);                                              \
		if(tr.ret == TEST_RETURN_ERROR)				\
		{							\
			PRINT_ERROR("KO: %s (line:%d): %s",             \
                                    #func,                              \
                                    tr.line,                            \
                                    tr.msg);                            \
		}							\
		else							\
		{							\
			PRINT_OK("OK: %s",                              \
                                 #func);                                \
		}							\
		main_return |= tr.ret;                                  \
	} while(0)

/*
 * Define a test function (Unit Test)
 *
 * A test function return:
 *  TEST_RETURN_ERROR if test has failed
 *  TEST_RETURN_SUCCESS if test is success
 */
#define TEST_DEF(name)                                  \
	static void name(struct test_result_t* __tr)

/*
 * Produce a assertion
 */
#define TEST_ASSERT(test, message, ...) do			\
	{							\
		if(!(test))					\
		{						\
			__tr->ret = TEST_RETURN_ERROR;          \
			__tr->line = __LINE__;			\
			snprintf(__tr->msg,			\
				 sizeof(__tr->msg),		\
				 message, ##__VA_ARGS__);	\
			return;                                 \
		}						\
	} while(0)

/*
 * Define a test module of unit tests
 */
#define TEST_MODULE_INIT(name)                          \
	int main_return = TEST_RETURN_SUCCESS;          \
	printf(COLOR_BLUE("@@ TEST " name " @@\n"))

#define TEST_MODULE_RETURN main_return

#endif
