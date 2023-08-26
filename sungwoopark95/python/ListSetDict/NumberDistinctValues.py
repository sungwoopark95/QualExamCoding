"""
# P3

딕셔너리(dictionary)의 key는 unique함이 보장되지만, value는 그렇지 않다. 
하나의 딕셔너리를 변수(argument)로 받고, 그것에 포함된 “distinct values”의 수를 리턴하는 함수를 작성하시오.

<조건>

1. 모든 values는 “Hashable” 함

예시1)
```
>>> P3({'red': 1, 'green': 1, 'blue': 2})
2
```

예시2) 
```
>>> P3({(1,2): 'a', 'g': 3, 1: True})
3
```

예시3) 
```
>>> P3(dict())
0
```

예시4) 
```
>>> P3({'a': True, 'b': True, 'c': True})
1
```
"""
from typing import Dict

def P3(dic:Dict):
    return len(set(dic.values()))

if __name__ == "__main__":
    print(P3({'red': 1, 'green': 1, 'blue': 2}))
    print(P3({(1,2): 'a', 'g': 3, 1: True}))
