#include <iostream>
using namespace std;

// Stack 클래스 정의
class Stack {
private:
    int* p_list;  // 스택의 항목들을 저장하는 동적 배열의 포인터
    int size;     // 현재 스택의 크기 (저장된 항목의 수)
    int MAX_SIZE; // 스택의 최대 크기
public:
    // 생성자: 스택의 초기 크기를 설정하며, 동적 배열을 할당합니다.
    Stack(int _MAX_SIZE = 100);
    
    // 소멸자: 동적으로 할당된 배열의 메모리를 해제합니다.
    ~Stack();
    
    // 주어진 항목의 인덱스를 찾아 반환합니다. 없으면 -1을 반환합니다.
    int find_index(int _item);
    
    // 스택에 항목을 추가합니다.
    void push(int _item);
    
    // 스택의 최상단 항목을 제거하고 반환합니다.
    int pop();
    
    // 스택의 현재 모든 항목을 출력합니다.
    void print() const;
    
    // 현재 스택의 크기(항목의 수)를 반환합니다.
    int get_size();
    
    // 주어진 인덱스의 항목을 반환합니다.
    int get_item(int _index);
    
    // 두 스택을 병합하는 연산자 오버로딩. 중복 항목은 제거합니다.
    Stack& operator+= (Stack& s2);
    
    // 두 스택이 같은지 비교하는 연산자 오버로딩.
    bool operator== (Stack& s2);
};

// 생성자 함수
// 주어진 최대 크기(_MAX_SIZE)로 스택을 초기화하며 기본값은 100입니다.
Stack::Stack(int _MAX_SIZE) {
    this->size = 0;                  // 초기 스택 크기를 0으로 설정
    this->MAX_SIZE = _MAX_SIZE;     // 최대 크기를 설정값으로 설정
    this->p_list = new int[_MAX_SIZE]; // 최대 크기만큼의 정수 배열을 동적 할당
}

// 소멸자 함수
// 스택에서 사용된 메모리를 해제하기 위해 호출됩니다.
Stack::~Stack() {
    delete[] this->p_list; // 동적으로 할당된 배열의 메모리를 해제
}

// 특정 항목의 인덱스를 찾는 함수
// 스택에서 _item 항목의 위치(인덱스)를 찾아서 반환합니다. 항목이 없으면 -1을 반환
int Stack::find_index(int _item) {
    for (int i=0;i<this->size;i++) {
        if (this->p_list[i] == _item) {
            return i; // 항목을 찾은 경우 그 위치를 반환
        }
    }
    return -1; // 항목을 찾지 못한 경우 -1 반환
}

// 항목을 스택에 추가하는 함수
void Stack::push(int _item) {
    // 스택이 꽉 찼을 때의 처리
    if (this->size == MAX_SIZE) {
        cout << "Stack Overflow." << endl; // 에러 메시지 출력
        exit(1); // 프로그램 종료
    }
    // 항목을 스택의 맨 위에 추가
    this->p_list[this->size++] = _item; 
}

// 스택의 최상단 항목을 제거하고 반환하는 함수
int Stack::pop() {
    // 스택이 비어있는 경우 처리
    if (this->size == 0) {
        cout << "Error: No item exists in the list" << endl; // 에러 메시지 출력
        exit(1); // 프로그램 종료
    }
    int temp = this->p_list[--this->size]; // 스택의 최상단 항목 값을 temp에 저장
    return temp; // temp 값을 반환
}

// 현재 스택에 저장된 항목 수를 반환하는 함수
int Stack::get_size() {
    return this->size; // 현재 크기 반환
}

// 특정 인덱스의 항목을 반환하는 함수
int Stack::get_item(int _index) {
    return this->p_list[_index]; // 주어진 인덱스의 항목 반환
}

// 스택의 모든 항목을 출력하는 함수
void Stack::print() const {
    bool is_start = true; // 첫 항목인지를 판단하기 위한 변수
    for (int i=0;i<this->size;i++) {
        if (!is_start) {
            cout << ", "; // 첫 항목이 아닌 경우 쉼표를 출력
        }
        cout << this->p_list[i]; // 항목 출력
        is_start = false; // 첫 항목이 아니므로 false로 설정
    }
    cout << endl; // 줄 바꿈
}

// += 연산자 오버로딩 함수
// 주어진 스택 s2의 항목들을 현재 스택에 추가합니다. 
// 이미 동일한 항목이 현재 스택에 있다면 추가하지 않습니다.
Stack& Stack::operator+= (Stack& s2) {
    for (int i=0; i<s2.get_size(); i++) { // s2의 모든 항목들을 순회
        int item = s2.get_item(i);       // s2의 i번째 항목 값을 가져옴

        // 현재 스택에 해당 항목이 존재하지 않는 경우
        if (this->find_index(item) == -1) {
            this->push(item);             // 현재 스택에 해당 항목 추가
        }
    }
    return *this; // 현재 스택의 참조를 반환 (메소드 체이닝을 가능하게 함)
}

// == 연산자 오버로딩 함수
// 현재 스택과 주어진 스택 s2가 동일한 항목들을 같은 순서로 가지고 있는지 확인
bool Stack::operator== (Stack& s2) {
    // 두 스택의 크기가 다른 경우 바로 false 반환
    if (this->size != s2.get_size()) {
        return false;
    }

    for (int i=0; i<this->size; i++) {  // 현재 스택의 모든 항목들을 순회
        // 현재 스택의 i번째 항목과 s2의 i번째 항목이 다른 경우
        if (this->p_list[i] != s2.get_item(i)) {
            return false; // 두 스택은 동일하지 않음
        }
    }
    return true; // 모든 항목들이 동일하므로 두 스택은 동일
}


int main() {
    Stack s1, s2, s3;

    s1.push(1);
    s1.push(2);
    s1.push(3);

    s2.push(1);
    s2.push(2);
    s2.push(5);

    s1.print();  // 출력: 1, 2, 3
    s2.print();  // 출력: 1, 2, 5

    s1 += s2;
    s1.print();  // 출력: 1, 2, 3, 5
    s2.print();  // 출력: 1, 2, 5

    cout << "s1 == s2 ? " << (s1 == s2) << endl;  // 출력: s1 == s2 ? 0

    cout << s1.pop() << endl;  // 출력: 5
    cout << s1.pop() << endl;  // 출력: 3
    cout << s2.pop() << endl;  // 출력: 5
    cout << "s1 == s2 ? " << (s1 == s2) << endl;  // 출력: s1 == s2 ? 1

    cout << s2.pop() << endl;  // 출력: 2
    cout << s2.pop() << endl;  // 출력: 1
    cout << s2.pop() << endl;  // 에러: No item exists in the list (프로그램 종료)
    
    return 0;
}