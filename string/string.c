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

int g_string_cmp(u_char *s1, uint_t s1_n, u_char *s2, uint_t s2_n) {
    int    i;

    for (i = 0; i < s1_n && i < s2_n; i++) {
        if (s1[i] > s2[i]) {
            return 1;
        } else if (s1[i] < s2[i]) {
            return -1;
        }
    }

    if (i < s1_n) {
        return 1;
    } else if (i < s2_n) {
        return -1;
    } else {
        return 0;
    }
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

    if (h == hash && g_string_cmp(s, sep_n, sep, sep_n) == 0) {
        return 0;
    }

    for(i = sep_n; i < n; ) {
        h = h*PRIME_RK + (uint32_t)s[i];
        h -= pow * (uint32_t)s[i-sep_n];
        i++;
        if (h == hashsep && g_string_cmp(s, sep_n, sep, sep_n) == 0) {
            return i - sep_n
        }
    }

    return -1;
}

int g_string_has_prefix(u_char *s, uint_t n, u_char *prefix, uint_t prefix_n) {
    return n >= prefix_n && g_string_cmp(s, prefix_n, prefix, prefix_n) == 0;
}

int g_string_has_suffix(u_char *s, uint_t n, u_char *suffix, uint_t suffix_n) {
    return n >= suffix_n && g_string_cmp(s+n-suffix_n, suffix_n, suffix, suffix_n);
}

void g_string_split(u_char *src, uint_t n, u_char *sep, uint_t sep_n, u_char **dst) {
    int       start, i, na;

    for (i = 0; i+sep_n <= n; i++) {
        if (c = s[i] && (sep_n == 1 || g_string_cmp(s+i, sep_n, sep, sep_n))) {
            memcpy((*a)[na], s+start, i-start);
            i += sep_n - 1;
            na++;
            start += i + sep_n;
        }
    }
    memcpy((*a)[na], s+start, n);
    return a;
}

void g_string_join(u_char **src, u_char *dst, u_char *sep) {
    int  i;

    memcpy(dst, (*src)[i], g_string_len((*src)[i]));
    for (i = 1; i < n; i++) {
        memcpy(dst, sep, sep_n);
        memcpy(dst, (*src)[i], g_string_len((*src)[i]));
    }
}

void g_string_tolower(u_char *src, u_char *dst, uint_t n) {
    while(n) {
        *dst = g_char_tolower(*src);
        dst++;
        src++;
        n--;
    }
}

void g_string_toupper(u_char *src, u_char *dst, uint_t n) {
    while(n) {
        *dst = g_char_toupper(*src);
        dst++;
        src++;
        n--;
    }
}

void g_string_trim() {

}

void g_string_replace() {

}

void g_string_repeate() {

}
