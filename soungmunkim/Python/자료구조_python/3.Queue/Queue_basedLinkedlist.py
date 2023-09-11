class QNode:
    def __init__(self, data):
        self.data = data  # 노드에 저장될 데이터
        self.next = None  # 다음 노드를 가리키는 포인터. 초기값은 None.

class Queue:
    def __init__(self):
        self.front = None  # 큐의 앞쪽(시작)를 가리키는 포인터. 초기값은 None.
        self.rear = None   # 큐의 뒷쪽(끝)을 가리키는 포인터. 초기값은 None.

    def enQueue(self, x):
        temp = QNode(x)  # 새로운 노드 생성

        # 큐가 비어 있을 경우
        if self.rear is None:
            self.front = self.rear = temp  # 새 노드를 큐의 앞쪽과 뒷쪽으로 설정
            return

        # 큐의 끝에 새로운 노드를 추가
        self.rear.next = temp
        self.rear = temp  # 뒷쪽 포인터를 새 노드로 이동

    def deQueue(self):
        # 큐가 비어 있을 경우 함수 종료
        if self.front is None:
            return

        # 현재 front가 가리키는 노드를 임시로 저장
        temp = self.front
        # front 포인터를 다음 노드로 이동
        self.front = temp.next

        # front가 None이면 큐가 비어있으므로 rear도 None으로 설정
        if self.front is None:
            self.rear = None

        # 더 이상 사용하지 않는 노드 메모리 해제 (파이썬에서는 garbage collector에 의해 자동으로 처리되므로 해당 코드는 생략)

# 드라이버 코드
if __name__ == '__main__':
    q = Queue()
    q.enQueue(10)
    q.enQueue(20)
    q.deQueue()
    q.deQueue()
    q.enQueue(30)
    q.enQueue(40)
    q.enQueue(50)
    q.deQueue()

    # 큐의 앞쪽과 뒷쪽 데이터 출력. 큐가 비어 있을 경우 -1 출력
    print(f"Queue Front : {q.front.data if q.front else -1}")
    print(f"Queue Rear : {q.rear.data if q.rear else -1}")

########################## 외부 함수들로 구현한 것 ###########################3
# class QNode:
#     def __init__(self, data):
#         self.data = data  # 노드에 저장될 데이터
#         self.next = None  # 다음 노드를 가리키는 포인터, 초기값은 None.

# class Queue:
#     def __init__(self):
#         self.front = None  # 큐의 앞쪽(시작)를 가리키는 포인터, 초기값은 None.
#         self.rear = None   # 큐의 뒷쪽(끝)를 가리키는 포인터, 초기값은 None.


# def is_empty(queue: Queue) -> bool:
#     """큐가 비어있는지 확인하는 함수"""
#     return queue.front is None


# def enQueue(queue: Queue, x: int):
#     """큐에 항목을 추가하는 함수"""
#     temp = QNode(x)  # 새로운 노드 생성

#     # 큐가 비어 있을 경우
#     if queue.rear is None:
#         queue.front = queue.rear = temp
#         return

#     # 큐의 끝에 새로운 노드를 추가
#     queue.rear.next = temp
#     queue.rear = temp  # 뒷쪽 포인터를 새 노드로 이동


# def deQueue(queue: Queue):
#     """큐에서 항목을 제거하는 함수"""
#     if is_empty(queue):
#         return

#     temp = queue.front
#     queue.front = temp.next

#     if queue.front is None:
#         queue.rear = None


# def get_front(queue: Queue) -> int:
#     """큐의 앞쪽 데이터 반환 함수"""
#     return queue.front.data if not is_empty(queue) else -1


# def get_rear(queue: Queue) -> int:
#     """큐의 뒷쪽 데이터 반환 함수"""
#     return queue.rear.data if not is_empty(queue) else -1


# # 드라이버 코드
# if __name__ == '__main__':
#     q = Queue()
#     enQueue(q, 10)
#     enQueue(q, 20)
#     deQueue(q)
#     deQueue(q)
#     enQueue(q, 30)
#     enQueue(q, 40)
#     enQueue(q, 50)
#     deQueue(q)

#     print(f"Queue Front : {get_front(q)}")
#     print(f"Queue Rear : {get_rear(q)}")
