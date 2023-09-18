#include <iostream>
#include <vector>
#include <string>
#include <functional> // 함수 객체를 위해 필요

using namespace std;

/* ================== 주어진 문자열의 모든 순열을 반환하는 함수 ================== */
vector<string> str_perm(string s) {
    vector<string> permutation_lst;

    // 백트래킹을 위한 재귀 함수 정의
    function<void(int)> backtrack = [&](int start) {
        // 기본 케이스: 문자열의 모든 위치를 검사했을 때
        if (start == s.size()) {
            permutation_lst.push_back(s);
            return;
        }
        
        // 시작 위치부터 문자열의 끝까지 순회
        for (int i = start; i < s.size(); ++i) {
            // 문자 위치 교환
            swap(s[start], s[i]);
            // 다음 위치로 재귀 호출
            backtrack(start + 1);
            // 백트래킹: 원래의 문자 위치로 복구
            swap(s[start], s[i]);
        }
    };

    // 백트래킹 시작
    backtrack(0);
    return permutation_lst;
}
/* ====================================================================== */

/* ================ 주어진 정수 리스트의 모든 순열을 반환하는 함수 ================= */
vector<vector<int>> int_perm(vector<int> nums) {
    vector<vector<int>> permutation_lst;

    // 백트래킹을 위한 재귀 함수 정의
    function<void(int)> backtrack = [&](int start) {
        // 기본 케이스: 리스트의 모든 위치를 검사했을 때
        if (start == nums.size()) {
            permutation_lst.push_back(nums);
            return;
        }

        // 시작 위치부터 리스트의 끝까지 순회
        for (int i = start; i < nums.size(); ++i) {
            // 정수 위치 교환
            swap(nums[start], nums[i]);
            // 다음 위치로 재귀 호출
            backtrack(start + 1);
            // 백트래킹: 원래의 정수 위치로 복구
            swap(nums[start], nums[i]);
        }
    };

    // 백트래킹 시작
    backtrack(0);
    return permutation_lst;
}
/* ====================================================================== */

int main() {
    vector<int> nums = {3, 2, 1};
    vector<vector<int>> result = int_perm(nums);

    // 결과 출력
    for (const auto& perm : result) {
        for (int num : perm) {
            cout << num << " ";
        }
        cout << endl;
    }

    return 0;
}
