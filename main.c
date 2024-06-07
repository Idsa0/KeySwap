/**
 * @brief This program reads a string from the clipboard, determines the language of the string, maps the string to the other language, and writes the mapped string back to the clipboard.
 * 
 * @author Idan Saltzman
 * @date 2024-06-07
 * @version 1.0.0
 */

#include "clipboard.h"
#include "keyboard.h"

#define MAX 0x80000 // 512KB

int main()
{
    wchar_t str[MAX];
    if (get_string(str) == -1)
        // This happens when the clipboard is empty or contains data that is not a string
        return EXIT_FAILURE;

    int lang = gmlang(str, wcslen(str));
    map(lang, str, wcslen(str));

    if (put_string(str) == -1)
        // Not sure when this would happen
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
