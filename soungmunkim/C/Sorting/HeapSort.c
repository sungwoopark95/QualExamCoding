#include <stdio.h>

// 배열을 최대 힙 구조로 만드는 함수
void heapify(int *arr, int size) {
    for (int i = 1; i < size; ++i) {
        int child = i;
        do {
            // 자식 노드가 부모 노드보다 크면 교환
            int root = (child - 1) / 2;
            if (arr[root] < arr[child]) {
                // 부모 노드와 자식 노드의 값을 교환
                int temp = arr[root];
                arr[root] = arr[child];
                arr[child] = temp;
            }
            child = root;
        } while (child != 0); // 최상단 노드까지 점검
    }
}

// 최상단 노드와 최하단 노드를 교체하는 함수
void heap(int *arr, int *size) {
    int temp = arr[0];
    arr[0] = arr[*size - 1];
    arr[*size - 1] = temp;
    --(*size);
}

int main() {

    int size = 10;
    // 무작위 배열
    int arr[10] = {5, 6, 10, 4, 3, 8, 7, 1, 2, 9};
    printf("원래 배열: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 힙 정렬
    printf("정렬 후 배열: ");
    for (int i = 0; i < 10; ++i) {
        heapify(arr, size); // 배열을 최대 힙 구조로 만듦
        heap(arr, &size);   // 최대 힙에서 최대값을 빼고 배열 크기를 줄임
    }

    // 정렬된 배열 출력
    for (int i = 0; i < 10; ++i) {
        printf("%d ", arr[i]);
    }

    return 0;
}
