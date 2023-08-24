// SPDSHW2_1_Spreadsheet_SM.h

#pragma once // 다중 포함 방지

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>

using namespace std;

// 스프레드시트를 표현하는 클래스
class Spreadsheet {
protected:
    // 알파벳을 숫자 인덱스로 변환하기 위한 맵 (dictionary 같은 것)
    map<char, int> index;
    // 스프레드시트의 실제 데이터를 저장하는 2차원 벡터
    vector<vector<string> > matrix;

public:
    // 생성자
    Spreadsheet();

    // 스프레드시트의 현재 상태를 문자열로 변환
    string to_string();

    // 특정 위치에 값을 설정하는 함수
    void set_value(string idx, string value);

    // 특정 위치의 값을 가져오는 함수
    virtual string get_value(string idx);
};
