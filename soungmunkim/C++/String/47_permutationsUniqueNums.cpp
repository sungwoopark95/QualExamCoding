/*
[주어진 정수 배열 nums에서 가능한 모든 고유한 순열을 생성하는 함수]

Given a collection of numbers, nums, that might contain duplicates, return all possible unique permutations in any order.


Example 1:
Input: nums = [1,1,2]
Output:
[[1,1,2],
 [1,2,1],
 [2,1,1]]
 
Example 2:
Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <sstream>

using namespace std;

// 백트래킹 함수를 미리 선언합니다.
void backtrack(int start, vector<int>& nums, vector<vector<int>>& permutations);

// 주어진 숫자 배열에서 가능한 모든 순열을 생성하는 함수입니다.
vector<vector<int>> permuteUnique(vector<int>& nums) {
    vector<vector<int>> permutations;  // 결과 순열을 저장할 벡터
    sort(nums.begin(), nums.end());    // 순열을 생성하기 전에 배열을 정렬합니다.

    // 순열 생성 시작
    backtrack(0, nums, permutations);

    return permutations;
}

// 백트래킹을 사용해 순열을 생성하는 도우미 함수
void backtrack(int start, vector<int>& nums, vector<vector<int>>& permutations) {
    // start가 nums의 크기와 같으면 하나의 순열이 완성된 것입니다.
    if (start == nums.size()) {
        permutations.push_back(nums);
        return;
    }
    for (int i = start; i < nums.size(); ++i) {
        // 중복 순열을 피하기 위한 조건
        if (i != start && nums[i] == nums[start]) continue;

        // 현재 요소와 그 이후의 요소들을 교환합니다.
        swap(nums[start], nums[i]);

        // 다음 위치로 재귀 호출합니다.
        backtrack(start + 1, nums, permutations);

        // 교환한 요소들을 원래대로 복원합니다.
        swap(nums[start], nums[i]);
    }
}

int main() {
    vector<int> nums;
    int num;
    string input;
    
    cout << "Enter numbers in the format [a,b,c,...]: ";
    getline(cin, input); // 입력 받기

    // 대괄호와 쉼표 제거 및 공백으로 대체
    for (char &c : input) {
        if (c == ',' || c == '[' || c == ']') {
            c = ' ';
        }
    }
    
    istringstream iss(input);
    while (iss >> num) {
        nums.push_back(num);
    }

    auto result = permuteUnique(nums);
    for (const auto& perm : result) {
        for (int num : perm) {
            cout << num << ' ';
        }
        cout << '\n';
    }

    return 0;
}
