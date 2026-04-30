#include "clipboard.h"
#include <string.h>

#define CLIP_RETRY_COUNT 3
#define CLIP_RETRY_DELAY_MS 10

static BOOL open_clipboard_retry(HWND hwnd)
{
    if (OpenClipboard(hwnd))
        return TRUE;

    for (int i = 0; i < CLIP_RETRY_COUNT; ++i)
    {
        Sleep(CLIP_RETRY_DELAY_MS);
        if (OpenClipboard(hwnd))
            return TRUE;
    }
    return FALSE;
}

int put_string(const wchar_t *str)
{
    if (!open_clipboard_retry(NULL))
        return -1;

    size_t bytes = (wcslen(str) + 1) * sizeof(wchar_t);

    EmptyClipboard();
    HGLOBAL clip = GlobalAlloc(GMEM_MOVEABLE, bytes);
    if (!clip)
    {
        CloseClipboard();
        return -1;
    }

    void *ptr = GlobalLock(clip);
    if (!ptr)
    {
        GlobalFree(clip);
        CloseClipboard();
        return -1;
    }

    memcpy(ptr, str, bytes);
    GlobalUnlock(clip);

    if (!SetClipboardData(CF_UNICODETEXT, clip))
    {
        GlobalFree(clip); // ownership not transferred
        CloseClipboard();
        return -1;
    }

    CloseClipboard();
    return 0;
}

int get_string(wchar_t *buf, size_t max_chars)
{
    if (!open_clipboard_retry(NULL))
        return -1;

    HANDLE h = GetClipboardData(CF_UNICODETEXT);
    if (!h)
    {
        CloseClipboard();
        return -1;
    }

    void *ptr = GlobalLock(h);
    if (!ptr)
    {
        CloseClipboard();
        return -1;
    }

    const wchar_t *w = (const wchar_t *)ptr;
    size_t len = wcslen(w);
    if (len >= max_chars)
    {
        GlobalUnlock(h);
        CloseClipboard();
        return -1; // buffer too small
    }

    memcpy(buf, w, (len + 1) * sizeof(wchar_t));

    GlobalUnlock(h);
    CloseClipboard();
    return (int)len;
}
