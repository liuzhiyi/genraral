#ifndef _ARRAY_H_
#define _ARRAY_H_
#include "../includes/array.h"

typedef int (*g_compare_pt)(void *, void *);

typedef struct g_array_s {
    void          *elts;
    void          *sentinel;
    unsigned int   d;
    unsigned int  *bounds;
    unsigned int   size;
    unsigned int   nelts;
    unsigned int   nalloc;
    g_compare_pt   cmp;
} g_array_t;


g_array_t *g_array_create(size_t size, compare_t cmp);
int g_compare(void *a, void *b);
int g_index(void *src, void *sep);

#endif
