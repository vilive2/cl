#include<stdio.h>
#include<string.h>
#include "../../data-structures/list/list.h"
#include "../../data-structures/queue/queue.h"
#define N 1000

LIST adj[N];
int n;
char vis[N];

void bfs(int s) {
    memset(vis, 0, n);

    QUEUE q;
    queue_init(&q, sizeof(int), n);
    queue_push_back(&q, &s);
    vis[0] = 1;

    while(q.size > 0) {
        int u;
        queue_pop_front(&q, &u);

        for(int i = 0 ; i < adj[u].size ; i++) {
            int v;
            list_get(&(adj[u]), &v, i);
            if(vis[v] == 0) {
                vis[v] = 1;
                queue_push_back(&q, &v);
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

    bfs(0);

    return 0;
}