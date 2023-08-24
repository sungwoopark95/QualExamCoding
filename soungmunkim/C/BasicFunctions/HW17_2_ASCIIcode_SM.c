/*
아래 가이드라인에 따라 프로그램 P2를 작성하여라.

(1) P2를 실행하면 “Enter any alphabet:”이라는 문구가 출력된다.
(2) 사용자로부터 임의의 영어 알파벳 한 개(소문자, 대문자 모두 포함)를 입력받는다.
(3) 해당 알파벳으로부터 대문자 A까지 내림차순으로 모든 character(알파벳 아닌 글자도 포함)를 출력한다. 내림차순의 기준은 ASCII 코드표 순서이다.

TestCase)
>>> ./P2
Enter any alphabet:a 
a`_^]\[ZYXWVUTSRQPONMLKJIHGFEDCBA
*/

#include <stdio.h>
#include <stdlib.h>

int main(void){
    char letter;

    printf("Enter any alphabet:");
    // char은 %c로 받고 string은 %s로 받아야 함
    scanf("%c", &letter);

    // C에서는 ASCII code보려면 (int)'chr'로 해야함
    // A (65)까지 출력하기
    for(int i = (int)letter; i >= 65; i--)
        printf("%c", (char)i);
    
    // 최종엔 줄바꿈해서 마무리
    printf("\n");

    return 0;
}