#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// ################################### MY CODE - TIME LIMIT ###################################
// 문자열의 유효성 검사 함수
bool isValid(const char* s) {
    int length = strlen(s);
    if (length % 2 == 1) {
        return false;
    }

    char stack[length];
    int stackIndex = 0;
    
    for (int i = 0; i < length; i++) {
        char c = s[i];
        switch(c) {
            case '(':
            case '{':
            case '[':
                stack[stackIndex++] = c;
                break;
            case ')':
                if(stackIndex == 0 || stack[--stackIndex] != '(') return false;
                break;
            case '}':
                if(stackIndex == 0 || stack[--stackIndex] != '{') return false;
                break;
            case ']':
                if(stackIndex == 0 || stack[--stackIndex] != '[') return false;
                break;
        }
    }

    return stackIndex == 0;
}

int longestValidParentheses(const char* s) {
    int length = strlen(s);
    if (length < 2) {
        return 0;
    }

    char substr[length];
    int max_len = 0;
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j <= length; j++) {
            memcpy(substr, &s[i], j-i);
            substr[j-i] = '\0';
            if (isValid(substr)) {
                if (max_len < (j - i)) {
                    max_len = j - i;
                }
            }
        }
    }

    return max_len;
}
// ################################### MY CODE - TIME LIMIT ###################################

// ######################################### ChatGPT #########################################
int longestValidParentheses(const char *s) {
    int left = 0, right = 0, maxlength = 0;
    
    int length = strlen(s);
    
    // 첫 번째 순회: 왼쪽에서 오른쪽으로 문자열을 순회합니다.
    for (int i = 0; i < length; i++) {
        if (s[i] == '(') {
            left++;
        } else {
            right++;
        }
        
        if (left == right) {
            maxlength = (maxlength > 2 * right) ? maxlength : 2 * right;
        } else if (right >= left) {
            left = 0;
            right = 0;
        }
    }
    
    left = 0;
    right = 0;
    
    // 두 번째 순회: 오른쪽에서 왼쪽으로 문자열을 순회합니다.
    for (int i = length - 1; i >= 0; i--) {
        if (s[i] == '(') {
            left++;
        } else {
            right++;
        }
        
        if (left == right) {
            maxlength = (maxlength > 2 * left) ? maxlength : 2 * left;
        } else if (left >= right) {
            left = 0;
            right = 0;
        }
    }
    
    return maxlength;
}
// ######################################### ChatGPT #########################################

int main() {
    char s[1000]; // 적절한 크기로 조절 가능
    fgets(s, sizeof(s), stdin);
    if (s[strlen(s) - 1] == '\n') {
        s[strlen(s) - 1] = '\0';  // 줄바꿈 문자 제거
    }
    printf("%d\n", longestValidParentheses(s));  // 함수 결과 출력
    return 0;
}