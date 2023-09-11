#include <string>
#include <iostream>

using namespace std;

// 노드 클래스 정의
class Node {
    string strData;     // 문자열 데이터
    Node* prev;         // 이전 노드 포인터
    Node* next;         // 다음 노드 포인터
    friend class DLinkedList; // DLinkedList 클래스에 private 멤버 접근 허용
};

// 이중 연결 리스트 클래스 정의
class DLinkedList {
    public:
        DLinkedList();               // 생성자
        ~DLinkedList();              // 소멸자
        bool isEmpty() const;        // 리스트가 비어 있는지 확인
        const string& getFront() const; // 첫 번째 노드의 데이터 반환
        const string& getBack() const;  // 마지막 노드의 데이터 반환
        void addFront(const string& e); // 리스트 앞에 노드 추가
        void addBack(const string& e);  // 리스트 뒤에 노드 추가
        void removeFront();             // 리스트 앞의 노드 삭제
        void removeBack();              // 리스트 뒤의 노드 삭제
        void TraverseForward();         // 리스트 앞에서 뒤로 순회하며 출력
        void TraverseBackward();        // 리스트 뒤에서 앞으로 순회하며 출력
    private:
        Node* header;                 // 리스트의 시작을 가리키는 노드
        Node* trailer;                // 리스트의 끝을 가리키는 노드
    protected:
        void add(Node* v, const string& e); // 특정 노드 뒤에 새 노드 추가
        void remove(Node* v);               // 특정 노드 삭제
};

// 생성자 구현
DLinkedList::DLinkedList() {
    header = new Node;            // 헤더 노드 할당
    trailer = new Node;           // 트레일러 노드 할당

    header->next = trailer;       // 헤더와 트레일러 연결
    trailer->prev = header;       // 트레일러와 헤더 연결
}

// 소멸자 구현
DLinkedList::~DLinkedList() {
    while(!isEmpty()) removeFront(); // 리스트가 빌 때까지 앞 노드 삭제
    delete header;                // 헤더 노드 해제
    delete trailer;               // 트레일러 노드 해제
}

// 리스트가 비어 있는지 확인하는 함수 구현
bool DLinkedList::isEmpty() const {
    return (header->next == trailer); // 헤더 다음이 트레일러면 true
}

// 리스트의 첫 번째 노드의 데이터를 반환하는 함수 구현
const string& DLinkedList::getFront() const {
    return header->next->strData; // 헤더 다음 노드의 데이터 반환
}

// 리스트의 마지막 노드의 데이터를 반환하는 함수 구현
const string& DLinkedList::getBack() const {
    return trailer->prev->strData; // 트레일러 이전 노드의 데이터 반환
}
// 리스트의 앞에 데이터를 추가하는 함수
void DLinkedList::addFront(const string& e) {
    add(header, e);  // 헤더 뒤에 새 노드 추가
}

// 리스트의 뒤에 데이터를 추가하는 함수
void DLinkedList::addBack(const string& e) {
    add(trailer->prev, e);  // 트레일러 앞에 새 노드 추가
}

// 특정 노드 v 뒤에 새 노드를 추가하는 함수
void DLinkedList::add(Node* v, const string& e) {
    Node* u = new Node;      // 새 노드 할당
    u->strData = e;          // 데이터 설정
    u->next = v->next;       // 새 노드의 다음을 v의 다음으로 설정
    u->prev = v;             // 새 노드의 이전을 v로 설정

    v->next->prev = u;       // v 다음 노드의 이전을 새 노드로 설정
    v->next = u;             // v의 다음을 새 노드로 설정
}

// 리스트의 앞 노드를 삭제하는 함수
void DLinkedList::removeFront() {
    remove(header->next);    // 헤더 다음 노드 삭제
}

// 리스트의 뒤 노드를 삭제하는 함수
void DLinkedList::removeBack() {
    remove(trailer->prev);   // 트레일러 이전 노드 삭제
}

// 특정 노드 v를 삭제하는 함수
void DLinkedList::remove(Node* v) {
    Node* u = v->prev;       // v의 이전 노드
    Node* w = v->next;       // v의 다음 노드
    u->next = w;             // u의 다음을 w로 설정
    w->prev = u;             // w의 이전을 u로 설정
    delete v;                // 노드 v 메모리 해제
}

// 리스트를 앞에서 뒤로 순회하며 출력하는 함수
void DLinkedList::TraverseForward() {
    Node* v = header->next;  // 첫 번째 노드부터 시작
    while(v->next != NULL) { // 다음 노드가 NULL이 아니면 계속
        cout << v->strData << " ";  // 현재 노드의 데이터 출력
        v = v->next;                // 다음 노드로 이동
    }
}

// 리스트를 뒤에서 앞으로 순회하며 출력하는 함수
void DLinkedList::TraverseBackward() {
    Node* v = trailer->prev; // 마지막 노드부터 시작
    while(v->prev != NULL) { // 이전 노드가 NULL이 아니면 계속
        cout << v->strData << " ";  // 현재 노드의 데이터 출력
        v = v->prev;                // 이전 노드로 이동
    }
}


int main (void) {
    DLinkedList* DL = new DLinkedList();

    DL->addFront("3");
    DL->addFront("5");
    DL->addFront("8");
    DL->addFront("10");

    // 3 -> 5 -> 8 -> 10
    DL->TraverseBackward();

    cout << endl;

    // 10 -> 8 -> 5 -> 3
    DL->TraverseForward();

    cout << endl;

    DL->removeBack();
    DL->removeBack();

    // 10 -> 8
    DL->TraverseForward();
    cout << endl;    

    return EXIT_SUCCESS;
}