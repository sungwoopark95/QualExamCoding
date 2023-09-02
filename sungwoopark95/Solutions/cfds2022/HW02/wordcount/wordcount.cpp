#include "wordcount.h"
#include <iostream>
#include <sstream>

#define MAX_WORDS 30
using namespace std;

bool in(string* arr, string word, int size) {
    for (int i=0;i<size;i++) {
        if (arr[i] == word) {
            return true;
        }
    }
    return false;
}

void wordcount(std::string sentences) {
    // store number of total words
    unsigned int total_words = 0;

    // TODO: calculate word counts
    stringstream ss1(sentences);
    string word1;
    while (ss1 >> word1) {
        total_words++;
    }

    std::cout << "Total number of words: " << total_words << std::endl;

    // TODO: print number of appearances for each word
    string used[total_words];
    int idx = 0;
    stringstream ss2(sentences);
    string word2;
    while (ss2 >> word2) {
        if (in(used, word2, total_words)) {
            continue;
        }
        string flag;
        int cnt = 0;
        stringstream tempss(sentences);
        string tempword;
        while (tempss >> tempword) {
            if (tempword == word2) {
                cnt++;
            }
        }
        if (cnt == 1) { flag = "once"; }
        else if (cnt == 2) { flag = "twice"; }
        else { flag = to_string(cnt) + " times"; }
        cout << "Word \"" << word2 << "\" appears " << flag << "." << endl; 

        used[idx++] = word2;
    }
}
