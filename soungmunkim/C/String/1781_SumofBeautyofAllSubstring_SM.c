/*
Sum of Beauty of all substring (counter 디버깅 함수 있음! 참고 가능)

[최대 char 빈도수 - 최소 char 빈도수 = beauty of string]
The beauty of a string is the difference in frequencies between the most frequent and least
frequent characters.
For example, the beauty of "abaacc" is 3 - 1 = 2 .
Given a string s , return the sum of beauty of all of its substrings.

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Please enter a string: aabcb 
5
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Please enter a string: aabcbaa
17
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

# define ALPHABET_SIZE 26

// character 빈도 저장하는 구조체 정의
typedef struct {
    int count[ALPHABET_SIZE];
} Counter;

// 새로운 Counter를 초기화하는 함수. 모든 알파벳의 빈도를 0으로 설정
Counter newCounter() {
    Counter c;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        c.count[i] = 0;
    }
    return c;
}

// 주어진 문자열(substring)의 문자 빈도를 계산하는 함수
Counter countFrequency(const char *s) {
    Counter c = newCounter();
    int len = strlen(s);

    for (int i = 0; i < len; i++) {
        // 해당 alphabet의 index = 'a' 뺀 것
        c.count[s[i] - 'a']++;  // 문자열의 각 문자에 대한 빈도 계산
    }
    return c;
}

void beautySum(char *s){
    // 총 beauty 
    int sumbeauty = 0;

    // 모든 가능한 substring 뽑기
    for(int i=0; i<strlen(s); i++){
        for(int j=i; j<strlen(s); j++){
            char sub[100] = {0};
            strncpy(sub, &s[i], j-i+1); // s의 부분 문자열 복사
            sub[j-i+1] = '\0';
            // printf("%s ", sub);

            // return 받아 올 것을 새로 할당할 counter 만들어서 sub 넣기
            Counter sub_counter = newCounter();
            sub_counter = countFrequency(sub);
            
            // // sub_counter 프린트해보기
            // for(int i=0;i<ALPHABET_SIZE;i++) {
            //     printf("%d ", sub_counter.count[i]);
            // }
            // printf("\n");

            int min_cnt = 100000;
            int max_cnt = 0;

            for(int i=0; i<ALPHABET_SIZE; i++){
                // char count가 0 이면 패스하기
                if(sub_counter.count[i] == 0)
                    continue;
                else{ // 아니면 Min or max count update하기
                    if(sub_counter.count[i] < min_cnt)
                        min_cnt = sub_counter.count[i];
                    if(sub_counter.count[i] > max_cnt)
                        max_cnt = sub_counter.count[i];
                }
            }
            // printf("min cnt: %d, max cnt: %d\n", min_cnt, max_cnt);
   
            int beauty_cnt = max_cnt - min_cnt;
            sumbeauty += beauty_cnt;
        }
    }
    printf("%d\n", sumbeauty);
}

int main() {

    char *s; 
    printf("Please enter a string: ");
    scanf("%s", s);

    beautySum(s);

    return 0;
}