class Stack:
    def __init__(self):
        self.stack = []
        
    # 원소를 스택에 추가합니다.
    def push(self, value):
        self.stack.append(value)
        
    # 스택의 최상단 원소를 제거하고 반환합니다.
    def pop(self):
        if self.is_empty():
            return None
        return self.stack.pop()
    
    # 스택의 최상단 원소를 반환합니다.
    def peek(self):
        if self.is_empty():
            return None
        return self.stack[-1]
    
    # 스택이 비어있는지 확인합니다.
    def is_empty(self):
        return len(self.stack) == 0
    
    # 스택에 저장된 원소의 개수를 반환합니다.
    def size(self):
        return len(self.stack)
    
    # 특정 원소가 스택에 포함되어 있는지 확인합니다.
    def contains(self, element):
        return element in self.stack

# 사용 예시
s = Stack()
s.push(1)
s.push(2)
s.push(3)
print(s.contains(2))  # True
print(s.contains(4))  # False
