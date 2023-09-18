/*
[palindrome partitions 중에 가장 적은 cut 수 구하기]

Given a string s, 
partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test                                                
Please enter a string: 
"aab"
["a", "a", "b"], ["aa", "b"]
min cut: 1

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Please enter a string: 
aab
["a", "a", "b"], ["aa", "b"]
min cut: 1

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Please enter a string: 
"a"
["a"]
min cut: 0
 
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Please enter a string: 
"ab"
["a", "b"]
min cut: 1
*/

#include <iostream>
#include <vector>
#include <string>
#include <stdbool.h>
#include <limits.h>

using namespace std;

// 복잡한 문자열도 palindrome인지 확인하는 방법 
bool palindrome(string s) {
    string cleanedString = "";
    for(char c : s) {
        if(isalnum(c)) {  // c가 알파벳 또는 숫자인지 확인
            cleanedString += tolower(c);  // 모든 문자를 소문자로 변환하여 cleanedString에 추가
        }
    }

    string reversedString = cleanedString;
    reverse(reversedString.begin(), reversedString.end());  // cleanedString을 뒤집어 reversedString에 저장

    return cleanedString == reversedString;
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

    // 2D array인 result를 [], [] 형태로 프린트하기
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

     /*
     모든 partitions 돌면서 길이가 가장 작은 것 구하기
    */

    int min_len = INT_MAX;
    int partition_size;
    int min_cut;
    for (size_t i = 0; i < result.size(); i++){
        partition_size = result[i].size();
        // cout <<"partition size: " << partition_size << endl;
        if(partition_size < min_len){
            min_len = partition_size;
            // cout << "min legth: " << min_len << endl;
        }
    }
    min_cut = min_len-1;
    cout << "min cut: " << min_cut << endl;
}

// 쌍따옴표를 제거하는 함수 (문자열 사이에 있을 경우)
string removeQuotes(const string& input) {
    string result = "";
    for(char c : input) {
        if (c != '"') {  // 쌍따옴표가 아니면 결과 문자열에 추가
            result += c;
        }
    }
    return result;
}


int main(){
    string s;
    int result; 
    int min_cut;

    cout << "Please enter a string: " << endl;
    getline(cin, s);

    s = removeQuotes(s); 

    palindrome_partition(s);

    return 0;
}