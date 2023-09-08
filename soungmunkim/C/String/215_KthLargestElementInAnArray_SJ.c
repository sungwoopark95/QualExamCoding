/* [min heap 사용 방식]
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

*/

#include <stdio.h>
#include <stdlib.h>

struct Solution {
    int* heap;
    int heapSize;
};

void init(struct Solution* s, int size) {
    s->heap = (int*)malloc(sizeof(int) * size);
    s->heapSize = 0;
}

void push(struct Solution* s, int val) {
    int i = s->heapSize++;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (s->heap[parent] <= val) break;
        s->heap[i] = s->heap[parent];
        i = parent;
    }
    s->heap[i] = val;
}

int pop(struct Solution* s) { //제일 작은 값 extract
    int popped = s->heap[0]; //store the value of the smallest element in the heap
    int last = s->heap[--s->heapSize]; //get the value of the last element and decrement heapSize
    int i = 0; //start at the root of the heap
    while (i * 2 + 1 < s->heapSize) { //while there's at least one child
        int child = i * 2 + 1; //calculate the left child's index
        //if the right child exists and is smaller than the left child, choose the right child
        if (child + 1 < s->heapSize && s->heap[child + 1] < s->heap[child]) {
            child++;
        }
        //if the value of the last element is less than or equal to the smallest child, break
        if (last <= s->heap[child]) break;
        //move the smaller child up to the current position
        s->heap[i] = s->heap[child];
        i = child; //move down the heap
    }
    //place the last element (which was previously removed) into the correct position
    s->heap[i] = last; 
    return popped; //return the originally smallest element
}

int findKthLargest(struct Solution* s, int* nums, int numsSize, int k) {
    init(s, k);
    for (int i = 0; i < numsSize; ++i) {
        push(s, nums[i]);
        if (s->heapSize > k) {
            pop(s);
        }
    }
    return s->heap[0];
}

int main() {
    struct Solution solution;
    int nums[] = {3, 2, 1, 5, 6, 4};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int k = 2;
    int result = findKthLargest(&solution, nums, numsSize, k);
    printf("Kth largest element: %d\n", result);
    free(solution.heap);
    return 0;
}