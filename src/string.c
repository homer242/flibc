#include "flibc/string.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

size_t sstrcpy(char *dst, size_t dst_size, const char *src)
{
        /* avoid segfault if src is NULL */
        if(src == NULL)
        {
                src = "";
        }

        strncpy(dst, src, dst_size);
        dst[dst_size - 1] = '\0';

        return strlen(dst);
}

int svsprintf(char *dst, size_t size, const char *fmt, va_list args)
{
        int ret;

        dst[size - 1] = '\0';

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
        char *d = dst;
        const char *s = src;
        size_t n = dst_size;
        size_t dlen;

        /* avoid segfault if src is NULL */
        if(src == NULL)
        {
                src = "";
                s = src;
        }

        /* Find the end of dst and adjust bytes left but don't go past end */
        while(n-- != 0 && *d != '\0')
        {
                ++d;
        }

        dlen = (size_t)(d - dst);
        n = dst_size - dlen;

        if(n == 0)
        {
                return 0;
        }

        while(--n != 0)
        {
                if((*d++ = *s++) == '\0')
                {
                        break;
                }
        }

        /* Not enough room in dst, add NULL */
        if(n == 0)
        {
                *d = '\0'; /* NULL-terminate dst */
                ++s;
        }

	return (size_t)(s - src - 1); /* count does not include NULL */
}

int strempty(const char *str)
{
        return (str == NULL || str[0] == '\0');
}

const char * strltrim(const char *str)
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

char * strrtrim(char *str)
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

long sstrtol(const char *str, long dfl)
{
        long ret;

        if(str == NULL || *str == '\0')
        {
                return dfl;
        }

        errno = 0;
        ret = strtol(str, NULL, 10);
        if (errno != 0)
        {
                return dfl;
        }

        return ret;
}

long long sstrtoll(const char *str, long long dfl)
{
        long long ret;

        if(str == NULL || *str == '\0')
        {
                return dfl;
        }

        errno = 0;
        ret = strtoll(str, NULL, 10);
        if (errno != 0)
        {
                return dfl;
        }

        return ret;      
}
