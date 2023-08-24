#include <stdio.h>

// 바이너리 탐색 함수
int binary_search(int lst[], int n, int val) {
    // bs: 내부 재귀 함수로 실제 바이너리 탐색을 수행합니다.
    int bs(int lst[], int low, int high, int val) {
        if (low > high) {
            return -1;
        }
        
        int i = (low + high) / 2;
        
        if (lst[i] == val) {
            return i;
        } else if (lst[i] < val) {
            return bs(lst, i+1, high, val);
        } else {
            return bs(lst, low, i-1, val);
        }
    }

    return bs(lst, 0, n - 1, val);
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
