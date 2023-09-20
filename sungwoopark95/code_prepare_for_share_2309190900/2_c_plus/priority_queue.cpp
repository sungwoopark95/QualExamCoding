#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// 우선순위와 데이터를 저장하는 구조체를 정의합니다.
struct Entry {
    int priority;
    string data;

    // 우선순위가 높은 엔트리가 먼저 나오도록 연산자를 오버로딩합니다.
    bool operator<(const Entry& rhs) const {
        return priority < rhs.priority;
    }
};

int main() {
    // 우선순위 큐를 생성합니다.
    priority_queue<Entry> pq;

    // 데이터를 추가합니다.
    pq.push({3, "Apple"});
    pq.push({1, "Banana"});
    pq.push({2, "Cherry"});

    // 우선순위가 가장 높은 데이터부터 꺼냅니다.
    while (!pq.empty()) {
        Entry entry = pq.top();
        pq.pop();
        cout << entry.priority << " " << entry.data << "\n";
    }

    return 0;
}