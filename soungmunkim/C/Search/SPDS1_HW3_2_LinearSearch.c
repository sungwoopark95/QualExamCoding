#include <stdio.h>

// lst: 탐색 대상이 되는 배열
// n: 배열의 크기
// val: 찾고자 하는 값
// 반환 값: 찾은 값의 인덱스 (값을 찾지 못한 경우 -1 반환)
int linear_search(int lst[], int n, int val) {
    for (int i = 0; i < n; i++) {
        if (lst[i] == val) {
            return i;  // 값을 찾은 경우 해당 인덱스를 반환
        }
    }
    return -1;  // 전체 배열을 탐색했지만 값을 찾지 못한 경우 -1 반환
}


int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(arr) / sizeof(arr[0]);
    int value = 7;
    
    int result = linear_search(arr, size, value);
    if (result != -1) {
        printf("값 %d는 배열의 %d번째 위치에 있습니다.\n", value, result);
    } else {
        printf("값 %d는 배열에 존재하지 않습니다.\n", value);
    }

    return 0;
}