class MinHeap:
    def __init__(self):
        # 힙을 리스트로 초기화
        self.heap = []

    def _swap(self, i, j):
        # 두 인덱스에 있는 요소의 값을 교환
        self.heap[i], self.heap[j] = self.heap[j], self.heap[i]

    def _sift_up(self, idx):
        # 현재 요소를 위로 올려 힙 조건을 만족시키는 함수
        parent_idx = (idx - 1) // 2
        while idx > 0 and self.heap[idx] < self.heap[parent_idx]:
            self._swap(idx, parent_idx)
            idx = parent_idx
            parent_idx = (idx - 1) // 2

    def _sift_down(self, idx):
        # 현재 요소를 아래로 내려 힙 조건을 만족시키는 함수
        child_idx = 2 * idx + 1
        while child_idx < len(self.heap):
            # 오른쪽 자식이 존재하고, 왼쪽 자식보다 값이 작은 경우
            if child_idx + 1 < len(self.heap) and self.heap[child_idx] > self.heap[child_idx + 1]:
                child_idx += 1
            if self.heap[child_idx] < self.heap[idx]:
                self._swap(child_idx, idx)
                idx = child_idx
                child_idx = 2 * idx + 1
            else:
                break

    def push(self, val):
        # 힙에 값을 추가하는 함수
        self.heap.append(val)
        self._sift_up(len(self.heap) - 1)

    def pop(self):
        # 힙의 최소 값을 제거하고 반환하는 함수
        if self.is_empty():
            raise Exception("Heap is empty")
        removed = self.heap[0]
        self._swap(0, len(self.heap) - 1)
        self.heap.pop()
        self._sift_down(0)
        return removed

    def peek(self):
        # 힙의 최소 값을 확인하는 함수
        if self.is_empty():
            raise Exception("Heap is empty")
        return self.heap[0]

    def is_empty(self):
        # 힙이 비어 있는지 확인하는 함수
        return len(self.heap) == 0

    def size(self):
        # 힙의 크기를 반환하는 함수
        return len(self.heap)


# 사용 예시
if __name__ == "__main__":
    min_heap = MinHeap()
    min_heap.push(3)
    min_heap.push(1)
    min_heap.push(2)
    print("Top element:", min_heap.peek())
    print("Popped element:", min_heap.pop())
    print("Top element after pop:", min_heap.peek())
