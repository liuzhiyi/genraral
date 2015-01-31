#include "../includes/utf8.h"
#include "../includes/string.h"

//explode splits src into an array of UTF-8 sequences
u_char **g_string_explode(u_char *src, uint_t n) {
    int            count, i, j, size;
    u_char         **dst;
    g_utf8_char_t  ch;

    count = g_utf8_char_count(src, n);
    *dest = g_malloc(count * sizoef(u_char *));
    i = 0;
    j = 0;
    while (i < n) {
        ch = g_utf8_decode(src+i, n-i, *size);
        if (ch == UTF8_ERROR) {
            (*dst)[j] = g_malloc(2 * sizeof(u_char));
            (*dst)[j][0] = 0xff;
            (*dst)[j][0] = 0xfd;
        } else {
            (*dst)[j] = g_malloc(size * sizeof(u_char));
            memcpy((*dst)[j], src+i, size);
        }
        i += size;
        j++;
    }

    return dest;
}

static void hash_str(u_char *s, uint_t n, uint32_t *hash, uint32_t *pow) {
    int  i;
    const uint32_t primeRK = 16777619;
    uint32_t sp = 1;

    hash = 0;
    for (i = 0; i < n; i++) {
        hash = hash*primeRK + (uint32_t)s[i];
    }

    for (i = n; i > 0; i >>= 1) {
        if i&1 != 0 {
            pow *= sq;
        }
        sq *= sq;
    }
}
