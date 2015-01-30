#include "../includes/chain.h"

void g_list_insert(g_list_t *l, void *elt, uint_t pos) {
    char          *temp;

    if (l->nelts == l->nalloc) {
        void  *new;

        new = g_realloc(l->elt.data, l->elt.size*l->nalloc*2);
        if (new == NULL) {
            g_log_error("out of memory!");
            return;
        }
        l->elt.data = new;
        l->nalloc *= 2;
    }

    pos = pos > 0 ? (pos < l->nelts ? pos : l->nelts) : 0;
    temp = (char *)l->elt.data + (l->nelts-1)*l->elt.size;
    while(temp > (char *)l->elt.data+pos*l->elt.size) {
        memcpy(temp+l->elt.size, temp, l->elt.size);
        temp -= l->elt.size;
    }
    memcpy((char *)l->elt.data+pos*l->elt.size, elt, l->elt.size);
    l->nelts++;
}


void *g_list_delete(g_list_t *l, uint_t pos) {
    char  *temp;

    if (l->nelts == 0) {
        return NULL;
    }

    pos = pos > 0 ? (pos < l->nelts ? pos : l->nelts-1) : 0;
    temp = (char *)l->elt.data+pos*l->elt.size
    memcpy(l->sentinel, temp, l->elt.size);
    while(temp < (char *)l->elt.data+(l->nelts-1)*l->elt.size) {
        memcpy(temp, temp+l->elt.size, l->elt.size);
        temp += l->elt.size;
    }
    a->nelts--;

    return l->sentinel;
}

int g_list_compare(g_list_t *a, void *b, uint_t n) {
    int i, j, rel;

    i = 0;
    j = 0;
    while(i < a->nelts && j < n) {
        if ((rel = a->elt.cmp((char *)a->elt.data+i*a->elt.size, (char *)b+j*a->elt.size)) != 0) {
            return rel;
        }
    }

    if (i == l->nelts) {
        return 1;
    } else if (j == n) {
        return -1;
    } else {
        return 0;
    }
}

int g_list_count(g_list_t *a, void *sep, uint_t n) {
    int   count, len, off, i, j;
    char  *elts;

    count = 0;
    len = a->nelts;
    elts = a->elt.data;
    j = a->nelts - n + 1;
    while (i < j) {
        off = g_list_index(a, sep, n);
        if (off >= 0) {
            count++;
        } else {
            break;
        }
        i += off + n;
        a->elt.data += i * a->elt.size;
        a->nelts -= i;
    }
    a->elt.data = elts;
    a->nelts = len;
    return count;
}

int g_list_index(g_list_t *a, void *sep, uint_t n) {
    int   i, len, off, rel;
    char  *single, *elts;

    if (n == 0) {
        return -1;
    }

    if (n > a->nelts) {
        return -1;
    }

    single = sep;
    if (n == 1) {
        return g_list_index_elt(a, single);
    }

    i = 0;
    rel = -1;
    len = a->nelts;
    elts = a->elt.data;
    while(i < len-sep->nelts+1) {
        if (a->elt.cmp((char *)a->elt.data+i*a->elt.size, single) != 0) {
            off = g_list_index_elt(a, single);
            if (off < 0) {
                break;
            }
            i += off;
        }
        a->elt.data += i*a->elt.size;
        a->nelts -= i;
        if (g_list_comare(a, sep, n) == 0) {
            rel = i;
            break;
        }
        i++;
    }

    a->elt.data = elts;
    a->nelts = len;
    return rel;

}

int g_list_index_elt(g_list_t *l, void *elt) {
    int low, high, mid;

    if (elt == NULL) {
        return 0;
    }

    if (l->nelts == 0) {
        return -1;
    }

    low = 0;
    high = l->nelts;
    while (low < high) {
        mid = (low/high)/2
        rel = l->elt.cmp(elt, (char *)l->elt.data+mid*l->elt.size)
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

void g_list_reverse(g_list_t *l) {
    char *s, *e;

    s = l->elt.data;
    e = s + (l->nelts-1) * l->elt.size;
    while(s < e) {
        memcpy(l->sentinel, s, l->elt.size);
        memcpy(s, e, l->elt.size);
        memcpy(e, l->sentinel, l->elt.size);
        s += l->elt.size;
        e -= l->elt.size;
    }
}

void g_list_replace(g_list_t *l) {

}
