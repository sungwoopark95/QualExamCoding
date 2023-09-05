//
//  ArrayBaseStack.hpp
//  DataStructure
//
//  Created by sogoagain on 2017. 1. 21..
//

#ifndef ArrayBaseStack_h
#define ArrayBaseStack_h

#include <algorithm>

using namespace std;

template <typename E>
class Stack {
private:
    static const int MAX_SIZE = 100;
    E* storage;  //데이터 저장할 array
    int maxSize;
    int top;
    
    bool isFull(void) {
        return top == maxSize - 1;
    }
    
public:
    Stack(int maxSize = MAX_SIZE):maxSize(maxSize) {
        storage = new E[maxSize];
        top = -1;
    }
    Stack(const Stack<E>& copy) {
        maxSize = copy.maxSize;
        top = copy.top;
        
        storage = new E[maxSize];
        
        for(int i = 0; i <= top; i++) {
            storage[i] = copy.storage[i];
        }
    }
    ~Stack() {
        delete[] storage;
    }
    Stack<E>& operator=(const Stack<E>& reference) {
        Stack temp = reference;
        maxSize = temp.maxSize;
        top = temp.top;
        
        std::swap(temp.storage, storage);
        return *this;
    }
    
    bool isEmpty(void) {
        return top == -1;
    }
    void push(E item) {
        if(isFull()) {
            fprintf(stderr, "스택이 가득 찼습니다.\n");
            return;
        }
        
        storage[++top] = item;
        return;
    }
    // top의 데이터를 읽기 및 제거.
    E pop(void) {
        if(isEmpty()) {
            fprintf(stderr, "스택이 비어있습니다.\n");
            exit(EXIT_FAILURE);
        }
        E target = storage[top];
        top--;
        return target;
    }
    // top위치의 데이터를 읽음.
    E peek(void) {
        if(isEmpty()) {
            fprintf(stderr, "스택이 비어있습니다.\n");
            exit(EXIT_FAILURE);
        }
        
        return storage[top];
    }
};

#endif /* ArrayBaseStack_h */