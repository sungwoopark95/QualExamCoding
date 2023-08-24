/*
[Check Prime Number] 사용자에게 Input 따로 받기
1) 2부터 X-1까지의 모든 자연수로 나누었을 때,
    나누어떨어지는 수가 하나라도 존재하면 X는 소수가아님
2) 2부터 math.sqrt(x) + 1 까지만 확인해서,
    나누어떨어지는 수가 하나라도 존재하면 X는 소수가아님 (더 빠른 방법)

[output]
Find prime number within a range: 
--------------------------------------
-> The start of the range: 1
-> The end of the range: 100

The prime numbers between 1 and 100 are:
2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97 

*/

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool isPrime(int num);

int main() {
    unsigned int start_num;
    unsigned int end_num;

    // Set start num and end num (Input 받기)
    printf("Find prime number within a range: \n");
    printf("--------------------------------------\n");
    printf("-> The start of the range: ");
    scanf("%u", &start_num); // %u를 사용하면 부호 없는 정수 (%d는 부호 있는 정수)
    printf("-> The end of the range: ");
    scanf("%u", &end_num);

    printf("\nThe prime numbers between %u and %u are:\n", start_num, end_num);

    // Prime number 찾기
    if (start_num < 1)
        printf("None\n");
    else if (start_num < 2) { // start, end가 1일때는 prime num 없음
        if (end_num < 2)
            printf("None\n");
        else // start num만 1부터라면 2로 바꾸기 (1은 Prime num이 아니라서)
            start_num = 2;
    }

    for (unsigned int num = start_num; num <= end_num; num++) {
        if (isPrime(num) == true)
            printf("%u ", num);
    }
    printf("\n");
    return 0;
}

bool isPrime(int num) {
    // doulbe은 부동소수점 숫자 저장 가능
    double num_sqrt = sqrt(num);
    // 한번이라도 나눠지면 prime number가 아니므로 false
    for (unsigned int i = 2; i <= num_sqrt; i++) {
        if (num % i == 0)
            return false;
    }
    return true;
}

