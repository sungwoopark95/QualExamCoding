/*
[Find word in a sentence]
문장 내에서 단어의 등장 위치를 찾는 함수 find word 를 작성하라. 
문장에서 단어는 공백, 쉼표(,), 및 마침표 (.)로 구분된다. 
또한, 단어가 일치함을 확인할 때 대소문자는 구분하지 않는다. 
주어진 단어가 문장 내에서 몇번째 단어로 등장하는지 그 위치들을 구해 정수의 리스트로 반환한다 

TestCase)
s = "Some feelings are shallow, some feelings are deep. Some make us smile, some make us weap."
find_word s, "feelings"
find_word s, "FeelinGs"
find_word s, "some"
find_word s, "python"
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h> 

// 대소문자를 구분하지 않고 두 문자열이 같은지 확인하는 함수
bool same(const char* input, const char* target) {
    // 두 문자열의 각 문자를 비교하기 위한 반복문
    while (*input && *target) {
        // tolower 함수를 사용하여 대소문자 구분 없이 비교
        if (tolower((unsigned char)*input) != tolower((unsigned char)*target)) {
            return false;
        }
        input++;
        target++;
    }
    // 두 문자열이 모두 끝났는지 확인하여 같은 길이인지 확인
    return (*input == '\0' && *target == '\0');
}

int main(int argc, char* argv[]){
    // 입력된 인자의 수가 부족한 경우 사용법 출력
    if (argc < 3) {
        printf("사용법: %s <문장> <타겟_단어>\n", argv[0]);
        return 1;
    }

    char word[300] = {0};  // 단어를 저장할 배열, 0으로 초기화
    char* input = argv[1];  // 첫 번째 인자 (문장)
    char* target_word = argv[2];  // 두 번째 인자 (타겟 단어)
    int size = strlen(input);
    int idx = 0;  // 단어의 위치를 나타내는 변수
    int word_index = 0;  // 현재 단어의 길이를 나타내는 변수

    bool first_match = true;  // 첫 번째 일치하는 단어를 판별하기 위한 변수 (첫번째는 숫자부터 들어가야 하므로)

    printf("[");  // 결과의 시작 부분 출력

    for (int i = 0; i <= size; i++){
        // 현재 문자가 공백, null 문자, 쉼표, 마침표가 아닌 경우 단어 배열에 추가
        if (input[i] != ' ' && input[i] != '\0' && input[i] != ',' && input[i] != '.'){
            word[word_index++] = input[i];
        }
        else {
            word[word_index] = '\0';  // 단어를 null로 종료
            if (word_index > 0) { // 단어만 index 올리기
                if (same(word, target_word)) {
                    if (!first_match) {
                        printf(", ");  // 첫 번째 일치하는 단어가 아니면 콤마와 공백 출력 
                    }
                    printf("%d", idx);
                    first_match = false;  // 첫 번째 일치하는 단어 판별 변수 업데이트
                }
                idx++;  // 단어의 위치 증가
            }
            word_index = 0;  // 다음 단어를 위해 인덱스 재설정
        }
    }

    printf("]\n");
    return 0;
}