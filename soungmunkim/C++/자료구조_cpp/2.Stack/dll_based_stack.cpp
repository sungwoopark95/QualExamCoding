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
    class Node {
        friend class Stack;
    private:
        E data;
        Node* rightLink;
        Node* leftLink;
        
    public:
        Node(void) {
            rightLink = NULL;
        }
        Node(E item, Node* previous, Node* next): data(item), rightLink(next), leftLink(previous) { }
    };
    
    Node* head;  // top. 
    Node* tail;  // bottom.
    
public:
    Stack() {
        head = NULL;
        tail = NULL;
    }
    Stack(const Stack<E>& copy) {
        head = NULL;
        tail = NULL;
        
        Node* search = copy.tail;
        
        while(search != NULL) {
            this->push(search->data);
            search = search->leftLink;
        }
    }
    ~Stack() {
        while(head != NULL) {
            Node* temp = head;
            head = temp->rightLink;
            delete temp;
        }
    }
    Stack<E>& operator=(const Stack<E>& reference) {
        Stack<E> temp = reference;
        std::swap(temp.head, head);
        std::swap(temp.tail, tail);
        return *this;
    }
    
    bool isEmpty(void) {
        return (head == NULL);
    }
    void push(E item) {
        head = new Node(item, NULL, head);
        
        if(tail == NULL) {
            tail = head;
        } else {
            head->rightLink->leftLink = head;
        }
    }
    E pop(void) {
        if(isEmpty()) {
            fprintf(stderr, "스택이 비어있습니다.\n");
            exit(EXIT_FAILURE);
        }
        
        Node* target = head;
        E poppedItem = target->data;
        
        head = target->rightLink;
        
        if(head == NULL) {
            tail = NULL;
        }
        
        delete target;
        return poppedItem;
        
    }
    E peek(void) {
        if(isEmpty()) {
            fprintf(stderr, "스택이 비어있습니다.\n");
            exit(EXIT_FAILURE);
        }
        
        return head->data;
    }
};

#endif /* ListBaseStack_h */