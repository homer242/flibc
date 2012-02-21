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

#include "flibc/str.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

size_t str_copy(char *dst, size_t dst_size, const char *src)
{
        size_t src_len = strlen(src);

        strncpy(dst, src, dst_size);
        dst[dst_size - 1] = '\0';

        return (src_len >= dst_size ? src_len : strlen(dst));
}

int str_vprintf(char *dst, size_t size, const char *fmt, va_list args)
{
        int ret;

	ret = vsnprintf(dst, size, fmt, args);
	if(ret < 0)
        {
                dst[0] = '\0';
        }
        else if(ret > (int)size - 1)
	{
		/* buffer has been truncated */
		dst[size - 1] = '\0';
	}

	return ret;
}

int str_printf(char *dst, size_t size, const char *fmt, ...)
{
        int ret;
        va_list args;

	va_start(args, fmt);
	ret = str_vprintf(dst, size, fmt, args);
	va_end(args);

	return ret;
}

size_t str_cat(char *dst, size_t dst_size, const char *src)
{
        size_t dst_len = strlen(dst);
        size_t dst_remain_size;
        char *dst_p = NULL;
        size_t ret;

        dst_p = dst + dst_len;
        dst_remain_size = dst_size - dst_len;

        ret = str_copy(dst_p, dst_remain_size, src);

        return ret + dst_len;
}

int str_empty(const char *str)
{
        return (str[0] == '\0');
}

unsigned int str_split(const char *str, const char *sep, struct list_head *list)
{
	const char *str_p = str;
	char *sep_in_str = NULL;
	size_t len_sep = strlen(sep);
        struct str_list_item *item = NULL;
        unsigned int i = 0;

        INIT_LIST_HEAD(list);

	str_p = str;
	while((sep_in_str = strstr(str_p, sep)) != NULL)
	{
		item = calloc(sizeof(*item), 1);
                item->value = strndup(str_p, (size_t)(sep_in_str - str_p));
                list_add_tail(&(item->node), list);
                ++i;

		str_p = sep_in_str + len_sep;
	}

        if(*str_p != '\0')
        {
                /* copy end of string */
                item = calloc(sizeof(*item), 1);
                item->value = strdup(str_p);
                list_add_tail(&(item->node), list);
                ++i;
        }

	return i;
}

const char* str_ltrim(const char *str)
{
        while(*str != '\0')
        {
                if(strchr(" \t\n\r", *str) == NULL)
                {
                        return str;
                }

                ++str;
        }

        return str;
}

char* str_rtrim(char *str)
{
        char *end = str + strlen(str);

        while(end-- > str)
        {
                if(strchr(" \t\n\r", *end) == NULL)
                {
                        return str;
                }

                *end = 0;
        }

        return str;
}

long str_tol(const char *str, char **endptr, int base, long dfl)
{
        long ret;

        if(*str == '\0')
        {
                return dfl;
        }

        errno = 0;
        ret = strtol(str, endptr, base);
        if (errno != 0)
        {
                return dfl;
        }

        return ret;
}

long long str_toll(const char *str, char **endptr, int base, long long dfl)
{
        long long ret;

        if(*str == '\0')
        {
                return dfl;
        }

        errno = 0;
        ret = strtoll(str, endptr, base);
        if (errno != 0)
        {
                return dfl;
        }

        return ret;      
}

void str_list_init(struct list_head *list)
{
        INIT_LIST_HEAD(list);
}

void str_list_free(struct list_head *list)
{
        struct str_list_item *item1 = NULL,
                *item2 = NULL;

        list_for_each_entry_safe(item1, item2, list, node)
        {
                free(item1->value);
                free(item1);
                list_del(&(item1->node));
        }
}

unsigned int str_list_toarray(struct list_head *list,
			      const char **array, size_t size)
{
        struct str_list_item *item1 = NULL;
        unsigned int count = 0;

        list_for_each_entry(item1, list, node)
        {
                array[count] = item1->value;

	        ++count;

		if(count == size)
		{
                        break;
		}
	}

	return count;
}
