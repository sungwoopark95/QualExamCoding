#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// 이진 트리의 노드를 표현하기 위한 구조체 정의
typedef struct Node {
    int data;               // 노드의 값
    struct Node* left;     // 왼쪽 자식 노드의 포인터
    struct Node* right;    // 오른쪽 자식 노드의 포인터
} Node;

// 큐의 노드를 표현하기 위한 구조체 정의
typedef struct QueueNode {
    Node* data;            // 큐 노드의 데이터 (트리 노드의 포인터)
    struct QueueNode* next;// 다음 큐 노드를 가리키는 포인터
} QueueNode;

// 큐를 표현하기 위한 구조체 정의
typedef struct {
    QueueNode* front;      // 큐의 앞쪽을 가리키는 포인터
    QueueNode* rear;       // 큐의 뒷쪽을 가리키는 포인터
    int size;              // 큐의 크기
} Queue;

// 큐를 초기화하는 함수
void init(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}

// 큐가 비어있는지 확인하는 함수
bool isEmpty(Queue* q) {
    return q->size == 0;
}

// 큐에 노드를 추가하는 함수
void enqueue(Queue* q, Node* data) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->data = data;
    newNode->next = NULL;

    if (isEmpty(q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }

    q->size++;
}

// 큐에서 노드를 제거하고 그 값을 반환하는 함수
Node* dequeue(Queue* q) {
    if (isEmpty(q)) return NULL;

    QueueNode* temp = q->front;
    Node* data = temp->data;
    q->front = q->front->next;

    free(temp);
    q->size--;

    return data;
}

// 새로운 이진 트리 노드를 생성하는 함수
Node* newNode(int data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

// 이진 트리를 레벨별로 인쇄하는 함수
void printLevelOrder(Node* root) {
    if (root == NULL) return;

    Queue q;
    init(&q);

    enqueue(&q, root);

    while (!isEmpty(&q)) {
        int nodeCount = q.size;
        while (nodeCount > 0) {
            Node* node = dequeue(&q);
            printf("%d ", node->data);

            if (node->left) enqueue(&q, node->left);
            if (node->right) enqueue(&q, node->right);

            nodeCount--;
        }
        printf("\n");
    }
}

int main() {
    Node* root = newNode(1);       // 루트 노드 생성
    root->left = newNode(2);      // 왼쪽 자식 노드 생성
    root->right = newNode(3);     // 오른쪽 자식 노드 생성
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);
    
    printLevelOrder(root);        // 레벨별로 트리 인쇄
    return 0;
}
