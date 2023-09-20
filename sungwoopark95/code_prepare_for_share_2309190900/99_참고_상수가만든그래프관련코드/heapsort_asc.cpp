// minheap, BOJ 1927
#include <iostream>
#define MAX_SIZE 100002
using namespace std;
int n;

void swap(int &x, int &y){
    int tmp;
    tmp = x;
    x = y;
    y = tmp;
    return;
}

class Heap{
private:
    int heararr[MAX_SIZE];
    int sz;

public:
    Heap() : sz(0) {}
    int getSize(){
        return sz;
    }
    void push(int x){
        heararr[++sz] = x;
        int idx = sz;
        while (idx != 1){
            int par = idx/2;
            if(heararr[par] <= heararr[idx]) break;
            swap(heararr[par], heararr[idx]);
            idx = par;
        }
    }

    int top(){
        return heararr[1];
    }
    void pop(){
        heararr[1] = heararr[sz--]; // 맨 마지막에 있는 것을 가져옴.
        int idx = 1;
        // 왼쪽 자식의 인덱스(=2*idx)가 size보다 크면 idx는 leaf
        while(2*idx <= sz){
            int lc = 2*idx, rc = 2*idx + 1;
            int min_child = lc; // 두자식중 작은 index를 담는다.
            if (rc <= sz & heararr[rc] < heararr[lc]) // rc 가 sz보다 작거나 같다는 것은  rc가 존재함을 의미
                min_child = rc;
            if (heararr[idx] <= heararr[min_child]) break;
            swap(heararr[idx], heararr[min_child]);
            idx = min_child;
        }    
    }
};

void heapSort(Heap &heap, int arr[], int n) {
    // Push all elements to the heap
    for (int i = 0; i < n; i++) {
        heap.push(arr[i]);
    }

    // Pop all elements from the heap into the array
    for (int i = 0; i < n; i++) {
        arr[i] = heap.top();
        heap.pop();
    }
}

int main() {
    int arr[] = {40, 20, 30, 10, 5, 15, 35, 25};
    int n = sizeof(arr) / sizeof(arr[0]);

    Heap heap;

    cout << "Original array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    heapSort(heap, arr, n);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}