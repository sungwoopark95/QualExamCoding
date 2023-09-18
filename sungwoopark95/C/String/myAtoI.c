#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

int myAtoi(char* s) {
    // 숫자를 문자로 변환하여 배열에 저장 (0~9까지)
    char dictionary[11] = "0123456789";
    int int_min = INT_MIN;
    int int_max = INT_MAX;

    int len = strlen(s);

    // 숫자가 처음 시작되는 위치를 찾는다.
    int start = -1;
    for (int i = 0; i < len; i++) {
        if (strchr(dictionary, s[i])) {
            start = i;
            break;
        }
    }

    // 결과로 사용될 문자열을 저장할 버퍼를 초기화합니다.
    char resultString[100] = "";

    // sign_flag는 부호 (+ 또는 -)가 이미 문자열에 추가되었는지 여부를 확인하기 위한 변수입니다.
    bool sign_flag = false;

    // 입력 문자열 s를 처음부터 끝까지 순회합니다.
    for (int j = 0; j < len; j++) {
        // 현재 문자가 '+' 또는 '-'인 경우
        if (s[j] == '+' || s[j] == '-') {
            // 현재 위치가 숫자가 시작되는 위치보다 앞이고, 아직 부호가 추가되지 않았다면
            if (j < start && !sign_flag) {
                // 부호를 결과 문자열에 추가하고
                strncat(resultString, &s[j], 1);
                // 부호가 추가되었음을 표시합니다.
                sign_flag = true;
            } else {
                // 그렇지 않은 경우, 문자열 처리를 중단합니다.
                break;
            }
        } 
        // 현재 문자가 공백인 경우
        else if (s[j] == ' ') {
            // 현재 위치가 숫자가 시작되는 위치보다 앞이라면
            if (j < start) {
                // 맨 처음 위치거나 직전 문자도 공백인 경우는 처리를 계속합니다.
                if (j == 0 || s[j-1] == ' ') {
                    continue;
                } else {
                    // 그렇지 않으면 문자열 처리를 중단합니다.
                    break;
                }
            } else {
                // 숫자가 시작된 이후의 공백은 문자열 처리를 중단합니다.
                break;
            }
        } 
        // 현재 문자가 '.'인 경우 문자열 처리를 중단합니다.
        else if (s[j] == '.') {
            break;
        } 
        // 현재 문자가 dictionary에 없는 경우 (즉, 숫자가 아닌 경우) 문자열 처리를 중단합니다.
        else if (!strchr(dictionary, s[j])) {
            break;
        } 
        // 그렇지 않은 경우 (즉, 숫자인 경우)
        else {
            // 숫자를 결과 문자열에 추가합니다.
            strncat(resultString, &s[j], 1);
        }
    }

    // 결과 문자열이 비어있거나, "+" 또는 "-"만 포함하는 경우 0 반환
    if (strlen(resultString) == 0 || strcmp(resultString, "+") == 0 || strcmp(resultString, "-") == 0) {
        return 0;
    }
    long long value = atoll(resultString);
    if (value < int_min) {
        return int_min;
    }
    if (value > int_max) {
        return int_max;
    }
    return (int)value;
}

int main() {
    char* test_cases[] = {"42", "  +  413", "words and 987", "+-419332", 
                          "-4193-3219-22", "   -42", "42.195", "42 195"};
    int num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_cases; i++) {
        printf("%s -> %d\n", test_cases[i], myAtoi(test_cases[i]));
    }
    return 0;
}
