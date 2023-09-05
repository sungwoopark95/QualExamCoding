/*
Given the head of a singly linked list, implement the function insertion_sort_list such
that sorts the list using insertion sort, and returns the sorted list's head.

(base) soungmunkim@gimseongmun-ui-MacBookPro LinkedList % ./test "[3,1,2,4]"
[3,1,2,4]
[1,2,3,4]
*/

/*
array로 바꿔서 풀기
*/


#include <iostream>
#include <vector>
#include <sstream>
using namespace std;  // 표준 네임스페이스 사용

// 두 정수 값을 교환하는 함수
void swap(int &a, int &b) {
    int temp = a;  // 임시 변수에 a 값을 저장
    a = b;  // a에 b 값을 저장
    b = temp;  // b에 임시 변수 값을 저장
}

// 연결 리스트의 노드를 정의하는 클래스
class ListNode {
public:
    int val;  // 노드의 값
    ListNode* next;  // 다음 노드를 가리키는 포인터

    // 생성자. 노드를 생성할 때 값을 초기화
    ListNode(int val, ListNode* next=NULL) {
        this->val = val;  // 현재 객체의 val 멤버 변수에 전달된 val 값을 저장
        this->next = next;  // 다음 노드 포인터 초기화 (기본값 NULL)
    }
};

// 주어진 배열을 기반으로 연결 리스트를 생성하는 함수
ListNode* create_linked_list(vector<int> &arr) {
    ListNode* head = new ListNode(arr[0]);  // 첫 번째 원소를 기반으로 헤드 노드 생성
    ListNode* curr = head;  // 현재 노드를 헤드로 초기화
    for (int i=1;i<arr.size();i++) {
        ListNode* newNode = new ListNode(arr[i]);  // 새 노드 생성
        curr->next = newNode;  // 현재 노드의 다음 노드를 새 노드로 설정
        curr = newNode;  // 현재 노드를 새 노드로 업데이트
    }
    return head;  // 생성된 연결 리스트의 헤드 반환
}

// 연결 리스트의 내용을 출력하는 함수
void print_linked_list(ListNode* head) {
    ListNode* curr = head;  // 현재 노드를 헤드로 초기화
    cout << "[";
    while (curr->next) {
        cout << curr->val << ",";  // 현재 노드의 값을 출력
        curr = curr->next;          // 다음 노드로 이동
    }
    cout << curr->val << "]";        // 마지막 노드의 값을 출력
    cout << endl;
}

// 연결 리스트를 배열로 변환하는 함수
vector<int> LinkedListToList(ListNode* head) {
    vector<int> newArr;  // 결과를 저장할 벡터
    ListNode* curr = head;  // 현재 노드를 헤드로 초기화
    while (curr) {
        newArr.push_back(curr->val);  // 벡터에 현재 노드의 값을 추가
        curr = curr->next;  // 다음 노드로 이동
    }
    return newArr;  // 변환된 배열 반환
}

// 연결 리스트를 삽입 정렬로 정렬하는 함수
ListNode* insertion_sort_list(ListNode* head) {
    vector<int> arr = LinkedListToList(head);  // 연결 리스트를 배열로 변환
    for (int i=1;i<arr.size();i++) {
        for (int j=i;j>0;j--) {
            if (arr[j-1] > arr[j]) {  // 앞의 원소가 더 크면
                swap(arr[j-1], arr[j]);  // 원소 교환
            } else {
                break;  // 정렬된 상태이면 반복 종료
            }
        }
    }
    return create_linked_list(arr);  // 정렬된 배열을 연결 리스트로 변환하여 반환
}

// 메인 함수
int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " [array]\n";  // 사용법 출력
        return 1;
    }

    string input = argv[1];  // 첫 번째 인자를 문자열로 저장
    vector<int> numbers;  // 숫자를 저장할 벡터

    istringstream iss(input);  // 입력 문자열을 스트림으로 변환
    string token;  // 각 토큰을 저장할 문자열
    while (getline(iss, token, ',')) {  // 스트림에서 ',' 구분자로 토큰을 추출
        if (token.front() == '[') token.erase(token.begin());  // '[' 제거
        if (token.back() == ']') token.pop_back();  // ']' 제거
        numbers.push_back(stoi(token));  // 문자열을 숫자로 변환하여 벡터에 추가
    }

    ListNode* head = create_linked_list(numbers);  // 벡터를 연결 리스트로 변환
    print_linked_list(head);  // 연결 리스트 출력
    ListNode* sorted = insertion_sort_list(head);  // 연결 리스트 정렬
    print_linked_list(sorted);  // 정렬된 연결 리스트 출력

    return 0;  // 프로그램 종료
}