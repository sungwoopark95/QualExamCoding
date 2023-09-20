#include "wordcount.h"
#include <iostream>
#include <sstream>
#include <map>
using namespace std;
void num_to_string(int x){
  if (x==1){ cout << "once";}
  else if (x==2){ cout << "twice";}
  else {cout << x << " times";}
}

void wordcount(string sentences) {
  // store number of total words
  unsigned int total_words = 0;

  // TODO: calculate word counts
  string tmp_string;
  stringstream mystream(sentences);
  map<string, int> mydict;
  while (mystream>>tmp_string){
    mydict[tmp_string]++;
    total_words++;
  }
  cout << "Total number of words: " << total_words << endl;

  // TODO: print number of appearances for each word
  map<string, int>::iterator m;
  for (m=mydict.begin(); m!=mydict.end(); m++){
    cout << "Word \"" << m->first << "\" appears ";
    num_to_string(m->second);
    cout<<".\n";
  }
}


// Word "love" appears once.