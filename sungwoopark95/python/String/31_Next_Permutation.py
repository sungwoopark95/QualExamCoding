"""
주어진 배열의 순열 중에서 다음에 오는 순열(사전식 순서로 다음 순서)을 찾아야 합니다. 
만약 주어진 배열이 사전식 순서로 가장 큰 경우(내림차순으로 정렬된 경우)에는 가장 작은 순서(오름차순으로 정렬된 경우)로 배열을 변경합니다. 
주어진 배열을 직접 변경해야 하며, 상수 시간 복잡도를 가진 추가 메모리만을 사용해야 합니다.

Example 1:
Input: nums = [1,2,3]
Output: [1,3,2]

Example 2: 
Input: nums = [3,2,1]
Output: [1,2,3]

Example 3:
Input: nums = [1,1,5]
Output: [1,5,1]
"""
from typing import List

###################################### MY CODE - TIME LIMIT ######################################
def nextPermutation(nums: List[int]) -> None:
    """
    Do not return anything, modify nums in-place instead.
    """
    ## make permutation list
    def int_perm(nums):
        def backtrack(start):
            if start == len(nums) and nums[:] not in permutation_lst:
                permutation_lst.append(nums[:])  # deep copy를 추가해주어야 합니다.
                return
            print(start, nums[:])
            for i in range(start, len(nums)):
                # 현재 시작 인덱스와 루프의 인덱스 위치의 정수를 교환 (스왑)
                nums[start], nums[i] = nums[i], nums[start]
                
                # 현재 시작 인덱스를 제외한 나머지 리스트에 대해 순열을 생성하기 위해 재귀적으로 호출
                backtrack(start + 1)
                
                # 이전 상태로 리스트를 복원하기 위해 다시 정수 위치를 교환 (백트래킹)
                nums[start], nums[i] = nums[i], nums[start]

        permutation_lst = []
        backtrack(0)
        return permutation_lst
    
    permList = int_perm(nums)
    sorted_perm = sorted(permList)
    print(sorted_perm)
    idx = -1
    for i, item in enumerate(sorted_perm):
        if item == nums:
            idx = i
            break
    
    if idx == len(sorted_perm) - 1:
        comp = sorted_perm[0]
    else:
        comp = sorted_perm[idx+1]
    
    for i in range(len(comp)):
        nums[i] = comp[i]
########################################################################################################

############################################### ChatGPT ################################################
"""
Example
nums = [3,2,1]
i = 1 # len(nums) - 2
nums[i] = 2, nums[i+1] = 1 -> while loop 들어감, i -> 0
nums[i] = 3, nums[i+1] = 2 -> while loop 들어감, i -> -1, while 종료
i < 0이므로 if문 들어가지 않고 통과
nums[i+1:] = nums[0:] = nums 자체
nums[i+1:] = sorted(nums[i+1:]) -> nums = [1,2,3]
"""
def next_permutation(nums):
    # i = len(nums) - 2로 설정하는 이유는 배열의 마지막 두 원소부터 시작해서 이전 원소와 비교하려는 의도 때문입니다.
    i = len(nums) - 2
    
    # i를 찾기: 내림차순이 깨지는 첫 번째 위치
    while i >= 0 and nums[i] >= nums[i + 1]:
        i -= 1
    
    if i >= 0:
        j = len(nums) - 1
        # j를 찾기: nums[i]보다 큰 첫 번째 원소
        while nums[j] <= nums[i]:
            j -= 1
        # i와 j 위치의 원소 교환
        nums[i], nums[j] = nums[j], nums[i]
    
    # i 뒤의 원소들을 오름차순으로 정렬
    nums[i+1:] = sorted(nums[i+1:])
    
    return nums
########################################################################################################
    
if __name__ == "__main__":
    nums = [1, 1, 5]
    nextPermutation(nums)
    print(nums)