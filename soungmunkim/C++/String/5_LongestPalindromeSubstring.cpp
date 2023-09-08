/*
[부분 문자열중에 가장 긴 palindrome 찾기]
Given a string s, return the longest 
palindromic substring in s.
 
Example 1:

Input: s = "babad"
Output: "bab"
Explanation: "aba" is also a valid answer.

Example 2:
Input: s = "cbbd"
Output: "bb"
*/


#include <iostream>
#include <string>

// 주어진 시작과 끝 인덱스 사이의 문자열이 팰린드롬인지 확인하는 함수
bool isPalindrome(const std::string& s, int start, int end) {
    // 시작 인덱스가 끝 인덱스보다 작은 동안
    while (start < end) {
        // 시작과 끝 문자가 다르면 바로 false 반환
        if (s[start] != s[end]) return false;
        start++;  // 시작 인덱스 증가
        end--;    // 끝 인덱스 감소
    }
    // 루프를 다 돌았다면 팰린드롬임
    return true;
}

// 문자열 s에서 가장 긴 팰린드롬 부분 문자열을 찾아 반환하는 함수
std::string longestPalindrome(const std::string& s) {
    int len = s.size();  // 입력 문자열의 길이
    if (len < 2) return s;  // 문자열 길이가 1 이하면 그대로 반환

    int start = 0;  // 팰린드롬 시작 인덱스
    int maxLen = 1;  // 가장 긴 팰린드롬의 길이

    // 문자열 전체를 순회
    for (int i = 0; i < len; ++i) {
        // 현재 인덱스에서 가장 긴 팰린드롬을 찾기 위한 조건문
        if (i - maxLen >= 1 && isPalindrome(s, i - maxLen - 1, i)) {
            start = i - maxLen - 1;
            maxLen += 2;
            continue;  // 다음 반복으로 넘어감
        }
        // 두 번째로 긴 팰린드롬을 찾기 위한 조건문
        if (isPalindrome(s, i - maxLen, i)) {
            start = i - maxLen;
            maxLen += 1;
        }
    }
    // 찾은 팰린드롬의 시작 인덱스와 길이를 사용하여 부분 문자열 반환
    return s.substr(start, maxLen);
}

// 메인 함수
int main() {
    std::string s;
    std::cin >> s;  // 사용자로부터 문자열 입력 받음
    std::cout << longestPalindrome(s) << std::endl;  // 결과 출력
    return 0;  // 프로그램 종료
}
