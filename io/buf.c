#include "../includes/io.h"
#include "../inlcudes/chain.h"

void g_reader_init(g_reader_t  *r, g_fd_pt fd) {
    r->fd = fd;
}

static void g_reader_fill(g_reader_t *r) {
    g_list_t    *l;
    int          i, n;

    l = r->buf;
    if (r->r > 0) {
        memcpy(l->elt.elts, l->elt.elts+r->r, r->w-r->r);
        r->w -= r->r;
        r->r = 0;
    }

    if (r->w >= l->nelts) {
        g_log_notice("bufio: tried to fill full buffer");
        return;
    }

    for (i = 0; i < maxConsecutiveEmptyReads; i++) {
        n = r->read(r->fd, l);
        if (n < 0) {
            g_log_notice("buffio: negative count");
            return;
        }
        r->w += n;
        if (n > 0) {
            return
        }
    }
}

void *g_reader_peek(g_reader_t *r, int n) {
    int       m;

    if (n < 0) {
        g_log_notice("bufio: reader returned negative count from Read");
        return NULL;
    }

    if (n > r->buf.nalloc) {
        g_log_notice("bufio: out of buffer");
        return NULL;
    }

    while(r->w-r->r < n) {
        g_reader_fill(r);
    }
    m = r->w - r->r;
    if m > n {
        m = n;
    }
    return r->buf.elts + r->r * r-buf.size;
}

int g_reader_read(g_reader_t *r, g_list_t *l) {
    int       n;

    n = l->nalloc;
    if (n == 0) {
        return 0;
    }
}
