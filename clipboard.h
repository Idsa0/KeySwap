/**
 * @brief Functions to interact with the clipboard
 * 
 * @author Idan Saltzman
 * @date 2024-06-07
 * @version 1.0.1
 */

#pragma once
#include <windows.h>

/**
 * @brief Put a string into the clipboard
 *
 * @param str The string to put into the clipboard
 * @return 0 if the string was successfully put into the clipboard, -1 if the clipboard could not be opened
 */
int put_string(const wchar_t *str, size_t len);

/**
 * @brief Get a string from the clipboard
 *
 * @param str The buffer to put the string into
 * @return The number of characters read from the clipboard or -1 if the clipboard could not be opened
 */
int get_string(wchar_t *str);
