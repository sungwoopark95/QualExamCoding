#pragma once

// Fill in here
#include <string>
#include <map>
//char *은 뒤에 /0이 붙음 (size가 1 더 큼)
//std::string은 /0이 붙지 않음 (len & size 같음)


class WordCounter {
    public:
     // Constructor
    std::string text;
    std::map<std::string, int> word_dict;
    void InputText(std::string input_text);

    int GetWordCount();
    int GetCharacterCount();
    int GetUniqueWordCount();
    int GetWordCount_OneWord(const char * word);
};