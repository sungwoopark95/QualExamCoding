/*
[Max palindrome 찾기]
"palindrome"은 앞에서 뒤로 읽었을 때와 뒤에서 앞으로 읽었을 때 동일한 문자열이나 숫자, 또는 다른 시퀀스를 의미
    즉, palindrome은 그 내용이 앞뒤가 똑같은 단어나 문장을 지칭
    
The list contains palindromes that are not a substring of another palindrome.
A substring is a contiguous sequence of characters within a string.
The characters used in a string are only lower-case alphabets and a space character.

# TestCase
(base) soungmunkim@gimseongmun-ui-MacBookPro String % gcc 2022_1_1_MaxPalindrome_SM.c -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test                                 
Please enter a string: 
kabccbadzdefgfeda
"k", "abccba", "dzd", "defgfed"
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test                                 
Please enter a string: 
kabccba dzabccbaza
"k", " ", "d", "zabccbaz", "aza"
*/

/*
1. 문자열 s의 모든 substring을 찾습니다.
2. 각 substring이 palindrome인지 확인합니다.
3. palindrome이라면, 이 palindrome이 다른 palindrome의 substring인지 확인합니다.
4. substring이 아닌 palindrome 중에서 가장 긴 palindrome을 선택합니다. (palindrome 중에 서로 substring 아닌지 체크)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool palindrome(char *s);
bool substring(char* s, char* t);
void max_palindrome(char* s);

int main(){
    char s[1000]; // 문자열의 최대 길이를 임의로 1000으로 설정했습니다. 필요에 따라 조정하실 수 있습니다.

    printf("Please enter a string: \n");
    fgets(s, sizeof(s), stdin);

    // fgets는 줄 바꿈 문자를 문자열의 끝에 포함시키므로 이를 제거합니다.
    s[strcspn(s, "\n")] = 0;

    // max_palindrome 함수 호출. 함수의 정의를 다른 곳에서 제공해야 합니다.
    max_palindrome(s);

    return 0;
}

// palindrome인지 아닌지 체크하기
bool palindrome(char *s){
    char reversed_s[300] = {0}; // 문자 배열 초기화
    int n = strlen(s);
    int j = 0; // 추가된 변수

    for(int i = n-1; i >= 0; i--){
        reversed_s[j++] = s[i];
    }
    reversed_s[j] = '\0'; // 문자열 종료

    if (strcmp(s, reversed_s) == 0){
        return true;
    }
    else {
        return false;
    }
}

// t가 s의 substring인지 체크
bool substring(char* s, char* t){
    int n = strlen(s);
    int m = strlen(t);

    if (m > n)
        return false;

    // s와 t 길이 차이만큼 for loop 돌건데 s를 t 길이만큼 돌면서 체크할 것
    for(int i = 0; i <= n-m; i++){
        char slice[300];
        strncpy(slice, &s[i], m); // s의 i 위치에서 m 길이만큼 복사
        slice[m] = '\0'; // null 종료 문자 추가
        if(strcmp(slice, t) == 0)
            return true;
    }
    return false;
}

// 주어진 문자열 s 내에서 가장 긴 palindrome들을 찾아 반환하는 함수
void max_palindrome(char* s){
    char max_pals[100][100] = {0}; // Assuming a maximum of 100 palindromes with a maximum length of 100
    int count = 0; // word시작 위치

    // 모든 가능한 substring 뽑기
    for(int i = 0; i < strlen(s); i++){
        for(int j = i; j < strlen(s); j++){
            char sub[100] = {0};
            strncpy(sub, &s[i], j-i+1); //s[i:j+1]
            sub[j - i + 1] = '\0';

            if(palindrome(sub)){ // 현재 substring이 palindrome 일때
                bool is_maximal = true;

                for(int k = 0; k < count; k++){
                    if(substring(max_pals[k], sub) && strcmp(max_pals[k], sub) != 0){
                        is_maximal = false;
                        break;
                    }
                }

                // 만약 현재 palindrome이 기존 palindrome의 substring이 아니라면 후보에 넣기
                if(is_maximal == true) {
                    strcpy(max_pals[count], sub);
                    count++;
                }
            }
        }
    }
    // palindrome 후보들간에서 substring인 후보는 빼기 (filltering 작업)
    char filtered_max_pals[100][100] = {0}; // 최종 Palindromes 담을 리스트 (100 palindromes with 100 lenghts)
    int cnt = 0; // word 시작 점

    for(int i=0; i<count; i++){
        bool is_substring = false;
        for(int j=0; j<count; j++){
            if(i != j) {// 자기 자신 제외
                // max_pals[i] 가 다른 palindrome의 substring인지 체크
                if(substring(max_pals[j], max_pals[i])){
                    is_substring = true;
                    break;
                }
            }
        }
        if(is_substring == false){
            strcpy(filtered_max_pals[cnt], max_pals[i]);
            cnt++;
        }
    }
    // 최종 결과 프린트하기
    printf("\"");
    for (int k=0; k < cnt; k++) {
        printf("%s", filtered_max_pals[k]);
        if(k != cnt -1) {
            printf("\", \"");
        }
    }
    printf("\"\n");
}


