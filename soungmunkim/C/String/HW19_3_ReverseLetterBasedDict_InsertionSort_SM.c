/*
사용자로부터 영어 알파벳 대/소문자 10개를 입력 받은 후 이를 사전 기준 역순으로 출력하는 함수

1. 단, 동일 알파벳의 대/소문자가 같이 있는 경우 대문자가 앞에 출력되도록 한다.
2. 역순으로 정렬 시 Insertion Sort 알고리즘을 변형하여 사용
3. 동일 알파벳이 중복해서 입력으로 주어지지는 않는다고 가정 (단, 대/소문자로
구분되는 경우는 제외)
    ex) A a는 가능 (AA or aa 는 불가능)
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_NUMS 10

void InsertionSortReverse(char list[]);
int main(int argc, char* argv[])
{
  char chars[MAX_NUMS]; //List of characters to be sorted

  if (argc < MAX_NUMS){
    printf("Please give %d inputs\n", MAX_NUMS);
    return -1;
  }
  

  for (int index=0; index < MAX_NUMS; index++)
  {
    chars[index] = argv[index + 1][0];    
  }

  InsertionSortReverse(chars); //Call sorting routine

  //Print sorted list  
  for (int index = 0; index < MAX_NUMS; index++)
    printf("%c", chars[index]);

  return 0;
}
/* Do not modify above*/

void InsertionSortReverse(char list[])
{
  /* Write your code here */	

}
