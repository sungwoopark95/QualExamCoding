"""
딕셔너리 형태로 저장된 두 개의 sparse vector를 변수(arguments)로 받아 그들의 내적을 계산하여 리턴하는 함수를 작성하시오.

TestCase1)
>>> P9({0:1, 6:3}, {0:2, 5:2, 6:2, 7:1}) 
8
"""
def P9(dic1, dic2):
    ans = 0
    for k,v in dic1.items():
        if k in dic2:
            ans += v * dic2.get(k)
    return ans