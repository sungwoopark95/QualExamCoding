# 노드를 나타내는 클래스
class Node:
    # 노드 초기화
    def __init__(self, data):
        self.data = data  # 노드의 데이터 부분
        self.next = None  # 다음 노드를 가리키는 포인터

# 스택을 나타내는 클래스
class Stack:
    # 스택 초기화. 기본 최대 크기는 무한대로 설정
    def __init__(self, max_size=float('inf')):
        self.top = None  # 스택의 최상단을 가리키는 포인터
        self.max_size = max_size  # 스택의 최대 크기
        self.size = 0  # 현재 스택의 크기

    # 데이터를 스택에 추가하는 함수
    def push(self, data):
        # 스택이 가득 찼는지 확인
        if self.is_full():
            raise Exception("Stack Overflow")
        
        # 새로운 노드 생성
        temp = Node(data)
        temp.next = self.top  # 새로운 노드의 다음 노드를 현재 top으로 설정
        self.top = temp  # top을 새로운 노드로 업데이트
        self.size += 1  # 스택 크기 증가

    # 스택이 비어있는지 확인하는 함수
    def isEmpty(self):
        return self.top is None

    # 스택이 가득 찼는지 확인하는 함수
    def is_full(self):
        return self.size == self.max_size

    # 스택의 최상단 데이터를 확인하는 함수
    def peek(self):
        if self.isEmpty():
            raise Exception("Stack is empty")
        return self.top.data  # 최상단 데이터 반환

    # 스택의 최상단 데이터를 제거하는 함수
    def pop(self):
        if self.isEmpty():
            raise Exception("Stack Underflow")
        self.size -= 1  # 스택 크기 감소
        self.top = self.top.next  # top을 다음 노드로 업데이트

    # 스택의 모든 데이터를 출력하는 함수
    def display(self):
        temp = self.top
        if temp is None:
            raise Exception("Stack Underflow")
        else:
            while temp:
                print(temp.data, end=" -> " if temp.next else "\n")  # 노드 데이터 출력
                temp = temp.next  # 다음 노드로 이동

if __name__ == "__main__":
    # 최대 크기가 4인 스택 생성
    s = Stack(4)

    # 스택에 데이터 추가
    s.push('a')
    s.push('b')
    s.push('c')
    s.push('d')

    # 스택 데이터 출력
    s.display()

    # 스택의 최상단 데이터 출력
    print("Top element is", s.peek())

    # 스택의 최상단 데이터 제거
    s.pop()
    s.pop()

    # 스택 데이터 출력
    s.display()

    # 스택의 최상단 데이터 출력
    print("Top element is", s.peek())

######################### 외부 함수들로 구현하기 #########################
# # 노드를 나타내는 클래스
# class Node:
#     # 노드 초기화
#     def __init__(self, data):
#         self.data = data  # 노드의 데이터 부분
#         self.next = None  # 다음 노드를 가리키는 포인터


# # 스택 초기화
# def init_stack(max_size=float('inf')):
#     return {'top': None, 'max_size': max_size, 'size': 0}


# # 데이터를 스택에 추가하는 함수
# def push(stack, data):
#     # 스택이 가득 찼는지 확인
#     if stack['size'] == stack['max_size']:
#         raise Exception("Stack Overflow")
    
#     # 새로운 노드 생성
#     temp = Node(data)
#     temp.next = stack['top']
#     stack['top'] = temp
#     stack['size'] += 1


# # 스택이 비어있는지 확인하는 함수
# def is_empty(stack):
#     return stack['top'] is None


# # 스택의 최상단 데이터를 확인하는 함수
# def peek(stack):
#     if is_empty(stack):
#         raise Exception("Stack is empty")
#     return stack['top'].data


# # 스택의 최상단 데이터를 제거하는 함수
# def pop(stack):
#     if is_empty(stack):
#         raise Exception("Stack Underflow")
#     stack['size'] -= 1
#     stack['top'] = stack['top'].next


# # 스택의 모든 데이터를 출력하는 함수
# def display(stack):
#     temp = stack['top']
#     while temp:
#         print(temp.data, end=" -> " if temp.next else "\n")
#         temp = temp.next


# if __name__ == "__main__":
#     # 최대 크기가 4인 스택 생성
#     s = init_stack(4)

#     # 스택에 데이터 추가
#     push(s, 'a')
#     push(s, 'b')
#     push(s, 'c')
#     push(s, 'd')

#     # 스택 데이터 출력
#     display(s)

#     # 스택의 최상단 데이터 출력
#     print("Top element is", peek(s))

#     # 스택의 최상단 데이터 제거
#     pop(s)
#     pop(s)

#     # 스택 데이터 출력
#     display(s)

#     # 스택의 최상단 데이터 출력
#     print("Top element is", peek(s))
