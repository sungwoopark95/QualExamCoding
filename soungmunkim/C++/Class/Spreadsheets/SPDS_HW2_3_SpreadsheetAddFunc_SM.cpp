#include <iostream>
#include <vector>
#include <functional>
#include <variant>
#include <string>
#include <map>
#include "SPDSHW2_1_Spreadsheet.h"

using namespace std;  // 표준 라이브러리 네임스페이스 사용

class SmartSpreadsheet : public Spreadsheet {
private:
    // 각 셀이 참조하는 다른 셀의 인덱스와 그 셀에 적용할 lambda 함수를 저장하는 구조체
    struct CellFunction {
        function<string(string)> lambda; // 입력값이 string이고 반환값도 string인 lambda 함수
        string operandIdx;               // 참조하는 셀의 인덱스
    };

    // 각 셀에 대한 참조 정보와 lambda 함수를 저장하는 맵
    map<string, CellFunction> functions;

    // 주어진 셀과 연관된 모든 종속 셀의 값을 업데이트하는 메서드
    void update_dependent_cells(string idx) {
        for (const auto& [key, cellFunc] : functions) {
            if (cellFunc.operandIdx == idx) {
                // 종속 셀의 값을 업데이트
                set_function(key, cellFunc.lambda, cellFunc.operandIdx);
                // 해당 종속 셀과 연관된 다른 종속 셀도 업데이트
                update_dependent_cells(key);
            }
        }
    }

public:
    // 특정 위치에 lambda 함수와 참조 셀의 정보를 설정하는 함수
    void set_function(string idx, function<string(string)> func, string operandIdx) {
        // operandIdx 셀의 값을 가져와 func에 적용한 결과를 idx 셀에 설정
        string operandValue = Spreadsheet::get_value(operandIdx);
        Spreadsheet::set_value(idx, func(operandValue));

        CellFunction cellFunc = {func, operandIdx};
        functions[idx] = cellFunc;
    }

    // 특정 위치에 값을 설정하는 함수 (재정의)
    void set_value(string idx, string value) {
        Spreadsheet::set_value(idx, value);
        // idx 셀의 값이 변경된 경우, 이 셀에 종속된 모든 셀의 값을 업데이트
        update_dependent_cells(idx);
    }

    // 특정 위치의 값을 가져오는 함수 (재정의)
    string get_value(string idx) override {
        return Spreadsheet::get_value(idx);
    }
};
