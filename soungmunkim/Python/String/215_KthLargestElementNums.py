"""
[숫자 리스트에서 k번째로 큰 숫자 반환하기]
Given an integer array nums and an integer k, 
    return the kth largest element in the array.

Note that it is the kth largest element in the sorted order, 
    not the kth distinct element.

Can you solve it without sorting?

Example 1:
Input: nums = [3,2,1,5,6,4], k = 2
Output: 5

Example 2:
Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
Output: 4
"""

from typing import List

def findKthLargest(nums:List[int], k:int)->int:
    # order 별로 숫자 저장할 리스트 (큰수->작은수)
    orderbymax = []
    # recursion
    def find_max(nums):
        # num 리스트가 다 없어지면 함수 종료
        if len(nums) == 0:
            return
        
        # 큰 값 찾아서 넣고 nums 리스트에 빼기
        orderbymax.append(max(nums))
        nums.remove(max(nums))
        find_max(nums)
        
    # recursion 함수 시작
    find_max(nums)
    
    # print(orderbymax)
    
    # index니까 k-1번째 숫자 빼기
    ans = orderbymax[k-1]
    return ans

if __name__ == "__main__":
    nums = [3,2,3,1,2,4,5,5,6]
    k = 4
    result = findKthLargest(nums, k)
    print(result)