#include <iostream>
#include <vector>

// 바이너리 탐색 함수
int binary_search(const std::vector<int>& lst, int val) {
    // bs: 내부 재귀 함수로 실제 바이너리 탐색을 수행합니다.
    std::function<int(const std::vector<int>&, int, int, int)> bs = 
    [&](const std::vector<int>& lst, int low, int high, int val) -> int {
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
    };

    return bs(lst, 0, lst.size() - 1, val);
}

int main() {
    std::vector<int> list1 = {3, 7, 9, 33, 126, 167};
    int value = 126;
    int result = binary_search(list1, value);

    if (result != -1) {
        std::cout << "값 " << value << "는 리스트의 " << result << "번째 인덱스에 있습니다." << std::endl;
    } else {
        std::cout << "값 " << value << "는 리스트에 존재하지 않습니다." << std::endl;
    }

    return 0;
}
