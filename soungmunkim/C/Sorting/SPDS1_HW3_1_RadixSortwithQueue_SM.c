/*
[Radix sort 구현; Queue 이용함]
Radix Sort는 낮은 자리수부터(일의자리, 십의자리, 등) 비교하여 정렬해 간다는 것을 기본 개념으로 정렬하는 알고리즘이다.
비교 연산을 하지 않으며 정렬 속도가 빠르지만 데이터 전체 크기에 기수 테이블의 크기만한 메모리가 더 필요하다. (공간 복잡도가 높아진다.)
*/

#include <stdio.h>
#include <stdlib.h>

// 연결 리스트의 노드를 정의하는 구조체
typedef struct Node {
    int data;           // 데이터를 저장할 변수
    struct Node* next;  // 다음 노드를 가리키는 포인터
} Node;

// 연결 리스트를 기반으로 한 큐를 정의하는 구조체
typedef struct {
    Node* front;  // 큐의 앞부분 (데이터가 추출되는 위치)
    Node* rear;   // 큐의 뒷부분 (데이터가 추가되는 위치)
} Queue;

// 새로운 큐를 생성하고 초기화하는 함수
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;  // 초기에는 큐가 비어 있으므로 front와 rear 모두 NULL로 설정
    return q;
}

// 큐가 비어 있는지 확인하는 함수
int isEmpty(Queue* q) {
    return q->front == NULL;  // front가 NULL이면 큐는 비어 있음
}

// 큐의 뒤쪽(rear)에 데이터를 추가하는 함수
void enqueue(Queue* q, int value) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = value;
    temp->next = NULL;
    if (q->rear == NULL) {
        // 큐가 비어 있을 경우 front와 rear 모두 새로운 노드를 가리킴
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;  // 현재 rear 노드의 다음 노드를 새로운 노드로 설정
    q->rear = temp;        // rear를 새로운 노드로 업데이트
}

// 큐의 앞쪽(front)에서 데이터를 추출하고 반환하는 함수
int dequeue(Queue* q) {
    if (isEmpty(q)) return -1;  // 큐가 비어 있으면 -1을 반환
    Node* temp = q->front;      // 현재 front 노드를 임시로 저장
    int item = temp->data;      // front 노드의 데이터 저장
    q->front = q->front->next;  // front를 다음 노드로 이동
    if (q->front == NULL)       // front가 NULL이면 큐가 비어 있음을 의미
        q->rear = NULL;         // 따라서 rear도 NULL로 설정
    free(temp);                 // 임시로 저장했던 노드 메모리 해제
    return item;                // 추출한 데이터 반환
}

// 레디스 정렬 함수
void radixSort(int arr[], int n) {
    int i, m = arr[0], exp = 1;
    Queue* bucket[10];  // 0~9까지의 숫자를 저장할 10개의 버킷(큐) 생성
    for (i = 0; i < 10; i++)
        bucket[i] = createQueue();  // 각 버킷 초기화
    for (i = 1; i < n; i++)
        if (arr[i] > m)
            m = arr[i];  // 배열에서 최대값 찾기

    // 최대값의 각 자릿수에 따라 정렬을 수행
    while (m / exp > 0) {
        for (i = 0; i < n; i++)
            enqueue(bucket[(arr[i] / exp) % 10], arr[i]);  // 해당 자릿수의 숫자를 기준으로 버킷에 데이터 추가

        // 각 버킷의 데이터를 순서대로 배열에 복사
        int pos = 0;
        for (i = 0; i < 10; i++) {
            while (!isEmpty(bucket[i])) {
                arr[pos++] = dequeue(bucket[i]);
            }
        }
        exp *= 10;  // 다음 자릿수를 처리하기 위해 exp를 10배로 늘림
    }
    for (i = 0; i < 10; i++)
        free(bucket[i]);  // 사용한 메모리 정리
}

int main() {
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(arr) / sizeof(arr[0]);
    radixSort(arr, n);  // 배열을 레디스 정렬로 정렬
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);  // 정렬된 배열 출력
    return 0;
}

