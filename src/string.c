#include "flc/string.h"

#include <errno.h>
#include <stdlib.h>

size_t sstrcpy(char *dst, size_t dst_size, const char *src)
{
        char *d = dst;
        const char *s = src;
        size_t n = dst_size;

        /* avoid segfault if src is NULL */
        if(src == NULL)
        {
                src = "";
                s = src;
        }

        /* Copy as many bytes as will fit */
        if(n != 0)
        {
                while(--n != 0)
                {
                        if((*d++ = *s++) == '\0')
                        {
                                break;
                        }
                }
        }

        /* Not enough room in dst, add NULL */
        if(n == 0 && dst_size != 0)
        {
                *d = '\0'; /* NULL-terminate dst */
                ++s;
        }

        return (s - src - 1); /* count does not include NULL */
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

        dlen = d - dst;
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

	return (s - src - 1); /* count does not include NULL */
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

long strtol_dfl(const char *str, long dfl)
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

long long strtoll_dfl(const char *str, long long dfl)
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
