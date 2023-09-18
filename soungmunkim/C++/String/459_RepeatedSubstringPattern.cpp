/*
[substring의 반복이 string이 되는지 check]
Given a string s, 
    check if it can be constructed by taking a substring of it 
    and appending multiple copies of the substring together.

Example 1:
Input: s = "abab"
Output: true
Explanation: It is the substring "ab" twice.

Example 2:
Input: s = "aba"
Output: false

Example 3:
Input: s = "abcabcabcabc"
Output: true
Explanation: It is the substring "abc" four times or the substring "abcabc" twice.
*/


#include <iostream>
#include <string>
using namespace std;

bool repeatedSubstringPattern(string s) {
    int s_size = s.length(); // 문자열 길이 저장

    for (int i = 0; i < s_size; i++) {
        // substring 뽑기 (첫번째 char 고정)
        // 예: "abab"에서 "a", "ab", "aba", "abab"
        string temp = s.substr(0, i + 1);
        string check = ""; // 비교할 문자열

        if (temp == s) // substring이 문자열 자체라면 False
            return false;

        int idx = 0; // while loop를 위한 index
        while (idx < s_size) {
            // 문자열 길이가 될 때까지 substring을 check에 추가
            check += temp;

            if (s == check) // substring의 반복으로 원본 문자열이 만들어진다면 True
                return true;

            idx += temp.length(); // 다음 substring의 시작 지점으로 이동
        }
    }

    return false; // 반복되는 substring이 없음
}

int main() {
    cout << repeatedSubstringPattern("abab") << endl;  // 1 (True)
    cout << repeatedSubstringPattern("aba") << endl;   // 0 (False)
    cout << repeatedSubstringPattern("abcabcabcabc") << endl;   // 1 (True)
    return 0;
}


/*----------------------------- 챗지피티 구현 -----------------------------*/
// #include <iostream>
// #include <string>
// using namespace std;

// bool repeatedSubstringPattern(string s) {
//     // 문자열의 길이를 저장합니다.
//     int n = s.length();

//     // 1부터 문자열의 절반 길이까지 반복합니다.
//     for (int i = 1; i <= n / 2; i++) {
//         if (n % i == 0) {  // 현재 i로 문자열 길이를 나누었을 때 나머지가 0이라면
//             bool match = true;  // 일치하는지 체크하기 위한 변수

//             // 문자열의 각 부분을 체크합니다.
//             for (int j = i; j < n; j++) {
//                 if (s[j] != s[j - i]) {
//                     match = false;  // 일치하지 않는 부분이 있다면 false로 설정하고 반복문을 빠져나옵니다.
//                     break;
//                 }
//             }

//             // 모든 부분이 일치한다면 true를 반환합니다.
//             if (match) {
//                 return true;
//             }
//         }
//     }

//     // 가능한 서브스트링으로 전체 문자열을 구성할 수 없다면 false를 반환합니다.
//     return false;
// }

// int main() {
//     cout << repeatedSubstringPattern("abab") << endl;  // 1 (True)
//     cout << repeatedSubstringPattern("aba") << endl;   // 0 (False)
//     cout << repeatedSubstringPattern("abcabcabcabc") << endl;   // 1 (True)
//     return 0;
// }
