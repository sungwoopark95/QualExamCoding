class Queue:
    def __init__(self, capacity):
        # 초기 설정: 큐의 앞, 큐의 크기, 그리고 큐의 끝 위치 설정
        self.front = self.size = 0
        self.capacity = capacity  # 큐의 최대 용량 설정
        self.rear = capacity - 1  # 끝 위치 초기 설정
        self.array = [None] * capacity  # 큐에 저장할 리스트 초기화

    def is_full(self):
        # 큐가 꽉 찼는지 확인하는 함수
        return self.size == self.capacity

    def is_empty(self):
        # 큐가 비어있는지 확인하는 함수
        return self.size == 0

    def enqueue(self, item):
        # 큐에 아이템 추가 함수
        if self.is_full():
            print("Queue is full!")  # 큐가 꽉 찼을 때의 처리
            return
        self.rear = (self.rear + 1) % self.capacity  # 끝 위치 재조정
        self.array[self.rear] = item  # 아이템 추가
        self.size += 1
        print(f"{item} enqueued to queue")

    def dequeue(self):
        # 큐에서 아이템 제거 함수
        if self.is_empty():
            print("Queue is empty!")  # 큐가 비어 있을 때의 처리
            return None
        item = self.array[self.front]  # 앞에 있는 아이템 가져오기
        self.front = (self.front + 1) % self.capacity  # 앞 위치 재조정
        self.size -= 1
        return item

    def get_front(self):
        # 큐의 앞쪽 아이템 가져오기
        if self.is_empty():
            print("Queue is empty!")  # 큐가 비어 있을 때의 처리
            return None
        return self.array[self.front]

    def get_rear(self):
        # 큐의 끝쪽 아이템 가져오기
        if self.is_empty():
            print("Queue is empty!")  # 큐가 비어 있을 때의 처리
            return None
        return self.array[self.rear]


# 드라이버 코드
if __name__ == "__main__":
    queue = Queue(1000)  # 큐 생성

    queue.enqueue(10)  # 10 추가
    queue.enqueue(20)  # 20 추가
    queue.enqueue(30)  # 30 추가
    queue.enqueue(40)  # 40 추가

    print(f"{queue.dequeue()} dequeued from queue")  # 큐에서 아이템 제거하고 출력
    print(f"Front item is {queue.get_front()}")  # 큐의 앞쪽 아이템 출력
    print(f"Rear item is {queue.get_rear()}")  # 큐의 끝쪽 아이템 출력


########################### 외부 함수들로 구현해줘 #########################
# def create_queue(capacity):
#     return {
#         "front": 0,
#         "size": 0,
#         "rear": capacity - 1,
#         "capacity": capacity,
#         "array": [None] * capacity
#     }

# def is_full(queue):
#     return queue["size"] == queue["capacity"]

# def is_empty(queue):
#     return queue["size"] == 0

# def enqueue(queue, item):
#     if is_full(queue):
#         print("Queue is full!")
#         return
#     queue["rear"] = (queue["rear"] + 1) % queue["capacity"]
#     queue["array"][queue["rear"]] = item
#     queue["size"] += 1
#     print(f"{item} enqueued to queue")

# def dequeue(queue):
#     if is_empty(queue):
#         print("Queue is empty!")
#         return None
#     item = queue["array"][queue["front"]]
#     queue["front"] = (queue["front"] + 1) % queue["capacity"]
#     queue["size"] -= 1
#     return item

# def get_front(queue):
#     if is_empty(queue):
#         print("Queue is empty!")
#         return None
#     return queue["array"][queue["front"]]

# def get_rear(queue):
#     if is_empty(queue):
#         print("Queue is empty!")
#         return None
#     return queue["array"][queue["rear"]]


# # 드라이버 코드
# if __name__ == "__main__":
#     queue = create_queue(1000)

#     enqueue(queue, 10)
#     enqueue(queue, 20)
#     enqueue(queue, 30)
#     enqueue(queue, 40)

#     print(f"{dequeue(queue)} dequeued from queue")
#     print(f"Front item is {get_front(queue)}")
#     print(f"Rear item is {get_rear(queue)}")
