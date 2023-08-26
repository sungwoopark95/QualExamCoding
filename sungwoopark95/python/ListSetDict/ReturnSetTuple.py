"""# P2

길이가 같은 리스트 두 개를 변수(arguments)로 받고, 같은 인덱스를 갖는 원소끼리 짝지은 튜플(tuple)의 집합(set)을 리턴하는 함수를 작성하시오. 

<조건>

1. 튜플은 (첫번째 리스트 원소, 두번째 리스트 원소) 순서로 만들어야 함

예시1) 
```
>>> P2(['red', 'yellow', 'purple'], ['apple', 'banana', 'grape'])
{('red', 'apple'), ('yellow', 'banana'), ('purple', 'grape')}
```

예시2)
```
>>> P2([1, 2, 3], ['computer', 'keyboard', 'mouse'])
{(1, 'computer'), (2, 'keyboard', (3, 'mouse')}
```

예시3)
```
>>> P2([], [])
set()
```
"""
    
from typing import List

def P2(a:List, b:List):
    ans = set()
    for item, jtem in zip(a, b):
        ans.add((item, jtem))
    return ans

if __name__ == "__main__":
    print(P2(['red', 'yellow', 'purple'], ['apple', 'banana', 'grape']))
    print(P2([1, 2, 3], ['computer', 'keyboard', 'mouse']))
    