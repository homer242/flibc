#ifndef _FLIBC_STRING_H_
#define _FLIBC_STRING_H_

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "flibc/list.h"

/*
 * structs and functions to deal with list of string
 */
struct str_list_item {
        char *value;
        struct list_head node;
};

static inline void str_list_init(struct list_head *list)
{
        INIT_LIST_HEAD(list);
}

static inline void str_list_free(struct list_head *list)
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

/* 
 * str_cpy (aka "safe strcpy") - wrapper function to strncpy
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
size_t str_cpy(char *dst, size_t dst_size, const char *src);

/*
 * str_vprintf (aka "safe vsprintf") - wrapper function to vsnprintf
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
int str_vprintf(char *dst, size_t dst_size, const char *fmt, va_list args);

/*
 * str_printf (aka "safe sprintf") - wrapper function snprintf
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
int str_printf(char *dst, size_t dst_size, const char *fmt, ...);

/* 
 * str_cat (aka "simple strcat")
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
size_t str_cat(char *dst, size_t dst_size, const char *src);

/*
 * str_matches
 *
 *  Compare a string to a constant string.
 *
 * - Be carefull, c_str must be an constant string !
 *
 * \param data Data string
 * \param cstr Must be an constant string !
 * \return 0 if strings doesn't matches, != 0 if matches.
 */
#define str_matches(s, c_str)						\
        ({                                                              \
                const char __dummy[] = c_str;                           \
                (void)(&__dummy);                                       \
                (s != NULL && memcmp (s, c_str, sizeof(c_str)) == 0);   \
        })

/*
 * str_empty
 *
 *  Test if string is empty.
 *
 * \return 0 if string isn't empty, different from 0 if empty
 */
int str_empty(const char *str);

/*
 * str_split
 *
 *  Split string into a list of words, using sep as the word delimiter
 *
 * - Think to free list (with str_list_free()) after you finish with it;
 *
 * Example:
 *
 *      count = str_split("Hello World!", " ", &list);
 *      list_for_each_entry(item, &list, node)
 *      {
 *             // you stuff //
 *      }
 *      str_list_free(&list);
 *
 * \param str Data string
 * \param sep The word delimiter
 * \param list Pointer to an empty list where str_split put
 *             struct str_list_item items.
 * \return count of words found and stored in list
 */
unsigned int str_split(const char *str, const char *sep,
		       struct list_head *list);

/*
 * str_ltrim
 *
 * Remove space, \t, \n, \r at start of the string.
 *
 * \param str string to left trim
 * \return pointer to the string left trimed
 */
const char* str_ltrim(const char *str);

/*
 * str_rtrim
 *
 * Remove space, \t, \n, \r at end of the string.
 *
 * \param str string to right trim
 * \return string right trimed
 */
char* str_rtrim(char *str);

/*
 * str_trim
 *
 * Remove space, \t, \n, \r at start and end of the string.
 *
 * \param str string to right trim
 * \return string trimed
 */
static inline const char* str_trim(char *str)
{
	return str_ltrim(str_rtrim(str));
}

/*
 * str_tol (aka "simple strtol") - wrapper to strtol
 *
 *  Convert a string to a long integer
 *
 * - This function request new argument "dfl" unlike strtol;
 * - Check errno return. If strtol fails, return dfl value.
 *
 * \brief Convert a string to a long integer
 * \param str string to convert
 * \param endptr first character in str which is not integer
 * \param base the base of the integer in string
 * \param dfl default value if convertion failed
 * \return long integer
 */
long str_tol(const char *str, char **endptr, int base, long dfl);

/*
 * str_toll (aka "simple strtoll") - wrapper to strtoll
 *
 *  Convert a string to a long long integer
 *
 * - This function request new argument "dfl" unlike strtoll;
 * - Check errno return. If strtol fails, return dfl value.
 *
 * \param str string to convert
 * \param endptr first character in str which is not integer
 * \param base the base of the integer in string
 * \param dfl default value if convertion failed
 * \return long long integer
 */
long long str_toll(const char *str, char **endptr, int base, long long dfl);

#endif

