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
    static const int MAX_SIZE = 100;   // 최대 스택 크기
    E* storage;  // 데이터를 저장할 배열
    int maxSize;  // 스택의 최대 크기
    int top;  // 현재 스택의 최상단 위치
    
    // 스택이 가득 찼는지 확인하는 메서드
    bool isFull(void) {
        return top == maxSize - 1;
    }
    
public:
    // 생성자: 스택의 최대 크기를 초기화하고, 스택 초기화
    Stack(int maxSize = MAX_SIZE):maxSize(maxSize) {
        storage = new E[maxSize];
        top = -1;  // 빈 스택을 나타냄
    }
    // 복사 생성자
    Stack(const Stack<E>& copy) {
        maxSize = copy.maxSize;
        top = copy.top;
        
        storage = new E[maxSize];
        
        for(int i = 0; i <= top; i++) {
            storage[i] = copy.storage[i];
        }
    }
    // 소멸자: 동적 할당된 메모리 해제
    ~Stack() {
        delete[] storage;
    }
    // 대입 연산자 오버로딩
    Stack<E>& operator=(const Stack<E>& reference) {
        Stack temp = reference;
        maxSize = temp.maxSize;
        top = temp.top;
        
        std::swap(temp.storage, storage);  // swap을 통해 메모리 교환
        return *this;
    }
    
    // 스택이 비어 있는지 확인하는 메서드
    bool isEmpty(void) {
        return top == -1;
    }
    // 아이템을 스택에 푸시
    void push(E item) {
        if(isFull()) {
            fprintf(stderr, "스택이 가득 찼습니다.\n");
            return;
        }
        
        storage[++top] = item;
        return;
    }
    // 스택의 최상단에서 아이템을 팝 (읽기 및 제거)
    E pop(void) {
        if(isEmpty()) {
            fprintf(stderr, "스택이 비어있습니다.\n");
            exit(EXIT_FAILURE);
        }
        E target = storage[top];
        top--;
        return target;
    }
    // 스택의 최상단 아이템을 읽음 (제거 없이)
    E peek(void) {
        if(isEmpty()) {
            fprintf(stderr, "스택이 비어있습니다.\n");
            exit(EXIT_FAILURE);
        }
        
        return storage[top];
    }
};

#endif /* ArrayBaseStack_h */
