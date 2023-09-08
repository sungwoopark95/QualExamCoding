/*
[인접 문자가 같지 않게 string 다시 배치하기]
Given a string s, rearrange the characters of s so that any two adjacent characters are not the same.

Return any possible rearrangement of s or return "" if not possible.

Example 1:
Input: s = "aab"
Output: "aba"

Example 2:
Input: s = "aaab"
Output: ""
*/

#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

// 인접한 두 문자가 같지 않도록 문자열 s를 재구성하여 반환하는 함수
string reorganizeString(string s) {
    // 문자 빈도수를 저장하기 위한 해시맵
    unordered_map<char, int> counter;
    // 문자열 s의 각 문자에 대해 빈도수를 계산
    for(char c : s) {
        counter[c]++;
    }
    
    // 빈도수를 기반으로 하는 최대 힙
    priority_queue<pair<int, char>> max_heap;
    // counter의 모든 요소를 max_heap에 추가
    for(auto [ch, freq] : counter) {
        max_heap.emplace(freq, ch);
    }

    // 문자열 s의 길이의 절반보다 큰 빈도수를 가진 문자가 있는 경우, 재구성 불가
    if (max_heap.top().first > (s.length() + 1) / 2) {
        return "";
    }
    
    string result;
    // 최대 힙의 크기가 1보다 크면 계속 실행
    while (max_heap.size() > 1) {
        // 가장 빈도수가 높은 두 문자를 추출
        auto [freq1, char1] = max_heap.top(); max_heap.pop();
        auto [freq2, char2] = max_heap.top(); max_heap.pop();
        
        // 결과 문자열에 두 문자를 추가
        result.push_back(char1);
        result.push_back(char2);
        
        // 두 문자의 빈도수 감소 후, 0보다 크면 다시 힙에 추가
        if (--freq1) max_heap.emplace(freq1, char1);
        if (--freq2) max_heap.emplace(freq2, char2);
    }
    
    // 힙에 남아 있는 마지막 문자를 결과 문자열에 추가
    if(!max_heap.empty()) {
        result.push_back(max_heap.top().second);
    }

    return result;
}

int main() {
    string s;
    cin >> s;  // 사용자로부터 문자열 입력 받기
    cout << reorganizeString(s) << endl;  // 재구성된 문자열 출력
    return 0;
}
