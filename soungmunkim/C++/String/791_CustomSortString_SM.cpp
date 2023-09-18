/*
[order 순서대로 s의 순서를 바꾸기] replace 방법 사용한 것
!! word한개를 각 각 받을 땨ㅐ !!

Example 1:
Input: order = "cba", s = "abcd"
Output: "cbad"
Explanation: 
"a", "b", "c" appear in order, so the order of "a", "b", "c" should be "c", "b", and "a". 
Since "d" does not appear in order, it can be at any position in the returned string. "dcba", "cdba", "cbda" are also valid outputs.

((base) soungmunkim@gimseongmun-ui-MacBookPro String % g++ -std=c++17 791_CustomSortString_SM.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test    
Enter a order string: "cbafg"
Enter a string: "abcd"
cbad

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Enter a order string: cba
Enter a string: abcd
cbad
*/

#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

string customSortString(const string& order, const string& s) {
    // s의 문자들의 빈도수를 저장하기 위한 해시맵
    unordered_map<char, int> cnt;
    // s를 순회하며 각 문자의 빈도수를 센다.
    for (char c : s) {
        cnt[c]++;
    }

    // 정렬된 결과를 저장할 문자열
    string ans = "";
    // 임시로 s의 내용을 복사해두는 변수
    string temp_s = s;

    // order를 순회하며 해당 문자가 s에 있으면 그 빈도수만큼 ans에 추가한다.
    for (char c : order) {
        if (cnt.find(c) != cnt.end()) {
            // 해당 문자를 그 빈도수만큼 ans에 추가한다.
            ans += string(cnt[c], c);
            
            // temp_s에서 해당 문자를 모두 제거한다.
            /*
            pos는 temp_s 문자열에서 문자 c를 찾은 위치를 저장하기 위한 변수.

            while((pos = temp_s.find(c)) != std::string::npos) { ... }
            temp_s.find(c) 함수는 문자열 temp_s에서 문자 c를 처음 발견한 위치를 반환
            
            만약 문자 c가 temp_s에 없다면, std::string::npos를 반환
            std::string::npos는 문자열의 위치를 나타내는 상수 중에서 가장 큰 값으로, 
                문자열에서 문자나 부분 문자열을 찾지 못했을 때 find 함수가 반환하는 값을 의미
            
            temp_s.replace(pos, 1, "");
            temp_s 문자열의 pos 위치에서부터 1개의 문자를 빈 문자열("")로 대체

            즉, 이 코드는 문자열 temp_s에서 주어진 문자 c를 모두 찾아서 제거하는 역할을 합니다.
            */
            size_t pos = 0;
            while((pos = temp_s.find(c)) != string::npos) {
                temp_s.replace(pos, 1, "");
            }
        }
    }
    // 아직 ans에 추가되지 않은 문자들을 추가한다.
    ans += temp_s;

    // 정렬된 결과 문자열을 반환한다.
    return ans;
}

// 쌍따옴표를 제거하는 함수
string removeQuotes(const string& input) {
    string result = "";
    for(char c : input) {
        if (c != '"') {  // 쌍따옴표가 아니면 결과 문자열에 추가
            result += c;
        }
    }
    return result;
}

int main() {
    string order, s;

    cout << "Enter a order string: ";
    getline(cin, order);
    order = removeQuotes(order);  // 쌍따옴표 제거

    cout << "Enter a string: ";
    getline(cin, s);
    s = removeQuotes(s);  // 쌍따옴표 제거

    // customSortString 함수의 결과를 출력한다.
    cout << customSortString(order, s) << endl;
    return 0;
}
