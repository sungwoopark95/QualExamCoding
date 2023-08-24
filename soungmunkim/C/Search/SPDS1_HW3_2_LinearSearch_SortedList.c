#include <stdio.h>
#include <stdbool.h>

// 정렬된 배열에서 주어진 값을 선형 탐색하는 함수
bool linear_search_sorted(int lst[], int n, int val) {
    for (int i = 0; i < n; i++) {
        if (lst[i] == val) { // 배열의 값과 주어진 값을 비교
            return true; // 주어진 값이 배열에 있으면 true 반환
        }
        if (lst[i] > val) { // 주어진 값보다 큰 값을 발견하면
            return false; // 주어진 값은 배열에 없다고 판단하고 false 반환
        }
    }
    return false; // 배열의 끝까지 탐색했는데 주어진 값이 없으면 false 반환
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // 검색할 정렬된 배열
    int size = sizeof(arr) / sizeof(arr[0]);    // 배열의 크기 계산
    int value = 7;                              // 찾고자 하는 값
    
    bool result = linear_search_sorted(arr, size, value); // 선형 탐색 함수 호출
    if (result) {
        printf("값 %d는 배열에 존재합니다.\n", value);
    } else {
        printf("값 %d는 배열에 존재하지 않습니다.\n", value);
    }

    return 0;
}
