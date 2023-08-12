/*
주어진 뼈대 코드를 수정하여 입력으로 주어진 2 개의 character의 순서를 바꾼 후 함수의 입력으로 들어온 첫 번째 포인터를 반환하는 함수를 작성하여라. 
*/

#include <stdio.h>
#include <stdlib.h>

/* Correct below function to swap two characters pointed by x and y 
  Then return the first pointer */
char* swap_pointers(char *x, char *y)
{
  /* Write your code here */
    char temp = *x;
    *x = *y;
    *y = temp;
    return x;
 /* Do no modify below */
}


int main(int argc, char* argv[])
{  
  if (argc != 3){       /* When the number of inputs is not 2 */
    printf("Please input 2 characters\n");
    return -1;
  }     

  char* s1 = argv[1];
  char* s2 = argv[2];   

  char* t1;  
  
  t1 = swap_pointers(s1,s2);  
  printf("%s,%s,%s\n", s1,s2,t1);  
  return 0;
}
