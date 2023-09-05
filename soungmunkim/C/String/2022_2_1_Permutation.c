/*
[string으로 permutation 구하기]
# TestCase
>>> s = "abc"
>>> str_perm(s)
>>> ["abc", "acb", "bac", "bca", "cab", "cba"]

>>> s = "abb"
>>> str_perm(s)
>>> ["abb", "aba", "bba"]

(base) soungmunkim@gimseongmun-ui-MacBookPro String % gcc 2022_2_1_Permutation.c -o Permutations
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./Permutations 
Please enter a string: 
abc 
"abc", "acb", "bac", "bca", "cba", "cab"
*/

#include <stdio.h>
#include <string.h>

void swap(char* a, char* b){
    char temp = *a;
    *a = *b;
    *b = temp;
}

int count = 0;  // 전역 변수로 count 선언
char permutations[100][100] = {0};  // 전역 변수로 permutations 선언

void backtrack(int start, char* s){
    if (start == strlen(s)){
        strcpy(permutations[count++], s);  // 문자열 복사 후 count 증가
    }

    for (int i = start; i < strlen(s); i++){
        swap(&s[start], &s[i]);
        backtrack(start+1, s);
        swap(&s[start], &s[i]);
    }
}

void str_perm(char *s){
    backtrack(0, s);

    printf("\"");
    for (int k = 0; k < count; k++) {
        printf("%s", permutations[k]);
        if(k != count - 1) {
            printf("\", \"");
        }
    }
    printf("\"\n");
}


int main() {    
    char s[1000]; // 문자열의 최대 길이를 임의로 1000으로 설정했습니다. 필요에 따라 조정하실 수 있습니다.

    printf("Please enter a string: \n");
    fgets(s, sizeof(s), stdin);

    // fgets는 줄 바꿈 문자를 문자열의 끝에 포함시키므로 이를 제거합니다.
    s[strcspn(s, "\n")] = 0;

    // max_palindrome 함수 호출. 함수의 정의를 다른 곳에서 제공해야 합니다.
    str_perm(s);

    return 0;



}