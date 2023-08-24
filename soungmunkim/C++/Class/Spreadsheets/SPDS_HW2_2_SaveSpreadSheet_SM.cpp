#include <iostream>  // 입출력 관련 기능을 사용하기 위한 헤더
#include <fstream>   // 파일 입출력 관련 기능을 사용하기 위한 헤더
#include <vector>    // 동적 배열을 위한 vector 클래스 헤더
#include <stdexcept> // 예외 처리 관련 헤더
#include "SPDSHW2_1_Spreadsheet.h"

// PermanentSpreadsheet는 스프레드시트의 데이터를 파일에 저장하거나 불러오는 기능을 제공합니다.
class PermanentSpreadsheet : public Spreadsheet {
public:
    // 스프레드시트의 데이터를 주어진 파일 이름으로 저장합니다.
    void export_sheet(const string& filename) {
        ofstream file(filename);  // 주어진 이름으로 파일을 쓰기 모드로 엽니다.

        if (!file.is_open()) {  // 파일 열기가 실패하면 예외를 발생시킵니다.
            throw runtime_error("파일을 쓰기 모드로 열 수 없습니다.");
        }

        // 전체 10x10 스프레드시트를 순회하며 각 셀의 데이터를 파일에 저장합니다.
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                string cell_value = matrix[i][j];
                if (!cell_value.empty()) {  // 셀에 값이 있다면
                    char column = 'A' + j;  // 컬럼 이름을 계산합니다.
                    file << column << (i+1) << ":" << cell_value << "\n";  // 파일에 "A1:값" 형태로 저장합니다.
                }
            }
        }

        file.close();  // 파일 저장을 마치면 파일을 닫습니다.
    }

    // 주어진 파일 이름에서 스프레드시트의 데이터를 불러옵니다.
    void import_sheet(const string& filename) {
        ifstream file(filename);  // 주어진 이름으로 파일을 읽기 모드로 엽니다.

        if (!file.is_open()) {  // 파일 열기가 실패하면 예외를 발생시킵니다.
            throw runtime_error("파일을 읽기 모드로 열 수 없습니다.");
        }

        // 스프레드시트의 데이터를 초기화합니다.
        matrix = vector<vector<string>>(10, vector<string>(10, ""));

        string line;
        while (getline(file, line)) {  // 파일에서 한 줄씩 읽습니다.
            char column = line[0];  // 컬럼 정보를 추출합니다.
            int row = line[1] - '0';  // 행 정보를 추출합니다.
            string value = line.substr(3);  // "A1:" 형태를 건너뛰고 셀의 값을 추출합니다.

            set_value(column, row, value);  // 추출한 값을 스프레드시트에 설정합니다.
        }

        file.close();  // 데이터 로딩을 마치면 파일을 닫습니다.
    }

    // 주어진 column과 row 위치에 값을 설정하는 함수
    void set_value(char column, int row, const string& value) {
        int columnIndex = column - 'A';  // 컬럼 정보를 숫자로 변환합니다.
        int rowIndex = row - 1;  // 행 정보를 0-based 인덱스로 변환합니다.

        matrix[rowIndex][columnIndex] = value;  // 스프레드시트의 해당 위치에 값을 저장합니다.
    }
};