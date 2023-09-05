/*
[Remove linked list elements]
Given the head of a linked list and an integer val, 
    remove all the nodes of the linked list that has Node.val == val, 
    and return the new head.
    
(base) soungmunkim@gimseongmun-ui-MacBookPro LinkedList % g++ -std=c++17 203_RemoveLinkedListElements_SM.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro LinkedList % ./test
Enter the list of integers separated by spaces and value: [7,7,7,7]
Enter the value you want to delete: 7
[]

(base) soungmunkim@gimseongmun-ui-MacBookPro LinkedList % ./test
Enter the list of integers separated by spaces and value: [1,2,3,4,6,5,6]
Enter the value you want to delete: 6
[1, 2, 3, 4, 5]
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
    while (node) {                      // 노드가 nullptr이 될 때까지 순회
        cout << node->val;  // 현재 노드의 값을 출력
        node = node->next;              // 다음 노드로 이동
        if (node) cout << ", ";         // 다음 노드가 있으면 쉼표 출력
    }
    cout << "]" << endl;                // 줄바꿈 출력
}


ListNode* removeElements(ListNode* head, int val){
    // 더미 노드를 생성하고, 이 더미의 next를 head로 설정
    // (이렇게 함으로써 head 자체가 삭제 대상이 될 경우에도 처리 가능)
    ListNode* dummy = new ListNode(0);
    dummy->next = head;

    // 현재 노드를 더미 노드를 설정
    ListNode* curr = dummy;

    if (!head)
        return;

    // 현재 노드의 next 노드가 None이 아닐 동안 반복
    while (curr -> next){
        // 현재 노드의 다음 노드의 값이 삭제 대상 값과 동일한 경우
        if(curr->next->val == val){
            // 현재 노드의 next를 그 다음 노드로 갱신
            curr->next = curr->next->next;
        }
        else {
            // 그렇지 않으면 현재 노드를 다음 노드로 이동
            curr = curr->next;
        }
    }
    // 더미 노드의 next를 반환 (새로운 head)
        return dummy->next;
}

int main() {
    // 사용자에게 숫자 리스트를 입력하라는 메시지를 출력
    cout << "Enter the list of integers separated by spaces and value: ";
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

    // 사용자에게 삭제하고 싶은 값을 입력하라는 메시지를 출력
    cout << "Enter the value you want to delete: ";
    int deleteVal;
    cin >> deleteVal;

    // 연결 리스트 생성 및 출력
    ListNode* head = create_linked_list(v);
    // print_linked_list(head);
    
    // 연결 리스트 정렬 및 출력
    ListNode* sorted_head = removeElements(head, deleteVal);
    print_linked_list(sorted_head);

    // 메모리 해제 (간략하게 생략)
    return 0;
}
