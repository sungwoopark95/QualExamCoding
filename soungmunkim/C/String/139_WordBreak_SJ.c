/*
Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of one or more dictionary words.

Note that the same word in the dictionary may be reused multiple times in the segmentation.

Example 1:

Input: s = "leetcode", wordDict = ["leet","code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".


Example 2:

Input: s = "applepenapple", wordDict = ["apple","pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
Note that you are allowed to reuse a dictionary word.


Example 3:

Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: false
 

Constraints:

1 <= s.length <= 300
1 <= wordDict.length <= 1000
1 <= wordDict[i].length <= 20
s and wordDict[i] consist of only lowercase English letters.
All the strings of wordDict are unique.
*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool wordBreak(char *s, char **wordDict, int wordDictSize) {
    bool *visited = calloc(strlen(s) + 1, sizeof(bool));
    int *q = malloc(sizeof(int)*(strlen(s)+1));
    int front = 0, rear = 0;
    q[rear++] = 0; // this is equivalent to q[rear] = 0; rear = rear + 1;

    while (front < rear) {
        int start = q[front++];
        if (start == strlen(s)) {
            free(visited);
            free(q);
            return true;
        }
        for (int end = start + 1; end <= strlen(s) + 1; end++) {
            if (!visited[end]) {
                for (int i = 0; i < wordDictSize; i++){
                    if (strstr(wordDict[i], strndup(s+start, end - start))){
                        q[rear++] = end;
                        visited[end] = true;
                    }
                }
            }
        }
    }

    free(visited);
    free(q);
    return false;
}

int main() {
    char *s = "leetcode";
    char *wordDict[] = {"leet", "code"};
    int wordDictSize = 2;

    if (wordBreak(s, wordDict, wordDictSize)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}
