/**
 * @brief This program reads a string from the clipboard, determines the language of the string, maps the string to the other language, and writes the mapped string back to the clipboard.
 *
 * @author Idan Saltzman
 * @date 2024-06-07
 * @version 1.0.1
 */

#include "clipboard.h"
#include "keyboard.h"

#define MAX 0x80000 // 512KB

int main()
{
    wchar_t str[MAX];
    size_t len = get_string(str);
    if (len == -1)
        // This happens when the clipboard is empty or contains data that is not a string
        return EXIT_FAILURE;

    int lang = gmlang(str, len);
    map(lang, str, len);

    if (put_string(str, len * sizeof(wchar_t) + 3) == -1)
        // Not sure when this would happen
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
