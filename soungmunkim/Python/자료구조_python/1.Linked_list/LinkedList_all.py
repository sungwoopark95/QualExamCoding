# 노드 클래스를 정의합니다.
class Node:
    # 노드 초기화: 데이터와 다음 노드의 포인터를 설정합니다.
    def __init__(self, data, next_node=None):
        self.data = data        # 노드의 데이터
        self.next = next_node   # 다음 노드를 가리키는 포인터

# 연결 리스트 클래스를 정의합니다.
class LinkedList:
    # 연결 리스트 초기화: 첫 번째 노드 포인터를 None(비어있음)으로 설정합니다.
    def __init__(self):
        self.head = None

    # 데이터를 받아 연결 리스트의 끝에 새 노드를 추가합니다.
    def append(self, data):
        # 연결 리스트가 비어있을 경우 새 노드를 첫 번째 노드로 설정합니다.
        if not self.head:
            self.head = Node(data)
            return
        current = self.head
        # 연결 리스트의 마지막 노드를 찾습니다.
        while current.next:
            current = current.next
        # 마지막 노드의 다음 포인터로 새 노드를 추가합니다.
        current.next = Node(data)

    # 연결 리스트에서 지정된 데이터를 가진 첫 번째 노드를 삭제합니다.
    def delete_node(self, data):
        if not self.head:
            return
        if self.head.data == data:
            self.head = self.head.next
            return
        current = self.head
        while current.next and current.next.data != data:
            current = current.next
        if not current.next:
            return
        current.next = current.next.next

    # 지정된 위치에 새 노드를 추가합니다.
    def insert(self, index, data):
        if index == 0:
            self.head = Node(data, self.head)
            return
        current = self.head
        for _ in range(index - 1):
            if not current:
                return
            current = current.next
        current.next = Node(data, current.next)

    # 연결 리스트를 오름차순으로 정렬합니다.
    def sort(self):
        if not self.head or not self.head.next:
            return
        i = self.head
        while i:
            j = i.next
            while j:
                if i.data > j.data:
                    i.data, j.data = j.data, i.data
                j = j.next
            i = i.next

    # 연결 리스트의 모든 노드를 출력합니다.
    def display(self):
        current = self.head
        while current:
            print(current.data, end=" -> ")
            current = current.next
        print("NULL")

    # 연결 리스트의 노드 개수를 반환합니다.
    def length(self):
        count = 0
        current = self.head
        while current:
            count += 1
            current = current.next
        return count

    # 지정된 위치에 노드를 추가합니다.
    def insert_at_position(self, position, data):
        if position < 0 or position > self.length():
            print("Invalid position!")
            return
        if position == 0:
            self.head = Node(data, self.head)
            return
        current = self.head
        for _ in range(1, position):
            current = current.next
        current.next = Node(data, current.next)

    # 연결 리스트의 노드를 역순으로 출력하는 재귀 함수입니다.
    def reverse_display(self, start):
        if not start:
            return
        self.reverse_display(start.next)
        print(start.data, end=" ")

    # 연결 리스트의 노드 순서를 역순으로 변경합니다.
    def reverse(self):
        prev = None
        current = self.head
        while current:
            next_node = current.next
            current.next = prev
            prev = current
            current = next_node
        self.head = prev

    # 연결 리스트의 모든 노드를 삭제합니다.
    def clear(self):
        self.head = None

if __name__ == '__main__':
    linked_list = LinkedList()  # 연결 리스트 객체를 생성합니다.
    linked_list.append('A')
    linked_list.append('B')
    linked_list.append('C')
    linked_list.display()

    linked_list.insert(1, 'X')
    linked_list.display()

    linked_list.delete_node('B')
    linked_list.display()

    linked_list.sort()
    linked_list.display()

    print("Length:", linked_list.length())

    print("Reverse display:", end=" ")
    linked_list.reverse_display(linked_list.head)
    print()

    linked_list.reverse()
    linked_list.display()

    linked_list.clear()
    linked_list.display()

######################## 외부 함수로 구현 #########################
# # 노드 클래스를 정의합니다.
# class Node:
#     # 노드 초기화: 데이터와 다음 노드의 포인터를 설정합니다.
#     def __init__(self, data, next_node=None):
#         self.data = data        # 노드에 저장될 데이터
#         self.next = next_node   # 다음 노드를 가리키는 포인터


