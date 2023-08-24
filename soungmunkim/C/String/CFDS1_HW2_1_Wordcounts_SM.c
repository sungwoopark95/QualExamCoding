/*
[문장에서 총 단어 수와 각 단어 빈도 수 찾기]

[결과]
Given string: "Doubt thou the stars are fire Doubt that the sun doth move Doubt truth to be a liar But never doubt I love"

unique number of words: 23
Word "Doubt" appears 3 times.
Word "thou" appears once.
Word "the" appears twice.
Word "stars" appears once.
Word "are" appears once.
Word "fire" appears once.
Word "that" appears once.
Word "sun" appears once.
Word "doth" appears once.
Word "move" appears once.
Word "truth" appears once.
Word "to" appears once.
Word "be" appears once.
Word "a" appears once.
Word "liar" appears once.
Word "But" appears once.
Word "never" appears once.
Word "doubt" appears once.
Word "I" appears once.
Word "love" appears once.
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_WORDS 100  // 최대 단어 수를 100으로 정의

// 단어와 그 출현 횟수를 저장하는 구조체를 정의
typedef struct {
    char word[50];  // 단어를 저장
    int count;      // 해당 단어의 출현 횟수를 저장
} Word;

void wordcount(char sentences[]);
bool same(const char* input, const char* target);

int main() {
    char sentences[] =
    "Doubt thou the stars are fire "
    "Doubt that the sun doth move "
    "Doubt truth to be a liar "
    "But never doubt I love";

    wordcount(sentences);  // 단어 출현 횟수를 계산 및 출력하는 함수 호출

    return 0;
}

/*
[만약 sentences를 사용자로부터 Input으로 받을 경우 ]
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_WORDS 100  // 최대 단어 수를 100으로 정의
#define MAX_SENTENCE_LENGTH 1000  // 문장의 최대 길이를 1000으로 정의

typedef struct {
    char word[50];
    int count;
} Word;

void wordcount(char sentences[]);
bool same(const char* input, const char* target);

int main() {
    char sentences[MAX_SENTENCE_LENGTH];  // 사용자로부터 입력 받을 문자열을 저장할 배열

    printf("Enter the text: ");
    fgets(sentences, sizeof(sentences), stdin);  // 표준 입력으로부터 문자열을 읽어서 sentences에 저장
    sentences[strcspn(sentences, "\n")] = '\0';  // fgets는 줄바꿈 문자도 읽기 때문에, 이를 문자열 끝으로 대체

    wordcount(sentences);

    return 0;
}

void wordcount(char sentences[]){
    // ... (나머지 코드는 동일)
}

*/

// 주어진 문자열에서 각 단어의 출현 횟수를 계산하는 함수
void wordcount(char sentences[]){
    char word[50];  // 현재 처리 중인 단어를 저장하는 배열
    Word words[MAX_WORDS] = {0};  // 단어와 그 출현 횟수를 저장하는 배열
    int unique_words = 0;  // 현재까지 발견된 unique 단어의 수
    int total_words = 0; // 문장에 있는 총 단어 수 (중복 포함)

    char* token = strtok(sentences, " ");  // 첫 번째 단어 추출

    while (token != NULL) {  // 단어가 더 이상 없을 때까지 반복
        total_words++; // 총 단어 수 체크하기

        bool found = false;
        for (int i = 0; i < unique_words; i++) {
            // 이미 발견된 단어와 현재 단어가 같은지 확인

            if (same(words[i].word, token)) {
                words[i].count++;  // 같은 단어의 출현 횟수 증가
                found = true;
                break;
            }
        }
        // 현재 단어가 처음 발견된 단어인 경우
        if (!found) {
            strcpy(words[unique_words].word, token);  // 단어 copy해서 words에 저장
            words[unique_words].count = 1;  // 출현 횟수 초기화
            unique_words++;  // 발견된 단어 수 증가
        }
        token = strtok(NULL, " ");  // 다음 단어 추출
    }

    // 결과 출력
    printf("Total number of words: %d\n", total_words);  // 총 단어수
    for (int i = 0; i < unique_words; i++) {
        printf("Word \"%s\" appears %d times.\n", words[i].word, words[i].count);
    }
}

// 두 문자열이 대소문자 구분 없이 같은지 확인하는 함수
bool same(const char* input, const char* target) {
    while (*input && *target) {
        if (tolower((unsigned char)*input) != tolower((unsigned char)*target)) {
            return false;
        }
        input++;
        target++;
    }
    // 두 문자열의 끝까지 도달했는지 확인하여 같은 길이인지 판별
    return (*input == '\0' && *target == '\0');
}

