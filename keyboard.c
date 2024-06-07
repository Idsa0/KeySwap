#include "keyboard.h"

#define MAPSIZE 34
mapping keymap[] = {{'a', 0x5E9}, {'b', 0x5E0}, {'c', 0x5D1}, {'d', 0x5D2}, {'e', 0x5E7}, {'f', 0x5DB}, {'g', 0x5E2}, {'h', 0x5D9}, {'i', 0x5DF}, {'j', 0x5D7}, {'k', 0x5DC}, {'l', 0x5DA}, {'m', 0x5E6}, {'n', 0x5DE}, {'o', 0x5DD}, {'p', 0x5E4}, {'q', 0x2F}, {'r', 0x5E8}, {'s', 0x5D3}, {'t', 0x5D0}, {'u', 0x5D5}, {'v', 0x5D4}, {'w', 0x27}, {'x', 0x5E1}, {'y', 0x5D8}, {'z', 0x5D6}, {'\'', 0x2C}, {',', 0x5EA}, {'.', 0x5E5}, {'/', 0x2E}, {';', 0x5E3}, {'[', 0x5D}, {']', 0x5B}, {'`', 0x3B}};

LANG gmlang(const wchar_t *str, size_t length)
{
    int eng = 0, heb = 0;
    for (int i = 0; i < length; ++i)
        eng(str[i]) ? ++eng : heb(str[i]) ? ++heb : 0;

    return eng > heb ? ENGLISH : HEBREW;
}

void map(LANG lang, wchar_t *str, size_t length)
{
    int i, j;
    if (lang == HEBREW)
    {
        // Hebrew to English
        // Since hebrew letters are not in a sequence, we need to iterate over the mapping to find the corresponding english letter
        for (i = 0; i < length; ++i)
        {
            for (j = 0; j < MAPSIZE; ++j)
            {
                if (str[i] == keymap[j].hebrew)
                {
                    str[i] = keymap[j].english;
                    break;
                }
            }
        }
    }
    else
    {
        // English to Hebrew
        // Since english letters are in a sequence, we can use the index of the letter in the alphabet to find the corresponding hebrew letter
        for (i = 0; i < length; ++i)
        {
            if (eng(str[i]))
                str[i] = keymap[lower(str[i]) - 'a'].hebrew;

            else
                for (j = 26; j < MAPSIZE; ++j)
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
