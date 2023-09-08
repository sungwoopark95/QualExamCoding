"""
[word dict가 s의 segmentation이 되어야 true]
!! string replace 사용함 !!

Given a string s and a dictionary of strings wordDict, 
    return true if s can be segmented into a space-separated sequence of one or more dictionary words.

Note that the same word in the dictionary may be reused multiple times 
    in the segmentation.

Example 1:
Input: s = "leetcode", wordDict = ["leet","code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".

Example 2:
Input: s = "applepenapple", wordDict = ["apple","pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as 
    "apple pen apple".
Note that you are allowed to reuse a dictionary word.

Example 3:
Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: false
"""


from typing import List

def wordBreak(s:str, wordDict:List[str]) -> bool:
    # string이 있을때까지 반복
    while s:
        # dict 돌아가면서 해당 단어가 s에 있으면 빈칸으로 대체
        for i in range(len(wordDict)):
            if wordDict[i] in s:
                s = s.replace(wordDict[i], '')
            # 같은 단어가 더이상 없는데 s가 남아있을 경우 False 리턴
            else:
                return False
    return True

if __name__ == "__main___":
    s = "catsandog"
    wordDict = ["cats","dog","sand","and","cat"]
    result = wordBreak(s, wordDict)
    print(result)
    
   