/*
 * Copyright (c) 2011-2013 Anthony Viallard
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

TEST_DEF(test_str_catf)
{
        char buf16[16],
                buf4[4];
        const char *my_string1 = NULL,
                *my_string2 = NULL;
        size_t ret;

        /* test truncation case and null terminated */
        buf16[0] = '\0';

        my_string1 = "0123456789";
        my_string2 = "0123456789";
        ret = str_catf(buf16, sizeof(buf16), "%s%s", my_string1, my_string2);

        TEST_ASSERT(ret > sizeof(buf16) - 1);
        TEST_ASSERT(ret == (strlen(my_string1) + strlen(my_string2)));
        TEST_ASSERT(buf16[sizeof(buf16) - 1] == '\0');

        /* basic test and truncation/nullended case */
        buf16[0] = '\0';

        my_string1 = "12345";

        ret = str_catf(buf16, sizeof(buf16), "%s", my_string1);

        TEST_ASSERT(ret == strlen(my_string1));
        TEST_ASSERT(strcmp(buf16, my_string1) == 0);

        ret = str_catf(buf16, sizeof(buf16), "%s", my_string1);

        TEST_ASSERT(ret == 2 * strlen(my_string1));
        TEST_ASSERT(strcmp(buf16, "1234512345") == 0);

        ret = str_catf(buf16, sizeof(buf16), my_string1);

        TEST_ASSERT(ret == 3 * strlen(my_string1));
        TEST_ASSERT(strcmp(buf16, "123451234512345") == 0);

        ret = str_catf(buf16, sizeof(buf16), my_string1);

        TEST_ASSERT(ret > sizeof(buf16) - 1);
        TEST_ASSERT(strcmp(buf16, "123451234512345") == 0);
        TEST_ASSERT(ret == 4 * strlen(my_string1));
        TEST_ASSERT(buf16[sizeof(buf16) - 1] == '\0');

        /* format test */
        buf4[0] = '\0';

        ret = str_catf(buf4, sizeof(buf4), "%d", 4444);

        TEST_ASSERT(ret > sizeof(buf4) - 1);
        TEST_ASSERT(strcmp(buf4, "444") == 0);
        TEST_ASSERT(buf4[sizeof(buf4) - 1] == '\0');
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
        struct str_list list;
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
        str_list_for_each_entry(&list, item)
        {
                /* printf(" * item = %s | item_expect = %s\n", */
		/*        item->value, items_expect[i]); */
                TEST_ASSERT(strcmp(items_expect[i], item->value) == 0);
                ++i;
        }
        TEST_ASSERT(count == i);
        str_list_cleanup(&list);

        /* no found delimiter in string */
        const char *items_expect2[] = {
                "therearenospacehere",
        };

        my_string = "therearenospacehere";

        count = str_split(my_string, " ", &list);
        TEST_ASSERT(count == 1);
        i = 0;
        str_list_for_each_entry(&list, item)
        {
                TEST_ASSERT(strcmp(items_expect2[i], item->value) == 0);
                /* printf(" * item = %s\n", item->value); */
                ++i;
        }
        TEST_ASSERT(count == i);
        str_list_cleanup(&list);

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

        my_string = ",one,,two,,,three,,,,four,,,,,five,,,,,";

        count = str_split(my_string, ",", &list);
	/*printf(" * count = %d | expect = %ld\n",
	  count, ARRAY_SIZE(items_expect3));*/
        TEST_ASSERT(count == ARRAY_SIZE(items_expect3));
        i = 0;
        str_list_for_each_entry(&list, item)
        {
                /* printf(" * item = %s, strlen()= %zu\n", */
                /*        item->value, strlen(item->value)); */
                TEST_ASSERT(strcmp(items_expect3[i], item->value) == 0);
                ++i;
        }
        TEST_ASSERT(count == i);
        str_list_cleanup(&list);

	/* empty values */
	const char *items_expect4[] = {
                "dnsmasq",
                "",
		"",
		"",
        };

	my_string = "dnsmasq,,,";

	count = str_split(my_string, ",", &list);
        TEST_ASSERT(count == ARRAY_SIZE(items_expect4));
        i = 0;
        str_list_for_each_entry(&list, item)
        {
                /*printf(" * item = %s, strlen()= %zu\n",
		  item->value, strlen(item->value));*/
                TEST_ASSERT(strcmp(items_expect4[i], item->value) == 0);
                ++i;
        }

        str_list_cleanup(&list);
}

