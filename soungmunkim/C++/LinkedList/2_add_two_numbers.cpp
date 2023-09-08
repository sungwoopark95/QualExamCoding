/*
[두 Linked list의 숫자를 합쳐서 한 linked list로 내보내기]

You are given two non-empty linked lists representing two non-negative integers. 
The digits are stored in reverse order, and each of their nodes contains a single digit. 
Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, 
    except the number 0 itself.

Input: l1 = [2,4,3], l2 = [5,6,4]
Output: [7,0,8]
Explanation: 342 + 465 = 807.

(base) soungmunkim@gimseongmun-ui-MacBookPro LinkedList % ./test
Enter the first list of integers in the format [x,y,z,...]: [2,4,3]
Enter the second list of integers in the format [x,y,z,...]: [5,6,4]
[7, 0, 8]

(base) soungmunkim@gimseongmun-ui-MacBookPro LinkedList % ./test
Enter the first list of integers in the format [x,y,z,...]: [0]
Enter the second list of integers in the format [x,y,z,...]: [0]
[0]

(base) soungmunkim@gimseongmun-ui-MacBookPro LinkedList % ./test
Enter the first list of integers in the format [x,y,z,...]: [9,9,9,9,9,9,9]
Enter the second list of integers in the format [x,y,z,...]: [9,9,9,9]
[8, 9, 9, 9, 0, 0, 0, 1]
*/

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class ListNode {
public:
    int val;                  // 노드의 값
    ListNode *next;           // 다음 노드를 가리키는 포인터

    ListNode(int x) : val(x), next(NULL) {}  // 생성자

    // 주어진 숫자 배열을 바탕으로 연결 리스트를 생성하는 스태틱 함수
    static ListNode* create(const vector<int>& nums) {
        if (nums.empty()) {
            return nullptr;  // 배열이 비어있다면 nullptr 반환
        }

        ListNode* start = new ListNode(nums[0]);
        ListNode* node = start;

        for (int i = 1; i < nums.size(); i++) {
            ListNode* node_new = new ListNode(nums[i]);
            node->next = node_new;
            node = node_new;
        }

        return start;  // 생성된 연결 리스트의 첫 번째 노드 반환
    }

    // 연결 리스트의 모든 노드의 값을 출력하는 함수
    void print() {
        cout << "[";
        ListNode* node = this;
        while (node->next) {
            cout << node->val << ", ";
            node = node->next;
        }
        cout << node->val << "]" << endl;
    }
};

// 두 연결 리스트를 받아 합을 새 연결 리스트로 반환하는 함수
ListNode* addTwoNums(ListNode* l1, ListNode* l2) {
    ListNode* dummy = new ListNode(0);  // 더미 노드 생성
    ListNode* current = dummy;
    int carry = 0;  // 올림값

    // 둘 중 하나의 리스트가 끝나거나 올림값이 없을 때까지 반복
    while (l1 || l2 || carry) {
        int sum = carry;
        if (l1) {
            sum += l1->val;
            l1 = l1->next;
        }

        if (l2) {
            sum += l2->val;
            l2 = l2->next;
        }

        carry = sum / 10;
        current->next = new ListNode(sum % 10);
        current = current->next;
    }

    ListNode* result = dummy->next;
    delete dummy;  // 더미 노드 메모리 해제
    return result;  // 결과 연결 리스트 반환
}

int main() {
    // 첫 번째 연결 리스트 입력 받기
    cout << "Enter the first list of integers separated by spaces: ";
    string line1;
    getline(cin, line1);

    // 불필요한 문자 제거
    for (auto& c : line1) {
        if (c == '[' || c == ']' || c == ',') {
            c = ' ';
        }
    }

    istringstream iss1(line1);
    int num1;
    vector<int> v1;
    while (iss1 >> num1) {
        v1.push_back(num1);
    }
    ListNode* head1 = ListNode::create(v1);

    // 두 번째 연결 리스트 입력 받기
    cout << "Enter the second list of integers separated by spaces: ";
    string line2;
    getline(cin, line2);

    // 불필요한 문자 제거
    for (auto& c : line2) {
        if (c == '[' || c == ']' || c == ',') {
            c = ' ';
        }
    }

    istringstream iss2(line2);
    int num2;
    vector<int> v2;
    while (iss2 >> num2) {
        v2.push_back(num2);
    }
    ListNode* head2 = ListNode::create(v2);

    // 두 연결 리스트 합산하기
    ListNode* result = addTwoNums(head1, head2);
    if (result) {
        result->print();
    } else{
        cout << "[]\n";
    }

    // 메모리 해제를 위한 코드는 여기에 추가 구현이 필요합니다.
    return 0;
}
