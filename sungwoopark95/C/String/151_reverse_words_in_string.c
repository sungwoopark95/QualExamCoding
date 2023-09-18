#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 10000

int split(char* s, char** word_list){
    // initialize the word list
    for (int i=0;i<MAXSIZE;i++) {
        word_list[i] = (char*)malloc(MAXSIZE * sizeof(char));
    }
    int word_idx = 0;
    int i = 0;
    int wordlen = 0;
    char* word = (char*)malloc(MAXSIZE * sizeof(char));
    while (s[i] != '\0') {
        if (s[i] == 32) {
            if (wordlen > 0) {
                word_list[word_idx++] = word;   
            }
            word = (char*)malloc(MAXSIZE * sizeof(char));
            wordlen = 0;
        } else {
            word[wordlen++] = s[i];
        }
        i++;
    }
    if (wordlen > 0) {
        word_list[word_idx++] = word;
    }
    free(word);
    return word_idx;
}

char* reverseWords(char* s) {
    char** word_list = (char**)malloc(MAXSIZE * sizeof(char*));
    int len = split(s, word_list);
    char* ans = (char*)malloc(MAXSIZE * sizeof(char));
    for (int i=0;i<len;i++) {
        if (i > 0) {
            strcat(ans, " ");
        }
        strcat(ans, word_list[len-i-1]);
    }

    for (int i=0;i<len;i++) {
        free(word_list[i]);
    }
    free(word_list);
    return ans;
}

int main() {
    char* s = "  hello world  ";

    // char** word_list = split(s);
    // for (int i=0;i<4;i++) {
    //     printf("%s\n", word_list[i]);
    // }

    char* ans = reverseWords(s);
    printf("%s\n", ans);
    free(ans);
    return 0;
}