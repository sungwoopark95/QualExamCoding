/*
텍스트 파일 이름을 입력으로 받는다. 
텍스트 파일은 여러 줄로 되어있고, 한 줄에는 자연수 2개가 space 하나로 구분되어 적혀있다. 
(예시 텍스트 파일 참고) 해당 텍스트 파일에 있는 모든 자연수를 붙여서 출력하는 프로그램을 작성하시오. 

P2_input1.txt
1 2
3 4
5 6
7 8
9 10
-> desired: 12345678910

P2_input2.txt
12 84
89 473
471 1
891 2
9381 12
-> 12848947347118912938112
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    char *input_filename = argv[1]; // name of input file
    // YOUR CODE HERE
    // 파일을 불러와서 읽는 코드
    FILE *file = fopen(input_filename, "r");
    int num1, num2;
    /*
    fscanf 함수는 형식 문자열에 따라 파일에서 데이터를 읽습니다. 
    이 함수는 성공적으로 읽은 항목의 수를 반환합니다. 
    따라서 fscanf(file, "%d %d", &num1, &num2) == 2는 두 개의 정수를 성공적으로 읽었는지 확인하는 조건입니다. 
    만약 파일에 더 이상 읽을 데이터가 없거나, 형식에 맞지 않는 데이터가 있으면 fscanf는 2를 반환하지 않아 while 루프가 종료됩니다.
    */
    int* ans = (int*)malloc(sizeof(int)); // 정수배열 동적할당
    int length = 0;
    while (fscanf(file, "%d %d", &num1, &num2) == 2) { 
        // scanf이므로 기본적으로 일반 변수는 그 주소값이 들어감
        ans[length++] = num1;
        ans[length++] = num2;
    }

    for (int j=0;j<length;j++) {
        printf("%d", ans[j]);
    }
    printf("\n");
    free(ans);
    fclose(file);
    return 0; 
}
