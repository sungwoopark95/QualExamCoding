/*
[유효한 parentheses 점수 계산하기]

valid한 stack인지 체크하는 함수
    -> valid 하지 않으면 -1 return
    
valid parethese일 경우 score = 1
A + B 형태일 경우 score + score
(A) 같은 형태일 경우 score * 2

stack에 각 점수를 넣고 열림도 0으로 stack에 표시하며 문제 품

Example 1:
Input: s = "()"
Output: 1

Example 2:
Input: s = "(())"
Output: 2

Example 3:
Input: s = "()()"
Output: 2

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
String: (), Score: 1
String: (()), Score: 2
String: [], Score: 1
String: {}, Score: 1
String: ([]), Score: 2
String: (())[]{}, Score: 4
String: ((())[]{}[]()), Score: 12
*/


#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 1000  // 스택의 최대 크기를 정의

// 문자용 스택 구조체 정의
typedef struct {
    char arr[MAX_SIZE];
    int top;
} StackChar;

// 숫자용 스택 구조체 정의
typedef struct {
    int arr[MAX_SIZE];
    int top;
} StackInt;

// 문자용 스택 초기화 함수
void init_char(StackChar *s) {
    s->top = -1;
}

// 숫자용 스택 초기화 함수
void init_int(StackInt *s) {
    s->top = -1;
}

// 문자용 스택에 값 추가 함수
void push_char(StackChar *s, char value) {
    s->arr[++s->top] = value;
}

// 숫자용 스택에 값 추가 함수
void push_int(StackInt *s, int value) {
    s->arr[++s->top] = value;
}

// 문자용 스택에서 값 꺼내는 함수
char pop_char(StackChar *s) {
    return s->arr[s->top--];
}

// 숫자용 스택에서 값 꺼내는 함수
int pop_int(StackInt *s) {
    return s->arr[s->top--];
}

// 문자용 스택의 최상위 값을 조회하는 함수
char top_char(StackChar *s) {
    return s->arr[s->top];
}

// 숫자용 스택의 최상위 값을 조회하는 함수
int top_int(StackInt *s) {
    return s->arr[s->top];
}

// 문자용 스택이 비어있는지 확인하는 함수
bool empty_char(StackChar *s) {
    return s->top == -1;
}

// 숫자용 스택이 비어있는지 확인하는 함수
bool empty_int(StackInt *s) {
    return s->top == -1;
}

// 괄호 문자열이 유효한지 확인하는 함수
bool is_valid(const char *s) {
    StackChar st;
    init_char(&st); // 스택 초기화

    for (int i = 0; i < strlen(s); i++) {
        char ch = s[i];
        if (ch == '(' || ch == '[' || ch == '{') {
            push_char(&st, ch); // 여는 괄호면 스택에 추가
        } else {
            if (empty_char(&st)) return false; // 스택이 비어있으면 유효하지 않음
            char open_bracket = pop_char(&st); // 최상위 괄호 꺼내기
            if (ch == ')' && open_bracket != '(') return false;
            if (ch == ']' && open_bracket != '[') return false;
            if (ch == '}' && open_bracket != '{') return false;
        }
    }

    return empty_char(&st); // 스택이 비어있으면 유효
}

// 괄호 문자열의 점수를 계산하는 함수
int score(const char *s) {
    if (!is_valid(s)) return -1; // 유효하지 않으면 -1 반환

    StackInt st;
    init_int(&st); // 스택 초기화

    for (int i = 0; i < strlen(s); i++) {
        char ch = s[i];
        if (ch == '(' || ch == '[' || ch == '{') {
            push_int(&st, 0); // 여는 괄호는 0으로 표시
        } else {
            if (top_int(&st) == 0) {
                pop_int(&st); // 최상위 0 제거
                push_int(&st, 1); // 점수 1 추가
            } else {
                int curr = 0;
                while (top_int(&st) != 0) {
                    curr += pop_int(&st); // 스택의 값들을 더함
                }
                pop_int(&st); // 최상위 0 제거
                push_int(&st, curr * 2); // 괄호 내부의 점수 * 2 추가
            }
        }
    }

    int result = 0;
    while (!empty_int(&st)) {
        result += pop_int(&st); // 스택의 모든 점수를 더함
    }
    return result;
}

int main() {
    const char *test_strs[] = {
        "()",
        "(())",
        "[]",
        "{}",
        "([])",
        "(())[]{}",
        "((())[]{}[]())"
    };

    int test_count = sizeof(test_strs) / sizeof(test_strs[0]);

    for (int i = 0; i < test_count; i++) {
        printf("String: %s, Score: %d\n", test_strs[i], score(test_strs[i])); // 점수 출력
    }

    return 0;
}
