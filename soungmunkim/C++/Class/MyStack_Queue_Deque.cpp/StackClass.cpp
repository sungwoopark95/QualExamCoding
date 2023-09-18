/*
1,2,3
1,2,5
1,2,3,5
1,2,5
s1 == s2 ? 0
5
3
5
s1 == s2 ? 1
2
1
Error: No item exists in the list
0
*/

#include <iostream>
#include <stdbool.h>

using namespace std;

class Stack{
    private:
        int* p_list; // 정수형 변수들 가지는 배열
        int size; // 현재 저장된 변수들의 개수
        int MAX_SIZE; // 최대로 저장할 수 있는 p_list 크기
    
    public:
        // constructor (p_list 크기를 MAX_SIZE만큼 동적할당)
        Stack(int _MAX_SIZE = 1000);
        ~Stack(); // deconstructor
        
        /*
        p_list에서 _item과 동일한 값이 있는지 검색 후
        발견시 index 반환
        없으면 -1 반환
        */
        int find_index(int _item);

        /*
        입력 item을 p_list 끝에 저장
        만약 동일한 값이 p_list에 이미 있으면 추가 안 함
        (find_index 통해서 중복 값 찾기)
        size가 MAX_SIZE보다 크면 item 추가 안 함
            Error: out of memory 출력하기
        */
        void push(int _item);

         /*
        p_list 마지막 item 제거한 후 return
        size가 0일때는 item제거 안 함 
            Error: No item exists in the list 출력하기
        */
        int pop();

        void print() const; // Stack 객체 items출력
        int get_size();     // Stack 객체의 크기 출력
        int get_item(int _index); // p_list의 해당 index에 있는 item 값 리턴

        void operator += (const Stack&);
        bool operator == (const Stack&);
};

/*
아래의 기능 추가해야함
1. s1 += s2
    s1에 s1과 s2의 모든 items 합침
    s1 끝에 s2 items 추가
    중복된 값을 가지는 item은 추가되지 않음
2. s1 == s2
    s1과 s2의 size와 item이 모두 동일한 경우 true
    그렇지 않은 경우 false 출력
    item 저장된 순서도 같아야 함
*/


Stack::Stack(int _MAX_SIZE){ //constructor (각 member variable 초기화 만들기)
    this->size = 0;
    this->MAX_SIZE = _MAX_SIZE;
    this->p_list = new int[_MAX_SIZE];
    
}

Stack::~Stack() { // 동적 할당한 p_list 지우기
    delete this->p_list;
}

// 해당 plist size만큼 돌면서 찾는 item이 있으면 
// 해당 Index 내보내기 
int Stack::find_index(int _item){
    for(int i=0; i<this->size; i++){
        if (_item == this->p_list[i]){
            return i;
        }
    }
    return -1;
}

// 해당 item 찾는 index 확인 후 
// 없으면 넣고 개수 늘리기 (index는 -1이니까)
void Stack::push(int _item){
    // full isze일 때
    if(this->size == this->MAX_SIZE){
        cout << "Error: out of memory" << endl;
    }
    if (find_index(_item) != -1){
        return;
    }
    else{
        // item 넣고 개수 늘리기
        this->p_list[size] = _item;
        this->size += 1;
    }
}

int Stack::pop(){
    if(this->size == 0){
        cout << "Error: No item exists in the list" << endl;
    }
    int data;
    data = this->p_list[size-1]; // 마지막 값 데이터에 저장
    this->size -= 1; // size 하나 줄이기 (지우기)

    return data;
}

void Stack::print() const {
    for(int i=0; i<this->size; i++){
        cout << this->p_list[i];
        if(i < this->size - 1){
            cout << ",";
        }
    }
    cout << endl;
}

int Stack::get_size(){
    return this->size;
}

int Stack::get_item(int _index){
    int data;
    data = this->p_list[_index];

    return data;
}

void Stack::operator += (const Stack& s2){
    // s2기준으로 돌면서 item이 s1에 없으면 s1뒤에 추가로 넣기
    for(int i=0; i<s2.size; i++){
        if(find_index(s2.p_list[i]) == -1){
           this->p_list[this->size++] = s2.p_list[i];
        }
    }
    // return *this;
}

 bool Stack::operator==(const Stack& s2){
    // s1기준으로 돌면서 서로 같은 자리에 같은 값이 없으면 false로 리턴하기
    for(int i=0; i<this->size; i++){
        if(this->p_list[i] != s2.p_list[i]){
            return false;
        }
    }
    return true;
 }


int main(){
    Stack s1, s2;
    s1.push(1);
    s1.push(2);
    s1.push(3);

    s2.push(1);
    s2.push(2);
    s2.push(5);

    s1.print();
    s2.print();

    s1 += s2;

    s1.print();
    s2.print();
    cout << "s1 == s2 ? " << (s1 == s2) << endl;

    cout << s1.pop() << endl;
    cout << s1.pop() << endl;
    cout << s2.pop() << endl;
    cout << "s1 == s2 ? " << (s1 == s2) << endl;
    
    cout << s2.pop() << endl;
    cout << s2.pop() << endl;
    cout << s2.pop() << endl;

    return 0;
    
}
