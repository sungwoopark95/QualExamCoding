#include <iostream>
using namespace std;

// 노드 클래스 정의
class Node {
public:
    char data;         // 노드에 저장될 데이터
    Node* next;        // 노드의 다음 포인터
    // 생성자: 초기 데이터와 다음 노드의 포인터를 받음. 다음 노드는 기본적으로 nullptr
    Node(char d, Node* n = nullptr) : data(d), next(n) {}  
};

class LinkedList {
private:
    Node* head;  // 연결 리스트의 첫 번째 노드를 가리키는 포인터

public:
    LinkedList();  // 기본 생성자 선언
    // head 노드를 반환하는 getter 함수
    Node* getHead() const { return head; }
    // 함수 선언들...
    void append(char data);
    void deleteNode(char data);
    void insert(int index, char data);
    void sort();
    void display();
    int length();
    void insertAtPosition(int position, char data);
    void reverseDisplay(Node* start);
    void reverse();
    void clear();
};

// 기본 생성자 정의: 연결 리스트의 첫 번째 노드를 nullptr로 초기화
LinkedList::LinkedList() : head(nullptr) {}

// 데이터를 받아 새 노드를 연결 리스트의 끝에 추가하는 함수
void LinkedList::append(char data) {
    if (head == nullptr) {          // 리스트가 비어 있으면
        head = new Node(data);      // 새 노드를 생성하고 head로 지정
        return;
    }
    Node* temp = head;
    // 마지막 노드를 찾기 위한 반복문
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = new Node(data);  // 마지막 노드 다음에 새 노드를 연결
}

// 데이터와 일치하는 첫 번째 노드를 연결 리스트에서 삭제하는 함수
void LinkedList::deleteNode(char data) {
    if (head == nullptr) return;     // 리스트가 비어 있으면 종료
    if (head->data == data) {        // 첫 번째 노드가 일치하면
        Node* temp = head;
        head = head->next;          // 두 번째 노드를 첫 번째 노드로 지정
        delete temp;                // 원래 첫 번째 노드 삭제
        return;
    }
    Node* temp = head;
    // 삭제할 노드를 찾기 위한 반복문
    while (temp->next != nullptr && temp->next->data != data) {
        temp = temp->next;
    }
    if (temp->next == nullptr) return; // 노드를 찾지 못하면 종료
    Node* toDelete = temp->next;
    temp->next = temp->next->next;   // 삭제할 노드를 리스트에서 제외
    delete toDelete;                 // 노드 메모리 해제
}

// 지정된 위치에 새 노드를 연결 리스트에 삽입하는 함수
void LinkedList::insert(int index, char data) {
    if (index == 0) {                // 맨 앞에 삽입하는 경우
        head = new Node(data, head); // 새 노드를 생성하고 원래 head를 next로 지정
        return;
    }
    Node* temp = head;
    // 삽입할 위치 바로 앞의 노드를 찾기 위한 반복문
    for (int i = 0; i < index - 1 && temp != nullptr; i++) {
        temp = temp->next;
    }
    if (temp == nullptr) return;     // 유효하지 않은 index면 종료
    temp->next = new Node(data, temp->next);  // 새 노드를 생성하고 원래 next를 그 노드의 next로 지정
}


// 연결 리스트를 오름차순으로 정렬하는 함수
void LinkedList::sort() {
    // 리스트가 비어 있거나 노드가 하나만 있으면 종료
    if (head == nullptr || head->next == nullptr) return;

    Node* i = head;
    // 외부 루프는 현재 정렬을 위한 노드를 가리킵니다.
    while (i != nullptr) {
        Node* j = i->next;
        // 내부 루프는 현재 노드보다 뒤에 있는 노드들과 비교를 위해 사용됩니다.
        while (j != nullptr) {
            if (i->data > j->data) {   // 두 노드의 데이터를 비교하여 필요하면 교환
                swap(i->data, j->data);
            }
            j = j->next;  // 다음 노드로 이동
        }
        i = i->next;  // 다음 노드로 이동
    }
}

// 연결 리스트의 모든 노드를 화면에 출력하는 함수
void LinkedList::display() {
    Node* temp = head;
    // 모든 노드를 순회하며 데이터를 출력
    while (temp != nullptr) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

// 연결 리스트의 노드 개수를 반환하는 함수
int LinkedList::length() {
    int count = 0;
    Node* temp = head;
    // 모든 노드를 순회하며 카운트 증가
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

// 지정된 위치에 노드를 삽입하는 함수
void LinkedList::insertAtPosition(int position, char data) {
    // 유효하지 않은 위치를 입력받았을 때의 처리
    if (position < 0 || position > length()) {
        cout << "Invalid position!" << endl;
        return;
    }
    // 맨 앞에 삽입하는 경우
    if (position == 0) {
        Node* newNode = new Node(data, head);
        head = newNode;
        return;
    }
    Node* temp = head;
    // 삽입할 위치 바로 앞의 노드를 찾음
    for (int i = 1; i < position; i++) {
        temp = temp->next;
    }
    // 새 노드를 생성하고 리스트에 삽입
    Node* newNode = new Node(data, temp->next);
    temp->next = newNode;
}

// 연결 리스트의 노드를 역순으로 화면에 출력하는 재귀 함수
void LinkedList::reverseDisplay(Node* start) {
    if (start == nullptr) return;   // 기저 조건
    reverseDisplay(start->next);    // 재귀 호출
    cout << start->data << " ";
}

// 연결 리스트의 노드 순서를 역순으로 바꾸는 함수
void LinkedList::reverse() {
    Node* prev = nullptr;
    Node* current = head;
    Node* next = nullptr;

    // 노드의 next 포인터를 변경하여 순서를 반전
    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;  // head 업데이트
}

// 연결 리스트의 모든 노드를 삭제하고 메모리를 해제하는 함수
void LinkedList::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    LinkedList list;  // 연결 리스트 객체 생성
    list.append('A');
    list.append('B');
    list.append('C');
    list.display();

    list.insert(1, 'X');
    list.display();

    list.deleteNode('B');
    list.display();

    list.sort();
    list.display();

    cout << "Length: " << list.length() << endl;

    cout << "Reverse display: ";
    list.reverseDisplay(list.getHead());
    cout << endl;

    list.reverse();
    list.display();

    list.clear();  // 리스트의 모든 노드 삭제
    list.display();

    return 0;
}
