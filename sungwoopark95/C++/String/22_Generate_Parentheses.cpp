#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <functional>
using namespace std;

//######################################## MY CODE - TIME LIMIT ########################################
bool isValid(const string& s) {
    if (s.size() % 2 == 1) {
        return false;
    }
    unordered_map<char, char> valid = {{'(', ')'}, {'{', '}'}, {'[', ']'}};
    vector<char> stack;
    for (char c : s) {
        if (valid.count(c)) {
            stack.push_back(c);
        } else {
            if (stack.empty() || valid[stack.back()] != c) {
                return false;
            }
            stack.pop_back();
        }
    }
    return stack.empty();
}

vector<string> str_perm(string s) {
    vector<string> permutation_lst;

    function<void(int)> backtrack = [&](int start) {
        if (start == s.size()) {
            if (find(permutation_lst.begin(), permutation_lst.end(), s) == permutation_lst.end()) {
                permutation_lst.push_back(s);
            }
            return;
        }
        for (int i = start; i < s.size(); i++) {
            swap(s[start], s[i]);
            backtrack(start + 1);
            swap(s[start], s[i]);
        }
    };
    backtrack(0);
    return permutation_lst;
}

vector<string> generateParenthesis(int n) {
    string candidate = string(n, '(') + string(n, ')');
    vector<string> perms = str_perm(candidate);
    vector<string> ans;
    for (const string& perm : perms) {
        if (isValid(perm)) {
            ans.push_back(perm);
        }
    }
    return ans;
}
//######################################################################################################

//############################################## Chat GPT ##############################################
// # generate 함수는 재귀적으로 괄호의 조합을 생성합니다.
// # p: 현재까지 만들어진 괄호의 조합 문자열
// # left: 사용할 수 있는 남은 여는 괄호의 수
// # right: 사용할 수 있는 남은 닫는 괄호의 수
// # parens: 지금까지 만들어진 모든 괄호의 조합 리스트
vector<string> generateParenthesis(int n) {
    vector<string> parens;

    function<void(string, int, int)> generate = [&](string p, int left, int right) {
        // # 만약 남은 여는 괄호가 있다면, 현재의 조합 문자열에 여는 괄호를 추가합니다.
        // # 그리고 남은 여는 괄호의 수를 하나 줄입니다.
        if (left) {
            generate(p + '(', left-1, right);
        }
        // # 닫는 괄호의 남은 수가 여는 괄호의 남은 수보다 많다면,
        // # 현재의 조합 문자열에 닫는 괄호를 추가합니다.
        // # 그리고 남은 닫는 괄호의 수를 하나 줄입니다.
        if (right > left) {
            generate(p + ')', left, right-1);
        }
        // # 더 이상 사용할 닫는 괄호가 없다면, 현재 괄호 조합을 결과 목록에 추가합니다.
        // # 이는 올바른 괄호 조합이 완성된 경우입니다.
        if (!right) {
            parens.push_back(p);
        }
    };
    // # generate 함수를 호출하여 올바른 괄호의 조합을 생성하고 반환합니다.
    // # 처음에는 아무런 괄호도 없는 상태로 시작하며, n개의 여는 괄호와 n개의 닫는 괄호를 사용할 수 있습니다.
    generate("", n, n);
    return parens;
}
//######################################################################################################

int main() {
    int n = 4;
    vector<string> result = generateParenthesis(n);
    for (const string& s : result) {
        cout << s << endl;
    }
    return 0;
}
