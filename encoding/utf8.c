#include "../includes/utf8.h"

g_utf8_char_t g_utf8_decode_internal(char *s, uint_t n) {
    char *c, c0, c1, c2, c3;

    if (n < 1) {
        return g_utf8_char(UTF8_ERROR, 0);
    }

    c = s;
    c0 = *c++;

    // 1-byte, 7-bit sequence?
    if (c0 < UTF8_TX) {
        return g_utf8_char(c0, 1);
    }

    // unexpected continuation byte?
    if (c0 < UTF8_T2) {
        return g_utf8_char(UTF8_ERROR, 0);
    }

    // need first continuation byte
    if (n < 2) {
        return g_utf8_char(UTF8_ERROR, 0);
    }
    c1 = *c++;
    if (c1 < UTF8_TX || UTF8_T2 <= c1) {
        return g_utf8_char(UTF8_ERROR, 0);
    }

    // 2-byte, 11-bit sequence?
    if (c0 < UTF8_T3) {
        r = rune(c0&UTF8_MASK2)<<6 | rune(c1&UTF8_MASKX)
        if (r <= UTF8_W1Max) {
            return g_utf8_char(UTF8_ERROR, 0);
        }
        return g_utf8_char(r, 2);
    }

    // need second continuation byte
    if (n < 3) {
        return g_utf8_char(UTF8_ERROR, 0);
    }
    c2 = *c++;
    if (c2 < UTF8_TX || UTF8_T2 <= c2) {
        return g_utf8_char(UTF8_ERROR, 0);
    }

    // 3-byte, 16-bit sequence?
    if (c0 < UTF8_T4) {
        r = rune(c0&UTF8_MASK3)<<12 | rune(c1&UTF8_MASK3)<<6 | rune(c2&UTF8_MASK3)
        if (r <= UTF8_W2Max) {
            return g_utf8_char(UTF8_ERROR, 0);
        }
        if (SURROGATE_MIN <= r && r <= SURROGATE_MAX) {
            return g_utf8_char(UTF8_ERROR, 0);
        }
        return g_utf8_char(r, 3);
    }

    // need third continuation byte
    if (n < 4) {
        return g_utf8_char(UTF8_ERROR, 0);
    }
    c3 = *c++;
    if (c3 < UTF8_TX || UTF8_T2 <= c3) {
        return g_utf8_char(UTF8_ERROR, 0);
    }

    // 4-byte, 21-bit sequence?
    if (c0 < UTF8_T5) {
        r = rune(c0&mask4)<<18 | rune(c1&maskx)<<12 | rune(c2&maskx)<<6 | rune(c3&maskx)
        if (r <= UTF8_W3Max || MAX_UTF8 < r) {
            return g_utf8_char(UTF8_ERROR, 0);
        }
        return g_utf8_char(r, 4);
    }

    return g_utf8_char(UTF8_ERROR, 0);
}

int g_utf8_full_char(char *s) {
    g_utf8_char_t  c;
    c = g_utf8_decode_internal(s);
    return c.size > 0;
}
