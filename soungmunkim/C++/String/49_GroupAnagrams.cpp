/*
[anagrams 그릅별로 묶기]
Anagrams: 다른 순서로 문자 바꾸면 새로운 문자열이 되는 것 (eat -> ate)

Given an array of strings strs, group the anagrams together. 
You can return the answer in any order.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, 
    typically using all the original letters exactly once.

(base) soungmunkim@gimseongmun-ui-MacBookPro String % g++ -std=c++17 49_GroupAnagrams.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test    
문자열 배열을 입력하세요 (예: ["단어1", "단어2"]): ["eat","tea","tan","ate","nat","bat"]
Output:
["ate", "eat", "tea"], ["nat", "tan"], ["bat"]

문자열 배열을 입력하세요 (예: ["단어1", "단어2"]): [""]
Output:
[""]

Example 3:
Input: strs = ["a"]
Output: [["a"]]
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

/*--------------- char dictionary ----------------*/
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

// 두 Counter 객체가 동일한지 확인하는 함수 (두 char frequency 체크)
bool isEqual(Counter c1, Counter c2) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (c1.count[i] != c2.count[i]) {
            return false;
        }
    }
    return true;
}

// int str size 안 쓰고 사용하는 방법
// strlen은 \0 포함해야함 (끝 표시)
bool is_anagram(char* s1, char* s2){
    int len_s1 = strlen(s1);
    int len_s2 = strlen(s2);

    // 두 str 길이가 다르면 
    if(len_s1 != len_s2)
        return false;
    
    // 두 문자열의 문자 빈도수를 계산합니다.
    Counter char1_dct = countFrequency(s1, len_s1);
    Counter char2_dct = countFrequency(s2, len_s2);

    // 두 문자열의 문자 빈도수가 동일한지 확인
    if(!isEqual(char1_dct, char2_dct))
        return false;

    return true;
} 
// /*------------- str array sorting하기 ------------*/

// swap은 무조건 주소값으로 접근! 함수 끝나도 바꾼 값 유지 
// int &a처럼 함수 인자를 바로 넘겨주는 것은 C++에서만 가능
void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 오른차순 정렬
void bubbleSort(char arr[][100], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            // strcmp는 두 문자열을 비교하며, 첫 번째 문자열이 두 번째 문자열보다 사전적으로 크면 양의 값을 반환합니다.
            if (strcmp(arr[j], arr[j+1]) > 0) {
                // 두 문자열 직접 교환
                char temp[100]; // 임시 문자열 변수
                strcpy(temp, arr[j]);       // temp에 arr[j] 복사
                strcpy(arr[j], arr[j+1]);   // arr[j]에 arr[j+1] 복사
                strcpy(arr[j+1], temp);     // arr[j+1]에 temp 복사
            }
        }
    }
}

// 아나그램 그룹을 찾는 함수
char*** anagram(char** s, int len_s, int* num_groups){
    int i=0;

    // 각 문자열이 이미 검사되었는지 여부를 저장하는 배열 선언
    bool checked[len_s];
    // checked 배열을 false로 모두 초기화. 여기서 false는 0, true는 1로 취급합니다.
    memset(checked, false, sizeof(checked));  // 모든 원소를 false로 초기화

    // 결과를 저장할 3중 포인터에 메모리 할당. (문자열 그룹 배열)
    char*** ans = (char***)malloc(sizeof(char**) * len_s); // c++에서는 이렇게 해야함
    for(int i = 0; i < len_s; i++) {
        ans[i] = (char**)malloc(sizeof(char*) * len_s); // C++에서는 이렇게해야함
        for(int j = 0; j < len_s; j++) {
            // c++에서는 이렇게 해야함
            ans[i][j] = (char*)malloc(sizeof(char) * 100); // 각 문자열은 최대 길이 100으로 가정
        }
    }
    *num_groups = 0; // 아나그램 그룹의 개수를 0으로 초기화

    // 모든 문자열을 순회하며 아나그램 그룹을 찾습니다.
    while(i < len_s){
        // 현재 문자열이 이미 검사되었다면 다음 문자열로 넘어갑니다.
        if(checked[i]) {
            i++;
            continue;
        }

        // 현재 아나그램 그룹을 저장할 배열
        char cur_group[len_s][100];
        int cur_idx = 0;

        // 현재 문자열을 그룹에 추가
        strcpy(cur_group[cur_idx], s[i]);
        cur_idx++;
        checked[i] = true;  // 현재 문자열을 검사했다고 표시

        // 나머지 문자열들 중 현재 문자열과 아나그램인 것을 찾아 그룹에 추가
        for(int idx=i+1; idx<len_s; idx++){
            if(is_anagram(s[i], s[idx])){
                strcpy(cur_group[cur_idx++], s[idx]);
                checked[idx] = true;  // 아나그램으로 판별된 문자열도 검사했다고 표시
            }
        }

        // 아나그램 그룹 내의 문자열들을 알파벳 순으로 정렬
        bubbleSort(cur_group, cur_idx);

        // 결과 배열(ans)에 아나그램 그룹을 추가
        for(int k = 0; k < cur_idx; k++){
            strcpy(ans[*num_groups][k], cur_group[k]);
        }
        (*num_groups)++;  // 아나그램 그룹의 개수 증가

        i++;
    }
    return ans;  // 아나그램 그룹 배열 반환
}
// [""] 이런 빈 문자열 체크하기 위해 필요함 (strok는 빈 문자열 인식 잘 못 함)
char* is_empty_string(char* str) {
    while (*str) {
        if (*str == '[' || *str == ' ' || *str == '\t') {
            str++;
        } else if (*str == '\"') {
            if (*(str+1) == '\"') {
                return str;  // 빈 문자열의 시작 위치를 반환
            }
            return NULL;
        } else {
            return NULL;
        }
    }
    return NULL;
}

// 메인 함수
int main() {
    char input[1000];
        // 사용자에게 문자열 배열을 입력받습니다.
        printf("문자열 배열을 입력하세요 (예: [\"단어1\", \"단어2\"]): ");
        fgets(input, 1000, stdin);

        input[strcspn(input, "\n")] = 0;  // 개행 문자 제거

        char* token;
        int count = 0;
        char* strs[101];  // 최대 100개의 문자열 + NULL 포인터를 저장하기 위한 배열

        // 입력이 [""]인지 확인
        char* empty_string_check = is_empty_string(input);

        if (empty_string_check) {
            strs[count] = (char*)malloc(1);
            strs[count][0] = '\0';
            count++;
        } else {

            // 입력 받은 문자열을 파싱하여 개별 단어를 추출합니다.
            token = strtok(input, "[\",\t\n\r ]");

            while (token != NULL) {
                strs[count] = (char*)malloc(strlen(token) + 1);
                strcpy(strs[count], token);
                count++;

                token = strtok(NULL, "[\",\t\n\r ]");
            }
        }
        strs[count] = NULL;  // 마지막에 NULL 포인터 추가

        int num_groups;
        char*** result = anagram(strs, count, &num_groups);

        // 출력하기 
        printf("Output:\n");
        for (int i = 0; i < num_groups; i++) {
            printf("[");
            // 빈 문자열 체크
            if (result[i][0][0] == '\0') {
                printf("\"\"");
            } else {
                for (int j = 0; j < count && result[i][j][0] != '\0'; j++) {
                    printf("\"%s\"", result[i][j]);
                    if (j < count - 1 && result[i][j+1][0] != '\0') {
                        printf(", ");
                    }
                }
            }
            printf("]");
            if(i != num_groups -1){
                printf(", ");
            }
        }
        printf("\n");

    return 0;
}
