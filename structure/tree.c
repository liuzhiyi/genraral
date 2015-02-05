#include "../include/tree.h"

/**
*每次插入的节点为红色节点,分左右子树两种情况：
*1、待平衡节点的父节点为黑色，直接跳过。
*2、待平衡节点的父节点为红色，叔父节点为红色，将父节点和叔父节点置为黑色，祖父节点置为红色，
*   然后将祖父节点作为待平衡节递归平衡。
*3、叔父节点为空，即是叶节点，如果待平衡节点为右节点，父节点左旋；
*  父节点置为黑色，祖父节点置为红色，祖父节点右旋。
*右子树大同小异。
******/
void g_rbtree_insert(g_rbtree_t *tree, g_rbtree_node_t *node) {
    g_rbtree_node_t    *root, *temp, **P;

    root = &tree->root;
    //二叉树插入
    temp = *root;
    while(1) {
        p = node->key > temp->key ? &temp->right : &temp->left;
        if (*p == NULL) break;
        temp = *p;
    }
    *p = node;
    node->left = NULL;
    node->right = NULL;
    node->parent = temp;
    g_rbtree_red(node);

    //重新平衡红黑树
    while(node != root && g_rbtree_is_black(node->parent)) {
        if (node->parent == node->parent->parent->left) {
            temp = node->parent->parent->right;
            if (g_rbtree_is_red(temp)) {
                g_rbtree_black(node->parent);
                g_rbtree_black(temp);
                g_rbtree_red(node->parent->parent);
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    g_rbtree_t_left_rotate(*root, node);
                }
                g_rbtree_black(node->parent);
                g_rbtree_red(node->parent->parent);
                g_rbtree_right_rotate(*root, node->parent->parent);
            }
        } else {
            temp = node->parent->parent->left;
            if (g_rbtree_is_red(temp)) {
                g_rbtree_black(node->parent);
                g_rbtree_black(temp);
                g_rbtree_red(node->parent->parent);
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    g_rbtree_t_right_rotate(*root, node);
                }
                g_rbtree_black(node->parent);
                g_rbtree_red(node->parent->parent);
                g_rbtree_left_rotate(*root, node->parent->parent);
            }
        }
    }
    g_rbtree_black(*root);
}

