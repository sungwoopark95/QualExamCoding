#include <iostream>
#include <string>
using namespace std;

int scoreOfParentheses(string s) {
    // 기본 경우
    // 빈 문자열은 점수 0을 가집니다.
    if (s == "") {
        return 0;
    }
    // "()" 문자열은 점수 1을 가집니다.
    if (s == "()") {
        return 1;
    }

    // 괄호의 균형을 추적하고 문자열을 분할하는 데 사용됩니다.
    int balance = 0;
    for (int i = 0; i < s.size(); ++i) {
        char c = s[i];
        // 열린 괄호('(')를 만나면 균형 점수를 1 증가시킵니다.
        if (c == '(') {
            balance += 1;
        }
        // 닫힌 괄호(')')를 만나면 균형 점수를 1 감소시킵니다.
        else {
            balance -= 1;
        }
        // 괄호의 균형이 맞는 경우 문자열을 분할합니다.
        if (balance == 0) {
            // 괄호의 균형이 문자열의 끝에서 발견되는 경우
            if (i == s.size() - 1) {
                // 내부 괄호 문자열의 점수를 재귀적으로 계산한 후 2를 곱합니다.
                return 2 * scoreOfParentheses(s.substr(1, i - 1));
            }
            // 괄호의 균형이 문자열 중간에서 발견되는 경우
            else {
                // 괄호 문자열을 두 부분으로 분할하고 각 부분의 점수를 재귀적으로 계산한 후 합합니다.
                return scoreOfParentheses(s.substr(0, i + 1)) + scoreOfParentheses(s.substr(i + 1));
            }
        }
    }
    return 0;  // 이 부분은 실행되지 않아야 하지만, 컴파일러의 모든 경로에 반환 값이 있어야 한다는 경고를 피하기 위해 추가됩니다.
}

int main() {
    string input;
    
    cout << "Balanced parentheses string을 입력하세요: ";
    getline(cin, input);
    // cout << input << endl;
    
    cout << "해당 문자열의 점수는: " << scoreOfParentheses(input) << endl;

    return 0;
}