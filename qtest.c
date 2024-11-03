#include<stdio.h>
#include "data-structures/queue/queue.h"

int main() {

    QUEUE q;
    queue_init(&q, sizeof(int), 20);

    int el = 10;
    queue_push_back(&q, &el);
    el = 20;
    queue_push_back(&q, &el);
    el = -28;
    queue_push_back(&q, &el);
    el = 388;
    queue_push_back(&q, &el);

    queue_front(&q, &el);
    printf("front %d \n", el);

    queue_pop_front(&q, &el);
    printf("pop %d \n", el);

    queue_pop_front(&q, &el);
    printf("pop %d \n", el);

    queue_pop_front(&q, &el);
    printf("pop %d \n", el);

    queue_pop_front(&q, &el);
    printf("pop %d \n", el);

    queue_pop_front(&q, &el);
    printf("pop %d \n", el);

    return 0;
}