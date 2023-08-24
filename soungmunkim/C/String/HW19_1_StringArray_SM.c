/*
string array에서 0 이상 3 이하의 4개의 정수 i, j, k, l을 입력 받음

1. string array의 i번째 element의 0번째 character
2. j번째 element의 1번째 character
3. k번째 element의 2번째 character
4. l번째 element의 3번째 character를 출력하는 함수

char *alphabet[] = {"ABCD", "EFGH", "IJKL", "MNOP"};
TestCase1)
./P1 0 0 0 0 
ABCD
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

// 입력받은 input이 4개보다 적을때 경고메시지
  if (argc < 4){
    printf("Please input at least 4 integers\n");
  }

  int i = atoi(argv[1]);
  int j = atoi(argv[2]);
  int k = atoi(argv[3]);
  int l = atoi(argv[4]);

  char *alphabet[] = {"ABCD", "EFGH", "IJKL", "MNOP"};  

  char a, b, c, d;
    
  /* Write your code here */
  a = alphabet[i][0];
  b = alphabet[j][1];
  c = alphabet[k][2];
  d = alphabet[l][3];

  /*do not modify below*/

  printf("%c%c%c%c\n", a,b,c,d);
  return 0;
}