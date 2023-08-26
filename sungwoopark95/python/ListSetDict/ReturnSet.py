"""
# P1

정수(int)로만 구성된 리스트를 변수(argument)로 받고, 그중 두 번 이상 반복되는 정수의 집합(set)을 리턴하는 함수를 작성하시오.

예시1)
```
>>> P1([1, 2, 3, 1]) 
{1}
```

예시2) 
```
>>> P1([1, 1, 2, 3, 3, 3]) 
{1, 3}
```

예시3)
```
>>> P1([1, 2, 3, 4, 5]) 
set()
```
"""

from typing import List

def P1(array:List):
    benchmark = set(array)
    for item in benchmark:
        array.remove(item)
    return set(array)

if __name__ == "__main__":
    print(P1([1, 2, 3, 1]))
    print(P1([1, 1, 2, 3, 3, 3]))
    print(P1([1, 2, 3, 4, 5]))
