#include "../includes/matrix.h"

static int g_matrix_compare_inside(float a, float b);

g_matrix_t *g_matrix_create(uint_t r, uint_t c, uint_t size, g_compare_pt cmp) {
    g_matrix_t     *m;
    uint_t           n;

    n = r * c;
    m = g_mcalloc(size * n);
    m->d = r;
    m->nalloc = n;
    m->nelts = n;
    m->size = size;
    m->cmp = cmp;
}

g_matrix_t *g_matrix_create_default(uint_t r, uint_t c) {
    return g_matrix_create(r, c, sizeof("float"), g_matrix_compare_inside);
}

uint_t g_matrix_find_position(uint_t r, uint_t c) {
    return (r-1) * (a->nelts/a->d) + c -1;
}
