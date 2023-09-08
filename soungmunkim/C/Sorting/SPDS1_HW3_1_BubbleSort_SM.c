/*
[Bubble sort 구현하기]
Bubble Sort: 인접한 두 원소의 순서가 바뀌어 있을 때 (앞의 원소가 뒤의 원소보다 클 때) 서로 swap하면서 정렬하는 알고리즘
정수로 이루어진 리스트(list)를 변수(argument)로 받아 버블 정렬할 때, swap이 일어나는 횟수를 리턴하는 함수를 작성하시오.

*/
#include<stdio.h>
// swap은 무조건 주소값으로 접근! 함수 끝나도 바꾼 값 유지 
// int &a처럼 함수 인자를 바로 넘겨주는 것은 C++에서만 가능
void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

// int* arr사용해도 됨! (array가 pointer 자체)
// 오른차순 정렬
void bubble_sort(int arr[], int n){
    int i, j;
    for (i=0; i<n; i++){
        for (j=0; j<n-i-1; j++){
            if (arr[j] > arr[j+1])
                // swap(arr+j, arr+j+1);
                swap(&arr[j], &arr[j+1]); // 해당 값의 주소값을 넣어야 pointer가 받을 수 있음 
                
        }
    }
}

// /*------------- str array sorting하기 ------------*/
// // 오른차순 정렬
// void bubbleSort(char** arr, int n) {
//     for (int i = 0; i < n-1; i++) {
//         for (int j = 0; j < n-i-1; j++) {
//             // strcmp는 두 문자열을 비교하며, 첫 번째 문자열이 두 번째 문자열보다 사전적으로 크면 양의 값을 반환합니다.
//             if (strcmp(arr[j], arr[j+1]) > 0) {
//                 // 두 문자열 포인터 교환
//                 char* temp = arr[j];
//                 arr[j] = arr[j+1];
//                 arr[j+1] = temp;
//             }
//         }
//     }
// }

// // 오른차순 정렬
// void bubbleSort(char arr[][100], int n) {
//     for (int i = 0; i < n-1; i++) {
//         for (int j = 0; j < n-i-1; j++) {
//             // strcmp는 두 문자열을 비교하며, 첫 번째 문자열이 두 번째 문자열보다 사전적으로 크면 양의 값을 반환합니다.
//             if (strcmp(arr[j], arr[j+1]) > 0) {
//                 // 두 문자열 직접 교환
//                 char temp[100]; // 임시 문자열 변수
//                 strcpy(temp, arr[j]);       // temp에 arr[j] 복사
//                 strcpy(arr[j], arr[j+1]);   // arr[j]에 arr[j+1] 복사
//                 strcpy(arr[j+1], temp);     // arr[j+1]에 temp 복사
//             }
//         }
//     }
// }


// // 내림차순 정렬
// void bubble_sort(int* arr, int length) {
//     for (int i=0;i<length;i++) {
//         for (int j=0;j<length-i-1;j++) {
//             if (arr[j] < arr[j+1]) {
//                 swap(arr[j], arr[j+1]);
//             }
//         }
//     }
// }

int main() {
    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    bubble_sort(arr, n);

    printf("Sorted array: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}

/*사용자에게 input으로 sorting 하고 싶은 인자를 받았을 때

int main() {
    char input[1000];  // 사용자 입력을 저장할 문자열 배열
    int arr[1000];     // 숫자들을 저장할 배열
    int n = 0;         // 배열의 크기를 저장할 변수

    // 사용자로부터 정렬할 숫자들을 입력받음
    printf("정렬할 숫자들을 공백으로 구분하여 입력해주세요:\n");
    fgets(input, sizeof(input), stdin);

    // 입력받은 문자열을 공백을 기준으로 나누어 숫자로 변환하고 배열에 저장
    char *token = strtok(input, " ");
    while (token) {
        arr[n++] = atoi(token);  // 문자열을 숫자로 변환하여 배열에 저장
        token = strtok(NULL, " ");
    }

    // 배열을 bubble_sort 함수를 사용하여 정렬
    bubble_sort(arr, n);

    // 정렬된 배열 출력
    printf("정렬된 배열: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
*/


/* list형태로 사용자에게 input으로 받았을 때
#define MAX_SIZE 100
int main() {
    char input[MAX_SIZE];
    int arr[MAX_SIZE];
    int n = 0; // 배열의 크기

    printf("Enter the list of numbers in the format [a,b,c,...]: ");
    fgets(input, sizeof(input), stdin);

    // 입력된 문자열 처리
    char* token = strtok(input, "[,]"); // '[' 또는 ',' 또는 ']'를 기준으로 문자열 분리
    while (token) {
        arr[n++] = atoi(token); // 문자열을 숫자로 변환하여 배열에 저장
        token = strtok(NULL, "[,]");
    }

    bubble_sort(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
*/