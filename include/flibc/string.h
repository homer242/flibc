#ifndef _FLC_STRING_H_
#define _FLC_STRING_H_

#include <string.h>
#include <stdarg.h>

/* 
 * sstrcpy (aka "safe strcpy") - wrapper function to strncpy
 *
 *  - always NULL terminated the destination buffer;
 *  - if src == NULL, copy "" in destination buffer;
 *  - unlike strncpy(), return count of char copied.
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
 * \return same return as vsnprintf
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
 * \return same return as snprintf
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
 * - if src == NULL, concat "" in dst buffer;
 * - dst buffer must be initialized with \0 before first call.
 *
 * \brief Concat string into buffer string.
 * \param dst Destination buffer where source string will be concat
 * \param dst_size Size of destination buffer (Total size not remaining)
 * \param src Source String
 * \return size count of char copied
 */
size_t sstrcat(char *dst, size_t dst_size, const char *src);

/*
 * sstrcmp - wrapper function to strcmp
 *
 * aka "safe strcmp"
 *
 * - If str1 or str2 pointers are NULL, set to empty string
 *   to avoid SEGFAULT.
 *
 * \brief Compare two strings
 * \param str1 First string
 * \param str2 Second string
 * \return same return as strcmp
 */
int sstrcmp(const char *str1, const char *str2);

/*
 * sstrncmp - wrapper function to strncmp
 *
 * aka "safe strncmp"
 *
 * - If str1 or str2 pointers are NULL, set to empty string
 *   to avoid SEGFAULT.
 *
 * \brief Compare two strings
 * \param str1 First string
 * \param maxsize Max count of caracters compared
 * \param str2 Second string
 * \return same return as strcmp
 */
int sstrncmp(const char *str1, size_t maxsize, const char *str2);

/*
 * strmatches
 *
 * - if s == NULL, return 0;
 * - Be carefull, c_str must be an constant string. No NULL check.
 * 
 * \brief Compare string to a constant string.
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
 * - if str == NULL, return int != 0.
 *
 * \brief Test if string is empty.
 * \return 0 if string isn't empty, != 0 if empty or NULL.
 */
int strempty(const char *str);

/*
 * strltrim
 *
 * - if str == NULL, return NULL.
 *
 * \brief Remove space, \t, \n, \r at start of the string.
 * \param str string to left trim
 * \return pointer to the string left trimed, or NULL if str is NULL
 */
const char* strltrim(const char *str);

/*
 * strrtrim
 *
 * - if str == NULL, return NULL.
 *
 * \brief Remove space, \t, \n, \r at end of the string.
 * \param str string to right trim
 * \return string right trimed, or NULL if str is NULL
 */
char* strrtrim(char *str);

/*
 * strtrim
 *
 * - if str == NULL, return NULL.
 *
 * \brief Remove space, \t, \n, \r at start and end of the string.
 * \param str string to right trim
 * \return string trimed, or NULL if str is NULL
 */
static inline const char* strtrim(char *str)
{
	return strltrim(strrtrim(str));
}

/*
 * sstrtol - wrapper to strtol
 *
 * aka "safe strtol"
 *
 * - If string is NULL or empty, return dfl value.
 *
 * \brief Convert a string to a long integer
 * \param str string to convert
 * \param dfl default value if convertion failed
 * \return long integer
 */
long sstrtol(const char *str, long dfl);

/*
 * sstrtoll - wrapper to strtoll
 *
 * aka "safe strtoll"
 *
 * - If string is NULL or empty, return dfl value.
 *
 * \brief Convert a string to a long long integer
 * \param str string to convert
 * \param dfl default value if convertion failed
 * \return long long integer
 */
long long sstrtoll(const char *str, long long dfl);

#endif

