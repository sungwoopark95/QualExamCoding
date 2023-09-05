"""
[Palindrome Partitioning]
string이 palindrome substring으로 다 나눠질 수 있다면 그 palindrome들 각 list에 저장하기

Given a string s, partition s such that every substring of the partition is a palindrome. 
Return all possible palindrome partitioning of s.

Example 1:
Input: s = "aab"
Output: [["a","a","b"],["aa","b"]]

Example 2:
Input: s = "a"
Output: [["a"]]
"""

def palindrome(s: str):
    # 문자열이 회문인지 확인하는 함수
    return s == s[::-1]


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
            if palindrome(s[start:end+1]):
                
                # 이 부분 문자열을 path에 추가하고
                path.append(s[start:end+1])

                # 다음 부분 문자열을 위해 재귀 호출
                backtrack(end+1)
                
                # 백트래킹
                path.pop()

    backtrack(0)
    return result