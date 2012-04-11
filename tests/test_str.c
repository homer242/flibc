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

#define ENABLE_VT102_COLOR 1
#include <flibc/str.h>
#include <flibc/flibc.h>
#include <flibc/math.h>
#include <flibc/list.h>
#include <flibc/unit.h>

TEST_DEF(test_str_copy)
{
        char buf1[1];
        char buf16[16];
        size_t ret;

        const char *my_string = NULL;

        /* copy of empty string */
        my_string = "";

        ret = str_copy(buf1, sizeof(buf1), my_string);

        TEST_ASSERT(ret == 0);
        TEST_ASSERT(strcmp(buf1, my_string) == 0);

        /* copy of normal string without truncated case */
        my_string = "Hello world !";

        ret = str_copy(buf16, sizeof(buf16), my_string);

        TEST_ASSERT(ret == strlen(buf16));
        TEST_ASSERT(strcmp(buf16, my_string) == 0);

        /* test return string copied is truncated and NULL terminated */
        my_string = "foobarfoobarfoobarfoo";

        ret = str_copy(buf16, sizeof(buf16), my_string);

        TEST_ASSERT(ret > sizeof(buf16) - 1);
        TEST_ASSERT(ret == strlen(my_string));
        TEST_ASSERT(buf16[sizeof(buf16) - 1] == '\0');
        TEST_ASSERT(strncmp(my_string, buf16, sizeof(buf16) - 1) == 0);
}

TEST_DEF(test_str_printf)
{
        char buf16[16];
        int ret;

        const char *my_string = NULL;

        /* test truncation case and null terminated */
        my_string = "0123456789012345";

        ret = str_printf(buf16, sizeof(buf16), "%s", my_string);

        TEST_ASSERT(ret > (int)sizeof(buf16) - 1);
        TEST_ASSERT(ret == (int)strlen(my_string));
        TEST_ASSERT(buf16[sizeof(buf16) - 1] == '\0');
}

TEST_DEF(test_str_cat)
{
        char buf16[16];
        const char *my_string = NULL;
        size_t ret;

        /* test truncation case and null terminated */
        buf16[0] = '\0';

        my_string = "01234567890123456789";
        ret = str_cat(buf16, sizeof(buf16), my_string);

        TEST_ASSERT(ret > sizeof(buf16) - 1);
        TEST_ASSERT(ret == strlen(my_string));
        TEST_ASSERT(buf16[sizeof(buf16) - 1] == '\0');

        /* basic test and truncation/nullended case */
        buf16[0] = '\0';

        my_string = "12345";

        ret = str_cat(buf16, sizeof(buf16), my_string);

        TEST_ASSERT(ret == strlen(my_string));
        TEST_ASSERT(strcmp(buf16, my_string) == 0);

        ret = str_cat(buf16, sizeof(buf16), my_string);

        TEST_ASSERT(ret == 2 * strlen(my_string));
        TEST_ASSERT(strcmp(buf16, "1234512345") == 0);

        ret = str_cat(buf16, sizeof(buf16), my_string);

        TEST_ASSERT(ret == 3 * strlen(my_string));
        TEST_ASSERT(strcmp(buf16, "123451234512345") == 0);

        ret = str_cat(buf16, sizeof(buf16), my_string);

        TEST_ASSERT(ret > sizeof(buf16) - 1);
        TEST_ASSERT(ret == 4 * strlen(my_string));
        TEST_ASSERT(buf16[sizeof(buf16) - 1] == '\0');
}

TEST_DEF(test_str_matches)
{
        char buf[16];

        snprintf(buf, sizeof(buf), "teststring");

        TEST_ASSERT(str_matches(buf, "teststring"));
        TEST_ASSERT(!str_matches(buf, "test"));
        TEST_ASSERT(!str_matches(buf, ""));
}

TEST_DEF(test_str_empty)
{
        TEST_ASSERT(str_empty(""));
        TEST_ASSERT(!str_empty("a"));
        TEST_ASSERT(!str_empty("Hello World !"));
}

TEST_DEF(test_str_split)
{
        struct list_head list;
        unsigned int count,
                i;
        const char *my_string = NULL;
        struct str_list_item *item = NULL;

        /* basic test */
        const char *items_expect[] = {
                "one",
                "two",
                "three",
                "four",
                "five",
        };

        my_string = "one two three four five";

        count = str_split(my_string, " ", &list);

        TEST_ASSERT(count == 5);
        i = 0;
        list_for_each_entry(item, &list, node)
        {
                TEST_ASSERT(strcmp(items_expect[i], item->value) == 0);
                /* printf(" * item = %s\n", item->value); */
                ++i;
        }
        TEST_ASSERT(count == i);
        str_list_free(&list);

        /* no found delimiter in string */
        const char *items_expect2[] = {
                "therearenospacehere",
        };

        my_string = "therearenospacehere";

        count = str_split(my_string, " ", &list);
        TEST_ASSERT(count == 1);
        i = 0;
        list_for_each_entry(item, &list, node)
        {
                TEST_ASSERT(strcmp(items_expect2[i], item->value) == 0);
                /* printf(" * item = %s\n", item->value); */
                ++i;
        }
        TEST_ASSERT(count == i);
        str_list_free(&list);

        /* garbage in string */
        const char *items_expect3[] = {
                "",
                "one",
                "",
                "two",
                "", "",
                "three",
                "","","",
                "four",
                "","","","",
                "five",
                "","","","","",
        };

        my_string = " one  two   three    four     five      ";

        count = str_split(my_string, " ", &list);
        TEST_ASSERT(count == 5 + (1 + 1 + 2 + 3 + 4 + 5));
        i = 0;
        list_for_each_entry(item, &list, node)
        {
                TEST_ASSERT(strcmp(items_expect3[i], item->value) == 0);
                /* printf(" * item = %s, strlen()=%zu\n", */
                /*        item->value, strlen(item->value)); */
                ++i;
        }
        TEST_ASSERT(count == i);
        str_list_free(&list);
}

