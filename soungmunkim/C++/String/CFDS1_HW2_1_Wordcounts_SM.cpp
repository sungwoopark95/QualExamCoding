/*
[Word counts in a sentence]
주어진 std::string object에 담겨 있는 단어의 개수와 각 단어 별 출현 빈도를 표시해주는 프로그램을 작성하라.
*/

/*------------------- Wordcount.h ------------------*/
#include <iostream>
#include <string>
#include <map>      // dictionary를 위해
#include <sstream> // 문자열 stream

using namespace std;
void wordcount(string sentencees);

/*------------------- Wordcount_main.cpp ------------------*/
int main() {
  string sentences =
    "Doubt thou the stars are fire "
    "Doubt that the sun doth move "
    "Doubt truth to be a liar "
    "But never doubt I love";
  cout << "Given string: \"" << sentences << "\"\n" << endl;

  wordcount(sentences);

  return 0;
}

/*------------------- Wourdcount.cpp ------------------*/

void wordcount(string sentences) {

    // 단어 별로 잘 나오는지 check
    // while(iss >> word) {
    //     cout << "word is " << word << endl;
    // }

    // 문장에서 단어들을 나눠서 word에 담을 예정
    istringstream iss(sentences);
    string word;

    map<string, int> wordCount_dct; // 단어와 그 단어 출현 빈도 dict에 저장

    // 각 단어의 출현 횟수 Update
    while (iss >> word){
        wordCount_dct[word]++;
    }
/*
// wordCount dictionary의 size가 곧 총 Unique 단어 횟수임 
    cout << "Total number of words: " << wordCount_dct.size() << endl;
*/  

    // 문장에 총 단어 횟수 체크하기 위해 각 단어 횟수들 다 더하기
    unsigned int total_words = 0;
    for (map<string, int>::iterator it = wordCount_dct.begin(); it != wordCount_dct.end(); it++){
        total_words += it->second;
    }
    cout << "Total number of words: " << total_words << endl;


    // map의 iterator 사용해서 각 요소 반복하기
    for (map<string, int>::iterator it = wordCount_dct.begin(); it != wordCount_dct.end(); it++) {
        cout << "Word \"" << it->first << "\" appears ";
        if (it->second > 2)
            cout << it->second << " times.";
        else if (it->second == 2)
            cout << "twice.";
        else   
            cout << "once.";
        cout << endl;
    }
}
