/* Stack 구현하기 */

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

class MyStack : public BaseArray{
    protected:
        int start; // stack 시작지점 index
        int end; // stack 끝지점 index


    public:
        // constructor (상속받은 거 외에 추가로 선언할 member 변수 초기화)
        MyStack(int capacity): BaseArray(capacity){ 
            start = 0;
            end = 0;
        }
        int length(); // stack 길이 return
        void push(int n); // stack n을 넣음 (불가능한 경우 'cannot push' print)
        int pop(); // stack 시행함 (불가능한 경우 -1 return) 
};

int MyStack::length(){
    return end-start;
}

void MyStack::push(int n){
    int max_size = getCapacity();
    // full size일 때
    if(this->length() == max_size){
        cout << "cannot push" << endl;
    }

    put(end, n);
    end = end+1;
}

int MyStack::pop(){
    // empty일 때
    if(this->length() == 0){
        return -1;
    }
    int data = get(end-1);
    end = end-1;
    return data;
}

