#include<stddef.h>
#include<assert.h>
#include "../../binary-tree.h"
#include "../bst.h"

extern int balance(TREE *tree, int root_index);
extern int bst_successor(TREE *tree, int root_index);

int bst_avl_delete_(TREE *tree, int root_index, int key, int *key_index) {
    if(root_index == -1) {
        *key_index = -1;
        return -1;
    }

    if( key < tree->nodelist[root_index].data ) {
        tree->nodelist[root_index].left = bst_avl_delete_(tree, tree->nodelist[root_index].left, key, key_index);
    } else if(key > tree->nodelist[root_index].data) {
        tree->nodelist[root_index].right = bst_avl_delete_(tree, tree->nodelist[root_index].right, key, key_index);
    } else {
        *key_index = root_index;
        if(tree->nodelist[root_index].left != -1 &&
            tree->nodelist[root_index].right != -1) {

            int succ_index = bst_successor(tree, root_index);
            assert(succ_index != -1);
            tree->nodelist[root_index].right = bst_avl_delete_(tree, tree->nodelist[root_index].right, 
                                                    tree->nodelist[succ_index].data, &succ_index);
            
            tree->nodelist[succ_index].left = tree->nodelist[root_index].left;
            tree->nodelist[succ_index].right = tree->nodelist[root_index].right;
            root_index = succ_index;
        } else if(tree->nodelist[root_index].left != -1) {
            root_index = tree->nodelist[root_index].left;
        } else {
            root_index = tree->nodelist[root_index].right;
        }
    }

    return balance(tree, root_index);
}