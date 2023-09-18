#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int scoreOfParentheses(char s[]) {
    // 기본 경우
    // 빈 문자열은 점수 0을 가집니다.
    if (strlen(s) == 0) {
        return 0;
    }
    // "()" 문자열은 점수 1을 가집니다.
    if (strcmp(s, "()") == 0) {
        return 1;
    }

    // 괄호의 균형을 추적하고 문자열을 분할하는 데 사용됩니다.
    int balance = 0;
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        char c = s[i];
        // 열린 괄호('(')를 만나면 균형 점수를 1 증가시킵니다.
        if (c == '(') {
            balance++;
        }
        // 닫힌 괄호(')')를 만나면 균형 점수를 1 감소시킵니다.
        else {
            balance--;
        }
        // 괄호의 균형이 맞는 경우 문자열을 분할합니다.
        if (balance == 0) {
            // 괄호의 균형이 문자열의 끝에서 발견되는 경우
            if (i == len - 1) {
                char inside[strlen(s) - 1];
                strncpy(inside, &s[1], i - 1);
                inside[i - 1] = '\0';
                return 2 * scoreOfParentheses(inside);
            }
            // 괄호의 균형이 문자열 중간에서 발견되는 경우
            else {
                char first[i + 2];
                strncpy(first, s, i + 1);
                first[i + 1] = '\0';
                return scoreOfParentheses(first) + scoreOfParentheses(&s[i + 1]);
            }
        }
    }
    return 0;  // 이 부분은 실행되지 않아야 하지만, 컴파일러의 모든 경로에 반환 값이 있어야 한다는 경고를 피하기 위해 추가됩니다.
}

int main() {
    char input[100]; // 임의로 100의 크기를 가진 문자열 배열을 정의합니다. 필요한 경우 크기를 조절하세요.
    
    printf("Balanced parentheses string을 입력하세요: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;  // fgets로 읽은 문자열에서 줄바꿈 문자 제거
    
    printf("해당 문자열의 점수는: %d\n", scoreOfParentheses(input));

    return 0;
}
