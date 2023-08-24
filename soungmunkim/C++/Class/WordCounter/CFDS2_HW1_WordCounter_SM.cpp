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

#include <iostream>
#include <string>
#include <map>
#include <sstream>

using namespace std;

/*-------------- WordCounter.h----------------*/
// superclass
class WordCounter{
    protected:
    string text;
    map<string, int> wordCount_dct;

    public:
    void InputText(string& input_text);
    int GetWordCount();
    int GetCharacterCount();
    int GetUniqueWordCount();
    int GetWordCount_OneWord(const char *word);
};

/*-------------- WordCounter.cpp----------------*/
void WordCounter::InputText(string& input_text) {
    /*
    만약 InputText(string, input_text)였다면,
    this -> text = input_text;
    */
    text = input_text; // input_text를 저장하기
    
    // text의 단어들 뽑아서 각 단어들과 나타나는 횟수 dict에 저장
    istringstream iss(text);
    string word;

    while (iss >> word){
        wordCount_dct[word]++;
    }
}

int WordCounter::GetWordCount(){
    // 단어 빈도 수 다 더하기 = 총 단어 수
    unsigned int total_words = 0;
    for (map<string, int>::iterator iter = wordCount_dct.begin(); iter != wordCount_dct.end(); iter++){
        total_words += iter->second;
    }
    return total_words;
}

int WordCounter::GetCharacterCount(){
    int size = text.size();
    int char_cnt = 0;

    for (int i = 0; i < size; i++){
        if(text[i] != ' ' && text[i] != ',' && text[i] != '.')
            char_cnt++;
    }
    return char_cnt;
}

int WordCounter::GetUniqueWordCount(){
    // dict size 구하기 = unique 단어 수
    int unique_words = wordCount_dct.size();
    
    return unique_words;
}

int WordCounter::GetWordCount_OneWord(const char *word){
    // 해당 단어의 value가 해당 단어 횟수
    int cnt = wordCount_dct[word];
    
    return cnt;
}



/*-------------- WordCounter_main.cpp----------------*/
int main() {
  
  	string text = "Mrs. Dursley was thin and blonde and had nearly twice the usual amount of neck, which came in very useful as she spent so much of her time craning over garden fences, spying on the neighbors.";
	WordCounter counter;
	counter.InputText(text);

    /* 만약 사용자가 input으로 sentence를 줄 때,
    WordCounter counter;
    string text;

    // 사용자에게 텍스트 입력 요청
    cout << "Please enter the text: ";
    getline(cin, text);  // 사용자의 전체 입력을 읽어서 text 변수에 저장

    counter.InputText(text);  // 사용자의 입력을 WordCounter 객체에 전달
    */
	
	cout << "Word Count: " << counter.GetWordCount() << endl;
	cout << "Character Count: " << counter.GetCharacterCount() << endl;
	cout << "Number of Unique Words: " << counter.GetUniqueWordCount() << endl;
 	cout << "The word and appears " << counter.GetWordCount_OneWord("and") << " times" << endl;
 	
 	return 0;
}