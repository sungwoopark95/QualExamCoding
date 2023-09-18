#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
using namespace std;

// ################################### MY CODE - TIME LIMIT ###################################
// 문자열의 유효성 검사 함수
bool isValid(const string& s) {
    if (s.length() % 2 == 1) {
        return false;
    }
    unordered_map<char, char> valid = {{'(', ')'}, {'{', '}'}, {'[', ']'}};
    stack<char> stack;
    
    for (char c : s) {
        if (valid.find(c) != valid.end()) {
            stack.push(c);
        } else {
            if (stack.empty() || valid[stack.top()] != c) {
                return false;
            }
            stack.pop();
        }
    }

    return stack.empty();
}

int longestValidParentheses(const string& s) {
    if (s.length() < 2) {
        return 0;
    }
    
    vector<string> valid_substring;
    for (int i = 0; i < s.length(); ++i) {
        for (int j = i + 1; j <= s.length(); ++j) {
            string substring = s.substr(i, j-i);
            if (isValid(substring)) {
                valid_substring.push_back(substring);
            }
        }
    }
    
    if (valid_substring.empty()) {
        return 0;
    }
    
    int max_len = -1;
    for (const auto& item : valid_substring) {
        if (max_len < item.length()) {
            max_len = item.length();
        }
    }

    return max_len;
}
// ################################### MY CODE - TIME LIMIT ###################################

// ######################################### ChatGPT #########################################
int longestValidParentheses(const string& s) {
    int left = 0, right = 0, maxlength = 0; // 여는 괄호와 닫는 괄호의 개수 및 최대 길이 초기화
    
    // 첫 번째 순회: 왼쪽에서 오른쪽으로 문자열을 순회합니다.
    for(int i = 0; i < s.length(); i++) {
        if (s[i] == '(') {
            left++; // 여는 괄호의 경우 left 카운터 증가
        } else {
            right++; // 닫는 괄호의 경우 right 카운터 증가
        }
        if (left == right) {
            // 여는 괄호와 닫는 괄호의 수가 동일한 경우, 최대 길이 업데이트
            maxlength = max(maxlength, 2*right);
        } else if (right >= left) {
            // 닫는 괄호의 수가 더 많을 경우, 카운터 초기화
            left = 0;
            right = 0;
        }
    }
    
    left = 0;  // 카운터 초기화
    right = 0; // 카운터 초기화
    
    // 두 번째 순회: 오른쪽에서 왼쪽으로 문자열을 순회합니다.
    for(int i = s.length() - 1; i >= 0; i--) {
        if (s[i] == '(') {
            left++; // 여는 괄호의 경우 left 카운터 증가
        } else {
            right++; // 닫는 괄호의 경우 right 카운터 증가
        }
        if (left == right) {
            // 여는 괄호와 닫는 괄호의 수가 동일한 경우, 최대 길이 업데이트
            maxlength = max(maxlength, 2*left);
        } else if (left >= right) {
            // 여는 괄호의 수가 더 많을 경우, 카운터 초기화
            left = 0;
            right = 0;
        }
    }
    
    return maxlength; // 최대 길이 반환
}
// ######################################### ChatGPT #########################################

int main() {
    string s;
    getline(cin, s);  // 문자열 입력 받기
    cout << longestValidParentheses(s) << endl;
    return 0;
}
