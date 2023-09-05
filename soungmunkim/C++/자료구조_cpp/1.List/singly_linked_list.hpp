#ifndef Singly_Linked_List_hpp
#define SinglyLinkedList_hpp

#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;


// node에 들어가는 데이터의 타입(T)을 자유롭게 지정할 수 있는 버전
template <typename T>
class LinkedList {
private:
    class Node {
        friend class LinkedList;
    private:
        T data;
        Node* link; //next node
        
    public:
        Node(void) {  //constructor : 인자 없을 경우
            link = NULL;
        }
        Node(T item, Node* next_node) {  //constructor : 인자 받을 경우
            data = item;
            link = next_node;
        }
    };
    
    Node* head;
    Node* current;
    Node* previous;
    int size;
    int (*compare)(const void*, const void*);
    
    bool verifyReferenceScope(int index);
    bool isPossibleToAdd(int index);
    void addToSort(T item);
    Node* getNodeAt(int index);
    

public:
    LinkedList();
    LinkedList(const LinkedList<T>& copy);
    ~LinkedList();
    LinkedList<T>& operator=(const LinkedList<T>& reference);
    
    bool isEmpty(void);
    void add(T item);
    void add(int index, T item);
    void set(int index, T item);
    T remove(int index);
    T remove(void);
    T getItem(int index);
    T getItem(void);
    int getSize(void);
    int indexOf(T item);
    int lastIndexOf(T item);
    
    bool hasNext(void);
    T first(void);
    T next(void);
    void sort(int (*compare)(const void *, const void *));
};

// index가 linkedlist의 범위 내에 있는지 확인
template <typename T>
bool LinkedList<T>::verifyReferenceScope(int index) {
    return (index >= 0) && (index < size);
}

// 해당 index가 추가 가능한 숫자인지
template <typename T>
bool LinkedList<T>::isPossibleToAdd(int index) {
    return ((index >= 0) && (index <= size));
}

// 'compare' 기준에 따라 node 삽입. linkedlist가 compare기준에 따라 이미 정렬되어 있을경우 사용.
template <typename T>
void LinkedList<T>::addToSort(T item) {
    if(compare == NULL) {
        fprintf(stderr, "비교 함수가 등록되지 않아 정렬을 중단합니다.\n");
        exit(EXIT_FAILURE);
    }
    
    Node* search = head;
    while((search->link != NULL) && (compare((void*)&item, (void*)&(search->link->data)) >= 0)) {
        search = search->link;
    }
    search->link = new Node(item, search->link);
    size++;
    return;
}

// linkedlist에서 index로 node return. index는 0부터 시작. head(root) node는 index -1.
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::getNodeAt(int index)  {
    if(index == -1) {
        return head;
    }
    
    if(!verifyReferenceScope(index)) {
        fprintf(stderr, "index[%d] 노드를 참조할 수 없습니다.\n",index);
        exit(EXIT_FAILURE);
    }
    
    Node* search = head;
    for(int i = 0; i <= index; i++) {
        search = search->link;
    }
    return search;
}

// constructor : 인수 없는 경우
template <typename T>
LinkedList<T>::LinkedList() {
    head = new Node();  // 더미노드 추가
    
    current = head;
    previous = NULL;
    size = 0;
    compare = NULL;
}

// constructor : 기존 linkedlist 복사하여 생성.
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& copy) {
    Node* tail; //새로 만들 linkedlist의 마지막 노드
    Node* search;
    
    head = new Node();  // 더미노드 추가
    tail = head;
    search = copy.head;
    size = 0;
    
    while(search->link != NULL) {
        search = search->link;
        tail->link = new Node(search->data, NULL);
        tail = tail->link;
        size++;
    }
    
    current = head;
    previous = NULL;
    compare = NULL;
}

// destructor
template <typename T>
LinkedList<T>::~LinkedList() {
    while(head->link != NULL) {
        Node* temp = head->link;
        head->link = temp->link;
        delete temp;
    }
    delete head;
}

// linkedlist 대입
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& reference) {
    LinkedList<T> temp = reference;
    size = temp.getSize();
    std::swap(temp.head, head);
    return *this;
}

// 리스트가 비어있는지 확인
template <typename T>
bool LinkedList<T>::isEmpty(void) {
    return (head->link == NULL);
}

