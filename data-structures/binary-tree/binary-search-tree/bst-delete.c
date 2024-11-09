#include<stddef.h>
#include "../binary-tree.h"

extern int bst_search(TREE *tree, DATA key);
extern int bst_successor(TREE *tree, int root);

void delete_casea(TREE *tree, int key_index) {
    TNODE *par_node, *key_node, *child_node;
    key_node = &(tree->nodelist[key_index]);
    int par = key_node->parent, child = key_node->left;
    if(child == -1)
        child = key_node->right;
    if(par != -1)
        par_node = &(tree->nodelist[par]);
    if(child != -1)
        child_node = &(tree->nodelist[child]);

    key_node->left = -1;
    key_node->right = -1;
    key_node->parent = -1;

    if(par != -1) {
        if(key_index == par_node->left)
            par_node->left = child;
        else 
            par_node->right = child;
    } else 
        tree->root = child;

    if(child != -1) 
        child_node->parent = par;
}

void delete_caseb(TREE *tree, int key_index) {
    int par, succ_index = bst_successor(tree, key_index);
    delete_casea(tree, succ_index);
    
    TNODE *par_node, *key_node, *left_node, *right_node, *succ_node;
    key_node = &(tree->nodelist[key_index]);
    par = key_node->parent;
    if(par != -1) 
        par_node = &(tree->nodelist[par]);

    left_node = &(tree->nodelist[key_node->left]);
    right_node = &(tree->nodelist[key_node->right]);
    succ_node = &(tree->nodelist[succ_index]);

    succ_node->left = key_node->left;
    left_node->parent = succ_index;
    succ_node->right = key_node->right;
    right_node->parent = succ_index;
    succ_node->parent = par;

    key_node->left = -1;
    key_node->right = -1;
    key_node->parent = -1;

    if(par != -1) {
        if(key_index == par_node->left)
            par_node->left = succ_index;
        else 
            par_node->right = succ_index;
    } else
        tree->root = succ_index;
}

int bst_delete_(TREE *tree, int key) {
    int key_index = bst_search(tree, key);
    if(key_index == -1) {
        return -1;
    }

    TNODE *key_node = &(tree->nodelist[key_index]);
    if(key_node->left != -1 && key_node->right != -1)
        delete_caseb(tree, key_index);
    else
        delete_casea(tree, key_index);

    return key_index;
}