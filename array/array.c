#include "../includes/array.h"

static int g_array_find_position(g_array_t *a, va_list args) {
    int   x, pos, d;

    pos = 0;
    x = 0;
    for (d = 0; d <= a->d; d++) {
        x = va_arg(args, int);
        pos += x * (a->nelts/a->bounds[d]);
    }
    return pos-1;
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
}

void g_array_insert(g_array_t *a, void *elt, uint_t pos) {
    char  *temp;

    if (a->nelts == a->nalloc) {
        void  *new;

        new = g_realloc(a->elts, a->size*a->nalloc*2);
        if (new == NULL) {
            g_log_error("out of memory!");
            return;
        }
        a->elts = new;
        a->nalloc *= 2;
    }

    pos = pos > 0 ? (pos <= a->nelts ? pos : a->nelts) : 0;
    temp = a->elts + a->nelts*a->size;
    while(temp > (char *)a->elts+pos*a->size) {
        memcpy(temp+a->size, temp, a->size)
        temp -= a->size;
    }
    memcpy(temp, elt, a->size);
    a->nelts++;
}

void *g_array_delete(g_array_t *a, uint_t pos) {
    char  *temp;

    if (a->nelts == 0) {
        return NULL;
    }

    pos = pos > 0 ? (pos < a->nelts ? pos : a->nelts-1) : 0;
    temp = (char *)a->elts+pos*a->size
    memcpy(a->sentinel, temp, a->size);
    while(temp < (char *)a->elts+(a->nelts-1)*a->size) {
        memcpy(temp, temp+a->size, a->size);
        temp += a->size;
    }
    a->nelts--;

    return a->sentinel;
}

void g_array_push(g_array_t *a, void *elt) {
    g_array_insert(a, elt, a->nelts);
}

void *g_array_pop(g_array_t *a) {
    return g_array_delete(a, a->nelt-1);
}

int g_array_compare(g_array_t *a, g_array_t *b) {
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

int g_array_count(g_array_t *a, g_array_t *sep) {
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

int g_array_index(g_array_t *a, g_array_t *sep) {
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
        return g_array_index_single(a, single);
    }

    i = 0;
    rel = -1;
    len = a->nelts;
    elts = a->elts;
    while(i < len-sep->nelts+1) {
        if (a->cmp((char *)a->elts+i*a->size, single) != 0) {
            off = g_array_index_single(a, single);
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

int g_array_index_single(g_array_t *a, void *elt) {
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

void g_array_reverse(g_array_t *a) {
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

void g_array_join(g_array_t *a, void *sep) {

}
