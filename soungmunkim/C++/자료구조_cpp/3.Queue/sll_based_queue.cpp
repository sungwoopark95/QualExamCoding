#include <stdlib.h>
#include <iostream>

using namespace std;
 
// 연결 리스트를 위한 노드 구조체
struct QNode {
    int data;
    QNode* next;
    // 생성자: 데이터와 다음 노드 포인터를 초기화한다.
    QNode(int d)
    {
        data = d;
        next = NULL;
    }
};
 
// 큐 구조체
struct Queue {
    QNode *front, *rear; // 큐의 앞과 뒤를 나타내는 포인터
    // 생성자: front와 rear를 NULL로 초기화한다.
    Queue() { front = rear = NULL; }
 
    // 큐에 항목을 추가하는 함수
    void enQueue(int x)
    {
        // 새 연결 리스트 노드를 생성한다.
        QNode* temp = new QNode(x);
 
        // 큐가 비어 있으면 새 노드가 front와 rear가 된다.
        if (rear == NULL) {
            front = rear = temp;
            return;
        }
 
        // 큐의 끝에 새 노드를 추가하고 rear를 변경한다.
        rear->next = temp;
        rear = temp;
    }
 
    // 큐에서 항목을 제거하는 함수
    void deQueue()
    {
        // 큐가 비어 있으면 NULL을 반환한다.
        if (front == NULL)
            return;
 
        // 이전 front를 저장하고 front를 한 노드 앞으로 이동한다.
        QNode* temp = front;
        front = front->next;
 
        // front가 NULL이 되면 rear도 NULL로 변경한다.
        if (front == NULL)
            rear = NULL;
 
        delete (temp);
    }
};
 
// 드라이버 코드
int main()
{
    Queue q;
    q.enQueue(10);
    q.enQueue(20);
    q.deQueue();
    q.deQueue();
    q.enQueue(30);
    q.enQueue(40);
    q.enQueue(50);
    q.deQueue();
    cout << "Queue Front : " << ((q.front != NULL) ? (q.front)->data : -1)<< endl;
    cout << "Queue Rear : " << ((q.rear != NULL) ? (q.rear)->data : -1);
}
