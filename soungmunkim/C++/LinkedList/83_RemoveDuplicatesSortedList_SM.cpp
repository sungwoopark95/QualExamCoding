/*
[sorted list에서 Duplicated num 제거하기]

Given the head of a sorted linked list, 
delete all duplicates such that each element appears only once. 
Return the linked list sorted as well.

(base) soungmunkim@gimseongmun-ui-MacBookPro LinkedList % ./test
Enter the list of integers separated by spaces: [1,1,2,3]
[1, 2, 3]

(base) soungmunkim@gimseongmun-ui-MacBookPro LinkedList % ./test
Enter the list of integers separated by spaces: [1,1,2,3,3]
[1, 2, 3]
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

// 겹치는 숫자 제거하기
ListNode* deleteDuplicates(ListNode* head){
    if(!head)
        return nullptr;

    ListNode* curr = head;

    while(curr) {
         // 비교할 다음 노드가 있고 현재노드와 다음노드 값이 같다면
        if (curr->next && curr->val == curr->next->val){
             // 현재노드의 다음노드를 겹친 노드 그 다음으로 설정해줌 (겹치는 노드 빼기)
            curr->next = curr->next->next;
        }
        curr = curr->next;
    }
    return head;
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
    ListNode* sorted_head = deleteDuplicates(head);
    print_linked_list(sorted_head);

    // 메모리 해제 (간략하게 생략)
    return 0;
}

