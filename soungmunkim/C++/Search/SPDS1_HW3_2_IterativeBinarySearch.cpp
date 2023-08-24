#include <iostream>
#include <vector>

// 이진 탐색 함수 (반복 버전)
int binary_search_iter(const std::vector<int>& lst, int val) {
    int low = 0;
    int high = lst.size() - 1;

    // low가 high보다 작거나 같은 동안 반복
    while (low <= high) {
        int i = (high + low) / 2; // 중간 인덱스 계산
        if (lst[i] == val) {
            return i; // 찾는 값이 있으면 해당 인덱스 반환
        } else if (lst[i] < val) {
            low = i + 1; // 중간 값이 찾는 값보다 작으면 왼쪽 부분 배열을 버리고 오른쪽 부분 배열 탐색
        } else {
            high = i - 1; // 중간 값이 찾는 값보다 크면 오른쪽 부분 배열을 버리고 왼쪽 부분 배열 탐색
        }
    }
    return -1; // 찾는 값이 없으면 -1 반환
}

int main() {
    std::vector<int> list1 = {3, 7, 9, 33, 126, 167};
    int value = 126;
    int result = binary_search_iter(list1, value);

    if (result != -1) {
        std::cout << "값 " << value << "는 리스트의 " << result << "번째 인덱스에 있습니다." << std::endl;
    } else {
        std::cout << "값 " << value << "는 리스트에 존재하지 않습니다." << std::endl;
    }

    return 0;
}
