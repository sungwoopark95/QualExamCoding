"""
[s1 string의 permutation 중 하나라도 s2의 substring이라면 True]
!! window 방법처럼 한문자씩 옮기면서 char 빈도 테이블 업뎃하기 !!
Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.

In other words, return true if one of s1's permutations is the substring of s2.

Example 1:

Input: s1 = "ab", s2 = "eidbaooo"
Output: true
Explanation: s2 contains one permutation of s1 ("ba").
Example 2:

Input: s1 = "ab", s2 = "eidboaoo"
Output: false
"""


def checkInclusion(s1, s2):
    from collections import Counter  # Counter를 사용하여 문자 빈도를 계산합니다.
    
    s1_counter = Counter(s1)  # s1의 각 문자에 대한 빈도수를 계산합니다.
    s2_counter = Counter(s2[:len(s1)])  # s2의 처음 len(s1) 길이의 문자에 대한 빈도수를 계산합니다.
    
    # s2의 나머지 부분을 확인하면서 슬라이딩 윈도우를 이동합니다.
    for i in range(len(s1), len(s2)):
        if s1_counter == s2_counter:  # s1의 문자 빈도와 현재 s2의 슬라이딩 윈도우 빈도가 동일한지 확인합니다.
            return True
        s2_counter[s2[i]] += 1  # 새로운 문자를 윈도우에 추가합니다.
        s2_counter[s2[i-len(s1)]] -= 1  # 가장 오래된 문자를 윈도우에서 제거합니다.
        
        # 만약 특정 문자의 빈도가 0이 되면, 그 문자를 빈도 테이블에서 제거합니다. (필요는 없음)
        if s2_counter[s2[i-len(s1)]] == 0:
            del s2_counter[s2[i-len(s1)]]
    
    # 마지막 윈도우에 대한 빈도가 s1의 빈도와 동일한지 다시 확인합니다.
    return s1_counter == s2_counter
