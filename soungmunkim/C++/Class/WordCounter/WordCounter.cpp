/*
[Word Counter Class 만들기]
문장 내에서 word 수와 character 수 얻는 함수 구현

1. count word (GetWordCount)
2. character (GetCharacterCount)
3. the number of unique words (GetUniqueWordCount)
4. count a particular word (GetWordCount_OneWord)

1) 대문자 소문자 다른 문자로 취급
2) , . 을 character로 취급 안 함
3) member functions:
    InputText(std::string)
    int GetWordCount()
    int GetCharacterCount()
    int GetUniqueWordCount()
    int GetWordCount_OneWord(const char *)
        -> 해당 단어가 몇번 횟수로 나왔는지 

[output]
Word Count: 36
Character Count: 152
Number of Unique Words: 33
The word and appears 2 times
*/

#include "WordCounter.h"

// 필요한 헤더 파일 포함
#include <map>
#include <string>
#include <iostream>

// 주어진 텍스트를 분석하여 단어의 출현 횟수를 저장하는 함수
void WordCounter::InputText(std::string input_text){
    // 멤버 변수 text에 입력값 저장
    this->text = input_text;

    // 단어를 저장하고 처리하기 위한 변수들 초기화
    int i = 0;
    int text_len = text.size();
    std::string word = " ";

    // 전체 텍스트를 반복하여 단어를 추출하고 단어의 출현 횟수를 계산
    while(i <= text_len){
        // 공백이나 텍스트의 끝을 만날 때마다 단어를 저장
        if ((text[i] == ' ' && text[i-1] != ' ') || (i+1 == text_len +1)){

            // 해당 단어가 이미 저장된 경우
            if (word_dict.count(word) > 0) 
                word_dict[word] += 1;

            // 해당 단어가 처음 발견된 경우
            else 
                word_dict.insert(make_pair(word, 1));

            word = "";
            i++;
        }
        else if (text[i] != ' '){

            // 마침표나 쉼표는 건너뜀
            if (text[i] == '.' || text[i] == ',')
                i++;
    
            else {
                // 그 외의 문자는 단어에 추가
                word += text[i];
                i++;
            }
        }
    }
}

// 전체 단어의 수를 반환하는 함수
int WordCounter::GetWordCount(){
    
    int words = 0;
    // word_dict의 모든 요소를 반복하여 단어의 출현 횟수를 합산
    for (auto iter = word_dict.begin(); iter != word_dict.end(); iter++){
        words += iter->second;
    }
    return words;
}

// 문자의 수를 반환하는 함수
int WordCounter::GetCharacterCount(){
    int ch = 0;
    int i = 0;
    while(text[i] != '\0'){
        // 공백, 마침표, 쉼표는 건너뜀
        if (text[i] == ' ' || text[i] == '.' || text[i] == ',')
            i++;
        else{
            // 그 외의 문자는 카운트
            ch++;
            i++;
        }
    }
    return ch;
}

// 중복되지 않는 단어의 수를 반환하는 함수
int WordCounter::GetUniqueWordCount(){
    int uniques = word_dict.size();
    return uniques;
}

// 특정 단어의 출현 횟수를 반환하는 함수
int WordCounter::GetWordCount_OneWord(const char *word){
    int oneword = 0;
    oneword = word_dict[word];
    return oneword;
}