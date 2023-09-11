#include <iostream>
#include <vector>

class MaxHeap {  // 최대 힙 클래스 정의
private:
    std::vector<int> heap;  // 힙을 위한 동적 배열

    void swap(int i, int j) {  // 두 인덱스에 있는 요소의 값을 교환
        std::swap(heap[i], heap[j]);
    }

    void siftUp(int idx) {  // 현재 요소를 위로 올려 힙 조건을 만족시키는 함수
        int parentIdx = (idx - 1) / 2;  // 부모 노드의 인덱스 계산
        while (idx > 0 && heap[idx] > heap[parentIdx]) {  // 현재 노드 값이 부모보다 큰 동안
            swap(idx, parentIdx);  // 현재 노드와 부모 노드 값을 교환
            idx = parentIdx;  // 현재 노드를 부모 노드로 설정
            parentIdx = (idx - 1) / 2;  // 부모 노드의 인덱스를 다시 계산
        }
    }

    void siftDown(int idx) {  // 현재 요소를 아래로 내려 힙 조건을 만족시키는 함수
        int childIdx = 2 * idx + 1;  // 왼쪽 자식 노드의 인덱스 계산
        while (childIdx < heap.size()) {  // 자식 노드가 존재하는 동안
            if (childIdx + 1 < heap.size() && heap[childIdx] < heap[childIdx + 1]) {  // 오른쪽 자식이 존재하고, 왼쪽 자식보다 값이 큰 경우
                childIdx++;  // 오른쪽 자식으로 설정
            }
            if (heap[childIdx] > heap[idx]) {  // 현재 노드 값보다 자식 노드 값이 큰 경우
                swap(childIdx, idx);  // 현재 노드와 자식 노드 값을 교환
                idx = childIdx;  // 현재 노드를 자식 노드로 설정
                childIdx = 2 * idx + 1;  // 다음 왼쪽 자식 노드의 인덱스 계산
            } else {
                break;  // 힙 조건 만족시 반복 종료
            }
        }
    }

public:
    MaxHeap() {}  // 기본 생성자

    void push(int val) {  // 힙에 값을 추가하는 함수
        heap.push_back(val);  // 값 추가
        siftUp(heap.size() - 1);  // 조건 만족을 위해 siftUp 실행
    }

    int pop() {  // 힙의 최대 값을 제거하고 반환하는 함수
        if (isEmpty()) {  // 힙이 비어 있을 경우 예외 처리
            throw std::runtime_error("Heap is empty");
        }
        int removed = heap[0];  // 제거될 값 저장
        swap(0, heap.size() - 1);  // 루트와 마지막 요소 교환
        heap.pop_back();  // 마지막 요소 제거
        siftDown(0);  // 조건 만족을 위해 siftDown 실행
        return removed;  // 제거된 값 반환
    }

    int peek() {  // 힙의 최대 값을 확인하는 함수
        if (isEmpty()) {  // 힙이 비어 있을 경우 예외 처리
            throw std::runtime_error("Heap is empty");
        }
        return heap[0];  // 루트 값 반환
    }

    bool isEmpty() const {  // 힙이 비어 있는지 확인하는 함수
        return heap.empty();
    }

    size_t size() const {  // 힙의 크기를 반환하는 함수
        return heap.size();
    }
};

int main() {  // 메인 함수
    MaxHeap max_heap;  // 최대 힙 객체 생성
    max_heap.push(1);  // 값 추가
    max_heap.push(5);
    max_heap.push(3);
    std::cout << "Heap size: " << max_heap.size() << std::endl;  // 힙의 크기 출력
    std::cout << "Top element: " << max_heap.peek() << std::endl;  // 루트 값 출력
    std::cout << "Popped element: " << max_heap.pop() << std::endl;  // 루트 값 제거 후 출력
    std::cout << "Heap size after pop: " << max_heap.size() << std::endl;  // 제거 후 힙의 크기 출력
    return 0;
}