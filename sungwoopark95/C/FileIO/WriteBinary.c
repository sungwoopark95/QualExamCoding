/*
텍스트 파일 이름 두 개를 입력으로 받는다. 
차례대로 입력 파일, 출력 파일의 이름이 된다. 입력 파일은 여러 줄로 되어 있고, 각 줄에는 1보다 큰 자연수 한 개가 적혀있다. 
각각의 자연수를 2진법으로 변환해서 출력 파일의 각 줄에 적어야 한다. 
(첨부 파일의 예시 입력 파일과 정답 출력 파일을 참고) 

다음 조건을 만족해야 한다. 
• 다음과 같은 형식으로 파일에 적어야 한다. 
    ◼ 7 = 111 
    ◼ 540 = 1000011100 
• 10진법 숫자와 등호(=) 사이, 등호와 2진법 숫자 사이에는 space 한 개가 있다. • 입력 파일에 적힌 순서대로 출력 파일의 각 줄마다 작성한다. 
• 실제로 test를 할 때에는 출력 파일은 처음에 없는 상태에서 프로그램을 실행하면 알맞게 적힌 파일이 생겨야 한다. 

프로그램 실행 예시 (print되는 것은 아무것도 없고 출력 파일이 생성되어야 함) 

P3_input1.txt           P3_output1.txt
2                       2 = 10
3                       3 = 11
4                       4 = 100
5                       5 = 101
6                       6 = 110
7                       7 = 111
8                       8 = 1000
9                       9 = 1001
10                      10 = 1010
11                      11 = 1011
12                      12 = 1100
13                      13 = 1101
14                      14 = 1110
15                      15 = 1111
*/

#include <stdio.h>
#include <stdlib.h>

// 주어진 정수를 이진수로 변환하는 함수
int to_binary(int* bin, int num) {
    // bin: 이진수로 변환된 결과를 저장할 배열
    // num: 이진수로 변환할 정수
    // 반환값: `bin`의 길이
    int length = 0;
    // num이 0이 될 때까지 반복
    while (num) {
        // 현재 num의 나머지를 bin 배열에 저장
        bin[length++] = num % 2;
        // num을 2로 나눈 몫을 다시 num에 저장
        // 이렇게 되면 bin에는 역순으로 나열된 이진수가 저장됨 (ex. 10 -> 0101)
        // 파일 쓸 때 뒤집어줄 예정
        num = num / 2;
    }
    return length;
}

int main(int argc, char *argv[]){    
    // 입력 파일의 이름
    char *input_filename = argv[1];
    // 출력 파일의 이름
    char *output_filename = argv[2];

    // 입력 파일을 읽기 모드로 열기
    FILE* input = fopen(input_filename, "r");
    // 출력 파일을 쓰기 모드로 열기 (파일이 없으면 새로 생성)
    FILE* output = fopen(output_filename, "w");
    // 입력 파일 열기에 실패한 경우 에러 메시지 출력
    if (input == NULL) {
        printf("Failed to open the input file");
        return 1;
    }

    // 입력 파일의 각 줄에서 정수를 읽어서 num에 저장
    int num;
    while (fscanf(input, "%d", &num) == 1) {
        // 이진수로 변환된 결과를 저장할 동적 배열 할당
        int* binary = (int*)malloc(sizeof(int));
        // 주어진 정수를 이진수로 변환하고, 변환된 이진수의 길이를 binlen에 저장
        int binlen = to_binary(binary, num);
        // 출력 파일에 원래의 정수와 변환된 이진수를 출력
        fprintf(output, "%d = ", num);
        for (int i=binlen-1;i>=0;i--) {
            // binary에는 역순으로 저장되어 있으므로, 파일에 쓸 때도 역순으로 써야 함
            fprintf(output, "%d", binary[i]);
        }
        fprintf(output, "\n");
        // 동적으로 할당된 배열 메모리 해제
        free(binary);
    }
    // 파일 스트림 닫기
    fclose(input);
    fclose(output);
    return 0;
}
