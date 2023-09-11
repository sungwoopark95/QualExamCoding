#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000  // 임의의 최대 큐 크기

typedef struct {
    int queue[MAX_SIZE];
    int size;
} FrontMiddleBackQueue;

FrontMiddleBackQueue* createQueue() {
    FrontMiddleBackQueue* q = malloc(sizeof(FrontMiddleBackQueue));
    q->size = 0;
    return q;
}

int getMiddleIndex(FrontMiddleBackQueue* q) {
    int length = q->size;
    if (length % 2 == 0) {
        return length / 2 - 1;
    }
    return length / 2;
}

void pushFront(FrontMiddleBackQueue* q, int val) {
    for (int i = q->size; i > 0; i--) {
        q->queue[i] = q->queue[i-1];
    }
    q->queue[0] = val;
    q->size++;
}

void pushMiddle(FrontMiddleBackQueue* q, int val) {
    int middle = getMiddleIndex(q);
    for (int i = q->size; i > middle; i--) {
        q->queue[i] = q->queue[i-1];
    }
    q->queue[middle] = val;
    q->size++;
}

void pushBack(FrontMiddleBackQueue* q, int val) {
    q->queue[q->size++] = val;
}

int popFront(FrontMiddleBackQueue* q) {
    if (q->size == 0) {
        return -1;
    }
    int res = q->queue[0];
    for (int i = 0; i < q->size - 1; i++) {
        q->queue[i] = q->queue[i+1];
    }
    q->size--;
    return res;
}

int popMiddle(FrontMiddleBackQueue* q) {
    if (q->size == 0) {
        return -1;
    }
    int middle = getMiddleIndex(q);
    int res = q->queue[middle];
    for (int i = middle; i < q->size - 1; i++) {
        q->queue[i] = q->queue[i+1];
    }
    q->size--;
    return res;
}

int popBack(FrontMiddleBackQueue* q) {
    if (q->size == 0) {
        return -1;
    }
    return q->queue[--q->size];
}

int main() {
    FrontMiddleBackQueue* q = createQueue();
    pushFront(q, 1);
    pushMiddle(q, 2);
    pushBack(q, 3);
    printf("%d\n", popFront(q));  // 1
    printf("%d\n", popMiddle(q));  // 2
    printf("%d\n", popBack(q));  // 3
    free(q);
    return 0;
}
