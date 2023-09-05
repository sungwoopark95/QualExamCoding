/*
[s1 string의 permutation 중 하나라도 s2의 substring이라면 True]
!! window 방법처럼 한문자씩 옮기면서 char 빈도 테이블 업뎃하기 !!
** dict 사용 방법 -> struct 이용

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
#include <string>
#include <map>

using namespace std;

bool checkInclusion(string s1, string s2) {
    map<char, int> s1_counter, s2_counter;  // 문자를 키로, 빈도수를 값으로 가지는 맵을 선언합니다.

    // s1의 각 문자에 대한 빈도수를 계산
    for (char c : s1) {
        s1_counter[c]++;
    }

    // s2의 처음 len(s1) 길이의 문자에 대한 빈도수를 계산
    for (int i = 0; i < s1.size(); i++) {
        s2_counter[s2[i]]++;
    }

    // s2의 나머지 부분을 확인하면서 슬라이딩 윈도우를 이동
    for (int i = s1.size(); i < s2.size(); i++) {
        if (s1_counter == s2_counter) {  // s1의 문자 빈도와 현재 s2의 슬라이딩 윈도우 빈도가 동일한지 확인합니다.
            return true;
        }
        s2_counter[s2[i]]++;  // 새로운 문자를 윈도우에 추가합니다.

        // 가장 오래된 문자를 윈도우에서 제거합니다.
        s2_counter[s2[i - s1.size()]]--;

        // 만약 특정 문자의 빈도가 0이 되면, 그 문자를 빈도 테이블에서 제거합니다.
        if (s2_counter[s2[i - s1.size()]] == 0) {
            s2_counter.erase(s2[i - s1.size()]);
        }
    }

    // 마지막 윈도우에 대한 빈도가 s1의 빈도와 동일한지 다시 확인합니다.
    return s1_counter == s2_counter;
}

int main() {
    string s1 = "ab";
    string s2 = "eidbaooo";

    if (checkInclusion(s1, s2)) {  // checkInclusion 함수를 호출하여 결과를 확인합니다.
        cout << "True" << endl;  // True 출력
    } else {
        cout << "False" << endl;  // False 출력
    }

    return 0;  // 프로그램 종료
}
