/*
## 1004. Max Consecutive Ones III
Medium
7.5K
85
Companies
Given a binary array nums and an integer k, return the maximum number of consecutive 1's in the array if you can flip at most k 0's.

 

Example 1:

Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
Output: 6
Explanation: [1,1,1,0,0,1,1,1,1,1,1]
Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.
Example 2:

Input: nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3
Output: 10
Explanation: [0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.
 

Constraints:

1 <= nums.length <= 105
nums[i] is either 0 or 1.
0 <= k <= nums.length

*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int longestOnes(int* nums, int numsSize, int k){
    int left_flip = k;
    int front=0; //ptr for the first element
    int rear=0; //ptr for the next(right) of the last element's
    int curr_ans=0; //answer with current position of two pointers
    int res=0; // result to return(the maximum value of possible curr_ans)

    // Use all k-flips from the front
    while ((rear<numsSize)&&(left_flip>0)){
        if (nums[rear]==0){ left_flip--;}
        rear++;
    }

    // After using all k-flips, move rear pointer until it discovers first 0.
    while ((rear<numsSize)&&(nums[rear]==1)){
        rear+=1;
    }

    // answer update
    curr_ans = rear-front;
    if (curr_ans > res){ res=curr_ans; }

    // From now, move front ptr forward with recovering left_flip.
    while (rear<numsSize){
        //recover left_flip before moving front ptr
        if (nums[front]==0) { left_flip++;}
        front++;
        
        // Use left k-flips from the front
        while ((rear<numsSize)&&(left_flip>0)){
            if (nums[rear]==0){ left_flip--;}
            rear++;
        }

        // After using all k-flips, move rear pointer until it discovers first 0.
        while ((rear<numsSize)&&(nums[rear]==1)){
            rear+=1;
        }

        // answer update
        curr_ans = rear-front;
        if (curr_ans > res){ res=curr_ans; }
    }
    return res;
}