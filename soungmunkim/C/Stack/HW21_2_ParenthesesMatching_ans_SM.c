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

/* 스택을 표현하기 위한 구조체 */
struct Stack {
    int top;                 // 스택의 최상단 요소의 위치
    unsigned capacity;       // 스택의 최대 크기
    char* array;             // 스택 요소를 저장할 배열
};
 
/* 주어진 용량으로 스택을 생성하는 함수. 스택의 초기 크기는 0 */
struct Stack* createStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));  // 스택 구조체 메모리 할당
    stack->capacity = capacity;  // 스택의 최대 크기 설정
    stack->top = -1;             // 초기 top 위치는 -1 (비어있는 상태)
    stack->array = (char*)malloc(stack->capacity * sizeof(char));  // 스택 배열 메모리 할당
    return stack;  // 생성된 스택 반환
}
 
/* 스택이 꽉 찼는지 확인하는 함수. top이 마지막 인덱스와 같으면 스택은 꽉 찬 것 */
int isFull(struct Stack* stack)
{
    return stack->top == stack->capacity - 1;
}

/* 스택이 비어있는지 확인하는 함수. top이 -1이면 스택은 비어 있는 것 */
int isEmpty(struct Stack* stack)
{
    return stack->top == -1;
}
 
/* 스택에 요소를 추가하는 함수. 스택이 꽉 찼다면 요소를 추가하지 않음 */
void push(struct Stack* stack, char item)
{
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;  // 스택에 요소 추가 후 top 위치 1 증가
}
 
/* 스택에서 최상단 요소를 제거하고 반환하는 함수. 스택이 비어있으면 '0' 반환 */
char pop(struct Stack* stack)
{
    if (isEmpty(stack))
        return '0';
    return stack->array[stack->top--];  // 현재 top의 요소 반환 후 top 위치 1 감소
}

int main(int argc, char* argv[])
{  
    char* strInput = argv[1];  // 사용자 입력 괄호 문자열
    int success = 0;           // 결과 저장 변수. 성공시 0, 실패시 -1 저장

    struct Stack * myStack = createStack(100);  // 최대 크기가 100인 스택 생성

    /* 입력 문자열의 각 문자를 순회 */
    for (char *c = strInput; *c; ++c){
        /* 여는 괄호일 경우 스택에 추가 */
        if (*c == '(' || *c == '{' || *c == '['){
            push(myStack, *c);
        } else {
            /* 닫는 괄호일 경우 스택의 최상단 요소와 짝이 맞는지 확인 */
            char poppedItem = pop(myStack);
            switch(*c){
                case ')':
                    if (poppedItem != '(') success = -1;
                    break;
                case '}':
                    if (poppedItem != '{') success = -1;
                    break;
                case ']':
                    if (poppedItem != '[') success = -1;
                    break;
                default:  // 유효하지 않은 문자나 스택이 빈 경우
                    success = -1;
                    break;
            }
            if (success == -1)  // 짝이 맞지 않는 괄호 발견 시 루프 종료
                break;
        }    
    }

    /* 모든 문자를 확인한 후 스택에 요소가 남아 있다면 괄호의 짝이 맞지 않는 것 */
    if (!isEmpty(myStack))
        success = -1;

    printf("%d\n", success);  // 결과 출력

    return 0;
}
