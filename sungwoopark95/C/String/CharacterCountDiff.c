/*
Sum of Beauty of all substring

[최대 char 빈도수 - 최소 char 빈도수 = beauty of string]
The beauty of a string is the difference in frequencies between the most frequent and least
frequent characters.
For example, the beauty of "abaacc" is 3 - 1 = 2 .
Given a string s , return the sum of beauty of all of its substrings.
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int beautySum(char * s){
    int length = 0;
    while (s[length] != '\0') {
        length++;
    }

    int freq_length = 'z' - 'a' + 1;
    // printf("%d\n", freq_length);
    int beauty = 0;
    for (int i=0;i<length;i++) {
        int freq[freq_length];
        for (int i=0;i<freq_length;i++) {
            freq[i] = 0;
        }
        for (int j=i;j<length;j++) {
            freq[s[j]-'a']++;
            int max = -1; int min = 1000;
            for (int k=0;k<freq_length;k++) {
                if (max < freq[k]) {
                    max = freq[k];
                }
                if (min > freq[k] && freq[k] != 0) {
                    min = freq[k];
                }
            }
            beauty += (max-min);
        }
    }
    // printf("%d\n", beauty);
    return beauty;
}

int main() {
    char s[300];

    printf("Please enter a string: ");
    scanf("%s", s);
    // char* s = "aabcb"; 
    printf("%d\n", beautySum(s));

    return 0;
}