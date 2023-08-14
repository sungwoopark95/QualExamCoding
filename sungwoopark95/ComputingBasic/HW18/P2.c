/*
십진수 자연수 n이 주어질 때 n의 각 자릿수의 합을 return하는 함수를 구현하시오. 
* n은 32 비트로 표현 가능한 자연수 범위 내의 수이다
*/

#include <stdio.h>
#include <stdlib.h>

int P2(int n) {
    int ans = 0;
    while (n) {
        ans += n % 10;
        n = n / 10;
    }
    return ans;
}

// DO NOT MODIFY BELOW!
int main(int argc, char* argv[]){
    int n = atoi(argv[1]);
    int ans = P2(n);

    printf("%d\n", ans);

    return 0;
}
