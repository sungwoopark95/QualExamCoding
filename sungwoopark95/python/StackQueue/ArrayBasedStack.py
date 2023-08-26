# array 기반의 stack
class Stack:
    def __init__(self):
        self.size = 0
        self.stack = []
    
    def size(self):
        return self.size
    
    def isEmpty(self):
        return self.size == 0
    
    def push(self, item):
        self.stack.append(item)
        self.size += 1
    
    def pop(self):
        if self.isEmpty():
            return None
        item = self.stack.pop(-1)
        self.size -= 1
        return item
    
    def top(self):
        if self.isEmpty():
            return None
        return self.stack[-1]
