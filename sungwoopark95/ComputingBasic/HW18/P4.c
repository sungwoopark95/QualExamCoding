/*
자연수 n을 입력 받아서 n 이하의 모든 자연수에 대해 나누어 떨어지는 자연수 중 가장 작은 수를 return하는 함수를 구현하시오.  
*/

#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b) {
        int temp = a;
        a = b;
        b = temp % b;
    }
    return a;
}

int lcm(int a, int b) {
    return (a*b) / gcd(a, b);
}

int P4(int n) {
    // write your code below
    int ans = 1;
    for (int i=1;i<=n;i++) {
        ans = lcm(ans, i);
    }
    return ans;
}

// DO NOT MODIFY BELOW!
int main(int argc, char* argv[]){
    int n = atoi(argv[1]);
    int ans = P4(n);

    printf("%d\n", ans);

    return 0;
}
