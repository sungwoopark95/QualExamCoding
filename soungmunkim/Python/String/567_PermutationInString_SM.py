"""
[s1 string의 permutation 중 하나라도 s2의 substring이라면 True]
!! string이 길면 엄청 오래걸림 !!
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
    """
    :type s1: str
    :type s2: str
    :rtype: bool
    """
    def str_perm(s):
        def backtrack(start):
            if start == len(s):
                permutation_lst.append(''.join(s))
                return
        
            # 시작 인덱스부터 문자열의 끝까지 루프를 실행
            for i in range(start, len(s)):
                # 현재 시작 인덱스와 루프의 인덱스 위치의 문자를 교환 (스왑)
                s[start], s[i] = s[i], s[start]
                
                # 현재 시작 인덱스를 제외한 나머지 문자열에 대해 순열을 생성하기 위해 재귀적으로 호출
                backtrack(start + 1)
                
                # 이전 상태로 문자열을 복원하기 위해 다시 문자 위치를 교환 (백트래킹)
                s[start], s[i] = s[i], s[start]

        permutation_lst = []
        s = list(s1)
        backtrack(0)
        return permutation_lst

    permutations = str_perm(s1)
    for per in permutations:
        if per in s2:
            return True
    return False


    