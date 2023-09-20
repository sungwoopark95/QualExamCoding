/*
# 1679. Max Number of K-Sum Pairs
## You are given an integer array nums and an integer k.

In one operation, you can pick two numbers from the array whose sum equals k and remove them from the array.

Return the maximum number of operations you can perform on the array.

 

Example 1:

Input: nums = [1,2,3,4], k = 5
Output: 2
Explanation: Starting with nums = [1,2,3,4]:
- Remove numbers 1 and 4, then nums = [2,3]
- Remove numbers 2 and 3, then nums = []
There are no more pairs that sum up to 5, hence a total of 2 operations.
Example 2:

Input: nums = [3,1,3,4,3], k = 6
Output: 1
Explanation: Starting with nums = [3,1,3,4,3]:
- Remove the first two 3's, then nums = [1,4,3]
There are no more pairs that sum up to 6, hence a total of 1 operation.
 

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 109
1 <= k <= 109
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100000

/*"dictionary"*/

typedef struct {
    int keys[MAX_SIZE];
    int values[MAX_SIZE];
    int size;
} Dictionary;

void init(Dictionary *dict) {
    dict->size = 0;
}

int get(Dictionary *dict, int key) {
    for (int i = 0; i < dict->size; i++) {
        if (dict->keys[i] == key) {
            return dict->values[i];
        }
    }
    return -1;
}

void put(Dictionary *dict, int key, int value) {
    for (int i = 0; i < dict->size; i++) {
        if (dict->keys[i] == key) {
            dict->values[i] = value;
            return;
        }
    }
    dict->keys[dict->size] = key;
    dict->values[dict->size] = value;
    dict->size++;
}

void remove_key(Dictionary *dict, int key) {
    for (int i = 0; i < dict->size; i++) {
        if (dict->keys[i] == key) {
            dict->keys[i] = dict->keys[--dict->size];
            dict->values[i] = dict->values[dict->size];
            break;
        }
    }
}

int maxOperations(int* nums, int numsSize, int k){
    Dictionary num_dict;
    init(&num_dict);
    int res=0; //result
    int ele; //element to check
    int matching_ele; // k-ele  :matching element value
    int tmp_value;  //for temporary usage

    for (int i=0; i<numsSize; i++){
        ele = nums[i];
        matching_ele = k-ele;
    
        tmp_value = get(&num_dict, matching_ele);
        if (tmp_value>0){
            put(&num_dict, matching_ele, tmp_value-1); // erase 1 if matching element exists(>1)
            res+=1; // raise 1 for matching operation
        }
        else {
            tmp_value=get(&num_dict, ele);
            if (tmp_value==-1){
                put(&num_dict, ele, 1);
            }
            else {
                put(&num_dict, ele, tmp_value+1);
            }
        }
    }

    return res;
