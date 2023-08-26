"""
0 이상 정수로 이루어진 리스트 `nums`와 1 이상 정수 `k`를 입력으로 받는다. 
리스트의 원소를 둘씩 짝지으려고 하는데, 각각의 쌍의 합이 모두 `k`로 나누어지도록 짝을 지으려 한다. 가능하면 `True`, 불가능하면 `False`를 return 하는 함수를 구현하시오.
(리스트의 길이는 2 이상 짝수이다) 
"""

from typing import List

def P1(nums:List[int], k:int):
    # 임의의 수에 대해서 k로 나누었을 때 나머지는 0 ~ k-1이다.
    # 따라서, k로 나누어 떨어지는 짝이 있을 가능성은 다음의 두 가지이다.
    # 나머지가 0인 수가 짝수 개인 경우
    # 나머지 i에 대해서, k-i의 나머지를 갖는 수가 존재하고 서로 짝이 맞는 경우
    remain = dict()
    for n in nums:
        r = n % k
        if r in remain:
            remain[r].append(n)
        else:
            remain[r] = [n]

    for key in remain:
        if key == 0:
            if len(remain[key]) % 2 != 0:
                return False
        else:
            if (k-key) not in remain:
                return False
            elif len(remain[key]) != len(remain[k-key]):
                return False
    return True

if __name__ == "__main__":
    print(P1([123, 36, 54, 28, 39, 28], 3))
