/*
[Score of parentheses]
parentheses에 정해진 규칙으로 점수 매기기

그냥 "()"는 1
A + B 는 2
(A) 는 2*A

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test                              
Enter a bracket sequence: ()
(, ) 
True
The score is 1
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Enter a bracket sequence: (())
(, ( 
False
The score is 2
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Enter a bracket sequence: ()()
(, ) 
True
(, ) 
True
The score is 2
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
int isValid(const char* bracket) {
    char c;
    bool isClosed = false;
    int score;
    int sum = 0;
    for (int i = 0; bracket[i] != '\0'; i += 2) {
        // 열린 괄호일 경우 스택에 추가
        if (bracket[i] == '(' || bracket[i] == '{' || bracket[i] == '[') {
            push(bracket[i]);
            c = pop();
            // printf("%c, %c \n", c, bracket[i+1]);

            if (bracket[i+1] != c) {
                isClosed = true;
            }
            else {
                isClosed = false;
            }

            score = 1;
        
            if(isClosed == true){
                // printf("True\n");
                sum += score;
            }
            else{
                // printf("False\n");
                sum += 2*score;
            }
        } 
    }
    return sum;
}

int main() {
    char input[1000];

    printf("Enter a bracket sequence: ");  // 사용자에게 문자열 입력 요청
    fgets(input, sizeof(input), stdin);    // 문자열 입력 받기
    input[strcspn(input, "\n")] = '\0';   // 줄바꿈 문자 제거

    // 입력된 문자열의 유효성 검사 후 결과 출력
   int result;
   result = isValid(input);
   
   printf("The score is %d\n", result);

    return 0;
}