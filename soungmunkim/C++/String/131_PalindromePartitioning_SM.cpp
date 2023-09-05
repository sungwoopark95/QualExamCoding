/*
[Palindrome Partitioning]
string이 palindrome substring으로 다 나눠질 수 있다면 그 palindrome들 각 list에 저장하기

Given a string s, partition s such that every substring of the partition is a palindrome. 
Return all possible palindrome partitioning of s.

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Please enter a string: 
aab
["a", "a", "b"], ["aa", "b"]

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Please enter a string: 
kabccba
["k", "a", "b", "c", "c", "b", "a"], ["k", "a", "b", "cc", "b", "a"], ["k", "a", "bccb", "a"], ["k", "abccba"]
*/

#include <iostream>
#include <vector>
#include <string>
#include <stdbool.h>

using namespace std;

bool palindrome(string s){
    string reversed_s = "";
    int n = s.size();

    for(int i = n-1; i>=0; i--){
        reversed_s += s[i];
    }

    if (s == reversed_s){
        return true;
    }
    return false;
}

void backtrack(int start, string& s, vector<string>& path, vector<vector<string>>& result){
    if (start == s.size()){
        result.push_back(path);
    }
    // 현재 위치에서 시작하는 모든 부분 문자열에 대해
    for(int end = start; end < s.size(); end++){
        // 현재 부분 문자열이 회문이라면
        if(palindrome(s.substr(start, end-start+1))){

            // 이 부분 문자열을 path에 추가하고
            path.push_back(s.substr(start, end-start+1));
            
            // 다음 부분 문자열을 위해 재귀 호출
            backtrack(end+1, s, path, result);
            
            // 백트래킹
            path.pop_back();
        }
    }
}

void palindrome_partition(string &s){
    vector<string> path;
    vector<vector<string>> result;
    backtrack(0, s, path, result);

     /*
    for 루프는 result의 모든 행 (row)에 대해 반복되며, 내부의 for 루프는 해당 row의 각 double val을 반복
    */
    for (size_t j = 0; j < result.size(); ++j) {
        cout << "[";
        for (size_t i = 0; i < result[j].size(); ++i) {
            cout << "\"" << result[j][i] << "\"";
            if (i != result[j].size() - 1) {  // 마지막 원소가 아닌 경우에만 쉼표를 추가
                cout << ", ";
            }
        }
        cout << "]";
        if (j != result.size() - 1) { // 마지막 행이 아닌 경우에만 쉼표와 공백을 추가
            cout << ", ";
        }
    }
    cout << endl;
}

int main(){
    string s;

    cout << "Please enter a string: " << endl;
    getline(cin, s);

    palindrome_partition(s);

    return 0;
}