#include <string>
#include <iostream>
#include <cmath>
using namespace std;

int myAtoi(string s) {
    // 숫자를 위한 사전 문자열을 초기화합니다.
    string dictionary = "0123456789";
    
    // 32비트 signed int의 최소 및 최대 값을 설정합니다.
    int int_min = -(pow(2, 31));
    int int_max = (pow(2, 31)) - 1;

    // 숫자가 시작되는 위치를 찾기 위한 초기 위치 설정
    int start = -1;
    
    // 입력 문자열 s의 각 문자를 확인하면서 첫 번째 숫자가 나오는 위치를 찾습니다.
    for (int i = 0; i < s.size(); i++) {
        if (dictionary.find(s[i]) != string::npos) {
            start = i;
            break;
        }
    }
    
    // 시작 인덱스 출력
    // cout << "start idx: " << start << endl;

    // 결과를 저장할 문자열 초기화
    string result = "";
    
    // 부호를 확인하기 위한 플래그 초기화
    bool sign_flag = false;
    
    // 입력 문자열 s를 순회하며 유효한 문자들을 결과 문자열에 추가합니다.
    for (int j = 0; j < s.size(); j++) {
        // 현재 문자와 인덱스 출력
        // cout << "j: " << j << ", c: " << s[j] << ", length: " << 1 << endl;
        
        // 현재 문자가 '+' 또는 '-'인 경우
        if (s[j] == '+' || s[j] == '-') {
            // 아직 숫자가 시작되지 않았고, 부호가 설정되지 않았을 때 부호 추가
            if (j < start && !sign_flag) {
                result += s[j];
                sign_flag = true;
            } else {
                break;
            }
        } else if (s[j] == ' ') { // 현재 문자가 공백인 경우
            if (j < start) {
                if (j == 0) {
                    continue;
                }
                if (j > 0 && s[j-1] == ' ') {
                    continue;
                } else {
                    break;
                }
            } else {
                break;
            }
        } else if (s[j] == '.') { // 현재 문자가 '.'인 경우, 더 이상 문자를 처리하지 않고 종료
            break;
        } else if (dictionary.find(s[j]) == string::npos) { // 현재 문자가 숫자가 아닌 경우
            break;
        } else {
            result += s[j]; // 숫자인 경우 결과 문자열에 추가
        }
    }

    // 현재까지 얻은 결과 출력
    // cout << result << endl;
    
    // 결과 문자열이 비어있거나, '+' 또는 '-'만 있는 경우 0 반환
    if (result.empty() || result == "+" || result == "-") {
        return 0;
    }
    
    // 문자열을 숫자로 변환
    long long num = stoll(result);
    
    // 변환된 숫자가 범위를 벗어난 경우, 해당 범위로 조정하여 반환
    if (num < int_min) {
        return int_min;
    }
    if (num > int_max) {
        return int_max;
    }
    
    // 조정된 숫자 반환
    return num;
}

int main() {
    vector<string> test_cases = {"42", "  +  413", "words and 987", "+-419332", "-4193-3219-22", "   -42", "42.195", "42 195"};

    for (string item : test_cases) {
        cout << item << " -> " << myAtoi(item) << endl;
    }

    return 0;
}
