"""
[substring의 반복이 string이 되는지 check]
Given a string s, 
    check if it can be constructed by taking a substring of it 
    and appending multiple copies of the substring together.

Example 1:
Input: s = "abab"
Output: true
Explanation: It is the substring "ab" twice.

Example 2:
Input: s = "aba"
Output: false

Example 3:
Input: s = "abcabcabcabc"
Output: true
Explanation: It is the substring "abc" four times or the substring "abcabc" twice.
"""

def repeatedSubstringPattern(s: str) -> bool:
    s_size = len(s) # 문자열 길이 저장

    for i in range(len(s)):
        # substring 뽑기 (첫번째 char 고정)
        # abab: a, ab, aba, abab
        temp = s[0:i+1]
        check = "" # 비교할 string
        # print('temp: ', temp)

        if temp == s: # substring이 그냥 string 그 자체라면 False
            return False
        idx = 0 # while loop 돌릴 index
        while idx < s_size:
            # 문자열 길이될때까지 계속 copy하면서 check
            check += temp 
            # print(check)
            if s == check:
                return True
            idx += len(temp)

    return False

#---------------------- 챗지피티 코드 --------------------------#
# def repeatedSubstringPattern(s: str) -> bool:
#     # 문자열의 길이를 저장합니다.
#     n = len(s)
    
#     # 1부터 문자열의 절반 길이까지 반복합니다.
#     for i in range(1, n // 2 + 1):
#         # 현재 i로 문자열 길이를 나누었을 때 나머지가 0이라면
#         if n % i == 0:
#             # 문자열의 처음부터 i만큼의 부분 문자열을 가져옵니다.
#             substring = s[:i]
            
#             # 예: 문자열 "abab"에서 i가 1일 때, s[:1]은 'a'입니다. 그러나 'a'를 반복하여 "abab"를 만들 수 없으므로 다음으로 넘어갑니다.
#             # i가 2일 때, s[:2]는 "ab"이며, 이것을 2번 반복하면 원래의 문자열 "abab"를 얻을 수 있습니다.
            
#             # 위에서 구한 부분 문자열을 n//i 만큼 반복하여 원래 문자열과 같은지 확인합니다.
#             if substring * (n // i) == s:
#                 return True  # 같다면 True를 반환합니다.

#     # 모든 가능한 부분 문자열로 반복하여 문자열을 생성해보았지만 원래 문자열을 만들 수 없다면 False를 반환합니다.
#     return False

# # 주어진 예제를 실행해봅니다.
# if __name__ == "__main__":
#     print(repeatedSubstringPattern("abab"))  # True
#     print(repeatedSubstringPattern("aba"))  # False
#     print(repeatedSubstringPattern("abcabcabcabc"))  # True
