
/*
[s를 k개의 palindrome으로 나눌 수 있다면 True 반환]
!! substring인 경우에만 해당됨 !!

1. palindrome이 될 수 있는지 체크하는 함수
2. palindrome이 될 수 있는 단어를 palindrome으로 만드는 함수 
3. 한 단어의 조합들이 Palindrome이 될 수 있는 단어들을 모은 partition 함수 
    -> backtracking 사용

(base) soungmunkim@gimseongmun-ui-MacBookPro String % c++ -std=c++17 1400_Construct_K_Palindrome.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test                                                
Enter a word: "annabelle"
Enter k: 2
True

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test                                                
Enter a word: "leetcode"
Enter k: 3
False

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Enter a word: "true"
Enter k: 4
True
*/


#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// palindrome이 될 수 있는지 체크하는 함수
bool canPalindrome(const string& word) {
    // word의 각 char 빈도 저장
    unordered_map<char, int> cnt;
    for(char c : word) {
        cnt[c]++;
    }

    int even = 0, odd = 0;
    // 빈도수 짝, 홀수 체크하기
    for(const auto& [ch, val] : cnt) {
        if (val % 2 == 0) {
            even++;
        } else {
            odd++;
        }
    }

    // 만약 모두 다 짝수거나 하나만 홀수이면 palindrome 만들 수 있음
    if (even == cnt.size()) return true;
    if (even == cnt.size() - 1 && odd == 1) return true;
    return false;
}

// palindrome 만드는 함수 (palindrome 만들 수 있을 때)
string constructPalindrome(const string& w) {
    // 만약 palindrome을 만들 수 없을 때
    if(!canPalindrome(w)) {
        return "Not a palindrome";
    }

    // char 빈도 저장할 dict
    unordered_map<char, int> cnt;
    for(char c : w) {
        cnt[c]++;
    }

    // 해당 단어만큼 '0'으로 채운 ans string 만들기
    string ans(w.length(), '0');

    // 만약 홀수 길이라면 홀수 빈도인 char을 중앙에 놓기
    if (w.length() % 2 != 0) {
        int mid_idx = w.length() / 2;

        // char과 해당 빈도 돌기 
        for(const auto& [ch, val] : cnt) {
            if(val % 2 != 0) {
                ans[mid_idx] = ch;
                cnt[ch]--;
                break;
            }
        }
    }

    int idx = 0;
    for(const auto& [ch, val] : cnt) {
        int freq = val;
         // 빈도수 가 0보다 클때까지
        while(freq > 0) {
            
            // 양 옆에 하나 채우고 빈도 2개 줄이기
            ans[idx] = ch;
            ans[w.length() - idx - 1] = ch;
            freq -= 2;

            // 앞 쪽으로 한칸 이동
            idx++;
        }
    }

    return ans;
}

void backtrack(int start, string& s, vector<string>& path, vector<vector<string>>& result){
    if (start == s.size()){
        result.push_back(path);
    }
    // 현재 위치에서 시작하는 모든 부분 문자열에 대해
    for(int end = start; end < s.size(); end++){
        // 현재 부분 문자열이 회문이라면
        if(canPalindrome(s.substr(start, end-start+1))){

            // 이 부분 문자열을 path에 추가하고
            path.push_back(s.substr(start, end-start+1));
            
            // 다음 부분 문자열을 위해 재귀 호출
            backtrack(end+1, s, path, result);
            
            // 백트래킹
            path.pop_back();
        }
    }
}

// s 문자열을 k개의 palindrome 문자열로 분할할 수 있는지 체크하는 함수
bool canConstruct(string& s, int k) {
    vector<string> path;
    vector<vector<string>> result;
    backtrack(0, s, path, result);

    // palindrome으로 만들어서 list에 담는 과정을 안 함 (파이썬 코드 참고)
    for(int i = 0; i<result.size(); i++){
        vector<string> partitions;
    
        if (result[i].size() == k){
            return true;
        }
    }
    return false;
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
    // 테스트용 코드
    string word;
    int k;
    
    cout << "Enter a word: ";
    cin >> word;

    word = removeQuotes(word);
    
    // cout << canPalindrome(word) << endl;
    // cout << constructPalindrome(word) << endl;

    cout << "Enter k: ";
    cin >> k;
    
    if (canConstruct(word, k))
        cout << "True" << endl;
    else    
        cout << "False" << endl;

    return 0;
}
