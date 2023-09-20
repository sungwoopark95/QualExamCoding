#pragma once
#define MAX_WORDS 30
#include <string>

class Dictionary {
    protected :
    int size;

    public:
    std::string word_key[MAX_WORDS];
    int num_value[MAX_WORDS];
    Dictionary(){size=0;};
    int get_size(){return size;};
    void size_up(){size++;}
    int get_value(const std::string&);
    int get_idx(const std::string&);
    void put(const std::string&);

    static void num_to_string(int x);
};

void wordcount(std::string sentences);
