"""
길이가 같은 리스트 두 개를 변수(arguments)로 받고, 
같은 인덱스를 갖는 원소끼리 짝지은 튜플(tuple)의 집합(set)을 리턴하는 함수를 작성하시오.

<조건>
1. 튜플은 (첫번째 리스트 원소, 두번째 리스트 원소) 순서로 만들어야 함

TestCase1)
>>> P2(['red', 'yellow', 'purple'], ['apple', 'banana', 'grape'])
{('red', 'apple'), ('yellow', 'banana'), ('purple', 'grape')}
"""

def P2(lst1, lst2):
    ans = set()
    for i in range(len(lst1)):
        add = [lst1[i], lst2[i]]
        ans.add(tuple(add))
    return ans