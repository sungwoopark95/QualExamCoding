/*
[order 순서대로 s의 순서를 바꾸기] replace 방법 없이 푼 것
!! word 한 개를 각 각 받을 때 !!

(base) soungmunkim@gimseongmun-ui-MacBookPro String % gcc 791_CustomSortStringWithoutReplace.c -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Enter a order string: cba
Enter a string: abcd
Result: cbad

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Enter a order string: "cbafg"
Enter a string: "abcd"
Result: cbad
*/

/*-----------------(with out replace) sorted로 order에 나온 만큼 붙이고 마지막 남은 것 붙이는 방법 -----------------*/


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

    // order를 순회하며 해당 문자가 s에 있으면 그 빈도수만큼 ans에 추가한다.
    for (char c : order) {

        if (cnt.find(c) != cnt.end()) {

            // 해당 문자를 그 빈도수만큼 ans에 추가한다.
            ans += string(cnt[c], c);

            // 해당 문자의 빈도수를 0으로 만든다.
            cnt[c] = 0;
        }
    }

    // 아직 ans에 추가되지 않은 문자들을 추가한다.
    for (auto& [key, value] : cnt) {
        ans += string(value, key);
    }

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
