"""
# P9

다음과 같이 대부분의 원소가 0으로 되어있는 벡터를 “Sparse vector”라 한다.

`sparse_vector = [1, 0, 0, 0, 0, 0, 3, 0, 0, 0]`

이때 벡터를 모든 0을 포함한 형태로 리스트에 저장하면 메모리가 낭비되기 때문에 딕셔너리를 이용하여 0이 아닌 원소만 나타내기도 한다. 위의 벡터는 딕셔너리를 사용하여 다음과 같이 나타낼 수 있다. `sparse_vector[0] = 1`, `sparse_vector[6] = 3` 을 딕셔너리로 표현한 것이다.

`{0: 1, 6: 3}`

두 벡터의 dot product는 corresponding elements의 products의 sum이다. 예를 들어 [1, 2, 3]과 [4, 5, 6]의 dot product는 4 + 10 + 18 = 32 이다. 두 “Sparse vectors”를 변수(arguments)로 받아 그들의 dot product를 계산하는 함수를 작성하시오.

예시1) 
```
>>> P9({0:1, 6:3}, {0:2, 5:2, 6:2, 7:1})
8
```

예시2)
``` 
>>> P9({0:1, 6:3}, {1:-1, 2:2, 3:2, 4:1})
0
```

예시3)
```
>>> P9({0:1, 6:-3}, {0:-1, 6:3})
-10
```
"""
from typing import Dict

def P9(a:Dict, b:Dict):
    dot = 0
    for key in a:
        if key in b:
            dot += a[key] * b[key]
    return dot

if __name__ == "__main__":
    print(P9({0:1, 6:3}, {0:2, 5:2, 6:2, 7:1}))
    print(P9({0:1, 6:3}, {1:-1, 2:2, 3:2, 4:1}))
