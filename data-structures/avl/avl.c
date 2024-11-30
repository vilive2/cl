#include<stddef.h>
#include<string.h>
#include<assert.h>
#include<stdlib.h>
#include "avl.h"

int avl_insert_(TREE *, int, int);
int avl_delete_(TREE *, int, const void *, int *);
extern int free_node(TREE *, int);
extern int get_free_node(TREE *);
extern void inorder(TREE *, int, void **);

int avl_init(TREE *tree, size_t key_size, int (*comp)(const void *, const void *)) {
    assert(tree != NULL);
    assert(key_size != 0);
    assert(comp != NULL);

    tree->key_size = key_size;
    tree->comp = comp;
    tree->capacity = 1;
    tree->size = 0;
    if(NULL == (tree->nodelist = (TNODE *)malloc(tree->capacity*sizeof(TNODE)))) {
        return -1;
    }

    if(NULL == (tree->nodelist[0].data = malloc(key_size))) {
        return -1;
    }

    tree->root = -1;
    tree->freelist = 0;

    tree->nodelist[0].right = -1;
    
    return 0;
}

int avl_search(TREE *tree, const void *key) {
    int cur = tree->root;
    while(cur != -1) {
        int r = tree->comp(tree->nodelist[cur].data, key);
        if( r == 0 ) 
            break;
        else if(r < 0) 
            cur = tree->nodelist[cur].right;
        else 
            cur = tree->nodelist[cur].left;
    }

    return cur;
}

int avl_insert(TREE *tree, const void *key) {
    int key_index = get_free_node(tree);
    if(key_index<0) {
        return -1;
    }

    tree->nodelist[key_index].left = -1;
    tree->nodelist[key_index].right = -1;
    memcpy(tree->nodelist[key_index].data, key, tree->key_size);

    tree->nodelist[key_index].height = 0;
    tree->root = avl_insert_(tree, tree->root, key_index); 
    tree->size++;

    return key_index;
}

int avl_delete(TREE *tree, const void *key) {
    int key_index;
    tree->root = avl_delete_(tree, tree->root, key, &key_index);

    if(key_index < 0)
        return -1;

    free_node(tree, key_index);
    tree->size--;

    return 0;
}

int avl_keys(TREE *tree, void **keys) {
    inorder(tree, tree->root, keys);
}

// driver functions
extern int balance(TREE *tree, int root_index);
extern int successor(TREE *tree, int root_index);

int avl_insert_(TREE *tree, int root_index, int key_index) {
    if(root_index == -1) 
        return key_index;
    else if(tree->nodelist[root_index].data < tree->nodelist[key_index].data) {
        tree->nodelist[root_index].right = avl_insert_(tree, tree->nodelist[root_index].right, key_index);
    } else if(tree->nodelist[root_index].data > tree->nodelist[key_index].data) {
        tree->nodelist[root_index].left = avl_insert_(tree, tree->nodelist[root_index].left, key_index);
    }
    
    return balance(tree, root_index);
}

int avl_delete_(TREE *tree, int root_index, const void *key, int *key_index) {
    if(root_index == -1) {
        *key_index = -1;
        return -1;
    }

    int r = tree->comp(key, tree->nodelist[root_index].data);
    if( r < 0 ) {
        tree->nodelist[root_index].left = avl_delete_(tree, tree->nodelist[root_index].left, key, key_index);
    } else if( r > 0 ) {
        tree->nodelist[root_index].right = avl_delete_(tree, tree->nodelist[root_index].right, key, key_index);
    } else {
        *key_index = root_index;
        if(tree->nodelist[root_index].left != -1 &&
            tree->nodelist[root_index].right != -1) {

            int succ_index = successor(tree, root_index);
            assert(succ_index != -1);
            tree->nodelist[root_index].right = avl_delete_(tree, tree->nodelist[root_index].right, 
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