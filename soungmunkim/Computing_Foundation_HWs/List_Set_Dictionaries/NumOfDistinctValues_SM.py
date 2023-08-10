"""
딕셔너리(dictionary)의 key는 unique함이 보장되지만, value는 그렇지 않다.
하나의 딕셔너리를 변수(argument)로 받고, 
그것에 포함된 “distinct values”의 수를 리턴하는 함수를 작성하시오.

<조건>
1. 모든 values는 “Hashable” 함

TestCase1)
>>> P3({'red': 1, 'green': 1, 'blue': 2}) 
2
TestCase2)
>>> P3({(1,2): 'a', 'g': 3, 1: True}) 
3
"""
def P3(dic):
    unique = set(dic.values())
    ans = len(unique)
    return ans