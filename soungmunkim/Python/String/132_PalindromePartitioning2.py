"""
[palindrome partitions 중에 가장 적은 cut 수 구하기]

Given a string s, 
partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

Example 1:
Input: s = "aab"
Output: 1
Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.

Example 2:
Input: s = "a"
Output: 0

Example 3:
Input: s = "ab"
Output: 1
"""

# 복잡한 문자열도 palindrome인지 체크함
def is_palindrome(s: str) -> bool:
    # 알파벳과 숫자만을 포함하는 새로운 문자열 생성
    cleaned_string = ''.join(char.lower() for char in s if char.isalnum())
    
    # cleaned_string을 뒤집은 문자열
    reversed_string = cleaned_string[::-1]
    
    return cleaned_string == reversed_string

# def palindrome(s: str):
#     # 문자열이 회문인지 확인하는 함수
#     return s == s[::-1]

# 모든 substring palindrome partition 찾기
def palindrome_partition(s: str):
    # 문자열의 모든 회문 파티션을 찾는 함수
    result = []
    path = []

    def backtrack(start):
        # 현재 위치가 문자열의 끝이라면, path를 결과에 추가
        if start == len(s):
            # print("path: ", path)
            result.append(list(path))
            return

        # 현재 위치에서 시작하는 모든 부분 문자열에 대해
        for end in range(start, len(s)):
            
            # 현재 부분 문자열이 회문이라면
            if is_palindrome(s[start:end+1]):
                
                # 이 부분 문자열을 path에 추가하고
                path.append(s[start:end+1])

                # 다음 부분 문자열을 위해 재귀 호출
                backtrack(end+1)
                
                # 백트래킹
                path.pop()

    backtrack(0)

    return result

def mincut(s:str):
    partitions = palindrome_partition(s)
    # 가장 길이가 작은 partitions 찾기
    min_len = float('inf')
    for i in range(len(partitions)):
        if len(partitions[i]) < min_len:
            min_len = len(partitions[i])
            
    #cut는 그 길이 -1 
    min_cut = min_len -1
    
    return min_cut

