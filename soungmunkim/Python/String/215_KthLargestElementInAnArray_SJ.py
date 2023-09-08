"""
[min heap 사용한 방식]
Given an integer array nums and an integer k, return the kth largest element in the array.

Note that it is the kth largest element in the sorted order, not the kth distinct element.

Can you solve it without sorting?

Example 1:

Input: nums = [3,2,1,5,6,4], k = 2
Output: 5


Example 2:

Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
Output: 4
 

Constraints:

1 <= k <= nums.length <= 105
-104 <= nums[i] <= 104
"""
import heapq as heap
class Solution:
	def findKthLargest(nums, k):
	    h = []
	    for num in nums:
	        heap.heappush(h, num)
	        if len(h) > k:
	            heap.heappop(h)
	    
	    return h[0]

#이런 방식으로도 가능
import heapq as heap
class Solution:
    def findKthLargest(self, nums: List[int], k: int) -> int:
        h = []
        for i in range(len(nums)):
            heap.heappush(h, nums[i])
        output = heap.nlargest(k, h)
        
        return output[-1]
