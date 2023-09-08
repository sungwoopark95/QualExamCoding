/*
[유효한 괄호 찾기]
‘(‘, ‘)’, ‘{‘, ‘}’, ‘[‘, ‘]’으로 구성된 String을 Input으로 받고, 
이 String이 아래 규칙에 의해 유효한지를 판단하여 True/False를 return하는 함수를 작성하여라.

<조건>
(1) 괄호가 열렸다면 같은 타입의 괄호에 의해 닫혀야 한다.
(2) 적절한 순서로 괄호가 배열되어야 한다. 안쪽에서 열린 괄호가 먼저 닫히고, 바깥쪽 괄호가 닫혀야 한다.

TestCase2)
>>> P1(‘()[]{}’) True
TestCase3)
>>> P1(‘([)]’) False
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// 스택을 위한 최대 크기 설정
#define MAX_SIZE 1000
// 스택 배열 선언
char stack[MAX_SIZE];
// 스택의 상단을 가리키는 변수 (비어있을 때 -1)
int top = -1;

// 스택에 원소를 추가하는 함수
void push(char c) {
    // 스택이 꽉 차지 않았는지 확인
    if (top < MAX_SIZE - 1) {
        stack[++top] = c;  // 원소를 추가하고 top 값을 증가
    }
}

// 스택에서 원소를 제거하고 반환하는 함수
char pop() {
    // 스택이 비어있지 않은지 확인
    if (top >= 0) {
        return stack[top--];  // 최상단 원소를 반환하고 top 값을 감소
    }
    return '\0';  // 스택이 비어있을 때 null 문자 반환
}

// 스택이 비어있는지 확인하는 함수
bool isEmpty() {
    return top == -1;
}

// 주어진 괄호 문자열이 유효한지 확인하는 함수
bool isValid(const char* bracket) {
    char c;
    for (int i = 0; bracket[i] != '\0'; i++) {
        // 열린 괄호일 경우 스택에 추가
        if (bracket[i] == '(' || bracket[i] == '{' || bracket[i] == '[') {
            push(bracket[i]);
        } else {
            // 닫힌 괄호일 경우 스택에서 꺼내어 짝이 맞는지 확인
            c = pop();
            if ((bracket[i] == ')' && c != '(') ||
                (bracket[i] == '}' && c != '{') ||
                (bracket[i] == ']' && c != '[')) {
                return false;  // 짝이 맞지 않으면 false 반환
            }
        }
    }
    // 모든 괄호가 정확하게 닫혔으면 스택이 비어있어야 함
    return isEmpty();
}

int main() {
    char input[1000];

    printf("Enter a bracket sequence: ");  // 사용자에게 문자열 입력 요청
    fgets(input, sizeof(input), stdin);    // 문자열 입력 받기
    input[strcspn(input, "\n")] = '\0';   // 줄바꿈 문자 제거

    // 입력된 문자열의 유효성 검사 후 결과 출력
    if (isValid(input)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}
