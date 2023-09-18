/*
[Isomorphic string]
s가 서로 반대되는 char로 바꼈을때 t로 된다면 iosmorphic string임
ex) egg = add

Example 1:
Input: s = "egg", t = "add"
Output: true

Example 2:
Input: s = "foo", t = "bar"
Output: false

Example 3:
Input: s = "paper", t = "title"
Output: true
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 256  // 확장 ASCII 코드까지 고려

// 두 문자열이 isomorphic인지 검사하는 함수
bool isIosmorphic(char *s, char *t) {
    int s_len = strlen(s);  // s의 길이를 저장
    int t_len = strlen(t);  // t의 길이를 저장

    // s와 t의 길이가 다르면 false 반환
    if (s_len != t_len) {
        return false;
    }

    char mapping_s_to_t[ALPHABET_SIZE] = {0};  // s의 문자를 t의 문자로 변환하기 위한 매핑
    char mapping_t_to_s[ALPHABET_SIZE] = {0};  // t의 문자를 s의 문자로 변환하기 위한 매핑

    // s와 t의 문자를 순회하며 매핑 생성
    for (int i = 0; i < s_len; i++) {
        // s의 문자에 대한 t의 문자 매핑이 설정되지 않았으면 설정
        if (!mapping_s_to_t[s[i]]) {
            mapping_s_to_t[s[i]] = t[i];
        } 
        // 이미 매핑이 설정되어 있고, 현재 t의 문자와 다르면 false 반환
        else if (mapping_s_to_t[s[i]] != t[i]) {
            return false;
        }

        // t의 문자에 대한 s의 문자 매핑 설정
        if (!mapping_t_to_s[t[i]]) {
            mapping_t_to_s[t[i]] = s[i];
        } 
        // 이미 매핑이 설정되어 있고, 현재 s의 문자와 다르면 false 반환
        else if (mapping_t_to_s[t[i]] != s[i]) {
            return false;
        }
    }

    char compare1[s_len + 1];  // s를 t로 변환한 결과를 저장할 문자열
    char compare2[t_len + 1];  // t를 s로 변환한 결과를 저장할 문자열

    // s와 t의 문자를 순회하며 변환된 문자열 생성
    for (int i = 0; i < s_len; i++) {
        compare1[i] = mapping_s_to_t[s[i]];
        compare2[i] = mapping_t_to_s[t[i]];
    }
    compare1[s_len] = '\0';  // 문자열 종료 문자 설정
    compare2[t_len] = '\0';

    // 변환된 문자열이 원래 문자열과 같은지 확인 후 결과 반환
    if (strcmp(compare1, t) == 0 && strcmp(compare2, s) == 0) {
        return true;
    }
    return false;
}


int main() {
    // 예제 데이터
    char* examples_s[] = {"egg", "foo", "paper"};
    char* examples_t[] = {"add", "bar", "title"};
    int numExamples = sizeof(examples_s) / sizeof(examples_s[0]);

    for(int i = 0; i < numExamples; i++) {
        printf("Example %d:\n", i+1);
        printf("Input: s = \"%s\", t = \"%s\"\n", examples_s[i], examples_t[i]);
        bool result = isIosmorphic(examples_s[i], examples_t[i]);
        printf("Output: %s\n\n", result ? "true" : "false");
    }

    return 0;
}