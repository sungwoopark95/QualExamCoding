"""
주어진 양의 정수 `n`을 이진수로 나타냈을 때 교차 비트로 이루어져 있는지를 확인하여 `bool` 값으로 return하는 `P1` 함수를 구현하여라. 

교차 비트로 이루어져 있다면 `True`, 이루어져 있지 않다면 `False`를 return한다. 

* 교차 비트란 0101… 혹은 1010…으로 인접한 비트가 항상 다른 비트인 것을 의미한다. 
* 양 옆에 인접 비트가 없을 때는 `True`를 반환한다. (ex. 1) 
* 1과 0의 개수가 다르면서 교차인 경우(10101과 같은 경우)에도 교차 비트로 이루어진 것으로 판단하여 `True`를 반환한다.
"""
def P1(n:int):
    def dec2bin(num:int):
        container = []
        while num > 1:
            container.append(str(num % 2))
            num = num // 2
        container.append(str(num))
        container.reverse()
        return ''.join(container)
    binary = dec2bin(n)
    print(binary)
    for i in range(len(binary)-1):
        if binary[i] == binary[i+1]:
            return False
    return True
