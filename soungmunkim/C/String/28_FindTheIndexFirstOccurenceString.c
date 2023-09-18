/*
[첫번째로 needle이 나온 index 반환하기]

(base) soungmunkim@gimseongmun-ui-MacBookPro String % gcc 28_FindTheIndexFirstOccurenceString.c -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test                                           
Enter a haystack: "leetcode"
Enter a needle: "leeto"
Result: -1

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Enter a haystack: "sadbutsad"
Enter a needle: "sad"
Result: 0

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Enter a haystack: sadbut
Enter a needle: sad
Result: 0
*/

#include<stdio.h>
#include<string.h>
#include<stdbool.h>


int strStr(char* haystack, char* needle){
    // 얼마큼 잘라서 볼 건지 size 정하기
    int window_size;

    // word 자체를 ==로 체크 못하므로 for loop 돌때 체크해야함
    bool isSame = false;
    window_size = strlen(needle);

    for(int i=0; i<strlen(haystack); i++){
        int length = window_size; //[i:i+window_size]
        char slice[300];

        strncpy(slice, &haystack[i], length);
        // printf("temp char: %s\n", slice);
        slice[length] = '\0';

        // printf("%d\n", strlen(slice));

        // word == word 인지 체크하는 방법
        for(int j=0; j<strlen(slice); j++){
            if(slice[j] == needle[j]) {
                isSame = true;
            }
            else {
                isSame = false;
                break;
            }
        }
        if (isSame == true)
            return i;
    }
    return -1;
}

// 불필요한 "" 나 , 제거하는 함수 
void removeExtraChars(char* str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (str[i] != '"' && str[i] != ',') {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

int main() {
    // 입력받는 게 string array가 아닌 word형태임 (char*)
    char s1[100];  // order 문자열을 저장하기 위한 배열
    char s2[100];    // 입력받을 문자열을 저장하기 위한 배열
    

    printf("Enter a haystack: ");
    scanf("%[^\n]s", s1);   // 줄바꿈 문자 전까지의 문자열을 입력받기 (공백 포함)
    getchar();  // 버퍼에 남아있는 줄바꿈 문자 제거

    printf("Enter a needle: ");
    scanf("%[^\n]s", s2);     // 줄바꿈 문자 전까지의 문자열을 입력받기 (공백 포함)

    removeExtraChars(s1);   // order에서 불필요한 문자 제거
    removeExtraChars(s2);     // str에서 불필요한 문자 제거

    int result = strStr(s1, s2);  // 문자열 정렬

    printf("Result: %d\n", result);  // 정렬된 결과 출력

    return 0;
}
