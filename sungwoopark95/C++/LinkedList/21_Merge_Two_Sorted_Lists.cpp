/*
"""
두 개의 정렬된 연결 리스트를 병합하는 함수
Input: list1 = [1,2,4], list2 = [1,3,4]
Output: [1,1,2,3,4,4]

Input: list1 = [], list2 = []
Output: []

Input: list1 = [], list2 = [0]
Output: [0]
"""
*/
#include <iostream>
#include <vector>
using namespace std;

class ListNode {
public:
    int val;
    ListNode* next;

    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* create_linked_list(const vector<int>& l) {
    if (l.empty()) {
        return nullptr;
    }

    ListNode* start = new ListNode(l[0]);
    ListNode* node = start;

    for (int i = 1; i < l.size(); i++) {
        ListNode* node_new = new ListNode(l[i]);
        node->next = node_new;
        node = node_new;
    }

    return start;
}

vector<int> linked_to_list(ListNode* head) {
    vector<int> ans;
    ListNode* curr = head;
    while (curr) {
        ans.push_back(curr->val);
        curr = curr->next;
    }
    return ans;
}

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    // 두 리스트가 모두 비어 있으면 nullptr 반환
    if (!list1 && !list2) {
        return nullptr;
    }
    // list1만 비어 있으면 list2 반환
    if (!list1) {
        return list2;
    }
    // list2만 비어 있으면 list1 반환
    if (!list2) {
        return list1;
    }

    ListNode* base;
    ListNode* other;
    // list1과 list2의 첫 번째 노드 값을 비교하여 더 작은 값을 가진 노드를 기준(base)으로 설정
    if (list1->val < list2->val) {
        base = list1;
        other = list2;
    } else {
        base = list2;
        other = list1;
    }

    // curr1과 curr2는 각 리스트의 현재 위치를 추적하는 포인터입니다.
    ListNode* curr1 = base;
    ListNode* curr2 = other;

    // 두 리스트 중 하나가 끝날 때까지 반복
    while (curr1 && curr2) {
        // curr1의 다음 노드 값이 curr2의 현재 노드 값보다 작으면 curr1을 다음 노드로 이동
        while (curr1->next && curr1->next->val < curr2->val) {
            curr1 = curr1->next;
        }

        // 삽입할 위치를 임시로 저장
        ListNode* temp1 = curr1->next;

        // curr2의 노드들을 curr1의 연결 리스트에 삽입
        while (temp1 && curr2 && curr2->val < temp1->val) {
            ListNode* temp2 = curr2;
            curr1->next = temp2;
            curr1 = curr1->next;
            curr2 = curr2->next;
            temp1 = curr1->next;
        }
    }

    // list2에 남아 있는 노드가 있으면 base 리스트의 끝에 추가
    if (curr2) {
        ListNode* newcurr = base;
        while (newcurr->next) {
            newcurr = newcurr->next;
        }
        newcurr->next = curr2;
    }

    // 병합된 리스트의 첫 번째 노드 반환
    return base;
}

int main() {
    // Sample usage
    vector<int> l1 = {1, 3, 5};
    vector<int> l2 = {2, 4, 6};

    ListNode* list1 = create_linked_list(l1);
    ListNode* list2 = create_linked_list(l2);

    ListNode* mergedList = mergeTwoLists(list1, list2);

    vector<int> ans = linked_to_list(mergedList);
    for (int val : ans) {
        cout << val << " ";
    }

    // Remember to free the allocated memory for linked list nodes
}
