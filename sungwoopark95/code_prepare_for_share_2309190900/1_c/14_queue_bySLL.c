#include <stdio.h>
#include <stdlib.h>

// Single Linked List 노드 구조체 정의
typedef struct Node {
    int data;
    struct Node* next;
} Node;

void init_node(Node* node){
    node->next=NULL;
}

// Queue 구조체 정의
typedef struct Queue {
    Node* front; // 큐의 맨 앞 요소
    Node* rear;  // 큐의 맨 뒤 요소
} Queue;

// 큐 초기화 함수
void initializeQueue(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

// 큐가 비어있는지 확인하는 함수
int isEmpty(Queue* queue) {
    return (queue->front == NULL);
}

// 큐에 요소 추가 (enqueue)
void enqueue(Queue* queue, int data) {
    // 새로운 노드 생성
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "메모리 할당 오류\n");
        exit(EXIT_FAILURE);
    }
    init_node(newNode);
    newNode->data = data;
    newNode->next = NULL;

    // 큐가 비어있는 경우
    if (isEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        // 큐의 뒤에 노드 추가
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// 큐에서 요소 제거 (dequeue)
int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        fprintf(stderr, "큐가 비어있습니다.\n");
        exit(EXIT_FAILURE);
    }

    // 큐의 맨 앞 노드 제거
    int data = queue->front->data;
    Node* temp;
    init_node(temp);
    temp = queue->front;
    queue->front = queue->front->next;

    // 제거한 노드 메모리 해제
    free(temp);

    // 만약 큐가 비어있다면 rear도 NULL로 설정
    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    return data;
}

// 큐의 맨 앞 요소 반환 (peek)
int front(Queue* queue) {
    if (isEmpty(queue)) {
        fprintf(stderr, "큐가 비어있습니다.\n");
        exit(EXIT_FAILURE);
    }
    return queue->front->data;
}

// 큐 출력 함수 (디버깅용)
void printQueue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("큐가 비어있습니다.\n");
        return;
    }

    Node* current = queue->front;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    Queue queue;
    initializeQueue(&queue);

    enqueue(&queue, 1);
    enqueue(&queue, 2);
    enqueue(&queue, 3);

    printf("First Element: %d\n", front(&queue));

    printf("Queue: ");
    printQueue(&queue);

    dequeue(&queue);
    printf("After deque: ");
    printQueue(&queue);

    return 0;
}