TEST_DEF(test_str_ltrim)
{
        const char *my_string = NULL,
                *ret = NULL;

        /* basic test */
        my_string = " \t  \n \v \r   Hello\n\r\n\t \v";

        ret = str_ltrim(my_string);

        TEST_ASSERT(strcmp(ret, "Hello\n\r\n\t \v") == 0);

        /* empty string */
        my_string = "";

        ret = str_ltrim(my_string);

        TEST_ASSERT(strcmp(ret, "") == 0);
}

TEST_DEF(test_str_rtrim)
{
        char *my_string = NULL,
                *ret = NULL;

        /* basic test */
        my_string = strdup(" \t  \n  \r \v  Hello\n\r\n\t \v");

        ret = str_rtrim(my_string);

        TEST_ASSERT(strcmp(ret, " \t  \n  \r \v  Hello") == 0);

        free(my_string);

        /* empty string */
        my_string = strdup("");

        ret = str_rtrim(my_string);

        TEST_ASSERT(strcmp(ret, "") == 0);

        free(my_string);
}

TEST_DEF(test_str_trim)
{
        char *my_string = NULL;
        const char *ret = NULL;

        /* basic test */
        my_string = strdup(" \t  \n  \r   Hello\n\r\n\t ");

        ret = str_trim(my_string);

        TEST_ASSERT(strcmp(ret, "Hello") == 0);

        free(my_string);

        /* empty string */
        my_string = strdup("");

        ret = str_trim(my_string);

        TEST_ASSERT(strcmp(ret, "") == 0);

        free(my_string);
}

TEST_DEF(test_str_tol)
{
        const char *my_string = NULL;
        long ret;

        /* basic test */
        my_string = "13";

        ret = str_tol(my_string, NULL, 10, -1);

        TEST_ASSERT(ret == 13);

        /* empty string */
        my_string = "";

        ret = str_tol(my_string, NULL, 10, -1);

        TEST_ASSERT(ret == -1);
}

TEST_DEF(test_str_toll)
{
        const char *my_string = NULL;
        long long ret;

        /* basic test */
        my_string = "13";

        ret = str_toll(my_string, NULL, 10, -1);

        TEST_ASSERT(ret == 13);

        /* empty string */
        my_string = "";

        ret = str_toll(my_string, NULL, 10, -1);

        TEST_ASSERT(ret == -1);
}

TEST_DEF(test_str_list_toarray)
{
	struct list_head list;
        unsigned int count,
                ret,
		i;
        const char *my_string = NULL;
	const char *ip_parts[4];

        /* basic test */
        const char *items_expect[] = {
                "192",
                "168",
                "1",
                "1",
        };

        my_string = "192.168.1.1";

        count = str_split(my_string, ".", &list);

	ret = str_list_toarray(&list, ip_parts, ARRAY_SIZE(ip_parts));

	TEST_ASSERT(count == 4);
	TEST_ASSERT(count == ret);

	for(i = 0; i < ARRAY_SIZE(ip_parts); ++i)
	{
		TEST_ASSERT(strcmp(ip_parts[i], items_expect[i]) == 0);
		/* printf("ip[%d] = %s\n", i, ip_parts[i]); */
	}

        str_list_free(&list);

        /* number of item in list != of number of items in array wanted */
        my_string = "foo";

        count = str_split(my_string, ".", &list);

	ret = str_list_toarray(&list, ip_parts, ARRAY_SIZE(ip_parts));

	TEST_ASSERT(count == 1);
	TEST_ASSERT(count == ret);

        str_list_free(&list);
}

int main(void)
{
        TEST_MODULE_INIT("flibc/str");

        TEST_RUN(test_str_copy);
        TEST_RUN(test_str_printf);
        TEST_RUN(test_str_cat);
        TEST_RUN(test_str_matches);
        TEST_RUN(test_str_empty);

        TEST_RUN(test_str_split);
        TEST_RUN(test_str_ltrim);
        TEST_RUN(test_str_rtrim);
        TEST_RUN(test_str_trim);

        TEST_RUN(test_str_tol);
        TEST_RUN(test_str_toll);

        TEST_RUN(test_str_list_toarray);

        return TEST_MODULE_RETURN;
}
