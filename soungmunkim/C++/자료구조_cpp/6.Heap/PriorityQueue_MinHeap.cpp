#include <iostream>
#include <vector>

class PriorityQueue {  // 우선순위 큐 클래스 정의
private:
    std::vector<int> queue;  // 큐를 위한 동적 배열

public:
    // 요소를 삽입할 때 min-heap 속성을 유지
    void insert(int data) {
        queue.push_back(data);  // 데이터를 배열 끝에 추가
        int index = queue.size() - 1;  // 추가된 데이터의 인덱스
        
        // 추가된 데이터가 부모노드보다 작은지 확인
        while (index > 0) {
            int parent_index = (index - 1) / 2;  // 부모 노드의 인덱스 계산
            if (queue[index] < queue[parent_index]) {
                std::swap(queue[index], queue[parent_index]);  // 부모 노드와 값 교환
                index = parent_index;  // 인덱스를 부모 노드의 인덱스로 변경
            } else {
                break;  // min-heap 속성을 만족하면 중지
            }
        }
    }

    // 최소값 추출
    int extract_min() {
        if (queue.empty()) {  // 큐가 비어있는 경우 에러 메시지 출력
            std::cerr << "The queue is empty!" << std::endl;
            return -1;
        }

        int min_val = queue[0];  // 최소값 저장
        queue[0] = queue.back();  // 마지막 값을 첫 번째 위치로 이동
        queue.pop_back();  // 마지막 값을 제거
        int index = 0;
        int length = queue.size();

        // min-heap 속성을 유지하면서 노드를 조정
        while (true) {
            int left_child_index = 2 * index + 1;  // 왼쪽 자식의 인덱스
            int right_child_index = 2 * index + 2;  // 오른쪽 자식의 인덱스
            int swap_index;

            // 두 자식 중 더 작은 자식을 찾음
            if (left_child_index < length && right_child_index < length) {
                if (queue[left_child_index] < queue[right_child_index]) {
                    swap_index = left_child_index;
                } else {
                    swap_index = right_child_index;
                }
            } else if (left_child_index < length) {
                swap_index = left_child_index;
            } else {
                break;  // 자식이 없으면 중지
            }

            if (queue[index] > queue[swap_index]) {
                std::swap(queue[index], queue[swap_index]);  // 노드와 자식 교환
                index = swap_index;  // 인덱스를 교환한 자식의 인덱스로 변경
            } else {
                break;  // min-heap 속성을 만족하면 중지
            }
        }

        return min_val;  // 최소값 반환
    }

    bool is_empty() {
        return queue.empty();  // 큐가 비어있는지 확인
    }
};
