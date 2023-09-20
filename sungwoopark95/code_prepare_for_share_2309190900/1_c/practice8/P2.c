/* Description
 * Write a function to return an natural number in base 4
 * (using only the digits 0,1,2,3) 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int base_four(int n){
    /* YOUR CODE HERE */
	int ans=0;
	int idx=0;
	int quotient, remainder;
	while (n>0){
		remainder=n%4;
		ans+=remainder*(int)(round(pow(10, idx++))); // pow 함수가 double 형의 argument이며, output도 double이기 때문에 int로 다루기 위해서는 round 함수를 써주고 int로 typecast를 해야 안정적인 코드 구현이 가능
		printf("%d\n", ans);
		n/=4;
	}
	return ans;


}

/* Do not modify below */
int main(void){
	int n;
	int f;
    //printf("\nEnter the number u want to change into base four: ");
    scanf(" %d", &n);
	f = base_four(n);
	printf("%d\n",f);

	return 0;
}


