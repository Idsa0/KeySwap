#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include "../keyboard.h"
#include "../clipboard.h"

static int failures = 0;

static void fail(const char *msg)
{
    fprintf(stderr, "FAIL: %s\n", msg);
    ++failures;
}

static void ok(const char *msg)
{
    printf("OK: %s\n", msg);
}

static void test_gmlang()
{
    /* Pure English */
    const wchar_t *eng = L"hello world";
    if (gmlang(eng, wcslen(eng)) != ENGLISH)
        fail("gmlang: pure English should be ENGLISH");
    else
        ok("gmlang: pure English");

    /* Pure Hebrew - construct a small Hebrew string using mapped output */
    wchar_t heb[64];
    wcscpy(heb, L"xccv");
    map(ENGLISH, heb, wcslen(heb));
    if (gmlang(heb, wcslen(heb)) != HEBREW)
        fail("gmlang: pure Hebrew should be HEBREW");
    else
        ok("gmlang: pure Hebrew");

    /* Mixed: English with a single Hebrew letter; English should win */
    const wchar_t *mixed = L"hello \u05D0"; /* hello + hebrew alef (U+05D0) */
    if (gmlang(mixed, wcslen(mixed)) != ENGLISH)
        fail("gmlang: mixed English+Hebrew should be ENGLISH (english majority)");
    else
        ok("gmlang: mixed English+Hebrew");

    /* Symbols only - expect tie -> HEBREW per implementation (eng>heb ? ENGLISH : HEBREW) */
    const wchar_t *sym = L"1234 !@#$";
    if (gmlang(sym, wcslen(sym)) != HEBREW)
        fail("gmlang: symbols-only should resolve to HEBREW by tie rule");
    else
        ok("gmlang: symbols-only");
}

static void test_map_roundtrip()
{
    /* Roundtrip letters a..z */
    wchar_t src[64];
    wcscpy(src, L"abcdefghijklmnopqrstuvwxyz");
    size_t len = wcslen(src);
    wchar_t tmp[64];
    wcscpy(tmp, src);
    map(ENGLISH, tmp, len); /* english -> hebrew */
    map(HEBREW, tmp, len);  /* hebrew -> english */
    if (wcscmp(src, tmp) != 0)
        fail("map: roundtrip for a-z did not return original");
    else
        ok("map: roundtrip for a-z");
}

static void test_clipboard_put_get()
{
    wchar_t buf[1024];
    wcscpy(buf, L"Test clipboard string 123 \u05D0\u05D1");

    if (put_string(buf) == -1)
    {
        fail("put_string failed (clipboard may be unavailable)");
        return;
    }

    wchar_t got[1024];
    int r = get_string(got, 1024);
    if (r == -1)
    {
        fail("get_string failed after put_string");
        return;
    }

    if (wcscmp(buf, got) != 0)
        fail("clipboard: put/get returned different strings");
    else
        ok("clipboard: put/get roundtrip");
}

int main(void)
{
    setlocale(LC_ALL, "");
    printf("Running tests...\n");

    test_gmlang();
    test_map_roundtrip();
    test_clipboard_put_get();

    if (failures > 0)
    {
        fprintf(stderr, "%d tests failed\n", failures);
        return 1;
    }

    printf("All tests passed\n");
    return 0;
}
