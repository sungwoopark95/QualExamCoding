"""
0 이상 정수 `num`을 입력으로 받는다. bit로 표현했을 때, ‘1’의 개수를 return하는 함수를 구현하시오. (`num`은 32bit를 넘지 않는다.) 
"""

def P4(num:int):
    ones = 0
    while num:
        ones += num % 2
        num = num // 2
    return ones
