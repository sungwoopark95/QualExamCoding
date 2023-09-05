/*
[겹치지 않는 char에서 가장 긴 substring 찾기]
!!!! C 버전이랑 똑같음 !!!!

Given a string s, find the length of the longest substring without repeating characters.

Example 1:
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

Example 2:
Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Example 3:
Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.

(base) soungmunkim@gimseongmun-ui-MacBookPro String % gcc 3_LongestSubstringNoRepeating_SM.c -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test                                        
Please enter a string: abcabcbb
3
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Please enter a string: bbbbb
1
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Please enter a string: pwwkew
3
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// in 함수 구현하기 (word 안 에서 특정 ch 있는지 찾기)
bool in(char* word, int word_idx, char ch){
    for(int i = 0; i < word_idx; i++){
        // 문자 비교할때는 directly 비교하면 됨!
        if (word[i] == ch){
            return true;
        }
    }
    return false;
}

int lengthOfLongestSubstring(char* s){
    int start = 0;
    int longest = 0;
    char word[300] = {0};
    int word_idx = 0;

    while(start != strlen(s)){
        for(int i = start; i<strlen(s); i++){
            if(!in(word, word_idx, s[i])){
                word[word_idx] = s[i];
                word_idx++;
            }
            else{
                start ++;
                if (longest < word_idx){
                    longest = word_idx;
                }

                char word[300] = {0}; // memset(word, 0, sizeof(word));  // Reset the word
                word_idx = 0;
                break;
            }
        }
    }
    return longest;
}

int main() {
    char s[300];

    printf("Please enter a string: ");
    scanf("%s", s);

    int ans = lengthOfLongestSubstring(s);

    printf("%d\n", ans);

    return 0;
}
