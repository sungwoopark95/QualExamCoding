/*
[Bubble sort 구현하기]
Bubble Sort: 인접한 두 원소의 순서가 바뀌어 있을 때 (앞의 원소가 뒤의 원소보다 클 때) 서로 swap하면서 정렬하는 알고리즘
정수로 이루어진 리스트(list)를 변수(argument)로 받아 버블 정렬할 때, swap이 일어나는 횟수를 리턴하는 함수를 작성하시오.

g++ -std=c++17 SPDS1_HW3_1_BubbleSort_SM.cpp -o BubbleSort
*/

#include<stdio.h>
#include<iostream>
#include<sstream>
#include<string>
#include<vector>

using namespace std;

// swap은 무조건 주소값으로 접근! 함수 끝나도 바꾼 값 유지 
// int &a처럼 함수 인자를 바로 넘겨주는 것은 C++에서만 가능
void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

// int* arr사용해도 됨! (array가 pointer 자체)
// 오른차순 정렬
void bubble_sort(vector<int>& arr, int n){
    int i, j;
    for (i=0; i<n; i++){
        for (j=0; j<n-i-1; j++){
            if (arr[j] > arr[j+1])
                // swap(arr+j, arr+j+1);
                swap(arr[j], arr[j+1]);  
                
        }
    }
}

// // 내림차순 정렬
// void bubble_sort(vector<int>& arr, int n) {
//     for (int i=0;i<n;i++) {
//         for (int j=0;j<n-i-1;j++) {
//             if (arr[j] < arr[j+1]) {
//                 swap(arr[j], arr[j+1]);
//             }
//         }
//     }
// }

int main() {
    // 직접 초기화된 배열
    vector<int> arr = {4, 2, 2, 8, 3, 3, 1};
    int size = arr.size();

    bubble_sort(arr, size);

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

    bubble_sort(arr, size);

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

    bubble_sort(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
*/