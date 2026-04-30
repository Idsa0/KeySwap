/**
 * @brief This program reads a string from the clipboard, determines the language of the string, maps the string to the other language, and writes the mapped string back to the clipboard.
 *
 * @author Idan Saltzman
 * @date 2024-06-07
 * @version 1.0.1
 */

#include "clipboard.h"
#include "keyboard.h"

/* Use a byte-budgeted MAX to avoid accidental oversized stack allocations. */
#define MAX_BYTES (512 * 1024)
#define MAX (MAX_BYTES / sizeof(wchar_t))

int main(void)
{
    wchar_t str[MAX];
    int len = get_string(str, MAX);
    if (len == -1)
        /* This happens when the clipboard is empty, not text, or larger than MAX */
        return 1;

    LANG lang = gmlang(str, (size_t)len);
    map(lang, str, (size_t)len);

    if (put_string(str) == -1)
        return 1;

    return 0;
}
