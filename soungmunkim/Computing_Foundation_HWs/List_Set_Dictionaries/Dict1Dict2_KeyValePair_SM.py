"""
두 개의 딕셔너리 dct1과 dct2를 변수(arguments)로 받아 
dct1과 dct2에 공통으로 포함된 key/value 쌍으로만 만든 새로운 딕셔너리를 리턴하는 함수를 작성하시오.

TestCase1)
>>> P6({'a': 1, 'b': True, 'c': [1,2]}, {'a': 1, 'b': 123, 'c': [1,2]}) 
{'a': 1, 'c': [1, 2]}
"""

def P6(dic1, dic2):
    ans = {}
    for k,v in dic1.items():
        if k in dic2:
            if dic2.get(k) == dic1.get(k):
                ans[k] = v
    return ans