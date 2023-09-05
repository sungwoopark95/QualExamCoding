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

< OutPut >
Size of the set is 6
Size of the set after inserts and erases is 5
Is number '32' exists in the set ? 0
Is number '22' exists in the set ? 0
Is number '100' exists in the set ? 1
*/
#include <iostream>
#include "CFDS1_HW5_MySet.h"

using namespace std;

void MySet::Insert(int data) {
  // 중복 element가 없을 때 insert 해야함
  if (MySet::Find(data) == false){
    BST::Insert(data);
    // RBT::Insert(data);
    
    size++; // 새로운 element 추가 후 size 올리기
  }
}

// set에서 data와 같은 값을 가지는 원소 제거
void MySet::Erase(int data) {
    if (MySet::Find(data) == true){
        // RBT 이용할 때도 같음
        // BST::GetRoot()함수 통해 해당 tree root 값 가져오기
        // root 값 시작으로 data (key) 찾기
        Node * target = Search(GetRoot(), data);
        Delete(target); //BST::Delete로 target node 지우기
        
        size--; // 지웠으니 사이즈 줄이기
    }
}

// Set에 data와 같은 값을 가지는 원소가 있는지 검색
bool MySet::Find(int data) {
    // BST::Search를 통해 root부터 타고 들어가서 해당 data(key)를 찾으면 true
  if (Search(GetRoot(), data) != NULL){
    return true;
  }
  return false;

    /* Under RBT*/ 
    // RBT에서는 -> key로 타고들어가야 함
    // RBT 클래스의 정의를 보면, Node 클래스 내부에는 key라는 변수가 있음
    // 이 변수는 해당 노드의 값을 저장
    // if (Search(GetRoot(), data)->key == data) {
    //   return true;
    // }
    // return false;
}

// Set에 들어있는 모든 원소의 개수를 반환
size_t MySet::Size() {
  return size;
  // size_t를 반환 유형으로 사용하는 것은 집합의 크기(원소의 개수)를 나타내기 때문
  // 여기서 "크기"는 원소의 개수를 의미하며, 이를 나타내기 위해 size_t를 사용하는 것이 일반적임
}