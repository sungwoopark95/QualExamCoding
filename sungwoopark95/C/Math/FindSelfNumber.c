/*
자연수 n에 대해서, 어떠한 자연수 k에 대해서도 k와 k의 각 자리 수를 모두 더했을 때 n으로 만들 수 없으면, n을 self number라고 한다. (https://en.wikipedia.org/wiki/Self_number)  
예를 들어, 21 = 15 + 1 + 5이므로(n = 21, k = 15) 21은 self number가 아니다. 
또 다른 예로,  19 = 14 + 1 + 4 이므로 (n=19, k=14) 19 역시 self number가 아니다. 
반면 20은 그러한 k가 존재하지 않으므로 self number가 맞다. 
자연수 n을 입력 받아서 n보다 큰 최소의 self number를 return하는 함수를 구현하시오. 
*/
#include <stdio.h>
#include <stdlib.h>

int digit_sum(int n) {
    int sum = 0;
    while (n) {
        sum += n % 10;
        n = n / 10;
    }
    return sum;
}

int is_self_num(int n) {
    for (int i=1;i<=n;i++) {
        if (n == (i + digit_sum(i))) {
            printf("%d = %d + %d\n", n, i, digit_sum(i));
            return 0;
        }
    }
    return 1;
}

int P3(int n){
    int ans = n + 1;
    while (!is_self_num(ans)) { ans++; }
    return ans;
}


// DO NOT MODIFY BELOW!
int main(int argc, char* argv[]){
    int n = atoi(argv[1]);
    int ans = P3(n);

    printf("%d\n", ans);

    return 0;
}
