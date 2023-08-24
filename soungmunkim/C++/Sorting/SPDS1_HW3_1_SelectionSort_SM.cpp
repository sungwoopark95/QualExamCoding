/*
[selection sort 구현하기]
가장 작은 element를 선택(select)하여 정렬하는 알고리즘
g++ -std=c++17 SPDS1_HW3_1_SelectionSort_SM.cpp -o SelectionSort
*/

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

void selection_sort(vector<int>& arr, int n){
    int i, j, smallest; // initialize smallest
    for(i=0; i<n; i++){
        smallest = i;
        for(j=i; j<n; j++){
            if(arr[j] < arr[smallest])
                smallest = j; // update smallest
        }
        if (arr[smallest] < arr[i])
            swap(arr[i], arr[smallest]);
    }
}

int main() {
    // 직접 초기화된 배열
    vector<int> arr = {4, 2, 2, 8, 3, 3, 1};
    int size = arr.size();

    selection_sort(arr, size);

    cout << "Sorted array: ";
    for (int i : arr) {
        cout << i << " ";
    }

    return 0;
}


/* 사용자로부터 sorting하고 싶은 숫자들을 받았을 때
int main() {
    string input;
    vector<int> arr;

    cout << "Enter the list of numbers in the format [a,b,c,...]: ";
    getline(cin, input);

    // 입력된 문자열 처리
    stringstream ss(input);
    char ch;
    int num;
    int size;


    // ','로 분리하여 숫자들을 추출
    while (ss >> ch >> num && ch == '[' || ch == ',') {
        arr.push_back(num);
    }
    size = arr.size();

    selection_sort(arr, size);

    cout << "Sorted array: ";
    for (int i : arr) {
        cout << i << " ";
    }

    return 0;
}
*/

/* [] 리스트 형태로 사용자에게 input 받았을 때
int main() {
    char input[MAX_SIZE];
    int arr[MAX_SIZE];
    int n = 0; // 배열의 크기

    printf("Enter the list of numbers in the format [a,b,c,...]: ");
    fgets(input, sizeof(input), stdin);

    // 입력된 문자열 처리
    char* token = strtok(input, "[,]"); // '[' 또는 ',' 또는 ']'를 기준으로 문자열 분리
    while (token) {
        arr[n++] = atoi(token); // 문자열을 숫자로 변환하여 배열에 저장
        token = strtok(NULL, "[,]");
    }

    insertionSort(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
*/