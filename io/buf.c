#include "../includes/io.h"
#include "../inlcudes/array.h"

void g_reader_init(g_reader_t  *r, g_fd_pt fd) {
    r->fd = fd;
}

static void g_reader_fill(g_reader_t *r) {
    g_list_t    *l;

    a = r->buf;
    if (r->r > 0) {
        memcpy(a->elt.elts, a->elt.elts+r->r, r->w-r->r);
        r->w -= r->r;
        r->r = 0;
    }
}

g_array_t *g_reader_peek(g_reader_t *r, int n) {
    if (n < 0) {
        g_log_notice("bufio: reader returned negative count from Read");
        return NULL;
    }
}
