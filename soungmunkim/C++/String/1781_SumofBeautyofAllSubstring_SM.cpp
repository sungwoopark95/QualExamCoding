/*
Sum of Beauty of all substring (counter 디버깅 함수 있음! 참고 가능)

[최대 char 빈도수 - 최소 char 빈도수 = beauty of string]
The beauty of a string is the difference in frequencies between the most frequent and least
frequent characters.
For example, the beauty of "abaacc" is 3 - 1 = 2 .
Given a string s , return the sum of beauty of all of its substrings.

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Please enter a string: aabcb 
5
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Please enter a string: aabcbaa
17
*/


#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

// 문자 빈도를 계산하는 함수 정의
unordered_map<char, int> charCounter(const string& sub) {
    unordered_map<char, int> counter;  // 문자를 키로, 빈도수를 값으로 하는 unordered_map 생성
    for(char ch : sub) {                    // 주어진 문자열에 대해 각 문자를 순회
        counter[ch]++;                      // 해당 문자의 빈도를 증가
    }
    return counter;                         // 생성된 빈도수 맵 반환
}

int beautySum(const string& s) {
    int sumbeauty = 0;                      // 합계 초기화

    // 모든 가능한 substring에 대하여
    for(int i = 0; i < s.length(); i++) {   // 시작 지점을 순회
        for(int j = i; j < s.length(); j++) { // 종료 지점을 순회
            string sub = s.substr(i, j - i + 1); // substring 추출
            unordered_map<char, int> sub_counter = charCounter(sub); // 해당 substring의 문자 빈도 계산

            int min_cnt = 1000000;           // 최소 빈도 초기화
            int max_cnt = 0;                 // 최대 빈도 초기화

            // 최소 및 최대 빈도 찾기
            for(const auto& kv : sub_counter) {  // 맵의 각 원소에 대해
                if(kv.second < min_cnt) {        // 최소값 갱신 확인
                    min_cnt = kv.second;
                }
                if(kv.second > max_cnt) {        // 최대값 갱신 확인
                    max_cnt = kv.second;
                }
            }

            int beauty_cnt = max_cnt - min_cnt; // 미인 점수 계산
            sumbeauty += beauty_cnt;            // 총 합에 추가
        }
    }

    return sumbeauty;                           // 최종 결과 반환
}

int main() {
    string s;
    cout << "Enter a string: ";            // 사용자에게 문자열 입력 요청
    cin >> s;                              // 문자열 입력 받기

    cout << beautySum(s) << endl;     // 계산 결과 출력

    return 0;
}
