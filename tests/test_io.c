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

#define ENABLE_VT102_COLOR 1
#include <flibc/str.h>
#include <flibc/flibc.h>
#include <flibc/math.h>
#include <flibc/unit.h>
#include <flibc/io.h>

#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

TEST_DEF(test_io_write_and_read)
{
        int fd;
        const char *str_to_wr = NULL;
        ssize_t ret;
        char buf[128];
        char little_buf[8];

        str_to_wr = "hello there !";

        /* write */
        fd = open("/tmp/test_io_write", O_CREAT | O_WRONLY, 0666);

        TEST_ASSERT(fd >= 0);

        ret = io_write(fd, str_to_wr, strlen(str_to_wr));

        TEST_ASSERT(ret == (ssize_t)strlen(str_to_wr));

        close(fd);

        /* reopen, read and compare */
        fd = open("/tmp/test_io_write", O_RDONLY);

        TEST_ASSERT(fd >= 0);

        ret = io_read(fd, buf, sizeof(buf));

        TEST_ASSERT(ret == (ssize_t)strlen(str_to_wr));
	buf[ret] = '\0';
        TEST_ASSERT(strcmp(str_to_wr, buf) == 0);

        close(fd);

        /* reopen, read and compare */
        fd = open("/tmp/test_io_write", O_RDONLY);

        TEST_ASSERT(fd >= 0);

        ret = io_read(fd, little_buf, sizeof(little_buf));

        TEST_ASSERT(ret != (ssize_t)strlen(str_to_wr)
                    && ret == sizeof(little_buf));
        TEST_ASSERT(strncmp(str_to_wr, little_buf, sizeof(little_buf)) == 0);

        close(fd);

        unlink("/tmp/test_io_write");
}

TEST_DEF(test_io_file_write_and_read)
{
        ssize_t ret;
        const char *str_to_wr = NULL;
        char buf[128];
        char little_buf[8];

        str_to_wr = "hello there !";

        /* write */
        ret = io_file_write("/tmp/test_io_write", str_to_wr, strlen(str_to_wr));

        TEST_ASSERT(ret == (ssize_t)strlen(str_to_wr));

        /* reopen, read and compare */
        ret = io_file_read("/tmp/test_io_write", buf, sizeof(buf));

        TEST_ASSERT(ret == (ssize_t)strlen(str_to_wr));
	buf[ret] = '\0';
        TEST_ASSERT(strcmp(str_to_wr, buf) == 0);

        /* reopen, read and compare */
        ret = io_file_read("/tmp/test_io_write", little_buf, sizeof(little_buf));

        TEST_ASSERT(ret != (ssize_t)strlen(str_to_wr)
                    && ret == sizeof(little_buf));
        TEST_ASSERT(strncmp(str_to_wr, little_buf, sizeof(little_buf)) == 0);

        unlink("/tmp/test_io_write");
}

int main(void)
{
        TEST_MODULE_INIT("flibc/io");

        TEST_RUN(test_io_write_and_read);

        TEST_RUN(test_io_file_write_and_read);

        return TEST_MODULE_RETURN;
}
