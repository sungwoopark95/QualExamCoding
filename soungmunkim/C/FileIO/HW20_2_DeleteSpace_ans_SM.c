/*
텍스트 파일 이름을 입력으로 받는다. 
텍스트 파일은 여러 줄로 되어있고, 한 줄에는 자연수 2개가 space 하나로 구분되어 적혀있다. (예시 텍스트 파일 참고) 
해당 텍스트 파일에 있는 모든 자연수를 붙여서 출력하는 프로그램을 작성하시오.
1 2
3 4
5 6
7 8
9 10

TestCase1)
./P2 P2_input1.txt 
12345678910
*/
#include <stdio.h>

int main(int argc, char *argv[]){
    FILE *file; //File pointer 선언
    char *filename = argv[1]; // input으로 받은 파일 이름 저장
    file = fopen(filename, "r"); // 해당 파일을 읽기 모드로 열기
    int i = 0;
    char str[300];

    // fscanf 함수를 이용하여 파일 읽음 
    // fscanf는 공백, 줄바꿈 등 자동으로 무시하면서 문자열 읽어옴
    while(fscanf(file, "%s", str) != EOF){ // EOF(end of file)에 도달할 때까지 반복
        int j = 0;
        // 문자열의 끝에 도달할 때까지 문자를 하나씩 출력함
        while (str[j] != '\0'){
            printf("%c", str[j]);

            j += 1;
        }
    }
    // 출력 끝난 후 줄바꿈 처리
    printf("\n");   

    /* 
    // fgets 함수를 이용하여 파일을 줄 단위로 읽음
    // 주석 처리된 코드 부분
    char ans[300];
    while(fgets(str, 300, file)){
        int j = 0;
        // 문자열의 끝(\0)에 도달할 때까지 문자를 하나씩 검사
        while (str[j] != '\0'){
            // 공백과 줄바꿈이 아닌 문자만 ans 배열에 저장
            if (str[j] != ' ' && str[j] != '\n'){
                ans[i] = str[j];
                i += 1;
            }
            j += 1; // 문자열의 다음 인덱스로 이동
        }
    }
    ans[i] = '\0'; // 문자열의 끝을 나타내는 null 문자를 추가
    printf("%s\n", ans);    
    */

   // 파일 닫음
   fclose(file);

   return 0;
}