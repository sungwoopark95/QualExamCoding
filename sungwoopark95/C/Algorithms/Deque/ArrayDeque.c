#include <stdio.h>
#include <stdbool.h>

#define MAX_DEQUE_SIZE 10  // 덱의 최대 크기 설정

typedef struct {
    int data[MAX_DEQUE_SIZE];  // 데이터 저장을 위한 배열
    int front;  // 첫 번째 요소 앞의 인덱스
    int rear;   // 마지막 요소의 인덱스
} Deque;

// 덱을 초기화하는 함수
void init(Deque* dq) {
    dq->front = 0;  // 초기값 설정
    dq->rear = 0;
}

// 덱이 비어 있는지 확인하는 함수
bool isEmpty(Deque* dq) {
    return dq->front == dq->rear;
}

// 덱이 꽉 차 있는지 확인하는 함수
bool isFull(Deque* dq) {
    return dq->front == (dq->rear + 1) % MAX_DEQUE_SIZE;
}

// 덱의 앞에 항목을 추가하는 함수
void addFront(Deque* dq, int n) {
    if (isFull(dq)) {
        printf("Deque Full Error\n");
        return;
    }
    dq->data[dq->front] = n;
    dq->front = (dq->front - 1 + MAX_DEQUE_SIZE) % MAX_DEQUE_SIZE;  // front가 0 이하일 경우, max 인덱스로 순회
}

// 덱의 뒤에 항목을 추가하는 함수
void addRear(Deque* dq, int n) {
    if (isFull(dq)) {
        printf("Deque Full Error\n");
        return;
    }
    dq->rear = (dq->rear + 1) % MAX_DEQUE_SIZE;  // rear가 최대값을 넘어가면 0번째 인덱스로 순회
    dq->data[dq->rear] = n;
}

// 덱의 앞 항목을 제거하는 함수
int deleteFront(Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque Empty Error\n");
        return -1;  // 에러 시 -1 반환
    }
    dq->front = (dq->front + 1) % MAX_DEQUE_SIZE;  // front가 최대값을 넘어가면 0번째 인덱스로 순회
    return dq->data[dq->front];
}

// 덱의 뒤 항목을 제거하는 함수
int deleteRear(Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque Empty Error\n");
        return -1;  // 에러 시 -1 반환
    }
    int temp = dq->data[dq->rear];
    dq->rear = (dq->rear - 1 + MAX_DEQUE_SIZE) % MAX_DEQUE_SIZE;  // rear가 0 이하일 경우, max 인덱스로 순회
    return temp;
}

// 덱의 크기를 반환하는 함수
int size(Deque* dq) {
    if (dq->front <= dq->rear) {
        return dq->rear - dq->front;
    } else {
        return (dq->rear + MAX_DEQUE_SIZE) - dq->front;
    }
}


// 덱의 내용을 출력하는 함수
void display(Deque* dq) {
    for (int i = dq->front + 1; i <= dq->front + size(dq); i++) {
        printf("[%d]", dq->data[i % MAX_DEQUE_SIZE]);
    }
    printf("\n");
}

// 원형 배열의 front와 rear 정보를 출력하기 위한 함수
void displayDetail(Deque* dq) {
    printf("DEQUE: ");
    for (int i = dq->front + 1; i <= dq->front + size(dq); i++) {
        printf("[%d]", dq->data[i % MAX_DEQUE_SIZE]);
    }
    printf("\n");

    printf("index: ");
    for (int i = dq->front + 1; i <= dq->front + size(dq); i++) {
        printf("%d ", i % MAX_DEQUE_SIZE);
    }
    printf("\n");

    printf("front: %d, rear: %d\n", dq->front, dq->rear);
}

// 메인 함수
int main() {
    Deque dq;
    init(&dq);

    printf("===== addRear x3 =====\n");
    addRear(&dq, 1);
    addRear(&dq, 2);
    addRear(&dq, 3);
    printf(" size: %d\n", size(&dq));
    displayDetail(&dq);

    printf("===== addFront x2 =====\n");
    addFront(&dq, 5);
    addFront(&dq, 6);
    printf(" size: %d\n", size(&dq));
    displayDetail(&dq);

    printf("===== deleteRear x1 =====\n");
    deleteRear(&dq);
    printf(" size: %d\n", size(&dq));
    displayDetail(&dq);

    printf("===== deleteFront x3 =====\n");
    deleteFront(&dq);
    deleteFront(&dq);
    deleteFront(&dq);
    printf(" size: %d\n", size(&dq));
    displayDetail(&dq);

    return 0;
}
