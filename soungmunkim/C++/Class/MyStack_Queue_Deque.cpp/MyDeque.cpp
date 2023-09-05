/* Deque 구현하기 */
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


/*2) Implement a MyDeque class that inherits the MyQueue class and works as a deque.*/
class MyDeque : public BaseArray{
    private:
        int start;
        int end;
    public:
        // constructor (상속받은 거 외에 추가로 선언할 member 변수 초기화)
        MyDeque(int capacity):BaseArray(capacity){ 
            start = 0;
            end = 0;
        }
        int length(); // 길이 return.
        void push_back(int n); // deque 의 뒤에 원소를 push. 불가능한 경우 ‘cannot push’ print
        int pop_back(); // deque 의 뒤의 원소를 pop. 불가능한 경우 -1 return.
        void push_front(int n); // deque 의 앞에 원소를 push. 불가능한 경우 ‘cannot push’ print
        int pop_front(); // deque 의 앞의 원소를 pop. 불가능한 경우 -1 return.
};

int MyDeque::length(){
    return end - start;
}

void MyDeque::push_back(int n){
    int max_size = getCapacity();
    // if full
    if(this->length() == max_size){
        cout << "cannot push" << endl;
    }
     // 뒤에 자리가 없는데 뒤에 넣어야 할 때 앞으로 한 칸씩 땡기기
    if(end == max_size+1 && this->length() != max_size){
        for (int i = start; i < end; i++){
            put(i-start, get(i));
        }
    }
    put(end, n);
    end = end+1;
}

int MyDeque::pop_back(){
    // if empty
    if(this->length() == 0){
        return -1;
    }
    int data = get(end-1);
    end = end - 1;
    return data;
}

void MyDeque::push_front(int n){
    int max_size = getCapacity();
    // if full
    if(this->length() == max_size){
        cout << "cannot push" << endl;
    }
    // 앞에 자리가 없는데 앞에 넣어야 할 때 뒤로 한 칸씩 보내기
    if(start == 0 && this->length() != max_size){
        for(int i=start; i<end; i++){
            put(end-1, get(end-i-1));
        }
    }
    put(end, n);
    end = end+1;
}

int MyDeque::pop_front(){
    // if empty
    if(this->length() == 0){
        return -1;
    }
    int data = get(start);
    start = start+1;
    return data;
}

