/*
[linked list cycle 찾기]

Given head, the head of a linked list, 
    determine if the linked list has a cycle in it.

There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer. Internally, pos is used to denote the index of the node that tail's next pointer is connected to. Note that pos is not passed as a parameter.

Return true if there is a cycle in the linked list. Otherwise, return false.

Input: head = [3,2,0,-4], pos = 1
Output: true
Explanation: There is a cycle in the linked list, 
    where the tail connects to the 1st node (0-indexed).
*/

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

// 노드의 구조를 정의한 클래스
class ListNode {
public:
    int val;                 // 노드의 값을 저장하는 멤버 변수
    ListNode* next;          // 다음 노드를 가리키는 포인터

    // 생성자: 값과 다음 노드 포인터를 초기화합니다.
    ListNode(int x) : val(x), next(nullptr) {}
};

bool hasCycle(ListNode* head) {
    unordered_set<ListNode*> visited_nodes;  // 방문한 노드들을 저장할 해쉬셋 초기화

    // 연결 리스트를 순회
    while (head) {
        // 이미 방문한 노드인지 확인
        if (visited_nodes.find(head) != visited_nodes.end()) {
            // 현재 노드가 해쉬셋에 있으면 사이클이 있다는 의미
            return true;
        }
        
        // 현재 노드를 방문한 노드 해쉬셋에 추가
        visited_nodes.insert(head);
        
        // 다음 노드로 이동
        head = head->next;
    }
    // 모든 노드를 순회한 후 사이클을 발견하지 못한 경우
    return false;
}

ListNode* create_linked_list_with_cycle(vector<int>& nums, int pos) {
    if (nums.empty()) {
        return nullptr;  // 입력 벡터가 비어 있으면 nullptr 반환
    }

    // 첫 번째 노드 생성
    ListNode* head = new ListNode(nums[0]);
    ListNode* node = head;

    // 생성된 노드들을 저장할 벡터 초기화
    vector<ListNode*> nodes = {head};

    // 두 번째 노드부터 마지막 노드까지 순회하며 연결 리스트 생성
    for (int i = 1; i < nums.size(); i++) {
        ListNode* new_node = new ListNode(nums[i]);
        node->next = new_node;  // 이전 노드의 next를 현재 노드로 설정
        nodes.push_back(new_node);
        node = new_node;        // 현재 노드 갱신
    }

    // pos 위치의 노드로 마지막 노드의 next 설정하여 사이클 생성
    if (pos != -1) {
        node->next = nodes[pos];
    }

    return head;  // 생성된 연결 리스트의 헤드 노드 반환
}

int main() {
    vector<int> test_list = {3, 2, 0, -4};  // 테스트용 벡터
    int pos = 1;  // 사이클을 생성할 위치

    // 테스트용 연결 리스트 생성
    ListNode* test_linked_list = create_linked_list_with_cycle(test_list, pos);
    
    // 사이클 유무 확인 후 결과 출력
    cout << hasCycle(test_linked_list) << endl;  // 사이클이 존재하면 1(True) 출력
    return 0;
}
