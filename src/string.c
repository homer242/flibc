#include "flibc/string.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

size_t sstrcpy(char *dst, size_t dst_size, const char *src)
{
        size_t src_len = strlen(src);

        strncpy(dst, src, dst_size);
        dst[dst_size - 1] = '\0';

        return (src_len >= dst_size ? src_len : strlen(dst));
}

int svsprintf(char *dst, size_t size, const char *fmt, va_list args)
{
        int ret;

	ret = vsnprintf(dst, size, fmt, args);
	if(ret > (int)size - 1)
	{
		/* buffer has been truncated */
		dst[size - 1] = '\0';
	}

	return ret;
}

int ssprintf(char *dst, size_t size, const char *fmt, ...)
{
        int ret;
        va_list args;

	va_start(args, fmt);
	ret = svsprintf(dst, size, fmt, args);
	va_end(args);

	return ret;
}

size_t sstrcat(char *dst, size_t dst_size, const char *src)
{
        size_t dst_len = strlen(dst);
        size_t dst_remain_size;
        char *dst_p = NULL;
        size_t ret;

        dst_p = dst + dst_len;
        dst_remain_size = dst_size - dst_len;

        ret = sstrcpy(dst_p, dst_remain_size, src);

        return ret + dst_len;
}

int strempty(const char *str)
{
        return (str[0] == '\0');
}

unsigned int strsplit(const char *str, const char *sep, struct list_head *list)
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

const char* strltrim(const char *str)
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

char* strrtrim(char *str)
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

long sstrtol(const char *str, long dfl, int base)
{
        long ret;

        if(*str == '\0')
        {
                return dfl;
        }

        errno = 0;
        ret = strtol(str, NULL, base);
        if (errno != 0)
        {
                return dfl;
        }

        return ret;
}

long long sstrtoll(const char *str, long long dfl, int base)
{
        long long ret;

        if(*str == '\0')
        {
                return dfl;
        }

        errno = 0;
        ret = strtoll(str, NULL, base);
        if (errno != 0)
        {
                return dfl;
        }

        return ret;      
}
