/**
 * @brief Functions to interact with the clipboard
 * 
 * @author Idan Saltzman
 * @date 2024-06-07
 * @version 1.0.1
 */

#pragma once
#include <windows.h>
#include <wchar.h>

/**
 * @brief Put a string into the clipboard
 *
 * The helper computes the number of bytes internally using (wcslen(str)+1)*sizeof(wchar_t).
 * On success returns 0, on failure returns -1.
 */
int put_string(const wchar_t *str);

/**
 * @brief Get a string from the clipboard
 *
 * Copies at most max_chars characters (including the terminating NUL) into buf.
 * Returns the number of characters (not bytes) read, or -1 on failure.
 */
int get_string(wchar_t *buf, size_t max_chars);
