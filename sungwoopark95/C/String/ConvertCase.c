/*
사용자로부터 10자 이내의 영어 알파벳으로 구성된 string을 입력 받아 대문자는 소문자로, 
소문자는 대문자로 바꾼 후 출력하는 함수를 작성하여라. 

예시1)  
./P2 ABCdef 
abcDEF
*/

#include <stdio.h>
#include <stdlib.h>

char case_convert(char c);

int main(int argc, char* argv[]) {
    int i = 0;
    while (argv[1][i]) {
        printf("%c", case_convert(argv[1][i]));
        i++;
    }
    printf("\n");
    return 0;
}

char case_convert(char c) {
    int upper_start = 'A';
    int upper_end = 'Z';
    int lower_start = 'a';
    int lower_end = 'z';
    char converted;

    if (c >= upper_start && c <= upper_end) {
        // if c is an upper case, convert it to the corresponding lower case
        converted = lower_start + (c - upper_start);
    } else if (c >= lower_start && c <= lower_end) {
        // if c is a lower case, convert it to the corresponding upper case
        converted = upper_start + (c - lower_start);
    }
    return converted;
}
