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

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool isValid(char* s) {
    int stack_size = strlen(s);
    char* stack = (char*) malloc(stack_size * sizeof(char));
    int top = -1;

    for (int i = 0; i < strlen(s); i++) {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
            stack[++top] = s[i];
        }
        else {
            if (top == -1) {
                // 스택이 비어있으면 유효하지 않은 괄호
                free(stack);
                return false;
            }

            if (s[i] == ')' && stack[top] != '(') {
                free(stack);
                return false;
            }
            if (s[i] == '}' && stack[top] != '{') {
                free(stack);
                return false;
            }
            if (s[i] == ']' && stack[top] != '[') {
                free(stack);
                return false;
            }
            
            top--;  // 유효한 괄호 쌍을 발견했으므로 스택에서 pop
        }
    }

    bool result = (top == -1);
    free(stack);
    return result;
}


