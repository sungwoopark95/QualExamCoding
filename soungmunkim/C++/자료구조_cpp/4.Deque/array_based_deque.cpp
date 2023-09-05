/*
 * array를 이용하여 Circular Deque 구현
 */
#include <iostream>
using namespace std;

#define MAX_DEQUE_SIZE 10

class Deque {
private:
    int front;  // 첫번째 요소 앞의 index
    int rear;   // 마지막 요소 index
    int data[MAX_DEQUE_SIZE];

public:
    Deque(){
        front = 0;
        rear = 0;
    }
    ~Deque(){}

    void addFront(int n){
        if(isFull()){
            cout << "Deque Full Error" << endl;
            exit(1);
        }
        data[front] = n;
        front = (front-1+MAX_DEQUE_SIZE)%MAX_DEQUE_SIZE;    // front가 0 이하로 떨어지는 경우 max index로 순회
    }

    void addRear(int n){    // push
        if(isFull()){
            cout << "Deque Full Error" << endl;
            exit(1);
        }
        rear = (rear+1)%MAX_DEQUE_SIZE;   // rear가 max를 넘어가는 경우 다시 0번째 index로 순회
        data[rear] = n;
    }

    int deleteFront(){  // pop
        if(isEmpty()){
            cout << "Deque Empty Error" << endl;
            exit(1);
        }
        front = (front+1)%MAX_DEQUE_SIZE;   // front가 max를 넘어가는 경우 다시 0번째 index로 순회
        return data[front];
    }

    int deleteRear(){
        if(isEmpty()){
            cout << "Deque Empty Error" << endl;
            exit(1);
        }
        int tmp = data[rear];
        rear = (rear-1+MAX_DEQUE_SIZE)%MAX_DEQUE_SIZE;   // rear가 0 이하로 떨어지는 경우 max index로 순회
        return tmp;
    }

    int getFront(){
        if(isEmpty()){
            cout << "Deque Empty Error" << endl;
            exit(1);
        }
        return data[(front+1)%MAX_DEQUE_SIZE];
    }

    int getRear(){
        if(isEmpty()){
            cout << "Deque Empty Error" << endl;
            exit(1);
        }
        return data[rear];
    }

    int size(){
        return front<=rear ? rear-front : (rear+MAX_DEQUE_SIZE)-front;
    }

    void display(){
        for(int i=front+1; i<=front+size(); i++){
            cout << "[" << data[i%MAX_DEQUE_SIZE] << "]";
        }
        cout << endl;
    }

    // circular array의 front와 rear 정보를 보기위한 메소드
    void displayDetail(){
        cout << "DEQUE :";
        for(int i=front+1; i<=front+size(); i++){
            cout << "[" << data[i%MAX_DEQUE_SIZE] << "]";
        }
        cout << endl;
        cout << "index :";
        for(int i=front+1; i<=front+size(); i++){
            cout << " " << i%MAX_DEQUE_SIZE << " ";
        }
        cout << endl;
        cout << "front : " << front << ", rear : " << rear << endl;
        cout << endl;
    }

    bool isEmpty(){
        return front == rear;
    }
    bool isFull() {
        return front == (rear+1)%MAX_DEQUE_SIZE;
    }
};

int main() {
    Deque deque;

    cout << "===== addRear x3 =====" << endl;
    deque.addRear(1);
    deque.addRear(2);
    deque.addRear(3);
    cout << " size : " << deque.size() << endl;
    deque.displayDetail();

    cout << "===== addFront x2 ======" << endl;
    deque.addFront(5);
    deque.addFront(6);
    cout << " size : " << deque.size() << endl;
    deque.displayDetail();

    cout << "===== deleteRear x1 ======" << endl;
    deque.deleteRear();
    cout << " size : " << deque.size() << endl;
    deque.displayDetail();

    cout << "===== deleteFront x3 ======" << endl;
    deque.deleteFront();
    deque.deleteFront();
    deque.deleteFront();
    cout << " size : " << deque.size() << endl;
    deque.displayDetail();
}