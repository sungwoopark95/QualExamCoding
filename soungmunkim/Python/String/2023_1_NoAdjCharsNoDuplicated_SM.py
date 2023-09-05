"""
(b) Implement a function bar(s) that returns a string t 
    in which no two adjacent characters are adjacent in s, 
    and s and t are different strings.
    When a character appears in s, t should contain it only once.
    When there is no such string t, it returns an empty string "".
    If there are multiple strings that satisfy the conditions,
    return any of them.
    
    print(bar("abccde"))    #[2,5,1,4,0,3] bdeac
    print(bar("abcde"))     #[2,0,4,1,3] bdeac
    print(bar("abc"))       # ""
    print(bar("abcdcef"))   #[0,2,4,6,1,3,5] bdafce
"""


"""
backtrack 함수 내에서 remaining_chars라는 리스트는 아직 순열에 포함되지 않은 문자들을 저장합니다. 
이를 통해 각 문자가 순열에 한 번만 사용되도록 합니다.

중복된 char은 하나만 포함하게 해야함
"""
def bar(s):
    
    # 순열을 생성하기 위한 재귀 함수 정의
    def backtrack(start):
        # 시작 인덱스가 원본 문자열의 길이와 같다면 (순열이 완성되었을 때)
        if start == len(origin_s):
            
            positions_match = True
            # (1) 생성된 순열에서 각 문자가 원본 문자열의 해당 위치와 다른지 확인
            for i in range(len(s)):
                if s[i] == origin_s[i]:
                    positions_match = False
                    break
            
            adjacent_positions_differ = True
            # (2) 생성된 순열에서 문자가 원본 문자열의 인접 문자와 동일한지 검사
            for i in range(1, len(s)-1):
                if s[i] == origin_s[i-1] or s[i] == origin_s[i+1]:
                    adjacent_positions_differ = False
                    break
                
            # 두 조건을 모두 만족한다면 해당 순열 반환
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

    # 중복 문자 제거
    unique_s = ''.join(sorted(set(s), key=s.index))
    # 원본 문자열 복사
    origin_s = unique_s[:]
    # 순열 생성을 위한 리스트. 처음에는 원본 문자열로 초기화.
    s = list(unique_s)

    # 순열 생성 시작
    t = backtrack(0)

    # 결과 문자열이 있다면 반환, 없다면 빈 문자열 반환
    if t:
        return t
    else:
        return ""