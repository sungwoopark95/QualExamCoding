/*
[Linked list 중간 노드부터 프린트 하기]
Given the head of a singly linked list, return the middle node of the linked list.

If there are two middle nodes, return the second middle node.

Input: head = [1,2,3,4,5]
Output: [3,4,5]
Explanation: The middle node of the list is node 3.

Input: head = [1,2,3,4,5,6]
Output: [4,5,6]
Explanation: Since the list has two middle nodes with values 3 and 4, we return the second one.

head = [1,2,3,4,5]
head1 = create_linked_list(head)
output1 = middleNode(head1)
print_linked_list(output1, []) # [3,4,5]

head = [1,2,3,4,5,6]
head2 = create_linked_list(head)
output2 = middleNode(head2)
print_linked_list(output2, [])  # [4,5,6]
*/

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

// 단일 연결 리스트의 노드를 위한 정의
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 리스트로부터 연결 리스트를 생성한 후 헤드 노드를 반환
ListNode* create_linked_list(const vector<int>& nums) {
    if (nums.empty()) {
        return nullptr;
    }

    ListNode* start = new ListNode(nums[0]);
    ListNode* node = start;

    for (int i = 1; i < nums.size(); i++) {
        ListNode* node_new = new ListNode(nums[i]);
        node->next = node_new;
        node = node_new;
    }

    return start;
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

ListNode* middleNode(ListNode* head) {
    ListNode* curr = head;
    vector<int> lst;

    // 리스트에 넣어서 중간 인덱스 찾기
    while (curr) {
        lst.push_back(curr->val);
        curr = curr->next;
    }

    int middle_point = lst.size() / 2;  // 정수 나눗셈은 자동으로 내림됨

    // 중간 인덱스 나올 때까지 돌고 찾으면 그 이후 노드들 리턴
    curr = head;
    for (int i = 0; i < middle_point; i++) {
        curr = curr->next;
    }

    return curr;
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
    ListNode* sorted_head = middleNode(head);
    print_linked_list(sorted_head);

    // 메모리 해제 (간략하게 생략)
    return 0;
}