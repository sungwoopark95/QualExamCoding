/*
[licensePlate에 있는 대소문자 상관없이 letter들이 모두 word에 포함되는 것 찾기]

1. 먼저 licensePlate에 char인 것을 찾고 대소문자 상관없이 다 소문자로 만들기
2. 해당 char과 빈도수 dict에 저장하기
3. word (string array) 돌면서 해당 char 다 있는지 체크 후 반환


Example 1:

Input: licensePlate = "1s3 PSt", words = ["step","steps","stripe","stepple"]
Output: "steps"
Explanation: licensePlate contains letters 's', 'p', 's' (ignoring case), and 't'.
"step" contains 't' and 'p', but only contains 1 's'.
"steps" contains 't', 'p', and both 's' characters.
"stripe" is missing an 's'.
"stepple" is missing an 's'.
Since "steps" is the only word containing all the letters, that is the answer.

Example 2:
Input: licensePlate = "1s3 456", words = ["looks","pest","stew","show"]
Output: "pest"
Explanation: licensePlate only contains the letter 's'. All the words contain 's', but among these "pest", "stew", and "show" are shortest. The answer is "pest" because it is the word that appears earliest of the 3.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

 /*--------------- word = "" 에서 char 하나씩 append 하는 함수 ---------------*/
char* append_char(char* str, char c) {
    // 문자열의 현재 길이를 구함
    int length = (str != NULL) ? strlen(str) : 0;

    // 문자열을 저장하기 위한 새로운 메모리를 할당하거나 재할당함.
    // 추가된 문자와 NULL 종료 문자('\0')를 위해 2만큼 더함
    char* new_str = (char*)realloc(str, (length + 2) * sizeof(char));
    if (new_str == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    // 새 문자를 추가하고 문자열을 종료
    new_str[length] = c;
    new_str[length + 1] = '\0';

    return new_str;
}

/*----------------------- 소문자 빈도수 저장하는 dict -----------------------*/

#define ALPHABET_SIZE 26  // 알파벳 크기 정의 (영어 소문자는 26개)

// 문자 빈도를 저장하는 구조체 정의
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

// 주어진 문자열의 문자 빈도를 계산하는 함수
Counter countFrequency(const char *s, int len) {
    Counter c = newCounter();
    for (int i = 0; i < len; i++) {
        // 해당 alphabet의 index = 'a' 뺀 것
        c.count[s[i] - 'a']++;  // 문자열의 각 문자에 대한 빈도 계산
    }
    return c;
}


/*------------------------------- 함수 시작 -------------------------------*/
char* shortestCompletingWord(char* licensePlate, char ** words, int wordsSize){

    int size = strlen(licensePlate);
    char* temp = NULL; //append char에 필요함
 
 /*-------------------- 숫자, 대문자, 소문자 뽑아내는 코드 (대문자를 소문자로) --------------------------*/
    for(int i=0; i < size; i++){
        // 해당 char이 숫자일때
        if((int)licensePlate[i] < 65){
            continue;
        }
        // 해당 char이 대문자일 경우 -> 소문자로
        if(65<=(int)licensePlate[i] && (int)licensePlate[i]<=90){
            int lowercaseVal;
            lowercaseVal = (int)licensePlate[i] + 32;
            // 소문자로 바꾼 것을 temp word에 추가하기
            // printf("to lowercase is: %c\n", (char)lowercaseVal);
            temp = append_char(temp, (char)lowercaseVal);
        }
        // 해당 char이 소문자일 경우
        if(97<=(int)licensePlate[i] && (int)licensePlate[i] <= 122){
            // printf("char is: %c\n", licensePlate[i]);
            temp = append_char(temp, licensePlate[i]);
        }
    }
 /*------------------------------------------------------------------------------------*/


    // 새로 만든 word size 저장
    int temp_size;
    temp_size = strlen(temp);
    int word_size;
    // 특정 char 빈도가 같은지 체크
    bool isSame = false;
    
    // word 담을 char* array 설정
    char* shortest[100];
    int shortest_idx = 0;

    // 짧은 word 찾기 위한 길이 체크용
    int min_len = 1000;
    char* result;

    // 새로 만든 word의 char 빈도수 저장 dict
    Counter tmp = countFrequency(temp, temp_size);
    
    // 모든 words 돌면서 temp와 비교하기
    for(int idx=0; idx<wordsSize; idx++){
        word_size = strlen(words[idx]);

        // 각 단어마다 counter dict 만들어서 저장하기 (단어마다 비교해야해서)
        Counter cur_word = countFrequency(words[idx], word_size);

        for(int j=0; j<temp_size; j++){
            // debug
            // printf("now char: %c , temp count: %d , cur_word count: %d \n", temp[j], tmp.count[temp[j]-'a'], cur_word.count[temp[j]-'a']);
            if(tmp.count[temp[j]-'a'] == cur_word.count[temp[j]-'a']){ // 해당 char의 빈도수 비교하기 
                isSame = true;
            }
            else{ // 한번이라도 틀리면 false하고 break (다음으로)
                isSame = false;
                break;
            }
        } // 다 같을 경우 단어 길이 체크 후 더 작으면 shortest string array에 담기
        if(isSame){
            if(word_size < min_len){
                min_len = word_size;
                shortest[shortest_idx++] = words[idx];
            }
        }
    }
    // 마지막으로 담은 것 내보내기
    return shortest[shortest_idx-1];
}

#include <stdio.h>

// 가정: shortestCompletingWord 함수는 이미 정의되어 있다.

int main(){
    int words_size = 4;
    char* licensePlate = "1s3 PSt";
    char* words1[] = {"step", "steps", "stripe", "stepple"};

    char* result;
    result = shortestCompletingWord(licensePlate, words1, words_size);
    printf("The result is: %s\n", result);

    // 새로운 예제 추가
    char* licensePlate2 = "1s3 456";
    char* words2[] = {"looks","pest","stew","show"};
    
    result = shortestCompletingWord(licensePlate2, words2, words_size);
    printf("The result is: %s\n", result);

    return 0;
}
