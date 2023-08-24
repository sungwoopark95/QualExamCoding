/*
[Radix sort 구현]
Radix Sort는 낮은 자리수부터(일의자리, 십의자리, 등) 비교하여 정렬해 간다는 것을 기본 개념으로 정렬하는 알고리즘이다.
비교 연산을 하지 않으며 정렬 속도가 빠르지만 데이터 전체 크기에 기수 테이블의 크기만한 메모리가 더 필요하다. (공간 복잡도가 높아진다.)
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 주어진 숫자의 특정 자릿수의 값을 반환하는 함수
int getDigit(int num, int digit_place) {
    // num을 digit_place로 나누어 주어진 자릿수의 값을 1의 자리로 이동시킨 후
    // % 10 연산을 통해 해당 자릿수의 숫자만 추출합니다.
    return (num / digit_place) % 10;
}

void radixSort(vector<int>& arr) {
    // arr 내에서 가장 큰 값을 찾아 max에 저장
    // 주어진 배열에서 최대값을 찾음
    int n = arr.size();

    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];

    // 현재 확인하려는 자릿수를 나타내는 변수 (1의 자리부터 시작)
    int digit_place = 1;

    // 정렬 중간 결과를 저장할 임시 벡터
    vector<int> result(arr.size());

    // max의 마지막 자릿수까지 반복
    while (max / digit_place > 0) {
        // 0부터 9까지의 숫자에 대한 카운팅을 위한 배열
        int count[10] = {0};

        // 현재 자릿수에 따라 arr의 각 숫자를 카운트
        for (int i = 0; i < arr.size(); i++)
            count[getDigit(arr[i], digit_place)]++;

        // 카운트 배열을 누적 카운트 배열로 변환
        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        // 누적 카운트 배열을 사용하여 숫자를 결과 벡터에 배치
        for (int i = arr.size() - 1; i >= 0; i--) {
            result[count[getDigit(arr[i], digit_place)] - 1] = arr[i];
            count[getDigit(arr[i], digit_place)]--;
        }

        // 결과 벡터의 내용을 원래 벡터에 복사
        for (int i = 0; i < arr.size(); i++)
            arr[i] = result[i];

        // 다음 자릿수를 확인하기 위해 digit_place를 10배로 늘림
        digit_place *= 10;
    }
}

int main() {
    vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};

    // 배열을 Radix Sort로 정렬
    radixSort(arr);

    // 정렬된 배열 출력
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
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

    radixSort(arr, size);

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

    radixSort(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
*/