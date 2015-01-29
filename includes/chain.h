#ifndef _CHAIN_H_
#define _CHAIN_H_
#include "../includes/os.h"

typedef struct g_chain_s {
    g_element_t           elt;
    struct g_chain_s     *next;
} g_chain_t;

typedef struct g_chain_head_s {
    g_chain_t         sentinel;
    uint_t            nelts;
} g_chain_head_t;

typdef struct g_list_s {
    g_element_t     elt;
    void           *sentinel;
    uint_t          nelts;
    uint_t          nalloc;
} g_list_t;

#endif
