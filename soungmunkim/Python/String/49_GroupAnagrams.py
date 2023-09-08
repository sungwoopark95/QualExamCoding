"""
[anagrams 그릅별로 묶기]
Anagrams: 다른 순서로 문자 바꾸면 새로운 문자열이 되는 것 (eat -> ate)

Given an array of strings strs, group the anagrams together. 
You can return the answer in any order.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, 
    typically using all the original letters exactly once.

Example 1:
Input: strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]

Example 2:
Input: strs = [""]
Output: [[""]]

Example 3:
Input: strs = ["a"]
Output: [["a"]]
"""

from typing import List

# anangram 체크 함수 
def is_anagram(s1: str, s2: str):   
    char1_dct = dict()
    char2_dct = dict()
    if len(s1) != len(s2):  # 길이 체크
        return False
    
    # 비교할 두 단어의 char 빈도수 담은 dictionary 만들기
    for i in range(len(s1)):
        if s1[i] not in char1_dct:
            char1_dct[s1[i]] = 1
        else:
            char1_dct[s1[i]] += 1
    for i in range(len(s2)):
        if s2[i] not in char2_dct:
            char2_dct[s2[i]] = 1
        else:
            char2_dct[s2[i]] += 1

    # 두 단어 char 단어 비교
    for key, cnt in char1_dct.items():
        if key not in char2_dct: # 해당 char이 다른 단어에 없다면
            return False  
        if char2_dct[key] != cnt: # 해당 char 빈도가 다른 단어와 다르면
            return False
         
    return True

def anagrams(s:List[str])->List[str]:
    i = 0
    ans = []
    while i < len(s):
        # 비교할 현재 단어 선택
        cur_s = s[i]
        # 현재 그룹에 첫 단어 넣기 (초기화)
        cur_group = [cur_s]
        
        # 모든 단어들 다 돌면서 체크
        for idx in range(0, len(s)):
            # 현재 단어가 타겟 단어랑 같으면 넘어감
            if cur_s == s[idx]:
                continue
            # 서로 다른 단어인데 anagram이면 현재 그룹에 넣기
            if is_anagram(cur_s, s[idx]):
                cur_group.append(s[idx])
        
        # 최종 현재 그룹을 sorting한 후 ans에 안 들어간 그룹이라면 넣기
        cur_group = sorted(cur_group) # sorting 해서 체크하기     
        if cur_group not in ans:
            ans.append(cur_group)   
              
        i += 1 # 다음 타겟 단어로 넘어가기
    
    return ans

if __name__ == "__main__":
    strs = ["eat","tea","tan","ate","nat","bat"]
    result = anagrams(strs)
    print(result)
    
