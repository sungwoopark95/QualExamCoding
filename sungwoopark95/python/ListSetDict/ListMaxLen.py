"""
세 개의 리스트를 입력으로 받고, 가장 길이가 긴 리스트의 길이를 리턴하는 함수 P2를 작성하세요.  

<조건> 

1. 항상 3개의 리스트가 입력으로 주어진다고 가정 

예시1)
```
>>> P2([1], [2, 3], [4, 5, 6]) 
>>> 3
```

예시2)
```
>>> P2([10, 11, 12, 13], ['a'], [1.11]) 
>>> 4
```
"""

from typing import List

def P2(a:List, b:List, c:List):
    maxlen = -1
    for item in [a, b, c]:
        if len(item) > maxlen:
            maxlen = len(item)
    return maxlen

if __name__ == "__main__":
    print(P2([1], [2, 3], [4, 5, 6]))
    print(P2([10, 11, 12, 13], ['a'], [1.11]))
