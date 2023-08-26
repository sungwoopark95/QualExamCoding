/*
하노이의 탑은 퍼즐의 일종이다. (https://en.wikipedia.org/wiki/Tower_of_Hanoi) 세 개의 기둥이 있고, 처음에 한 기둥에 원판이 작은 것이 위에 있도록 순서대로 쌓여 있다. 
퍼즐의 목적은 다음 두 가지 조건을 만족하면서, 한 기둥에 꽂힌 원판을 그 순서 그대로 다른 기둥으로 옮겨서 다시 쌓는 것이다.  

a. 한 번에 한 개의 원판만 옮길 수 있다.  
b. 큰 원판이 작은 원판 위에 있어서는 안 된다. 

원판의 개수 n 을 입력 받을 때, 위 조건을 만족하면서 처음의 한 기둥에 있는 원판을 모두 다른 하나의 기둥에 옮기기 위한 최소 횟수를 return 하는 함수를 구현하시오. (recursion 을 이용해서 풀어보세요!) 
*/

#include <stdio.h>
#include <stdlib.h>

int P1(int n) {
    if (n == 1) {
        return 1;
    } else {
        return 2 * P1(n-1) + 1;
    }
}

int main(int argc, char* argv[]){ //argc: 입력된 문자열 개수, argc: 입력된 문자열
    int n = atoi(argv[1]); //atoi: 입력된 문자열을 정수로 변환
    int ans = P1(n);

    printf("%d\n", ans);

    return 0;
}
