#include<stdio.h>
#include<string.h>
#include "../../data-structures/list/list.h"
#include "../../data-structures/stack/stack.h"
#define N 1000

LIST adj[N];
int n;
char vis[N];

void dfs(int s) {
    memset(vis, 0, n);

    STACK st;
    stack_init(&st, sizeof(int), n);
    stack_push(&st, &s);
    vis[s] = 1;

    while(st.size > 0) {
        int u;
        stack_pop(&st, &u);

        for(int i = 0 ; i < adj[u].size ; i++) {
            int v;
            list_get(&(adj[u]), &v, i);
            if(vis[v] == 0) {
                vis[v] = 1;
                stack_push(&st, &v);
            }
        }

        printf("%d ", u);
    }

    printf("\n");
}

int main() {

    scanf("%d", &n);
    for(int i = 0 ; i < n ; i++) {
        list_init(&adj[i], 0, sizeof(int));
    }

    int m;
    scanf("%d", &m);
    for(int i = 0 ; i < m ; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        v--;
        u--;
        list_append(&adj[u], &v);
        list_append(&adj[v], &u);
    }

    dfs(0);

    return 0;
}