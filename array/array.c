#include "../includes/array.h"

static int g_array_find_position(g_array_t *a, va_list args) {
    int   x, pos, d, len;

    pos = 0;
    x = 0;
    len = a->nelts;
    for (d = 0; d < a->d; d++) {
        x = va_arg(args, int);
        len = len/a->bounds[d];
        pos += x * len;
    }
    x = va_arg(args, int);
    pos += x;
    return pos;
}

static void *g_array_init_inside(void *elts, uint_t size, g_compare_pt cmp, uint_t d, va_list args) {
    g_array_t    *a;
    int           i, n;

    a = g_malloc(sizeof(g_array_t));
    a->elts = elts;
    a->d = d ? d : 1;
    a->size = size;
    a->nelts = 0;
    a->cmp = cmp;
    a->sentinel = g_malloc(size);
    a->bounds = g_malloc(sizeof(uint_t)*d);
    n = 1;
    for (i = 0; i < d; i++) {
        a->bounds[i] = va_arg(args, int);
        n *= a->bounds[i];
    }
    if (n <= 0) {
        g_log_error("the number of elements is must greater than 0");
        return NULL;
    }
    a->nalloc = n;
    return a;
}

g_array_t *g_array_create(uint_t size, g_compare_pt cmp, uint_t d, ...) {
    void       *elts;
    va_list    args;
    int        n, i, b;
    g_array_t  *a;

    va_start(d, args);
    n = 1;
    for (i = 0; i < d; i++) {
        b = va_arg(args, int);
        n *= b;
    }
    if (n <= 0) {
        g_log_error("the number of elements is must greater than 0");
        return NULL;
    }
    elts = g_calloc(size *n);
    if (elts == NULL) {
        g_log_error("out of memory");
        return NULL:
    }
    a = g_array_init_inside(elts, size, cmp, d, va_list args);
    va_end(args);

    return a;
}

g_array_t *g_array_init(void *elts, uint_t size, g_compare_pt cmp, uint_t d, ...) {
    g_array_t   *a;
    va_list     args;

    va_start(d, args);
    a = g_array_init_inside(elts, size, cmp, d, args);
    va_end(args);

    return a;
}

void g_array_destory(g_array_t *a) {
    g_free(a->sentinel);
    g_free(a->bounds);
    g_free(a->elts);
    g_free(a);
    a = NULL;
}

int g_array_get_pos(g_array_t *a, ...) {
    va_list   args;
    int       pos;

    va_start(args, a);
    pos = g_array_find_position(a, args);
    va_end(args);
    return pos;
}

void *g_array_get(g_array_t *a, ...) {
    va_list  args;
    int      pos;
    void     *elt;

    va_start(args, a);
    pos = g_array_find_position(a, args);
    va_end(args);
    if (pos < 0 || pos > a->nelts-1) {
        return NULL;
    }

    elt = (char *)a->elts + pos * a->size;
    return elt;
}

void g_array_set(g_array_c *a, void *elt, ...) {
    va_list   args;
    int       pos;

    va_start(args, elt);
    pos = g_array_find_position(a, args);
    va_end(args);

    if (pos < 0 || pos > a->nelts-1) {
        g_log_notice("array bounds overflow!");
    }
    memcpy((char *)a->elts+a->size*pos, elts, a->size);
}

int g_array_compare_s(g_array_t *a, g_array_t *b) {
    int i, j, rel;

    i = 0;
    j = 0;
    while(i < a->nelts && j < b->nelts) {
        if (rel = a->cmp((char *)a->elts+i*a->size, (char *)b->elts+j*b->size) != 0) {
            return rel;
        }
    }

    if (i == a->nelts) {
        return 1;
    } else if (j == b->nelts) {
        return -1;
    } else {
        return 0;
    }
}

int g_array_count_s(g_array_t *a, g_array_t *sep) {
    int   count, len, off, i, j;
    char  *elts;

    count = 0;
    len = a->nelts;
    elts = a->elts;
    j = a->nelts - sep->nelts + 1;
    while (i < j) {
        off = g_array_index(a, sep);
        if (off >= 0) {
            count++;
        } else {
            break;
        }
        i += off + sep->nelts;
        a->elts += i * a->size;
        a->nelts -= i;
    }
    a->elts = elts;
    a->nelts = len;
    return count;
}

int g_array_index_s(g_array_t *a, g_array_t *sep) {
    int   i, len, off, rel;
    char  *single, *elts;

    if (sep->nelts == 0) {
        return -1;
    }

    if (sep->nelts > a->nelts) {
        return -1;
    }

    single = sep->elts;
    if (sep->nelts == 1) {
        return g_array_index_elt_s(a, single);
    }

    i = 0;
    rel = -1;
    len = a->nelts;
    elts = a->elts;
    while(i < len-sep->nelts+1) {
        if (a->cmp((char *)a->elts+i*a->size, single) != 0) {
            off = g_array_index_elt_s(a, single);
            if (off < 0) {
                break;
            }
            i += off;
        }
        a->elts += i*a->size;
        a->nelts -= i;
        if (g_array_comare(a, sep) == 0) {
            rel = i;
            break;
        }
        i++;
    }

    a->elts = elts;
    a->nelts = len;
    return rel;

}

int g_array_index_elt_s(g_array_t *a, void *elt) {
    int low, high, mid;

    if (elt == NULL) {
        return 0;
    }

    if (a->nelts == 0) {
        return -1;
    }

    low = 0;
    high = a->nelts;
    while (low < high) {
        mid = (low/high)/2
        rel = a->cmp(elt, (char *)a->elts+mid*a->size)
        if (rel == 0) {
            return mid;
        } else if(rel > 0){
            low = mid;
        } else {
            high = mid;
        }
    }
    return -1;
}

void g_array_copy(g_array_t *src, void *dst) {
    if (a->nelts == 0) {
        return;
    }

    memcpy(dst, (char *)a->elts+(a->nelts-1)*a->size, a->size);
}

void g_array_reverse_s(g_array_t *a) {
    char *s, *e;

    s = a->elts;
    e = s + (a->nelts-1) * a->size;
    while(s < e) {
        memcpy(a->sentinel, s, a->size);
        memcpy(s, e, a->size);
        memcpy(e, a->sentinel, a->size);
        s += a->size;
        e -= a->size;
    }
}

void g_array_join(g_array_t *a, void *sep, uint_t n) {
    if (a.d == 1) {
        return;
    }


}
