#include<stddef.h>
#include<stdio.h>
#include "../binary-tree.h"
#include "bst.h"

void bst_insert_(TREE *t, int root, int key_index);

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
        bst_insert_(t, t->root, i);
    }

    t->freelist = -1;
}

void bst_insert(TREE *t, int root, int key) {
    int key_index = get_free_node(t);
    if(key_index<0) {
        return;
    }

    t->nodelist[key_index].left = -1;
    t->nodelist[key_index].right = -1;
    t->nodelist[key_index].data = key;

    bst_insert_(t, root, key_index);
}

void bst_insert_(TREE *t, int root, int key_index) {
    if(root == -1) {
        t->root = key_index;
        t->nodelist[key_index].parent = root;
        return;
    }

    if(t->nodelist[root].data < t->nodelist[key_index].data) {
        if(t->nodelist[root].right == -1) {
            t->nodelist[root].right = key_index;
            t->nodelist[key_index].parent = root;
        } else {
            bst_insert_(t, t->nodelist[root].right, key_index);
        }
    } else {
        if(t->nodelist[root].left == -1) {
            t->nodelist[root].left = key_index;
            t->nodelist[key_index].parent = root;
        } else {
            bst_insert_(t, t->nodelist[root].left, key_index);
        }
    }
}

int bst_search(TREE *t, int root, int key) {
    if(root == -1) 
        return -1;

    if(t->nodelist[root].data == key) {
        return root;
    } else if(t->nodelist[root].data > key) {
        return bst_search(t, t->nodelist[root].left, key);
    }
    
    return bst_search(t, t->nodelist[root].right, key);
}

int bst_minimum(TREE *t, int root) {
    if(root == -1) 
        return -1;

    if(t->nodelist[root].left == -1) {
        return root;
    } 

    return bst_minimum(t, t->nodelist[root].left);
}

int bst_successor(TREE *t, int root) {
    if(root == -1)
        return -1;

    if(t->nodelist[root].right == -1) {
        return -1;
    }

    return bst_minimum(t, t->nodelist[root].right);
}

void delete(TREE *t, int node);

void bst_delete(TREE *t, int root, int key) {
    if(root == -1) {
        fprintf(stderr, "%d not found\n", key);
        return;
    }

    if(t->nodelist[root].data == key) {
        delete(t, root);
    } else if(t->nodelist[root].data < key) {
        bst_delete(t, t->nodelist[root].right, key);
    } else {
        bst_delete(t, t->nodelist[root].left, key);
    }
}

void detach_successor(TREE *t, int succ_index) {
    TNODE *succ = &(t->nodelist[succ_index]);
    TNODE *parent = &(t->nodelist[succ->parent]);
    if(parent->left == succ_index) {
        parent->left = succ->right;
    } else {
        parent->right = succ->right;
    }

    if(succ->right != -1)
        t->nodelist[succ->right].parent = succ->parent;
}

void delete(TREE *t, int node_index) {
    int replacer = -1;

    TNODE *node = &(t->nodelist[node_index]);
    TNODE *left = NULL, *right = NULL, *parent = NULL;
    if(node->parent != -1) {
        parent = &(t->nodelist[node->parent]);
    }
    if(node->left != -1) {
        left = &(t->nodelist[node->left]);
    }

    if(node->right != -1) {
        right = &(t->nodelist[node->right]);
    }

    // case 1 both child
    if(node->left != -1 && node->right != -1) {
        replacer = bst_successor(t, node_index);
        detach_successor(t, replacer);
    }
    // case 2 single child
    else if(node->left == -1) {
        replacer = node->right;
    } else if(node->right == -1) {
        replacer = node->left;
    }

    // fix link
    if(left) {
        left->parent = replacer;
        t->nodelist[replacer].left = node->left;
    }

    if(right) {
        right->parent = replacer;
        t->nodelist[replacer].right = node->right;
    }


    if(replacer != -1)
        t->nodelist[replacer].parent = node->parent;
    if(node->parent == -1) {
        t->root = replacer;
    } else {
        if(node_index == parent->left) {
            parent->left = replacer;
        } else {
            parent->right = replacer;
        }
    }

    // ADD node to freelist
    free_node(t, node_index);
}