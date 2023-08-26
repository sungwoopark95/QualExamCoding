"""
정수(int)로만 구성된 리스트를 입력으로 받고, 리스트의 메서드(method)를 활용하여 아래의 지시를 순서대로 따르는 함수 P1을 완성하세요. 

1. 입력으로 받은 리스트를 오름차순으로 정렬  
2. 리스트에서 1234 제거 
3. [4321, 2222]를 추가하여 리스트를 확장(extend) 
4. 1번 index 위치에 1111 추가 (주의: python의 index 규칙을 잘 확인할 것) 

<가정> 

1. 리스트는 정수로만 구성됨 
2. 각 숫자들은 리스트 내에 한 번씩만 등장하여 숫자가 중복되는 경우는 없음 
3. 입력되는 리스트에는 1234가 항상 존재 

예시1) 
```
>>> P1([1234, 1011, 3124])  
>>> [1011, 1111, 3124, 4321, 2222]
```

예시2)
```
>>> P1([7777, 5555, 8888, 1234, 9876])  
>>> [5555, 1111, 7777, 8888, 9876, 4321, 2222] 
```
"""

from typing import List

def P1(array:List[int]):
    ## 오름차순 정렬
    array.sort()
    
    ## 1234 제거
    if 1234 in array:
        array.remove(1234)
        
    ## [4321, 2222]를 추가하여 리스트 확장
    array.extend([4321, 2222])
    
    ## 1번 index 위치에 1111 추가
    array.insert(1, 1111)
    
    return array

if __name__ == "__main__":
    print(P1([1234, 1011, 3124]))
    print(P1([7777, 5555, 8888, 1234, 9876])
