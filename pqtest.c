#include<stdio.h>
#include "data-structures/priority-queue/priority-queue.h"

int comp(const void *a, const void *b) {
    return *(int *)a - *(int *)b ;
}


void printpq(PRIORITY_QUEUE *pq) {
    int *arr = (int *)pq->elements;
    for(int i = 0 ; i < pq->size ; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {

    PRIORITY_QUEUE pq;

    priority_queue_init(&pq, sizeof(int), 5, comp);
    
    int el = 100;
    priority_queue_push(&pq, &el);

    printpq(&pq);

    el = 20;
    priority_queue_push(&pq, &el);

    printpq(&pq);

    el = 3;
    priority_queue_push(&pq, &el);

    printpq(&pq);

    el = 5;
    priority_queue_push(&pq, &el);

    printpq(&pq);

    priority_queue_top(&pq, &el);
    printf("min: %d\n", el);

    el = 1;
    priority_queue_push(&pq, &el);

    printpq(&pq);

    priority_queue_top(&pq, &el);
    printf("min: %d\n", el);

    if(priority_queue_pop(&pq, &el) < 0 )
        return 1;

    printpq(&pq);

    priority_queue_top(&pq, &el);
    printf("min: %d\n", el);

    if(priority_queue_pop(&pq, &el) < 0)
         return 1;

    printpq(&pq);

    if(priority_queue_pop(&pq, &el) < 0)
         return 1;

    priority_queue_top(&pq, &el);
    printf("min: %d\n", el);

    printpq(&pq);

    return 0;
}