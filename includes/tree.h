#ifndef _TREE_H_
#define _TREE_H_
#include "../includes/os.h"
#include "../includes/global.h"

typedef struct g_btree_node_s {
    g_element_t             elt;
    struct g_btree_node_s   *left;
    struct g_btree_node_s   *right;
} g_btree_node_t;

typedef struct g_btree_s {
    g_btree_node_t       *root;
    g_btree_node_t       *sentinel;
} g_btree_t;

// 性质1. 节点是红色或黑色。
// 性质2. 根是黑色。
// 性质3. 所有叶子都是黑色（叶子是NIL节点）。
// 性质4. 每个红色节点必须有两个黑色的子节点。(从每个叶子到根的所有路径上不能有两个连续的红色节点。)
// 性质5. 从任一节点到其每个叶子的所有简单路径都包含相同数目的黑色节点。
typedef struct g_rbtree_node_s {
    g_element_t              elt;
    struct g_rbtree_node_s   *left;
    struct g_rbtree_node_s   *right;
    struct g_rbtree_node_s   *parent;
    uint_t                   key;
    u_char                   color;
} g_rbtree_node_t;

typedef struct g_rbtree_s {
    g_rbtree_node_t       *root;
    g_rbtree_node_t       *sentinel;
} g_rbtree_t;

//基数树
typedef struct g_radix_node_s {
    struct g_radix_node_s  *right;
    struct g_radix_node_s  *left;
    struct g_radix_node_s  *parent;
    void                   *value;
} g_radix_node_t;

typedef struct g_radix_s {
    g_radix_node_t    *root;
} g_radix_t;

#define g_rbtree_red(node)        ((node) != NULL && (node)->color = 1)
#define g_rbtree_black(node)      ((node) != NULL && (node)->color = 0)
#define g_rbtree_is_red(node)     ((node) != NULL && (node)->color)
#define g_rbtree_is_black(node)   (!(g_rbtree_is_red(node)))

#endif
