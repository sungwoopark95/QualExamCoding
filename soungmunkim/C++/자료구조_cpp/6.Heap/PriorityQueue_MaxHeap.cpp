#include <iostream>
#include <vector>

class PriorityQueue {  // 우선순위 큐 클래스 정의
private:
    std::vector<int> queue;  // 큐를 위한 동적 배열

    void swap(int i, int j) {  // 두 인덱스에 있는 요소의 값을 교환
        std::swap(queue[i], queue[j]);
    }

    void siftUp(int idx) {  // 현재 요소를 위로 올려 큐의 조건을 만족시키는 함수
        int parentIdx = (idx - 1) / 2;  // 부모 노드의 인덱스 계산
        while (idx > 0 && queue[idx] > queue[parentIdx]) {  // 현재 요소가 부모보다 크면
            swap(idx, parentIdx);  // 현재 요소와 부모의 값을 교환
            idx = parentIdx;  // 현재 요소를 부모로 설정
            parentIdx = (idx - 1) / 2;  // 부모 노드의 인덱스 다시 계산
        }
    }

    void siftDown(int idx) {  // 현재 요소를 아래로 내려 큐의 조건을 만족시키는 함수
        int childIdx = 2 * idx + 1;  // 왼쪽 자식의 인덱스 계산
        while (childIdx < queue.size()) {  // 자식이 존재하는 동안
            if (childIdx + 1 < queue.size() && queue[childIdx] < queue[childIdx + 1]) {  // 오른쪽 자식이 존재하며 왼쪽 자식보다 큰 경우
                childIdx++;  // 오른쪽 자식을 선택
            }
            if (queue[childIdx] > queue[idx]) {  // 자식이 현재 요소보다 큰 경우
                swap(childIdx, idx);  // 자식과 현재 요소 교환
                idx = childIdx;  // 현재 요소를 자식으로 설정
                childIdx = 2 * idx + 1;  // 다음 왼쪽 자식의 인덱스 계산
            } else {
                break;  // 큐의 조건을 만족하면 종료
            }
        }
    }

public:
    void push(int val) {  // 값을 큐에 추가
        queue.push_back(val);  // 값을 배열 끝에 추가
        siftUp(queue.size() - 1);  // 조건 만족을 위해 siftUp 실행
    }

    int pop() {  // 큐의 최상위 값을 제거하고 반환
        if (isEmpty()) {  // 큐가 비어있는 경우 예외 처리
            throw std::runtime_error("Queue is empty");
        }
        int removed = queue[0];  // 제거될 값 저장
        swap(0, queue.size() - 1);  // 첫 요소와 마지막 요소 교환
        queue.pop_back();  // 마지막 요소 제거
        siftDown(0);  // 조건 만족을 위해 siftDown 실행
        return removed;  // 제거된 값 반환
    }

    int peek() {  // 큐의 최상위 값을 확인하지만 제거하지 않음
        if (isEmpty()) {  // 큐가 비어있는 경우 예외 처리
            throw std::runtime_error("Queue is empty");
        }
        return queue[0];  // 첫 요소 반환
    }

    bool isEmpty() const {  // 큐가 비어 있는지 확인
        return queue.empty();
    }

    size_t size() const {  // 큐의 크기 반환
        return queue.size();
    }
};

int main() {  // 메인 함수
    PriorityQueue pq;  // 우선순위 큐 객체 생성
    pq.push(3);  // 값 추가
    pq.push(5);
    pq.push(2);
    std::cout << "Top element: " << pq.peek() << std::endl;  // 최상위 값 출력
    std::cout << "Popped element: " << pq.pop() << std::endl;   // 최상위 값 제거 후 출력
    std::cout << "Top element after pop: " << pq.peek() << std::endl;  // 제거 후 최상위 값 출력
    return 0;
}
