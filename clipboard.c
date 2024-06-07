#include "clipboard.h"

int put_string(const wchar_t *str)
{
    if (!OpenClipboard(NULL))
        return -1;

    EmptyClipboard();
    HGLOBAL clip = GlobalAlloc(GMEM_MOVEABLE, wcslen(str) * sizeof(wchar_t) + 3);
    if (!clip)
    {
        CloseClipboard();
        return -1;
    }

    wcscpy((wchar_t *)GlobalLock(clip), str);
    GlobalUnlock(clip);
    SetClipboardData(CF_UNICODETEXT, clip);

    CloseClipboard();

    return 0;
}

int get_string(wchar_t *str)
{
    if (!OpenClipboard(NULL))
        return -1;

    HANDLE clip = GetClipboardData(CF_UNICODETEXT);
    CloseClipboard();

    if (!clip)
        return -1;

    wcscpy(str, (wchar_t *)clip);
    return wcslen(str);
}
