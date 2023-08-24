/*
하노이 탑 푸는 방법은 메르센 수 이용하면 됨
f(n) = 2^n - 1
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int P1(int n); // 함수 선언

// Implement P1 
// You can define other function, but P1 must return answer.

int P1(int n){ // 함수 정의
// write your code below
    int ans;
    ans = pow(2, n) - 1;
    return ans;
}


// DO NOT MODIFY BELOW!
int main(int argc, char* argv[]){ //argc: 입력된 문자열 개수, argc: 입력된 문자열
    int n = atoi(argv[1]); //atoi: 입력된 문자열을 정수로 변환
    int ans = P1(n);

    printf("%d\n", ans);

    return 0;
}