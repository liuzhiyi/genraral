#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#include "../includes/os.h"

typedef struct g_element_s {
    void          *data;
    uint_t         size;
    g_compare_pt   cmp;
} g_element_t;

#define    g_get_d(var, pt, type)                        if (pt = NULL) { \
                                                         }

#define    g_element_init_d(elt, data, size, cmp)        elt.data = data; \
                                                         elt.size = size; \
                                                         elt.cmp  = cmp

#endif
