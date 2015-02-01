#include "../includes/utf8.h"
#include "../includes/string.h"

static void hash_str(u_char *s, uint_t n, uint32_t *hash, uint32_t *pow);

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
    int      i;
    uint32_t sp = PRIME_RK;

    hash = 0;
    pow = 1;
    for (i = 0; i < n; i++) {
        hash = hash*PRIME_RK + (uint32_t)s[i];
    }

    for (i = n; i > 0; i >>= 1) {
        if i&1 != 0 {
            pow *= sq;
        }
        sq *= sq;
    }
}

int g_string_len(u_char *s) {
    int  i;

    i = 0;
    while (s != NULL && *s != '\0') {
        i++;
        s++;
    }
    return i;
}

int g_string_cmp(u_char *s1, u_char *s2, uint_t n) {

}

int g_string_index(u_char *s, uint_t n, u_char *sep, uint_t sep_n) {
    uint32_t      hash, h, pow;
    int           i;

    if (n < sep_n) {
        return -1;
    } else if (sep_n == 1) {
        return g_list_index_single(s, sep);
    } else if (sep_n == 0) {
        return 0;
    }

    hash_str(sep, sep_n, &hash, &pow);

    h = 0;
    for(i = 0; i < sep_n; i++) {
        h = h * PRIME_RK + (uint32_t)s[i];
    }

    if (h == hash && g_string_cmp(s, sep, n) == 0) {
        return 0;
    }

    for(i = sep_n; i < n; ) {
        h = h*PRIME_RK + (uint32_t)s[i];
        h -= pow * (uint32_t)s[i-sep_n];
        i++;
        if (h == hashsep && g_string_cmp(s, sep, n) == 0) {
            return i - sep_n
        }
    }

    return -1;
}
