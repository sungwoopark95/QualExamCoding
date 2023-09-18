#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ---------------- 문자열에 문자를 추가하는 함수 ----------------- */
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
/* --------------------------------------------------------- */

/* ---------------- 문자열에 문자열을 추가하는 함수 ----------------- */
char* append_string(char* str, const char* append_str) {
    int len_str = (str != NULL) ? strlen(str) : 0;
    int len_append = (append_str != NULL) ? strlen(append_str) : 0;
    
    // 결과 문자열을 위한 메모리 할당
    char* new_str = (char*)malloc((len_str + len_append + 1) * sizeof(char));
    if (!new_str) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    // NULL 문자로 초기화 (이 부분이 추가되었습니다)
    memset(new_str, 0, (len_str + len_append + 1) * sizeof(char));

    // 원래의 문자열이 있다면 그것을 복사
    if (str) {
        strcpy(new_str, str);
    }

    // 추가 문자열을 결과 문자열의 끝에 추가
    strcpy(new_str + len_str, append_str);

    return new_str;
}
/* ----------------------------------------------------------- */

/* ---------------- 문장에서 특정 단어를 다른 단어로 대체하는 함수 ----------------- */
char* replace(char* str, const char* find, const char* replace) {
    // 결과 문자열을 저장할 포인터
    char* result;

    // 다음 복사 위치를 나타내는 포인터
    char* ins;

    // 임시 포인터
    char* tmp;

    // 입력 문자열의 길이, 찾을 문자열의 길이, 대체할 문자열의 길이 구하기
    int len_str = strlen(str);
    int len_find = strlen(find);
    int len_replace = strlen(replace);

    // 문자열 대체 횟수
    int count = 0;

    // 대체할 문자열이 없으면 원본 문자열을 복사한 후 반환
    if (len_find == 0) {
        result = (char*)malloc(len_str + 1);
        strcpy(result, str);
        return result;
    }

    // 찾을 문자열의 등장 횟수 계산
    ins = str;
    while ((tmp = strstr(ins, find)) != NULL) {
        ins = tmp + len_find;
        count++;
    }

    // 결과 문자열을 위한 메모리 할당
    tmp = result = (char*)malloc(len_str + (len_replace - len_find) * count + 1);

    // 문자열 대체 수행
    while (count--) {
        ins = strstr(str, find);
        int len_front = ins - str;
        tmp = strncpy(tmp, str, len_front) + len_front;
        tmp = strcpy(tmp, replace) + len_replace;
        str += len_front + len_find;
    }

    // 나머지 문자열 복사
    strcpy(tmp, str);

    return result;
}
/* ---------------------------------------------------------------------- */

/* ---------------- 문장에서 특정 문자를 다른 문자로 대체하는 함수 ----------------- */
char* replace_char(char* str, char find, char replace) {
    int len_str = strlen(str);
    char* result = (char*)malloc(len_str + 1);
    if (!result) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < len_str; i++) {
        result[i] = (str[i] == find) ? replace : str[i];
    }
    result[len_str] = '\0';

    return result;
}
/* ---------------------------------------------------------------------- */

int main() {
    // append_char 테스트 - 빈 문자열
    char* str = NULL;
    str = append_char(str, 'H');
    str = append_char(str, 'i');
    printf("append_char: %s\n", str);
    free(str); // 할당된 메모리 해제

    // append_string 테스트 - 빈 문자열 아님
    char* hello = "Every One, ";
    hello = append_string(hello, "Hello");
    hello = append_string(hello, ", World!");
    printf("append_string: %s\n", hello);
    free(hello); // 할당된 메모리 해제

    // append_string 테스트 - 빈 문자열
    char* null = NULL;
    null = append_string(null, "Hello");
    null = append_string(null, ", World!");
    printf("append_string: %s\n", null);
    free(null); // 할당된 메모리 해제

    // replace 테스트
    char sentence[] = "I love apple. apple is delicious.";
    char* replaced_sentence = replace(sentence, "apple", "banana");
    printf("replace: %s\n", replaced_sentence);
    free(replaced_sentence); // 할당된 메모리 해제

    // replace_char 테스트
    char text[] = "apple";
    char* replaced_text = replace_char(text, 'a', 'o');
    printf("replace_char: %s\n", replaced_text);
    free(replaced_text); // 할당된 메모리 해제

    // replace 테스트
    char* sentence2 = "I love apple. apple is delicious.";
    char* replaced_sentence2 = replace(sentence, "apple", "banana");
    printf("replace: %s\n", replaced_sentence);
    free(replaced_sentence2); // 할당된 메모리 해제

    // replace_char 테스트
    char* text2 = "apple";
    char* replaced_text2 = replace_char(text, 'a', 'o');
    printf("replace_char: %s\n", replaced_text);
    free(replaced_text2); // 할당된 메모리 해제

    return 0;
}
