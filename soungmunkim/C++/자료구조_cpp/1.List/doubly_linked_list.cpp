#include <string>
#include <iostream>

using namespace std;

class Node {
    string strData;
    Node* prev;
    Node* next;
    friend class DLinkedList;
};

class DLinkedList {
    public:
        DLinkedList();  // create empty list
        ~DLinkedList();
        bool isEmpty() const;
        const string& getFront() const;
        const string& getBack() const;
        void addFront(const string& e);
        void addBack(const string& e);
        void removeFront();
        void removeBack();
        void TraverseForward();
        void TraverseBackward();
    private:
        Node* header;  // 리스트 시작점
        Node* trailer;  // 리스트 끝점
    protected: // local utilities
        void add(Node* v, const string& e);
        void remove(Node* v);
};

DLinkedList::DLinkedList() {
    header = new Node;
    trailer = new Node;

    // Header and Trailer are sentinel Nodes.
    // No data is included at those nodes.
    header->next = trailer;
    trailer->prev = header;
}

DLinkedList::~DLinkedList() {
    while(!isEmpty()) removeFront();
    delete header;
    delete trailer;
}

bool DLinkedList::isEmpty() const {
    if (header->next == trailer);
}

const string& DLinkedList::getFront() const {
    return header->next->strData;
}

const string& DLinkedList::getBack() const {
    return trailer->prev->strData;
}
void DLinkedList::addFront(const string& e) {
    add(header, e);
}

void DLinkedList::addBack(const string& e) {
    add(trailer->prev, e);
}


// Insert new Node after v
void DLinkedList::add(Node* v, const string& e) {
    Node* u = new Node;
    u->strData = e;
    u->next = v->next;
    u->prev = v;

    v->next->prev = u;
    v->next = u;
}


void DLinkedList::removeFront() {
    remove(header->next);
}

void DLinkedList::removeBack() {
    remove(trailer->prev);
}

void DLinkedList::remove(Node* v) {
    Node* u = v->prev;
    Node* w = v->next;
    u->next = w;
    w->prev = u;
    delete v;
}

void DLinkedList::TraverseForward() {
    Node* v = header->next;
    while(v->next != NULL) {
        cout << v->strData << " ";
        v = v->next;
    }
}

void DLinkedList::TraverseBackward() {
    Node* v = trailer->prev;
    while(v->prev != NULL) {
        cout << v->strData << " ";
        v = v->prev;
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