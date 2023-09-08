/*
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: 
(you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:

string convert(string s, int numRows);
 
Example 1:
Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"

Example 2:
Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:
P     I    N
A   L S  I G
Y A   H R
P     I

Example 3:
Input: s = "A", numRows = 1
Output: "A"
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

string convert(string s, int numRows) {
    // numRows가 1인 경우 바로 원본 문자열 반환
    if (numRows == 1) return s;

    // 각 행마다 문자를 저장하기 위한 벡터를 초기화
    vector<string> rows(min(numRows, int(s.size())));
    int curRow = 0;
    bool goingDown = false;

    // 각 문자를 적절한 행에 배치
    for (char c : s) {
        rows[curRow] += c;
        // 행의 시작이나 끝에서 방향을 전환
        if (curRow == 0 || curRow == numRows - 1) goingDown = !goingDown;
        curRow += goingDown ? 1 : -1;
    }

    // 결과 문자열 생성
    string ret;
    for (string row : rows) ret += row;
    return ret;
}

int main() {
    string s = "PAYPALISHIRING";
    int numRows = 3;
    cout << convert(s, numRows) << endl;
    return 0;
}
