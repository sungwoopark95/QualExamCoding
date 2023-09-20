/* array를 활용한 Queue 구현
    시작과 끝을 나타내는 index를 활용하여 구현한다.*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define QUEUE_SIZE 5

typedef struct {
    int* arr;
    int capacity; 
    int start; //Queue의 First in이 있는 index
    int end; //다음에 들어올 원소가 위치할 index(Queue가 가득 차거나 텅 비어있을 때는 start와 값이 같게 된다.)
    int size;

} Queue;

void queue_init(Queue* q, int capacity) {
    q->capacity = capacity;
    q->start=0;
    q->end=0;
    q->size=0;
    q->arr = (int*)malloc(capacity*sizeof(int));
}

void queue_destroy(Queue* q){
    free(q->arr);
}

bool is_full(Queue* q) {
    // return ((q->end - q-> start) % q->capacity == 0) && ((q->end - q-> start) / q->capacity >= 1);
    return (q->size == q->capacity);
}

bool is_empty(Queue* q) {
    // return q->rear == q->start;
    return q->size==0 ;
}

void enqueue(Queue* q, int item) {
    if (is_full(q)) {
        printf("Queue is full\n");
        return;
    }
    q->arr[q->end % q->capacity] = item;
    q->end++;
    q->size++;
}

int dequeue(Queue* q) {
    if (is_empty(q)) {
        printf("Queue is empty\n");
        // return -1;
        fprintf(stderr, "FAILED TO DEQUEUE SINCE IT IS EMPTY.\n");
        exit(EXIT_FAILURE);
    }
    int item = q->arr[q->start%q->capacity];
    q->start+=1;
    q->size--;
    return item;
}

int size_method(Queue* q) {
    // return (q->end - q->start) % q->capacity;
    return q->size;
}

int main(void) {
    

    Queue q;
    queue_init(&q, QUEUE_SIZE);

    printf("Size : %d\n", size_method(&q)); 
    enqueue(&q, 1);
    printf("Size : %d\n", size_method(&q)); 
    enqueue(&q, 2);
    printf("Size : %d\n", size_method(&q)); 
    enqueue(&q, 3);
    printf("Size : %d\n", size_method(&q)); 
    enqueue(&q, 4);
    printf("Size : %d\n", size_method(&q)); 
    enqueue(&q, 5);
    printf("Size : %d\n", size_method(&q)); 
    enqueue(&q, 6);
    printf("Size : %d\n", size_method(&q)); 

    printf("Dequeue : %d\n", dequeue(&q));
    printf("Size : %d\n", size_method(&q)); 

    printf("Dequeue : %d\n", dequeue(&q));
    printf("Size : %d\n", size_method(&q)); 

    printf("Dequeue : %d\n", dequeue(&q));
    printf("Size : %d\n", size_method(&q)); 

    printf("Dequeue : %d\n", dequeue(&q));
    printf("Size : %d\n", size_method(&q)); 

    printf("Dequeue : %d\n", dequeue(&q));
    printf("Size : %d\n", size_method(&q)); 

    printf("Dequeue : %d\n", dequeue(&q));
    printf("Size : %d\n", size_method(&q)); 

    return 0;
}