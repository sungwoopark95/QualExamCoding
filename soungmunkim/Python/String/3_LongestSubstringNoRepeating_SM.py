"""
[겹치지 않는 char에서 가장 긴 substring 찾기]

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
"""

def lengthOfLongestSubstring(s):
    start = 0  # 시작 위치를 설정
    dct = dict()  # 현재 부분 문자열에 있는 문자를 저장하는 딕셔너리 초기화
    longest = 0  # 가장 긴 부분 문자열의 길이를 저장하는 변수 초기화

    while(start != len(s)):  # 시작 위치가 문자열의 끝에 도달할 때까지 반복
        # print(start)
        for i in range(start, len(s)):  # 시작 위치에서 문자열의 끝까지 반복
            if s[i] not in dct:  # 문자가 딕셔너리에 없으면
                dct[s[i]] = 1  # 딕셔너리에 문자를 추가
                
            else:  # 문자가 딕셔너리에 이미 있으면
                start += 1  # 시작 위치를 한 칸 이동
                # print(dct)
                # print(dct.keys())
                if longest < len(dct):  # 현재 딕셔너리의 길이가 최대 길이보다 길면
                    longest = len(dct)  # 최대 길이를 갱신
                dct = dict()  # 딕셔너리를 초기화
                break  # 내부 for 루프를 종료
        
    return longest  # 최대 길이를 반환
