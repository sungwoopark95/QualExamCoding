/*
‘(’, ‘)’, ‘{’, ‘}’, ‘[’, ‘]’으로 구성된 String을 Input으로 받는다. 
또한 Skeleton Code에는 Stack의 구현을 위한 함수들이 구현되어 있다. 
이를 적절히 활용하여 String이 아래 규칙을 만족하면 0, 만족하지 않으면 -1을 출력하도록 코드를 작성하여라. 
‘ ’
<규칙> 
(1) 괄호가 열렸다면 같은 타입의 괄호에 의해 닫혀야 한다. 
(2) 적절한 순서로 괄호가 배열되어야 한다.안쪽에서 열린 괄호가 먼저 닫히고, 바깥쪽 괄호가 닫혀야 한다. 

※ Command line argument 입력시 “”으로 감싸주어야 한다.
※ 괄호의 총 개수는 100개 미만으로 제한된다. 

TestCase1)
>>> ./P2 "()"
0

TestCase2)
>>> ./P2 "([)]"
-1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100  // 스택의 최대 크기를 정의

char stack[MAX_SIZE];  // 스택 배열
int top = -1;  // 스택의 최상단을 가리키는 변수

// 스택에 요소를 추가하는 함수
void push(char c) {
    if (top < MAX_SIZE - 1) {  // 스택이 꽉 찼는지 확인
        stack[++top] = c;  // 요소를 추가하고 top 위치를 1 증가
    }
}

// 스택에서 요소를 제거하고 반환하는 함수
char pop() {
    if (top >= 0) {  // 스택에 요소가 있는지 확인
        return stack[top--];  // 현재 top의 요소를 반환하고 top 위치를 1 감소
    }
    return '\0';  // 스택이 비어있을 경우 NULL 문자 반환
}

// 스택의 최상단 요소를 반환하지만 제거하지는 않는 함수
char peek() {
    if (top >= 0) {  // 스택에 요소가 있는지 확인
        return stack[top];  // 현재 top의 요소를 반환
    }
    return '\0';  // 스택이 비어있을 경우 NULL 문자 반환
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("문자열을 입력하세요.\n");
        return -1;
    }

    char* input = argv[1];  // 사용자가 입력한 문자열 저장

    for (int i = 0; i < strlen(input); i++) {
        char current = input[i];
        
        // 여는 괄호는 스택에 추가
        if (current == '(' || current == '{' || current == '[') {
            push(current);
        } 
        // 닫는 괄호인 경우
        else if (current == ')' || current == '}' || current == ']') {
            char lastOpened = pop();  // 스택의 최상단 요소를 꺼냄
            
            // 각 닫는 괄호와 짝이 되는 여는 괄호를 비교
            if ((current == ')' && lastOpened != '(') ||
                (current == '}' && lastOpened != '{') ||
                (current == ']' && lastOpened != '[')) {
                printf("-1\n");  // 짝이 안 맞는 경우 -1 출력
                return 0;
            }
        }
    }

    // 전체 문자열을 확인한 후에도 스택이 비어있지 않다면 짝이 맞지 않는 괄호가 있다는 뜻
    if (top == -1) {
        printf("0\n");  // 모든 괄호의 짝이 맞는 경우 0 출력
    } else {
        printf("-1\n");  // 짝이 맞지 않는 경우 -1 출력
    }

    return 0;
}
