
/*
[s를 k개의 palindrome으로 나눌 수 있다면 True 반환]
!! substring인 경우에만 해당됨 !!

1. palindrome이 될 수 있는지 체크하는 함수
2. palindrome이 될 수 있는 단어를 palindrome으로 만드는 함수 
3. 한 단어의 조합들이 Palindrome이 될 수 있는 단어들을 모은 partition 함수 
    -> backtracking 사용

(base) soungmunkim@gimseongmun-ui-MacBookPro String % c++ -std=c++17 1400_Construct_K_Palindrome.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test                                                
Enter a word: "annabelle"
Enter k: 2
True

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test                                                
Enter a word: "leetcode"
Enter k: 3
False

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Enter a word: "true"
Enter k: 4
True
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

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


// word가 팰린드롬으로 구성될 수 있는지 검사하는 함수
bool canPalindrome(const char* word) {
    // word의 문자 빈도를 계산
    Counter cnt = countFrequency(word);

    int odd = 0;
    // 각 알파벳에 대해 홀수 빈도를 가진 문자 수를 계산
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (cnt.count[i] % 2 == 1) {
            odd++;
        }
    }

    // 팰린드롬은 홀수 빈도 문자가 1개 이하로만 허용됨
    return odd <= 1;
}

// word를 이용해 팰린드롬을 만들고 반환하는 함수
char* constructPalindrome(const char* word) {

    // 만약 주어진 단어로 팰린드롬을 만들 수 없으면 "Not a palindrome" 반환
    if (!canPalindrome(word)) return "Not a palindrome";
    int len = strlen(word);  // 주어진 단어의 길이 계산

    // 주어진 단어의 길이만큼 메모리를 할당하여 결과 문자열을 저장할 공간 생성
    char* ans = (char*)malloc(len + 1);
    if (!ans) return NULL;  // 메모리 할당이 실패하면 NULL 반환

    // 결과 문자열을 0으로 초기화
    memset(ans, '\0', len + 1);

    // 주어진 단어에서 각 알파벳의 빈도수를 저장
    Counter cnt = countFrequency(word);

    
    
    // 만약 주어진 단어의 길이가 홀수라면
    if (len % 2 != 0) {
        int mid_idx = len / 2;  // 중앙 인덱스 계산
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            // 빈도수가 홀수인 알파벳을 찾아서 중앙에 배치
            if (cnt.count[i] % 2 != 0) {
                ans[mid_idx] = i + 'a';
                cnt.count[i]--;
                break;
            }
        }
    }
    int idx = 0;  // 결과 문자열에 문자를 배치할 위치를 가리키는 인덱스
    // 각 알파벳에 대해
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        // 해당 알파벳의 빈도수만큼 팰린드롬의 양쪽에 배치
        while (cnt.count[i] > 0) {
            ans[idx] = i + 'a'; // 팰린드롬의 앞쪽에 배치 (char가져온 것)
            cnt.count[i]--; 

            ans[len - idx - 1] = i + 'a';  // 팰린드롬의 뒤쪽에 배치
            cnt.count[i]--;

            idx++;  // 다음 위치로 이동

            if (idx >= len - idx - 1) 
                break;
        }
    }

    return ans;  // 결과 팰린드롬 문자열 반환
}


// 모든 가능한 조합을 만드는 백트래킹 함수
void backtrack(int start, const char* s, int* path_count, char path[1000][100], char result[1000][1000], int* result_count) {
    if (start == strlen(s)) {
        for (int i = 0; i < *path_count; i++) {
            strcat(result[*result_count], path[i]);
            if (i != *path_count - 1) 
                strcat(result[*result_count], ",");
        }
        (*result_count)++;
        return;
    }

    for (int end = start; end < strlen(s); end++) {
        char slice[300];
        // 현재 부분 문자열(slice) 추출
        strncpy(slice, &s[start], end - start + 1);
        slice[end - start + 1] = '\0';

        // 해당 부분 문자열이 팰린드롬으로 구성될 수 있다면 재귀 호출
        if (canPalindrome(slice)) {
            strcpy(path[*path_count], slice);
            (*path_count)++;
            backtrack(end + 1, s, path_count, path, result, result_count);
            (*path_count)--;
        }
    }
}

// s가 k 개의 팰린드롬 부분 문자열로 나눌 수 있는지 확인하는 함수
bool canConstruct(const char* s, int k) {
    int path_count = 0;
    char path[1000][100];
    char result[1000][1000] = {0};
    int result_count = 0;

    // 모든 가능한 조합 탐색
    backtrack(0, s, &path_count, path, result, &result_count);
    
    for (int i = 0; i < result_count; i++) {
        char *token;
        // temp pointer로 해당 list의 pointer 복제함
        char *tmp = strdup(result[i]);
        int partitions = 0;
        
        // 각 결과에서 팰린드롬 부분 문자열 개수를 계산
        token = strtok(tmp, ",");
        while (token != NULL) {
            partitions++;
            token = strtok(NULL, ",");
        }
        
        free(tmp);
        
        // 만약 팰린드롬 부분 문자열의 개수가 k와 같다면 true 반환
        if(partitions == k)
            return true;
    }
    return false;
}

// 따음표 제거하는 함수
char* removeQuotes(const char* input) {
    char* result = (char*)malloc(strlen(input) + 1);
    int idx = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] != '\"') result[idx++] = input[i];
    }
    result[idx] = '\0';

    return result;
}

int main() {
    char word[300];
    int k;

    printf("Enter a word: ");
    scanf("%s", word);

    char* cleanedWord = removeQuotes(word);
    
    printf("Enter k: ");
    scanf("%d", &k);

    printf("Palindrome looks like: %s\n", constructPalindrome(cleanedWord));
    if (canConstruct(cleanedWord, k))
        printf("True\n");
    else
        printf("False\n");

    free(cleanedWord);
    return 0;
}
