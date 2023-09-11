#include<iostream>
#include<vector>
using namespace std;

int arr[8] = { 9,6,7,5,3,1,4,2 };		//처음 노드를 1로 해야하는데, 어캐해야하지.
										// 0을 미리넣은 vector 생성 및 arr값 복사해서 넣어준후 마지막에 arr값에 정렬된값 복사하자
vector<int> v;

void buildHeap(int* arr, int* end) {	//일단 maxheap의 형태로 만들자.
	int root = 1,parent=1,child=1;
	v.push_back(0);
	for (int i = 0; i < end - arr; i++) {
		v.push_back(arr[i]);
	}
	for (int i = end-arr-1; i >1; i--) {
		child = i;
		parent = child/2;
		while (v[child]> v[parent] && parent!=0) {
			swap(v[child], v[parent]);
			child = parent;
			parent = child / 2;
		}
	}
}

void heapify(int start, int end) {		//start(거의 1)에서 end범위에서 heap을 만들어준다. 제일 큰값이 1의 위치로 오게
	int current = start;				//current커서에 start값 넣어줌
	int leftchild = 2 * current;		//leftchild에 2*current
	int rightchild = 2 * current+1;		//rightchild에 2*current+1

	if (leftchild<=end && v[current ]< v[leftchild]) current = leftchild;		//leftchild 노드값이 end값 넘는 지 체크, current값이 leftchild값보다 작으면 current 커서 옮겨줌
	if (rightchild<=end && v[current] < v[rightchild]) current = rightchild;	//rightchild 노드값이 end값 넘는 지 체크, current값이 rightchild값보다 작으면 current 커서 옮겨줌

	if (start != current) {														//current커서가 움직였다면 parent노드보다 큰 child노드 하나 있는것이므로
		swap(v[start], v[current]);												//해당 current노드 값과 start노드 값 바꿔주고
		heapify(current, end);													//해당 current노드에서부터 다시 heapify시작
	}



}

void heapSort(int*arr,int*end) {
	buildHeap(arr, end);					//max힙의 형태로 만든후
	for (int i = end - arr ; i > 1; i--) {	//맨 마지막 원소부터 2번째 원소까지  
															
		swap(v[1], v[i]);					//i번째 원소와 제일큰원소 바꾼 후,
		heapify(1,i-1);						//제일 큰원소는 정렬 되어 있으므로 정렬된값 제외하고 다시 maxheap으로 만들어주고 반복
	}
	for (int i = 0; i < v.size()-1; i++) {	//정렬된 v값 넣어주기
		arr[i] = v[i + 1];
	}
}

void print() {
	for (int elem : arr) {
		cout << elem << " ";
	}
}


int main() {
	heapSort(arr, arr + 8);
	print();
}