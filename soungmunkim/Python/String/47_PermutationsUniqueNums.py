"""
[주어진 정수 배열 nums에서 가능한 모든 고유한 순열을 생성하는 함수]

Given a collection of numbers, nums, that might contain duplicates, return all possible unique permutations in any order.


Example 1:
Input: nums = [1,1,2]
Output:
[[1,1,2],
 [1,2,1],
 [2,1,1]]
 
Example 2:
Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
"""

from typing import List
import copy

def permuteUnique(nums: List[int]) -> List[List[int]]:
    
    # 백트래킹을 위한 함수
    def backtrack(start):
        # 만약 start가 nums의 길이와 같다면 하나의 순열이 완성된 것
        if start == len(nums):
            # 해당 순열이 결과 목록에 이미 존재하지 않는 경우에만 추가
            if nums not in permutations:
                permutations.append(copy.deepcopy(nums))
            return

        # start부터 배열의 끝까지 각 위치의 요소를 교환하며 순열 탐색
        for i in range(start, len(nums)):
            # 교환 (swap)
            nums[start], nums[i] = nums[i], nums[start]
            # 백트래킹 (다음 요소로 재귀)
            backtrack(start+1)
            # 원상복구 (swap을 원래대로 되돌리기)
            nums[start], nums[i] = nums[i], nums[start]

    # 결과를 저장할 리스트
    permutations = list()
    # 백트래킹 시작
    backtrack(0)

    return permutations
