"""
숫자로 구성된 리스트를 입력으로 받고, 해당 리스트에서 음수만 제거하는 함수 P8를 작성하세요. 

<조건> 

1. 입력으로는 숫자만 주어짐 

예시1)
```
>>> P8([1, 2, 3, -3, 6, -1, -3, 1])
>>> [1, 2, 3, 6, 1]
```

예시2)
```
>>> P8([-5, 1, -3, 2])
>>> [1, 2]
```
"""

from typing import List

def P8(array:List[int]):
    ans = [item for item in array if item >= 0]
    return ans

if __name__ == "__main__":
    print(P8([1, 2, 3, -3, 6, -1, -3, 1]))
    print(P8([-5, 1, -3, 2]))
