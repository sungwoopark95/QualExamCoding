"""
# P6

두 개의 딕셔너리 dct1과 dct2를 변수(arguments)로 받아 dct1과 dct2에 공통으로 포함된 key/value 쌍으로만 만든 새로운 딕셔너리를 리턴하는 함수를 작성하시오.

예시1)
```
>>> P6({'a': 1, 'b': True, 'c': [1,2]}, {'a': 1, 'b': 123, 'c': [1,2]})
{'a': 1, 'c': [1, 2]}
```

예시2) 
```
>>> P6({'a': 1, 'b': True }, {'c': 1, 'd': 123, 'e': [1,2]})
{}
```

예시3) 
```
>>> P6({}, {'c': 1, 'd': 123, 'e': [1,2]})
{}
```
"""

from typing import Dict

def P6(dct1:Dict, dct2:Dict):
    ans = dict()
    for key, val in dct1.items():
        if key in dct2.keys() and dct1[key] == dct2[key]:
            ans[key] = val
    return ans

if __name__ == "__main__":
    print(P6({'a': 1, 'b': True, 'c': [1,2]}, {'a': 1, 'b': 123, 'c': [1,2]}))
    print(P6({'a': 1, 'b': True }, {'c': 1, 'd': 123, 'e': [1,2]}))
