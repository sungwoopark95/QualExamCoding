/*
 * 이중 연결 리스트를 사용하여 Deque를 구현한 코드
 */
#include <iostream>
using namespace std;

// Node: 이중 연결 리스트의 기본 단위입니다.
struct Node {
    int data;       // 노드에 저장되는 값
    Node* prev;     // 이전 노드를 가리키는 포인터
    Node* next;     // 다음 노드를 가리키는 포인터

public:
    // 기본 생성자
    Node(){
        prev = nullptr;
        next = nullptr;
        data = 0;
    }
    // 값을 받는 생성자
    Node(int n, Node* prevNode = nullptr, Node* nextNode = nullptr){
        data = n;
        prev = prevNode;
        next = nextNode;
    }

    // 이전 노드를 설정하는 함수
    void setPrev(Node* prevNode){
        prev = prevNode;
    }
    // 다음 노드를 설정하는 함수
    void setNext(Node* nextNode){
        next = nextNode;
    }
};

// Deque: 이중 연결 리스트를 사용하여 구현된 Deque 클래스
class Deque {
private:
    Node* front;    // Deque의 앞쪽 노드를 가리키는 포인터
    Node* rear;     // Deque의 뒷쪽 노드를 가리키는 포인터
    int dataSize;   // 현재 Deque에 저장된 데이터의 개수

public:
    // 생성자: 초기에는 비어있는 상태
    Deque(){
        front = nullptr;
        rear = nullptr;
        dataSize = 0;
    }
    // 소멸자: Deque 소멸 시 모든 노드 메모리 해제
    ~Deque(){
        while(!isEmpty()){
            deleteFront();
        }
        delete front;
        delete rear;
    }

    // 앞쪽에 데이터 추가
    void addFront(int n){
        Node* node = new Node(n, nullptr, front);
        if(rear == nullptr){  // 첫 번째 노드인 경우
            rear = node;
        }else{
            front->setPrev(node); // 기존 front 노드의 prev를 새 노드로 설정
        }
        front = node; // front 포인터를 새 노드로 업데이트
        dataSize++;   // 데이터 개수 증가
    }

    // 뒷쪽에 데이터 추가
    void addRear(int n){
        Node* node = new Node(n, rear, nullptr);
        if(front == nullptr){  // 첫 번째 노드인 경우
            front = node;
        }else{
            rear->setNext(node); // 기존 rear 노드의 next를 새 노드로 설정
        }
        rear = node;  // rear 포인터를 새 노드로 업데이트
        dataSize++;   // 데이터 개수 증가
    }

    // 앞쪽 데이터 삭제 후 반환
    int deleteFront(){
        if(isEmpty()){
            cout << "Deque Empty Error" << endl;
            exit(EXIT_FAILURE);
        }else{
            int data = front->data;
            Node* node = front;
            front = front->next;
            if(front) front->setPrev(nullptr);  // front가 nullptr이 아니면 prev를 nullptr로 설정
            delete node;
            dataSize--;   // 데이터 개수 감소
            return data;
        }
    }

    //deleteFront()와 같은 맥락.
    //deque가 비어있는 경우 error occurred
    //그렇지 않다면, 우선 rear node의 데이터를 임시 변수 'data'에 담아놓음
    //rear를 prev node로 변경한 다음, 삭제된 node(rear였던)는 delete 처리 (메모리자원을위해)
    //아까 담아놓은 'data'를 반환
    //또한 현재 rear노드의 next를 null로 지정
    // 뒷쪽 데이터 삭제 후 반환
    int deleteRear(){
        if(isEmpty()){
            cout << "Deque Empty Error" << endl;
            exit(EXIT_FAILURE);
        }else{
            int data = rear->data;
            Node* node = rear;
            rear = rear->prev;
            if(rear) rear->setNext(nullptr);  // rear가 nullptr이 아니면 next를 nullptr로 설정
            delete node;
            dataSize--;   // 데이터 개수 감소
            return data;
        }
    }

    // Deque 내의 모든 데이터를 출력
    void display(){
        if(isEmpty()){
            cout << "Deque is Empty" << endl;
        }else{
            Node* node = front;
            while(node){
                cout << "[" << node->data << "]";
                node = node->next;  // 다음 노드로 이동
            }
            cout << endl;
        }
    }

    // Deque의 크기(저장된 데이터 개수)를 반환
    int size(){
        return dataSize;
    }

    // Deque가 비어있는지 확인
    bool isEmpty(){
        return dataSize == 0;
    }
};

// 메인 함수: Deque 클래스를 테스트하는 코드
int main() {
    Deque deque;

    cout << "===== addRear x3 =====" << endl;
    deque.addRear(1);
    deque.addRear(2);
    deque.addRear(3);
    cout << " size : " << deque.size() << endl;
    deque.display();

    cout << "===== addFront x2 ======" << endl;
    deque.addFront(5);
    deque.addFront(6);
    cout << " size : " << deque.size() << endl;
    deque.display();

    cout << "===== deleteRear x1 ======" << endl;
    cout << deque.deleteRear() << endl;
    cout << " size : " << deque.size() << endl;
    deque.display();

    cout << "===== deleteFront x3 ======" << endl;
    cout << deque.deleteFront() << endl;
    cout << deque.deleteFront() << endl;
    cout << deque.deleteFront() << endl;
    cout << " size : " << deque.size() << endl;
    deque.display();
}