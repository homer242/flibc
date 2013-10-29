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

#ifndef _FLIBC_IO_H_
#define _FLIBC_IO_H_

#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

/*
 * io_write
 *
 *  Write data in file by his descriptor
 *
 * \param fd File descriptor
 * \param buf Source pointer
 * \param len Number of byte being copied from the source pointer
 * \return The number of byte written or -1 to indicate error
 */
ssize_t io_write(int fd, const void *buf, size_t len);

/*
 * io_read
 *
 *  Read data from file by his descriptor
 *
 * \param fd File descriptor
 * \param dst Destination pointer
 * \param len Number of byte being read and copied to destination pointer
 * \return The number of byte actually read (less or egal to len)
 *         or -1 to indicate error
 */
ssize_t io_read(int fd, void *dst, size_t len);

/*
 * io_file_write
 *
 *  Write data in file by his filename
 *
 * \param filename File name
 * \param buf Source pointer
 * \param len Number of byte being copied from the source pointer
 * \return The number of byte written or -1 to indicate error
 */
ssize_t io_file_write(const char *filename, const void *buf, size_t len);

/*
 * io_file_read
 *
 *  Read data from file by his filename
 *
 * \param fd File descriptor
 * \param dst Destination pointer
 * \param len Number of byte being read and copied to destination pointer
 * \return The number of byte actually read (less or egal to len)
 *         or -1 to indicate error
 */
ssize_t io_file_read(const char *filename, void *dst, size_t len);

#endif
