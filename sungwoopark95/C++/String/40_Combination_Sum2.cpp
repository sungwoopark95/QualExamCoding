/*
주어진 후보 숫자 집합(candidates)과 목표 숫자(target)가 있을 때, 후보 숫자의 합이 목표 숫자가 되는 모든 유일한 조합을 찾아야 합니다.
각 후보 숫자는 조합에서 한 번만 사용될 수 있습니다.
참고: 결과 집합에는 중복된 조합이 포함되어서는 안 됩니다.

예시 1:
입력: candidates = [10,1,2,7,6,1,5], target = 8
출력:
[
[1,1,6],
[1,2,5],
[1,7],
[2,6]
]

예시 2:
입력: candidates = [2,5,2,1,2], target = 5
출력:
[
[1,2,2],
[5]
]
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/* ================================= My Code ================================= */
vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    // 결과를 저장할 2D 벡터와 현재 조합을 저장할 벡터 초기화
    vector<vector<int>> result, unique_result;
    vector<int> combo;

    // 백트래킹 함수 정의 (람다 함수 사용)
    function<void(int, int, vector<int>&)> backtrack = [&](int remaining, int start, vector<int>& combo) {
        // 만약 남은 타겟이 0이면 현재 조합을 unique_result에 추가
        if (remaining == 0) {
            unique_result.push_back(combo);
            return;
        } else if (remaining < 0) { // 남은 타겟이 음수면 종료
            return;
        }

        // start부터 후보 숫자를 하나씩 조합에 추가해 본다.
        for (int i = start; i < candidates.size(); i++) {
            combo.push_back(candidates[i]);
            backtrack(remaining - candidates[i], i + 1, combo); // 재귀적으로 다음 숫자 탐색
            combo.pop_back(); // 백트래킹: 마지막에 추가된 숫자 제거
        }
    };

    // 후보 숫자 정렬
    sort(candidates.begin(), candidates.end());
    backtrack(target, 0, combo); // 백트래킹 시작

    // unique_result에 중복되지 않은 조합만 result에 추가
    for (vector<int>& item : unique_result) {
        if (find(result.begin(), result.end(), item) == result.end()) {
            result.push_back(item);
        }
    }
    return result; // 결과 반환
}
/* =============================================================================== */

/* =================================== ChatGPT =================================== */
vector<vector<int>> combinationSum2Opt(vector<int>& candidates, int target) {
    vector<vector<int>> res;
    vector<int> path;
    sort(candidates.begin(), candidates.end()); // 후보 숫자 정렬

    // 백트래킹 함수 정의 (람다 함수 사용)
    function<void(int, int, vector<int>&)> backtrack = [&](int start, int target, vector<int>& path) {
        if (target == 0) {
            res.push_back(path); // 타겟이 0이면 경로 저장
            return;
        }
        for (int i = start; i < candidates.size(); i++) {
            if (i > start && candidates[i] == candidates[i-1]) continue; // 중복된 숫자 건너뛰기
            if (candidates[i] > target) break; // 현재 숫자가 타겟보다 크면 종료
            path.push_back(candidates[i]); // 현재 숫자 경로에 추가
            backtrack(i + 1, target - candidates[i], path); // 재귀적으로 다음 숫자 탐색
            path.pop_back(); // 백트래킹: 마지막에 추가된 숫자 제거
        }
    };

    backtrack(0, target, path); // 백트래킹 시작
    return res; // 결과 반환
}
/* =============================================================================== */

int main() {
    // 테스트 케이스
    vector<int> candidates = {10,1,2,7,6,1,5};
    int target = 8;
    vector<vector<int>> result = combinationSum2Opt(candidates, target);

    // 결과 출력
    for (vector<int>& vec : result) {
        for (int num : vec) {
            cout << num << " ";
        }
        cout << endl;
    }
    return 0;
}
