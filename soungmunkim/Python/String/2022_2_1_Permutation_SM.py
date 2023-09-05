"""
[string으로 permutation 구하기]
# TestCase
>>> s = "abc"
>>> str_perm(s)
>>> ["abc", "acb", "bac", "bca", "cab", "cba"]

>>> s = "abb"
>>> str_perm(s)
>>> ["abb", "aba", "bba"]
"""

def str_perm(s):
    # 재귀적으로 호출되는 내부 함수
    def backtrack(start):
        # 시작 인덱스가 문자열의 길이와 같아지면, 현재 문자열의 순열을 저장
        if start == len(s):
            permutations.append(''.join(s))
            return
        
        # 시작 인덱스부터 문자열의 끝까지 루프를 실행
        for i in range(start, len(s)):
            # 현재 시작 인덱스와 루프의 인덱스 위치의 문자를 교환 (스왑)
            s[start], s[i] = s[i], s[start]
            
            # 현재 시작 인덱스를 제외한 나머지 문자열에 대해 순열을 생성하기 위해 재귀적으로 호출
            backtrack(start + 1)
            
            # 이전 상태로 문자열을 복원하기 위해 다시 문자 위치를 교환 (백트래킹)
            s[start], s[i] = s[i], s[start]
    
    # 문자열을 문자 리스트로 변환
    s = list(s)
    # 생성된 순열을 저장할 리스트 초기화
    permutations = []
    # 처음에는 0번 인덱스부터 순열 생성을 시작
    backtrack(0)
    # 생성된 모든 순열을 반환
    return permutations
