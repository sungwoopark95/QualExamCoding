/*
Given the head of a singly linked list, implement the function insertion_sort_list such
that sorts the list using insertion sort, and returns the sorted list's head.

(base) soungmunkim@gimseongmun-ui-MacBookPro LinkedList % g++ -std=c++17 147_InsertionSortLitst_v2.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro LinkedList % ./test                                              
Enter the list of integers separated by spaces: [4,1,3,2]
[1 2 3 4]
*/

/*
Linked list를 유지해서 푼 버전
*/

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

// 연결 리스트의 노드를 정의하는 구조체
struct ListNode {
    int val;                      // 노드의 값
    ListNode *next;               // 다음 노드를 가리키는 포인터
    ListNode(int x) : val(x), next(NULL) {} // 생성자를 통해 값을 초기화하고, 다음 노드는 NULL로 설정
};

// 벡터로부터 연결 리스트를 생성하고 시작 노드를 반환하는 함수
ListNode* create_linked_list(const vector<int>& v) {
    if (v.empty()) return nullptr; // 벡터가 비어있으면 nullptr 반환

    ListNode* start = new ListNode(v[0]);  // 첫 번째 원소로 시작 노드를 생성
    ListNode* node = start;                // 현재 노드를 시작 노드로 설정

    for (size_t i = 1; i < v.size(); ++i) { // 벡터의 나머지 원소를 순회하며 연결 리스트 생성
        ListNode* node_new = new ListNode(v[i]);  // 새로운 노드 생성
        node->next = node_new;                   // 현재 노드의 다음 노드를 새로운 노드로 연결
        node = node_new;                         // 현재 노드를 새로운 노드로 갱신
    }

    return start; // 생성된 연결 리스트의 시작 노드 반환
}

// 연결 리스트의 모든 노드의 값을 출력하는 함수
void print_linked_list(ListNode* node) {
    cout << "[";
    while (node->next) {                      // 노드가 nullptr이 될 때까지 순회
        cout << node->val << ", ";  // 현재 노드의 값을 출력
        node = node->next;              // 다음 노드로 이동
    }
    cout << node->val << "]" << endl;             // 줄바꿈 출력
}

// 연결 리스트를 삽입 정렬을 이용해 오름차순으로 정렬하는 함수
ListNode* insert_sort_list(ListNode* head) {
    ListNode* dummy = new ListNode(0);  // 더미 노드 생성
    dummy->next = head;                 // 더미 노드의 다음 노드를 헤드 노드로 설정
    ListNode* prev = dummy;             // prev 포인터를 더미 노드로 설정
    ListNode* curr = head;              // curr 포인터를 헤드 노드로 설정

    while (curr) {
        if (curr->next && curr->val > curr->next->val) { // 현재 노드의 값이 다음 노드의 값보다 크다면
            while (prev->next && prev->next->val < curr->next->val) { // 삽입할 위치를 찾기 위해 prev 이동
                prev = prev->next;
            }

            ListNode* temp = curr->next; // temp는 현재 노드의 다음 노드
            curr->next = temp->next;     // curr의 다음 노드를 temp의 다음 노드로 설정
            temp->next = prev->next;     // temp의 다음 노드를 prev의 다음 노드로 설정
            prev->next = temp;           // prev의 다음 노드를 temp로 설정

            prev = dummy;                // prev를 더미 노드로 재설정
        } else {
            curr = curr->next;           // curr를 다음 노드로 이동
        }
    }

    return dummy->next;                  // 정렬된 연결 리스트의 시작 노드 반환
}

int main() {
    // 사용자에게 숫자 리스트를 입력하라는 메시지를 출력
    cout << "Enter the list of integers separated by spaces: ";
    string line;
    getline(cin, line); // 전체 라인을 읽음

    // 불필요한 문자들 제거
    for (auto& c : line) {
        if (c == '[' || c == ']' || c == ',') {
            c = ' '; // 대괄호와 쉼표를 공백으로 교체
        }
    }

    istringstream iss(line);
    int num;
    vector<int> v;
    // stringstream을 사용하여 공백을 기준으로 숫자를 파싱
    while (iss >> num) {
        v.push_back(num); // 파싱한 숫자를 벡터에 추가
    }

    // 연결 리스트 생성 및 출력
    ListNode* head = create_linked_list(v);
    // print_linked_list(head);
    
    // 연결 리스트 정렬 및 출력
    ListNode* sorted_head = insert_sort_list(head);
    print_linked_list(sorted_head);

    // 메모리 해제 (간략하게 생략)
    return 0;
}
