#include <stdlib.h>
#include <iostream>

using namespace std;
 
// 큐를 표현하기 위한 구조체
class Queue {
public:
    int front, rear, size;
    unsigned capacity;
    int* array;
};
 
// 주어진 용량으로 큐를 생성하는 함수.
// 큐의 크기를 0으로 초기화한다.
Queue* createQueue(unsigned capacity)
{
    Queue* queue = new Queue();
    queue->capacity = capacity;
    queue->front = queue->size = 0;
 
    // 이 부분이 중요하다. enqueue를 보자.
    queue->rear = capacity - 1;
    queue->array = new int[queue->capacity];
    return queue;
}
 
// 큐가 꽉 찼을 때 true를 반환한다.
// 크기가 용량과 같아지면 큐가 꽉 찼다는 뜻이다.
int isFull(Queue* queue)
{
    return (queue->size == queue->capacity);
}
 
// 큐가 비었을 때 true를 반환한다.
// 크기가 0이면 큐가 비어 있다는 뜻이다.
int isEmpty(Queue* queue)
{
    return (queue->size == 0);
}
 
// 큐에 항목을 추가하는 함수.
// rear와 size를 변경한다.
void enqueue(Queue* queue, int item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
    cout << item << " enqueued to queue\n";
}
 
// 큐에서 항목을 제거하는 함수.
// front와 size를 변경한다.
int dequeue(Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}
 
// 큐의 앞쪽 항목을 얻는 함수
int front(Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->front];
}
 
// 큐의 뒷쪽 항목을 얻는 함수
int rear(Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->rear];
}
 
// 드라이버 코드
int main()
{
    Queue* queue = createQueue(1000);
 
    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    enqueue(queue, 40);
 
    cout << dequeue(queue) << " dequeued from queue\n";
 
    cout << "Front item is " << front(queue) << endl;
    cout << "Rear item is " << rear(queue) << endl;
 
    return 0;
}
