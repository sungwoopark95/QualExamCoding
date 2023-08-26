"""
정수로 이루어진 리스트 `nums`를 인자로 받는다. `nums`의 성분 중, 두 개의 정수는 한 개씩만 있고, 나머지 정수들은 두 개씩 있다. 한 개씩 있는 두 개의 정수를 `set`으로 return 하는 `P3` 함수를 구현하시오.
구현 방법에는 여러 가지가 있을 수 있으나, bit operation을 이용해서 구현해보자. 
Time complexity $O(n)$, 입력으로 들어가는 `nums`를 제외한 space complexity $O(1)$에 구현할 수 있다. (채점은 구현에 상관없이 return 값으로만 채점할 것이다.) 
"""

def P3(arr:list):
    ans = set()
    while arr:
        target = arr.pop(0)
        if target in arr:
            arr.remove(target)
            continue
        else:
            ans.add(target)
    return ans
