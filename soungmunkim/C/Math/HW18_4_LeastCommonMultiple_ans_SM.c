/*
[각 숫자에 대해 n 이하의 모든 자연수로 나누어지는지 체크하는 방식]
자연수 n 을 입력 받아서 n 이하의 모든 자연수에 대해 나누어 떨어지는 자연수 중 가장 작은 수를 return 하는 함수를 구현하시오.
*/

#include <stdio.h>
#include <stdlib.h>

int P4(int n);
/*
k가 n 이하의 자연수 중 모든 수로 나누어 떨어지면 1, 그렇지 않으면 0 반환하는 함수
*/
int check(int n, int k); 
int check(int n, int k){
    for(int i = 1; i<=n; i++){
        if(k % i != 0){
            return 0;
        }
    }
    return 1;
}
int P4(int n){
    // write your code below
    // 각 숫자에 대해 n 이하의 모든 자연수로 나누어지는지 체크하는 방식
    int k = n;
    while(1){
        if(check(n, k))
            return k;
        else
            k++;
    }
}

// DO NOT MODIFY BELOW!
int main(int argc, char* argv[]){
    int n = atoi(argv[1]);
    int ans = P4(n);

    printf("%d\n", ans);

    return 0;
}