TEST_DEF(test_str_ltrim)
{
        const char *my_string = NULL,
                *ret = NULL;

        /* basic test */
        my_string = " \t  \n \v \r   Hello\n\r\n\t \v";

        ret = str_ltrim_blanks(my_string);

        TEST_ASSERT(strcmp(ret, "Hello\n\r\n\t \v") == 0);

        /* empty string */
        my_string = "";

        ret = str_ltrim_blanks(my_string);

        TEST_ASSERT(strcmp(ret, "") == 0);

        /* zzzzemptyzzzz */
        my_string = "zzzzemptyzzzz";

        ret = str_ltrim(my_string, "z");

        TEST_ASSERT(strcmp(ret, "emptyzzzz") == 0);
}

TEST_DEF(test_str_rtrim)
{
        char *my_string = NULL,
                *ret = NULL;

        /* basic test */
        my_string = strdup(" \t  \n  \r \v  Hello\n\r\n\t \v");

        ret = str_rtrim_blanks(my_string);

        TEST_ASSERT(strcmp(ret, " \t  \n  \r \v  Hello") == 0);

        free(my_string);

        /* empty string */
        my_string = strdup("");

        ret = str_rtrim_blanks(my_string);

        TEST_ASSERT(strcmp(ret, "") == 0);

        free(my_string);

        /* zzzzemptyzzzz */
        my_string = strdup("zzzzemptyzzzz");

        ret = str_rtrim(my_string, "z");

        TEST_ASSERT(strcmp(ret, "zzzzempty") == 0);

        free(my_string);
}

TEST_DEF(test_str_trim)
{
        char *my_string = NULL;
        const char *ret = NULL;

        /* basic test */
        my_string = strdup(" \t  \n  \r   Hello\n\r\n\t ");

        ret = str_trim_blanks(my_string);

        TEST_ASSERT(strcmp(ret, "Hello") == 0);

        free(my_string);

        /* empty string */
        my_string = strdup("");

        ret = str_trim_blanks(my_string);

        TEST_ASSERT(strcmp(ret, "") == 0);

        free(my_string);

        /* aaaaemptyzzzz */
        my_string = strdup("aaaaemptyzzzz");

        ret = str_trim(my_string, "az");

        TEST_ASSERT(strcmp(ret, "empty") == 0);

        free(my_string);
}

TEST_DEF(test_str_startwith)
{
        TEST_ASSERT(str_startwith("hello world", "hello"));
        TEST_ASSERT(!str_startwith("hello world", "ello"));

        TEST_ASSERT(!str_startwith("hell", "hello"));
}

TEST_DEF(test_str_endwith)
{
        TEST_ASSERT(str_endwith("hello world", "world"));
        TEST_ASSERT(!str_endwith("hello world", "worl"));

        TEST_ASSERT(!str_endwith("orld", "world"));
}

TEST_DEF(test_str_replace)
{
        char buffer[256],
                buf16[16];
        int ret;

        /* simple test */
        ret = str_replace("http://www.github.com/",
                          "http", "flocfloc",
                          buffer, sizeof(buffer));

        TEST_ASSERT(ret == 0);
        TEST_ASSERT(strcmp(buffer, "flocfloc://www.github.com/") == 0);

        /* test truncation */
        ret = str_replace("01234567890123456789",
                          "1", "0",
                          buf16, sizeof(buf16));

        TEST_ASSERT(ret != 0);
        TEST_ASSERT(strcmp(buf16, "002345678900234") == 0);
        TEST_ASSERT(buf16[sizeof(buf16) - 1] == '\0');
}

