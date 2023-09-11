#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// 최대 힙 구조체 정의
typedef struct {
    int* heap;       // 힙 데이터
    int size;        // 힙의 현재 크기
    int capacity;    // 할당된 메모리 크기
} MaxHeap;

// 힙 초기화
MaxHeap* init_heap() {
    MaxHeap* h = (MaxHeap*)malloc(sizeof(MaxHeap));
    h->heap = NULL;
    h->size = 0;
    h->capacity = 0;
    return h;
}

// 힙에 item이 포함되어 있는지 확인
bool contains(MaxHeap* h, int item) {
    for (int i = 0; i < h->size; i++) {
        if (h->heap[i] == item) {
            return true;
        }
    }
    return false;
}

// 힙의 크기 반환
int getSize(MaxHeap* h) {
    return h->size;
}

// 힙이 비어있는지 확인
bool isEmpty(MaxHeap* h) {
    return h->size == 0;
}

// 최대 힙 정렬
void max_heapify(int* array, int root, int last) {
    int largest = root;
    int left_child = (2 * root) + 1;
    int right_child = (2 * root) + 2;

    // 부모 값보다 큰 자식이 있는지 확인
    if (left_child < last && array[left_child] > array[largest]) {
        largest = left_child;
    }
    if (right_child < last && array[right_child] > array[largest]) {
        largest = right_child;
    }

    // 더 큰 자식이 있다면 교환
    if (largest != root) {
        int temp = array[root];
        array[root] = array[largest];
        array[largest] = temp;

        // 영향을 받은 하위 트리를 재귀적으로 수정
        max_heapify(array, largest, last);
    }
}

// 힙 구성
void build_heap(MaxHeap* h) {
    for (int i = getSize(h) / 2 - 1; i >= 0; i--) {
        max_heapify(h->heap, i, getSize(h));
    }
}

// 힙에 값 추가
void push(MaxHeap* h, int val) {
    if (h->size >= h->capacity) {
        h->capacity = h->capacity == 0 ? 4 : h->capacity * 2;
        h->heap = (int*)realloc(h->heap, h->capacity * sizeof(int));
    }
    h->heap[h->size++] = val;
    build_heap(h);
}

// 힙에서 최댓값 제거 및 반환
int pop(MaxHeap* h) {
    if (isEmpty(h)) {
        return -1;  // 힙이 비어 있음
    }
    int value = h->heap[0];
    h->heap[0] = h->heap[--h->size];
    build_heap(h);
    return value;
}

int main() {
    MaxHeap* h = init_heap();

    push(h, 3);
    push(h, 4);
    push(h, 5);
    push(h, 10);
    push(h, 2);
    push(h, 6);
    push(h, 7);

    printf("Is 3 in the heap? : %s\n", contains(h, 3) ? "true" : "false");
    printf("Is 24 in the heap? : %s\n", contains(h, 24) ? "true" : "false");

    for (int i = 0; i < getSize(h); i++) {
        printf("%d ", h->heap[i]);
    }
    printf("\n");

    printf("Popped: ");
    while (!isEmpty(h)) {
        printf("%d ", pop(h));
    }
    printf("\n");

    free(h->heap);
    free(h);
    return 0;
}
