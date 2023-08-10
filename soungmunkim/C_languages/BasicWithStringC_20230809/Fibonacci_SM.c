/*
사용자로부터 임의의 자연수 혹은 0을 argument로 입력 받아 해당하는 피보나치 수열의 값을 Return 하는 fibonacci 함수를 작성

TestCase1)
>>> ./P3 1 
1

TestCase2)
>>> ./P3 10 
89
*/

#include <stdio.h>
#include <stdlib.h> //for atoi()
// fibonacci sequence = f(n) = f(n-1) + f(n-2)
int f(int n); //함수 선언

int main(int argc, char* argv[]){
    if (argc > 1) { //argv[1]부터 받은 input이 시작됨
        int n = atoi(argv[1]); //문자열로 받은 걸 정수로 변환
        printf("%d\n", f(n));
    }
    else {
        printf("No argument provided.\n");
    }
    return 0;
}

int f(int n){
    if(n == 1 || n == 0)
        return 1;
    return f(n-1) + f(n-2); //recursive function
}