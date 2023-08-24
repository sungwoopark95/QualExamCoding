/*
자연수 n 에 대해서, 어떠한 자연수 k 에 대해서도 k 와 k 의 각 자리 수를 모두 더했을 때 n 으로 만들 수 없으면,
 n 을 self number 라고 한다.

예를 들어,21=15+1+5 이므로(n=21,k=15)21 은 selfnumber 가 아니다. 
또 다른 예로, 19=14+1+4 이므로 (n=19,k=14)19 역시 selfnumber 가 아니다. 
반면 20 은 그러한 k 가 존재하지 않으므로 selfnumber 가 맞다. 
자연수 n 을 입력 받아서 n 보다 큰 최소의 self number 를 return 하는 함수를 구현하시오.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int P3(int n);
//selfSum 함수는 추가로 구현한 함수 (self sum이 해당 값과 같다면 self number가 아님으로 체크를 위해 만듦)
int selfNum(int k);
int selfNum(int k){
    // write your code below'
    int sum = k;
    while(k != 0){
        sum += k % 10; // k와 k의 각 자릿 수 더함
        k /= 10;
    }
    return sum;
}
int P3(int n){
    int ans = n+1; // n+1부터 self number인지 확인 시작
    // 1부터 ans-1까지의 수 중 self sum을 하면 ans인 경우 self number가 아님
    while(1){
        bool isSelfNum = true;
        for(int i = 1; i < ans; i++) {
            if(selfNum(i) == ans){
                isSelfNum = false;
                break;
            }
        }
        // 만약 self number이면 return하고 아닐 경우 다음 숫자로 넘어감
        if(isSelfNum == true)
            return ans;
        else
            ans += 1;
    }
    return 0;
}

// DO NOT MODIFY BELOW!
int main(int argc, char* argv[]){
    int n = atoi(argv[1]);
    int ans = P3(n);

    printf("%d\n", ans);

    return 0;
}