TEST_DEF(test_str_lcut)
{
        const char *p = NULL;

        /* simple test */
        p = str_lcut("http://www.linux.org", "http://");

        TEST_ASSERT(strcmp("www.linux.org", p) == 0);

        /* no cut this ! */
        p = str_lcut("xhttp://www.linux.org", "http://");

        TEST_ASSERT(strcmp("xhttp://www.linux.org", p) == 0);
}

TEST_DEF(test_str_rcut)
{
        char buf256[256];
        char *p = NULL;

        /* simple test */
        snprintf(buf256, sizeof(buf256), "mynameisnobody.txt");

        p = str_rcut(buf256, ".txt");

        TEST_ASSERT(strcmp("mynameisnobody", p) == 0);

        /* no cut this ! */
        snprintf(buf256, sizeof(buf256), "mynameisnobody.txt");

        p = str_rcut(buf256, ".tx");

        TEST_ASSERT(strcmp("mynameisnobody.txt", p) == 0);
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
	struct str_list list;
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
		/* printf("ip[%d] = %s\n", i, ip_parts[i]); */
		TEST_ASSERT(strcmp(ip_parts[i], items_expect[i]) == 0);
	}

        str_list_cleanup(&list);

        /* number of item in list != of number of items in array wanted */
        my_string = "foo";

        count = str_split(my_string, ".", &list);

	ret = str_list_toarray(&list, ip_parts, ARRAY_SIZE(ip_parts));

	TEST_ASSERT(count == 1);
	TEST_ASSERT(count == ret);

        str_list_cleanup(&list);
}

TEST_DEF(test_str_list_add_remove)
{
	struct str_list str_list;
	struct str_list_item *str_list_item;
        const char *items[] = {
                "the world is crazy",
                "allright",
                "one good thing about music",
                "when it hurts you, you feel no pain",
                "allright",
        };
        unsigned int found,
		i;

	str_list_init(&str_list);

	for(i = 0; i < ARRAY_SIZE(items); ++i)
	{
		TEST_ASSERT(str_list_add(&str_list, items[i]) == 0);
	}

	str_list_for_each_entry(&str_list, str_list_item)
	{
		for(i = 0; i < ARRAY_SIZE(items); ++i)
		{
			found = 0;
			if(strcmp(str_list_item->value,
				  items[i]) == 0)
			{
				found = 1;
				break;
			}
		}

		TEST_ASSERT(found);
	}

	TEST_ASSERT(str_list_remove(&str_list, "allright") == 2);

	found = 0;
	str_list_for_each_entry(&str_list, str_list_item)
	{
		if(strcmp(str_list_item->value, "allright") == 0)
		{
			++found;
		}
	}

	TEST_ASSERT(found == 0);

	str_list_cleanup(&str_list);
}

int main(void)
{
        TEST_MODULE_INIT("flibc/str");

        TEST_RUN(test_str_copy);
        TEST_RUN(test_str_printf);
        TEST_RUN(test_str_cat);
        TEST_RUN(test_str_catf);
        TEST_RUN(test_str_matches);
        TEST_RUN(test_str_empty);

        TEST_RUN(test_str_split);
        TEST_RUN(test_str_ltrim);
        TEST_RUN(test_str_rtrim);
        TEST_RUN(test_str_trim);

        TEST_RUN(test_str_startwith);
        TEST_RUN(test_str_endwith);

        TEST_RUN(test_str_replace);

        TEST_RUN(test_str_lcut);
        TEST_RUN(test_str_rcut);

        TEST_RUN(test_str_tol);
        TEST_RUN(test_str_toll);

        TEST_RUN(test_str_list_toarray);
        TEST_RUN(test_str_list_add_remove);

        return TEST_MODULE_RETURN;
}
