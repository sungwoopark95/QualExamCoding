from typing import List
from collections import Counter

def P2_On2(nums:List):
    ## O(n^2)로 푸는 방법
    max_cnt = -1
    for i in range(len(nums)-1):
        itm_max = -1
        for j in range(i, len(nums)):
            slce = nums[i:j]
            cnt_dict = Counter(slce)
            if cnt_dict[1] == 0 or cnt_dict[0] == 0:
                cnt = 0
            elif cnt_dict[1] == cnt_dict[0]:
                cnt = 2 * cnt_dict[1]
            else:
                cnt = 2 * min(cnt_dict[1], cnt_dict[0])
            if itm_max < cnt:
                itm_max = cnt
        if max_cnt < itm_max:
            max_cnt = itm_max
    return max_cnt

## O(n)으로 푸는 방법
def P2_On(nums):
    """
    1. 0을 -1로 변환하고, 1은 그대로 1로 두어 누적 합을 계산합니다.
    2. 누적 합이 같은 두 지점 사이에는 0과 1의 개수가 동일하다는 것을 의미합니다. -> 그 사이에 존재하는 숫자들의 합이 0이기 때문
    3. 따라서 누적 합이 0인 지점까지의 길이나 누적 합이 같은 두 지점 사이의 길이를 찾아 최대 길이를 계산합니다.
    => cum_sum이 처음 나온 위치를 저장한 뒤, 해당 cum_sum이 다시 나올 때마다 처음 나온 위치와 현재 위치 사이의 길이를 계산하는 방법
    """
    # 0을 -1로 변환
    nums = [-1 if num == 0 else 1 for num in nums]
    
    # 누적 합과 해당 지점의 인덱스를 저장할 딕셔너리
    sum_to_index = {0: -1}
    max_len = 0
    cum_sum = 0
    
    for i, num in enumerate(nums):
        cum_sum += num
        
        # 누적 합이 이전에 나왔던 적이 있다면, 그 지점과 현재 지점 사이의 길이를 계산
        if cum_sum in sum_to_index:
            max_len = max(max_len, i - sum_to_index[cum_sum])
        else:
            sum_to_index[cum_sum] = i
        print(f"{i} - cum_sum : {cum_sum}, max_len : {max_len}")
    print(sum_to_index)
    
    return max_len

if __name__ == "__main__":
    print(P2_On([1, 1, 0, 1, 0, 1]))
