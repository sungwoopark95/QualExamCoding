#include <stdio.h>

void Swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void SelectionSort(int* arr, int len) {
    for (int i = 0; i < len; i++) {
        int smallest = i;
        for (int j = i; j < len; j++) {
            if (arr[j] < arr[smallest]) { smallest = j; }
        }
        if (arr[smallest] < arr[i]) {
            Swap(&arr[i], &arr[smallest]);
        }
    }
}

void SelectionSort_out(int* arr, int len, int* out) {
    for (int i=0;i<len;i++) {
        out[i] = arr[i];
    }

    for (int i = 0; i < len; i++) {
        int smallest = i;
        for (int j = i; j < len; j++) {
            if (out[j] < out[smallest]) { smallest = j; }
        }
        if (out[smallest] < out[i]) {
            Swap(&out[i], &out[smallest]);
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
    
    SelectionSort(test, N);
    
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