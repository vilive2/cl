#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "binary-tree.h"

int height(TREE *t, int root) {
    if(root == -1) return 0;
    if(t->nodelist[root].left == -1 && 
        t->nodelist[root].right == -1) return 0;

    int left_subtree_height = height(t, t->nodelist[root].left);
    int right_subtree_height = height(t, t->nodelist[root].right);
    int curr_subtree_height = left_subtree_height + 1;

    if(right_subtree_height > left_subtree_height) 
        curr_subtree_height = right_subtree_height + 1;

    return curr_subtree_height;
}

void preorder(TREE *t, int root, int *dest, int *cur_index) {
    if(root == -1) return;
    
    dest[*cur_index] = t->nodelist[root].data;
    *cur_index = *cur_index + 1;
    preorder(t, t->nodelist[root].left, dest, cur_index);
    preorder(t, t->nodelist[root].right, dest, cur_index);
}

void inorder(TREE *t, int root, int *dest, int *cur_index) {
    if(root == -1) return;

    inorder(t, t->nodelist[root].left, dest, cur_index);
    dest[*cur_index] = t->nodelist[root].data;
    *cur_index = *cur_index + 1;
    inorder(t, t->nodelist[root].right, dest, cur_index);
}

void postorder(TREE *t, int root, int *dest, int *cur_index) {
    if(root == -1) return;

    postorder(t, t->nodelist[root].left, dest, cur_index);
    postorder(t, t->nodelist[root].right, dest, cur_index);
    dest[*cur_index] = t->nodelist[root].data;
    *cur_index = *cur_index + 1;
}

int init_tree(TREE *t, size_t capacity) {
    t->capacity = capacity;
    t->num_nodes = 0;
    t->root = -1;
    if(NULL == (t->nodelist = (TNODE *)malloc(t->capacity*sizeof(TNODE)))) {
        return -1;
    }
    
    return 0;
}

int resize(TREE *t, size_t capacity) {
    t->capacity = capacity;
    size_t next_size = capacity * sizeof(TNODE);
    printf("\n next cap: %ld * %ld\n", capacity, sizeof(TNODE));
    if(NULL == (t->nodelist = (TNODE *)realloc(t->nodelist, next_size))) {
        return -1;
    }

    return 0;
}

void free_node(TREE *t, int node) {
    if(t->freelist == -1) {
        t->nodelist[node].right = -1;
    } else {
        t->nodelist[node].right = t->freelist;
    }
    t->freelist = node;
}

void increase_free_list(TREE *t, int base, size_t size) {
    for(int i = 0 ; i < size ; i++) {
        free_node(t, base + i);
    }
}

int get_free_node(TREE *t) {
    if(t->freelist == -1) {
        if(resize(t, 1 + t->capacity * 2)) {
            return -1;
        }  
        increase_free_list(t, t->num_nodes, 1 + t->num_nodes);
    }

    int node = t-> freelist;
    t->freelist = t->nodelist[node].right;

    return node;
}

void read_tree(TREE *t) {
    int num_nodes;
    scanf("%data", &num_nodes);
    if(init_tree(t, num_nodes) == -1) {
        fprintf(stderr, "out of memory");
        exit(0);
    }
    t->num_nodes = num_nodes;

    int i;
    TNODE *node;
    for(node = t->nodelist, i = 0; i < num_nodes; node++, i++){
        scanf("%d%d%d", &(node->data), &(node->left), &(node->right));
        if(node->left != -1) t->nodelist[node->left].parent = i;
        if(node->right != -1) t->nodelist[node->right].parent = i;
    }
    t->root=0;
}

void print_nodelist(TREE *t) {
    printf("Tree:\nnum_of_nodes: %ld\n", t->num_nodes);
    printf("index data left right parent\n");
    int i;
    TNODE *node;
    for(node = t->nodelist, i = 0; i < t->num_nodes; node++, i++)
        printf("%5d %4d %4d %5d %6d\n", i, (node->data), (node->left), (node->right), (node->parent));
}

int min(int a, int b) {
    return a>b? b: a;
}

int print_tree_(TREE *t, int root, int line_num, int *line_end, char (*lines)[201]);
void print_tree(TREE *t, int root) {
    int h = 2*height(t, root);
    printf("\nPRINT TREE : %d\n", h);
    char lines[h+1][201];
    for(int i = 0 ; i < h+1 ; i++) lines[i][0] = '\0';
    int line_end = -1;
    print_tree_(t, root, 0, &line_end, lines);

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

int print_tree_(TREE *t, int root, int line_num, int *line_end, char (*lines)[201]) {
    if(root == -1) {
        return -1;
    }

    int root_index, left_child_index, right_child_index;

    int line_start = strlen(&lines[line_num][0]);
    fillspace(&(lines[line_num+1][0]), min(200, line_start));
    
    left_child_index = print_tree_(t, t->nodelist[root].left, line_num + 2, line_end, lines);
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
    *line_end = (*line_end) + 1 + snprintf(&lines[line_num][(*line_end)+1], 200 - min(200, (*line_end)+1) + 1, "%d", t->nodelist[root].data);

    fillspace(&(lines[line_num+1][0]), min(200, *line_end));

    line_start = *line_end;
    
    right_child_index = print_tree_(t, t->nodelist[root].right, line_num + 2, line_end, lines);
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