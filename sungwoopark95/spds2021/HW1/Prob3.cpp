/*
# P3. 문자열 찾기 

문장 내에서 단어의 등장 위치를 찾는 함수 `find_word`를 작성하라. 문장에서 단어는 공백, 쉼표(,), 및 마침표(.)로 구분된다. 
또한, 단어가 일치함을 확인할 때 대소문자는 구분하지 않는다. 
주어진 단어가 문장 내에서 몇 번째 단어로 등장하는지 그 위치들을 구해 정수의 리스트로 반환한다 (위치는 0부터 시작한다). 
*/

#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

// uppercase -> lowercase로 바꾸는 함수
char lower_letter(char letter) {
    if (letter >= 'A' && letter <= 'Z') {
        return 'a' + (letter - 'A');
    }
    // 이미 lowercase인 경우 그대로 pass
    return letter;
}

char upper_letter(char letter) {
    if (letter >= 'a' && letter <= 'z') {
        return 'A' + (letter - 'a');
    }
    return letter;
}

string lower(string s) {
    string converted = "";
    for (int i=0;i<s.length();i++) {
        converted += lower_letter(s[i]);
    }
    return converted;
}

string upper(string s) {
    string converted = "";
    for (int i=0;i<s.length();i++) {
        converted += upper_letter(s[i]);
    }
    return converted;
}

bool string_eq(string s1, string s2) {
    if (s1.length() != s2.length()) {
        return false;
    }
    for (int i=0;i<s1.length();i++) {
        if (s1[i] != s2[i]) {
            return false;
        }
    }
    return true;
}

vector<int> find_word(string s, string target) {
    vector<string> split;
    int i = 0, j = 1;
    while (i < s.length() && j < s.length()) {
        string word = "";
        word += s[i];
        while (s[j] != ' ' && s[j] != ',' && s[j] != '.') {
            word += s[j++];
        }
        split.push_back(word);
        if (s[j] == ' ') { i = j+1; }
        else { i = j+2; }
        j = i+1;
    }

    vector<int> ans;
    for (int i=0;i<split.size();i++) {
        if (string_eq(lower(target), lower(split[i]))) {
            ans.push_back(i);
        }
    }
    return ans;
}

int main(int argc, char* argv[]) {
    string s = argv[1];
    string target = argv[2];
    vector<int> word_index = find_word(s, target);

    cout << "[";
    for (int i=0;i<word_index.size();i++) {
        if (i < word_index.size() - 1) {
            cout << word_index[i] << ", ";
        }
        else {
            cout << word_index[i];
        }
    }
    cout << "]" << endl;

    return 0;
}
