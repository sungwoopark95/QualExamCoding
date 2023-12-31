"""
정수 2개를 입력으로 받고, 아래 조건을 만족하는 리스트를 리턴하는 함수 P6를 작성하세요.

<조건>
1.입력은항상정수2개 
2.입력받은 두 정수 중 큰수부터 시작하여 작은수까지 포함된 리스트를 리턴 
3. 리턴하는 리스트는 내림차순으로 정렬되어 있어야 함 
4.입력받는 두정수가 같은 경우는 해당정수가 1번만 포함된 리스트를 리턴

TestCase1)
>>> P6(3, 9)
[9, 8, 7, 6, 5, 4, 3]
"""

def P6(v1, v2):
    ans = []
    if v1 == v2:
        ans.append(v1)
    else: 
        # range(시작, 끝-1, step:-1)
        for val in range(max(v1,v2), min(v1,v2)-1, -1):
            ans.append(val)
    return ans