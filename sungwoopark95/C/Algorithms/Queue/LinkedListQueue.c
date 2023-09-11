#include <stdio.h>
#include <stdlib.h>

// 큐 노드 구조체 정의
typedef struct QNode {
    int data;
    struct QNode* next;
} QNode;

// 큐 구조체 정의
typedef struct {
    QNode* front;
    QNode* rear;
} Queue;

// 새로운 큐 노드 생성 함수
QNode* newQNode(int data) {
    QNode* temp = (QNode*)malloc(sizeof(QNode));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

// 큐 생성 함수
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enQueue(Queue* q, int data) {
    QNode* temp = newQNode(data);
    
    if (!q->rear) {
        q->front = q->rear = temp;
        return;
    }

    q->rear->next = temp;
    q->rear = temp;
}

void deQueue(Queue* q) {
    if (!q->front) return;

    QNode* temp = q->front;
    q->front = q->front->next;

    if (!q->front) q->rear = NULL;

    free(temp);
}

int main() {
    Queue* q = createQueue();
    enQueue(q, 10);
    enQueue(q, 20);
    deQueue(q);
    deQueue(q);
    enQueue(q, 30);
    enQueue(q, 40);
    enQueue(q, 50);
    deQueue(q);

    printf("Queue Front: %d\n", q->front ? q->front->data : -1);
    printf("Queue Rear: %d\n", q->rear ? q->rear->data : -1);

    return 0;
}
