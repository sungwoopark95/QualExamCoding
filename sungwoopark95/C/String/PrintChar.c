/*
뼈대 코드의 main 함수 안에는 아래와 같은 string array가 정의되어 있다. 
0 이상 3 이하의 4개의 정수 i, j, k, l을 입력 받아 string array의 i번째 element의 0번째 character,  
j번째 element의 1번째 character, k번째 element의 2번째 character, 
l번째 element의 3번째 character를 출력하는 함수를 완성하여라. 

예시 1)
./P1 0 0 0 0 
ABCD

예시2)  
./P1 0 2 0 2 
AJCL
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

    if (argc < 4){
        printf("Please input at least 4 integers\n");
    }

    int i = atoi(argv[1]);
    int j = atoi(argv[2]);
    int k = atoi(argv[3]);
    int l = atoi(argv[4]);
    // for (int i=0;i<5;i++) {
    //     printf("%s ", argv[i]);
    // }
    // printf("\n");

    char *alphabet[] = {"ABCD", "EFGH", "IJKL", "MNOP"};  

    char a, b, c, d;

    /* Write your code here */
    a = alphabet[i][0];
    b = alphabet[j][1];
    c = alphabet[k][2];
    d = alphabet[l][3];

    /* do not modify below */

    printf("%c%c%c%c\n", a,b,c,d);
    return 0;
}
