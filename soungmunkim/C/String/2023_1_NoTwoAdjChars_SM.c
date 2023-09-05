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

(base) soungmunkim@gimseongmun-ui-MacBookPro String % gcc 2023_1_NoTwoAdjChars_SM.c -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test                               
문자열을 입력하세요: abcdcef
"bdacfce"
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test                               
문자열을 입력하세요: abc
""
*/

/*
permutation을 사용하여 여러 다양한 swap들 중 인접하지 않은 새로운 조합 찾는 방식

from itertools import permutations # 이렇게도 사용 가능
for perm_str in permutations(s):
    # 문자열로 변환
    perm_str = ''.join(perm_str
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// 백트래킹을 이용한 재귀 함수. idx[]의 순열 중 조건에 맞는 순열을 찾는 함수
bool backtrack(int idx[], int s_idx[], int start, int len) {
    // 시작 인덱스가 len과 같을 때 (하나의 순열이 완성되었을 때)
    if (start == len) {
        bool positions_match = true;
        // (1) 순열 내 각 위치의 인덱스가 원본 문자열 인덱스와 동일한지 확인
        for (int i = 0; i < len; i++) {
            if (idx[i] == s_idx[i]) {
                positions_match = false;
                break;
            }
        }

        bool adjacent_positions_differ = true;
        // (2) 순열 내 각 위치의 인덱스가 원본 문자열 인덱스의 이웃 인덱스와 동일한지 확인
        for (int i = 1; i < len-1; i++) {
            if (idx[i] == idx[i-1]-1 || idx[i] == idx[i-1]+1 || idx[i] == idx[i+1]-1 || idx[i] == idx[i+1]+1) {
                adjacent_positions_differ = false;
                break;
            }
        }

        // 두 조건을 모두 만족하면 true 반환
        if (positions_match && adjacent_positions_differ) {
            return true;
        }
    }

    // 현재 인덱스부터 마지막 인덱스까지의 요소를 스왑하며 순열 생성
    for (int i = start; i < len; i++) {
        // 현재 시작 인덱스와 i 인덱스의 위치를 스왑
        int temp = idx[start];
        idx[start] = idx[i];
        idx[i] = temp;

        // 재귀 호출을 통해 다음 인덱스부터의 순열 생성
        if (backtrack(idx, s_idx, start+1, len)) {
            return true;
        }

        // 백트래킹: 이전 상태로 복원
        temp = idx[start];
        idx[start] = idx[i];
        idx[i] = temp;
    }

    return false;
}

// 원본 문자열 s를 입력으로 받아 조건에 맞는 새 문자열을 생성하는 함수
char* foo(const char* s) {
    int len = strlen(s);       // 문자열의 길이 계산
    int s_idx[len];            // 원본 문자열의 인덱스 저장을 위한 배열
    int idx[len];              // 인덱스 순열 생성을 위한 배열
    
    // 초기 인덱스 설정
    for (int i = 0; i < len; i++) {
        s_idx[i] = i;
        idx[i] = i;
    }

    // 조건에 맞는 순열이 있는 경우
    if (backtrack(idx, s_idx, 0, len)) {
        char* result = (char*) malloc(len+1);  // 결과 저장을 위한 문자열 메모리 할당
        for (int i = 0; i < len; i++) {
            result[i] = s[idx[i]];             // 새로운 문자열 생성
        }
        result[len] = '\0';                    // 문자열 끝에 널 문자 추가
        return result;
    } else {
        return "";                             // 조건에 맞는 순열이 없는 경우 빈 문자열 반환
    }
}

// 메인 함수
int main() {
    char s[100];   // 입력받을 문자열. 최대 길이는 100으로 가정

    printf("문자열을 입력하세요: ");
    fgets(s, sizeof(s), stdin);   // 사용자로부터 문자열 입력받기

    // fgets는 '\n' (개행 문자)도 문자열에 포함하므로, 이를 제거
    s[strcspn(s, "\n")] = '\0'; 

    // foo 함수 호출 및 결과 출력
    printf("\"%s\"\n", foo(s));
    return 0;
}







/*----------------------------- 홀 짝으로 간단히 처리하는 코드 -------------------------------*/
// #include <stdio.h>
// #include <string.h>

// // 문자열을 처리하는 함수
// void foo(char *s, char *result) {
//     // chars 개수가 4개 이하이면 계속 two adjacent는 생길 수 밖에 없음
//     // <주의> !! 인접이란 character 기준이 아니라 말 그대로 인접한 애들이기때문에 Index 기준으로 생각해야 함 !!
//     if (strlen(s) < 5) {
//         strcpy(result, "");
//     } else {
//         char odds[100] = "", evens[100] = ""; // 적당한 크기의 배열을 선언
//         for (int i = 0; i < strlen(s); i += 2) {
//             strncat(evens, &s[i], 1); // 문자열 결합은 strncat 함수를 사용
//         }
//         for (int i = 1; i < strlen(s); i += 2) {
//             strncat(odds, &s[i], 1);
//         }

//         // printf("%s%s", evens, odds); // 문자열 결합은 %s 로 가능
//         sprintf(result, "%s%s", evens, odds);
//     }
// }

// int main() {
//     char input_str[100];
//     printf("문자열을 입력하세요: ");
//     scanf("%s", input_str);

//     char output_str[200]; // 충분한 크기의 배열 선언
//     foo(input_str, output_str);
//     printf("처리된 문자열: %s\n", output_str);

//     return 0;
// }
