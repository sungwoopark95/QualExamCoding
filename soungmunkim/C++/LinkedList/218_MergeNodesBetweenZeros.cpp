/*
[0 사이의 숫자 합들을 리스트로 반환하기]

You are given the head of a linked list, 
    which contains a series of integers separated by 0's. 
    
The beginning and end of the linked list will have Node.val == 0.

For every two consecutive 0's, 
    merge all the nodes lying in between them into a single node 
    whose value is the sum of all the merged nodes. 

The modified list should not contain any 0's.

(base) soungmunkim@gimseongmun-ui-MacBookPro LinkedList % g++ -std=c++17 218_MergeNodesBetweenZeros.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro LinkedList % ./test                                               
Enter the list of integers separated by spaces: [0,3,1,0,4,5,2,0]
[4, 11]

(base) soungmunkim@gimseongmun-ui-MacBookPro LinkedList % ./test
Enter the list of integers separated by spaces: [0,1,0,3,0,2,2,0]
[1, 3, 4]
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

void mergeNodes(ListNode* head) {

    vector<int> ans;  // 결과를 저장할 벡터
    int sum = 0;      // 연속된 노드의 합

    ListNode* curr = head; // 현재 노드를 헤드로 초기화
    ListNode* next = nullptr;

    // 노드가 존재하는 동안 순회
    while(curr->next) {
        next = curr->next;
        curr = next;

        if(curr->val != 0) {  // 노드의 값이 0이 아니라면
            sum += curr->val;  // 합에 노드의 값을 더함
        } else {  // 노드의 값이 0이면
            ans.push_back(sum);  // 합을 결과 벡터에 추가
            sum = 0;  // 합을 0으로 초기화
        }

    }
    // 최종 결과 프린트하기
    cout << "[";
    for (int i = 0; i < ans.size(); i++){
        cout  << ans[i];
        if(i != ans.size() - 1){
            cout << ", ";
        }
    }
    cout << "]" << endl;
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
    mergeNodes(head);


    // 메모리 해제 (간략하게 생략)
    return 0;
} 

