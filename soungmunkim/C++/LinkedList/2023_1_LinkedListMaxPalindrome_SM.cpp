/*
[Linked list로 max palindrome 찾기]
|!!! Linked list를 list로 변환해서 푼 것 !!!

Suppose we represent a sequence of integers from 0 to 9 with a list, and it is implemented with a linked list. 
For example, an integer list [3, 7, 6, 8] is implemented with a linked list:

A list of integers is a palindrome if it is identical to its reversion. 
Given a list s of integers, you will finally implement a function max_palindromes(s) 
    that prints a list of sub-lists of s that are maximal palindromes. 
    
That is, t is a list that contains palindrome sub-lists of s that are not a sub-list of another palindrome sub-list of s. 

For example, when s is [8,1,2,3,3,2,1,4,9,5,4,5,6,7,6,5,4,1], 
    **max-palindromes(s)** prints:
    [[8], [1,2,3,3,2,1], [4,9,4], [4,5,6,7,6,5,4]].

When s is [8,1,2,3,3,2,1,0,4,9,1,2,3,3,2,1,9,1], 
    max_palindromes(s) prints:
    [[8], [0], [4], [9,1,2,3,3,2,1,9], [1,9,1]].

Assume that the length of s is at most 32.


(a) Write a function **print_list(s)** that prints the sequence (i.e., the linked list) s in the list format. 
    For example, linked list in Figure 3 should be printed as [3,7,6,8].

(b) Write a function **palindrome(s)** that returns 1 if the list s is a palindrome. O
    therwise, it returns 0.

(c) Write a function **sub_list(s, t)** that returns 1 if the list t is a sub-list of the list s. 
    Otherwise, it returns 0. 

(d) Write the function **max_palindromes(s)** that uses palindrome(s), sub_list(s, t), and print_list(s).

In **print_list** and **max_palindromes**, the printed string should only contain square brackets ([ and ]), commas, digits (0 9), 
    and spaces between them. We accept any formats and orders that describe the answer. 
    For example, “[ [1, 2, 1], [3]]” and “[[3], [1,2,1]]” are both OK if the answer is [[1,2,1],[3]].
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 노드 클래스 정의
class Node {
public:
    char data;  // 노드에 저장할 데이터
    Node* next;  // 다음 노드를 가리키는 포인터
    Node(char d, Node* n = nullptr) : data(d), next(n) {}  // 생성자
};

// (a) 연결 리스트를 리스트 형식으로 출력하는 함수
void print_list(Node* s) {
    vector<char> output;  // 출력을 위한 벡터 생성
    while (s != nullptr) {  // 리스트의 끝까지 반복
        output.push_back(s->data);  // 데이터를 벡터에 추가
        s = s->next;  // 다음 노드로 이동
    }
    for (char c : output) {  // 벡터에 저장된 각 문자 출력
        cout << c << " ";
    }
    cout << endl;  // 줄 바꿈
}

// (b) 문자열이 회문인지 확인하는 함수
bool palindrome(string s) {
    string reversed_s = s;  // 문자열 복사
    reverse(reversed_s.begin(), reversed_s.end());  // 문자열 반전
    return s == reversed_s;  // 원본과 반전된 문자열이 같은지 확인
}

// (c) t가 s의 부분 문자열인지 확인하는 함수
bool substring(string s, string t) {
    return s.find(t) != string::npos;  // s에서 t를 찾아서 위치를 반환. 없으면 npos를 반환
}

// (d) 연결 리스트에서 가능한 최대 회문 찾는 함수
vector<string> max_palindromes(Node* s) {
    string str;  // 연결 리스트의 데이터를 저장할 문자열
    while (s) {
        str.push_back(s->data);  // 연결 리스트의 데이터를 문자열에 추가
        s = s->next;  // 다음 노드로 이동
    }

    vector<string> max_pals;  // 가능한 최대 회문 저장을 위한 벡터

    for (int i = 0; i < str.length(); ++i) {
        for (int j = i; j < str.length(); ++j) {
            string sub = str.substr(i, j - i + 1);  // 부분 문자열 추출
            if (palindrome(sub)) {  // 부분 문자열이 회문인지 확인
                bool is_maximal = true;
                for (string& pal : max_pals) {  // 이미 찾은 회문들과 비교
                    if (substring(pal, sub) && pal != sub) {
                        is_maximal = false;  // 현재 회문이 다른 회문의 부분 문자열인 경우
                        break;
                    }
                }
                if (is_maximal) {  // 현재 회문이 최대 회문인 경우
                    max_pals.push_back(sub);  // 벡터에 추가
                }
            }
        }
    }

    vector<string> filtered_max_pals;  // 최종적으로 선택된 최대 회문 저장을 위한 벡터
    for (string& pal : max_pals) {
        bool is_substring = false;
        for (string& other : max_pals) {  // 이미 찾은 회문들과 비교
            if (pal != other && substring(other, pal)) {  // 현재 회문이 다른 회문의 부분 문자열인 경우
                is_substring = true;
                break;
            }
        }
        if (!is_substring) {
            filtered_max_pals.push_back(pal);  // 현재 회문을 벡터에 추가
        }
    }

    for (string& pal : filtered_max_pals) {  // 최종적으로 선택된 최대 회문 출력
        cout << pal << " ";
    }
    cout << endl;

    return filtered_max_pals;  // 최종적으로 선택된 최대 회문 반환
}

int main() {
    // 사용자로부터 연결 리스트의 크기를 입력받기
    int size;
    cout << "Enter the size of the list: ";
    cin >> size;

    // 첫 번째 노드의 데이터 입력받기
    cout << "Enter node data: ";
    char data;
    cin >> data;
    Node* head = new Node(data);  // 첫 번째 노드 생성
    Node* current = head;

    // 나머지 노드의 데이터 입력받기
    for (int i = 1; i < size; ++i) {
        cout << "Enter node data: ";
        cin >> data;
        current->next = new Node(data);
        current = current->next;
    }

    // 입력된 연결 리스트 출력
    cout << "You entered the list: ";
    print_list(head);

    // 연결 리스트에서 최대 회문 찾기
    vector<string> result = max_palindromes(head);
    cout << "Maximal Palindromes: [";
    for (int i = 0; i < result.size(); i++) {
        cout << "[" << result[i] << "]";
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]." << endl;

    // 연결 리스트 메모리 해제
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    return 0;
}
