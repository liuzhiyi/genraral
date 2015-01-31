#include "../includes/utf8.h"

g_utf8_char_t g_utf8_decode(u_char *s, uint_t n, int *size) {
    u_char *c, c0, c1, c2, c3;
    g_utf8_char_t r;

    if (n < 1) {
        *size = 0;
        return r = UTF8_ERROR;
    }

    c = s;
    c0 = *c++;

    // 1-byte, 7-bit sequence?
    if (c0 < UTF8_TX) {
        *size = 1;
        return (g_utf8_char_t)c0;
    }

    // unexpected continuation byte?
    if (c0 < UTF8_T2) {
        *size = 0;
        return r = UTF8_ERROR;
    }

    // need first continuation byte
    if (n < 2) {
        *size = 0;
        return r = UTF8_ERROR;
    }
    c1 = *c++;
    if (c1 < UTF8_TX || UTF8_T2 <= c1) {
        *size = 0;
        return r = UTF8_ERROR;
    }

    // 2-byte, 11-bit sequence?
    if (c0 < UTF8_T3) {
        r = ((g_utf8_char_t)(c0&UTF8_MASK2))<<6 | (g_utf8_char_t)(c1&UTF8_MASKX);
        if (r <= UTF8_W1Max) {
            *size = 0;
            return r = UTF8_ERROR;
        }
        *size = 2;
        return r;
    }

    // need second continuation byte
    if (n < 3) {
        *size = 0;
        return r = UTF8_ERROR;
    }
    c2 = *c++;
    if (c2 < UTF8_TX || UTF8_T2 <= c2) {
        *size = 0;
        return r = UTF8_ERROR;
    }

    // 3-byte, 16-bit sequence?
    if (c0 < UTF8_T4) {
        r = ((g_utf8_char_t)(c0&UTF8_MASK3))<<12 | ((g_utf8_char_t)(c1&UTF8_MASKX))<<6 |
            (g_utf8_char_t)(c2&UTF8_MASKX);
        if (r <= UTF8_W2Max) {
            *size = 0;
            return r = UTF8_ERROR;
        }
        if (SURROGATE_MIN <= r && r <= SURROGATE_MAX) {
            *size = 0;
            return r = UTF8_ERROR;
        }
        *size = 3;
        return r;
    }

    // need third continuation byte
    if (n < 4) {
        *size = 0;
        return r = UTF8_ERROR;
    }
    c3 = *c++;
    if (c3 < UTF8_TX || UTF8_T2 <= c3) {
        *size = 0;
        return r = UTF8_ERROR;
    }

    // 4-byte, 21-bit sequence?
    if (c0 < UTF8_T5) {
        g_utf8_char_t  r;

        r = ((g_utf8_char_t)(c0&UTF8_MASK4))<<18 | ((g_utf8_char_t)(c1&UTF8_MASKX))<<12 |
            ((g_utf8_char_t)(c2&UTF8_MASKX))<<6 | ((g_utf8_char_t)(c3&UTF8_MASKX));
        if (r <= UTF8_W3Max || MAX_UTF8 < r) {
            *size = 0;
            return r = UTF8_ERROR;
        }
        *size = 4;
        return r;
    }
    *size = 0;
    return r = UTF8_ERROR;
}

int g_utf8_full_char(u_char *s, uint_t n) {
    g_utf8_char_t  c;
    int            size;

    c = g_utf8_decode(s, n, &size);
    return size > 0;
}

int g_utf8_char_len(g_utf8_char_t c) {
    if (c < 0) {
        return -1;
    } else if (c <= UTF8_W1Max) {
        return 1;
    } else if (c <= UTF8_W2Max) {
        return 2;
    } else if (c > MAX_UTF8 || (SURROGATE_MIN <= c && c <= SURROGATE_MAX)) {
        g_log_notice("utf8 valid char");
        return -1;
    } else if (c <= UTF8_W3Max) {
        return 3;
    } else {
        return 4;
    }
}

int g_utf8_encode(u_char *s, g_utf8_char_t c) {
    if (c <= UTF8_W1Max) {
        *s++ = (u_char)c;
        return 1;
    } else if (c <= UTF8_W2Max) {
        *s++ = UTF8_T2 | (u_char)(c >> 6);
        *s   = UTF8_TX | ((u_char)c)&UTF8_MASKX;
        return 2;
    } else if (c > MAX_UTF8 || (SURROGATE_MIN <= c && c <= SURROGATE_MAX)) {
        g_log_notice("utf8 valid char");
        c = UTF8_ERROR;
        return 0;
    } else if (c <= UTF8_W3Max) {
        *s++ = UTF8_T3 | (u_char)(c >> 12);
        *s++ = UTF8_TX | ((u_char)(c >> 6))&UTF8_MASKX;
        *s   = UTF8_TX | ((u_char)c)&UTF8_MASKX;
        return 3;
    } else {
        *s++ = UTF8_T4 | (u_char)(c >> 18);
        *s++ = UTF8_TX | ((u_char)(c >> 12))&UTF8_MASKX;
        *s++ = UTF8_TX | ((u_char)(c >> 6))&UTF8_MASKX;
        *s   = UTF8_TX | ((u_char)c)&UTF8_MASKX;
        return 4;
    }
}

int g_utf8_char_count(u_char *s, uint_t n) {
    int  i, count, size;

    for (i = 0, count = 0; i < n; count++) {
        if (s[i] < UTF8_SELF) {
            i++;
        } else {
            g_utf8_decode(s+i, n-i, &size);
            i += size;
        }
    }
    return count;
}
