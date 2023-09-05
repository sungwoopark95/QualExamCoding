/*
(b) Implement a function bar(s) that returns a string t 
    in which no two adjacent characters are adjacent in s, 
    and s and t are different strings.
    When a character appears in s, t should contain it only once.
    When there is no such string t, it returns an empty string "".
    If there are multiple strings that satisfy the conditions,
    return any of them.
    
    print(bar("abccde"))    #[2,5,1,4,0,3] bdeac
    print(bar("abcde"))     #[2,0,4,1,3] bdeac
    print(bar("abc"))       # ""
    print(bar("abcdcef"))   #[0,2,4,6,1,3,5] bdafce
*/


/*
backtrack 함수 내에서 remaining_chars라는 리스트는 아직 순열에 포함되지 않은 문자들을 저장합니다. 
이를 통해 각 문자가 순열에 한 번만 사용되도록 합니다.

중복된 char은 하나만 포함하게 해야함

*/

#include <iostream>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

string origin_s;
string s;

bool isValid(int start) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == origin_s[i]) return false; // 현재 문자와 원본 문자열의 같은 위치의 문자가 동일한 경우
        if (i > 0 && s[i] == origin_s[i-1]) return false; // 현재 문자와 이전 문자가 동일한 경우
        if (i < s.size() - 1 && s[i] == origin_s[i+1]) return false; // 현재 문자와 다음 문자가 동일한 경우
    }
    return true;
}

string backtrack(int start) {
    if (start == s.size()) {
        if (isValid(start)) return s; // 모든 위치의 문자가 처리되었을 때 유효한 조합인지 확인하고 반환
        return "";
    }

    for (int i = start; i < s.size(); i++) {
        swap(s[start], s[i]); // 현재 위치의 문자와 i 위치의 문자를 교환
        
        string result = backtrack(start + 1); // 다음 위치의 문자를 처리하기 위해 재귀 호출
        if (!result.empty()) return result; // 유효한 조합이 발견되었으면 결과 반환

        swap(s[start], s[i]); // 이전 상태로 문자 위치를 복원 (백트래킹)
    }

    return "";
}

string foo(const string& input_s) {
    s = input_s;
    origin_s = s;

    string t = backtrack(0); // 순열 생성 시작

    if (!t.empty()) {
        return t; // 유효한 조합이 발견되었을 때 반환
    } else {
        return ""; // 유효한 조합이 없을 때 빈 문자열 반환
    }
}

int main() {
    string input;
    cout << "문자열을 입력하세요: ";
    cin >> input; // 사용자로부터 문자열 입력 받기
    
    string result = foo(input); // 입력 받은 문자열을 처리하여 결과 얻기

    if (!result.empty()) {
        cout << "새로운 문자열 조합: " << result << endl;
    } else {
        cout << "유효한 조합이 없습니다." << endl;
    }
    
    return 0;
}
