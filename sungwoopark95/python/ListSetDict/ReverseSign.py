"""
정수로 구성된 리스트를 입력으로 받고 리스트 안의 값이 음수이면 양수로, 양수이면 음수로 변경하여 리턴하는 함수 P3를 작성하세요.  

<조건> 

1. 값이 0일 때는 변경 없음 
2. 입력 받은 원본 리스트를 변경하지 말고, 새로운 리스트를 리턴하여야 함 

예시1)  
```
>>> P3([-1, 2]) 
>>> [1, -2] 
```

예시2)  
```
>>> P3([66, 0, -11]) 
>>> [-66, 0, 11] 
```
"""

from typing import List

def P3(array:List[int]):
    answer = [0 for _ in range(len(array))]
    for i, item in enumerate(array):
        answer[i] = item * -1
    return answer

if __name__ == "__main__":
    print(P3([-1, 2]))
    print(P3([66, 0, -11]))
