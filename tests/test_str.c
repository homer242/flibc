#include <flibc/string.h>
#include <flibc/flibc.h>
#include <flibc/math.h>

#include "libtest.h"

TEST_DEF(test_sstrcpy)
{
        unsigned int i;
        char buf1[1];
        char buf16[16];
        size_t ret;
        unsigned int m;

        const char * strs[] = {
                "",
                "0foobar1foobar2",
                "0foobar1foobar2foobar3foobar4",
        };

        for(i = 0; i < ARRAY_SIZE(strs); ++i)
        {
                /* 1 byte buffer */
                m = min(sizeof(buf1) - 1, strlen(strs[i]));
                ret = sstrcpy(buf1, sizeof(buf1), strs[i]);

                TEST_ASSERT(m == ret,
                            "Invalid copy (ret=%zu != %d)",
                            ret, m);

                TEST_ASSERT(strncmp(buf1, strs[i], m) == 0,
                            "Copy of '%s' in buf of 1 byte ('%s') failed",
                            strs[i],
                            buf1);

                /* 16 byte buffer */
                m = min(sizeof(buf16) - 1, strlen(strs[i]));
                ret = sstrcpy(buf16, sizeof(buf16), strs[i]);

                TEST_ASSERT(m == ret,
                            "Invalid copy (ret=%zu != %d)",
                            ret, m);

                TEST_ASSERT(strncmp(buf16, strs[i], m) == 0,
                            "Copy of '%s' in buf of 1 byte ('%s') failed",
                            strs[i],
                            buf16);
        }
}

TEST_DEF(test_sstrcpy_null)
{
        char buf[16] = "  d  ";
        size_t ret;

        ret = sstrcpy(buf, sizeof(buf), NULL);

        TEST_ASSERT(ret == 0,
                    "Invalid return %zu !",
                    ret);

        TEST_ASSERT(strcmp(buf, "") == 0,
                    "Invalid copy (%s) !",
                    buf);
}

TEST_DEF(test_strmatches)
{
        char buf[16];

        snprintf(buf, sizeof(buf),
                 "teststring");

#define STR1 "teststring"
        TEST_ASSERT(strmatches(buf, STR1),
                    "matches (%s, %s) failed",
                    buf, STR1);
#undef STR1

#define STR1 "test"
        TEST_ASSERT(!strmatches(buf, STR1),
                    "matches (%s, %s) failed",
                    buf, STR1);
#undef STR1

#define STR1 ""
        TEST_ASSERT(!strmatches(buf, STR1),
                    "matches (%s, %s) failed",
                    buf, STR1);
#undef STR1
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

TEST_DEF(test_sstrcat_null)
{
        char buf[16] = "  d  ";
        size_t ret;

        ret = sstrcat(buf, sizeof(buf), NULL);

        TEST_ASSERT(ret == 0,
                    "Invalid return %zu !",
                    ret);

        TEST_ASSERT(strcmp(buf, "  d  ") == 0,
                    "Invalid copy (%s) !",
                    buf);
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

int main(void)
{
        TEST_MODULE_INIT("flc_str");

        TEST_RUN(test_sstrcpy);

        TEST_RUN(test_sstrcpy_null);

        TEST_RUN(test_strmatches);

        TEST_RUN(test_sstrcat);

        TEST_RUN(test_sstrcat_null);

        TEST_RUN(test_ssprintf_nullended);

        return TEST_MODULE_RETURN;
}
