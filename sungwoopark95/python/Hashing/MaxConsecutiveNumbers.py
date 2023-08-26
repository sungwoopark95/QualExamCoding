"""
정수로 이루어진 리스트 `nums`를 입력으로 받는다. 여기서 몇 개의 수를 뽑는데, 뽑은 수들이 연속적이어야 한다 (순서는 상관없음). 
뽑을 수 있는 최대 개수를 return하는 함수를 구현하시오. (리스트의 길이는 1 이상이다. 리스트 내 숫자는 중복되지 않는다.)
```py
>>> P4([3, 6, 4, 64, 10, 29, 5, 9, 11]) 
4
```
설명: 3, 6, 4, 5를 뽑으면 연속된 4개의 정수가 된다. 뽑는 방법은 여러가지일 수 있고, 최대 개수만 return 하면 된다. 
"""

from typing import List

def P4(nums:List[int]):
    # sort the list first
    nums.sort()
    
    # get the difference list
    diffs = [nums[i+1] - nums[i] for i in range(len(nums)-1)]
    
    # count the number of consecutive numbers
    cnt = 1
    max_cnt = 1
    for item in diffs:
        if item == 1:
            cnt += 1
        else:
            # 현재까지 나온 consecutive number의 개수를 저장해놓고, 1로 reset
            max_cnt = max(max_cnt, cnt)
            cnt = 1

    # 여태 나온 consecutive number 가운데 최댓값
    max_cnt = max(max_cnt, cnt)
    return max_cnt

