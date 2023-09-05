/*
[s1 string의 permutation 중 하나라도 s2의 substring이라면 True]
!! string이 길면 엄청 오래걸림 !!
Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.

In other words, return true if one of s1's permutations is the substring of s2.

Example 1:

Input: s1 = "ab", s2 = "eidbaooo"
Output: true
Explanation: s2 contains one permutation of s1 ("ba").
Example 2:

Input: s1 = "ab", s2 = "eidboaoo"
Output: false
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 순열 생성 함수: 주어진 문자열 s에 대해 가능한 모든 순열을 생성하여 permutation_lst에 저장
void str_perm(string s, int start, vector<string>& permutation_lst) {
    // 기저 사례: start가 문자열 s의 크기와 같을 때, 즉 모든 문자를 사용했을 때
    if (start == s.size()) {
        // 현재 문자열 s를 permutation_lst에 추가
        permutation_lst.push_back(s);
        return;
    }
    for (int i = start; i < s.size(); i++) {
        // s의 start 위치와 i 위치의 문자를 교환 (스왑)
        swap(s[start], s[i]);
        // 재귀 호출: start 위치를 제외하고 나머지 부분에 대해 순열 생성
        str_perm(s, start + 1, permutation_lst);
        // 백트래킹: 원래 상태로 문자열 s를 복구
        swap(s[start], s[i]);
    }
}

// s2 문자열 내에 s1의 순열 중 하나가 포함되어 있는지 검사
bool checkInclusion(string s1, string s2) {
    // s1의 모든 가능한 순열을 저장할 벡터
    vector<string> permutations;
    // s1의 모든 순열을 생성
    str_perm(s1, 0, permutations);
    // 생성된 각 순열에 대해
    for (string per : permutations) {
        // s2 내에 해당 순열이 포함되어 있는지 검사
        if (s2.find(per) != string::npos) {
            // s2 내에 순열이 있으면 true 반환
            return true;
        }
    }
    // 모든 순열에 대해 s2 내에 없으면 false 반환
    return false;
}

int main() {
    // 테스트 케이스
    string s1 = "abc";
    string s2 = "eidbaooo";

    // checkInclusion 함수를 호출하여 결과 출력
    if (checkInclusion(s1, s2)) {
        cout << "True" << endl;
    } else {
        cout << "False" << endl;
    }

    return 0;
}
