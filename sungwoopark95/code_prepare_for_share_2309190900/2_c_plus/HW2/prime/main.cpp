#include <cstdlib>
#include <iostream>
#include <math.h>

int main() {
  unsigned int start_num;
  unsigned int end_num;

  std::cout << "Find prime number within a range:\n";
  std::cout << "--------------------------------------\n";
  std::cout << "-> The start of the range: ";
  // TODO: set start_num
  std::cin >> start_num;

  std::cout << "-> The end of the range: ";
  // TODO: set end_num
  std::cin >> end_num;

  std::cout << "\nThe prime numbers between " << start_num
            << " and " << end_num << " are:" << std::endl;

  // TODO: print prime numbers
  int res=0;
  int flag=0;
  int j;
  for (int i=start_num; i<=end_num; i++){
    if (i==1) { continue;}
    flag=1;
    for (int j=2; j<=i/2; j++){
      if (i%j==0){
        flag=0;
        break;}

    }
    if (flag==1){
      std::cout << i << " ";
    }
    
  }
  return EXIT_SUCCESS;
}
