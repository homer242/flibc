#ifndef _FLC_STRING_H_
#define _FLC_STRING_H_

#include <string.h>
#include <stdarg.h>

/* 
 * sstrcpy (aka "safe strcpy") - wrapper function to strncpy
 *
 *  - always NULL terminated the destination buffer
 *  - if src == NULL, copy "" in destination buffer.
 *  - unlike strncpy(), return count of char copied
 *
 * \brief Copy string into buffer.
 * \param dst Destination buffer where source string will be copied
 * \param dst_size Size of destination buffer
 * \param src Source String
 * \return size count of char copied
 */
size_t sstrcpy(char *dst, size_t dst_size, const char *src);

/*
 * svsprintf
 *
 * aka "safe vsprintf"
 *
 * it's a vnsprintf wrapper which certified the buffer (str) will
 * be always NULL terminated.
 *
 * \brief Copy formated string with its arguments into buffer.
 * \param dst Destination buffer where output will be copied
 * \param dst_size Size of destination buffer
 * \param fmt Formated string
 * \param args va_list
 * \return same return than vsnprintf
 */
int svsprintf(char *dst, size_t dst_size, const char *fmt, va_list args);

/*
 * ssprintf
 *
 * aka "safe sprintf"
 *
 * it's a snprintf wrapper which certified the buffer (str) will
 * be always NULL terminated.
 *
 * \brief Copy formated string with its arguments into buffer.
 * \param dst Destination buffer where output will be copied
 * \param dst_size Size of destination buffer
 * \param fmt Formated string
 * \param ... The arguments
 * \return same return than snprintf
 */
int ssprintf(char *dst, size_t dst_size, const char *fmt, ...);

/* 
 * sstrcat
 *
 * aka "safe strcat"
 *
 * Appends src to string dst of size dst_size (unlike strncat, dst_size is the
 * full size of dst, not space left).  At most dst_size-1 characters
 * will be copied.  Always NULL terminates (unless dst_size <= strlen(dst)).
 * If strlen(src) >= dst_size - strlen(dst), truncation occurred.
 *
 * if src == NULL, concat "" in dst buffer.
 *
 * dst buffer must be initialized with \0 before first call
 *
 * \brief Concat string into buffer string.
 * \param dst Destination buffer where source string will be concat
 * \param dst_size Size of destination buffer (Total size not remaining)
 * \param src Source String
 * \return size count of char copied
 */
size_t sstrcat(char *dst, size_t dst_size, const char *src);

/*
 * \brief Compare string to a constant string.
 * \param data Data string
 * \param cstr Constant string
 */
#define strmatches(s, c_str)                                    \
        ({                                                      \
                const char __dummy[] = c_str;                   \
                (void)(&__dummy);                               \
                (memcmp (s, c_str, sizeof(c_str)) == 0);        \
        })

/*
 * \brief Test if string is empty.
 * \return 0 if str is empty or NULL, -1 otherwise
 */
int strempty(const char *str);

/*
 * Remove space, \t, \n, \r at start of the string.
 *
 * \param str string to left trim
 * \return pointer to the string left trimed
 */
const char * strltrim(const char *str);

/*
 * Remove space, \t, \n, \r at end of the string.
 *
 * \param str string to right trim
 * \return string right trimed
 */
char * strrtrim(char *str);

/*
 * Remove space, \t, \n, \r at start and end of the string.
 *
 * \param str string to right trim
 * \return string trimed
 */
static inline const char * strtrim(char *str)
{
	return strltrim(strrtrim(str));
}

/*
 * Convert a string to a long integer
 *
 * \param str string to convert
 * \param dfl default value if convertion failed
 * \return long integer
 */
long sstrtol(const char *str, long dfl);

/*
 * Convert a string to a long long integer
 *
 * \param str string to convert
 * \param dfl default value if convertion failed
 * \return long long integer
 */
long long sstrtoll(const char *str, long long dfl);

#endif

