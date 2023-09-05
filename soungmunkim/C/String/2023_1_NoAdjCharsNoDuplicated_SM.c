/*
(b) Implement a function bar(s) that returns a string t 
    in which no two adjacent characters are adjacent in s, 
    and s and t are different strings.
    When a character appears in s, t should contain it only once.
    When there is no such string t, it returns an empty string "".
    If there are multiple strings that satisfy the conditions,
    return any of them.
    
    print(bar("abccde"))    #[2,5,1,4,0,3] bdeac
    print(bar("abcde"))     #[2,0,4,1,3] bdeac
    print(bar("abc"))       # ""
    print(bar("abcdcef"))   #[0,2,4,6,1,3,5] bdafce
*/


/*
backtrack 함수 내에서 remaining_chars라는 리스트는 아직 순열에 포함되지 않은 문자들을 저장합니다. 
이를 통해 각 문자가 순열에 한 번만 사용되도록 합니다.

중복된 char은 하나만 포함하게 해야함

*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// 중복된 문자를 제거하는 도우미 함수
void removeDuplicates(char* s, char* result) {
    int index = 0;
    bool found[256] = { false };
    
    // 문자열을 순회하며 중복 문자를 제거
    for (int i = 0; s[i]; i++) {
        char temp = s[i];
        if (!found[temp]) {
            found[temp] = true;
            result[index++] = temp;
        }
    }
    result[index] = '\0'; // 결과 문자열의 끝에 NULL 문자 추가
}

// 현재 순열이 조건을 만족하는지 확인하는 함수
bool isValid(char* s, char* origin_s) {
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] == origin_s[i]) return false; // 같은 위치에 같은 문자가 있는 경우 false
        if (i > 0 && s[i] == origin_s[i-1]) return false; // 이전 위치에 같은 문자가 있는 경우 false
        if (i < strlen(s) - 1 && s[i] == origin_s[i+1]) return false; // 다음 위치에 같은 문자가 있는 경우 false
    }
    return true; // 위의 조건들을 모두 만족하지 않으면 true
}

// 순열을 생성하고 조건을 확인하는 함수
bool permute(char* s, int start, char* origin_s) {
    if (start == strlen(s) - 1) { // 순열이 완성된 경우
        return isValid(s, origin_s);
    }

    for (int i = start; i < strlen(s); i++) {
        // 문자를 바꾸기
        char temp = s[start];
        s[start] = s[i];
        s[i] = temp;

        if (permute(s, start + 1, origin_s)) return true; // 재귀 호출을 통한 순열 생성

        // 문자를 원래대로 돌리기 (백트래킹)
        temp = s[start];
        s[start] = s[i];
        s[i] = temp;
    }

    return false;
}

char* bar(const char* str) {
    static char s[100];
    static char unique_s[100];

    strcpy(s, str); // 문자열 복사
    removeDuplicates(s, unique_s); // 중복 문자 제거

    // 순열 생성
    if (permute(unique_s, 0, s)) {
        return unique_s;
    } else {
        return "";
    }
}

int main() {
    char userInput[100];
    printf("문자열을 입력하세요: "); // 사용자에게 문자열을 입력 받습니다.
    scanf("%99s", userInput); // 최대 99 문자까지 입력 받음 (1 문자는 널 문자를 위한 공간)
    printf("결과: %s\n", bar(userInput)); // 결과 출력

    return 0;
}
