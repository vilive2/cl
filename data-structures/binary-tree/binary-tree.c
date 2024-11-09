#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include "binary-tree.h"

int height(TREE *tree, int root) {
    if(root == -1) return 0;
    if(tree->nodelist[root].left == -1 && 
        tree->nodelist[root].right == -1) return 0;

    int left_subtree_height = height(tree, tree->nodelist[root].left);
    int right_subtree_height = height(tree, tree->nodelist[root].right);
    int curr_subtree_height = left_subtree_height + 1;

    if(right_subtree_height > left_subtree_height) 
        curr_subtree_height = right_subtree_height + 1;

    return curr_subtree_height;
}

void preorder(TREE *tree, int root, int *dest, int *cur_index) {
    if(root == -1) return;
    
    dest[*cur_index] = tree->nodelist[root].data;
    *cur_index = *cur_index + 1;
    preorder(tree, tree->nodelist[root].left, dest, cur_index);
    preorder(tree, tree->nodelist[root].right, dest, cur_index);
}

void inorder(TREE *tree, int root, int *dest, int *cur_index) {
    if(root == -1) return;

    inorder(tree, tree->nodelist[root].left, dest, cur_index);
    dest[*cur_index] = tree->nodelist[root].data;
    *cur_index = *cur_index + 1;
    inorder(tree, tree->nodelist[root].right, dest, cur_index);
}

void postorder(TREE *tree, int root, int *dest, int *cur_index) {
    if(root == -1) return;

    postorder(tree, tree->nodelist[root].left, dest, cur_index);
    postorder(tree, tree->nodelist[root].right, dest, cur_index);
    dest[*cur_index] = tree->nodelist[root].data;
    *cur_index = *cur_index + 1;
}

int init_tree(TREE *tree) {
    assert(tree != NULL);
    tree->capacity = MAX_NODES;
    tree->size = 0;
    if(NULL == (tree->nodelist = (TNODE *)malloc(tree->capacity*sizeof(TNODE)))) {
        return -1;
    }

    tree->root = -1;
    tree->freelist = 0;

    int i;
    for(i = 1 ; i < tree->capacity ; i++)
        tree->nodelist[i-1].right = i;

    tree->nodelist[i-1].right = -1;
    
    return 0;
}

void free_node(TREE *tree, int node) {
    if(tree->freelist == -1) {
        tree->nodelist[node].right = -1;
    } else {
        tree->nodelist[node].right = tree->freelist;
    }
    tree->freelist = node;
}

int get_free_node(TREE *tree) {
    if(tree->freelist == -1)
        return -1;

    int node = tree->freelist;
    tree->freelist = tree->nodelist[node].right;

    return node;
}

void read_tree(TREE *tree) {
    int size;
    scanf("%d", &size);
    if(init_tree(tree) == -1) {
        fprintf(stderr, "out of memory");
        exit(0);
    }
    tree->size = size;

    int i;
    TNODE *node;
    for(node = tree->nodelist, i = 0; i < size; node++, i++){
        scanf("%d%d%d", &(node->data), &(node->left), &(node->right));
        if(node->left != -1) tree->nodelist[node->left].parent = i;
        if(node->right != -1) tree->nodelist[node->right].parent = i;
    }
    tree->root=0;
}

void print_nodelist(TREE *tree) {
    printf("Tree:\nnum_of_nodes: %ld, root : %d\n", tree->size, tree->root);
    printf("index data left right parent height\n");
    int i;
    TNODE *node;
    for(node = tree->nodelist, i = 0; i < tree->size; node++, i++)
        printf("%5d %4d %4d %5d %6d %6d\n", i, (node->data), (node->left), (node->right), (node->parent), (node->height));
}

int min(int a, int b) {
    return a>b? b: a;
}

int print_tree_(TREE *tree, int root, int line_num, int *line_end, char (*lines)[201]);
void print_tree(TREE *tree, int root) {
    int h = 2*height(tree, root);
    printf("\nPRINT TREE : %d\n", h);
    char lines[h+1][201];
    for(int i = 0 ; i < h+1 ; i++) lines[i][0] = '\0';
    int line_end = -1;
    print_tree_(tree, root, 0, &line_end, lines);

    for(int i = 0 ; i < h+1 ; i++) {
        printf("%s\n", lines[i]);
    }
}

void fillspace(char *c, int end_index) {
    int start_index = strlen(c);
    for(int i = start_index ; i < end_index ; i++)
        c[i] = ' ';
    c[end_index] = '\0';
}

int print_tree_(TREE *tree, int root, int line_num, int *line_end, char (*lines)[201]) {
    if(root == -1) {
        return -1;
    }

    int root_index, left_child_index, right_child_index;

    int line_start = strlen(&lines[line_num][0]);
    fillspace(&(lines[line_num+1][0]), min(200, line_start));
    
    left_child_index = print_tree_(tree, tree->nodelist[root].left, line_num + 2, line_end, lines);
    for(int i = line_start ; i <= (*line_end) && i < 200 ; i++) {
        lines[line_num][i] = ' ';
        if(i>=left_child_index && left_child_index != -1)
            lines[line_num][i] = '-';
        
        lines[line_num+1][i] = ' ';
        if(i == left_child_index)
            lines[line_num+1][i] = '|';
    }

    lines[line_num+1][min(200, ((*line_end)+1))] = '\0'; 

    root_index = (*line_end)+1;
    *line_end = (*line_end) + 1 + snprintf(&lines[line_num][(*line_end)+1], 200 - min(200, (*line_end)+1) + 1, "%d", tree->nodelist[root].data);

    fillspace(&(lines[line_num+1][0]), min(200, *line_end));

    line_start = *line_end;
    
    right_child_index = print_tree_(tree, tree->nodelist[root].right, line_num + 2, line_end, lines);
    for(int i = line_start ; i <= (*line_end) && i < 200 ; i++) {
        lines[line_num][i] = ' ';
        if(i <= right_child_index) 
            lines[line_num][i] = '-';

        lines[line_num+1][i] = ' ';
        if(i == right_child_index)
            lines[line_num+1][i] = '|';
    }
    lines[line_num][min(200, (*line_end)+1)] = '\0';
    lines[line_num+1][min(200, (*line_end)+1)] = '\0';

    return root_index;
}