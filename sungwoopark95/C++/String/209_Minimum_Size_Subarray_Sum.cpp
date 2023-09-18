/*
합이 target보다 같은 subarray 가운데 길이가 가장 짧은 subarray의 길이를 반환하는 함수
Input: target = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: The subarray [4,3] has the minimal length under the problem constraint.

Input: target = 4, nums = [1,4,4]
Output: 1

Input: target = 11, nums = [1,1,1,1,1,1,1,1]
Output: 0
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>  // for accumulate
#include <functional> // for std::function
#include <climits> // for INT_MAX

using namespace std;

/* ================================== list2가 list1의 부분 배열인지 확인 =================================== */
bool isSubarray(vector<int>& list1, vector<int>& list2) {
    // list2의 첫 번째 요소의 인덱스를 찾습니다.
    int start_idx = -1;
    for (int i = 0; i < list1.size(); i++) {
        if (list1[i] == list2[0]) {
            start_idx = i;
            break;
        }
    }

    // list2의 첫 번째 요소가 list1에 없으면 False 반환
    if (start_idx == -1) {
        return false;
    }

    // start_idx부터 list2의 모든 요소가 list1에 순서대로 있는지 확인
    for (int j = 0; j < list2.size(); j++) {
        if (list1[start_idx + j] != list2[j]) {
            return false;
        }
    }
    return true;
}

/* ===================== target보다 sum이 크거나 같은 subarray 가운데 최소 길이를 찾는 작업 ======================= */
int minSubArrayLen(int target, vector<int>& nums) {
    if (accumulate(nums.begin(), nums.end(), 0) < target) {
        return 0;
    }

    vector<vector<int>> result;

    function<void(int, vector<int>&, int)> backtrack = [&](int remaining, vector<int>& combo, int start) {
        if (remaining <= 0 && isSubarray(nums, combo)) {
            result.push_back(combo);
            return;
        }

        for (int i = start; i < nums.size(); i++) {
            if (i > start && nums[i] == nums[i - 1]) {
                continue;
            }
            combo.push_back(nums[i]);
            backtrack(remaining - nums[i], combo, i + 1);
            combo.pop_back();
        }
    };

    vector<int> combo;
    backtrack(target, combo, 0);

    int min_len = INT_MAX;
    for (const auto& item : result) {
        if (min_len > item.size()) {
            min_len = item.size();
        }
    }
    return min_len;
}

/* ================================== Two-point window 사용하는 Chat GPT =================================== */
int min_subarray_length(int target, vector<int>& nums) {
    // left: 부분 배열의 시작 인덱스
    // total: 현재 부분 배열의 합
    // min_len: target 이상의 합을 가진 최소 길이의 부분 배열 길이
    int left = 0;
    int total = 0;
    int min_len = INT_MAX;

    // nums 배열을 순회하면서 각 원소를 right로 참조
    for (int right = 0; right < nums.size(); right++) {
        // 현재 원소(nums[right])를 total에 더함
        total += nums[right];

        // 현재 부분 배열의 합(total)이 target보다 크거나 같은 경우
        while (total >= target) {
            // 최소 길이 부분 배열을 찾기 위해, 현재 부분 배열의 길이(right - left + 1)와 
            // 이전까지의 최소 길이(min_len) 중 작은 값을 선택
            min_len = min(min_len, right - left + 1);
            
            // 부분 배열의 합에서 가장 왼쪽 원소(nums[left])를 뺌
            total -= nums[left];
            
            // left 포인터를 오른쪽으로 이동시킴
            left++;
        }
    }

    // 최소 길이 부분 배열을 찾았다면 그 길이(min_len)를 반환하고, 찾지 못했다면 0을 반환
    return (min_len != INT_MAX) ? min_len : 0;
}

int main() {
    vector<int> nums = {2,3,1,2,4,3};
    int target = 7;
    cout << min_subarray_length(target, nums) << endl;
    return 0;
}