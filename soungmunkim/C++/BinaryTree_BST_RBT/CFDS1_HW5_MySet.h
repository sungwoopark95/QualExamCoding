/*
[RBT or BST 알고리즘 이용해서 Set 구현하기]

<Methods>
1. void Insert
    Set에 data를 값으로 가지는 원소를 삽입,
    주의할 점은 STL set과 마찬가지로 MySet은 중복된 원소 insert 허용 안 됨
2. void Erase
    Set에서 data와 같은 값을 가지는 원소를 제거
3. bool Find
    Set에 data와 같은 값을 가지는 원소가 있는지 검색,
    있으면 true를 반환하고 없으면 false 반환
4. size_t Size
    Set에 들어있는 모든 원소의 개수를 반환
*/

#pragma once

#include "CFDS1_HW5_BST.h"
#include "CFDS1_HW5_RBT.h"

/* MySet based on BST (BST의 subclass로 MySet 구현) */
class MySet : public BST {
    size_t size; // 부호 없는 정수형(즉, 양수만 포함)으로 주로 객체나 배열의 크기, 길이, 용량 등을 표현할 때 사용
public:
    MySet() {
        size = 0;
    } // constructor

    void Insert(int data);
    void Erase(int data);
  
    bool Find(int data);
    size_t Size();
};

// /* MySet based on RBT (RBT의 subclass로 MySet 구현) */
// class MySet : public RBT {
//     size_t size; // 부호 없는 정수형(즉, 양수만 포함)으로 주로 객체나 배열의 크기, 길이, 용량 등을 표현할 때 사용
// public:
//     MySet() {
//         size = 0;
//     } // constructor
    
//     void Insert(int data);
//     void Erase(int data);
  
//     bool Find(int data);
//     size_t Size();
// };
