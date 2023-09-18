#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/* ===================== 더해서 n이 되는 모든 k개의 정수 조합을 찾는 함수 ===================== */
vector<vector<int>> sum_comb(int n, int k, vector<int> current = {}, int start = 1) {
    // n이 0이고, k도 0인 경우 현재 조합(current)이 원하는 조합이므로 반환합니다.
    if (k == 0 && n == 0) {
        return {current};
    }
    // k가 0이거나 n이 0보다 작은 경우 유효하지 않은 조합이므로 빈 리스트를 반환합니다.
    if (k == 0 || n < 0) {
        return {};
    }

    vector<vector<int>> result;
    // start에서 n까지 순회하면서 가능한 조합을 탐색합니다.
    for (int i = start; i <= n; ++i) {
        auto temp = sum_comb(n - i, k - 1, current, i);
        current.push_back(i);
        result.insert(result.end(), temp.begin(), temp.end());
    }

    return result;
}
/* ==================================================================================== */

/* ==================================== My Code ======================================= */
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> ans;
    // 1부터 target까지의 정수에 대해 각각의 정수를 포함하는 조합을 탐색합니다.
    for (int i = 1; i <= target; ++i) {
        // target을 만드는 i개의 조합을 탐색합니다.
        auto combinations = sum_comb(target, i);
        // 찾은 각 조합에 대해 처리합니다.
        for (auto& comb : combinations) {
            bool flag = true;
            // 조합의 각 요소가 candidates에 포함되어 있는지 확인합니다.
            for (auto& element : comb) {
                if (find(candidates.begin(), candidates.end(), element) == candidates.end()) {
                    flag = false;
                }
            }
            // 모든 요소가 candidates에 포함되어 있고, 해당 조합이 ans에 없으면 ans에 추가합니다.
            if (flag && find(ans.begin(), ans.end(), comb) == ans.end()) {
                ans.push_back(comb);
            }
        }
    }
    return ans;
}
/* ===================================================================================== */

/* ==================================== ChatGPT 코드 ==================================== */
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> result;

    function<void(int, vector<int>&, int)> backtrack = [&](int remaining, vector<int>& combo, int start) {
        if (remaining == 0) {
            // 잔여 합계가 0이면 현재 조합을 결과에 추가합니다.
            result.push_back(combo);
            return;
        } else if (remaining < 0) {
            // 잔여 합계가 0보다 작으면 더 이상의 조합을 탐색할 필요가 없습니다.
            return;
        }

        for (int i = start; i < candidates.size(); ++i) {
            // 현재 숫자를 조합에 추가하고, 백트래킹을 통해 가능한 조합을 탐색합니다.
            combo.push_back(candidates[i]);
            backtrack(remaining - candidates[i], combo, i);
            // 백트래킹을 위해 마지막에 추가된 숫자를 제거합니다.
            combo.pop_back();
        }
    };

    vector<int> combo;
    backtrack(target, combo, 0);
    return result;
}
/* ===================================================================================== */

int main() {
    vector<int> candidates = {2};
    int target = 1;
    auto result = combinationSum(candidates, target);
    for (auto& vec : result) {
        for (int num : vec) {
            cout << num << " ";
        }
        cout << endl;
    }
    return 0;
}
