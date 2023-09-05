/*
[string으로 permutation 구하기]
# TestCase
>>> s = "abc"
>>> str_perm(s)
>>> ["abc", "acb", "bac", "bca", "cab", "cba"]

>>> s = "abb"
>>> str_perm(s)
>>> ["abb", "aba", "bba"]
*/

#include<iostream>
#include<string>
#include <vector>

using namespace std;

void swap(char& a, char& b){
    char temp = a;
    a = b;
    b = temp;
}

vector<string> backtrack(int start, string& s, vector<string>& permutations){
    // 시작 인덱스가 문자열의 길이와 같아지면, 현재 문자열의 순열을 저장
    if (start == s.size()){
        permutations.push_back(s);
    }

    for(int i = start; i < s.size(); i++){
        // 현재 시작 인덱스와 루프의 인덱스 위치의 문자를 교환 (스왑)
        swap(s[start], s[i]);
        // 현재 시작 인덱스를 제외한 나머지 문자열에 대해 순열을 생성하기 위해 재귀적으로 호출
        backtrack(start+1, s, permutations);
        // 이전 상태로 문자열을 복원하기 위해 다시 문자 위치를 교환 (백트래킹)
        swap(s[start], s[i]);
    }
    return permutations;
}

// 원본 문자열 변경하지 않기
void str_perm(const string& input){
    vector<string> permutations;
    string s = input; // 복사본 사용하기
    vector<string> output = backtrack(0, s, permutations);

    // 최종 결과 프린트하기
    for (int i = 0; i < output.size(); i++){
        cout << "\"" << output[i] << "\"";
        if(i != output.size() - 1){
            cout << ", ";
        }
    }
    cout << endl;
}

int main() {
    str_perm("abc");
    return 0;
}