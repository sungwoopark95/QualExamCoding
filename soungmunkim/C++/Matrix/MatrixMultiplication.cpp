/*
두 matrix 곱셈하기
*/

#include <iostream>
#include <vector>

using namespace std;

// 두 행렬의 곱셈을 수행하는 함수
vector<vector<int>> matrixMultiplication(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    // 행렬 A와 B의 행과 열의 크기를 구합니다.
    int rowsA = A.size();
    int colsA = A[0].size();
    int rowsB = B.size();
    int colsB = B[0].size();

    // 행렬 곱셈의 조건을 검사합니다. 행렬 A의 열의 수와 행렬 B의 행의 수가 같아야 합니다.
    if (colsA != rowsB) {
        // 조건에 맞지 않으면 예외를 발생시킵니다.
        throw runtime_error("행렬 A의 열 수와 행렬 B의 행 수가 일치하지 않습니다. 행렬 곱셈을 수행할 수 없습니다.");
    }

    // 결과를 저장할 행렬을 초기화합니다.
    vector<vector<int>> result(rowsA, vector<int>(colsB, 0));

    // 행렬 곱셈을 수행합니다.
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            for (int k = 0; k < colsA; ++k) {
                // A의 i번째 행의 원소와 B의 j번째 열의 원소를 곱하여 결과 행렬의 (i, j) 위치에 더합니다.
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // 결과 행렬을 반환합니다.
    return result;
}

int main() {
    // 테스트용 행렬 A와 B를 정의합니다.
    vector<vector<int>> A = {
        {1, 2, 3},
        {4, 5, 6}
    };

    vector<vector<int>> B = {
        {7, 8},
        {9, 10},
        {11, 12}
    };

    try {
        // 행렬 곱셈 함수를 호출하여 결과를 얻습니다.
        vector<vector<int>> C = matrixMultiplication(A, B);
        
        // 결과 행렬 C를 화면에 출력합니다.
        for (const auto& row : C) {
            for (int val : row) {
                cout << val << " ";
            }
            cout << endl;
        }
    } catch (const exception& e) { // 예외가 발생하면 에러 메시지를 출력합니다.
        cerr << e.what() << endl;
    }

    return 0;
}
