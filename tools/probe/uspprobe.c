/* Probe: Uniscribe's itemization under Wine, which a multiline EDIT uses to
 * draw a line item by item (each item opaque: its background box covers the
 * previous item's overhang; tools/probe/edititems.c).  For every printable
 * ASCII character c and a few contexts "XcX", prints where items start. */
#include <windows.h>
#include <usp10.h>
#include <stdio.h>

static void items(const char *s)
{
    WCHAR w[64];
    SCRIPT_ITEM it[64];
    int n, i, len = (int)strlen(s);
    for (i = 0; i < len; i++)
        w[i] = (unsigned char)s[i];
    if (ScriptItemize(w, len, 63, NULL, NULL, it, &n) != S_OK) {
        printf("[%s] fail\n", s);
        return;
    }
    printf("[%s]", s);
    for (i = 0; i < n; i++)
        printf(" %d", it[i].iCharPos);
    printf("\n");
}

int main(void)
{
    char s[64];
    int a, b, k, i;
    unsigned seed = 1;
    /* pairs: one line per first character, '1' where "ab" is two items */
    for (a = 0x21; a < 0x7f; a++) {
        printf("%c ", a);
        for (b = 0x21; b < 0x7f; b++) {
            WCHAR w[2] = {(WCHAR)a, (WCHAR)b};
            SCRIPT_ITEM it[4];
            int n;
            ScriptItemize(w, 2, 3, NULL, NULL, it, &n);
            putchar(n > 1 ? '1' : '0');
        }
        printf("\n");
    }
    /* bytes 0x80..0xff (code page 1252) against one of each class */
    for (a = 0x80; a < 0x100; a++) {
        static const char reps[] = "a.#1";
        char ab[2];
        printf("hi %02x ", a);
        for (b = 0; b < 4; b++) {
            WCHAR w[2];
            SCRIPT_ITEM it[4];
            int n;
            ab[0] = (char)a; ab[1] = reps[b];
            MultiByteToWideChar(1252, 0, ab, 2, w, 2);
            ScriptItemize(w, 2, 3, NULL, NULL, it, &n);
            putchar(n > 1 ? '1' : '0');
        }
        printf("\n");
    }
    /* random strings (an LCG tools can replay) */
    for (k = 0; k < 400; k++) {
        int len = 2 + (int)((seed = seed * 1103515245 + 12345) >> 16) % 12;
        for (i = 0; i < len; i++) {
            int r = (int)((seed = seed * 1103515245 + 12345) >> 16) % 100;
            s[i] = (char)(r < 25 ? ' ' : 0x21 + (r * 7 + i * 13) % 94);
        }
        s[len] = 0;
        items(s);
    }
    return 0;
}
