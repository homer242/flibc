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

#include "flibc/io.h"
#include "flibc/math.h"

#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

ssize_t io_write(int fd, const void *buf, size_t len)
{
	ssize_t cc;
	ssize_t total;

	total = 0;
	while(len != 0)
        {
                do
                {
                        cc = write(fd, buf, len);
                }
                while(cc < 0 && errno == EINTR);

		if(cc < 0)
                {
			return cc;
                }

		total += cc;
		buf = ((const char *)buf) + cc;
		len -= (size_t)cc;
	}

	return total;
}

ssize_t io_read(int fd, void *dst, size_t len)
{
	ssize_t cc;
	ssize_t total;

	total = 0;
	while(len != 0)
        {
                do 
                {
                        cc = read(fd, dst, len);
                }
                while(cc < 0 && errno == EINTR);

		if(cc < 0)
                {
			return cc;
                }

		if(cc == 0)
                {
			break;
                }

		dst = ((char *)dst) + cc;
		total += cc;
		len -= (size_t)cc;
	}

	return total;
}

ssize_t io_file_write(const char *filename, const void *buf, size_t len)
{
	int fd;
	ssize_t count;

	fd = open(filename,
                  O_CREAT | O_WRONLY,
                  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if(fd < 0)
        {
		return -1;
        }

	count = io_write(fd, buf, len);

	close(fd);

	return count;
}

ssize_t io_file_read(const char *filename, void *dst, size_t len)
{
        int fd;
	ssize_t count;

	fd = open(filename, O_RDONLY);
	if(fd < 0)
        {
		return -1;
        }

	count = io_read(fd, dst, len);

	close(fd);

	return count;
}
