// gcc input_P1.c -o input_P1
/*
아래 가이드라인에 따라 프로그램 P1을 작성하여라.

(1) P1을 실행하면 “Enter any natural number:”라는 문구가 출력된다.
(2) 사용자로부터 임의의 자연수를 입력받는다.
(3) 이 자연수가 3으로 나누어 떨어지면 1을 출력하고, 나누어 떨어지지 않으면 0을 출력한다.

TestCase1)
>>> ./P1
Enter any natural number:5 
ans:0
*/

#include <stdio.h>

int main(void){
    int num;
    int ans;

    printf("Enter any natural number:");
    scanf("%d", &num);

    if (num % 3 == 0)
        ans = 1;
    else
        ans = 0;
    printf("ans:%d\n", ans);

}