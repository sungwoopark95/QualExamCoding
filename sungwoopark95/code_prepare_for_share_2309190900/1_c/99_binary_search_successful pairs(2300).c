
/*
## 2300. Successful Pairs of Spells and Potions

 You are given two positive integer arrays spells and potions, of length n and m respectively, where spells[i] represents the strength of the ith spell and potions[j] represents the strength of the jth potion.
You are also given an integer success. A spell and potion pair is considered successful if the product of their strengths is at least success.
Return an integer array pairs of length n where pairs[i] is the number of potions that will form a successful pair with the ith spell.

Example 1:

Input: spells = [5,1,3], potions = [1,2,3,4,5], success = 7
Output: [4,0,3]
Explanation:
- 0th spell: 5 * [1,2,3,4,5] = [5,10,15,20,25]. 4 pairs are successful.
- 1st spell: 1 * [1,2,3,4,5] = [1,2,3,4,5]. 0 pairs are successful.
- 2nd spell: 3 * [1,2,3,4,5] = [3,6,9,12,15]. 3 pairs are successful.
Thus, [4,0,3] is returned.
Example 2: 
*/

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdio.h>
#include <math.h>
 
void merge(int* l, int start, int mid, int end) {
    int len1=mid-start+1;
    int len2=end-(mid+1)+1;
    int sub1[len1];
    int sub2[len2];
    memcpy(sub1, l+start, (len1)*sizeof(int)); 
    memcpy(sub2, l+mid+1, (len2)*sizeof(int));
    int k = start;
    int i = 0;
    int j = 0;
    while ((i<len1) && (j<len2)) {
        if (sub1[i]<sub2[j]) {
            l[k]=sub1[i];
            i++;
        }
        else {
            l[k]=sub2[j];
            j++;
        }
        k++;
    }
    if (i<len1) {
        memcpy(l+k, sub1+i, (len1-i)*sizeof(int));
    }
    if (j<len2){
        memcpy(l+k, sub2+j, (len2-j)*sizeof(int));
    }

}

void merge_sort(int* l, int start, int end) {
    if (start==end) {return;}
    int mid = start + (end-start)/2;
    merge_sort(l, start, mid);
    merge_sort(l, mid+1, end);
    merge(l, start, mid ,end);
}

int binary_search(int* l, int length, int val){
    // //case1) bing chat 버전
    // int start = 0;
    // int end = length;
    // int mid;
    // while (start<end){
    //     mid = start + (end - start)/2;
    //     if (l[mid]<val) {
    //         start = mid +1;
    //     }
    //     else {
    //         end=mid;
    //     }
    // }
    // return length-start;
    

    // //초기버전          
    // int start = 0;
    // int end = length-1;
    // int mid;
    // while (start<=end){
    //     mid = (start+end)/2;
    //     if (l[mid]<val) {
    //         start = mid +1;
    //     }
    //     else {
    //         end=mid-1;
    //     }
    // }
    // if ((start<length) && (l[start]>=val)) {
    //     return start;
    // }
    // // else if (start>=length) {
    // else {
    //     return length;
    // }

    // reform //54번째(/56) 케이스에서 자꾸 에러남..
    int start = 0;
    int end = length-1;
    int mid;
    while (start<end){
        mid = (start+end)/2;
        if (l[mid]<val) {
            start = mid +1;
        }
        else {
            end=mid;
        }
    }
    if ((start < length)&&(l[start]<val)){
        return 0;
    }
    else if ((start < length)&&(l[start]>=val)){
        return length-start;
    }
    else //(start >= length)
    { return length; }
}


int* successfulPairs(int* spells, int spellsSize, int* potions, int potionsSize, long long success, int* returnSize){
    merge_sort(potions, 0, potionsSize-1);
    int* res;
    res = (int*) malloc(spellsSize*sizeof(int));
    int threshold;
    for (int i=0;i<spellsSize;i++){
        threshold = (int)(ceil((double)success / spells[i]));
        // res[i] = potionsSize - binary_search(potions, potionsSize, threshold);
        res[i] =binary_search(potions, potionsSize, threshold);
    }
    *returnSize=spellsSize;
    return res;
}