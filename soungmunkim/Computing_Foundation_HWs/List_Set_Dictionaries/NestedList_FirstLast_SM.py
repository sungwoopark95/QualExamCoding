"""
중첩 리스트(nested list)를 입력으로 받고, 
안쪽 리스트 중 첫 리스트의 첫 원소와 마지막 리스트의 마지막 원소를 리턴하는 함수 P9를 작성하세요.

<조건>
1. 바깥 리스트는 항상 2개의 리스트를 원소로 가짐 
2.안쪽리스트들은각각최소1개의원소를가짐

TestCase1)
>>> P9([['km','miles','league'],['kg','pound','stone']]) 
['km','stone']
"""
def P9(nested_lst):
    ans = []
    ans.extend([nested_lst[0][0], nested_lst[-1][-1]])
    return ans