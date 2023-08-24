/*
[최대 공배수 사용하여 풀기]
자연수 n 을 입력 받아서 n 이하의 모든 자연수에 대해 나누어 떨어지는 자연수 중 가장 작은 수를 return 하는 함수를 구현하시오.
*/

#include <stdio.h>
#include <stdlib.h>

int P4(int n);
int gcd(int a, int b);
int lcm(int a, int b);

// 최대 공약수 계산 함수
int gcd(int a, int b) {
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

// 최소 공배수 계산 함수
// 두 수의 곱을 두 수의 최대 공약수(GCD)로 나눈 값이 최소 공배수
int lcm(int a, int b) {
    return a * b / gcd(a, b);
} 
// n 이하의 모든 자연수로 나누어 떨어지는 가장 작은 수를 계산하는 함수
int P4(int n){
    // write your code below
    int result = 1;
    // 1부터 n까지 순회하며 해당 숫자와 현재 결과값의 최소 공배수를 찾음
    for(int i = 2; i <= n; i++){
        result = lcm(result, i);
    }
    return result;

}

// DO NOT MODIFY BELOW!
int main(int argc, char* argv[]){
    int n = atoi(argv[1]);
    int ans = P4(n);

    printf("%d\n", ans);

    return 0;
}