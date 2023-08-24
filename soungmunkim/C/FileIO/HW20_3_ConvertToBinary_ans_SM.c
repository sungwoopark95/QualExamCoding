/*
[Text file 읽고 숫자 binary로 바꿔 Ouput file에 쓰기]
텍스트 파일 이름 두 개를 입력으로 받는다. 
차례대로 입력 파일, 출력 파일의 이름이 된다. 입력 파일은 여러 줄로 되어 있고, 각 줄에는 1보다 큰 자연수 한 개가 적혀있다. 
각각의 자연수를 2진법으로 변환해서 출력 파일의 각 줄에 적어야 한다.(첨부 파일의 예시 입력 파일과 정답 출력 파일을 참고) 다음 조건을 만족해야 한다.
• 다음과 같은 형식으로 파일에 적어야 한다. 
    ◼ 7 = 111
    ◼ 540 = 1000011100
• 10진법 숫자와 등호(=) 사이, 등호와 2진법 숫자 사이에는 space 한 개가 있다.
• 입력 파일에 적힌 순서대로 출력 파일의 각 줄마다 작성한다.
• 실제로 test를 할 때에는 출력 파일은 처음에 없는 상태에서 프로그램을 실행하면 알맞게 적힌 파일이 생겨야 한다.

TestCase1)
./P3 P3_input1.txt P3_output1.txt
*/
#include <stdio.h> 
#include <string.h> 

int main(int argc, char *argv[]) {
    FILE *input_file; // 입력 파일 포인터
    FILE *output_file; // 출력 파일 포인터
    char *input_filename = argv[1];
    char *output_filename = argv[2];

    // input file을 읽기 모드로, output file은 쓰기 모드로
    input_file = fopen(input_filename, "r");
    output_file = fopen(output_filename, "w");
    int num = 0; // 숫자 저장하기 위한 변수 지정

    // input file로부터 숫자를 읽어오는 동안 반복
    while(fscanf(input_file, "%d", &num) != EOF){
        // output file에 숫자 기록하고 = 붙임
        fprintf(output_file, "%d = ", num);

        int num_bin = 0; // 2진수 저장하는 변수
        int i = 1;
        while( num > 1){
            // 현재 숫자의 나머지를 이용해 2진수의 현재 자리 값 결정
            num_bin += (num % 2) * i;
            num = num / 2; 
            i *= 10; // 다음 자릿수로 넘어감 
        }
        num_bin += i; // 마지막 자리 처리 (1의 자리)

        // 2진수 값을 output file에 기록
        fprintf(output_file, "%d\n", num_bin);
    }
    // 열었던 파일들 닫기
    fclose(input_file);
    fclose(output_file);

    return 0;
}