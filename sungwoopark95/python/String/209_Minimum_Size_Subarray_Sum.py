"""
합이 target보다 같은 subarray 가운데 길이가 가장 짧은 subarray의 길이를 반환하는 함수
Input: target = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: The subarray [4,3] has the minimal length under the problem constraint.

Input: target = 4, nums = [1,4,4]
Output: 1

Input: target = 11, nums = [1,1,1,1,1,1,1,1]
Output: 0
"""

from typing import List
############################################# My Code #############################################
################################## list2가 list1의 부분 배열인지 확인 ###################################
def isSubarray(list1, list2):
    # list2의 첫 번째 요소의 인덱스를 찾습니다.
    start_idx = -1
    for i, num in enumerate(list1):
        if num == list2[0]:
            start_idx = i
            break
    
    # list2의 첫 번째 요소가 list1에 없으면 False 반환
    if start_idx == -1:
        return False
    
    # start_idx부터 list2의 모든 요소가 list1에 순서대로 있는지 확인
    for j in range(len(list2)):
        if list1[start_idx+j] != list2[j]:
            return False
    return True
####################################################################################################

##################### target보다 sum이 크거나 같은 subarray 가운데 최소 길이를 찾는 작업 #######################
def minSubArrayLen(target: int, nums: List[int]) -> int:
    if sum(nums) < target:
        return 0
    
    def backtrack(remaining, combo, start):
        if remaining <= 0 and isSubarray(nums, list(combo)):
            # 잔여 합계가 0과 같거나 0보다 작고, 현재 조합이 nums의 subarray인 경우 현재 조합을 결과에 추가합니다.
            result.append(list(combo))
            return

        for i in range(start, len(nums)):
            # 이전 숫자와 현재 숫자가 동일한 경우 중복을 방지하기 위해 건너뜁니다.
            if i > start and nums[i] == nums[i-1]:
                continue
            # 현재 숫자를 조합에 추가하고, 백트래킹을 통해 가능한 조합을 탐색합니다.
            combo.append(nums[i])
            # backtracking을 할 때, i부터 시작하면 자기 자신의 index부터 다시 시작하기 때문에 자기 자신도 포함될 수 있음
            # 여기서는 중복을 방지하기 위해 i+1로 자기 자신을 지난 다음부터 backtracking하도록 조작
            backtrack(remaining - nums[i], combo, i+1)
            # 백트래킹을 위해 마지막에 추가된 숫자를 제거합니다.
            combo.pop()

    result = []
    backtrack(target, [], 0)
    
    # 최소 길이를 찾는 과정
    min_len = (10 ** 6)
    for item in result:
        if min_len > len(item):
            min_len = len(item)    
    return min_len
####################################################################################################

############################################# ChatGPT ##############################################
def min_subarray_length(target, nums):
    # left: 부분 배열의 시작 인덱스
    # total: 현재 부분 배열의 합
    # min_len: target 이상의 합을 가진 최소 길이의 부분 배열 길이
    left, total, min_len = 0, 0, float('inf')

    # nums 배열을 순회하면서 각 원소를 right로 참조
    for right in range(len(nums)):
        # 현재 원소(nums[right])를 total에 더함
        total += nums[right]

        # 현재 부분 배열의 합(total)이 target보다 크거나 같은 경우
        while total >= target:
            # 최소 길이 부분 배열을 찾기 위해, 현재 부분 배열의 길이(right - left + 1)와 
            # 이전까지의 최소 길이(min_len) 중 작은 값을 선택
            min_len = min(min_len, right - left + 1)
            
            # 부분 배열의 합에서 가장 왼쪽 원소(nums[left])를 뺌
            total -= nums[left]
            
            # left 포인터를 오른쪽으로 이동시킴
            left += 1

    # 최소 길이 부분 배열을 찾았다면 그 길이(min_len)를 반환하고, 찾지 못했다면 0을 반환
    return min_len if min_len != float('inf') else 0
####################################################################################################

