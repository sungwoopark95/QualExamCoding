#include <iostream>
#include <vector>

// 정렬된 벡터에서 주어진 값을 선형 탐색하는 함수
bool linear_search_sorted(const std::vector<int>& lst, int val) {
    for (int i : lst) { // 벡터의 모든 원소에 대해서
        if (i == val) { // 벡터의 값과 주어진 값을 비교
            return true; // 주어진 값이 벡터에 있으면 true 반환
        }
        if (i > val) { // 주어진 값보다 큰 값을 발견하면
            return false; // 주어진 값은 벡터에 없다고 판단하고 false 반환
        }
    }
    return false; // 벡터의 끝까지 탐색했는데 주어진 값이 없으면 false 반환
}

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // 검색할 정렬된 벡터
    int value = 7; // 찾고자 하는 값
    
    bool result = linear_search_sorted(vec, value); // 선형 탐색 함수 호출
    if (result) {
        std::cout << "값 " << value << "는 벡터에 존재합니다." << std::endl;
    } else {
        std::cout << "값 " << value << "는 벡터에 존재하지 않습니다." << std::endl;
    }

    return 0;
}

