/*
[앞 중간 뒤 Queue 디자인]
Design a queue that supports push and pop operations in the front, middle, and back.

Implement the FrontMiddleBack class:

FrontMiddleBack() Initializes the queue.
void pushFront(int val) Adds val to the front of the queue.
void pushMiddle(int val) Adds val to the middle of the queue.
void pushBack(int val) Adds val to the back of the queue.
int popFront() Removes the front element of the queue and returns it. If the queue is empty, return -1.
int popMiddle() Removes the middle element of the queue and returns it. If the queue is empty, return -1.
int popBack() Removes the back element of the queue and returns it. If the queue is empty, return -1.
Notice that when there are two middle position choices, the operation is performed on the frontmost middle position choice. For example:

Pushing 6 into the middle of [1, 2, 3, 4, 5] results in [1, 2, 6, 3, 4, 5].
Popping the middle from [1, 2, 3, 4, 5, 6] returns 3 and results in [1, 2, 4, 5, 6].
 

Example 1:

Input:
["FrontMiddleBackQueue", "pushFront", "pushBack", "pushMiddle", "pushMiddle", "popFront", "popMiddle", "popMiddle", "popBack", "popFront"]
[[], [1], [2], [3], [4], [], [], [], [], []]
Output:
[null, null, null, null, null, 1, 3, 4, 2, -1]

Explanation:
FrontMiddleBackQueue q = new FrontMiddleBackQueue();
q.pushFront(1);   // [1]
q.pushBack(2);    // [1, 2]
q.pushMiddle(3);  // [1, 3, 2]
q.pushMiddle(4);  // [1, 4, 3, 2]
q.popFront();     // return 1 -> [4, 3, 2]
q.popMiddle();    // return 3 -> [4, 2]
q.popMiddle();    // return 4 -> [2]
q.popBack();      // return 2 -> []
q.popFront();     // return -1 -> [] (The queue is empty)

*/


#include <vector>
#include <iostream>

using namespace std;

class FrontMiddleBackQueue {
public:
    FrontMiddleBackQueue() { }

    vector<int> q;
    
    void pushFront(int val) {
        q.insert(q.begin(), val);
    }
    
    void pushMiddle(int val) {
        q.insert(q.begin() + getMiddleIndex(q.size()+1), val);
    }
    
    void pushBack(int val) {
        q.push_back(val);
    }
    
    int popFront() {
        if (q.empty()) return -1;
        
        int val = q.front();
        q.erase(q.begin());
        
        return val;
    }
    
    int popMiddle() {
        if (q.empty()) return -1;
        
        int middle = getMiddleIndex(q.size());
        int val = q[middle];
        q.erase(q.begin() + middle);
        
        return val; 
    }
    
    int popBack() {
        if (q.empty()) return -1;
        
        int val = q.back();
        q.pop_back();
        
        return val;
    }

private:
    int getMiddleIndex(int length) {
        if (length % 2 == 0) {
            return length / 2-1;
        } else {
            return length / 2;
        }
    }
};
