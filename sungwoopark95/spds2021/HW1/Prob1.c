/*
# P1. 소인수분해
자연수 한 개를 입력으로 받아 이를 소인수분해한 결과를 반환하는 함수 `prime_factorizer`를 작성하라. 
소인수분해한 결과는 (소수, 지수)의 tuple을 담은 list로 반환하며, 리스트 내 tuple의 순서는 소수 크기의 오름차 순으로 정렬하여야 한다.
실행 예시는 다음과 같다.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXLEN 1000

typedef struct {
    int x;
    int y;
} pair;

int is_prime(int x) {
    if (x == 1) {
        return 0;
    }
    for (int i=2;i<=sqrt(x);i++) {
        if (x % i == 0) {
            return 0;
        }
    }
    return 1;
}

int prime_factorizer(pair* ans, int num) {
    /*
    a function that store a pair into `ans` and returns the length of `ans`
    */
    int length = 0;
    for (int i=1;i<=num;i++) {
        if (is_prime(i)) {
            int power = 0;
            while (num % i == 0) {
                power++;
                num = num / i;
            }
            if (power > 0) {
                // store the (prime, power) into the ans
                ans[length].x = i;
                ans[length].y = power;
                length++;
            }
        }
        if (num == 1) { break; }
    }
    return length;
}

int main(int argc, char* argv[]) {
    int num = atoi(argv[1]);
    // 새로운 구조체 만들고 동적할당하기 위해서는 그 구조체가 들어갈 수 있는 크기를 반드시 지정해야 함!
    pair* factors = (pair*)malloc(sizeof(pair)*MAXLEN);
    int length = prime_factorizer(factors, num);

    printf("[");
    for (int i=0;i<length;i++) {
        pair p = factors[i];
        if (i < length - 1) {
            printf("(%d, %d), ", p.x, p.y);
        } else {
            printf("(%d, %d)", p.x, p.y);
        }
    }
    printf("]\n");

    free(factors);
    return 0;
}
