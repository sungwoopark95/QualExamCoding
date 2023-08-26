class ListNode:
    def __init__(self, val):
        self.val = val
        self.next = None

class Stack:
    def __init__(self):
        self.size = 0
        self.top_node = None  # 스택의 최상단 노드를 가리킴
    
    def size(self):
        return self.size
    
    def isEmpty(self):
        return self.size == 0
    
    def push(self, item):
        new_node = ListNode(item)
        # 새로운 노드를 스택의 최상단에 추가
        new_node.next = self.top_node
        self.top_node = new_node
        self.size += 1
    
    def pop(self):
        if self.isEmpty():
            return None
        # 스택의 최상단 노드를 제거하고 반환
        item = self.top_node.val
        self.top_node = self.top_node.next
        self.size -= 1
        return item
    
    def top(self):
        if self.isEmpty():
            return None
        return self.top_node.val
