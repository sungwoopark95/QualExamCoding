class Deque:
    def __init__(self):
        self.MAX_DEQUE_SIZE = 10  # 덱의 최대 크기 설정
        self.front = 0  # 첫 번째 요소 앞의 인덱스
        self.rear = 0   # 마지막 요소의 인덱스
        self.data = [0] * self.MAX_DEQUE_SIZE  # 데이터 저장을 위한 배열

    # 덱의 앞에 항목을 추가하는 함수
    def addFront(self, n):
        if self.isFull():  # 덱이 가득 찼을 때
            print("Deque Full Error")
            return
        self.data[self.front] = n
        # front가 0 이하일 경우, max 인덱스로 순회
        self.front = (self.front - 1 + self.MAX_DEQUE_SIZE) % self.MAX_DEQUE_SIZE

    # 덱의 뒤에 항목을 추가하는 함수
    def addRear(self, n):
        if self.isFull():  # 덱이 가득 찼을 때
            print("Deque Full Error")
            return
        # rear가 최대값을 넘어가면 0번째 인덱스로 순회
        self.rear = (self.rear + 1) % self.MAX_DEQUE_SIZE
        self.data[self.rear] = n

    # 덱의 앞 항목을 제거하는 함수
    def deleteFront(self):
        if self.isEmpty():  # 덱이 비어 있을 때
            print("Deque Empty Error")
            return
        # front가 최대값을 넘어가면 0번째 인덱스로 순회
        self.front = (self.front + 1) % self.MAX_DEQUE_SIZE
        return self.data[self.front]

    # 덱의 뒤 항목을 제거하는 함수
    def deleteRear(self):
        if self.isEmpty():  # 덱이 비어 있을 때
            print("Deque Empty Error")
            return
        temp = self.data[self.rear]
        # rear가 0 이하일 경우, max 인덱스로 순회
        self.rear = (self.rear - 1 + self.MAX_DEQUE_SIZE) % self.MAX_DEQUE_SIZE
        return temp

    # 덱의 앞 항목을 조회하는 함수
    def getFront(self):
        if self.isEmpty():  # 덱이 비어 있을 때
            print("Deque Empty Error")
            return
        return self.data[(self.front + 1) % self.MAX_DEQUE_SIZE]

    # 덱의 뒤 항목을 조회하는 함수
    def getRear(self):
        if self.isEmpty():  # 덱이 비어 있을 때
            print("Deque Empty Error")
            return
        return self.data[self.rear]

    # 덱의 크기를 반환하는 함수
    def size(self):
        return self.rear - self.front if self.front <= self.rear else (self.rear + self.MAX_DEQUE_SIZE) - self.front

    # 덱의 내용을 출력하는 함수
    def display(self):
        for i in range(self.front + 1, self.front + self.size() + 1):
            print(f"[{self.data[i % self.MAX_DEQUE_SIZE]}]", end="")
        print()

    # 원형 배열의 front와 rear 정보를 출력하기 위한 함수
    def displayDetail(self):
        print("DEQUE: ", end="")
        for i in range(self.front + 1, self.front + self.size() + 1):
            print(f"[{self.data[i % self.MAX_DEQUE_SIZE]}]", end="")
        print()

        print("index: ", end="")
        for i in range(self.front + 1, self.front + self.size() + 1):
            print(f"{i % self.MAX_DEQUE_SIZE} ", end="")
        print()

        print(f"front: {self.front}, rear: {self.rear}\n")

    # 덱이 비어 있는지 확인하는 함수
    def isEmpty(self):
        return self.front == self.rear

    # 덱이 꽉 차 있는지 확인하는 함수
    def isFull(self):
        return self.front == (self.rear + 1) % self.MAX_DEQUE_SIZE


# 메인 함수
if __name__ == '__main__':
    deque = Deque()

    print("===== addRear x3 =====")
    deque.addRear(1)
    deque.addRear(2)
    deque.addRear(3)
    print(f" size: {deque.size()}")
    deque.displayDetail()

    print("===== addFront x2 =====")
    deque.addFront(5)
    deque.addFront(6)
    print(f" size: {deque.size()}")
    deque.displayDetail()

    print("===== deleteRear x1 =====")
    deque.deleteRear()
    print(f" size: {deque.size()}")
    deque.displayDetail()

    print("===== deleteFront x3 =====")
    deque.deleteFront()
    deque.deleteFront()
    deque.deleteFront()
    print(f" size: {deque.size()}")
    deque.displayDetail()

