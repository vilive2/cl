#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "avl.h"

int successor(TREE *tree, int root) {
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

void inorder(TREE *tree, int root, void **dest) {
    if(root == -1) return;

    inorder(tree, tree->nodelist[root].left, dest);
    memcpy(*dest, tree->nodelist[root].key, tree->key_size);
    *dest = (*dest) + tree->key_size;
    inorder(tree, tree->nodelist[root].right, dest);
}

void free_node(TREE *tree, int node) {
    if(tree->freelist == -1) {
        tree->nodelist[node].right = -1;
    } else {
        tree->nodelist[node].right = tree->freelist;
    }
    tree->freelist = node;
}

int resize(TREE *tree);

int get_free_node(TREE *tree) {
    if(tree->freelist == -1) {
        if(resize(tree))
            return -1;
    }

    int node = tree->freelist;
    tree->freelist = tree->nodelist[node].right;

    return node;
}

int resize(TREE *tree) {
    size_t new_cap = tree->capacity * 2;
    if(NULL == (tree->nodelist = (TNODE *)realloc(tree->nodelist, new_cap * sizeof(TNODE)))) {
        return -1;
    } 

    void *dataptr = tree->nodelist[0].key;
    if(NULL == (dataptr = realloc(dataptr, new_cap * tree->key_size))) {
        return -1;
    }
    for(int i = 0 ; i < new_cap ; i++) {
        tree->nodelist[i].key = dataptr;
        dataptr = dataptr + tree->key_size;
    }

    for(int i = tree->size ; i < new_cap - 1 ; i++) {
        tree->nodelist[i].right = i + 1;
    }
    tree->nodelist[new_cap - 1].right = -1;
    tree->freelist = tree->size;
    tree->capacity = new_cap;

    return 0;
}

int print_tree_(TREE *tree, int root, int line_num, int *line_end, char (*lines)[201]);
void print_tree(TREE *tree, int root) {
    int h = 0;
    if(root != -1)
        h = 2 * tree->nodelist[root].height;
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

int min(int a, int b) {
    return a>b?b:a;
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
    *line_end = (*line_end) + 1 + snprintf(&lines[line_num][(*line_end)+1], 200 - min(200, (*line_end)+1) + 1, "%d", *(int *)tree->nodelist[root].key);

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