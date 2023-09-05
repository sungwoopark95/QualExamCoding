/*
 * 이중 Linked List를 이용하여 Deque 구현
 */
#include <iostream>
using namespace std;

// Doubly Linked List
struct Node {
    int data;
    Node* prev; // 이전 Node를 가리키는 pointer
    Node* next; // 다음 Node를 가리키는 pointer

public:
    Node(){
        prev = nullptr;
        next = nullptr;
        data = 0;
    }
    Node(int n, Node* prevNode = nullptr, Node* nextNode = nullptr){
        data = n;
        prev = prevNode;
        next = nextNode;
    }
    ~Node(){}

    void setPrev(Node* prevNode){
        prev = prevNode;
    }
    void setNext(Node* nextNode){
        next = nextNode;
    }
};

// Deque Class
class Deque {
private:
    Node* front;    // Deack의 front를 가리키는 Node pointer
    Node* rear;     // Deack의 rear를 가리키는 Node pointer
    int dataSize;   // Stack에 저장된 데이터 size

public:
    Deque(){
        front = nullptr;
        rear = nullptr;
        dataSize = 0;
    }
    ~Deque(){
        while(!isEmpty()){
            deleteFront(); //deleteRear();
        }
        delete front;
        delete rear;
    }

    //새로운 node를 생성 (prev : null, next : 기존의 front node)
    //front를 새로운 node로 변경
    //최초 생성이라면 rear = node 해줌
    //이후 front가 추가될 때마다 기존 node의 prev에 새로 추가되는 node 대입
    void addFront(int n){
        Node* node = new Node(n, nullptr, front);
        if(rear == nullptr){
            rear = node;
        }else{
            front->setPrev(node);
        }
        front = node;
        dataSize++;
    }

    //addFront()와 같은 맥락.
    //새로운 node를 생성 (prev : 기존의 rear node, next : null)
    //rear를 새로운 node로 변경
    //최초 생성이라면 front = node 해줌
    //이후 rear가 추가될 때마다 기존 node의 next에 새로 추가되는 node 대입
    void addRear(int n){
        Node* node = new Node(n, rear, nullptr);
        if(front == nullptr){
            front = node;
        }else{
            rear->setNext(node);
        }
        rear = node;
        dataSize++;
    }

    //deque가 비어있는 경우 error occurred
    //그렇지 않다면, 우선 front node의 데이터를 임시 변수 'data'에 담아놓음
    //front를 next node로 변경한 다음, 삭제된 node(front였던)는 delete 처리 (메모리자원을위해)
    //아까 담아놓은 'data'를 반환
    //또한 현재 front노드의 prev를 null로 지정
    int deleteFront(){
        if(isEmpty()){
            cout << "Deque Empty Error" << endl;
            exit(EXIT_FAILURE);
        }else{
            int data = front->data;
            Node* node = front;
            front = front->next;
            front->setPrev(nullptr);
            delete node;
            dataSize--;
            return data;
        }
    }

    //deleteFront()와 같은 맥락.
    //deque가 비어있는 경우 error occurred
    //그렇지 않다면, 우선 rear node의 데이터를 임시 변수 'data'에 담아놓음
    //rear를 prev node로 변경한 다음, 삭제된 node(rear였던)는 delete 처리 (메모리자원을위해)
    //아까 담아놓은 'data'를 반환
    //또한 현재 rear노드의 next를 null로 지정
    int deleteRear(){
        if(isEmpty()){
            cout << "Deque Empty Error" << endl;
            exit(EXIT_FAILURE);
        }else{
            int data = rear->data;
            Node* node = rear;
            rear = rear->prev;
            rear->setNext(nullptr);
            delete node;
            dataSize--;
            return data;
        }
    }

    // deque의 모든 data 출력
    void display(){
        if(isEmpty()){
            cout << "Deque is Empty" << endl;
        }else{
            Node* node = front;
            while(node){
                cout << "[" << node->data << "]";
                node = node->next;
            }
            cout << endl;
        }
    }

    // deque size 반환
    int size(){
        return dataSize;
    }

    bool isEmpty(){
        return dataSize == 0;
    }
};

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