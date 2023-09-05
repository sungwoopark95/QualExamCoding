/*
[Max palindrome 찾기]
"palindrome"은 앞에서 뒤로 읽었을 때와 뒤에서 앞으로 읽었을 때 동일한 문자열이나 숫자, 또는 다른 시퀀스를 의미
    즉, palindrome은 그 내용이 앞뒤가 똑같은 단어나 문장을 지칭
    
The list contains palindromes that are not a substring of another palindrome.
A substring is a contiguous sequence of characters within a string.
The characters used in a string are only lower-case alphabets and a space character.

# TestCase
(base) soungmunkim@gimseongmun-ui-MacBookPro String % g++ -std=c++17 2022_1_1_MaxPalindrome.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test  
Please enter a string: 
kabccbadzdefgfeda
"k", "abccba", "dzd", "defgfed"
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test
Please enter a string: 
kabccba dzabccbaza
"k", " ", "d", "zabccbaz", "aza"
*/

/*
1. 문자열 s의 모든 substring을 찾습니다.
2. 각 substring이 palindrome인지 확인합니다.
3. palindrome이라면, 이 palindrome이 다른 palindrome의 substring인지 확인합니다.
4. substring이 아닌 palindrome 중에서 가장 긴 palindrome을 선택합니다. (palindrome 중에 서로 substring 아닌지 체크)
*/

#include <iostream>
#include <vector>
#include <string>
#include <stdbool.h>

using namespace std;

bool palindrome(string s);
bool substring(string s, string t);
void max_palindrome(string s);

int main(){
    string s;

    cout << "Please enter a string: " << endl;
    getline(cin, s);

    max_palindrome(s);

    return 0;
}

// palindrome인지 아닌지 체크하기
bool palindrome(string s){
    string reversed_s = "";
    int n = s.size();

    for(int i = n-1; i >= 0; i--){
        reversed_s += s[i];
    }
    // reversed string 잘 만들어 지는지 체크 완료
    // cout << "reversed s: " << reversed_s << endl; 

    if (s == reversed_s){
        return true;
    }
    else {
        return false;
    }
}

// t가 s의 substring인지 체크
bool substring(string s, string t){
    int n = s.size();
    int m = t.size();

    // 만약 길이 자체가 t가 더 크면 -> t는 s의 substring 아님
    if (m > n)
        return false;
    // s와 t 길이 차이만큼 for loop 돌건데 s를 t 길이만큼 돌면서 체크할 것
    for (int i = 0; i <= n-m; i++){
        if(s.substr(i, m) == t)
            return true;
    }
    return false;
}

// 주어진 문자열 s 내에서 가장 긴 palindrome들을 찾아 반환하는 함수
void max_palindrome(string s){
    vector<string> max_pals; // max palindromes 저장할 벡터

    // 모든 가능한 substring 뽑기
    int n = s.size();
    for (int i = 0; i < n; i++){
        for (int j = i; j < n; j++){
            string sub = s.substr(i, j-i+1); //s[i:j+1]

            if (palindrome(sub)){ // 현재 substring이 palindrome 일때
                bool is_maximal = true;

                for(const auto& pal : max_pals){
                    // 만약 현재 palindrome이 기존 palindrome의 substring이라면
                    if(substring(pal, sub) and pal != sub){
                        is_maximal = false;
                        break;
                    }
                }
                // 만약 현재 palindrome이 기존 palindrome의 substring이 아니라면 후보에 넣기
                if (is_maximal == true){
                    max_pals.push_back(sub);
                }
            }
        }
    }
    // palindrome 후보들간에서 substring인 후보는 빼기 (filltering 작업)
    vector<string> filtered_max_pals; // 최종 Palindromes 담을 리스트

    int m = max_pals.size();
    for(int i=0; i<m; i++){
        bool is_substring = false;
        for(int j=0; j<m; j++){
            if(i != j) {// 자기 자신 제외
                // max_pals[i] 가 다른 palindrome의 substring인지 체크
                if(substring(max_pals[j], max_pals[i])){
                    is_substring = true;
                    break;
                }
            }
        }
        if(is_substring == false)
            filtered_max_pals.push_back(max_pals[i]);
    }
    // 최종 결과 프린트하기
    for (int i = 0; i < filtered_max_pals.size(); i++){
        cout << "\"" << filtered_max_pals[i] << "\"";
        if(i != filtered_max_pals.size() - 1){
            cout << ", ";
        }
    }
    cout << endl;
}

