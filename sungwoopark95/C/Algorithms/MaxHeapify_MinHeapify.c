#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 1000

// // int array
// void swap(int* a, int* b) {
//     int temp = *a;
//     *a = *b;
//     *b = temp;
// }

// void max_heapify(int* arr, int size, int i) {
//     int largest = i;
//     int l = 2 * i + 1;
//     int r = 2 * i + 2;

//     if (l < size && arr[largest] < arr[l]) {
//         largest = l;
//     }

//     if (r < size && arr[largest] < arr[r]) {
//         largest = r;
//     }

//     if (largest != i) {
//         // swap(&arr[i], &arr[largest]);
//         swap((arr+i), (arr+largest));
//         max_heapify(arr, size, largest);
//     }
// }

// void min_heapify(int* arr, int size, int i) {
//     int smallest = i;
//     int l = 2 * i + 1;
//     int r = 2 * i + 2;

//     if (l < size && arr[l] < arr[smallest]) {
//         smallest = l;
//     }

//     if (r < size && arr[r] < arr[smallest]) {
//         smallest = r;
//     }

//     if (smallest != i) {
//         // swap(&arr[i], &arr[smallest]);
//         swap((arr+i), (arr+smallest));
//         min_heapify(arr, size, smallest);
//     }
// }

// char array
int len(char* s) {
    int length = 0;
    while (s[length] != '\0') {
        length++;
    }
    return length;
}

void swap(char* a, char* b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void max_heapify(char* arr, int size, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < size && arr[largest] < arr[l]) {
        largest = l;
    }

    if (r < size && arr[largest] < arr[r]) {
        largest = r;
    }

    if (largest != i) {
        // swap(&arr[i], &arr[largest]);
        swap((arr+i), (arr+largest)); // pointer 형태의 swap
        max_heapify(arr, size, largest);
    }
}

void min_heapify(char* arr, int size, int i) {
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < size && arr[smallest] > arr[l]) {
        smallest = l;
    }

    if (r < size && arr[smallest] > arr[r]) {
        smallest = r;
    }

    if (smallest != i) {
        // swap(&arr[i], &arr[smallest]);
        swap((arr+i), (arr+smallest)); // 위와 똑같음
        min_heapify(arr, size, smallest);
    }
}


int main(int argc, char* argv[]) {
    // 사용자에게 입력받는 경우
    if (argc < 2) {
        printf("Usage: %s <array string>\n", argv[0]);
        return 1;
    }

    char *input = argv[1];

    // // int heap
    // int *arr = (int*)malloc(MAXSIZE * sizeof(int)); // 동적할당
    // int count = 0;

    // char *token = strtok(input, "[, ]");  // 대괄호와 쉼표, 공백을 구분자로 사용합니다.
    // while (token) {
    //     arr[count++] = atoi(token);  // 문자열을 정수로 변환하고 배열에 저장합니다.
    //     token = strtok(NULL, "[, ]");
    // }

    // // 변환된 정수 배열을 출력합니다.
    // for (int i = 0; i < count; i++) {
    //     printf("%d ", arr[i]);
    // }
    // printf("\n");

    // for (int i=count/2-1;i>=0;i--) {
    //     max_heapify(arr, count, i);
    // }

    // printf("Max heap : ");
    // for (int i = 0; i < count; i++) {
    //     printf("%d ", arr[i]);
    // }
    // printf("\n");

    // // making a min heap
    // for (int i=count/2-1;i>=0;i--) {
    //     min_heapify(arr, count, i);
    // }

    // printf("Min heap : ");
    // for (int i = 0; i < count; i++) {
    //     printf("%d ", arr[i]);
    // }
    // printf("\n");

    // character heap
    // char 출력
    for (int i=0;i<len(input);i++) {
        printf("%c ", input[i]);
    }
    printf("\n");
    for (int i=len(input)/2-1;i>=0;i--) {
        max_heapify(input, len(input), i);
    }

    printf("Max heap : ");
    for (int i = 0; i < len(input); i++) {
        printf("%d ", input[i]);
    }
    printf("\n");

    // making a min heap
    for (int i=len(input)/2-1;i>=0;i--) {
        min_heapify(input, len(input), i);
    }

    printf("Min heap : ");
    for (int i = 0; i < len(input); i++) {
        printf("%d ", input[i]);
    }
    printf("\n");

    return 0;
}

    /* Heap을 완벽하게 구현했다고 생각했을 때의 동작
    int* copied = (int*)malloc(count*sizeof(int));
    for (int i=0;i<count;i++) {
        copied[i] = arr[i];
        for (int j=i/2;j>=0;j--) {
            max_heapify(copied, i, j);
        }

        int is_first = 1;
        for (int j=0;j<i;j++) {
            if (!is_first) { printf(", "); }
            printf("%d", copied[j]);
            is_first = 0;
        }
        printf("\n");
    }
    for (int j=count/2;j>=0;j--) {
        max_heapify(copied, count, j);
    }

    int is_first = 1;
    for (int j=0;j<count;j++) {
        if (!is_first) { printf(", "); }
        printf("%d", copied[j]);
        is_first = 0;
    }
    printf("\n");
    */