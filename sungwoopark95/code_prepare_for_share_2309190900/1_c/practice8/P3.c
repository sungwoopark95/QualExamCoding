/* P3: 소인수분해(Integer factorization):
Write a program that factorizes integers. 
For example, if an input is 56, then the output should be (2,3) (7,1).
The first input must be the number of inputs that you want to factorize.
The rest input(s) must be the integer(s) you want to factorize.
*/

#include <stdio.h>

void factorize(int n, int start_val){
  if (n==1) {printf("\n");}

  int divisor=0;
  int num_divide=0;

  for (int i=start_val+1; i<n/2;++i){
    if (n%i==0) {
      divisor=i;
      break;}
  }

  if (divisor>0) {
    num_divide=0;
    while (n%divisor==0){
      n/=divisor;
      num_divide++;
    }
    printf("(%d,%d) ", divisor, num_divide);
    if (n!=1) {factorize(n, divisor);}
    else {printf("\n");}
    
  }
  else {
    printf("(%d,1)\n", n);
  }


}

int main(void)
{
  int num; // First input: number of input(s) that you want to factorize
  int n; // Rest input(s): what to factorize

  //printf("Enter how many numbers you want to factorize: "); 
  scanf(" %d", &num);

  while (num > 0){

    //printf("\nEnter the numbers you want to factorize: ");
    scanf(" %d", &n);

    /*
    YOUR CODE HERE
    */
   factorize(n, 1);
   num--;

  } 
  return 0;
}