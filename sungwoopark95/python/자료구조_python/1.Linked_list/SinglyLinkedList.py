import random

class Node:
    """단일 연결 리스트의 노드 클래스"""
    def __init__(self, data):
        self.data = data  # 노드에 저장될 데이터
        self.next = None  # 다음 노드를 가리키는 포인터. 초기값은 None

class LinkedList:
    """단일 연결 리스트 클래스"""
    def __init__(self):
        self.head = None  # 리스트의 시작 노드
        self.tail = None  # 리스트의 마지막 노드
        self.current = None  # 현재 조회 중인 노드
        self.before = None  # 현재 조회 중인 노드의 이전 노드
        self.num_of_data = 0  # 리스트에 저장된 데이터의 개수

    def add(self, data):
        new_node = Node(data)  # 새로운 노드 생성
        if self.head is None:  # 리스트가 비어 있으면
            self.head = new_node  # 헤드와 테일을 새 노드로 지정
            self.tail = new_node
        else:
            self.tail.next = new_node  # 리스트의 끝에 새로운 노드 추가
            self.tail = new_node  # 테일을 새 노드로 업데이트
        self.num_of_data += 1  # 데이터 개수 증가

    def first(self):
        if self.head is None:  # 리스트가 비어 있으면
            return None
        self.before = self.head  # before와 current를 초기화
        self.current = self.head.next
        return self.before.data  # 현재 데이터 반환

    def next(self):
        if self.current is None:  # 다음 데이터가 없으면
            return None
        self.before = self.current  # before와 current를 이동
        self.current = self.current.next
        return self.before.data  # 현재 데이터 반환

    def remove(self):
        if self.before is self.head:  # 첫 번째 데이터를 삭제하는 경우
            self.head = self.current  # 헤드를 다음 노드로 이동
            self.before = self.current  # before도 이동
        else:
            self.before.next = self.current  # before의 다음 노드를 current의 다음 노드로 변경
            self.before = self.current  # before를 이동
        if self.current:  # current가 None이 아니면
            self.current = self.current.next  # current를 이동
        else:
            self.tail = self.before  # current가 None이면 before를 테일로 설정
        self.num_of_data -= 1  # 데이터 개수 감소

    def pop(self):
        if not self.current:
            print("No current node to pop.")
            return None

        data = self.current.strData

        if self.before is self.head:  # 첫 번째 데이터를 삭제하는 경우
            self.head = self.current.next  # 헤드를 다음 노드로 이동
            self.before = self.current  # before도 이동
        else:
            self.before.next = self.current.next  # before의 다음 노드를 current의 다음 노드로 변경

        if self.current.next:  # current의 다음 노드가 None이 아니면
            self.current = self.current.next  # current를 이동
        else:
            self.tail = self.before  # current가 None이면 before를 테일로 설정
            self.current = None

        self.num_of_data -= 1  # 데이터 개수 감소

        return data

    def getSize(self):  # 데이터 개수 반환
        return self.num_of_data

    def isEmpty(self):  # 리스트가 비어 있는지 확인
        return self.num_of_data == 0

    def hasNext(self):  # 다음 데이터가 있는지 확인
        return self.current is not None

class Point:
    def __init__(self, x=0, y=0):  # 생성자: x, y 좌표 초기화 (기본값은 0)
        self.x = x
        self.y = y

    def print(self):  # 좌표 출력 함수
        print(f"({self.x}, {self.y})")

    def __eq__(self, other):  # 두 Point 객체가 같은지 확인
        return self.x == other.x and self.y == other.y

def main():
    point_list = LinkedList()  # Point 객체들을 저장할 연결 리스트 생성

    for _ in range(10):  # 10개의 Point 객체를 랜덤하게 생성하여 리스트에 추가
        point = Point(random.randint(0, 2), random.randint(0, 2))
        point_list.add(point)

    print(f"현재 데이터 수: {point_list.getSize()}")  # 현재 데이터 개수 출력

    point_list.first().print()  # 첫 번째 데이터 출력
    while point_list.hasNext():  # 나머지 데이터 출력
        point_list.next().print()

    print("---printf finished--\n")

    compare_position = Point(random.randint(0, 2), random.randint(0, 2))  # 랜덤한 위치의 Point 객체 생성
    print("삭제할 Point: ", end="")  # 삭제할 Point 출력
    compare_position.print()

    if point_list.first() == compare_position:  # 첫 번째 데이터와 비교 후 일치하면 삭제
        point_list.remove()

    while point_list.hasNext():  # 나머지 데이터와 비교 후 일치하면 삭제
        if point_list.next() == compare_position:
            point_list.remove()

    print(f"현재 데이터 수: {point_list.getSize()}")  # 현재 데이터 개수 출력

    point_list.first().print()  # 첫 번째 데이터 출력
    while point_list.hasNext():  # 나머지 데이터 출력
        point_list.next().print()

    print("---printf finished--\n")

if __name__ == "__main__":
    main()  # 메인 함수 실행
