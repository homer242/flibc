#include <flibc/string.h>
#include <flibc/flibc.h>
#include <flibc/math.h>
#include <flibc/list.h>

#include "libtest.h"

TEST_DEF(test_sstrcpy)
{
        char buf1[1];
        char buf16[16];
        size_t ret;

        const char *my_string = NULL;

        /* copy of empty string */
        my_string = "";

        ret = sstrcpy(buf1, sizeof(buf1), my_string);

        TEST_ASSERT(ret == 0);
        TEST_ASSERT(strcmp(buf1, my_string) == 0);

        /* copy of normal string without truncated case */
        my_string = "Hello world !";

        ret = sstrcpy(buf16, sizeof(buf16), my_string);

        TEST_ASSERT(ret == strlen(buf16));
        TEST_ASSERT(strcmp(buf16, my_string) == 0);

        /* test return string copied is truncated and NULL terminated */
        my_string = "foobarfoobarfoobarfoo";

        ret = sstrcpy(buf16, sizeof(buf16), my_string);

        TEST_ASSERT(ret > sizeof(buf16) - 1);
        TEST_ASSERT(ret == strlen(my_string));
        TEST_ASSERT(buf16[sizeof(buf16) - 1] == '\0');
        TEST_ASSERT(strncmp(my_string, buf16, sizeof(buf16) - 1) == 0);
}

TEST_DEF(test_ssprintf)
{
        char buf16[16];
        int ret;

        const char *my_string = NULL;

        /* test truncation case and null terminated */
        my_string = "0123456789012345";

        ret = ssprintf(buf16, sizeof(buf16), "%s", my_string);

        TEST_ASSERT(ret > (int)sizeof(buf16) - 1);
        TEST_ASSERT(ret == (int)strlen(my_string));
        TEST_ASSERT(buf16[sizeof(buf16) - 1] == '\0');
}

TEST_DEF(test_sstrcat)
{
        char buf16[16];
        const char *my_string = NULL;
        size_t ret;

        /* test truncation case and null terminated */
        buf16[0] = '\0';

        my_string = "01234567890123456789";
        ret = sstrcat(buf16, sizeof(buf16), my_string);

        TEST_ASSERT(ret > sizeof(buf16) - 1);
        TEST_ASSERT(ret == strlen(my_string));
        TEST_ASSERT(buf16[sizeof(buf16) - 1] == '\0');

        /* basic test and truncation/nullended case */
        buf16[0] = '\0';

        my_string = "12345";

        ret = sstrcat(buf16, sizeof(buf16), my_string);

        TEST_ASSERT(ret == strlen(my_string));
        TEST_ASSERT(strcmp(buf16, my_string) == 0);

        ret = sstrcat(buf16, sizeof(buf16), my_string);

        TEST_ASSERT(ret == 2 * strlen(my_string));
        TEST_ASSERT(strcmp(buf16, "1234512345") == 0);

        ret = sstrcat(buf16, sizeof(buf16), my_string);

        TEST_ASSERT(ret == 3 * strlen(my_string));
        TEST_ASSERT(strcmp(buf16, "123451234512345") == 0);

        ret = sstrcat(buf16, sizeof(buf16), my_string);

        TEST_ASSERT(ret > sizeof(buf16) - 1);
        TEST_ASSERT(ret == 4 * strlen(my_string));
        TEST_ASSERT(buf16[sizeof(buf16) - 1] == '\0');
}

TEST_DEF(test_strmatches)
{
        char buf[16];

        snprintf(buf, sizeof(buf), "teststring");

        TEST_ASSERT(strmatches(buf, "teststring"));
        TEST_ASSERT(!strmatches(buf, "test"));
        TEST_ASSERT(!strmatches(buf, ""));
}

TEST_DEF(test_strempty)
{
        TEST_ASSERT(strempty(""));
        TEST_ASSERT(!strempty("a"));
        TEST_ASSERT(!strempty("Hello World !"));
}

TEST_DEF(test_strsplit)
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

        count = strsplit(my_string, " ", &list);

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

        count = strsplit(my_string, " ", &list);
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

        count = strsplit(my_string, " ", &list);
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

int main(void)
{
        TEST_MODULE_INIT("flibc/string");

        TEST_RUN(test_sstrcpy);
        TEST_RUN(test_ssprintf);
        TEST_RUN(test_sstrcat);
        TEST_RUN(test_strmatches);
        TEST_RUN(test_strempty);

        TEST_RUN(test_strsplit);

        return TEST_MODULE_RETURN;
}
