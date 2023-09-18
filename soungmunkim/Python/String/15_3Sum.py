"""
[3 Sum]
서로 다른 위치들 값 다 더해서 0이 나오는 조합 찾기

Example 1:
Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation: 
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
The distinct triplets are [-1,0,1] and [-1,-1,2].
Notice that the order of the output and the order of the triplets does not matter.

Example 2:
Input: nums = [0,1,1]
Output: []
Explanation: The only possible triplet does not sum up to 0.

Example 3:
Input: nums = [0,0,0]
Output: [[0,0,0]]
Explanation: The only possible triplet sums up to 0.
"""
from typing import List

##################### list에서 정해진 길이만큼의 조합(combination)을 만드는 함수 #####################
def list_comb(nums, length):
    # 리스트의 길이가 요구되는 길이보다 짧을 경우 에러 메시지를 출력하고 빈 리스트 반환
    if length > len(nums):
        print("length cannot be greater than the length of nums")
        return []

    def backtrack(start, length, path):
        # 기저 조건: path의 길이가 요구되는 길이와 같을 경우
        if len(path) == length:
            output.append(path[:])  # path의 복사본을 output에 추가
            return
        for i in range(start, len(nums)):
            # 현재의 숫자를 path에 추가
            path.append(nums[i])
            # 다음 정수들을 사용하여 조합을 완성
            backtrack(i + 1, length, path)
            # 백트래킹: 마지막에 추가된 숫자 제거
            path.pop()
    
    output = []  # 최종 결과를 저장할 리스트
    backtrack(0, length, [])  # 백트래킹 시작
    return output  # 완성된 조합들의 리스트 반환


def threeSum(nums: List[int]) -> List[List[int]]:
    
    # 3가지 조합으로 list뽑을 수 있는것 다 저장
    three_comb = list_comb(nums, 3)
    # print(list_comb(nums, 3))
    ans = []
    
    # 그 중 합이 0이되고 sorted된게 같지 않으면 ans에 넣기
    for i in range(len(three_comb)):
        if sum(three_comb[i]) == 0:
            if sorted(three_comb[i]) not in ans:
                ans.append(sorted(three_comb[i]))
            
    return ans
            

if __name__ == "__main__":
    nums = [-1,0,1,2,-1,-4]
    print(threeSum(nums))
    
    nums1 = [0,1,1]
    print(threeSum(nums1))
    
    nums2 = [0,0,0]
    print(threeSum(nums2))
    
