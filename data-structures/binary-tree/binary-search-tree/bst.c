#include<stddef.h>
#include<stdio.h>
#include "../binary-tree.h"
#include "bst.h"

void bst_insert_(TREE *t, int key_index);

void bst_build(TREE *t) {
    if(t->num_nodes == 0) {
        t->root = -1;
        return;
    }
    t->root = 0;
    t->nodelist[0].parent = -1;
    t->nodelist[0].left = -1;
    t->nodelist[0].right = -1;

    for(int i = 1 ; i < t->num_nodes ; i++) {
        t->nodelist[i].left = -1;
        t->nodelist[i].right = -1;
        bst_insert_(t, i);
    }

    t->freelist = t->num_nodes;
    if(t->num_nodes == t->capacity) 
        t->freelist = -1;
}

void bst_insert(TREE *t, int key) {
    int key_index = get_free_node(t);
    if(key_index<0) {
        return;
    }

    t->nodelist[key_index].left = -1;
    t->nodelist[key_index].right = -1;
    t->nodelist[key_index].data = key;

    bst_insert_(t, key_index);
    t->num_nodes++;
}

void bst_insert_(TREE *t, int key_index) {
    if(t->root == -1) {
        t->root = key_index;
        t->nodelist[key_index].parent = -1;
        return;
    }

    int par = t->root;
    TNODE *node = &(t->nodelist[key_index]);
    int key = node->data;
    TNODE *cur = &(t->nodelist[par]);
    
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

        cur = &(t->nodelist[par]);
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

int bst_search(TREE *t, int key) {
    int cur = t->root;
    while(cur != -1) {
        if(t->nodelist[cur].data == key) 
            break;
        else if(t->nodelist[cur].data < key) 
            cur = t->nodelist[cur].right;
        else 
            cur = t->nodelist[cur].left;
    }

    return cur;
}

int bst_successor(TREE *t, int root) {
    if(root == -1)
        return -1;

    int par = t->nodelist[root].right;
    int cur = par;

    while(cur != -1) {
        par = cur;
        cur = t->nodelist[cur].left;
    }

    return par;
}

void delete_casea(TREE *t, int key_index) {
    TNODE *par_node, *key_node, *child_node;
    key_node = &(t->nodelist[key_index]);
    int par = key_node->parent, child = key_node->left;
    if(child == -1)
        child = key_node->right;
    if(par != -1)
        par_node = &(t->nodelist[par]);
    if(child != -1)
        child_node = &(t->nodelist[child]);

    key_node->left = -1;
    key_node->right = -1;
    key_node->parent = -1;

    if(par != -1) {
        if(key_index == par_node->left)
            par_node->left = child;
        else 
            par_node->right = child;
    } else 
        t->root = child;

    if(child != -1) 
        child_node->parent = par;
}

void delete_caseb(TREE *t, int key_index) {
    int par, succ_index = bst_successor(t, key_index);
    delete_casea(t, succ_index);
    
    TNODE *par_node, *key_node, *left_node, *right_node, *succ_node;
    key_node = &(t->nodelist[key_index]);
    par = key_node->parent;
    if(par != -1) 
        par_node = &(t->nodelist[par]);

    left_node = &(t->nodelist[key_node->left]);
    right_node = &(t->nodelist[key_node->right]);
    succ_node = &(t->nodelist[succ_index]);

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
        t->root = succ_index;
}

void bst_delete(TREE *t, int key) {
    int key_index = bst_search(t, key);
    if(key_index == -1) {
        return;
    }

    TNODE *key_node = &(t->nodelist[key_index]);
    if(key_node->left != -1 && key_node->right != -1)
        delete_caseb(t, key_index);
    else
        delete_casea(t, key_index);

    free_node(t, key_index);
    t->num_nodes--;
}