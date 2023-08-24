/*
[문장에서 총 단어 수와 각 단어 빈도 수 찾기]
g++ -c wordcounts.cpp
g++ -c main.cpp
g++ wordcounts.o main.o -o wordcount_program
------------- OR --------------------------
g++ wordcounts.cpp main.cpp -o wordcount_program

[결과]
Given string: "Doubt thou the stars are fire Doubt that the sun doth move Doubt truth to be a liar But never doubt I love"

Total number of words: 23
Word "Doubt" appears 3 times.
Word "thou" appears once.
Word "the" appears twice.
Word "stars" appears once.
Word "are" appears once.
Word "fire" appears once.
Word "that" appears once.
Word "sun" appears once.
Word "doth" appears once.
Word "move" appears once.
Word "truth" appears once.
Word "to" appears once.
Word "be" appears once.
Word "a" appears once.
Word "liar" appears once.
Word "But" appears once.
Word "never" appears once.
Word "doubt" appears once.
Word "I" appears once.
Word "love" appears once.
*/


#include <iostream>
#include <sstream>
#include "CFDS1_HW2_1_Wordcounts.h"
using namespace std;

// 최대 단어의 개수를 30으로 설정
#define MAX_WORDS 30

void wordcount(string sentences) {
    // 'words'는 입력된 문장 내에서 발견된 단어들을 저장하는 배열
    string words[MAX_WORDS];

    // 'word_count'는 words 배열의 각 단어별로 출현한 횟수를 저장하는 배열
    unsigned int word_count[MAX_WORDS] = {0}; // 0으로 다 초기화

    // 'total_words'는 입력된 문장 내의 전체 단어 수를 저장
    unsigned int total_words = 0;

    // 'total_kinds'는 중복되지 않는, 즉 유일한 단어의 개수를 저장
    unsigned int total_kinds = 0;

    // 문자열 스트림 객체 생성.
    // 입력된 문장을 스트림으로 변환하여 단어별로 분리하기 쉽게 함
    stringstream ss(sentences);

    string word; // ss 저장할 곳

    // 'matched'는 현재 처리 중인 단어가 이전에 나타난 단어인지를 확인하는 플래그
    bool matched;

    unsigned int i;

    // 스트림에서 단어를 하나씩 추출하여 처리
    while (ss >> word) {
        total_words++;

        matched = false;
        for (i = 0; i < total_kinds; i++) {
            // 현재 단어가 이전에 나타난 단어와 일치하는지 확인
            if (words[i] == word) {
                word_count[i]++;
                matched = true;
                break;
            }
        }
        // 만약 현재 단어가 처음 나타나는 단어라면 배열에 추가
        if (matched == false) {
            words[total_kinds] = word;
            word_count[i]++;
            total_kinds++;
        }
    }

    // 결과 출력 부분
    // 전체 단어 수 출력
    cout << "Total number of words: " << total_words << endl;

    // 각 단어와 그 단어의 출현 횟수를 출력
    for (i = 0; i < total_kinds; i++) {
        cout << "Word \"" << words[i] << "\" appears ";
        if (word_count[i] > 2)
            cout << word_count[i] << " times.";
        else if (word_count[i] == 2)
            cout << "twice.";
        else
            cout << "once.";
        cout << endl;
    }
}



