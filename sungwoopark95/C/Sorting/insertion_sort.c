#include <stdio.h>

// Swap 함수 정의
void Swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// InsertionSort 함수 정의
void InsertionSort(int* arr, int len) {
    for (int i = 1; i < len; i++) {
        for (int j = i; j > 0; j--) {
            if (arr[j-1] > arr[j]) {
                Swap(&arr[j], &arr[j-1]); // 포인터를 전달
            }
        }
    }
}

void InsertionSort_out(int* arr, int len, int* out) {
    for (int i=0;i<len;i++) {
        out[i] = arr[i];
    }
    for (int i = 1; i < len; i++) {
        for (int j = i; j > 0; j--) {
            if (out[j-1] > out[j]) {
                Swap(&out[j], &out[j-1]); // 포인터를 전달
            }
        }
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
    
    InsertionSort(test, N);
    
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