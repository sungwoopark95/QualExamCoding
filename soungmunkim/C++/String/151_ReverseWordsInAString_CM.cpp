/*
[string 거꾸로 뒤집기]
공백이 얼마나 있던 간에 뒤집었을 때는 공백 1개로 프린트되게 하게

(base) soungmunkim@gimseongmun-ui-MacBookPro String % g++ -std=c++17 151_ReverseWordsInAString_CM.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test                                                 
Enter a sentence:  "the sky is blue"
blue is sky the 
-----------------------------------------------------------------------
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Enter a sentence: the sky is blue
blue is sky the 
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Enter a sentence:   hello world  
world hello 
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Enter a sentence: a good   example
example good a 


(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test                                                 
blue is sky the 
world hello 
example good a 
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

// 문자열들을 거꾸로 출력하는 함수
// void reverseWords(const std::string& input)
void reverseWords(const vector<string>& strs) {
    int strsSize = strs.size(); // 문자열 개수 파악

    // 문자열이 없는 경우 빈 문자열을 반환합니다.
    if (strsSize == 0) {
        cout << "";
    }

    // 거꾸로 돌면서 단어를 출력합니다.
    for (int i = strsSize - 1; i >= 0; i--) {
        cout << strs[i] << " ";
    }
    cout << "\n";
}

int main() {
    string input;

    // 사용자에게 문자열을 입력받습니다.
    cout << "Enter a sentence: ";
    getline(cin, input);  // C++에서의 문자열 입력 함수

    // []나 ""를 제거합니다.
    input.erase(remove_if(input.begin(), input.end(), [](char c) {
        return c == '[' || c == ']' || c == '\"';
    }), input.end());

    vector<string> strs;  // 단어를 저장할 vector 컨테이너
    istringstream iss(input);  // 입력 문자열을 파싱하기 위한 stringstream 객체
    string token;

    // stringstream 객체를 사용하여 입력 문자열을 공백 기준으로 파싱합니다.
    while (iss >> token) {
        strs.push_back(token);  // 추출된 단어를 vector에 저장합니다.
    }

    // 단어들의 순서를 거꾸로 출력합니다.
    reverseWords(strs);

    return 0;
}


/*-------------------- int main에 예제가 주어졌을 때 ---------------------*/
// int main() {
//     // 주어진 예시 문자열들을 저장하는 벡터
//     vector<string> examples = {
//         "the sky is blue",
//         "  hello world  ",
//         "a good   example"
//     };

//     // 각 예시 문자열에 대해 처리
//     for (const auto& example : examples) {
//         // 문자열의 앞뒤 공백 제거
//         size_t first = example.find_first_not_of(' ');
//         size_t last = example.find_last_not_of(' ');
//         string trimmedExample = example.substr(first, (last - first + 1));

//         vector<string> words;  // 단어들을 저장할 벡터
//         istringstream stream(trimmedExample);  // 문자열 스트림으로 변환
//         string word;
//         // 스트림에서 단어를 추출하여 words 벡터에 저장
//         while (stream >> word) {
//             words.push_back(word);
//         }

//         // 단어들을 거꾸로 출력하는 함수 호출
//         reverseWords(words);
//     }

//     return 0;  // 프로그램 종료
// }
