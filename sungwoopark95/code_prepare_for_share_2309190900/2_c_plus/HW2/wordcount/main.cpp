#include <cstdlib>
#include <iostream>
#include "wordcount.h"

int main() {
  std::string sentences =
    "Doubt thou the stars are fire "
    "Doubt that the sun doth move "
    "Doubt truth to be a liar "
    "But never doubt I love";
  std::cout << "Given string: \"" << sentences << "\"\n" << std::endl;

  wordcount(sentences);

  return EXIT_SUCCESS;
}
