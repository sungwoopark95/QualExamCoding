/*
[뒤에서 n번째 노드 지우기]
Given the head of a linked list, 
remove the nth node from the end of the list and return its head.

(base) soungmunkim@gimseongmun-ui-MacBookPro LinkedList % g++ -std=c++17 19_RemoveNthNodeFromEnd.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro LinkedList % ./test
Enter the first list: [1,2,3,4,5]
Enter the integer(nth) that you want to remove: 2
[1, 2, 3, 5]

(base) soungmunkim@gimseongmun-ui-MacBookPro LinkedList % ./test
Enter the first list: [1]
Enter the integer(nth) that you want to remove: 1
[]

(base) soungmunkim@gimseongmun-ui-MacBookPro LinkedList % ./test
Enter the first list: [1,2]
Enter the integer(nth) that you want to remove: 1
[1]
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

ListNode* removeNthFromEnd(ListNode* head, int n) {
    // 더미 노드를 생성하고 초기화한다.
    ListNode* dummy = new ListNode(0);
    dummy->next = head;

    ListNode* front = dummy;
    ListNode* back = dummy;

    // 뒷 포인터를 n개 먼저 움직인다.
    for (int i = 0; i < n; i++) {
        back = back->next;
    }

    // n개 떨어진 앞, 뒤 포인터가 끝까지 순차적으로 간다.
    while (back->next) {
        front = front->next;
        back = back->next;
    }

    // 맨 마지막에 다다르면 앞 포인터의 다음 노드를 뒷 포인터와 연결한다.
    front->next = front->next->next;

    // dummy 노드의 다음 노드를 반환한다.
    ListNode* result = dummy->next;
    delete dummy;
    return result;
}

int main() {
    // 첫 번째 연결 리스트 입력 받기
    cout << "Enter the first list: ";
    string line;
    getline(cin, line);

    // 불필요한 문자 제거
    for (auto& c : line) {
        if (c == '[' || c == ']' || c == ',') {
            c = ' ';
        }
    }

    istringstream iss1(line);
    int num;
    vector<int> v;
    while (iss1 >> num) {
        v.push_back(num);
    }
    ListNode* head = ListNode::create(v);

    // 지우고 싶은 뒤에서 n번째 받기
    cout << "Enter the integer(nth) that you want to remove: ";
    int n;
    cin >> n;

    // 뒤에서 nth node 지우기
    ListNode* result = removeNthFromEnd(head, n);
    if (result) {
        result->print();  // 결과 출력
    } else {
        cout << "[]\n";   // 빈 연결 리스트를 나타냄
    }


    // 메모리 해제를 위한 코드는 여기에 추가 구현이 필요합니다.
    return 0;
}