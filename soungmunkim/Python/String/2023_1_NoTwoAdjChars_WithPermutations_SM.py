"""
[ 주변 char이 겹치지 않는 또 다른 string 구현하기 ]
Consider a string that contains only lower-case alphabets.
The number of characters in a does not exceed 10.

(a) Implement a function foo(s) that returns a string t 
    in which no two adjacent characters are adjacent in s, and
    t contains exactly the same number of characters as that of s.
    Moreover, when a character appears in s, t should contain it as often as in s.
    When there is no such string t, it returns an empty string "".
    If there are multiple strings that satisfy the conditions, return any of them.

TestCase
print(foo("abccde"))    #[0,2,4,1,3,5] acdbce
print(foo("abcde"))     #[0,2,4,1,3] acebd
print(foo("abc"))       # ""
print(foo("abcdcef"))   #[0,2,4,6,1,3,5] accfbde
"""


"""
permutation을 사용하여 여러 다양한 swap들 중 인접하지 않은 새로운 조합 찾는 방식

from itertools import permutations # 이렇게도 사용 가능
for perm_str in permutations(s):
    # 문자열로 변환
    perm_str = ''.join(perm_str
"""
def foo(s):
    # 재귀 함수로 순열을 생성하는 내부 함수
    def backtrack(start):
        # 시작 인덱스가 문자열의 길이와 같을 때 (하나의 순열이 완성되었을 때)
        if start == len(s):
            
            positions_match = True
            # (1) 순열 내 각 위치의 문자가 원본 문자열과 동일한지 확인
            for i in range(len(s)):
                if s[i] == origin_s[i]:
                    positions_match = False
                    break
            
            adjacent_positions_differ = True
            # (2) 순열 내 각 위치의 문자가 원본 문자열의 이웃 문자와 동일한지 확인
            for i in range(1, len(s)-1):
                if s[i] == origin_s[i-1] or s[i] == origin_s[i+1]:
                    adjacent_positions_differ = False
                    break
                
            # 위의 두 조건을 모두 만족하면 현재 순열을 반환
            if positions_match and adjacent_positions_differ:
                return ''.join(s)
        
        # 현재 인덱스부터 마지막 인덱스까지 각 문자를 시작 인덱스와 바꿔가며 순열을 생성
        for i in range(start, len(s)):
            # 현재 시작 인덱스와 i 인덱스 위치의 문자를 교환 (스왑)
            s[start], s[i] = s[i], s[start]
            
            # 시작 인덱스를 1 증가시켜 재귀 호출하여 순열 생성 계속
            result = backtrack(start + 1)
            
            # 만약 결과 문자열이 반환되었다면, 더 이상의 순열 생성을 중단하고 결과 반환
            if result:
                return result
            
            # 이전 상태로 문자열을 복원하기 위해 다시 문자 위치를 교환 (백트래킹)
            s[start], s[i] = s[i], s[start]
        
    # 원본 문자열 복사
    origin_s = s[:]
    # 문자열을 리스트로 변환하여 문자 위치 교환을 용이하게 함
    s = list(s)
    
    # 순열 생성 시작
    t = backtrack(0)
    
    # 결과 문자열이 있다면 반환, 없다면 빈 문자열 반환
    if t:
        return t
    else:
        return ""
    
    
################## 더 간단하게 푸는 법 ###################    
# def foo(s):
#     # chars 개수가 4개 이하이면 계속 two adjacent는 생길 수 밖에 없음
# # <주의> !! 인접이란 character 기준이 아니라 말 그대로 인접한 애들이기때문에 Index 기준으로 생각해야 함 !!
#     if len(s) < 5:
#         return ""

#     else:
#         odds = []
#         evens = []
#         for i in range(0, len(s), 2):
#             evens.append(s[i])    
#         for i in range(1, len(s), 2):
#             odds.append(s[i])   

#         # print(evens + odds) // list끼리는 더하기로 합칠 수 있음
#         new_str_lst = evens + odds
#         # print(new_str_lst)
        
#         # t = ""
#         # for ch in new_str_lst:
#         #     t = t + ch
        
#         t = ''.join(new_str_lst) # list안에 있는 char 합쳐서 str로 내보내기
#         return t


