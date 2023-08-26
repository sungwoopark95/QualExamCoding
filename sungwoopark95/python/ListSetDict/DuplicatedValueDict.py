"""
# P5

딕셔너리를 변수(argument)로 받아 두 번 이상 나타나는 value를 리스트로 저장하여 리턴하는 함수를 작성하시오. 

<조건>
1. 리턴되는 리스트 요소들의 순서는 상관없음
2. 1과 True가 동일하게 취급되는 문제는 고려하지 않음

예시1) 
```
>>> P5({'red': 1, 'green': 1, 'blue': 2})
[1]
```

예시2)
```
>>> P5({'r': 'a', 'g': 'b', 'b': 'c'})
[]
```

예시3) 
```
>>> P5({'a': True, 'b': True, 'c': 2, 'd': 2})
[True, 2]
```

예시4)
```
>>> P5(dict())
[]
```
"""

from typing import Dict

def P5(arg:Dict):
    array = list(arg.values())
    benchmark = set(array)
    for item in benchmark:
        array.remove(item)
    return array

if __name__ == "__main__":
    print(P5({'red': 1, 'green': 1, 'blue': 2}))
    print(P5({'r': 'a', 'g': 'b', 'b': 'c'}))
