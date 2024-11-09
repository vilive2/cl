#include<stddef.h>
#include "../binary-tree.h"

void bst_insert_(TREE *tree, int key_index) {
    if(tree->root == -1) {
        tree->root = key_index;
        tree->nodelist[key_index].parent = -1;
        return;
    }

    int par = tree->root;
    TNODE *node = &(tree->nodelist[key_index]);
    int key = node->data;
    TNODE *cur = &(tree->nodelist[par]);
    
    while(1) {
        if(cur->data < key) {
            if(cur->right != -1) 
                par = cur->right;
            else 
                break;
        } else {
            if(cur->left != -1)
                par = cur->left;
            else
                break;
        }

        cur = &(tree->nodelist[par]);
    }

    if(cur->data < key) {
        // INSERT RIGHT
        cur->right = key_index;
    } else {
        // INSERT LEFT
        cur->left = key_index;
    }
    node->parent = par;
}