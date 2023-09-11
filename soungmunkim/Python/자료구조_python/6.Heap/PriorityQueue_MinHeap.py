class PriorityQueue:
    def __init__(self):
        # 큐를 위한 리스트 초기화
        self.queue = []

    def insert(self, data):
        # 데이터를 리스트 끝에 추가
        self.queue.append(data)
        index = len(self.queue) - 1  # 추가된 데이터의 인덱스

        # 추가된 데이터가 부모노드보다 작은지 확인
        while index > 0:
            parent_index = (index - 1) // 2  # 부모 노드의 인덱스 계산
            if self.queue[index] < self.queue[parent_index]:
                self.queue[index], self.queue[parent_index] = self.queue[parent_index], self.queue[index]  # 부모 노드와 값 교환
                index = parent_index  # 인덱스를 부모 노드의 인덱스로 변경
            else:
                break  # min-heap 속성을 만족하면 중지

    def extract_min(self):
        # 큐가 비어있는 경우 에러 메시지 출력
        if not self.queue:
            raise Exception("The queue is empty!")

        min_val = self.queue[0]  # 최소값 저장
        self.queue[0] = self.queue[-1]  # 마지막 값을 첫 번째 위치로 이동
        self.queue.pop()  # 마지막 값을 제거
        index = 0

        # min-heap 속성을 유지하면서 노드를 조정
        while True:
            left_child_index = 2 * index + 1  # 왼쪽 자식의 인덱스
            right_child_index = 2 * index + 2  # 오른쪽 자식의 인덱스

            # 두 자식 중 더 작은 자식을 찾음
            if left_child_index < len(self.queue) and right_child_index < len(self.queue):
                swap_index = left_child_index if self.queue[left_child_index] < self.queue[right_child_index] else right_child_index
            elif left_child_index < len(self.queue):
                swap_index = left_child_index
            else:
                break  # 자식이 없으면 중지

            if self.queue[index] > self.queue[swap_index]:
                self.queue[index], self.queue[swap_index] = self.queue[swap_index], self.queue[index]  # 노드와 자식 교환
                index = swap_index  # 인덱스를 교환한 자식의 인덱스로 변경
            else:
                break  # min-heap 속성을 만족하면 중지

        return min_val  # 최소값 반환

    def is_empty(self):
        # 큐가 비어있는지 확인
        return len(self.queue) == 0
