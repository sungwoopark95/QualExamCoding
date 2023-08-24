/*
[spreadsheet 만들기]c++로 구현 실패 (ouptut이 안 나옴)
g++ SPDSHW2_1_Spreadsheet_SM.cpp -o SPDSHW2_1_Spreadsheet_SM  

!! ostringstream 객체인 oss는 정수를 문자열로 변환하고, 다른 문자열과 함께 문자열을 조립하는 데 사용
!! str() 메서드는 oss에 저장된 문자열을 반환

Microsoft Excel과 유사하게 데이터를 저장하고 읽을 수 있는 스프레드시트를 class Spreadsheet로 구현하라. 

Spreadsheet의 제약조건은 아래와 같다.
• 스프레드시트는 10개의 row, 10개의 column으로 구성된다. 
    Microsoft Excel과 유사하게 column은 알파벳(A, B, ..., J, 혹은 a, b, ..., j)으로, 
    row는 정수(1, 2, 3, ..., 10)로 indexing한다.
• 스프레드시트의 각 셀은 int, bool, string을 저장할 수 있다. 
    이 때 string은 whitespace 문자(\n, \t, space 등)를 포함하지 않는다고 가정한다.
• 생성자는 별도의 입력을 받지 않는다.
• Spreadsheet object를 print할 경우, Spreadsheet에 저장된 내용이 출력되어야 한다. 
    이 때 한 row 내의 element 사이는 comma(,) 한 개로 구분하고, row 사이는 개행(\n) 한 개로 구분하도록 하여 출력한다. 
    출력을 보기 좋게 만들기 위해 임의로 whitespace를 추가하여도 된다

      ,       , True  ,       ,       ,       ,       ,       ,       ,       , 
      ,       ,       ,       ,       ,       ,       ,       ,       ,       , 
5     ,       ,       ,       ,       ,       ,       ,       ,       ,       , 
      ,       ,       ,       ,       ,       ,       ,       ,       ,       , 
      ,       ,       ,       ,       , hello ,       ,       ,       ,       , 
      ,       ,       ,       ,       ,       ,       ,       ,       ,       , 
      ,       ,       ,       ,       ,       ,       ,       ,       ,       , 
      ,       ,       ,       ,       ,       ,       ,       ,       ,       , 
      ,       ,       ,       ,       ,       ,       ,       ,       ,       , 
      ,       ,       ,       ,       ,       ,       ,       ,       ,       , 
*/
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>
// #include </Users/soungmunkim/Desktop/Coding/gsds_qual/C++/Class/SPDSHW2_1_Spreadsheet.h>
#include "SPDS_HW2_1_Spreadsheet.h"

using namespace std;

// 스프레드시트를 표현하는 클래스
class Spreadsheet {
private:
    // 알파벳을 숫자 인덱스로 변환하기 위한 맵 (dictionary 같은 것)
    map<char, int> index;
    // 스프레드시트의 실제 데이터를 저장하는 2차원 벡터
    vector<vector<string> > matrix;

public:
    // 생성자
    Spreadsheet() {
        // 알파벳 인덱스 초기화
        index['A'] = 0; index['B'] = 1; index['C'] = 2; index['D'] = 3; index['E'] = 4;
        index['F'] = 5; index['G'] = 6; index['H'] = 7; index['I'] = 8; index['J'] = 9;

        // 2차원 벡터 초기화 (10x10 크기로 모두 빈 문자열로 채움)
        matrix = vector<vector<string> >(10, vector<string>(10, ""));
    }

    // 스프레드시트의 현재 상태를 문자열로 변환
    string to_string() {
        /*
        ostringstream 객체인 oss는 정수를 문자열로 변환하고, 
            다른 문자열과 함께 문자열을 조립하는 데 사용되었습니다. 
        str() 메서드는 oss에 저장된 문자열을 반환
        */
        ostringstream oss; // 출력 스트림을 사용하여 문자열 생성
        int max_width = 0;

        // 모든 셀을 순회하며 가장 긴 문자열의 길이를 찾음
        for (size_t rowIdx = 0; rowIdx < matrix.size(); ++rowIdx) {
            for (size_t colIdx = 0; colIdx < matrix[rowIdx].size(); ++colIdx) {
                const string& cell = matrix[rowIdx][colIdx];
                if (!cell.empty() && cell.length() > max_width) {
                    max_width = cell.length();
                }
            }
        }

        // 각 셀의 값을 문자열로 변환하여 oss에 저장
        // size_t: 객체의 크기를 나타내는 데 사용되는 부호 없는 정수 타입
        for (size_t rowIdx = 0; rowIdx < matrix.size(); ++rowIdx) {
            for (size_t colIdx = 0; colIdx < matrix[rowIdx].size(); ++colIdx) {
                const string& cell = matrix[rowIdx][colIdx];
                if (cell.empty()) {
                    oss << setw(max_width) << " " << " , ";
                } else {
                    oss << setw(max_width) << cell << " , ";
                }
            }
            oss << "\n";
        }
        return oss.str();
    }

    // 특정 위치에 값을 설정하는 함수
    void set_value(string idx, string value) {
        // 인덱스의 길이가 2가 아니라면 잘못된 입력
        if (idx.length() != 2) {
            cerr << "Invalid Index" << endl;
            return;
        }

        char j = idx[0];             // 문자 부분 (A-J)
        int i = idx[1] - '0';       // 숫자 부분 (1-10)

        // 유효한 인덱스인지 확인
        if (index.find(j) == index.end() || i < 1 || i > 10) {
            cerr << "Invalid Index" << endl;
            return;
        }

        // 지정된 위치에 값을 설정
        matrix[i-1][index[j]] = value;
    }

    // 특정 위치의 값을 가져오는 함수
    virtual string get_value(string idx) {
        // 인덱스의 길이가 2가 아니라면 잘못된 입력
        if (idx.length() != 2) {
            cerr << "Invalid Index" << endl;
            return "";
        }

        char j = idx[0];             // 문자 부분 (A-J)
        int i = idx[1] - '0';       // 숫자 부분 (1-10)

        // 유효한 인덱스인지 확인
        if (index.find(j) == index.end() || i < 1 || i > 10) {
            cerr << "Invalid Index" << endl;
            return "";
        }

        // 지정된 위치의 값을 반환
        return matrix[i-1][index[j]];
    }
};

// 전역 변수로 Spreadsheet 객체 선언
Spreadsheet sheet;

int main(int argc, char* argv[]) {
    // 입력된 명령어와 input의 개수를 확인
    if (argc < 3) {
        cerr << "Usage: ./program <command> <args...>" << endl;
        return 1;
    }

    string command = argv[1];

    // 입력된 명령어에 따라 적절한 동작 수행
    if (command == "set_value") {
        if (argc != 4) {
            cerr << "Usage: ./program set_value <index> <value>" << endl;
            return 1;
        }
        sheet.set_value(argv[2], argv[3]);
    } else if (command == "get_value") {
        if (argc != 3) {
            cerr << "Usage: ./program get_value <index>" << endl;
            return 1;
        }
        cout << sheet.get_value(argv[2]) << endl;
    } else if (command == "print") {
        cout << sheet.to_string() << endl;
    } else {
        cerr << "Unknown command" << endl;
        return 1;
    }

    return 0;
}
