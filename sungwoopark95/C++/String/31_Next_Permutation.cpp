/*
주어진 배열의 순열 중에서 다음에 오는 순열(사전식 순서로 다음 순서)을 찾아야 합니다. 
만약 주어진 배열이 사전식 순서로 가장 큰 경우(내림차순으로 정렬된 경우)에는 가장 작은 순서(오름차순으로 정렬된 경우)로 배열을 변경합니다. 
주어진 배열을 직접 변경해야 하며, 상수 시간 복잡도를 가진 추가 메모리만을 사용해야 합니다.

Example 1:
Input: nums = [1,2,3]
Output: [1,3,2]

Example 2: 
Input: nums = [3,2,1]
Output: [1,2,3]

Example 3:
Input: nums = [1,1,5]
Output: [1,5,1]
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/* ================================================ permutation ================================================ */
void int_perm(int start, vector<int>& nums, vector<vector<int>>& permutation_lst) {
    if (start == nums.size() && find(permutation_lst.begin(), permutation_lst.end(), nums) == permutation_lst.end()) {
        permutation_lst.push_back(nums);
        return;
    }

    for (int i = start; i < nums.size(); i++) {
        // 현재 시작 인덱스와 루프의 인덱스 위치의 정수를 교환 (스왑)
        swap(nums[start], nums[i]);
        
        // 현재 시작 인덱스를 제외한 나머지 리스트에 대해 순열을 생성하기 위해 재귀적으로 호출
        int_perm(start + 1, nums, permutation_lst);
        
        // 이전 상태로 리스트를 복원하기 위해 다시 정수 위치를 교환 (백트래킹)
        swap(nums[start], nums[i]);
    }
}

void nextPermutation(vector<int>& nums) {
    vector<vector<int>> permList;
    int_perm(0, nums, permList);
    
    sort(permList.begin(), permList.end());
    
    auto it = find(permList.begin(), permList.end(), nums);
    
    if (it == permList.end() - 1) { // 마지막 순열의 경우 첫 번째 순열로 설정
        nums = permList[0];
    } else { // 그렇지 않은 경우 다음 순열로 설정
        nums = *(it + 1);
    }
}
/* ============================================================================================================= */

/* ================================================ two pointer ================================================ */
/*
Example
nums = [3,2,1]
i = 1 # len(nums) - 2
nums[i] = 2, nums[i+1] = 1 -> while loop 들어감, i -> 0
nums[i] = 3, nums[i+1] = 2 -> while loop 들어감, i -> -1, while 종료
i < 0이므로 if문 들어가지 않고 통과
nums[i+1:] = nums[0:] = nums 자체
nums[i+1:] = sorted(nums[i+1:]) -> nums = [1,2,3]
*/
void next_permutation(vector<int>& nums) {
    // i = nums.size() - 2로 설정하는 이유는 배열의 마지막 두 원소부터 시작해서 
    // 이전 원소와 비교하려는 의도 때문입니다.
    int i = nums.size() - 2;

    // i를 찾기: 내림차순이 깨지는 첫 번째 위치
    while (i >= 0 && nums[i] >= nums[i + 1]) {
        i--;
    }

    // i가 0보다 크거나 같은 경우, 즉 내림차순이 깨진 위치가 있는 경우
    if (i >= 0) {
        int j = nums.size() - 1;
        // j를 찾기: nums[i]보다 큰 첫 번째 원소
        while (nums[j] <= nums[i]) {
            j--;
        }
        // i와 j 위치의 원소 교환
        swap(nums[i], nums[j]);
    }

    // i 뒤의 원소들을 오름차순으로 정렬
    reverse(nums.begin() + i + 1, nums.end());
}
/* ============================================================================================================= */

int main() {
    // Example
    vector<int> nums = {1, 1, 5};
    next_permutation(nums);
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}