// index의 위치에 노드 삽입
template <typename T>
void LinkedList<T>::add(int index, T item) {
    if(!isPossibleToAdd(index)) {
        fprintf(stderr, "index[%d]에 저장이 불가능합니다.\n", index);
        return;
    }
    
    Node* search = getNodeAt(index - 1);
    search->link = new Node(item, search->link);
    size++;
    return;
}

// linkedlist의 맨 앞에 노드 삽입
template <typename T>
void LinkedList<T>::add(T item) {
    head->link = new Node(item, head->link);
    size++;
    return;
}

// index위치의 노드 값 변경
template <typename T>
void LinkedList<T>::set(int index, T item) {
    if(!verifyReferenceScope(index)) {
        fprintf(stderr, "index[%d]의 값을 변경할 수 없습니다.\n", index);
        return;
    }
    
    Node* search = getNodeAt(index);
    search->data = item;
    return;
}

// index위치의 노드 제거, 제거 후 삭제된 값 return.
template <typename T>
T LinkedList<T>::remove(int index) {
    if(!verifyReferenceScope(index)) {
        fprintf(stderr, "index[%d]의 값을 삭제할 수 없습니다.\n", index);
        exit(EXIT_FAILURE);
    }
    
    Node* search = getNodeAt(index - 1);  // 삭제할 노드의 이전 노드
    Node* target = search->link;          // 삭제할 노드
    T deletedData;
    
    deletedData = target->data;
    search->link = target->link;   // 삭제할 노드의 이전노드와 다음노드 연결.
    
    if(target == current) {
        current = search;
    }
    
    delete target;
    
    size--;
    return deletedData;
}

// linkedlist의 current node 삭제. 제거 후 삭제된 값 return
template <typename T>
T LinkedList<T>::remove(void) {
    if(current == head) {
        fprintf(stderr, "first(), next()를 통해 참조 위치를 설정하세요");
        exit(EXIT_FAILURE);
    }
    
    T target;
    target = current->data;
    previous->link = current->link;
    
    delete current;
    current = previous;
    
    size--;
    return target;
}

// index위치의 값 return
template <typename T>
T LinkedList<T>::getItem(int index) {
    Node* search = getNodeAt(index);
    return search->data;
}

// linkedlist의 current node 값 return
template <typename T>
T LinkedList<T>::getItem(void) {
    return current->data;
}

// linkedlist의 size
template <typename T>
int LinkedList<T>::getSize(void) {
    return size;
}

// item값을 가진 처음 node의 index return
template <typename T>
int LinkedList<T>::indexOf(T item) {
    int index = 0;
    Node* search = head;
    
    while(search->link != NULL) {
        search = search->link;
        if(search->data == item) {
            return index;
        }
        index++;
    }
    return -1;
}

// item값을 가진 마지막 node의 index return
template <typename T>
int LinkedList<T>::lastIndexOf(T item) {
    int index = 0;
    int result = -1;
    Node* search = head;
    
    while(search->link != NULL) {
        search = search->link;
        if(search->data == item) {
            result = index;
        }
        index++;
    }
    
    return result;
}

// current node의 다음 노드 유무 체크
template <typename T>
bool LinkedList<T>::hasNext(void) {
    return (current->link != NULL);
}

// current Node 진행. 다음노드가 current node가 됨.
template <typename T>
T LinkedList<T>::next(void) {
    if(!hasNext()) {
        fprintf(stderr, "참조할 다음 데이터가 없습니다.\n");
        exit(EXIT_FAILURE);
    }
    
    previous = current;
    current = current->link;
    
    return current->data;
}

// 처음 node data 가져오기
template <typename T>
T LinkedList<T>::first(void) {
    if(isEmpty()) {
        fprintf(stderr, "저장된 데이터가 없습니다.\n");
        exit(EXIT_FAILURE);
    }
    
    previous = head;
    current = head->link;
    
    return current->data;
}

// linkedlist 정렬.
template <typename T>
void LinkedList<T>::sort(int (*compare)(const void *, const void *)) {
    // 정렬된 list 임시저장할 리스트
    LinkedList temp;
    //    this->compare = compare;
    temp.compare = compare;
    
    Node* search = head;
    // 정렬기준에 맞추어, temp list에 node하나씩 삽입. 
    while(search->link != NULL) {
        search = search->link;
        temp.addToSort(search->data);
    }
    
    std::swap(temp.head, head);
}

#endif /* SinglyLinkedList_hpp */