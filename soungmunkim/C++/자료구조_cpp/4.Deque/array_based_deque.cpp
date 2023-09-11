
/*
 * 배열을 이용하여 원형 덱(Circular Deque) 구현
 */
#include <iostream>
using namespace std;

#define MAX_DEQUE_SIZE 10  // 덱의 최대 크기 설정

class Deque {
private:
    int front;  // 첫 번째 요소 앞의 인덱스
    int rear;   // 마지막 요소 인덱스
    int data[MAX_DEQUE_SIZE];  // 데이터 저장을 위한 배열

public:
    // 생성자: front와 rear를 초기화한다.
    Deque(){
        front = 0;
        rear = 0;
    }
    ~Deque(){}  // 소멸자

    // 덱의 앞에 항목을 추가
    void addFront(int n){
        if(isFull()){
            cout << "Deque Full Error" << endl;
            exit(1);
        }
        data[front] = n;
        front = (front-1+MAX_DEQUE_SIZE)%MAX_DEQUE_SIZE;  // front가 0 이하일 경우, max 인덱스로 순회
    }

    // 덱의 뒤에 항목을 추가 (일반적인 push와 동일)
    void addRear(int n){
        if(isFull()){
            cout << "Deque Full Error" << endl;
            exit(1);
        }
        rear = (rear+1)%MAX_DEQUE_SIZE;  // rear가 최대값을 넘어가면 0번째 인덱스로 순회
        data[rear] = n;
    }

    // 덱의 앞 항목을 제거 (일반적인 pop과 동일)
    int deleteFront(){
        if(isEmpty()){
            cout << "Deque Empty Error" << endl;
            exit(1);
        }
        front = (front+1)%MAX_DEQUE_SIZE;  // front가 최대값을 넘어가면 0번째 인덱스로 순회
        return data[front];
    }

    // 덱의 뒷 항목을 제거
    int deleteRear(){
        if(isEmpty()){
            cout << "Deque Empty Error" << endl;
            exit(1);
        }
        int tmp = data[rear];
        rear = (rear-1+MAX_DEQUE_SIZE)%MAX_DEQUE_SIZE;  // rear가 0 이하일 경우, max 인덱스로 순회
        return tmp;
    }

    // 덱의 앞 항목 조회
    int getFront(){
        if(isEmpty()){
            cout << "Deque Empty Error" << endl;
            exit(1);
        }
        return data[(front+1)%MAX_DEQUE_SIZE];
    }

    // 덱의 뒷 항목 조회
    int getRear(){
        if(isEmpty()){
            cout << "Deque Empty Error" << endl;
            exit(1);
        }
        return data[rear];
    }

    // 덱의 크기 반환
    int size(){
        return front<=rear ? rear-front : (rear+MAX_DEQUE_SIZE)-front;
    }

    // 덱의 내용 출력
    void display(){
        for(int i=front+1; i<=front+size(); i++){
            cout << "[" << data[i%MAX_DEQUE_SIZE] << "]";
        }
        cout << endl;
    }

    // 원형 배열의 front와 rear 정보를 출력하기 위한 메서드
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

    // 덱이 비어 있는지 확인
    bool isEmpty(){
        return front == rear;
    }

    // 덱이 꽉 차 있는지 확인
    bool isFull() {
        return front == (rear+1)%MAX_DEQUE_SIZE;
    }
};

// 메인 함수
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
