#include <iostream>
#include <vector>
#include <string>

using namespace std;

/* ========================= 리스트에서 정해진 길이만큼의 조합을 만드는 함수 ========================= */
vector<vector<int>> list_comb(const vector<int>& nums, int length) {
    // 결과를 저장할 벡터
    vector<vector<int>> output;

    // 백트래킹 함수 정의
    function<void(int, int, vector<int>&)> backtrack = 
    [&](int start, int length, vector<int>& path) {
        // 기저 조건
        if (path.size() == length) {
            output.push_back(path);
            return;
        }
        for (int i = start; i < nums.size(); ++i) {
            path.push_back(nums[i]);
            backtrack(i + 1, length, path);
            path.pop_back();
        }
    };

    if (length > nums.size()) {
        cout << "length cannot be greater than the length of nums" << endl;
        return {};
    }

    vector<int> temp;
    backtrack(0, length, temp);
    return output;
}
/* ======================================================================================= */

/* ========================= 문자열에서 정해진 길이만큼의 조합을 만드는 함수 ========================= */
vector<string> str_comb(const string& nums, int length) {
    vector<string> output;

    // 백트래킹 함수 정의
    function<void(int, int, string&)> backtrack = 
    [&](int start, int length, string& path) {
        if (path.size() == length) {
            output.push_back(path);
            return;
        }
        for (int i = start; i < nums.size(); ++i) {
            path.push_back(nums[i]);
            backtrack(i + 1, length, path);
            path.pop_back();
        }
    };

    if (length > nums.size()) {
        cout << "length cannot be greater than the length of nums" << endl;
        return {};
    }

    string temp;
    backtrack(0, length, temp);
    return output;
}
/* ======================================================================================= */

/* ======================== 더해서 n이 되는 모든 k개의 정수 조합을 찾는 함수 ======================== */
vector<vector<int>> sum_comb(int n, int k, int start = 1) {
    if (k == 0 && n == 0) return {{}};

    if (k == 0 || n < 0) return {};

    vector<vector<int>> result;
    for (int i = start; i <= n; ++i) {
        for (const auto& arr : sum_comb(n - i, k - 1, i)) {
            result.push_back({i});
            result.back().insert(result.back().end(), arr.begin(), arr.end());
        }
    }
    return result;
}
/* ======================================================================================= */

int main() {
    // 예제 테스트
    auto lst = list_comb({1, 2, 3}, 2);
    for (const auto& v : lst) {
        for (int n : v) {
            cout << n << " ";
        }
        cout << endl;
    }

    auto str_lst = str_comb("str", 2);
    for (const auto& s : str_lst) {
        cout << s << " ";
    }
    cout << endl;

    auto sum_lst = sum_comb(4, 3);
    for (const auto& v : sum_lst) {
        for (int n : v) {
            cout << n << " ";
        }
        cout << endl;
    }

    return 0;
}