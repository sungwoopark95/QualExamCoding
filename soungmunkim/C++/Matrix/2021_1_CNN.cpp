/*
[CNN 구현하기] -> 2d array인 matrix 활용법: vector 두개 쌓기

image: m x n np array
pattern: n x n np array
stride도 감안해야 함 (Padding, Dilation 등은 없음)
    stride 기본 값인 1
m < n이거나, stride와 m, n이 정확히 맞아 떨어지지 않으면 error 출력

(base) soungmunkim@gimseongmun-ui-MacBookPro PreviousExams % g++ -std=c++17 2021_1_CNN.cpp -o CNN
(base) soungmunkim@gimseongmun-ui-MacBookPro PreviousExams % ./CNN
15 18 
30 35 
*/

#include <iostream>
#include <vector>

using namespace std;

// conv. 연산 수행하는 함수
vector<vector<double> > conv(const vector<vector<double> >& image,
                                const vector<vector<double> >& pattern,
                                int stride = 1) {
    // 이미지와 패턴의 크기를 얻음
    int m = image.size();
    int n  = pattern.size();

    // 패턴 차원이 이미지 차원보다 클 경우 -> error
    if(m < n)
        printf("Error: m < n\n");
    
    // stride 값에 따라 output size가 정수가 아니면 -> error
    if((m-n) % stride != 0)
        printf("Error: Encompatible stride, m, and n\n");

    // conv 연산 결과를 저장할 array 크기 계산
    int output_size = (m-n) / stride + 1;

    /*
     vector<vector<double>> 이것은 2차원 벡터를 의미
        각 내부 벡터는 double 타입의 원소를 저장합니다.
    result(output_size, vector<double>(output_size, 0.0)) 
        이 코드는 result라는 2차원 벡터를 초기화하는 것
        첫 번째 매개변수인 output_size는 result 벡터의 크기, 즉 row의 수
        두 번째 매개변수인 vector<double>(output_size, 0.0)는 각 row에 대한 초기화 값을 제공
        여기서 각 row은 double 타입의 원소를 output_size만큼 가지며, 모든 원소의 초기값은 0.0
   
    결론적으로, 위 코드는 output_size x output_size 크기의 2차원 벡터를 생성하고, 모든 원소를 0.0으로 초기화합니다. 
    */
    vector<vector<double> > result(output_size, vector<double>(output_size, 0.0));

    // conv. 연산을 수행합니다.
    for (int i = 0; i < output_size; i++) {
        for (int j = 0; j < output_size; j++) {
            double sum = 0;
            for (int x = 0; x < n; x++) {
                for (int y = 0; y < n; y++) {
                    sum += image[i*stride + x][j*stride + y] * pattern[x][y];
                }
            }
            // 합산된 결과를 결과 배열에 저장합니다.
            result[i][j] = sum;
        }
    }

    return result;
    
}


int main() {
    // 예제 이미지와 패턴을 선언합니다.
    vector<vector<double>> image = {
        {1, 2, 3, 3, 3},
        {4, 5, 6, 6, 6},
        {7, 8, 9, 9, 9},
        {10, 11, 12, 13, 13},
        {10, 11, 12, 13, 13}
    };

    vector<vector<double>> pattern = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    try {
        // 합성곱 연산을 수행하고 그 결과를 저장합니다.
        vector<vector<double>> result = conv(image, pattern, 2);

        // 합성곱 연산의 결과를 출력합니다.
        /*
        for 루프는 result의 모든 행 (row)에 대해 반복되며, 내부의 for 루프는 해당 row의 각 double val을 반복
        */
        for (const auto& row : result) {
            for (double val : row) {
                cout << val << " ";
            }
            cout << endl;
        }

    // try쪽에서 예외가 발생했을 때 그 예외에 대한 정보를 출력하는 것
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }

    return 0;
}




