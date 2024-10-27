#include<stdio.h>
#include<stdlib.h>

#define N 100006

typedef struct {
    int *elements;
    size_t capacity, size;
} LIST;

int init_list(LIST *list, size_t capacity);
int append(LIST *list, int element);

int dfs(int u, LIST *adj, int *a, int *vis, int n, int cats, int max_cats);

int main() {

    int n, m;
    scanf("%d%d", &n, &m);

    int a[N];
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    LIST adj[n];
    for(int i = 0 ; i < n ; i++) if(init_list(&adj[i], 1)) exit(1);

    for(int i = 1; i < n; i++) {
        int xi, yi;
        scanf("%d%d", &xi, &yi);
        if(append(&adj[xi-1], yi-1)) exit(1);
        if(append(&adj[yi-1], xi-1)) exit(1);
    }

    int vis[N] = {0};

    int ans = dfs(0, adj, a, vis, n, 0, m);
    printf("%d\n", ans);

    return 0;
}

int dfs(int u, LIST *adj, int *a, int *vis, int n, int cats, int max_cats) {
    if(a[u]) cats++;
    else cats = 0;
    if(cats > max_cats) return 0;

    vis[u] = 1;
    if(adj[u].size == 1 && vis[adj[u].elements[0]]) return 1;

    int rest = 0;

    for(int i = 0 ; i < adj[u].size ; i++) {
        int v = adj[u].elements[i];
        if(!vis[v]) {
            rest += dfs(v, adj, a, vis, n, cats, max_cats);
        }
    }

    return rest;
}

int init_list(LIST *list, size_t capacity) {
    list->capacity = capacity;
    list->size = 0;
    if(NULL == (list->elements = (int *)malloc(sizeof(int)*capacity))) {
        fprintf(stdout, "memory allocation failed\n");
        return -1;
    }

    return 0;
}

int append(LIST *list, int element) {
    if(list->size == list->capacity) {
        list->capacity = 2 * list->capacity;
        if(NULL == (list->elements = (int *)realloc(list->elements, sizeof(int)*list->capacity))) {
            fprintf(stdout, "memory reallocation failed\n");
            return -1;
        }
    }

    list->elements[list->size++] = element;

    return 0;
}