/*
주어진 string을 뒤집되, 새로운 list를 생성하지 않고 in-place로 작동하도록 해야 함

Input: s = ["h","e","l","l","o"]
Output: ["o","l","l","e","h"]

Input: s = ["H","a","n","n","a","h"]
Output: ["h","a","n","n","a","H"]
*/

#include <iostream>
#include <vector>
using namespace std;

// 문자열 s를 거꾸로 뒤집는 함수
void reverseString(vector<char>& s) {
    int size = s.size();  // 문자열의 길이를 저장

    // 문자열의 앞쪽과 뒤쪽을 바꾸는 과정
    for (int i=0; i<(size/2); i++) {
        char temp = s[i];             // 임시 변수에 현재 문자를 저장
        s[i] = s[size-1-i];           // 현재 문자의 위치에 뒤쪽 문자를 저장
        s[size-1-i] = temp;           // 뒤쪽 문자의 위치에 임시 변수에 저장한 문자를 저장
    }
}

int main() {
    string input;
    cout << "String을 입력하세요 : ";
    cin >> input;
    vector<char> vec(input.begin(), input.end());

    for (char c : vec) {
        cout << c;
    }
    cout << endl;

    reverseString(vec);
    for (char c : vec) {
        cout << c;
    }
    cout << endl;
    return 0;
}