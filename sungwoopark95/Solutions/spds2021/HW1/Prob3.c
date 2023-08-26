/*
# P3. 문자열 찾기 

문장 내에서 단어의 등장 위치를 찾는 함수 `find_word`를 작성하라. 문장에서 단어는 공백, 쉼표(,), 및 마침표(.)로 구분된다. 
또한, 단어가 일치함을 확인할 때 대소문자는 구분하지 않는다. 
주어진 단어가 문장 내에서 몇 번째 단어로 등장하는지 그 위치들을 구해 정수의 리스트로 반환한다 (위치는 0부터 시작한다). 
*/

#include <stdio.h>
#include <stdlib.h>

int len(char* s) {
    int length = 0;
    while (s[length] != '\0') {
        length++;
    }
    return length;
}

char lower_letter(char letter) {
    if (letter >= 'A' && letter <= 'Z') {
        return 'a' + (letter - 'A');
    }
    // 이미 lowercase인 경우 그대로 pass
    return letter;
}

void lower(char* s, char* converted) {
    // length: length of s
    for (int i=0;i<len(s);i++) {
        converted[i] = lower_letter(s[i]);
    }
}

int string_eq(char* s1, char* s2) {
    if (len(s1) != len(s2)) {
        return 0;
    }
    for (int i=0;i<len(s1);i++) {
        if (s1[i] != s2[i]) {
            return 0;
        }
    }
    return 1;
}

int find_word(int* ans, char* s, char* target) {
    char lower_target[len(target)];
    lower(target, lower_target);

    // split word and check
    int i = 0, j = 1, ans_idx = 0, cnt = 0;
    while (i < len(s) && j < len(s)) {
        char* word = (char*)malloc(sizeof(char));
        int k = 0; // k: word에 담길 index
        word[k++] = s[i];
        while (s[j] != ' ' && s[j] != ',' && s[j] != '.') {
            word[k++] = s[j++];
        }
        char lower_word[len(word)];
        lower(word, lower_word);
        if (string_eq(lower_word, lower_target)) {
            ans[cnt++] = ans_idx;
        }
        if (s[j] == ' ') { i = j+1; }
        else { i = j+2; }
        j = i+1;
        ans_idx++;
        free(word);
    }
    return cnt;
}

int main(int argc, char* argv[]) {
    char* s = argv[1];
    char* target = argv[2];

    int* word_index = (int*)malloc(sizeof(int));
    int total_length = find_word(word_index, s, target);

    printf("[");
    for (int i=0;i<total_length;i++) {
        if (i < total_length - 1) {
            printf("%d, ", word_index[i]);
        } else {
            printf("%d", word_index[i]);
        }
    }
    printf("]\n");

    free(word_index);
    return 0;
}
