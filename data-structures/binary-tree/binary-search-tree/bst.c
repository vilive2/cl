#include<stddef.h>
#include<stdio.h>
#include "../binary-tree.h"
#include "bst.h"

int bst_successor(TREE *tree, int root) {
    if(root == -1)
        return -1;

    int par = tree->nodelist[root].right;
    int cur = par;

    while(cur != -1) {
        par = cur;
        cur = tree->nodelist[cur].left;
    }

    return par;
}

extern void bst_insert_(TREE *tree, int key_index);
extern int bst_delete_(TREE *tree, DATA key);

int bst_search(TREE *tree, DATA key) {
    int cur = tree->root;
    while(cur != -1) {
        if(tree->nodelist[cur].data == key) 
            break;
        else if(tree->nodelist[cur].data < key) 
            cur = tree->nodelist[cur].right;
        else 
            cur = tree->nodelist[cur].left;
    }

    return cur;
}

int bst_insert(TREE *tree, DATA key) {
    #ifdef DEBUG
    printf("insert process begin\n");
    #endif
    int key_index = get_free_node(tree);
    if(key_index<0) {
        return -1;
    }


    tree->nodelist[key_index].left = -1;
    tree->nodelist[key_index].right = -1;
    tree->nodelist[key_index].data = key;

    bst_insert_(tree, key_index);
    tree->size++;

    return 0;
}

int bst_delete(TREE *tree, DATA key) {
    
    int key_index = bst_delete_(tree, key);

    if(key_index < 0)
        return -1;

    free_node(tree, key_index);
    tree->size--;

    return 0;
}