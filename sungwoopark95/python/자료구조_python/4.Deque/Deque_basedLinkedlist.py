# Node: 이중 연결 리스트의 기본 단위
class Node:
    def __init__(self, n=None, prev_node=None, next_node=None):
        self.data = n  # 노드에 저장되는 값
        self.prev = prev_node  # 이전 노드를 가리키는 포인터
        self.next = next_node  # 다음 노드를 가리키는 포인터

    # 이전 노드를 설정하는 함수
    def set_prev(self, prev_node):
        self.prev = prev_node

    # 다음 노드를 설정하는 함수
    def set_next(self, next_node):
        self.next = next_node


# Deque: 이중 연결 리스트를 사용하여 구현된 Deque 클래스
class Deque:
    def __init__(self):
        self.front = None  # Deque의 앞쪽 노드를 가리키는 포인터
        self.rear = None   # Deque의 뒷쪽 노드를 가리키는 포인터
        self.data_size = 0  # 현재 Deque에 저장된 데이터의 개수

    # 앞쪽에 데이터 추가
    def add_front(self, n):
        node = Node(n, None, self.front)
        if self.rear is None:  # 첫 번째 노드인 경우
            self.rear = node
        else:
            self.front.set_prev(node)  # 기존 front 노드의 prev를 새 노드로 설정
        self.front = node  # front 포인터를 새 노드로 업데이트
        self.data_size += 1  # 데이터 개수 증가

    # 뒷쪽에 데이터 추가
    def add_rear(self, n):
        node = Node(n, self.rear, None)
        if self.front is None:  # 첫 번째 노드인 경우
            self.front = node
        else:
            self.rear.set_next(node)  # 기존 rear 노드의 next를 새 노드로 설정
        self.rear = node  # rear 포인터를 새 노드로 업데이트
        self.data_size += 1  # 데이터 개수 증가

    # 앞쪽 데이터 삭제 후 반환
    def delete_front(self):
        if self.is_empty():
            raise ValueError("Deque Empty Error")
        data = self.front.data
        node = self.front
        self.front = self.front.next
        if self.front:
            self.front.set_prev(None)  # front가 None이 아니면 prev를 None으로 설정
        del node
        self.data_size -= 1  # 데이터 개수 감소
        return data

    # 뒷쪽 데이터 삭제 후 반환
    def delete_rear(self):
        if self.is_empty():
            raise ValueError("Deque Empty Error")
        data = self.rear.data
        node = self.rear
        self.rear = self.rear.prev
        if self.rear:
            self.rear.set_next(None)  # rear가 None이 아니면 next를 None으로 설정
        del node
        self.data_size -= 1  # 데이터 개수 감소
        return data

    # Deque 내의 모든 데이터를 출력
    def display(self):
        if self.is_empty():
            print("Deque is Empty")
        else:
            node = self.front
            while node:
                print(f"[{node.data}]", end="")
                node = node.next  # 다음 노드로 이동
            print()

    # Deque의 크기(저장된 데이터 개수)를 반환
    def size(self):
        return self.data_size

    # Deque가 비어있는지 확인
    def is_empty(self):
        return self.data_size == 0


# 메인 함수: Deque 클래스를 테스트하는 코드
if __name__ == "__main__":
    deque = Deque()

    print("===== addRear x3 =====")
    deque.add_rear(1)
    deque.add_rear(2)
    deque.add_rear(3)
    print(f" size : {deque.size()}")
    deque.display()

    print("===== addFront x2 =====")
    deque.add_front(5)
    deque.add_front(6)
    print(f" size : {deque.size()}")
    deque.display()

    print("===== deleteRear x1 =====")
    print(deque.delete_rear())
    print(f" size : {deque.size()}")
    deque.display()

    print("===== deleteFront x3 =====")
    print(deque.delete_front())
    print(deque.delete_front())
    print(deque.delete_front())
    print(f" size : {deque.size()}")
    deque.display()

########################### 외부 함수들로 구현 ###########################
# # 노드 클래스 선언
# class Node:
#     # 초기화 메서드
#     def __init__(self, data=None, prev=None, next=None):
#         self.data = data  # 데이터 저장
#         self.prev = prev  # 이전 노드 포인터
#         self.next = next  # 다음 노드 포인터

# # 전역 변수 선언
# front = None  # Deque의 앞부분
# rear = None   # Deque의 뒷부분
# data_size = 0 # Deque의 데이터 크기

# # 앞부분에 데이터 추가
# def add_front(n):
#     global front, rear, data_size
#     node = Node(n, None, front)
#     if not rear:  # 만약 Deque가 비어있으면
#         rear = node
#     else:
#         front.prev = node
#     front = node
#     data_size += 1

# # 뒷부분에 데이터 추가
# def add_rear(n):
#     global front, rear, data_size
#     node = Node(n, rear, None)
#     if not front:  # 만약 Deque가 비어있으면
#         front = node
#     else:
#         rear.next = node
#     rear = node
#     data_size += 1

# # 앞부분 데이터 삭제
# def delete_front():
#     global front, rear, data_size
#     if is_empty():  # Deque가 비어있는 경우 에러 발생
#         raise ValueError("Deque Empty Error")
#     data = front.data
#     node = front
#     front = front.next
#     if front:
#         front.prev = None
#     else:
#         rear = None
#     del node
#     data_size -= 1
#     return data

# # 뒷부분 데이터 삭제
# def delete_rear():
#     global front, rear, data_size
#     if is_empty():  # Deque가 비어있는 경우 에러 발생
#         raise ValueError("Deque Empty Error")
#     data = rear.data
#     node = rear
#     rear = rear.prev
#     if rear:
#         rear.next = None
#     else:
#         front = None
#     del node
#     data_size -= 1
#     return data

# # Deque 내의 모든 데이터를 출력
# def display():
#     node = front
#     while node:  # 노드가 None이 될 때까지 반복
#         print(f"[{node.data}]", end="")
#         node = node.next
#     print()

# # Deque의 크기 반환
# def size():
#     return data_size

# # Deque가 비어있는지 확인
# def is_empty():
#     return data_size == 0

# # 테스트 코드
# if __name__ == "__main__":
#     print("===== addRear x3 =====")
#     add_rear(1)
#     add_rear(2)
#     add_rear(3)
#     print(f" size : {size()}")
#     display()

#     print("===== addFront x2 =====")
#     add_front(5)
#     add_front(6)
#     print(f" size : {size()}")
#     display()

#     print("===== deleteRear x1 =====")
#     print(delete_rear())
#     print(f" size : {size()}")
#     display()

#     print("===== deleteFront x3 =====")
#     print(delete_front())
#     print(delete_front())
#     print(delete_front())
#     print(f" size : {size()}")
#     display()
