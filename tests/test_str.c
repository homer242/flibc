#include <flibc/string.h>
#include <flibc/flibc.h>
#include <flibc/math.h>

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

        TEST_ASSERT(ret == 0,
                    "Return of empty string copy invalid (ret=%zu != 0)",
                    ret);

        TEST_ASSERT(strcmp(buf1, my_string) == 0,
                    "Copy of \"\" in buf of 1 byte ('%s') failed",
                    buf1);

        /* copy of normal string without truncated case */
        my_string = "Hello world !";

        ret = sstrcpy(buf16, sizeof(buf16), my_string);

        TEST_ASSERT(ret == strlen(buf16),
                    "condition ret=%zu == strlen(%s)=%zu failed",
                    ret, buf16, strlen(buf16));

        TEST_ASSERT(strcmp(buf16, my_string) == 0,
                    "condition strcmp(%s, %s) == 0 failed",
                    buf16, my_string);

        /* test return string copied is truncated */
        my_string = "foobarfoobarfoobarfoo";

        ret = sstrcpy(buf16, sizeof(buf16), my_string);

        TEST_ASSERT(ret > sizeof(buf16) - 1,
                    "Return in truncated case is invalid !(ret=%zu > sizeof(buf16) - 1)",
                    ret);

        TEST_ASSERT(ret == strlen(my_string),
                    "ret=%zu != strlen(%s)=%zu",
                    ret, my_string, strlen(my_string));
}

TEST_DEF(test_sstrcpy_nullended)
{
        size_t ret;
        char buf[16];
        char fmt[17] = "0123456789123456";

        ret = sstrcpy(buf, sizeof(buf), fmt);

        TEST_ASSERT(ret > sizeof(buf) - 1,
                    "condition ret=%zu > sizeof(buf)=%zu  - 1",
                    ret, sizeof(buf));

        TEST_ASSERT(ret == strlen(fmt),
                    "ret(=%zu) != strlen(%s)(=%zu)",
                    ret, fmt, strlen(fmt));

        TEST_ASSERT(buf[sizeof(buf) - 1] == '\0',
                    "buf isn't NULL ended : %c",
                    buf[sizeof(buf) - 1]);

        TEST_ASSERT(strncmp(fmt, buf, sizeof(buf) - 1) == 0,
                    "strncmp(%s, %s, %zu) != 0 !",
                    buf, fmt, sizeof(buf) - 1);
}

TEST_DEF(test_strmatches)
{
        char buf[16];
        char *null_str = NULL;

        TEST_ASSERT(!strmatches(null_str, "teststring"),
                    "matches (NULL, string) return true");

        snprintf(buf, sizeof(buf),
                 "teststring");

        TEST_ASSERT(strmatches(buf, "teststring"),
                    "matches (%s, %s) return false",
                    buf, "teststring");

        TEST_ASSERT(!strmatches(buf, "test"),
                    "matches (%s, %s) return true",
                    buf, "test");

        TEST_ASSERT(!strmatches(buf, ""),
                    "matches (%s, %s) return true",
                    buf, "");
}

TEST_DEF(test_sstrcat)
{
        unsigned int i;
        char buf[12] = "";
        size_t ret;
        unsigned int m;

#define STR1 "0foobar1foobar2"
#define STR2 "0foobar1foobar2foobar3foobar4"
        const char *strs[] = {
                "",
                STR1,
                STR2,
        };

        for(i = 0; i < ARRAY_SIZE(strs); ++i)
        {
                m = min(strlen(strs[i]),
                        sizeof(buf) - 1 - strlen(buf));
                ret = sstrcat(buf, sizeof(buf), strs[i]);

                TEST_ASSERT(ret == m,
                            "cat return invalid %zu != %d",
                            ret, m);
        }
                
        TEST_ASSERT(strncmp(buf, STR1 STR2, sizeof(buf) - 1) == 0,
                    "cat failed (%s, %.*s)",
                    buf, (int)sizeof(buf) - 1, STR1 STR2);
#undef STR1
#undef STR2
}

TEST_DEF(test_ssprintf_nullended)
{
        int ret;
        char buf[16];
        char fmt[17] = "0123456789123456";

        ret = ssprintf(buf, sizeof(buf), fmt);

        /* printf(" * fmt = %s\n", fmt); */
        /* printf(" * buf = %s\n", buf); */
        /* printf(" * ret = %d\n", ret); */

        TEST_ASSERT(ret == (int)strlen(fmt),
                    "ret(=%d) != strlen(%s)(=%zu)",
                    ret, fmt, strlen(fmt));

        TEST_ASSERT(buf[sizeof(buf) - 1] == '\0',
                    "buf isn't NULL ended : %c",
                    buf[sizeof(buf) - 1]);

        TEST_ASSERT(strncmp(fmt, buf, sizeof(buf) - 1) == 0,
                    "strncmp(%s, %s, %zu) != 0 !",
                    buf, fmt, sizeof(buf) - 1);
}

TEST_DEF(test_strempty)
{
        TEST_ASSERT(strempty(""), "Empty string seems to be not empty ?!?");

        TEST_ASSERT(!strempty("a"), "strempty(a) return true instead of false");

        TEST_ASSERT(!strempty("Hello World !"),
                    "strempty(Hello World !) return true instead of false");
}

int main(void)
{
        TEST_MODULE_INIT("flc_str");

        TEST_RUN(test_sstrcpy);
        TEST_RUN(test_sstrcpy_nullended);

        TEST_RUN(test_strmatches);

        TEST_RUN(test_sstrcat);

        TEST_RUN(test_ssprintf_nullended);

        TEST_RUN(test_strempty);

        return TEST_MODULE_RETURN;
}
