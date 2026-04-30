/**
 * @brief Functions to detect and convert between languages - English and Hebrew
 *
 * @author Idan Saltzman
 * @date 2024-06-07
 * @version 1.0.2
 */

#pragma once
#include <wchar.h>

/**
 * Check if the character is an English letter
 */
static inline int is_eng(wchar_t c)
{
    return ((c) >= L'a' && (c) <= L'z') || ((c) >= L'A' && (c) <= L'Z');
}

/**
 * Check if the character is a Hebrew letter
 */
static inline int is_heb(wchar_t c)
{
    return (c >= 0x05D0 && c <= 0x05EA);
}

/**
 * Convert the character to lowercase
 */
static inline wchar_t to_lower_w(wchar_t c)
{
    return (c >= L'A' && c <= L'Z') ? (c + (L'a' - L'A')) : c;
}

/**
 * @brief A mapping between English and Hebrew characters
 */
typedef struct mapping
{
    wchar_t english;
    wchar_t hebrew;
} mapping;

#define ENGLISH 0
#define HEBREW 1
#define LANG int

/**
 * @brief Get the main language of the string
 *
 * @param str The string to check
 * @param length The length of the string
 * @return int 0 if the string is in English, 1 if the string is in Hebrew
 */
LANG gmlang(const wchar_t *str, size_t length);

/**
 * @brief Convert the string to the opposite language
 *
 * @param lang The language of the string
 * @param str The string to convert
 * @param length The length of the string
 */
void map(LANG lang, wchar_t *str, size_t length);
