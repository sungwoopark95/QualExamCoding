/*
[소인수분해: Prime Factorizer]
자연수 한 개를 입력으로 받아 이를 소인수분해한 결과를 반환하는 함수 prime factorizer를 작성하라. 
소인 수분해한 결과는 (소수, 지수)의 tuple을 담은 list로 반환하며, 
리스트 내 tuple의 순서는 소수 크기의 오름차 순으로 정렬하여야 한다.

TestCase1)
>>> prime_factorizer(1)
[]
TestCase2)
>>> prime_factorizer(24)
[(2.3), (3,1)]
TestCase3)
>>> prime_factorizer(30)
[(2,1), (3,1), (5,1)]
*/

#include <iostream>  // c++ 기본 입출력 library
#include <vector>    // 동적 배열을 위한 Library
#include <utility>   // std::pair를 위한 library

/*
std::vector: 동적 크기의 배열. 
    크기가 고정되어 있지 않고 필요에 따라 커지거나 줄어듭니다.
std::pair: 두 개의 요소를 가진 튜플. 
    여기서는 두 개의 int 값을 가집니다.
*/
std::vector<std::pair<int, int> > prime_factorizer(int n){
    // 결과를 저장할 동적 배열을 선언
    std::vector<std::pair<int, int> > ans;
    int i = 2;
    int quotient = n;

    while (quotient > 1){
        int cnt = 0;

        while (quotient % i == 0){
            quotient /= i;
            cnt ++;
        }

        if (cnt > 0){
            ans.push_back(std::make_pair(i, cnt));
        }
        i++;
    }
    return ans;
}

int main(int argc, char* argv[]){
    int num = atoi(argv[1]);

    std::vector<std::pair<int, int> > ans = prime_factorizer(num);
    /*
    ans 컨테이너의 각 요소에 대해 반복하면서 해당 요소의 참조를 
        factor (std::pair<int, int> type인)변수에 할당
    이로 인해 순회 중에는 ans의 실제 요소 값을 변경할 수 없으며, 
        각 요소의 복사본을 생성하지 않아 성능 저하도 방지
    
    // ans의 각 요소에 대해 반복하면서 출력합니다.
    for (const auto &factor : ans) {
        // factor.first는 소수, factor.second는 그 소수의 지수입니다.
        std::cout << "Prime: " << factor.first << ", Count: " << factor.second << std::endl;
    }
    */
    std::cout << "[";
    // size_t:  부호 없는 정수 타입이므로 항상 0 또는 양수 값
    // 배열의 최대 크기를 나타낼 수 있을 만큼 충분히 큰 값으로 정의 (반환된 크기와 타입이 일치함)
    for (size_t i = 0; i < ans.size(); i++) {
        std::cout << "(" << ans[i].first << ", " << ans[i].second << ")";
        if (i != ans.size() - 1)  // 마지막 요소가 아니라면 쉼표를 출력
            std::cout << ", ";
    }
    std::cout << "]" << std::endl;
    return 0;
}