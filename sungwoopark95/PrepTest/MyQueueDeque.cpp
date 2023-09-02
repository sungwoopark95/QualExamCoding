#include <iostream>
using namespace std;

class BaseArray { 
private: 
    int capacity; 
    int* mem; 

protected: 
    BaseArray(int capacity = 100) {      // constructor 
        this->capacity = capacity;   
        mem = new int[capacity]; 
    } 
    
    ~BaseArray() { delete[] mem; }      // destructor 
    
    void put(int index, int val) { 
        mem[index] = val; 
    } 
    
    int get(int index) { 
        return mem[index]; 
    } 
    
    int getCapacity() { 
        return capacity; 
    } 
};

// BaseArray 클래스를 상속받는 MyQueue 클래스 정의
class MyQueue : public BaseArray {
protected:
    int start; // 큐의 시작지점을 가리키는 인덱스
    int end;   // 큐의 끝지점을 가리키는 인덱스

public:
    // 생성자: capacity를 인자로 받아 BaseArray의 생성자에 전달하고, start와 end를 0으로 초기화
    MyQueue(int capacity) : BaseArray(capacity) { 
        start = 0; end = 0; 
    }
    
    int length(); // 큐의 길이를 반환하는 함수
    void enqueue(int n); // 큐에 n 값을 추가하는 함수. 추가가 불가능할 경우 "cannot push"를 출력
    int dequeue(); // 큐에서 값을 제거하고 그 값을 반환하는 함수. 제거할 값이 없을 경우 -1을 반환
};

// 큐의 길이를 반환하는 함수: end와 start의 차이를 반환
int MyQueue::length() {
    return (end - start);
}

// 큐에 n 값을 추가하는 함수
void MyQueue::enqueue(int n) {
    // 현재 큐의 길이가 최대 용량보다 작은 경우에만 추가 가능
    if (this->length() < this->getCapacity()) {
        // 큐의 시작지점이 0보다 큰 경우 (이전에 dequeue 연산이 수행된 경우)
        if (start > 0) {
            // 앞에 빈 자리가 있으므로 뒤에 있는 항목들을 앞으로 옮김
            for (int i=start;i<end;i++) {
                this->put(i-start, this->get(i));
            }
            end -= start; // end 위치 조정
            start = 0;    // start 위치 초기화
        }
        // 값을 큐의 끝에 추가
        this->put(end, n);
        end++; // end 위치 증가
    } else {
        // 큐가 가득 찬 경우 "cannot push" 출력
        cout << "cannot push" << endl;
    }
}

// 큐에서 값을 제거하고 그 값을 반환하는 함수
int MyQueue::dequeue() {
    int val = -1; // 반환할 값 초기화
    // 큐에 값이 있는 경우
    if (this->length() > 0) {
        val = this->get(start); // 시작지점의 값을 가져옴
        start++; // 시작지점 증가
    }
    return val; // 값을 반환
}

// MyQueue를 상속받는 MyDeque 클래스 정의
class MyDeque : protected MyQueue {
public:
    // 생성자: capacity를 인자로 받아 MyQueue의 생성자에 전달하고, start와 end를 0으로 초기화
    MyDeque(int capacity) : MyQueue(capacity) { 
        int start = 0; int end = 0; 
    }

    int length(); // 덱의 길이를 반환하는 함수
    void push_back(int n); // 덱의 뒤쪽에 원소를 추가하는 함수. 추가가 불가능할 경우 "cannot push"를 출력
    int pop_front(); // 덱의 앞쪽에서 원소를 제거하고 그 값을 반환하는 함수. 제거할 값이 없을 경우 -1을 반환
    void push_front(int n); // 덱의 앞쪽에 원소를 추가하는 함수. 추가가 불가능할 경우 "cannot push"를 출력
    int pop_back(); // 덱의 뒤쪽에서 원소를 제거하고 그 값을 반환하는 함수. 제거할 값이 없을 경우 -1을 반환
};

// 덱의 길이를 반환하는 함수: end와 start의 차이를 반환
int MyDeque::length() {
    return end - start;
}

// 덱의 뒤쪽에 원소를 추가하는 함수
void MyDeque::push_back(int n) {
    // 덱의 현재 길이와 end의 위치를 확인하여 추가 가능한지 확인
    if (this->length() < this->getCapacity() && end < this->getCapacity()) {
        this->put(end, n); // 원소를 덱의 뒤쪽에 추가
        end++; // end 위치 증가
    } else {
        // 덱이 가득 찬 경우 "cannot push" 출력
        cout << "cannot push" << endl;
    }
}

// 덱의 앞쪽에 원소를 추가하는 함수
void MyDeque::push_front(int n) {
    // 덱의 현재 길이를 확인하여 추가 가능한지 확인
    if (this->length() < this->getCapacity()) {
        if (start > 0) {
            // 앞에 빈 자리가 있는 경우
            this->put(start-1, n);
            start--; // start 위치 감소
        } else {
            // 앞에 빈 자리가 없는 경우
            // 먼저 이미 있는 원소들을 뒤로 한 칸씩 옮김
            for (int i=end-1;i>=0;i--) {
                this->put(i+1, this->get(i));
            }
            end++; // end 위치 증가
            // 원소를 덱의 앞쪽에 추가
            this->put(0, n);
        }
    } else {
        // 덱이 가득 찬 경우 "cannot push" 출력
        cout << "cannot push" << endl;
    }
}

// 덱의 뒤쪽에서 원소를 제거하고 그 값을 반환하는 함수
int MyDeque::pop_back() {
    int val = -1; // 반환할 값 초기화
    // 덱에 값이 있는 경우
    if (this->length() > 0) {
        val = this->get(end-1); // 덱의 뒤쪽에서 값을 가져옴
        end--; // end 위치 감소
    }
    return val; // 값을 반환
}

// 덱의 앞쪽에서 원소를 제거하고 그 값을 반환하는 함수
int MyDeque::pop_front() {
    int val = -1; // 반환할 값 초기화
    // 덱에 값이 있는 경우
    if (this->length() > 0) {
        val = this->get(start); // 덱의 앞쪽에서 값을 가져옴
        start++; // start 위치 증가
    }
    return val; // 값을 반환
}


#define MAXSIZE 5

int main() {
    MyQueue q = MyQueue(MAXSIZE);

    cout << q.length() << endl;

    q.enqueue(10);
    q.enqueue(1);
    q.enqueue(3);
    q.enqueue(2);
    q.enqueue(6);
    q.enqueue(8);

    cout << q.dequeue() << " " << q.length() << endl;
    cout << q.dequeue() << " " << q.length() << endl;
    cout << q.dequeue() << " " << q.length() << endl;
    cout << q.dequeue() << " " << q.length() << endl;
    cout << q.dequeue() << " " << q.length() << endl;
    cout << q.dequeue() << " " << q.length() << endl;

    return 0;
}
