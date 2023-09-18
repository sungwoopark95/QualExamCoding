"""
주어진 array에서 "연결된 가장 짧은 subarray"를 찾되, 해당 subarray만 정렬하면 전체 array가 정렬되어야 한다.

Input: nums = [2,6,4,8,10,9,15]
Output: 5
Explanation: [6, 4, 8, 10, 9]만 정렬하면 전체 array가 정렬된다.

Input: nums = [1,2,3,4]
Output: 0

Input: nums = [1]
Output: 0
"""
from typing import List

from typing import List

def findUnsortedSubarray(nums: List[int]) -> int:
    # 만약 리스트의 길이가 1이거나 이미 정렬되어 있으면
    if len(nums) == 1 or nums == sorted(nums):
        return 0

    # 리스트를 정렬하여 비교용으로 사용
    comp = sorted(nums)
    
    # 최대와 최소 인덱스 초기 값 설정
    max_idx = -1
    min_idx = 10000000

    # 리스트를 순회하면서 정렬되지 않은 첫 번째와 마지막 요소를 찾음
    for i in range(len(nums)):
        # 원래 리스트의 요소가 정렬된 위치에 없다면
        if nums[i] != comp[i]:
            # 현재 인덱스가 더 작으면 min_idx 업데이트
            if min_idx > i:
                min_idx = i
            # 현재 인덱스가 더 크면 max_idx 업데이트
            if max_idx < i:
                max_idx = i
    
    # 정렬되지 않은 하위 배열의 길이를 계산하여 반환
    return (max_idx - min_idx) + 1

if __name__ == "__main__":
    nums = [2,6,4,8,10,9,15]
    print(findUnsortedSubarray(nums))