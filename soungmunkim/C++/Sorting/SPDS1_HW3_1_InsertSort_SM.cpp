/*
[Insertion Sort 구현]

- 정렬되지 않은 데이터를 이미 정렬된 부분의 적절한 위치에 "삽입"하는 방식으로 동작하는 정렬 알고리즘
- 첫 번째 원소는 항상 정렬되어 있다고 가정한다.
- 두 번째 원소(`i=1`)부터 array를 한 바퀴 돌면서
    - 다시 `i`번째 element부터 첫 번째 원소까지 서로 인접한 원소들에 대해 거꾸로 array를 살펴본다.
    - 서로 인접한 원소 가운데 앞의 원소가 뒤의 원소보다 크다면 서로 교환한다.
- 이런 식으로 정렬할 위치를 직접 찾아 insert하는 알고리즘이다.
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

void insertion_sort(vector<int>& arr){
    int n = arr.size();
    int i, j , key;
    for(i = 1; i < n; i++){
        // 현재 위치의 값을 key에 저장
        key = arr[i];

         /*
        현재 정렬된 배열은 i-1까지이므로 i-1번째부터 역순으로 조사한다.
        j 값은 음수가 아니어야 되고
        key 값보다 정렬된 배열에 있는 값이 크면 
        그 위치로부터 현재 위치까지 모든 값을 오른쪽으로 한 칸씩 이동
        */
        for (j-1; j>=0 && arr[j]>key; j--){
            arr[j+1] = arr[j];// 오른쪽으로 이동
        }
        arr[j+1] = key; // key 값을 알맞은 위치에 저장
    }
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


    // ','로 분리하여 숫자들을 추출
    while (ss >> ch >> num && ch == '[' || ch == ',') {
        arr.push_back(num);
    }

    insertion_sort(arr);

    cout << "Sorted array: ";
    for (int i : arr) {
        cout << i << " ";
    }

    return 0;
}

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