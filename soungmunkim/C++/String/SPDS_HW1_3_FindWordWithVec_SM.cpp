/*
c++에서 지원되는 string과 vector 등을 사용해서 풀기

[Find word in a sentence]
문장 내에서 단어의 등장 위치를 찾는 함수 find word 를 작성하라. 
문장에서 단어는 공백, 쉼표(,), 및 마침표 (.)로 구분된다. 
또한, 단어가 일치함을 확인할 때 대소문자는 구분하지 않는다. 
주어진 단어가 문장 내에서 몇번째 단어로 등장하는지 그 위치들을 구해 정수의 리스트로 반환한다 

TestCase)
s = "Some feelings are shallow, some feelings are deep. Some make us smile, some make us weap."
find_word s, "feelings"
find_word s, "FeelinGs"
find_word s, "some"
find_word s, "python"
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

// 대소문자를 구분하지 않고 두 문자열이 같은지 확인하는 함수
bool same(const string& input, const string& target) {
    // 입력된 두 문자열의 길이가 다르면 바로 false 반환
    if (input.size() != target.size()) {
        return false;
    }

    // 각 문자를 대소문자 구분 없이 비교
    for (size_t i = 0; i < input.size(); ++i) {
        if (tolower(input[i]) != tolower(target[i])) {
            return false;
        }
    }
    return true;
}

vector<int> find_word(const string& s, const string& target) {
    vector<int> positions;  // 결과를 저장할 벡터
    string word;            // 분리된 단어를 저장할 문자열
    istringstream iss(s);   // 문자열 스트림 생성
    int idx = 0;

    // 공백을 기준으로 문자열에서 단어 분리
    while (getline(iss, word, ' ')) {
        // 단어 끝에 쉼표나 마침표가 있으면 제거
        if (word.back() == ',' || word.back() == '.') {
            word.pop_back();
        }

        // 분리된 단어와 타겟 단어가 같은지 확인
        if (same(word, target)) {
            positions.push_back(idx);  // 일치하면 결과 벡터에 추가
        }
        idx++;  // 단어의 위치 증가
    }
    return positions;  // 결과 벡터 반환
}

int main(int argc, char* argv[]){
    // 인자의 수가 부족한 경우 사용법 출력
    if (argc < 3) {
    cout << "사용법: " << argv[0] << " <문장> <타겟_단어>" <<endl;
        return 1;
    }

    string input = argv[1];          // 첫 번째 인자: 문장
    string target_word = argv[2];    // 두 번째 인자: 타겟 단어

    // find_word 함수 호출하여 결과 받기
    vector<int> positions = find_word(input, target_word);
        
     // 결과 출력
    cout << "[";
        for (size_t i = 0; i < positions.size(); ++i) {
        cout << positions[i];
            if (i != positions.size() - 1) {  // 마지막 위치가 아니면 콤마와 공백 출력
            cout << ", ";
            }
        }
    cout << "]" << endl;

        return 0;
}
