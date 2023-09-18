/*
[유효한 parentheses 점수 계산하기]

valid한 stack인지 체크하는 함수
    -> valid 하지 않으면 -1 return
    
valid parethese일 경우 score = 1
A + B 형태일 경우 score + score
(A) 같은 형태일 경우 score * 2

stack에 각 점수를 넣고 열림도 0으로 stack에 표시하며 문제 품

Example 1:
Input: s = "()"
Output: 1

Example 2:
Input: s = "(())"
Output: 2

Example 3:
Input: s = "()()"
Output: 2

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
String: (), Score: 1
String: (()), Score: 2
String: [], Score: 1
String: {}, Score: 1
String: ([]), Score: 2
String: (())[]{}, Score: 4
String: ((())[]{}[]()), Score: 12
*/

#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

// 유효한 괄호 문자열인지 확인하는 함수
bool is_valid(const string& s) {
    stack<char> st;  // 스택을 이용해 괄호 쌍을 확인
    for (char ch : s) {
        if (ch == '(' || ch == '[' || ch == '{') {  // 여는 괄호인 경우
            st.push(ch);
        } else {  // 닫는 괄호인 경우
            if (st.empty()) return false;  // 스택이 비어있으면 유효하지 않음
            char open_bracket = st.top(); st.pop();
            if (ch == ')' && open_bracket != '(') return false;
            if (ch == ']' && open_bracket != '[') return false;
            if (ch == '}' && open_bracket != '{') return false;
        }
    }
    return st.empty();  // 스택이 비어 있으면 유효한 괄호 문자열
}

// 괄호 문자열의 점수를 계산하는 함수 
int score(const string& s) {
    if (!is_valid(s)) return -1;  // 문자열이 유효하지 않으면 -1 반환

    stack<int> st;  // 점수를 계산하기 위한 스택 초기화
    for (char ch : s) {
        if (ch == '(' || ch == '[' || ch == '{') {  // 여는 괄호인 경우
            st.push(0);  // 0을 스택에 추가하여 여는 괄호를 표시합니다.
        } else {
            if (st.top() == 0) {  // 괄호의 쌍이 바로 연속된 경우 (예: '()')
                st.pop();  // 여는 괄호를 표시하는 0 제거
                st.push(1);  // 점수 1 추가
            } else {
                int curr = 0;  // 현재 계산 중인 점수 초기화
                while (st.top() != 0) {  // 스택의 최상위 요소가 숫자인 동안
                    curr += st.top(); st.pop();  // 여는 괄호가 나올 때까지 숫자를 추출해 curr에 더함
                }
                st.pop();  // 여는 괄호를 표시하는 0 제거
                st.push(curr * 2);  // 괄호 안의 점수 * 2를 스택에 추가
            }
        }
    }

    int result = 0;
    while (!st.empty()) {  // 스택에 있는 모든 점수 합산
        result += st.top();
        st.pop();
    }
    return result;
}

int main() {
    vector<string> test_strs = {
        "()",
        "(())",
        "[]",
        "{}",
        "([])",
        "(())[]{}",
        "((())[]{}[]())"
    };

    for (const string& test_str : test_strs) {
        cout << "String: " << test_str << ", Score: " << score(test_str) << endl;
    }

    return 0;
}
