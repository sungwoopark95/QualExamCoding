#include <stdio.h>

// Swap 함수 정의
void Swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify 함수 정의
void Heapify(int* arr, int root, int last) {
    int largest = root;
    int left_child = (2 * root) + 1;
    int right_child = (2 * root) + 2;

    if (left_child < last && arr[left_child] > arr[largest]) {
        largest = left_child;
    }
    if (right_child < last && arr[right_child] > arr[largest]) {
        largest = right_child;
    }

    if (largest != root) {
        Swap(&arr[root], &arr[largest]);
        Heapify(arr, largest, last);
    }
}

// HeapSort 함수 정의
void HeapSort(int* arr, int len) {
    for (int i = (len / 2) - 1; i >= 0; i--) {
        Heapify(arr, i, len);
    }

    for (int i = len - 1; i > 0; i--) {
        Swap(&arr[0], &arr[i]);
        Heapify(arr, 0, --len);
    }
}

// 새로운 sorted array를 만들고자 하는 경우
void HeapSort_out(int* arr, int len, int* out) {
    for (int i=0;i<len;i++) {
        out[i] = arr[i];
    }

    for (int i = (len / 2) - 1; i >= 0; i--) {
        Heapify(out, i, len);
    }

    for (int i = len - 1; i > 0; i--) {
        Swap(&out[0], &out[i]);
        Heapify(out, 0, --len);
    }
}

int main() {
    int N = 10;
    int test[10] = {25, 48, 5, 43, 34, 28, 3, 50, 21, 38};
    
    printf("Before sort\n");
    int is_start = 1;
    for (int i=0;i<N;i++) { 
        if (!is_start) {
            printf(" ");
        }
        printf("%d", test[i]);
        is_start = 0;
    }
    
    HeapSort(test, N);
    
    printf("After sort\n");
    is_start = 1;
    for (int i=0;i<N;i++) { 
        if (!is_start) {
            printf(" ");
        }
        printf("%d", test[i]);
        is_start = 0;
    }
    printf("\n");
    
    return 0;
}