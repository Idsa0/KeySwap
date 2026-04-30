#include "keyboard.h"

mapping keymap[] = {
    {'a', 0x5E9},
    {'b', 0x5E0},
    {'c', 0x5D1},
    {'d', 0x5D2},
    {'e', 0x5E7},
    {'f', 0x5DB},
    {'g', 0x5E2},
    {'h', 0x5D9},
    {'i', 0x5DF},
    {'j', 0x5D7},
    {'k', 0x5DC},
    {'l', 0x5DA},
    {'m', 0x5E6},
    {'n', 0x5DE},
    {'o', 0x5DD},
    {'p', 0x5E4},
    {'q', 0x2F},
    {'r', 0x5E8},
    {'s', 0x5D3},
    {'t', 0x5D0},
    {'u', 0x5D5},
    {'v', 0x5D4},
    {'w', 0x27},
    {'x', 0x5E1},
    {'y', 0x5D8},
    {'z', 0x5D6},
    {'\'', 0x2C},
    {',', 0x5EA},
    {'.', 0x5E5},
    {'/', 0x2E},
    {';', 0x5E3},
    {'[', 0x5D},
    {']', 0x5B},
    {'`', 0x3B}};
mapping hebmap[] = {
    {'w', 0x0027},
    {'\'', 0x002C},
    {'/', 0x002E},
    {'q', 0x002F},
    {'`', 0x003B},
    {']', 0x005B},
    {'[', 0x005D},
    {'t', 0x05D0},
    {'c', 0x05D1},
    {'d', 0x05D2},
    {'s', 0x05D3},
    {'v', 0x05D4},
    {'u', 0x05D5},
    {'z', 0x05D6},
    {'j', 0x05D7},
    {'y', 0x05D8},
    {'h', 0x05D9},
    {'l', 0x05DA},
    {'f', 0x05DB},
    {'k', 0x05DC},
    {'o', 0x05DD},
    {'n', 0x05DE},
    {'i', 0x05DF},
    {'b', 0x05E0},
    {'x', 0x05E1},
    {'g', 0x05E2},
    {';', 0x05E3},
    {'p', 0x05E4},
    {'.', 0x05E5},
    {'m', 0x05E6},
    {'e', 0x05E7},
    {'r', 0x05E8},
    {'a', 0x05E9},
    {',', 0x05EA}};

#define MAPSIZE (sizeof(keymap) / sizeof(mapping))

_Static_assert((sizeof(keymap) / sizeof(mapping)) == (sizeof(hebmap) / sizeof(mapping)), "keymap/hebmap size mismatch");

/**
 * Binary search helper over hebmap (sorted by hebrew).
 * Returns the english char for a hebrew key or the key unchanged.
 */
wchar_t heb_to_english_char(wchar_t key)
{
    size_t low = 0, high = MAPSIZE; /* high is exclusive */
    while (low < high)
    {
        size_t mid = low + (high - low) / 2;
        if (hebmap[mid].hebrew == key)
            return hebmap[mid].english;
        else if (hebmap[mid].hebrew < key)
            low = mid + 1;
        else
            high = mid;
    }
    return key;
}

LANG gmlang(const wchar_t *str, size_t length)
{
    int eng_count = 0, heb_count = 0;
    for (size_t i = 0; i < length; ++i)
        is_eng(str[i]) ? ++eng_count : is_heb(str[i]) ? ++heb_count : 0;

    return eng_count > heb_count ? ENGLISH : HEBREW;
}

void map(LANG lang, wchar_t *str, size_t length)
{
    if (lang == HEBREW)
    {
        /* Hebrew to English: binary search per character */
        for (size_t i = 0; i < length; ++i)
            str[i] = heb_to_english_char(str[i]);
    }
    else
    {
        /* English to Hebrew: a-z mapped by position; punctuation handled by tail of keymap */
        for (size_t i = 0; i < length; ++i)
        {
            if (is_eng(str[i]))
                str[i] = keymap[to_lower_w(str[i]) - L'a'].hebrew;
            else
            {
                for (size_t j = 26; j < MAPSIZE; ++j)
                {
                    if (str[i] == keymap[j].english)
                    {
                        str[i] = keymap[j].hebrew;
                        break;
                    }
                }
            }
        }
    }
}
