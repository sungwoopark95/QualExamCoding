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

#include <stdio.h>
#include <string.h>

int repeatedSubstringPattern(char* s) {
    int s_size = strlen(s); // 문자열 길이 저장
    char temp[1001]; // 최대 1000개의 문자로 가정
    char check[2001]; // 최대 2 * 1000으로 가정

    for (int i = 0; i < s_size; i++) {
        strncpy(temp, s, i + 1); // substring 뽑기 (첫번째 char 고정)
        temp[i + 1] = '\0'; // null 문자 추가

        if (!strcmp(temp, s)) // substring이 문자열 자체라면 0 (False)
            return 0;

        check[0] = '\0'; // check 초기화
        int idx = 0; // while loop를 위한 index
        while (idx < s_size) {
            strcat(check, temp); // check에 substring 추가

            if (!strcmp(s, check)) // substring의 반복으로 원본 문자열이 만들어진다면 1 (True)
                return 1;

            idx += strlen(temp); // 다음 substring의 시작 지점으로 이동
        }
    }

    return 0; // 반복되는 substring이 없음
}

int main() {
    printf("%d\n", repeatedSubstringPattern("abab"));  // 1 (True)
    printf("%d\n", repeatedSubstringPattern("aba"));   // 0 (False)
    printf("%d\n", repeatedSubstringPattern("abcabcabcabc"));   // 1 (True)
    return 0;
}

/*-------------------------------- 챗지피티 구현 코드 -----------------------------------*/
// #include <stdio.h>
// #include <stdbool.h>
// #include <string.h>

// bool repeatedSubstringPattern(char* s) {
//     // 문자열의 길이를 구한다.
//     int n = strlen(s);

//     // 1부터 문자열 길이의 절반까지 반복한다.
//     for (int i = 1; i <= n / 2; i++) {
//         if (n % i == 0) {
//             bool match = true;

//             /*
//             반복문 시작: for (int j = i; j < n; j++) 여기서 i는 현재 고려 중인 서브스트링의 길이
//                 j는 문자열 내에서 현재 체크하려는 문자의 위치입니다.

//             문자 비교: if (s[j] != s[j - i]) 
//                 이 부분에서 s[j]는 현재 체크하려는 문자이고, s[j - i]는 그 문자와 비교하려는 서브스트링 내의 문자입니다.

//             로직의 동작 방식: 예를 들어, 문자열 s = "abab"이 있고 현재 i = 2인 경우
//                 j가 2에서 시작합니다. (i의 값과 동일)
//                 첫 번째 반복에서, s[2] (즉, 'a')와 s[2 - 2] (즉, 'a')가 비교 -> 둘은 일치
//                 다음 반복에서, s[3] (즉, 'b')와 s[3 - 2] (즉, 'b')가 비교 -> 이 둘도 일치
//                 문자열의 끝에 도달하므로 서브스트링 "ab"는 문자열을 구성하는 반복 패턴으로 사용 가능
            
//             일치하지 않을 경우: s[j] != s[j - i]의 조건이 참이면, 
//                 해당 서브스트링은 문자열을 반복하여 구성할 수 없다는 것을 의미
//                 따라서 match 변수를 false로 설정하고 break로 반복문을 종료.
//             */

//             // 문자열의 각 부분을 체크한다.
//             for (int j = i; j < n; j++) {
//                 if (s[j] != s[j - i]) {
//                     match = false;
//                     break;
//                 }
//             }
            
//             // 모든 부분이 일치한다면 true를 반환한다.
//             if (match) {
//                 return true;
//             }
//         }
//     }

//     // 가능한 서브스트링으로 전체 문자열을 구성할 수 없다면 false를 반환한다.
//     return false;
// }

// int main() {
//     printf("%d\n", repeatedSubstringPattern("abab")); // 1 (True)
//     printf("%d\n", repeatedSubstringPattern("aba")); // 0 (False)
//     printf("%d\n", repeatedSubstringPattern("abcabcabcabc")); // 1 (True)
//     return 0;
// }
