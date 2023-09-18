/*
[Isomorphic string]
s가 서로 반대되는 char로 바꼈을때 t로 된다면 iosmorphic string임
ex) egg = add

Example 1:
Input: s = "egg", t = "add"
Output: true

Example 2:
Input: s = "foo", t = "bar"
Output: false

Example 3:
Input: s = "paper", t = "title"
Output: true
*/

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

bool isIsomorphic(string s, string t) {
    unordered_map<char, char> mapping1;  // s의 문자를 t의 문자로 매핑
    unordered_map<char, char> mapping2;  // t의 문자를 s의 문자로 매핑

    // s와 t의 길이가 다르면 isomorphic 할 수 없으므로 false 반환
    if (s.size() != t.size()) return false;

    // s와 t의 각 문자를 순회하며 매핑을 생성
    for (int i = 0; i < s.size(); ++i) {
        mapping1[s[i]] = t[i];
        mapping2[t[i]] = s[i];
    }

    string compare1 = "";  // s를 t로 변환한 결과를 저장할 문자열
    string compare2 = "";  // t를 s로 변환한 결과를 저장할 문자열

    // s와 t의 각 문자를 순회하며 변환된 문자열 생성
    for (int i = 0; i < s.size(); ++i) {
        compare1 += mapping1[s[i]];
        compare2 += mapping2[t[i]];
    }

    // 변환된 문자열이 원본 문자열과 일치하는지 확인
    return compare1 == t && compare2 == s;
}

int main() {
    string s, t;
    cout << "s 문자열을 입력하세요: ";
    cin >> s;
    cout << "t 문자열을 입력하세요: ";
    cin >> t;

    cout << (isIsomorphic(s, t) ? "True" : "False") << endl;
    return 0;
}