############################ 외부 함수들로 구현 #############################
# MAX_DEQUE_SIZE = 10  # 덱의 최대 크기 설정

# # 초기화 함수
# def init():
#     return {'front': 0, 'rear': 0, 'data': [0] * MAX_DEQUE_SIZE}

# # 덱이 비어 있는지 확인하는 함수
# def isEmpty(deque):
#     return deque['front'] == deque['rear']

# # 덱이 꽉 차 있는지 확인하는 함수
# def isFull(deque):
#     return deque['front'] == (deque['rear'] + 1) % MAX_DEQUE_SIZE

# # 덱의 앞에 항목을 추가하는 함수
# def addFront(deque, n):
#     if isFull(deque):
#         print("Deque Full Error")
#         return
#     deque['data'][deque['front']] = n
#     deque['front'] = (deque['front'] - 1 + MAX_DEQUE_SIZE) % MAX_DEQUE_SIZE

# # 덱의 뒤에 항목을 추가하는 함수
# def addRear(deque, n):
#     if isFull(deque):
#         print("Deque Full Error")
#         return
#     deque['rear'] = (deque['rear'] + 1) % MAX_DEQUE_SIZE
#     deque['data'][deque['rear']] = n

# # 덱의 앞 항목을 제거하는 함수
# def deleteFront(deque):
#     if isEmpty(deque):
#         print("Deque Empty Error")
#         return
#     deque['front'] = (deque['front'] + 1) % MAX_DEQUE_SIZE
#     return deque['data'][deque['front']]

# # 덱의 뒤 항목을 제거하는 함수
# def deleteRear(deque):
#     if isEmpty(deque):
#         print("Deque Empty Error")
#         return
#     temp = deque['data'][deque['rear']]
#     deque['rear'] = (deque['rear'] - 1 + MAX_DEQUE_SIZE) % MAX_DEQUE_SIZE
#     return temp

# # 덱의 크기를 반환하는 함수
# def size(deque):
#     return deque['rear'] - deque['front'] if deque['front'] <= deque['rear'] else (deque['rear'] + MAX_DEQUE_SIZE) - deque['front']

# # 덱의 내용을 출력하는 함수
# def display(deque):
#     for i in range(deque['front'] + 1, deque['front'] + size(deque) + 1):
#         print(f"[{deque['data'][i % MAX_DEQUE_SIZE]}]", end="")
#     print()

# # 원형 배열의 front와 rear 정보를 출력하기 위한 함수
# def displayDetail(deque):
#     print("DEQUE: ", end="")
#     for i in range(deque['front'] + 1, deque['front'] + size(deque) + 1):
#         print(f"[{deque['data'][i % MAX_DEQUE_SIZE]}]", end="")
#     print()

#     print("index: ", end="")
#     for i in range(deque['front'] + 1, deque['front'] + size(deque) + 1):
#         print(f"{i % MAX_DEQUE_SIZE} ", end="")
#     print()

#     print(f"front: {deque['front']}, rear: {deque['rear']}\n")

# # 메인 함수
# if __name__ == '__main__':
#     deque = init()

#     print("===== addRear x3 =====")
#     addRear(deque, 1)
#     addRear(deque, 2)
#     addRear(deque, 3)
#     print(f" size: {size(deque)}")
#     displayDetail(deque)

#     print("===== addFront x2 =====")
#     addFront(deque, 5)
#     addFront(deque, 6)
#     print(f" size: {size(deque)}")
#     displayDetail(deque)

#     print("===== deleteRear x1 =====")
#     deleteRear(deque)
#     print(f" size: {size(deque)}")
#     displayDetail(deque)

#     print("===== deleteFront x3 =====")
#     deleteFront(deque)
#     deleteFront(deque)
#     deleteFront(deque)
#     print(f" size: {size(deque)}")
#     displayDetail(deque)
