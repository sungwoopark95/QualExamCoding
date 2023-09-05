"""
[젤 첫번째 문자를 포함해서 다 겹치는 가장 긴 char 찾기]
!!!첫번째 문자가 무조건 같아야 함!!!

Write a function to find the longest common prefix string amongst an array of strings.
If there is no common prefix, return an empty string "".

 

Example 1:
Input: strs = ["flower","flow","flight"]
Output: "fl"

Example 2:
Input: strs = ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.
"""
def longestCommonPrefix(strs):
    # 입력 리스트가 비어있을 때 빈 문자열 반환
    if not strs:
        return ""
    
    # 첫 번째 문자열을 기준으로 설정
    prefix = strs[0]
    
    # 첫 번째 문자열의 각 문자를 순회
    for i in range(len(prefix)):
        # 첫 번째 문자열의 i번째 문자
        char = prefix[i]
        
        # 다른 문자열들 순회
        for j in range(1, len(strs)):
            # i가 현재 문자열의 길이와 같거나, 현재 문자열의 i번째 문자가 char와 다를 경우
            if i == len(strs[j]) or strs[j][i] != char:
                return prefix[:i]  # 현재까지의 접두사 반환
    
    return prefix  # 모든 문자열이 첫 번째 문자열과 일치하면 첫 번째 문자열 반환


# def longestCommonPrefix(self, strs):
#     """
#     :type strs: List[str]
#     :rtype: str
#     """
#     min_len = float('inf')
#     for word in strs:
#         if min_len > len(word):
#             min_len = len(word)
            
#     dct = dict()
#     idx = 0
#     while idx != min_len:
#         for word in strs:
#             if idx not in dct:
#                 dct[idx] = word[idx]
#             else:
#                 if word[idx] == dct.get(idx):
#                     continue
#                 dct[idx]+= word[idx]
                
#         if len(dct.get(0)) > 1:
#             return ""  
#         if len(dct.get(idx))>1:
#             del dct[idx]            
#         idx += 1
        
#     # print(dct)
#     prefix = ""
#     for i in range(len(dct)):
#         if i not in dct:
#             prefix += " "
#         else:
#             prefix+=dct[i]
    
#     longest_prefix = ""
#     for pre in (prefix.split()):
#         if len(longest_prefix) < len(pre):
#             longest_prefix = pre
    
#     return longest_prefix
