#include <iostream>
#include <vector>

class ListNode {
public:
    int val;
    ListNode* next;

    ListNode(int x) : val(x), next(nullptr) {}
};

std::vector<int> linkedListToList(ListNode* head) {
    std::vector<int> result;     // 결과를 저장할 벡터 초기화
    ListNode* current = head;

    while (current) {
        result.push_back(current->val);  // 현재 노드의 값을 벡터에 추가
        current = current->next;         // 다음 노드로 이동
    }

    return result; // 결과 벡터 반환
}
