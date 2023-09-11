class Stack:
    def __init__(self, max_size=100):
        self.MAX_SIZE = max_size  # 최대 스택 크기
        self.storage = [None] * self.MAX_SIZE  # 데이터를 저장할 리스트
        self.top = -1  # 현재 스택의 최상단 위치

    def is_full(self):
        """스택이 가득 찼는지 확인하는 메서드"""
        return self.top == self.MAX_SIZE - 1

    def is_empty(self):
        """스택이 비어 있는지 확인하는 메서드"""
        return self.top == -1

    def push(self, item):
        """아이템을 스택에 푸시"""
        if self.is_full():
            raise Exception("스택이 가득 찼습니다.")
        self.top += 1
        self.storage[self.top] = item

    def pop(self):
        """스택의 최상단에서 아이템을 팝 (읽기 및 제거)"""
        if self.is_empty():
            raise Exception("스택이 비어있습니다.")
        target = self.storage[self.top]
        self.storage[self.top] = None  # Optional: Clear the popped value
        self.top -= 1
        return target

    def peek(self):
        """스택의 최상단 아이템을 읽음 (제거 없이)"""
        if self.is_empty():
            raise Exception("스택이 비어있습니다.")
        return self.storage[self.top]

if __name__ == "__main__":
    stack = Stack()

    stack.push(10)
    stack.push(20)
    stack.push(30)

    print(stack.peek())  # 30
    print(stack.pop())   # 30
    print(stack.peek())  # 20


########################## 외부 함수로 구현 ########################
# def create_stack(max_size=100):
#     return {'storage': [None] * max_size, 'top': -1, 'max_size': max_size}

# def is_full(stack):
#     """스택이 가득 찼는지 확인"""
#     return stack['top'] == stack['max_size'] - 1

# def is_empty(stack):
#     """스택이 비어 있는지 확인"""
#     return stack['top'] == -1

# def push(stack, item):
#     """아이템을 스택에 푸시"""
#     if is_full(stack):
#         raise Exception("스택이 가득 찼습니다.")
#     stack['top'] += 1
#     stack['storage'][stack['top']] = item

# def pop(stack):
#     """스택의 최상단에서 아이템을 팝 (읽기 및 제거)"""
#     if is_empty(stack):
#         raise Exception("스택이 비어있습니다.")
#     target = stack['storage'][stack['top']]
#     stack['storage'][stack['top']] = None
#     stack['top'] -= 1
#     return target

# def peek(stack):
#     """스택의 최상단 아이템을 읽음 (제거 없이)"""
#     if is_empty(stack):
#         raise Exception("스택이 비어있습니다.")
#     return stack['storage'][stack['top']]
