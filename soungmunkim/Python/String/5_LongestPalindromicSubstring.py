"""
[부분 문자열중에 가장 긴 palindrome 찾기]
Given a string s, return the longest 
palindromic substring in s.
 
Example 1:

Input: s = "babad"
Output: "bab"
Explanation: "aba" is also a valid answer.

Example 2:
Input: s = "cbbd"
Output: "bb"
"""

# 회문을 판별하는 함수
def palindrome(s: str) -> bool:
    # 문자열 s와 s를 뒤집은 것이 같은지 비교하여 회문 여부를 반환
    return s == s[::-1]

# s 문자열 내에서 가장 긴 palindrome을 찾아 반환하는 함수
def longest_palindrome(s: str) -> str:
    n = len(s)  # 문자열 s의 길이
    max_palindrome = ""  # 현재까지 발견한 가장 긴 회문 저장 변수

    # 아래 두 개의 for 문은 모든 가능한 부분 문자열(substring)을 생성하기 위한 것
    for i in range(n):
        for j in range(i, n):
            # 부분 문자열 추출
            sub = s[i:j+1]
            
            # 해당 부분 문자열이 회문인지 확인 (palindrome 함수 사용)
            # 그리고 현재 발견한 회문이 이전까지의 최장 회문보다 긴 경우에만 업데이트
            if palindrome(sub) and len(sub) > len(max_palindrome):
                max_palindrome = sub
                
    return max_palindrome  # 가장 긴 회문 반환