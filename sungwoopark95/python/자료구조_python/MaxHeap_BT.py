class TreeNode:
    def __init__(self, val=0):
        self.val = val  # 노드의 값
        self.left = None    # 왼쪽 자식 노드
        self.right = None   # 오른쪽 자식 노드


class MaxHeap:
    def __init__(self) -> None:
        self.root = None    # 힙의 루트 노드
        self.nodes = []     # 노드 삽입 및 삭제를 위한 노드의 목록
        self.size = 0       # 힙의 크기
    
    def __contains__(self, val) -> bool:
        return self.__search(val)

    def getSize(self) -> int:
        return self.size    # 힙의 크기 반환

    def isEmpty(self) -> bool:
        return self.size == 0  # 힙이 비어있는지 확인
    
    def __search(self, val) -> bool:
        # BFS를 활용해 heap에 해당 value가 있는지 없는지 확인
        if not self.root:
            return False

        queue = [self.root]
        while queue:
            node = queue.pop(0)
            if node.val == val:
                return True
            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)
        return False

    def __max_heapify(self, node: TreeNode) -> None:
        if not node:
            return
        largest = node
        # left child에 값이 있고, 그 값이 parent의 값보다 큰 경우 교환 -> parent에 항상 더 큰 값이 있어야
        if node.left and node.left.val > node.val:
            largest = node.left
        # right child에 값이 있고, 그 값이 parent의 값보다 큰 경우 교환 -> parent에 항상 더 큰 값이 있어야
        if node.right and node.right.val > largest.val:
            largest = node.right

        # 교환의 필요성이 생기면
        if largest != node:
            # 값 교환
            node.val, largest.val = largest.val, node.val
            # 재귀적으로 힙 속성 유지
            self.__max_heapify(largest)

    def push(self, val):
        new_node = TreeNode(val)
        if not self.root:
            self.root = new_node
        else:
            # 새 노드를 올바른 위치에 삽입
            parent = self.nodes[(self.size - 1) // 2]
            if not parent.left:
                parent.left = new_node
            else:
                parent.right = new_node
        self.nodes.append(new_node)
        self.size += 1

        # 아래로 내리며 힙 속성 유지 (down-heap)
        current = new_node
        while current != self.root and current.val > parent.val:
            current.val, parent.val = parent.val, current.val
            current = parent
            parent = self.nodes[(self.nodes.index(current) - 1) // 2]

    def pop(self):
        if self.isEmpty():
            return None

        # 최소값 반환
        value = self.root.val

        # 마지막 노드로 루트 노드 교체
        last_node = self.nodes.pop()
        self.size -= 1
        if self.nodes:
            self.root.val = last_node.val

            # 마지막 노드의 부모에서 마지막 노드 제거
            parent = self.nodes[(self.size - 1) // 2]
            if parent.right:
                parent.right = None
            else:
                parent.left = None

            # 위로 올리며 힙 속성 유지
            self.__max_heapify(self.root)
        else:
            self.root = None
        
        return value


if __name__ == "__main__":
    h = MaxHeap()
    
    h.push(3)
    h.push(4)
    h.push(5)
    h.push(10)
    h.push(2)
    h.push(6)
    h.push(7)
    
    print(f"Is 3 in the heap? : {3 in h}")
    print(f"Is 24 in the heap? : {24 in h}")
        
    is_start = True
    print("Popped : ", end='')
    while not h.isEmpty():
        if not is_start:
            print(" ", end='')
        print(f"{h.pop()}", end='')
        is_start = False
    print()