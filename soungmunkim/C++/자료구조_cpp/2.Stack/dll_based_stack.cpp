//
//  ListBaseStack.hpp
//  DataStructure
//
//  Created by sogoagain on 2017. 1. 22..
//

#ifndef ListBaseStack_h
#define ListBaseStack_h

#include <algorithm>

using namespace std;

template <typename E>
class Stack {
private:
    // 노드 클래스 선언
    class Node {
        friend class Stack;  // Stack 클래스가 Node의 private 멤버에 접근할 수 있도록 함
    private:
        E data;  // 노드에 저장될 데이터
        Node* rightLink;  // 오른쪽(위) 노드를 가리키는 링크
        Node* leftLink;   // 왼쪽(아래) 노드를 가리키는 링크

    public:
        Node(void) {
            rightLink = NULL;
        }
        Node(E item, Node* previous, Node* next) 
        : data(item), rightLink(next), leftLink(previous) { }  // 초기화 리스트를 사용한 생성자
    };

    Node* head;  // 스택의 최상단을 가리키는 포인터 (top)
    Node* tail;  // 스택의 최하단을 가리키는 포인터 (bottom)

public:
    // 기본 생성자: head와 tail 초기화
    Stack() {
        head = NULL;
        tail = NULL;
    }
    // 복사 생성자
    Stack(const Stack<E>& copy) {
        head = NULL;
        tail = NULL;
        
        Node* search = copy.tail;  // 입력 스택의 tail부터 시작하여 거꾸로 탐색
        
        while(search != NULL) {
            this->push(search->data);  // 데이터를 현재 스택에 푸시
            search = search->leftLink;  // 왼쪽(아래) 노드로 이동
        }
    }
    // 소멸자: 동적 할당된 메모리 해제
    ~Stack() {
        while(head != NULL) {
            Node* temp = head;
            head = temp->rightLink;
            delete temp;
        }
    }
    // 대입 연산자 오버로딩
    Stack<E>& operator=(const Stack<E>& reference) {
        Stack<E> temp = reference;
        std::swap(temp.head, head);  // head 스왑
        std::swap(temp.tail, tail);  // tail 스왑
        return *this;
    }

    // 스택이 비어 있는지 확인
    bool isEmpty(void) {
        return (head == NULL);
    }
    // 아이템을 스택에 푸시
    void push(E item) {
        head = new Node(item, NULL, head);
        
        if(tail == NULL) {
            tail = head;
        } else {
            head->rightLink->leftLink = head;
        }
    }
    // 스택의 최상단에서 아이템을 팝 (읽기 및 제거)
    E pop(void) {
        if(isEmpty()) {
            fprintf(stderr, "스택이 비어있습니다.\n");
            exit(EXIT_FAILURE);
        }

        Node* target = head;  // 현재 head를 target으로 설정
        E poppedItem = target->data;  // 팝 할 아이템
        
        head = target->rightLink;  // head를 다음 노드로 이동
        
        if(head == NULL) {  // 스택이 비었을 경우
            tail = NULL;
        }

        delete target;  // 노드 삭제
        return poppedItem;
    }
    // 스택의 최상단 아이템을 읽음 (제거 없이)
    E peek(void) {
        if(isEmpty()) {
            fprintf(stderr, "스택이 비어있습니다.\n");
            exit(EXIT_FAILURE);
        }

        return head->data;  // 현재 head의 데이터 반환
    }
};

#endif /* ListBaseStack_h */
