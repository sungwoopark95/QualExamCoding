/*
334. Increasing Triplet Subsequence
Medium
7.2K
360
Companies
Given an integer array nums, return true if there exists a triple of indices (i, j, k) such that i < j < k and nums[i] < nums[j] < nums[k]. If no such indices exists, return false.

 

Example 1:

Input: nums = [1,2,3,4,5]
Output: true
Explanation: Any triplet where i < j < k is valid.
Example 2:

Input: nums = [5,4,3,2,1]
Output: false
Explanation: No triplet exists.
Example 3:

Input: nums = [2,1,5,0,4,6]
Output: true
Explanation: The triplet (3, 4, 5) is valid because nums[3] == 0 < nums[4] == 4 < nums[5] == 6.
 

Constraints:

1 <= nums.length <= 5 * 105
-231 <= nums[i] <= 231 - 1
 

Follow up: Could you implement a solution that runs in O(n) time complexity and O(1) space complexity?
Accepted
438.1K
Submissions
1.1M

*/

#include <math.h>

bool increasingTriplet(int* nums, int numsSize){
    // int first=(int)(pow(2, 31))-1;
    // int second=(int)(pow(2, 31))-1;
    // for (int i=0; i<numsSize;i++){
    //     if (nums[i]<=first){
    //         first = nums[i];
    //     }
    //     else if (nums[i]<=second){
    //         second = nums[i];
    //     }
    //     else {
    //         return true;
    //     }
    // }
    // return false;
    
    double first=(pow(2, 31))-1;
    double second=(pow(2, 31))-1;
    for (int i=0; i<numsSize;i++){
        if ((double)nums[i]<=first){
            first = (double) nums[i];
        }
        else if ((double)nums[i]<=second){
            second = (double)nums[i];
        }
        else {
            return true;
        }
    }
    return false;
}