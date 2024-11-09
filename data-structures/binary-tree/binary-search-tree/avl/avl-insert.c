#include<stddef.h>
#include "../../binary-tree.h"
#include "../bst.h"

extern int balance(TREE *tree, int root_index);

int bst_avl_insert_(TREE *tree, int root_index, int key_index) {
    if(root_index == -1) 
        return key_index;
    else if(tree->nodelist[root_index].data < tree->nodelist[key_index].data) {
        tree->nodelist[root_index].right = bst_avl_insert_(tree, tree->nodelist[root_index].right, key_index);
    } else if(tree->nodelist[root_index].data > tree->nodelist[key_index].data) {
        tree->nodelist[root_index].left = bst_avl_insert_(tree, tree->nodelist[root_index].left, key_index);
    }
    
    return balance(tree, root_index);
}

