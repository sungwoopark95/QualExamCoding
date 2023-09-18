#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 주어진 문자열을 사용하여 알파벳 별 빈도수를 벡터로 반환하는 함수
vector<int> hashtable(const string& str) {
    // 'a'부터 'z'까지의 각 알파벳에 대한 빈도수를 0으로 초기화한 벡터 생성
    vector<int> ans(26, 0);  // 26 letters in the alphabet
    
    // 문자열의 각 문자에 대해 해당 문자의 빈도수를 증가
    for(char c : str) {
        int idx = c - 'a';  // 알파벳 'a'를 기준으로 한 문자의 인덱스 계산
        ans[idx]++;
    }
    
    return ans;
}

// 두 문자열이 아나그램인지 확인하는 함수
bool isAnagram(const string& s, const string& t) {
    // 주어진 문자열을 사용하여 알파벳 별 빈도수를 벡터로 반환하는 함수
    // 두 문자열 s와 t에 대한 빈도수 벡터 생성
    vector<int> s_hash = hashtable(s);
    vector<int> t_hash = hashtable(t);

    // 두 문자열의 빈도수 벡터가 동일한지 비교하여 결과 반환
    return s_hash == t_hash;
}

int main() {
    string s = "anagram";
    string t = "nagaram";
    
    // 두 문자열이 아나그램인지 확인하고 결과 출력
    cout << (isAnagram(s, t) ? "True" : "False") << endl;

    return 0;
}
