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