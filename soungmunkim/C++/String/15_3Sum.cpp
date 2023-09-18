/*
[3 Sum]
서로 다른 위치들 값 다 더해서 0이 나오는 조합 찾기

Example 1:
Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation: 
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
The distinct triplets are [-1,0,1] and [-1,-1,2].
Notice that the order of the output and the order of the triplets does not matter.

Example 2:
Input: nums = [0,1,1]
Output: []
Explanation: The only possible triplet does not sum up to 0.

Example 3:
Input: nums = [0,0,0]
Output: [[0,0,0]]
Explanation: The only possible triplet sums up to 0.

(base) soungmunkim@gimseongmun-ui-MacBookPro String % g++ -std=c++17 15_3Sum.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test    
[[-1, 0, 1], [-1, -1, 2]]
[]
[[0, 0, 0]]
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>

using namespace std;

/* ========================= 리스트에서 정해진 길이만큼의 조합을 만드는 함수 ========================= */
/* 리스트에서 정해진 길이만큼의 조합을 만드는 함수 */
vector<vector<int>> list_comb(const vector<int>& nums, int length) {
    // 결과를 저장할 벡터 선언
    vector<vector<int>> output;

    // 백트래킹 함수 정의
    function<void(int, int, vector<int>&)> backtrack = 
    [&](int start, int length, vector<int>& path) {
        // 기저 조건: path의 길이가 요구되는 길이와 같다면
        if (path.size() == length) {
            output.push_back(path);  // path를 output에 추가
            return;
        }
        for (int i = start; i < nums.size(); ++i) {
            path.push_back(nums[i]);  // 현재의 숫자를 path에 추가
            backtrack(i + 1, length, path);  // 재귀적으로 백트래킹
            path.pop_back();  // 백트래킹: 마지막에 추가된 숫자 제거
        }
    };

    // 요구되는 길이가 주어진 리스트의 길이보다 크면 에러 메시지 출력 후 빈 벡터 반환
    if (length > nums.size()) {
        cout << "length cannot be greater than the length of nums" << endl;
        return {};
    }

    vector<int> temp;  // 백트래킹 함수를 위한 임시 벡터 선언
    backtrack(0, length, temp);  // 백트래킹 시작
    return output;  // 완성된 조합들의 벡터 반환
}




// 벡터 내에 특정 벡터 값이 있는지 확인하는 함수
bool in(const vector<vector<int>>& container, const vector<int>& element) {
    return find(container.begin(), container.end(), element) != container.end();
}

// 3개의 정수 조합 중 합이 0이 되는 조합을 찾는 함수
vector<vector<int>> threeSum(vector<int>& nums) {
    // 3개 조합의 리스트를 얻는다.
    vector<vector<int>> three_comb = list_comb(nums, 3);
    vector<vector<int>> ans;  // 결과를 저장할 벡터 선언
    
    for (vector<int> comb : three_comb) {  // 모든 조합을 반복
        if (accumulate(comb.begin(), comb.end(), 0) == 0) {  // 조합의 합이 0이라면
            sort(comb.begin(), comb.end());  // 조합을 정렬
            if (!in(ans, comb)) {  // 결과 벡터에 동일한 조합이 없으면 추가
                ans.push_back(comb);
            }
        }
    }

    return ans;  // 결과 반환
}

void printResults(const vector<vector<int>>& results) {
    cout << "[";
    for (size_t i = 0; i < results.size(); ++i) {
        const vector<int>& result = results[i];
        cout << "[";
        for (size_t j = 0; j < result.size(); ++j) {
            cout << result[j];
            if (j < result.size() - 1) cout << ", ";
        }
        cout << "]";
        if (i < results.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    vector<int> nums = {-1, 0, 1, 2, -1, -4};
    vector<vector<int>> results = threeSum(nums);
    printResults(results);  // [[-1, 0, 1], [-1, -1, 2]]

    vector<int> nums1 = {0, 1, 1};
    results = threeSum(nums1);
    printResults(results);  // []

    vector<int> nums2 = {0, 0, 0};
    results = threeSum(nums2);
    printResults(results);  // [[0, 0, 0]]

    return 0;  // 프로그램 종료
}
