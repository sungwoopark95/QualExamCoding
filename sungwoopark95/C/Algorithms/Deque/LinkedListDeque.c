#include <stdio.h>
#include <stdlib.h>

// Node: 이중 연결 리스트의 기본 단위
typedef struct Node {
    int data;  // 노드에 저장되는 값
    struct Node* prev;  // 이전 노드를 가리키는 포인터
    struct Node* next;  // 다음 노드를 가리키는 포인터
} Node;

Node* create_node(int data, Node* prev, Node* next) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->prev = prev;
    new_node->next = next;
    return new_node;
}

// Deque: 이중 연결 리스트를 사용하여 구현된 Deque 구조체
typedef struct Deque {
    Node* front;  // Deque의 앞쪽 노드를 가리키는 포인터
    Node* rear;   // Deque의 뒷쪽 노드를 가리키는 포인터
    int data_size;  // 현재 Deque에 저장된 데이터의 개수
} Deque;

Deque* create_deque() {
    Deque* dq = (Deque*)malloc(sizeof(Deque));
    dq->front = NULL;
    dq->rear = NULL;
    dq->data_size = 0;
    return dq;
}

// 앞쪽에 데이터 추가
void add_front(Deque* dq, int n) {
    Node* node = create_node(n, NULL, dq->front);
    if (dq->rear == NULL) {  // 첫 번째 노드인 경우
        dq->rear = node;
    } else {
        dq->front->prev = node;  // 기존 front 노드의 prev를 새 노드로 설정
    }
    dq->front = node;  // front 포인터를 새 노드로 업데이트
    dq->data_size++;  // 데이터 개수 증가
}

// 뒷쪽에 데이터 추가
void add_rear(Deque* dq, int n) {
    Node* node = create_node(n, dq->rear, NULL);
    if (dq->front == NULL) {  // 첫 번째 노드인 경우
        dq->front = node;
    } else {
        dq->rear->next = node;  // 기존 rear 노드의 next를 새 노드로 설정
    }
    dq->rear = node;  // rear 포인터를 새 노드로 업데이트
    dq->data_size++;  // 데이터 개수 증가
}

// 앞쪽 데이터 삭제 후 반환
int delete_front(Deque* dq) {
    if (dq->data_size == 0) {
        printf("Deque Empty Error\n");
        exit(1);
    }
    int data = dq->front->data;
    Node* node = dq->front;
    dq->front = dq->front->next;
    if (dq->front) {
        dq->front->prev = NULL;  // front가 NULL이 아니면 prev를 NULL로 설정
    }
    free(node);
    dq->data_size--;  // 데이터 개수 감소
    return data;
}

// 뒷쪽 데이터 삭제 후 반환
int delete_rear(Deque* dq) {
    if (dq->data_size == 0) {
        printf("Deque Empty Error\n");
        exit(1);
    }
    int data = dq->rear->data;
    Node* node = dq->rear;
    dq->rear = dq->rear->prev;
    if (dq->rear) {
        dq->rear->next = NULL;  // rear가 NULL이 아니면 next를 NULL로 설정
    }
    free(node);
    dq->data_size--;  // 데이터 개수 감소
    return data;
}

// Deque 내의 모든 데이터를 출력
void display(Deque* dq) {
    if (dq->data_size == 0) {
        printf("Deque is Empty\n");
    } else {
        Node* node = dq->front;
        while (node) {
            printf("[%d]", node->data);
            node = node->next;  // 다음 노드로 이동
        }
        printf("\n");
    }
}

// Deque의 크기(저장된 데이터 개수)를 반환
int size(Deque* dq) {
    return dq->data_size;
}

// Deque가 비어있는지 확인
int is_empty(Deque* dq) {
    return dq->data_size == 0;
}

// 메인 함수: Deque 구조체를 테스트하는 코드
int main() {
    Deque* deque = create_deque();

    printf("===== addRear x3 =====\n");
    add_rear(deque, 1);
    add_rear(deque, 2);
    add_rear(deque, 3);
    printf(" size : %d\n", size(deque));
    display(deque);

    printf("===== addFront x2 =====\n");
    add_front(deque, 5);
    add_front(deque, 6);
    printf(" size : %d\n", size(deque));
    display(deque);

    printf("===== deleteRear x1 =====\n");
    printf("%d\n", delete_rear(deque));
    printf(" size : %d\n", size(deque));
    display(deque);

    printf("===== deleteFront x3 =====\n");
    printf("%d\n", delete_front(deque));
    printf("%d\n", delete_front(deque));
    printf("%d\n", delete_front(deque));
    printf(" size : %d\n", size(deque));
    display(deque);

    free(deque);

    return 0;
}
