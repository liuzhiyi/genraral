#ifndef _ARRAY_H_
#define _ARRAY_H_
#include "../includes/array.h"

typedef int (*g_compare_t)(void *, void *);

typedef struct g_array_s {
    void           *elts;
    void           *sentinel;
    unsigned int   d;
    unsigned int   *bounds;
    unsigned int   size;
    unsigned int   nelts;
    unsigned int   nalloc;
    compare_t      cmp;
} g_array_t;


g_array_t *g_array_create(size_t size, compare_t cmp);
void g_array_push(g_array_t *a, void *elt);
void *g_array_pop(g_array_t);
int g_compare(void *a, void *b);
int g_index(void *src, void *sep);

#endif
