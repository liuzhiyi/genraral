#include <stdio.h>
#include "../includes/chain.h"

int main() {
    g_chain_head_t  *c;
    g_chain_t       *b;
    int              a = 6;

    c = malloc(sizeof(g_chain_head_t));
    //c->sentinel = malloc(sizeof(g_chain_t));
    c->sentinel.next   = NULL;
    c->sentinel.elt    = (void *)a;
    c->nelts            = 1;
    b                   = c;
    printf("%d vars %d", c, b->elt);
}
