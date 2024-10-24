#include<stdlib.h>
#include<stdio.h>
#include "node.h"

int max(int a, int b) {
    return a>b? a : b;
}

int height(TREE *t, int root) {
    if(root == -1) return 0;
    if(t->nodelist[root].left == -1 && 
        t->nodelist[root].right == -1) return 0;

    return 1 + max(height(t, t->nodelist[root].left), 
                    height(t, t->nodelist[root].right));
}

int leaves(TREE *t, int root) {
    if(root == -1) return 0;
    if(t->nodelist[root].left == -1 && 
        t->nodelist[root].right == -1) return 1;

    return leaves(t, t->nodelist[root].left)+ 
                    leaves(t, t->nodelist[root].right);
}

int weight(TREE *t, int root) {
    if(root == -1) return 0;

    return t->nodelist[root].d +
            weight(t, t->nodelist[root].left)+ 
                weight(t, t->nodelist[root].right);
}

void preorder(TREE *t, int root) {
    if(root == -1) return;
    
    printf("%d ", t->nodelist[root].d);
    preorder(t, t->nodelist[root].left);
    preorder(t, t->nodelist[root].right);
}

void inorder(TREE *t, int root) {
    if(root == -1) return;

    inorder(t, t->nodelist[root].left);
    printf("%d ", t->nodelist[root].d);
    inorder(t, t->nodelist[root].right);
}

void postorder(TREE *t, int root) {
    if(root == -1) return;

    postorder(t, t->nodelist[root].left);
    postorder(t, t->nodelist[root].right);
    printf("%d ", t->nodelist[root].d);
}

int pathsum(TREE *t, int root, int target) {
    if(root == -1) return target == 0;

    target -= t->nodelist[root].d;

    return pathsum(t, t->nodelist[root].left, target) ||
                pathsum(t, t->nodelist[root].right, target);
}



int main() {

    TREE t;
    read_tree(&t);
    print_tree(&t);

    printf("height: %d\n", height(&t, t.root));
    printf("leaves: %d\n", leaves(&t, t.root));
    printf("weight: %d\n", weight(&t, t.root));

    printf("preorder: ");
    preorder(&t, t.root);
    printf("\n");

    printf("inorder: ");
    inorder(&t, t.root);
    printf("\n");

    printf("postorder: ");
    postorder(&t, t.root);
    printf("\n");


    int target = 12;
    printf("pathsum of %d exist: %d\n", target, pathsum(&t, t.root, target));

    return 0;
}
