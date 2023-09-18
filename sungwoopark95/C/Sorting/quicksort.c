#include <stdio.h>

void Swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int Partition(int* arr, int left, int right) {
    int pivot = arr[left];
    int low = left + 1;
    int high = right;

    while (low < high) {
        while (arr[low] < pivot && low < right) { low++; }
        while (arr[high] > pivot && high > left) { high--; }
        if (low < high) { Swap(&arr[low], &arr[high]); }
    }

    if (pivot > arr[high]) { Swap(&arr[left], &arr[high]); }
    return high;
}

void QuickHelp(int* arr, int left, int right) {
    if (left < right) {
        int piv = Partition(arr, left, right);
        QuickHelp(arr, left, piv - 1);
        QuickHelp(arr, piv + 1, right);
    }
}

void QuickSort(int* arr, int len) {
    QuickHelp(arr, 0, len - 1);
}

void QuickSort(int* arr, int len, int* out) {
    for (int i=0;i<len;i++) {
        out[i] = arr[i];
    }
    QuickHelp(out, 0, len - 1);
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
    
    QuickSort(test, N);
    
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