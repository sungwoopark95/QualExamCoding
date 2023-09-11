from typing import List

## MaxHeap을 사용한 priority queue
class PriorityQueue:
    def __init__(self) -> None:
        self.heap = []

    def __contains__(self, item):
        return item in self.heap

    def getSize(self) -> int:
        return len(self.heap)
    
    def isEmpty(self) -> bool:
        return self.getSize() == 0

    def __max_heapify(self, array:List, root:int, last:int) -> None:
        largest = root
        left_child = (2 * root) + 1
        right_child = (2 * root) + 2

        # check if there is any child whose value is larger than the parent
        if left_child < last and array[left_child] > array[largest]:
            largest = left_child
        if right_child < last and array[right_child] > array[largest]:
            largest = right_child
        
        # if larger child exists, change
        if largest != root:
            array[root], array[largest] = array[largest], array[root]
            # recursively modify the affected subtree
            self.__max_heapify(array, largest, last)

    def build_heap(self) -> None:
        for i in range(self.getSize()//2-1, -1, -1):
            self.__max_heapify(self.heap, i, self.getSize())
    
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
    
    def peek(self):
        if self.isEmpty():
            return None
        return self.heap[0]


if __name__ == "__main__":
    pq = PriorityQueue()
    
    pq.push(4)
    pq.push(5)
    pq.push(10)
    pq.push(2)
    pq.push(6)
    pq.push(7)
    
    print(f"Top element: {pq.peek()}")
    
    is_start = True
    print("Popped : ", end='')
    while not pq.isEmpty():
        if not is_start:
            print(" ", end='')
        print(f"{pq.pop()}", end='')
        is_start = False
    print()