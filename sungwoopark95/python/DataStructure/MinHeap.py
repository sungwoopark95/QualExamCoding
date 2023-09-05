from typing import List

class MinHeap:
    def __init__(self) -> None:
        self.heap = []
        
    def getSize(self) -> int:
        return len(self.heap)
    
    def getHeap(self) -> List:
        return self.heap
    
    def isEmpty(self) -> bool:
        return self.getSize() == 0

    def __min_heapify(self, array:List, root:int, last:int) -> None:
        smallest = root
        left_child = (2 * root) + 1
        right_child = (2 * root) + 2

        # check if there is any child whose value is smaller than the parent
        if left_child < last and array[left_child] < array[smallest]:
            smallest = left_child
        if right_child < last and array[right_child] < array[smallest]:
            smallest = right_child
        
        # if smaller child exists, change
        if smallest != root:
            array[root], array[smallest] = array[smallest], array[root]
            # recursively modify the affected subtree
            self.__min_heapify(array, smallest, last)

    def build_heap(self) -> None:
        for i in range(self.getSize()//2-1, -1, -1):
            self.__min_heapify(self.heap, i, self.getSize())
    
    def push(self, val):
        self.heap.append(val)
        self.build_heap()
    
    def pop(self):
        if self.isEmpty():
            return None
        # return the minimum value
        value = self.heap.pop(0)
        self.build_heap()
        return value
    
if __name__ == "__main__":
    h = MinHeap()
    
    h.push(10)
    h.push(2)
    h.push(11)
    h.push(7)
    h.push(20)
    h.push(3)
    
    while not h.isEmpty():
        print(f"Heap : {h.getHeap()}\tPopped : {h.pop()}")