/**
*左子树情况：
*1、替换节点为红色，置为删除节点的颜色直接跳过。以下都是替换节点为黑色的情况，子节点为待平衡节点
*2、待平衡节点的兄弟点为红色，将父节点置为红色，兄弟节点置为黑色，父节点左旋，（注意此时兄弟节点已经变了），
*   继续按下面的情况进行。
*3、待平衡节点的兄弟节点为黑色，兄弟节点的右子节点为红色，将兄弟节点置为父节点的颜色，父节点置为黑色，
*   兄弟节点的右节点置为黑色，父节点左旋，将根节点置为黑色（有可能在旋转过程中，根节点已经变了）。
*4、待平衡节点的兄弟点为黑色，兄弟节点的孩子节点都为黑色，将兄弟节点置为红色，平衡节点变为父节点，重新进入递归；
*5、兄弟节点的右子节点为黑色，左子节点为红色，将左子节点置为黑色，兄弟节点置为红色，兄弟节点右旋。然后按情况3处理。
*右子树大同小异。
******/
void g_rbtree_delete(g_rbtree_t *tree, g_rbtree_node_t *node) {
    g_rbtree_node_t **tree, *temp, *b, *parent, *subst;

    *root = tree->root;
    //二叉树删除
    if (node->left == NULL) {
        temp = node->right;
        subst = node;
    } else if (node->right == NULL) {
        temp = node->left;
        subst = node;
    } else {
        subst = g_rbtree_min(node->right);
        temp = subst->right;
    }

    if (subst == *root) {
        *root = temp;
        g_rbtree_black(temp);

        node->left = NULL;
        node->right = NULL;
        node->parent = NULL;
        node->key = 0;
        return;
    }

    parent = subst->parent;
    if (subst == parent->left) {
        parent->left = temp;
    } else {
        parent->right = temp;
    }
    if (node == subst) {
        temp != NULL && temp->parent = parent;
    } else {
        if (subst->parent == node) {
            parent = subst;
            temp != NULL && temp->parent = parent;
        } else {
            temp != NULL && temp->parent = parent;
        }
        subst->left = node->left;
        subst->right = node->right;
        subst->parent = node->parent;
        subst->color = node->color;

        if (node == *root) {
            *root = subst;
        } else {
            if (node == node->parent->left) {
                node->parent->left = subst;
            } else {
                node->parent->right = subst;
            }
        }

        if (subst->left != NULL) {
            subst->left->parent = subst;
        }

        if (subst->right != NULL) {
            subst->right->parent = subst;
        }
    }
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->key = 0;
    if (g_rbtree_is_red(subst)) {
        return;
    }

    //重新平衡
    while(temp != root && g_rbtree_is_black(temp)) {
        if (temp == parent->left) {
            b = parent->right;
            if (g_rbtree_is_red(b)) {
                g_rbtree_black(b);
                g_rbtree_red(parent);
                g_rbtree_left_rotate(*root, parent);
                b = parent->right;
            }

            if (g_rbtree_is_black(b->left) && g_rbtree_is_black(b->right)) {
                g_rbtree_red(b);
                temp = parent;
                parent = parent->parent;
            } else {
                if (g_rbtree_is_black(b->right)) {
                    g_rbtree_black(b->left);
                    g_rbtree_red(b);
                    g_rbtree_right_rotate(*root, b);
                    b = parent->right;
                }
                b->color = parent->color;
                g_rbtree_black(parent);
                g_rbtree_black(b->right);
                g_rbtree_left_rotate(*root, parent);
                temp = root;
                parent = NULL;
            }
        } else {
            b = temp->parent->left;
            if (g_rbtree_is_red(b)) {
                g_rbtree_black(b);
                g_rbtree_red(temp->parent);
                g_rbtree_left_rotate(*root, temp->parent);
                b = temp->parent->right;
            }

            if (g_rbtree_is_black(b->left) && g_rbtree_is_black(b->right)) {
                g_rbtree_red(b);
                temp = temp->parent;
            } else {
                if (g_rbtree_is_black(b->right)) {
                    g_rbtree_black(b->left);
                    g_rbtree_red(b);
                    g_rbtree_right_rotate(*root, b);
                    b = temp->parent->right;
                }
                b->color = temp->parent->color;
                g_rbtree_black(temp->parent);
                g_rbtree_black(b->right);
                g_rbtree_left_rotate(*root, temp->parent);
                temp = root;
            }
        }
    }
    g_rbtree_black(temp);
}

void g_rbtree_left_rotate(g_rbtree_node_t **root, g_rbtree_node_t *node) {
    g_rbtree_node_t    *temp;

    temp = node->right;
    if (temp->left == NULL) {
        temp->left->parent = node;
    }
    temp->parent = node->parent;
    if (node == *root) {
        *root = temp;
    } else if (node == node->parent->left){
        node->parent->left = temp;
    } else {
        node->parent->right = temp;
    }
    node->right = temp->left;
    temp->left = node;
    node->parent = temp;
}

void g_rbtree_right_rotate(g_rbtree_node_t **root, g_rbtree_node_t *node) {
    g_rbtree_node_t      *temp;

    temp = node->left;
    if (temp->right == NULL) {
        temp->right->parent = node;
    }
    temp->parent = node->parent;
    if (node == *root) {
        *root = temp;
    } else if (node == node->parent->left) {
        node->parent->left = temp;
    } else {
        node->parent->right = temp;
    }
    node->left = temp->right;
    temp->right = node;
    node->parent = temp;
}

/*
*第一层mask：1000 0000 0000 0000 0000 0000 0000 0000;
*第二层为：  1100 0000 0000 0000 0000 0000 0000 0000;
*第三层为：  1110 0000 0000 0000 0000 0000 0000 0000;
*/
void g_radix32_insert_node(g_radix_t *root, g_radix_node_t *node) {

}
