#include <stdio.h>

// Merge 함수 정의
void Merge(int* arr, int start, int mid, int last) {
    int k = start;
    int len1 = (mid + 1) - start;
    int len2 = last - mid;
    int sub1[len1];
    int sub2[len2];

    for (int i = 0; i < len1; i++) {
        sub1[i] = arr[start + i];
    }
    for (int j = 0; j < len2; j++) {
        sub2[j] = arr[mid + 1 + j];
    }

    int m = 0, l = 0;
    while (m < len1 && l < len2) {
        if (sub1[m] > sub2[l]) {
            arr[k] = sub2[l++];
        } else {
            arr[k] = sub1[m++];
        }
        k++;
    }

    if (m == len1) {
        for (int x = l; x < len2; x++) {
            arr[k++] = sub2[x];
        }
    } else {
        for (int x = m; x < len1; x++) {
            arr[k++] = sub1[x];
        }
    }
}

// MergeHelp 함수 정의
void MergeHelp(int* arr, int start, int last) {
    if (start == last) return;
    int mid = (start + last) / 2;
    MergeHelp(arr, start, mid);
    MergeHelp(arr, mid + 1, last);

    Merge(arr, start, mid, last);
}

// MergeSort 함수 정의
void MergeSort(int* arr, int len) {
    MergeHelp(arr, 0, len - 1);
}

void MergeSort_out(int* arr, int len, int* out) {
    for (int i=0;i<len;i++) {
        out[i] = arr[i];
    }
    MergeHelp(out, 0, len - 1);
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
    
    MergeSort(test, N);
    
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