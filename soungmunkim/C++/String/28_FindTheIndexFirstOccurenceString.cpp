/*
[첫번째로 needle이 나온 index 반환하기]

(base) soungmunkim@gimseongmun-ui-MacBookPro String % gcc 28_FindTheIndexFirstOccurenceString.c -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test                                           
Enter a haystack: "leetcode"
Enter a needle: "leeto"
Result: -1

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Enter a haystack: "sadbutsad"
Enter a needle: "sad"
Result: 0

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Enter a haystack: sadbut
Enter a needle: sad
Result: 0
*/

#include <iostream>
#include <string>
using namespace std;

// haystack 문자열에서 needle 문자열의 시작 인덱스를 반환하는 함수
int strStr(string haystack, string needle) {
    int window_size = needle.size();  // needle 문자열의 크기를 window_size 변수에 저장

    // haystack 문자열을 순회하면서 needle 문자열과 일치하는 부분이 있는지 확인
    for (int i = 0; i < haystack.size(); ++i) {
        string window = haystack.substr(i, window_size);  // haystack에서 window_size 만큼 잘라낸 부분 문자열을 window 변수에 저장
        if (window == needle) {
            return i;  // 일치하는 부분을 찾으면 해당 인덱스 반환
        }
    }
    return -1;  // 일치하는 부분이 없으면 -1 반환
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
    string haystack, needle;  // haystack과 needle 문자열을 저장할 변수 선언

    cout << "Enter a haystack: ";
    getline(cin, haystack);  // 사용자로부터 haystack 문자열 입력받기
    haystack = removeQuotes(haystack);

    cout << "Enter a needle: ";
    getline(cin, needle);  // 사용자로부터 needle 문자열 입력받기
    needle = removeQuotes(needle);
    
    // strStr 함수를 호출하여 haystack에서 needle의 시작 인덱스를 찾기
    int result = strStr(haystack, needle);  

    cout << "Result: " << result << endl;  // 결과 출력

    return 0;
}
