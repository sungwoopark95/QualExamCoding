/*
[소인수분해: Prime Factorizer]
자연수 한 개를 입력으로 받아 이를 소인수분해한 결과를 반환하는 함수 prime factorizer를 작성하라. 
소인 수분해한 결과는 (소수, 지수)의 tuple을 담은 list로 반환하며, 
리스트 내 tuple의 순서는 소수 크기의 오름차 순으로 정렬하여야 한다.

TestCase1)
>>> prime_factorizer(1)
[]
TestCase2)
>>> prime_factorizer(24)
[(2.3), (3,1)]
TestCase3)
>>> prime_factorizer(30)
[(2,1), (3,1), (5,1)]
*/

#include <stdio.h>
#include <stdlib.h>

// prime과 그 count를 저장하기 위한 구조체 
typedef struct{
    int prime;
    int count;
} Factor;

// 소인수분해 함수 구현
Factor* prime_factorizer(int n, int* returnSize);

Factor* prime_factorizer(int n, int* returnSize){
    // 최악의 경우(모든 숫자가 소수일 경우) num개의 소수가 나올 수 있으므로 n 크기로 할당 (동적 할당)
    // [list array 만드는 과정]
    Factor* factors = (Factor*)malloc(n * sizeof(Factor));
    int i = 2;
    int quotient = n;
    // 결과로 반환될 구조체 개수 (포인터를 통해 값을 변경할 예정)
    *returnSize = 0; // 초기에는 아직 소수를 찾지 않았으므로 0으로 설정

    while (quotient > 1){
        int cnt = 0;

        while (quotient % i == 0){
            quotient /= i;
            cnt++;
        }

        if (cnt > 0){
            // List[0].prime = 2 이런식으로 List index에 저장되는 느낌
            factors[*returnSize].prime = i;
            factors[*returnSize].count = cnt;
            (*returnSize)++;
        }
        i++;
    }
    return factors;
}

int main(int argc, char* argv[]){
    int num = atoi(argv[1]);
    int size;
    /*
    size 변수는 prime_factorizer 함수를 통해 설정
    prime_factorizer 함수의 두 번째 인자로 size의 주소를 전달하면, 
    함수 내에서 이 주소에 저장된 값을 변경하여 size를 업데이트

    */
    Factor* ans = prime_factorizer(num, &size);

    // list안 tuple 형태로 Print하기
    printf("[");
    for (int i = 0; i < size; i++){
        printf("(%d, %d)", ans[i].prime, ans[i].count);
        if (i != size - 1){
            printf(", ");
        }
    }
    printf("]\n");

    free(ans); // 동적 메모리 해제
    return 0;
}