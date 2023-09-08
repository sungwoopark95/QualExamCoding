#include <stdio.h>
#include <stdlib.h>
#include <limits.h>    // INT_MIN을 위한 헤더 파일

// 큐 구조체 정의
typedef struct queue {
	int* array;           // 큐의 배열
	int size, front, rear, capacity; // 큐의 크기, 시작점, 끝점, 총 용량
} Queue;

// 큐 생성 함수
Queue* createQueue(int capacity)
{
	Queue* queue = (Queue*)malloc(sizeof(Queue)); // 큐 동적 할당

	if(queue == NULL) // 메모리 할당 검사
	{
		printf("Heap over.");
		exit(1);
	}

	queue->array = (int *)malloc(sizeof(int) * capacity); // 배열 동적 할당
	
	if (queue->array == NULL) // 배열 메모리 할당 검사
	{
		printf("Heap over.");
		exit(1);
	}

	queue->capacity = capacity;
	queue->size = 0;
	queue->front = 0;
	queue->rear = capacity - 1; // 초기 rear 위치 설정

	return queue; // 생성된 큐 반환
}

// 큐가 가득 찼는지 검사
int isFull(Queue* queue)
{
	return queue->size == queue->capacity;
}

// 큐가 비었는지 검사
int isEmpty(Queue* queue)
{
	return queue->size == 0;
}

// 큐에 데이터 삽입 함수
void enqueue(Queue* queue, int data)
{
	if(isFull(queue)) // 큐가 가득 찼을 경우
	{
		printf("Queue is full.");
		return;
	}

	queue->rear = (queue->rear + 1) % queue->capacity; // 순환 큐 rear 위치 조정
	queue->size++;
	queue->array[queue->rear] = data;

	printf("enqueue : %d\n", data);
}

// 큐에서 데이터 추출 함수
int dequeue(Queue* queue)
{
	if (isEmpty(queue)) // 큐가 비었을 경우
	{
		printf("Queue is empty.");
		return INT_MIN; // 가장 작은 정수 반환
	}

	int retData = queue->array[queue->front];
	queue->front = (queue->front + 1) % queue->capacity; // 순환 큐 front 위치 조정
	queue->size--;
	return retData; // 데이터 반환
}

// 큐의 맨 앞 데이터 확인 함수
int front(Queue* queue)
{
	if (isEmpty(queue)) // 큐가 비었을 경우
		return INT_MIN;
	return queue->array[queue->front];
}

// 큐의 맨 뒤 데이터 확인 함수
int rear(Queue* queue)
{
	if (isEmpty(queue)) // 큐가 비었을 경우
		return INT_MIN;
	return queue->array[queue->rear];
}

int main(void)
{
	Queue* queue = createQueue(10);
	enqueue(queue, 1);
	enqueue(queue, 2);
	enqueue(queue, 3);
	enqueue(queue, 4);
	enqueue(queue, 5);
	enqueue(queue, 6);
	enqueue(queue, 7);
	enqueue(queue, 8);
	enqueue(queue, 9);
	enqueue(queue, 10);

	printf("%d \n", dequeue(queue));
	printf("%d \n", dequeue(queue));
	printf("%d \n", dequeue(queue));
	printf("%d \n", dequeue(queue));
	printf("%d \n", dequeue(queue));
	printf("%d \n", dequeue(queue));
	printf("%d \n", dequeue(queue));
	printf("%d \n", dequeue(queue));
	printf("%d \n", dequeue(queue));
	printf("%d \n", dequeue(queue));

	enqueue(queue, 5);
	printf("%d \n", dequeue(queue));

	enqueue(queue, 1);

	printf("front : %d \n", front(queue));
	printf("rear : %d \n", rear(queue));
	getchar();

	return 0;
}