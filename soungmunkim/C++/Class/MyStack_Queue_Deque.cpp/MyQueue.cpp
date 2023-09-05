/*
Queue 구현하기 
*/

#include <iostream>

using namespace std;

class BaseArray{
    private:
        int capacity;
        int* mem; // pointer(starting point of the array)

    protected:
        BaseArray(int capacity = 100){ //constructor
            this->capacity = capacity;
            this->mem = new int[capacity];
        }
        ~BaseArray() {delete[] mem;} //destructor
        void put(int index, int val) {mem[index] = val;} // insert a value val at the index position of the array.
        int get(int index) {return mem[index];} // gets the value at the index position of the array
        int getCapacity() {return capacity;} // return size of the array
};

/* 1) Implement a class MyQueue that inherits the BaseArray class and works as a queue.*/
class MyQueue : public BaseArray{
    protected:
        int start; // queue 시작지점 index
        int end; // queue 끝지점 index


    public:
        // constructor (상속받은 거 외에 추가로 선언할 member 변수 초기화)
        MyQueue(int capacity): BaseArray(capacity){ 
            start = 0;
            end = 0;
        }
        int length(); // queue의 길이 return
        void enqueue(int n); // queue에 n을 넣음 (불가능한 경우 'cannot push' print)
        int dequeue(); // dequeue를 시행함 (불가능한 경우 -1 return) 
};



// /*2) Implement a MyDeque class that inherits the MyQueue class and works as a deque.*/
// class MyDeque : protected MyQueue{
//     public:
//         // constructor (상속받은 거 외에 추가로 선언할 member 변수 초기화)
//         MyDeque(int capacity):MyQueue(capacity){ 
//             int start = 0;
//             int end = 0;
//         }
//         int length(); // 길이 return.
//         void push_back(int n); // deque 의 뒤에 원소를 push. 불가능한 경우 ‘cannot push’ print
//         int pop_front(); // deque 의 앞의 원소를 pop. 불가능한 경우 -1 return.
//         void push_front(int n); // deque 의 앞에 원소를 push. 불가능한 경우 ‘cannot push’ print
//         int pop_back(); // deque 의 뒤의 원소를 pop. 불가능한 경우 -1 return.
// };

int MyQueue::length(){
    return end - start;
}

void MyQueue::enqueue(int n){
    int max_size = getCapacity();
    // 만약 뒤에는 다 찬 상태에서 앞에 공간이 비어있을 때 모든 elements 다 앞으로 땡겨주기
    if(end == max_size + 1 && this->length() != max_size){
        for(int i = start; i<end; i++){
            put(i-start, get(i));
        }
    }
    // 만약 queue가 다 찼을 때 
    if(this->length() == max_size){
        cout << "cannot push" << endl;
        return;
    }
    put(end, n);
    end = (end + 1);
}

int MyQueue::dequeue(){
    if(start == end){
        return -1;
    }
    int data = get(start);
    start = start + 1;
    return data;
}