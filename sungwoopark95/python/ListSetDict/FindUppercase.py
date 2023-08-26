"""
알파벳으로만 구성된 리스트를 입력으로 받고, 대문자가 처음으로 등장하는 index를 리턴하는 함수 P5을 작성하세요. (for loop을 통해서 해결 가능하지만, while loop을 활용하는 훈련을 해보는 것도 좋습니다. 어떻게 구현하여도 점수와 관계는 없습니다.) 

<조건> 

1. 입력 리스트는 알파벳 대문자 혹은 소문자로만 구성됨 
2. 대문자가 존재하지 않는 경우는 -1을 리턴 

예시1)  

```
>>> P5(['a', 'B', 'c', 'D'])
>>> 1
```

예시2)
```
>>> P5(['z', 'b', 'k', 'D', 'I', 'q'])
>>> 3
```

예시3)
```
>>> P5(['a', 'b'])
>>> -1 
```
"""

from typing import List

def P5(array:List[str]):
    num_alphabets = ord('Z') - ord('A')
    capitals = [chr(ord('A')+i) for i in range(num_alphabets)]
    for idx, item in enumerate(array):
        if item in capitals:
            return idx
    ## if the for loop ends, it means that there is no uppercase in the array
    return -1

if __name__ == "__main__":
    print(P5(['a', 'B', 'c', 'D']))
    print(P5(['z', 'b', 'k', 'D', 'I', 'q']))
    print(P5(['a', 'b']))
