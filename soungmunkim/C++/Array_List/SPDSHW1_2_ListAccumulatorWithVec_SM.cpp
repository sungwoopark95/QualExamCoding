/*
[list 합치기] C++에서 제공하는 vector와 string 이용하기

C에서는 nested list 지원이 안 되므로 -> Linked list로 풀기
list1 = [1, 2, 3]
list2 = [1, [2, 3], [[4]]]
list3 = [[[1], 3], [[4, 2], 5], 6, [[7]]]
위와 같은 정수 nested list를 입력으로 받아 저장된 모든 정수를 합쳐서 반환하는 함수

>>> ./SPDSHW1_2_ListAccumulator_SM "[1, 2, 3]"
6
>>> ./SPDSHW1_2_ListAccumulator_SM "[1, [2, 3], [4]]"
10
*/

#include <iostream>
#include <memory>
#include <string>
using namespace std;


// 노드의 타입을 나타내는 열거형 클래스
enum class NodeType {
    INTEGER, // 정수 타입
    LIST    // 리스트 타입
};

class ListNode : public enable_shared_from_this<ListNode> {
public:
    NodeType type;  // 현재 노드의 타입 (정수 or 리스트)
    union {
        int value;  // 정수 값을 저장할 변수
        shared_ptr<ListNode> sublist;  // 리스트를 가리킬 포인터 (sublist)
    };
    shared_ptr<ListNode> next;  // next node를 가리키는 포인터

    // int type node를 위한 생성자
    ListNode(int v) : type(NodeType::INTEGER), value(v), next(nullptr) {}

    // list type node를 위한 생성자
    ListNode(shared_ptr<ListNode> sub) : type(NodeType::LIST), sublist(sub), next(nullptr) {}

    // 문자열로부터 중첩 리스트를 파싱하는 함수
    static shared_ptr<ListNode> parseNestedList(const char*& pStr);
    
    // 중첩 리스트의 모든 값을 합산하는 함수
    int listAccumulator();
};

// 문자열로부터 중첩 리스트를 파싱하여 ListNode 형태로 반환하는 함수
shared_ptr<ListNode> ListNode::parseNestedList(const char*& pStr) {
    auto head = make_shared<ListNode>(0);  // 가상의 시작 노드
    auto current = head;

    // ']' 문자를 만나거나 문자열의 끝을 만날 때까지 반복
    while (*pStr && *pStr != ']') {
        if (*pStr == '[') {  // '[' 문자를 만나면 새로운 리스트 시작
            pStr++;
            auto sublist = parseNestedList(pStr);
            auto newNode = make_shared<ListNode>(sublist);
            current->next = newNode;
            current = newNode;
        } else if ('0' <= *pStr && *pStr <= '9') {  // 숫자를 만나면
            int value = 0;
            // 숫자 값을 추출
            while ('0' <= *pStr && *pStr <= '9') {
                value = value * 10 + (*pStr - '0');
                pStr++;
            }
            auto newNode = make_shared<ListNode>(value);
            current->next = newNode;
            current = newNode;
        } else {  // 그 외 문자는 무시
            pStr++;
        }
    }

    if (*pStr == ']') pStr++;  // ']' 문자 다음으로 이동
    return head->next;  // 가상의 시작 노드 다음 노드 반환
}

// 중첩 리스트의 모든 값을 합산하는 함수
int ListNode::listAccumulator() {
    int sum = 0;
    auto node = shared_from_this();  // 현재 객체의 shared_ptr 획득
    while (node) {
        if (node->type == NodeType::INTEGER) {  // 정수 타입 노드면 값을 합산
            sum += node->value;
        } else {  // 리스트 타입 노드면 재귀적으로 합산
            sum += node->sublist->listAccumulator();
        }
        node = node->next;  // 다음 노드로 이동
    }
    return sum;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "사용법: " << argv[0] << " <중첩 리스트>" << endl;
        return 1;
    }

    const char* input = argv[1];
    auto head = ListNode::parseNestedList(input);  // 문자열로부터 중첩 리스트 파싱
    int sum = head->listAccumulator();  // 중첩 리스트의 모든 값을 합산
    cout << sum << endl;  // 결과 출력

    return 0;
}
