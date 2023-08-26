"""
“Balanced color”는 red, green, blue 값을 합해서 1.0이 되는 것을 의미한다. Key가 ‘R’, ‘G’, ‘B’이고 각각의 value가 0과 1 사이인 딕셔너리를 변수(arguments)로 받아서 그 딕셔너리가 “Balanced color”를 의미하면 True, 아니면 False를 리턴하는 함수를 작성하시오.

예시1)
```
>>> P8({'R': 0.2, 'G': 0.3, 'B': 0.5})
True
```

예시2)
```
>>> P8({'R': 0.2, 'G': 0.3, 'B': 0.6})
False
```

예시3)
```
>>> P8({'R': 0.1, 'G': 0.1, 'B': 0.1})
False
"""

from typing import Dict

def P8(colors:Dict[str, float]):
    if sum(colors.values()) == 1:
        return True
    return False
