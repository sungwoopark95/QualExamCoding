/*
[숫자패드에 letters가 써있는 핸드폰 생각하기]
[ 해당 숫자패드의 letters의 모든 조합 리턴하는 방식]

Given a string containing digits from 2-9 inclusive, 
return all possible letter combinations that the number could represent. 
Return the answer in any order.

A mapping of digits to letters (just like on the telephone buttons) is given below. 
Note that 1 does not map to any letters.


Enter a sequence of digits (2-9): 23
["ad","ae","af","bd","be","bf","cd","ce","cf"]

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Enter a sequence of digits (2-9): ""
[]

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Enter a sequence of digits (2-9): 2
["a","b","c"]

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test 23                                                
["ad","ae","af","bd","be","bf","cd","ce","cf"]

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test ""
[]

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test 2 
["a","b","c"]
*/

#include <iostream> // 입출력 관련 헤더파일
#include <vector>   // 벡터 사용을 위한 헤더파일
#include <string>   // 문자열 사용을 위한 헤더파일
#include <unordered_map> // 해시 맵 사용을 위한 헤더파일

using namespace std;

// 전화기 키패드에 해당하는 숫자와 문자열 매핑을 전역 변수로 정의
unordered_map<char, string> phone = {
    {'2', "abc"},
    {'3', "def"},
    {'4', "ghi"},
    {'5', "jkl"},
    {'6', "mno"},
    {'7', "pqrs"},
    {'8', "tuv"},
    {'9', "wxyz"}
};

// 백트래킹을 위한 함수 정의
void backtrack(string combination, string next_digit, vector<string>& ans, const unordered_map<char, string>& phone) {
    // 다음 숫자가 없으면 결과 벡터에 조합 추가
    if (next_digit.empty()) {
        ans.push_back(combination);
        return;
    }
    // 현재 숫자에 해당하는 모든 문자에 대하여 재귀적으로 백트래킹 수행
    for (char letter : phone.at(next_digit[0])) {
        backtrack(combination + letter, next_digit.substr(1), ans, phone); //recursive
    }
}

// 주요 함수: 주어진 숫자열로 가능한 모든 문자열 조합 반환
vector<string> letterCombinations(string digits) {
    vector<string> ans;

    // 입력 문자열이 비어있으면 빈 벡터 반환
    if (digits.empty()) return ans;

    // 입력 문자열의 길이가 1인 경우
    if (digits.size() == 1) {
        for (char ch : phone[digits[0]]) {
            // string ans이기때문에 ch을 1번만 복사해서 string에 붙이는 느낌
            ans.push_back(string(1, ch));
        }
        return ans;
    }

    // 백트래킹 함수 호출
    backtrack("", digits, ans, phone);

    // 최종 결과 반환
    return ans;
}

int main() {
    string input;
    cout << "Enter a sequence of digits (2-9): ";
    cin >> input;

    // // 따옴표 제거
    // input = input.substr(1, input.length() - 2);
    
    // 2 미만인 숫자일 경우
    bool hasInvalidDigit = false;
    for (char ch : input) {
        if (ch < '2' || ch > '9') {
            hasInvalidDigit = true;
            break;
        }
    }

    if (hasInvalidDigit) {
        cout << "[]" << endl;
        return 1;
    }

    vector<string> combinations = letterCombinations(input);
    
    cout << "[";
    for (size_t i = 0; i < combinations.size(); ++i) {
        cout << "\"" << combinations[i] << "\"";
        if (i != combinations.size() - 1) {
            cout << ",";
        }
    }
    cout << "]" << endl;

    return 0;
}

// /*-------- shell 에서 직접 입력받을 때 ./test 23 이렇게 넣을 경우 --------------*/
// int main(int argc, char* argv[]) {
//     if (argc != 2) {
//         cerr << "Usage: " << argv[0] << " <digits>" << endl;
//         return 1;
//     }

//     string digits = argv[1];
//     bool hasInvalidDigit = false;
//     for (char ch : digits) {
//         if (ch < '2' || ch > '9') {
//             hasInvalidDigit = true;
//             break;
//         }
//     }

//     if (hasInvalidDigit) {
//         cout << "[]" << endl;
//         return 1;
//     }

//     vector<string> combinations = letterCombinations(digits);

//     cout << "[";
//     for (size_t i = 0; i < combinations.size(); ++i) {
//         cout << "\"" << combinations[i] << "\"";
//         if (i != combinations.size() - 1) {
//             cout << ",";
//         }
//     }
//     cout << "]" << endl;

//     return 0;
// }


/*---------------- 내부 함수 넣는 법 (재귀 함수 실행할 떄)---------------------------*/
// vector<string> letterCombinations(string digits) {
//     // 숫자와 문자의 매핑을 위한 해시맵 선언
//     unordered_map<char, string> phone = {
//         {'2', "abc"},
//         {'3', "def"},
//         {'4', "ghi"},
//         {'5', "jkl"},
//         {'6', "mno"},
//         {'7', "pqrs"},
//         {'8', "tuv"},
//         {'9', "wxyz"}
//     };

//     vector<string> ans; // 결과를 저장할 벡터

//     // 입력 문자열이 비어있는 경우 빈 벡터 반환
//     if (digits.empty()) return ans;

//     // 입력 문자열의 길이가 1인 경우 해당 숫자에 매핑되는 문자들을 반환
//     if (digits.size() == 1) {
//         for (char ch : phone[digits[0]]) {
//             // ch을 1번 복사해서 문자열 만들기위해 (ans는 string이어서 이렇게 처리해야함)
//             ans.push_back(string(1, ch));
//         }
//         return ans;
//     }

//     // 백트래킹을 위한 람다 함수 선언
//     function<void(string, string)> backtrack = [&](string combination, string next_digit) {
//         // 다음 숫자가 없는 경우 현재 조합을 결과 벡터에 추가
//         if (next_digit.empty()) {
//             ans.push_back(combination);
//             return;
//         }
//         // 다음 숫자에 해당하는 문자들로 조합을 이어나감
//         // .at은 참조하는 느낌
//         for (char letter : phone[next_digit[0]]) {
//             backtrack(combination + letter, next_digit.substr(1));
//         }
//     };

//     // 백트래킹 시작
//     backtrack("", digits);
    
//     return ans; // 결과 반환
// }
