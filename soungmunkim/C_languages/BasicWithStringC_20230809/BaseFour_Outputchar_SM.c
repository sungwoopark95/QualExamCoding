/*
임의의 자연수를 argument로 입력 받아 4진수로 변환하고, 변환된 4진수를 Return하는 base_four 함수를 작성하여라.

TestCase1)
>>> ./P3 10 
22

TestCase2)
>>> ./P3 4 
10
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverseString(char* str);

int main(int argc, char* argv[]){
    int m;
    int remainder;
    int size=2; //초기 크기 할당 (최소 크기 char+null = 2)
    char* bit = (char*) malloc(size * sizeof(char)); //char 동적할당으로 string만들기
    int idx = 0;

    if (argc > 1){
        int n = atoi(argv[1]); //input받은 문자열 정수로 변환
        m = n;
        while (m >= 4){
            // 마지막 위치에 왔는지 확인 (문자열은 0에서 시작하기 때문)
            // idx는 현재까지 저장된 bit 문자의 개수
            if(idx == size-1){
                size *= 2;
                // bit가 새로운 메모리 주소 가르킴
                bit = realloc(bit, size); //realloc은 할당된 메모리의 크기 재조정할 때 사용
            }
            remainder = m % 4;
            bit[idx] = '0'+remainder; // ASCII 코드를 이용하여 숫자를 문자로 변환
            m =  m / 4;
            idx++;
        }
        bit[idx] = '0'+m;
        bit[idx+1] = '\0'; //문자열 종료
    }

    reverseString(bit); //문자열인 bit 뒤집기
    printf("%s\n", bit);

    free(bit); //동적으로 할당된 메모리 해제
    return 0;
}

//문자열이 짝수던 홀수던 항상 이 함수 사용함
void reverseString(char* str) {
    int length = strlen(str);
    for (int i = 0; i < length/2; i++){
        char temp = str[i];
        str[i] = str[length -1 -i];
        str[length -1 -i] = temp;
    }
}