/*
[ 주변 char이 겹치지 않는 또 다른 string 구현하기 ]
Consider a string that contains only lower-case alphabets.
The number of characters in a does not exceed 10.

(a) Implement a function foo(s) that returns a string t 
    in which no two adjacent characters are adjacent in s, and
    t contains exactly the same number of characters as that of s.
    Moreover, when a character appears in s, t should contain it as often as in s.
    When there is no such string t, it returns an empty string "".
    If there are multiple strings that satisfy the conditions, return any of them.

TestCase
print(foo("abccde"))    #[0,2,4,1,3,5] acdbce
print(foo("abcde"))     #[0,2,4,1,3] acebd

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
문자열을 입력하세요: abcdcef
"bdacfce"
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
문자열을 입력하세요: abc
""
*/

/*
permutation을 사용하여 여러 다양한 swap들 중 인접하지 않은 새로운 조합 찾는 방식
*/


#include <iostream>
#include <vector>
#include <string>

// idx 배열을 재배열하여 주어진 조건을 만족하는 순열을 찾는 함수
bool backtrack(std::vector<int>& idx, const std::vector<int>& s_idx, int start) {
    // 시작 인덱스가 idx의 크기와 동일하면 하나의 순열을 완성한 것임
    if (start == idx.size()) {
        bool positions_match = true;
        // 순열 내 각 위치의 인덱스가 원본 문자열의 인덱스와 동일한지 확인
        for (int i = 0; i < idx.size(); i++) {
            if (idx[i] == s_idx[i]) {
                positions_match = false;
                break;
            }
        }

        bool adjacent_positions_differ = true;
        // 순열 내 각 위치의 인덱스가 원본 문자열의 인접한 인덱스와 동일한지 확인
        for (int i = 1; i < idx.size()-1; i++) {
            if (idx[i] == idx[i-1]-1 || idx[i] == idx[i-1]+1 || idx[i] == idx[i+1]-1 || idx[i] == idx[i+1]+1) {
                adjacent_positions_differ = false;
                break;
            }
        }

        // 두 조건을 모두 만족하면 참을 반환
        if (positions_match && adjacent_positions_differ) {
            return true;
        }
    }

    // 현재 인덱스부터 마지막 인덱스까지 순열 생성
    for (int i = start; i < idx.size(); i++) {
        std::swap(idx[start], idx[i]);

        if (backtrack(idx, s_idx, start+1)) {
            return true;
        }

        std::swap(idx[start], idx[i]);  // 백트래킹
    }

    return false;
}

// 주어진 문자열에 대해 조건을 만족하는 다른 문자열을 찾는 함수
std::string foo(const std::string& s) {
    std::vector<int> s_idx(s.size());
    std::vector<int> idx(s.size());

    // 원본 문자열의 인덱스 초기화
    for (int i = 0; i < s.size(); i++) {
        s_idx[i] = i;
        idx[i] = i;
    }

    if (backtrack(idx, s_idx, 0)) {
        std::string result;
        for (int i = 0; i < s.size(); i++) {
            result += s[idx[i]];  // 결과 문자열 생성
        }
        return result;
    } else {
        return "";  // 조건을 만족하는 문자열이 없을 경우 빈 문자열 반환
    }
}

int main() {
    std::string s;
    std::cout << "문자열을 입력하세요: ";
    std::cin >> s;  // 사용자로부터 문자열 입력 받기

    std::cout << "\"" << foo(s) << "\"" << std::endl;  // foo 함수 호출 및 큰 따옴표 안에 결과 출력
    return 0;
}





/*----------------------------- 홀 짝으로 간단히 처리하는 코드 -------------------------------*/
// #include <iostream>
// #include <string>
// using namespace std;

// string foo(string s) {
//     // chars 개수가 4개 이하이면 계속 two adjacent는 생길 수 밖에 없음
//     // <주의> !! 인접이란 character 기준이 아니라 말 그대로 인접한 애들이기때문에 Index 기준으로 생각해야 함 !!
//     if (s.length() < 5) {
//         return "";
//     } else {
//         string odds, evens;
//         for (int i = 0; i < s.length(); i += 2) {
//             evens += s[i];
//         }
//         for (int i = 1; i < s.length(); i += 2) {
//             odds += s[i];
//         }

//         // cout << evens + odds; // 문자열 결합은 + 로 할 수 있음
//         string new_str = evens + odds;
//         // cout << new_str;

//         return new_str;
//     }
// }

// int main() {
//     string input_str;
//     cout << "문자열을 입력하세요: ";
//     cin >> input_str;

//     string output_str = foo(input_str);
//     cout << "처리된 문자열: " << output_str << endl;

//     return 0;
// }
