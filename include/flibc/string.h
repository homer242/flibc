#ifndef _FLC_STRING_H_
#define _FLC_STRING_H_

#include <string.h>
#include <stdarg.h>

/* 
 * sstrcpy (aka "safe strcpy") - wrapper function to strncpy
 *
 *  Copy string into buffer.
 *
 *  - unlike strncpy(), destination buffer is always null terminated;
 *  - unlike strncpy(), return count of char copied (or should have 
 *    been copied if truncation occured);
 *  - if return > dst_size - 1, truncation occured.
 *
 * \param dst Destination buffer where source string will be copied
 * \param dst_size Size of destination buffer
 * \param src Source String
 * \return count of char copied (or should have been copied in case
 *                               of truncation)
 */
size_t sstrcpy(char *dst, size_t dst_size, const char *src);

/*
 * svsprintf (aka "safe vsprintf") - wrapper function to vsnprintf
 *
 *  Copy formatted output conversion into buffer.
 *
 *  - unlike vsnprintf(), destination buffer is always null terminated;
 *  - if return > dst_size - 1, truncation occured.
 *
 * \param dst Destination buffer where output will be copied
 * \param dst_size Size of destination buffer
 * \param fmt Formated string
 * \param args va_list
 * \return same return as vsnprintf
 */
int svsprintf(char *dst, size_t dst_size, const char *fmt, va_list args);

/*
 * ssprintf (aka "safe sprintf") - wrapper function ssprintf
 *
 *  Copy formatted output conversion into buffer.
 *
 *  - unlike snprintf(), destination buffer is always null terminated;
 *  - if return > dst_size - 1, truncation occured.
 *
 * \param dst Destination buffer where output will be copied
 * \param dst_size Size of destination buffer
 * \param fmt Formated string
 * \param ... The arguments
 * \return same return as snprintf
 */
int ssprintf(char *dst, size_t dst_size, const char *fmt, ...);

/* 
 * sstrcat (aka "simple strcat")
 *
 *  Concat string into buffer.
 *
 * - Be carefull, dst string buffer must be initiliazed before first call
 *   (with dst[0] = '\0' for example);
 * - destination buffer is always null terminated;
 * - unlike strncat, dst_size is the full size of dst, not space left !;
 * - copy at most dst_size - 1 characters;
 * - if return > dst_size - 1, truncation occurred.
 *
 * \param dst Destination buffer where source string will be concat
 * \param dst_size Size of destination buffer (Total size not remaining)
 * \param src Source String
 * \return total count of char in destination buffer (or should have been 
 *                                                    in buffer in case of
 *                                                    truncation)
 */
size_t sstrcat(char *dst, size_t dst_size, const char *src);

/*
 * strmatches
 *
 *  Compare a string to a constant string.
 *
 * - Be carefull, c_str must be an constant string !
 *
 * \param data Data string
 * \param cstr Must be an constant string !
 * \return 0 if strings doesn't matches, != 0 if matches.
 */
#define strmatches(s, c_str)                                            \
        ({                                                              \
                const char __dummy[] = c_str;                           \
                (void)(&__dummy);                                       \
                (s != NULL && memcmp (s, c_str, sizeof(c_str)) == 0);   \
        })

/*
 * strempty
 *
 *  Test if string is empty.
 *
 * \return 0 if string isn't empty, different from 0 if empty
 */
int strempty(const char *str);

/*
 * strltrim
 *
 * Remove space, \t, \n, \r at start of the string.
 *
 * \param str string to left trim
 * \return pointer to the string left trimed
 */
const char* strltrim(const char *str);

/*
 * strrtrim
 *
 * Remove space, \t, \n, \r at end of the string.
 *
 * \param str string to right trim
 * \return string right trimed
 */
char* strrtrim(char *str);

/*
 * strtrim
 *
 * Remove space, \t, \n, \r at start and end of the string.
 *
 * \param str string to right trim
 * \return string trimed
 */
static inline const char* strtrim(char *str)
{
	return strltrim(strrtrim(str));
}

/*
 * sstrtol (aka "simple strtol") - wrapper to strtol
 *
 *  Convert a string to a long integer
 *
 * - Check errno return. If strtol fails, return dfl value.
 *
 * \brief Convert a string to a long integer
 * \param str string to convert
 * \param dfl default value if convertion failed
 * \param base the base of the integer in string (like strtol)
 * \return long integer
 */
long sstrtol(const char *str, long dfl, int base);

/*
 * sstrtoll (aka "safe strtoll") - wrapper to strtoll
 *
 *  Convert a string to a long long integer
 *
 * - Check errno return. If strtol fails, return dfl value.
 *
 * \param str string to convert
 * \param dfl default value if convertion failed
 * \param base the base of the integer in string (like strtol)
 * \return long long integer
 */
long long sstrtoll(const char *str, long long dfl, int base);

#endif

