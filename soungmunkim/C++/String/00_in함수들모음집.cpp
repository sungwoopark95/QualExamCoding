
#include <iostream>
#include <string>
#include <set>
#include <map>
using namespace std;

/*-------- 문자열 word에서 문자 ch가 있는지 확인하는 함수: ---------*/

bool in(const string& word, char ch) {
    return word.find(ch) != string::npos;
}


/*--------  문자열 sentence에서 단어 word가 있는지 확인하는 함수: ---------*/

bool in(const string& sentence, const string& word) {
    return sentence.find(word) != string::npos;
}


/*-------- 벡터에 특정 원소가 있는지 확인하는 함수 (정수형을 대상으로 합니다): ---------*/

bool in(const vector<int>& vec, int value) {
    return find(vec.begin(), vec.end(), value) != vec.end();
}


/*-------- 세트에 특정 원소가 있는지 확인하는 함수 (정수형을 대상으로 합니다): ---------*/
bool in(const set<int>& s, int value) {
    return s.find(value) != s.end();
}


/*-------- 맵에서 특정 키가 있는지 확인하는 함수 (정수형 키와 문자열 값을 대상으로 합니다): ---------*/
bool in(const map<int, string>& m, int key) {
    return m.find(key) != m.end();
}



/*-------- 문자열에 특정 부분 문자열이 있는지 확인하는 함수: ---------*/
bool in(const string& str, const string& substring) {
    return str.find(substring) != string::npos;
}
