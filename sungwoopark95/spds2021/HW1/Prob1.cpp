/*
# P1. 소인수분해
자연수 한 개를 입력으로 받아 이를 소인수분해한 결과를 반환하는 함수 `prime_factorizer`를 작성하라. 
소인수분해한 결과는 (소수, 지수)의 tuple을 담은 list로 반환하며, 리스트 내 tuple의 순서는 소수 크기의 오름차 순으로 정렬하여야 한다.
실행 예시는 다음과 같다.
*/

#include <iostream>
#include <math.h>
#include <vector>
#include <utility>
using namespace std;

bool is_prime(int x) {
    if (x == 1) { 
        return false; 
    }
    for (int i=2;i<=sqrt(x);i++) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

vector<pair<int, int>> prime_factorizer(int num) {
    vector<pair<int, int>> ans;
    for (int i=1;i<=num;i++) {
        if (is_prime(i)) {
            int power = 0;
            while (num % i == 0) {
                power++;
                num = num / i;
            }
            if (power > 0) {
                ans.push_back({i, power});
            }
        }
        if (num == 1) {
            break;
        }
    }
    return ans;
}

int main(int argc, char* argv[]) {
    int x = atoi(argv[1]);
    vector<pair<int, int>> factors = prime_factorizer(x);

    cout << "[";
    for (int i=0;i<factors.size();i++) {
        pair<int, int> p = factors[i];
        if (i < factors.size() - 1) {
            cout << "(" << p.first << ", " << p.second << "), ";
        } else {
            cout << "(" << p.first << ", " << p.second << ")";
        }
        
    }
    cout << "]" << endl;
    
    return 0;
}
