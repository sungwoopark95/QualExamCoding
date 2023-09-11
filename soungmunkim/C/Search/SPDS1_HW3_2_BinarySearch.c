#include <stdio.h>

// 바이너리 탐색 함수
int binary_search(int lst[], int n, int val) {
    int low = 0, high = n - 1;
    
    while (low <= high) {
        int mid = (low + high) / 2;
        
        if (lst[mid] == val) {
            return mid;
        } else if (lst[mid] < val) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;  // 값을 찾을 수 없으면 -1 반환
}


int main() {
    int list1[] = {3, 7, 9, 33, 126, 167};
    int n = sizeof(list1) / sizeof(list1[0]); // 배열의 크기 계산
    int value = 126;
    int result = binary_search(list1, n, value);

    if (result != -1) {
        printf("값 %d는 배열의 %d번째 인덱스에 있습니다.\n", value, result);
    } else {
        printf("값 %d는 배열에 존재하지 않습니다.\n", value);
    }

    return 0;
}
