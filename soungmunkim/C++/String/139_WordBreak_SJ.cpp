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
#include <iostream>
#include <vector>
#include <string>
#include <cstring>

bool wordBreak(std::string s, std::vector<std::string>& wordDict) {
    std::vector<bool> visited(s.length() + 1, false);
    std::vector<int> q(s.length() + 1, 0);
    int front = 0, rear = 0;
    q[rear++] = 0;

    while (front < rear) {
        int start = q[front++];
        if (start == s.length()) {
            return true;
        }
        for (int end = start + 1; end <= s.length() + 1; end++) {
            if (!visited[end]) {
                for (const std::string& word : wordDict) {
                    if (word == s.substr(start, end - start)) {
                        q[rear++] = end;
                        visited[end] = true;
                    }
                }
            }
        }
    }

    return false;
}

int main() {
    std::string s = "applepenapple";
    std::vector<std::string> wordDict = {"apple", "pen"};

    if (wordBreak(s, wordDict)) {
        std::cout << "True" << std::endl;
    } else {
        std::cout << "False" << std::endl;
    }

    return 0;
}
