class Stack:
    # Node 클래스 선언
    class Node:
        # Node 클래스 생성자
        def __init__(self, data, left=None, right=None):
            self.data = data           # 노드에 저장될 데이터
            self.left = left           # 왼쪽(아래) 노드를 가리키는 링크
            self.right = right         # 오른쪽(위) 노드를 가리키는 링크

    # Stack 클래스 생성자
    def __init__(self):
        self.head = None               # 스택의 최상단을 가리키는 포인터 (top)
        self.tail = None               # 스택의 최하단을 가리키는 포인터 (bottom)

    # 아이템을 스택에 푸시하는 메서드
    def push(self, item):
        # 새로운 노드를 스택의 최상단에 추가
        self.head = self.Node(item, None, self.head)
        
        # 스택이 비어 있을 경우 tail도 새 노드를 가리킴
        if not self.tail:
            self.tail = self.head
        else:
            # 새로운 노드의 오른쪽 노드의 왼쪽 링크를 새 노드로 설정
            self.head.right.left = self.head

    # 스택의 최상단에서 아이템을 팝하는 메서드
    def pop(self):
        # 스택이 비어 있을 경우 오류 발생
        if not self.head:
            raise Exception("스택이 비어있습니다.")
        
        target = self.head              # 현재 head를 target으로 설정
        popped_item = target.data       # 팝 할 아이템
        
        self.head = target.right        # head를 다음 노드로 이동
        
        # 스택이 비었을 경우 tail을 None으로 설정
        if not self.head:
            self.tail = None
        
        return popped_item

    # 스택의 최상단 아이템을 읽는 메서드 (제거 없이)
    def peek(self):
        if not self.head:
            raise Exception("스택이 비어있습니다.")
        
        return self.head.data           # 현재 head의 데이터 반환

    # 스택이 비어 있는지 확인하는 메서드
    def is_empty(self):
        return self.head is None


# 사용 예제
if __name__ == "__main__":
    s = Stack()                          # 스택 객체 생성
    s.push(1)                            # 스택에 1 푸시
    s.push(2)                            # 스택에 2 푸시
    s.push(3)                            # 스택에 3 푸시
    print(s.peek())                      # 스택의 최상단 요소 출력 -> 3
    print(s.pop())                       # 스택의 최상단 요소 팝 -> 3
    print(s.pop())                       # 스택의 최상단 요소 팝 -> 2
    s.push(4)                            # 스택에 4 푸시
    print(s.peek())                      # 스택의 최상단 요소 출력 -> 4
    print(s.pop())                       # 스택의 최상단 요소 팝 -> 4
    print(s.pop())                       # 스택의 최상단 요소 팝 -> 1

######################### 외부 함수들로 구현한 것 ########################3
# # 노드를 나타내는 클래스
# class Node:
#     # Node 클래스 생성자
#     def __init__(self, data, left=None, right=None):
#         self.data = data           # 노드에 저장될 데이터
#         self.left = left           # 왼쪽(아래) 노드를 가리키는 링크
#         self.right = right         # 오른쪽(위) 노드를 가리키는 링크

# # 스택을 나타내는 클래스
# class Stack:
#     # Stack 클래스 생성자
#     def __init__(self):
#         self.head = None               # 스택의 최상단을 가리키는 포인터 (top)
#         self.tail = None               # 스택의 최하단을 가리키는 포인터 (bottom)

# # 아이템을 스택에 푸시하는 함수
# def push(stack, item):
#     # 새로운 노드를 생성하여 스택의 최상단에 추가
#     stack.head = Node(item, None, stack.head)
    
#     # 스택의 최하단이 설정되어 있지 않을 경우 최하단을 현재 노드로 설정
#     if not stack.tail:
#         stack.tail = stack.head
#     else:
#         # 새로운 노드의 오른쪽 링크를 업데이트하여 연결
#         stack.head.right.left = stack.head

# # 스택의 최상단에서 아이템을 팝하는 함수
# def pop(stack):
#     # 스택이 비어 있는지 확인
#     if not stack.head:
#         raise Exception("스택이 비어있습니다.")
    
#     # 스택의 최상단 노드를 가져옴
#     target = stack.head
#     popped_item = target.data
    
#     # 스택의 최상단을 다음 노드로 이동
#     stack.head = target.right
#     if not stack.head:
#         stack.tail = None
    
#     # 팝된 아이템 반환
#     return popped_item

# # 스택의 최상단 아이템을 읽는 함수 (제거 없이)
# def peek(stack):
#     # 스택이 비어 있는지 확인
#     if not stack.head:
#         raise Exception("스택이 비어있습니다.")
