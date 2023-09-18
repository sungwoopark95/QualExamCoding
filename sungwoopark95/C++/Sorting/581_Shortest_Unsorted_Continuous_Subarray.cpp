/*
주어진 array에서 "연결된 가장 짧은 subarray"를 찾되, 해당 subarray만 정렬하면 전체 array가 정렬되어야 한다.

Input: nums = [2,6,4,8,10,9,15]
Output: 5
Explanation: [6, 4, 8, 10, 9]만 정렬하면 전체 array가 정렬된다.

Input: nums = [1,2,3,4]
Output: 0

Input: nums = [1]
Output: 0
*/

#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

void Merge(vector<int>& arr, int start, int mid, int last){
    int k = start;
    int len1 = (mid+1) - start; // 첫 번째 부분 리스트의 길이
    int len2 = last - mid; // 두 번째 부분 리스트의 길이
    int sub1[len1]; // 첫 번째 부분 리스트를 저장할 배열
    int sub2[len2]; // 두 번째 부분 리스트를 저장할 배열

    // 첫 번째 부분 리스트의 원소들을 sub1에 복사
    for (int i=0;i<len1;i++) { 
        sub1[i] = arr[start+i]; 
    }

    // 두 번째 부분 리스트의 원소들을 sub2에 복사
    for (int j=0; j<len2; j++) { 
        sub2[j] = arr[mid+1+j]; 
    }

    int m=0; int l=0;
    // sub1과 sub2의 원소들 중 작은 값을 arr에 병합
    while (m < len1 && l < len2) {
        if (sub1[m] > sub2[l]) { 
            arr[k] = sub2[l++]; 
        } else { 
            arr[k] = sub1[m++]; 
        }
        k++;
    }

    // sub1의 모든 원소가 병합되었으면, sub2의 나머지 원소들을 arr에 복사
    if (m == len1) {
        for (int x=l; x<len2; x++) { 
            arr[k++] = sub2[x]; 
        }
    } 
    // sub2의 모든 원소가 병합되었으면, sub1의 나머지 원소들을 arr에 복사
    else {
        for (int x=m; x<len1; x++) { 
            arr[k++] = sub1[x]; 
        }
    }
}

// 재귀적인 병합 정렬 도우미 함수
void MergeHelp(vector<int>& arr, int start, int last) {
    if (start == last) { return; } // 부분 리스트의 길이가 1이면 반환
    int mid = (start+last) / 2; // 중간 위치 계산
    MergeHelp(arr, start, mid); // 첫 번째 부분 리스트 정렬
    MergeHelp(arr, mid+1, last); // 두 번째 부분 리스트 정렬
    
    Merge(arr, start, mid, last); // 두 부분 리스트를 병합
}

// 병합 정렬 메인 함수
vector<int> MergeSort(vector<int>& arr, int n) {
    vector<int> copied;
    for (int i=0;i<arr.size();i++) {
        copied.push_back(arr[i]);
    }
    MergeHelp(copied, 0, n-1); // 병합 정렬 시작
    return copied;
}

int findUnsortedSubarray(vector<int>& nums) {
    vector<int> sorted = MergeSort(nums, nums.size());
    if (nums.size() == 1 || nums == sorted) {
        return 0;
    }

    int max_idx = -1;
    int min_idx = 10000000;
    for (int i=0;i<nums.size();i++) {
        if (nums[i] != sorted[i]) {
            if (min_idx > i) { min_idx = i; }
            if (max_idx < i) { max_idx = i; }
        }
    }

    cout << max_idx << ", " << min_idx << endl;
    return (max_idx - min_idx) + 1;
}

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

    cout << findUnsortedSubarray(arr) << endl;

    return 0;
}