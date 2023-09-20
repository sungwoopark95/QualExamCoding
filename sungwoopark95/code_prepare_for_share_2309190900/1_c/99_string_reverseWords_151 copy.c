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

#include <string.h>

// reverse spelling for word
void reverseWord(char* s){
    int length = strlen(s);
    char temp;
    for (int i=0; i<length/2;i++){
        temp=s[i];
        s[i]=s[length-i-1];
        s[length-i-1]=temp;
    }
}

char * reverseWords(char * s){
    int length = strlen(s);
    char* res = (char*) malloc((length+1)*sizeof(char));//for final result
    char word[length+1]; // for immediate word
    int word_size=0; // for immediate word
    int idx=0; //index for inserting a word in res
    for (int i=length-1; i>=0; i--){
        if (s[i]!=' '){
            word[word_size]=s[i];
            word_size++;
        }
        else {
            if (word_size!=0) {
                word[word_size]='\0'; //end the string
                reverseWord(word); // reverse the word
                strncpy(res+idx, word, strlen(word)); //copy to res
                idx+=strlen(word); //update the index
                res[idx]=' '; //a space for next word
                idx++;//update the index
                word_size=0; //initialize immediate word
            }
            else {
                continue;

            }
        }
    }
    if (word_size!=0) {
        word[word_size]='\0'; //end the string
        reverseWord(word); // reverse the word
        strncpy(res+idx, word, strlen(word)); //copy to res
        idx+=strlen(word); //update the index
        res[idx]=' '; //a space for next word
        idx++;//update the index
    }
    res[idx-1]='\0';
    return res;

}