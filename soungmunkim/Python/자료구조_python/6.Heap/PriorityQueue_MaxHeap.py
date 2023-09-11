class PriorityQueue:
    def __init__(self):
        # 우선순위 큐를 위한 리스트 초기화
        self.queue = []

    def _swap(self, i, j):
        # 두 인덱스에 있는 요소의 값을 교환
        self.queue[i], self.queue[j] = self.queue[j], self.queue[i]

    def _sift_up(self, idx):
        # 현재 요소를 위로 올려 우선순위 큐의 조건을 만족시키는 함수
        parent_idx = (idx - 1) // 2
        while idx > 0 and self.queue[idx] > self.queue[parent_idx]:
            self._swap(idx, parent_idx)
            idx = parent_idx
            parent_idx = (idx - 1) // 2

    def _sift_down(self, idx):
        # 현재 요소를 아래로 내려 우선순위 큐의 조건을 만족시키는 함수
        child_idx = 2 * idx + 1
        while child_idx < len(self.queue):
            # 오른쪽 자식이 존재하며 왼쪽 자식보다 큰 경우
            if child_idx + 1 < len(self.queue) and self.queue[child_idx] < self.queue[child_idx + 1]:
                child_idx += 1
            if self.queue[child_idx] > self.queue[idx]:
                self._swap(child_idx, idx)
                idx = child_idx
                child_idx = 2 * idx + 1
            else:
                break

    def push(self, val):
        # 값을 우선순위 큐에 추가
        self.queue.append(val)
        self._sift_up(len(self.queue) - 1)

    def pop(self):
        # 우선순위 큐의 최상위 값을 제거하고 반환
        if self.is_empty():
            raise Exception("Queue is empty")
        removed = self.queue[0]
        self._swap(0, len(self.queue) - 1)
        self.queue.pop()
        self._sift_down(0)
        return removed

    def peek(self):
        # 우선순위 큐의 최상위 값을 확인하지만 제거하지 않음
        if self.is_empty():
            raise Exception("Queue is empty")
        return self.queue[0]

    def is_empty(self):
        # 우선순위 큐가 비어 있는지 확인
        return len(self.queue) == 0

    def size(self):
        # 우선순위 큐의 크기 반환
        return len(self.queue)


# 사용 예시
if __name__ == "__main__":
    pq = PriorityQueue()
    pq.push(3)
    pq.push(5)
    pq.push(2)
    print("Top element:", pq.peek())
    print("Popped element:", pq.pop())
    print("Top element after pop:", pq.peek())
