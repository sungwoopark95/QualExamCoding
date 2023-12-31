from typing import List

class MaxHeap:
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
    
    print(h.heap)
    
    is_start = True
    print("Popped : ", end='')
    while not h.isEmpty():
        if not is_start:
            print(" ", end='')
        print(f"{h.pop()}", end='')
        is_start = False
    print()