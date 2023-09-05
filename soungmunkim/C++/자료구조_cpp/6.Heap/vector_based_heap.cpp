// maxheap 구현
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
using namespace std;

// 최대 힙 노드를 저장할 데이터 구조
struct PriorityQueue
{
private:
    // 힙 요소를 저장할 Vector
    vector<int> A;
 
    // `A[i]`의 부모를 반환
    // `i`가 이미 루트 노드인 경우 이 함수를 호출하지 마십시오.
    int PARENT(int i) {
        return (i - 1) / 2;
    }
 
    // `A[i]`의 왼쪽 자식 반환
    int LEFT(int i) {
        return (2*i + 1);
    }
 
    // `A[i]`의 오른쪽 자식 반환
    int RIGHT(int i) {
        return (2*i + 2);
    }
 
    // 재귀적 heapify-down 알고리즘.
    // 인덱스 `i`에 있는 노드와 두 개의 직계 자식
    // 힙 속성 위반
    void heapify_down(int i)
    {
        // 인덱스 `i`에 있는 노드의 왼쪽 및 오른쪽 자식 가져오기
        int left = LEFT(i);
        int right = RIGHT(i);
 
        int largest = i;
 
        // `A[i]`를 왼쪽 및 오른쪽 자식과 비교
        // 그리고 가장 큰 값을 찾습니다.
        if (left < size() && A[left] > A[i]) {
            largest = left;
        }
 
        if (right < size() && A[right] > A[largest]) {
            largest = right;
        }
 
        // 더 큰 값을 가진 자식으로 교환하고
        // 자식에 대해 heapify-down 호출
        if (largest != i)
        {
            swap(A[i], A[largest]);
            heapify_down(largest);
        }
    }
 
    // 재귀적 heapify-up 알고리즘
    void heapify_up(int i)
    {
        // 인덱스 `i`에 있는 노드와 그 부모가 힙 속성을 위반하는지 확인합니다.
        if (i && A[PARENT(i)] < A[i])
        {
            // 힙 속성이 위반되면 둘을 교환합니다.
            swap(A[i], A[PARENT(i)]);
 
            // 부모에서 heapify-up 호출
            heapify_up(PARENT(i));
        }
    }
 
public:
    // 힙 크기 반환
    unsigned int size() {
        return A.size();
    }
 
    // 힙이 비어있는지 확인하는 함수
    bool empty() {
        return size() == 0;
    }
 
    // 힙에 키 삽입
    void push(int key)
    {
        // Vector의 끝에 새로운 요소를 삽입
        A.push_back(key);
 
        // 요소 인덱스를 가져오고 heapify-up 프로시저를 호출합니다.
        int index = size() - 1;
        heapify_up(index);
    }
 
    // 우선순위가 가장 높은 요소를 제거하는 함수(루트에 있음)
    void pop()
    {
        try {
            // 힙에 요소가 없으면 예외를 던집니다.
            if (size() == 0)
            {
                throw out_of_range("Vector<X>::at() : "
                        "index is out of range(Heap underflow)");
            }
 
            // 힙의 루트를 마지막 요소로 바꿉니다.
            // Vector의
            A[0] = A.back();
            A.pop_back();
 
            // 루트 노드에서 heapify-down 호출
            heapify_down(0);
        }
        // 예외를 잡아서 출력
        catch (const out_of_range &oor) {
            cout << endl << oor.what();
        }
    }
 
    // 우선순위가 가장 높은 요소를 반환하는 함수(루트에 있음)
    int top()
    {
        try {
            // 힙에 요소가 없으면 예외를 던집니다.
            if (size() == 0)
            {
                throw out_of_range("Vector<X>::at() : "
                        "index is out of range(Heap underflow)");
            }
 
            // 그렇지 않으면 맨 위(첫 번째) 요소를 반환합니다.
            return A.at(0);        // 또는 return A[0];
        }
        // 예외를 잡아서 출력
        catch (const out_of_range &oor) {
            cout << endl << oor.what();
        }
    }
};
 
// C++에서 최대 힙 구현
int main()
{
    PriorityQueue pq;
 
    // 참고: 요소의 값이 우선 순위를 결정합니다.
 
    pq.push(3);
    pq.push(2);
    pq.push(15);
 
    cout << "Size is " << pq.size() << endl;
 
    cout << pq.top() << " ";
    pq.pop();
 
    cout << pq.top() << " ";
    pq.pop();
 
    pq.push(5);
    pq.push(4);
    pq.push(45);
 
    cout << endl << "Size is " << pq.size() << endl;
 
    cout << pq.top() << " ";
    pq.pop();
 
    cout << pq.top() << " ";
    pq.pop();
 
    cout << pq.top() << " ";
    pq.pop();
 
    cout << pq.top() << " ";
    pq.pop();
 
    cout << endl << boolalpha << pq.empty();
 
    pq.top();    // 빈 힙에 대한 최상위 작업
    pq.pop();    // 빈 힙에 대한 팝 작업
 
    return 0;
}