# # 노드 생성 함수
# def create_node(data, next_node=None):
#     return Node(data, next_node)  # 데이터와 다음 노드 포인터로 노드 객체를 생성하고 반환


# # 노드 추가 함수
# def append(head, data):
#     if not head:  # 연결리스트의 헤드가 비어있는 경우
#         return create_node(data)  # 새 노드를 생성하고 반환
#     current = head
#     while current.next:  # 연결리스트의 마지막 노드를 찾기 위한 반복문
#         current = current.next
#     current.next = create_node(data)  # 마지막 노드 다음에 새 노드를 연결
#     return head  # 연결리스트의 헤드 반환


# # 노드 삭제 함수
# def delete_node(head, data):
#     if not head:  # 연결리스트가 비어있는 경우
#         return
#     if head.data == data:  # 헤드 노드의 데이터가 삭제할 데이터와 일치하는 경우
#         return head.next
#     current = head
#     while current.next and current.next.data != data:  # 삭제할 노드의 이전 노드를 찾기 위한 반복문
#         current = current.next
#     if not current.next:  # 삭제할 노드가 연결리스트에 없는 경우
#         return head
#     current.next = current.next.next  # 삭제할 노드를 연결리스트에서 제거
#     return head  # 연결리스트의 헤드 반환


# # 리스트 출력 함수
# def display(head):
#     current = head
#     while current:  # 연결리스트의 모든 노드를 순회하는 반복문
#         print(current.data, end=" -> ")  # 현재 노드의 데이터 출력
#         current = current.next
#     print("NULL")  # 연결리스트의 마지막을 표시


# # 노드 정렬 함수
# def sort(head):
#     if not head or not head.next:  # 연결리스트가 비어있거나 노드가 하나만 있는 경우
#         return head
#     i = head
#     while i:  # 외부 반복문은 현재 정렬을 위한 노드를 가리킵니다.
#         j = i.next
#         while j:  # 내부 반복문은 현재 노드보다 뒤에 있는 노드들과 비교를 위해 사용됩니다.
#             if i.data > j.data:  # 두 노드의 데이터를 비교하여 필요하면 교환
#                 i.data, j.data = j.data, i.data
#             j = j.next  # 다음 노드로 이동
#         i = i.next  # 다음 노드로 이동
#     return head  # 정렬된 연결리스트의 헤드 반환


# # 리스트의 길이 반환 함수
# def length(head):
#     count = 0
#     current = head
#     while current:  # 연결리스트의 모든 노드를 순회하는 반복문
#         count += 1  # 노드 개수 카운트
#         current = current.next
#     return count  # 연결리스트의 길이 반환


# # 노드의 순서를 역순으로 변경 함수
# def reverse(head):
#     prev = None
#     current = head
#     while current:
#         next_node = current.next  # 현재 노드의 다음 노드를 임시 저장
#         current.next = prev  # 현재 노드의 다음 노드를 이전 노드로 변경
#         prev = current  # 이전 노드를 현재 노드로 업데이트
#         current = next_node  # 다음 노드로 이동
#     return prev  # 역순으로 변경된 연결리스트의 헤드 반환


# # 리스트에서 모든 노드 삭제 함수
# def clear():
#     return None  # 빈 연결리스트 반환


# if __name__ == '__main__':
#     linked_list = None
#     linked_list = append(linked_list, 'A')  # 연결리스트에 'A' 추가
#     linked_list = append(linked_list, 'B')  # 연결리스트에 'B' 추가
#     linked_list = append(linked_list, 'C')  # 연결리스트에 'C' 추가
#     display(linked_list)  # 연결리스트 출력

#     linked_list = delete_node(linked_list, 'B')  # 연결리스트에서 'B' 삭제
#     display(linked_list)  # 연결리스트 출력

#     linked_list = sort(linked_list)  # 연결리스트 정렬
#     display(linked_list)  # 연결리스트 출력

#     print("Length:", length(linked_list))  # 연결리스트의 길이 출력

#     linked_list = reverse(linked_list)  # 연결리스트 역순으로 변경
#     display(linked_list)  # 연결리스트 출력

#     linked_list = clear()  # 연결리스트에서 모든 노드 삭제
#     display(linked_list)  # 연결리스트 출력
