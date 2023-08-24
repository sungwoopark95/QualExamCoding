#include <iostream>
#include <vector>

// lst: 탐색 대상이 되는 벡터
// val: 찾고자 하는 값
// 반환 값: 찾은 값의 인덱스 (값을 찾지 못한 경우 -1 반환)
int linear_search(const std::vector<int>& lst, int val) {
    int n = lst.size();
    for (int i = 0; i < n; i++) {
        if (lst[i] == val) {
            return i;  // 값을 찾은 경우 해당 인덱스를 반환
        }
    }
    return -1;  // 전체 벡터를 탐색했지만 값을 찾지 못한 경우 -1 반환
}


int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int value = 7;
    
    int result = linear_search(vec, value);
    if (result != -1) {
        std::cout << "값 " << value << "는 벡터의 " << result << "번째 위치에 있습니다." << std::endl;
    } else {
        std::cout << "값 " << value << "는 벡터에 존재하지 않습니다." << std::endl;
    }

    return 0;
}