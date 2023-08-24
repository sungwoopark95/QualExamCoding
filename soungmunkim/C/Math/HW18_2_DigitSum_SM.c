/*
십진수 자연수 n이 주어질 때 n의 각 자릿수의 합을 return 하는 함수를 구현하시오.
n 은 32 비트로 표현 가능한 자연수 범위 내의 수이다.

TestCase1)
./P2 158
14
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int DigitSum(int n); // 함수 선언

int DigitSum(int n){ // 합수 정의
    // write your code below
    int sum = 0; // 0으로 꼭 설정하기!
    while (n>0){
        sum += n % 10; //마지막 자리수 sum에 더하기
        n /= 10; // 마지막 자리수 빼기
    }
    return sum;
}


// DO NOT MODIFY BELOW!
int main(int argc, char* argv[]){
    int n = atoi(argv[1]);
    int ans = DigitSum(n);

    printf("%d\n", ans);

    return 0;
}