#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

string reverseWords(const string& s) {
    istringstream ss(s);
    string word;
    vector<string> list_s;

    while (ss >> word) {
        list_s.push_back(word);
    }

    reverse(list_s.begin(), list_s.end());

    ostringstream oss;
    for (size_t i = 0; i < list_s.size(); i++) {
        if (i != 0) {
            oss << " ";
        }
        oss << list_s[i];
    }

    return oss.str();
}

int main() {
    string s = "  hello world  ";
    cout << reverseWords(s) << endl;
    return 0;
}
