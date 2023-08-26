/*
(1) P2를 실행하면 “Enter any alphabet:”이라는 문구가 출력된다. 
(2) 사용자로부터 임의의 영어 알파벳 한 개(소문자, 대문자 모두 포함)를 입력받는다.  
(3) 해당 알파벳으로부터 대문자 A까지 내림차순으로 모든 character(알파벳 아닌 글자도 포함)를 출력한다. 내림차순의 기준은 ASCII 코드표 순서이다.
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    char letter;
    int target = 'A'; // ascii code 나옴
    printf("Enter any alphabet:");
    scanf("%c", &letter);

    for (int i = (int)letter; i >= target; i--) {
        printf("%c", (char)i);
    }
    printf("\n");
    return 0;
}
