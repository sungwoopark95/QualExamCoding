"""
중첩 리스트(nested list)를 입력으로 받고, 안쪽 리스트 중 첫 리스트의 첫 원소와 마지막 리스트의 마지막 원소를 리턴하는 함수 P9를 작성하세요.

<조건> 

1. 바깥 리스트는 항상 2개의 리스트를 원소로 가짐 
2. 안쪽 리스트들은 각각 최소 1개의 원소를 가짐 

예시1)
```
>>> P9([['km','miles','league'],['kg','pound','stone']])
>>> ['km','stone']
```

예시2)
```
>>> P9([[0,1,2,3],[4,5,6]])
>>> [0,6]
```

예시3)
```
>>> P9([[0,0,0],[1]])
>>> [0,1]
```
"""
from typing import List

def P9(array:List):
    a, b = array
    ans = [a[0], b[-1]]
    return ans

if __name__ == "__main__":
    print(P9([['km','miles','league'],['kg','pound','stone']]))
    print(P9([[0,1,2,3],[4,5,6]]))
    print(P9([[0,0,0],[1]]))
