#include <stdlib.h>
#include <iostream>

using namespace std;
 
// 연결 리스트를 생성합니다.
class Node {
public:
    int data;     // 노드에 저장될 데이터
    Node* link;   // 다음 노드를 가리키는 포인터

    // 생성자
    Node(int n)
    {
        this->data = n;
        this->link = NULL;
    }
};

class Stack {
    Node* top;  // 스택의 최상단을 가리키는 포인터

public:
    // 기본 생성자: top 초기화
    Stack() { top = NULL; }

    // 데이터를 스택에 푸시
    void push(int data)
    {
        // 새 노드 temp를 힙에 메모리 할당
        Node* temp = new Node(data);

        // 스택(힙)이 가득 찼는지 확인.
        // 요소를 삽입하면 스택 오버플로우가 발생할 수 있음
        if (!temp) {
            cout << "\nStack Overflow";
            exit(1);
        }

        // temp 데이터 필드를 초기화
        temp->data = data;

        // temp 링크에 top 포인터 참조 삽입
        temp->link = top;

        // Stack의 top으로 temp 설정
        top = temp;
    }

    // 스택이 비어 있는지 확인하는 유틸리티 함수
    bool isEmpty()
    {
        // top이 NULL이면 스택에 요소가 없다는 의미
        return top == NULL;
    }

    // 스택의 최상단 요소를 반환하는 유틸리티 함수
    int peek()
    {
        // 스택이 비어 있지 않으면 top 요소 반환
        if (!isEmpty())
            return top->data;
        else
            exit(1);
    }

    // 스택에서 키를 제거하는 함수
    void pop()
    {
        Node* temp;

        // 스택 언더플로우 확인
        if (top == NULL) {
            cout << "\nStack Underflow" << endl;
            exit(1);
        }
        else {
            // top을 temp에 할당
            temp = top;

            // 두 번째 노드를 top으로 설정
            top = top->link;

            // 이것은 첫 번째 노드와 두 번째 노드 사이의 링크를 자동으로 파괴함

            // top 노드의 메모리 해제 (노드 삭제)
            free(temp);
        }
    }

    // 스택의 모든 요소를 출력하는 함수
    void display()
    {
        Node* temp;

        // 스택 언더플로우 확인
        if (top == NULL) {
            cout << "\nStack Underflow";
            exit(1);
        }
        else {
            temp = top;
            while (temp != NULL) {

                // 노드 데이터 출력
                cout << temp->data;

                // temp 링크에 temp 할당
                temp = temp->link;
                if (temp != NULL)
                    cout << " -> ";
            }
        }
    }
};

 
// Driven Program
int main()
{
    // Creating a stack
    Stack s;
 
    // Push the elements of stack
    s.push(11);
    s.push(22);
    s.push(33);
    s.push(44);
 
    // Display stack elements
    s.display();
 
    // Print top element of stack
    cout << "\nTop element is " << s.peek() << endl;
 
    // Delete top elements of stack
    s.pop();
    s.pop();
 
    // Display stack elements
    s.display();
 
    // Print top element of stack
    cout << "\nTop element is " << s.peek() << endl;
 
    return 0;
}