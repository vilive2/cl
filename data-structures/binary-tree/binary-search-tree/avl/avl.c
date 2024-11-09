#include<stddef.h>
#include "../../binary-tree.h"
#include "../bst.h"

extern int bst_avl_insert_(TREE *tree, int root_index, int key_index);
extern int bst_avl_delete_(TREE *tree, int root_index, int key, int *key_index);

void bst_insert_(TREE *tree, int key_index) {
    tree->nodelist[key_index].height = 0;
    tree->root = bst_avl_insert_(tree, tree->root, key_index); 
}


int bst_delete_(TREE *tree, DATA key) {
    int key_index;

    tree->root = bst_avl_delete_(tree, tree->root, key, &key_index);

    return key_index;
}