"""
세 개의 리스트를 입력으로 받고, 가장 길이가 긴 리스트의 길이를 리턴하는 함수 P2를 작성하세요.

<조건>
1. 항상 3개의 리스트가 입력으로 주어진다고 가정

TestCase1)
>>> P2([1], [2, 3], [4, 5, 6]) 
3
"""

def P2(lst1, lst2, lst3):
    ans = max(len(lst1), len(lst2), len(lst3))
    
    return ans