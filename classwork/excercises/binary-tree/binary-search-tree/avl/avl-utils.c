#include<stddef.h>
#include "../../binary-tree.h"
#include "../bst.h"

int rotate_LL(TREE *tree, int root_index) {
    int k2 = root_index;
    int k1 = tree->nodelist[k2].left;
    int Z = tree->nodelist[k2].right;
    int X = tree->nodelist[k1].left;
    int Y = tree->nodelist[k1].right;

    // rotate
    tree->nodelist[k2].left = Y;
    tree->nodelist[k1].right = k2;

    // update heights
    tree->nodelist[k2].height = 1 + MAX(HEIGHT(tree, Y), HEIGHT(tree, Z));
    tree->nodelist[k1].height = 1 + MAX(HEIGHT(tree, X), HEIGHT(tree, k2));

    return k1;
}

int rotate_RR(TREE *tree, int root_index) {
    int k1 = root_index;
    int X = tree->nodelist[k1].left;
    int k2 = tree->nodelist[k1].right;
    int Y = tree->nodelist[k2].left;
    int Z = tree->nodelist[k2].right;

    // rotate
    tree->nodelist[k1].right = Y;
    tree->nodelist[k2].left = k1;

    // update heights
    tree->nodelist[k1].height = 1 + MAX(HEIGHT(tree, X), HEIGHT(tree, Y));
    tree->nodelist[k2].height = 1 + MAX(HEIGHT(tree, k1), HEIGHT(tree, Z));

    return k2;
}

int rotate_LR(TREE *tree, int root_index) {
    tree->nodelist[root_index].left = rotate_RR(tree, tree->nodelist[root_index].left);
    return rotate_LL(tree, root_index);
}

int rotate_RL(TREE *tree, int root_index) {
    tree->nodelist[root_index].right = rotate_LL(tree, tree->nodelist[root_index].right);
    return rotate_RR(tree, root_index);
}

int balance(TREE *tree, int root_index) {
    if(root_index == -1) 
        return -1;

    int left = tree->nodelist[root_index].left;
    int right = tree->nodelist[root_index].right;

    if(HEIGHT(tree, left) - HEIGHT(tree, right) > 1) {
        // L
        if(HEIGHT(tree, tree->nodelist[left].left) >= HEIGHT(tree, tree->nodelist[left].right)) {
            // L
            return rotate_LL(tree, root_index);
        } else {
            // R
            return rotate_LR(tree, root_index);
        }
    } else if(HEIGHT(tree, right) - HEIGHT(tree, left) > 1) {
        // R
        if(HEIGHT(tree, tree->nodelist[right].left) >= HEIGHT(tree, tree->nodelist[right].right)) {
            // L
            return rotate_RL(tree, root_index);
        } else {
            // R
            return rotate_RR(tree, root_index);
        }
    }

    tree->nodelist[root_index].height = 1 + MAX(HEIGHT(tree, left), HEIGHT(tree, right));

    return root_index;
}